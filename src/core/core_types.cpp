//---------------------------------------------------------------------------------------------------------------------
//  MICO - core plugin
//---------------------------------------------------------------------------------------------------------------------
//  Copyright 2019 Pablo Ramon Soria (a.k.a. Bardo91) pabramsor@gmail.com
//---------------------------------------------------------------------------------------------------------------------
//  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
//  and associated documentation files (the "Software"), to deal in the Software without restriction,
//  including without limitation the rights to use, copy, modify, merge, publish, distribute,
//  sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial
//  portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
//  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
//  OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
//  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//---------------------------------------------------------------------------------------------------------------------


#include <flow/DataFlow.h>
//
//#ifdef _WIN32
//	// https://stackoverflow.com/a/12229732/1304903
//	// In windows, there is not proper dynamic loading of libraries so the compiler complains about the undefined definicion of the
//	// static factory registration.... As what we will do is to load the registration types and block creation, we will just define the 
//	// variable to allow the generation of the shared library to be loaded by flow_kids.
//	std::vector<std::string> flow::TypeLog::registeredTypes_ = {};
//#endif

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <Eigen/Eigen>
#include <opencv2/opencv.hpp>
#include <string>

FLOW_TYPE_REGISTER(int, int)
FLOW_TYPE_REGISTER(bool, bool)
FLOW_TYPE_REGISTER(float, float)
FLOW_TYPE_REGISTER(byte, uint8_t)
FLOW_TYPE_REGISTER(string, std::string)
/*FLOW_TYPE_REGISTER(cloud, pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr)
FLOW_TYPE_REGISTER(mat44, Eigen::Matrix4f)
FLOW_TYPE_REGISTER(vec3, Eigen::Vector3f)
FLOW_TYPE_REGISTER(vec4, Eigen::Vector4f)
FLOW_TYPE_REGISTER(quat, Eigen::Quaternionf)
FLOW_TYPE_REGISTER(image, cv::Mat)
*/
