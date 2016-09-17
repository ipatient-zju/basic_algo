#include "path_output/path_output.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "path_output_node");
    //ros::NodeHandle nh;
    
    ROS_INFO("Started path_output_node ...");
    
    PathOutput pathoutput;
    
    ros::spin();
    
    return 0;
}