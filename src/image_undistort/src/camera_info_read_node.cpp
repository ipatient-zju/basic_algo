#include "image_undistort/camera_info_read.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "camera_info_read_node");
    ros::NodeHandle nh,private_nh("~");
    
    ROS_INFO("Started camera_info_read_node ...");
    
    CameraInfoRead camerainforead(nh,private_nh);
    
    ros::spin();
    
    return 0;
}