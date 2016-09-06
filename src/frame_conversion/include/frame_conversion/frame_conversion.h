#ifndef __FRAME_CONVERSION_H_
#define __FRAME_CONVERSION_H_

#include <iostream>
#include <Eigen/Geometry>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;

class FrameConversion{
public:
    Quaterniond euler2quaternion(Vector3d euler);
    Matrix3d quaternion2mat(Quaterniond q);
    Vector3d mat2euler(Matrix3d m);
    Quaterniond mat2quaternion(Matrix3d m);
    Matrix3d euler2mat(Vector3d euler);
    Vector3d quaternion2euler(Quaterniond q);
    Matrix3d yaw2mat(double yaw);
    Matrix4d c_n2g(double yaw, Vector3d t_n2g);
    Matrix4d c_b2n(Quaterniond q, Vector3d t_b2n);
    

};

#endif
