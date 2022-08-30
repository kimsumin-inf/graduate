#include <ros/ros.h>
#include <opencv2/opencv.hpp>
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
    void center_CB(cv::Point p1, cv::Point p2);

    ros::Subscriber subCAM;
    ros::Subscriber subCNT;
    ros::Subscriber subBBOX;

    cv::Mat frame; 
    cv_bridge::CvImagePtr cv_ptr;
    darknet_ros::BoundingBoxes bbox;
    darknet_ros::ObjectCount cnt;


public:
    tracking();
};