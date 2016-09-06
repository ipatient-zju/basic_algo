#include "image_undistort/image_undistort.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "image_undistort_node");
    ros::NodeHandle nh,private_nh("~");
    ROS_INFO("Starting image_undistort_node...");
    
    ImageUndistort imageundistort(nh,private_nh);
    ros::spin();
    return 0;
}