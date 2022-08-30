#pragma Once

#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/tracking.hpp>
#include <cv_bridge/cv_bridge.h>

#include <darknet_ros_msgs/BoundingBoxes.h>
#include <darknet_ros_msgs/ObjectCount.h>
#include <std_msgs/Int32.h>
#include <sensor_msgs/Image.h>

class tracking{
private:
    ros::NodeHandle nh;
    ros::NodeHandle pnh;

    void cam_CB(const sensor_msgs::Image::ConstPtr &msg);
    void bbox_CB(const darknet_ros_msgs::BoundingBoxes::ConstPtr &msg);
    void objcnt_CB(const darknet_ros_msgs::ObjectCount::ConstPtr &msg);
    cv::Point center(cv::Point p1, cv::Point p2);
    int calc_move_theta(cv::Point p);

    void show(std::string window_name, cv::Mat frame, int time);
    ros::Subscriber subCAM;
    ros::Subscriber subCNT;
    ros::Subscriber subBBOX;


    cv_bridge::CvImagePtr cv_ptr;
    darknet_ros_msgs::BoundingBoxes bbox;
    int cnt;
    cv::Ptr<cv::Tracker> tracker = cv::TrackerCSRT::create();

    int board_to_distance;
    bool init_detect;

    cv::Mat frame;
    cv::Mat obj_frame;
    cv::Point obj_center;
    cv::Rect2d predict_bbox;



public:
    tracking();
};