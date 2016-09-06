#include "frame_conversion.h"
#include <boost/concept_check.hpp>
/*****************************
 *  |xw|   |cos(yaw)  sin(yaw)  tx | |xn|
 *  |yw| = |-sin(yaw) cos(yaw)  ty | |yn|
 *  |1 |   |	0	 0      1  | |1 |
 * 
 *  yaw 为 n系相对于w系转动的角度，顺时针为正
 *  (tx,ty)为n系原点在w系下的坐标点
 * 
****************************/




//TODO : Rotation matrix: R_body2ned
Matrix3d FrameConversion::quaternion2mat(Quaterniond q)
{
    Matrix3d m;
    double q0=q.w(),q1=q.x(),q2=q.y(),q3=q.z();
    m<< q0*q0+q1*q1-q2*q2-q3*q3,2*(q1*q2-q0*q3),2*(q1*q3+q0*q2),
	2*(q1*q2+q0*q3),q0*q0-q1*q1+q2*q2-q3*q3,2*(q2*q3-q0*q1),
	2*(q1*q3-q0*q2),2*(q2*q3+q0*q1),q0*q0-q1*q1-q2*q2=q3*q3;
    return m;
}
//TODO:R_n_g; frameg 相对 framen转动的角度为yaw,逆时针为正或者可以说framen相对于frameg转动的角度，顺时针为正
Matrix3d FrameConversion::yaw2mat(double yaw)
{
    Matrix3d m;
    double cy = cos(yaw);
    double sy = sin(yaw);
    
    m<< cy,  sy, 0,
	-sy, cy,  0,
	0,   0,  1;
	
    return m;
}
Matrix4d FrameConversion::c_n2g(double yaw, Vector3d t_n2g)
{
    Matrix4d c;
    Matrix3d r;
    r = yaw2mat(yaw);
    c << r(0),r(1),r(2),t_n2g(0),
	 r(3),r(4),r(5),t_n2g(1),
	 r(6),r(7),r(8),t_n2g(2),
	  0  ,  0 ,  0 ,  1 ;
    
}

Matrix4d FrameConversion::c_b2n(Quaterniond q, Vector3d t_b2n)
{
    Matrix4d c;
    Matrix3d r;
    r = quaternion2mat(q);
    c << r(0),r(1),r(2),t_b2n(0),
	 r(3),r(4),r(5),t_b2n(1),
	 r(6),r(7),r(8),t_b2n(2),
	  0  ,  0 ,  0 ,  1 ;
}


