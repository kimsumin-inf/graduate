#include "grd_tracking/tracking.h"

using namespace std;
using namespace cv;

tracking :: tracking()
: nh(""), pnh("")
{
    subCAM= nh.subscribe("/usb_cam/image_raw", 1, &tracking::cam_CB, this);
    subCNT = nh.subscribe("/darknet_ros/found_object", 1, &tracking::objcnt_CB, this);
    subBBOX = nh.subscribe("/darknet_ros/bounding_boxes",1 , &tracking::bbox_CB, this);

    board_to_distance = 500;
    init_detect = true;

}

void tracking :: cam_CB(const sensor_msgs::Image::ConstPtr &msg){
    ROS_INFO("Cam Setting: (%d, %d)", msg->width, msg->height);
    try{
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::RGB8);
        frame = cv_ptr->image;
    } catch(cv_bridge::Exception &e){
        ROS_ERROR("Error to  Convert");
        return;
    }
}

void tracking :: bbox_CB(const darknet_ros_msgs::BoundingBoxes::ConstPtr &msg){
    bbox = *msg;
    if (init_detect == true && cnt == 1){
        for(auto i: bbox.bounding_boxes){
            obj_center = center(Point(i.xmin,i.ymin), Point(i.xmax, i.ymax));
            rectangle(frame, Rect(i.xmin, i.ymin, (i.xmin+i.xmax)/2, (i.ymin+i.ymax)/2), Scalar(0,0,255),1,LINE_AA);
            tracker->init(frame, Rect(i.xmin, i.ymin, (i.xmin+i.xmax)/2, (i.ymin+i.ymax)/2));
        }
        init_detect =false;
    }
    if (cnt = 1){
        for(auto i: bbox.bounding_boxes){
            obj_center = center(Point(i.xmin,i.ymin), Point(i.xmax, i.ymax));
            rectangle(frame, Rect(i.xmin, i.ymin, (i.xmin+i.xmax)/2, (i.ymin+i.ymax)/2), Scalar(0,0,255),1,LINE_AA);
            tracker->init(frame, Rect(i.xmin, i.ymin, (i.xmin+i.xmax)/2, (i.ymin+i.ymax)/2));        }
    }
    else {
        tracker->update(frame, predict_bbox);
        rectangle(frame, predict_bbox, Scalar(0,255,0),1,LINE_AA);
    }
}
void tracking :: objcnt_CB(const darknet_ros_msgs::ObjectCount::ConstPtr &msg){
    cnt = msg->count;

}
Point tracking :: center(Point p1, Point p2){
    return Point(round((p1.x+p2.x)/2), round((p1.y+p2.y)/2));
}

int tracking ::calc_move_theta(cv::Point p) {
    int width = frame.cols;
    int height = frame.rows;
    double theta;
    int dif = p.x - int(width/2);
    theta = atan2(board_to_distance, dif);


}

void tracking::show(std::string window_name, cv::Mat frame, int time) {
    imshow(window_name, frame);
    waitKey(time);
}