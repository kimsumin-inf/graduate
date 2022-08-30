#include "grd_tracking/tracking.h"

using namespace std;
using namespace cv;

tracking :: tracking()
: nh(""), pnh("")
{
    subCAM= nh.subscribe("/usb_cam/image_raw", 1, &tracking::cam_CB, this);
    subCNT = nh.subscribe("/darknet_ros/found_object", 1, &tracking::objcnt_CB, this);
    subBBOX = nh.subscribe("/darknet_ros/bounding_boxes",1 , &tracking::bbox_CB, this);

}

void tracking :: cam_CB(const sensor_msgs::Image::ConstPtr &msg){
    ROS_INFO("Cam Setting: (%d, %d)", msg->widht, msg->height);
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
}    
void tracking :: objcnt_CB(const darknet_ros_msgs::ObjectCount::ConstPtr &msg){
    cnt = *msg;
}
void tracking :: center_CB(Point p1, Point p2){
    return Point(round((p1.x+p2.x)/2), round((p1.y+p2.y)/2));
}
