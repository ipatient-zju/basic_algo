#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

#include <iostream>
#include <sstream>

#include <opencv2/opencv.hpp>

using namespace std;

cv::Mat dst;
bool flag = false;


void imageCallback(const sensor_msgs::ImageConstPtr &msg)
{
    cv_bridge::CvImagePtr cv_ptr;
    try{
	//cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
	cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch(cv_bridge::Exception& e)
    {
	ROS_ERROR("cv_bridge exception: %s", e.what());
	return;
    }
    
    dst = cv_ptr->image;
    flag = true;
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "image_to_video_node");
    ros::NodeHandle nh;
    
    string image_input_topic;
    int isColor,fps,width,height;
    nh.param("image_input_topic",image_input_topic,string("/mv_26804026/image_rect_color"));
    nh.param("isColor",isColor,1);
    nh.param("fps",fps,30);
    nh.param("width",width,640);
    nh.param("height",height,480);
    int count = 1;
    
    ros::Subscriber image_sub = nh.subscribe(image_input_topic.c_str(),10,imageCallback);
    cv::VideoWriter avi_writer("/home/aicrobo/out.avi",CV_FOURCC('P','I','M','1'),fps,cvSize(width,height),isColor);
    /***
     *	CV_FOURCC('P', 'I', 'M', '1') = MPEG-1 codec
	CV_FOURCC('M', 'J', 'P', 'G') = motion-jpeg codec
	CV_FOURCC('M', 'P', '4', '2') = MPEG-4.2 codec 
	CV_FOURCC('D', 'I', 'V', '3') = MPEG-4.3 codec 
	CV_FOURCC('D', 'I', 'V', 'X') = MPEG-4 codec 
	CV_FOURCC('U', '2', '6', '3') = H263 codec 
	CV_FOURCC('I', '2', '6', '3') = H263I codec 
	CV_FOURCC('F', 'L', 'V', '1') = FLV1 codec
     * 
     * */
    
    while (ros::ok())
    {
	ros::spinOnce();
	if (flag == true)
	{   
	    avi_writer.write(dst);
	    cout <<"image write count:"<< count << endl;
	    count++;
	    flag = false;
	}
    }
    return 0;
}