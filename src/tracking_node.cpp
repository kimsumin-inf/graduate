#include "grd_tracking/tracking.h"

int main(int argc, char** argv){
    ros::init(argc, argv, "stop_line");
    tracking tr;
    ros::spin();
    return 0;
}