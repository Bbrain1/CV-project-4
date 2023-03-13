//
//  Task5.cpp
//  part_2
//
//  Created by Chandler Smith on 3/9/23.
//
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <cstring>
#include <cstdlib>
#include <opencv2/calib3d.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include <filesystem>
#include "Task5.hpp"

// 3D Axis
int Plot3D(cv::Mat filteredFrame, cv::Mat camMat, cv::Mat rvec, cv::Mat tvec,  cv::Mat distCoeff, std::vector<cv::Point2f> corner_Set){
    
    // get object points initialize inside the function
    std::vector<cv::Point2d> imagePoints;
    std::vector<cv::Point3d> imagePoints3D;
    
    //std::cout << imagePoints << std::endl;
    
     imagePoints3D.push_back(cv::Point3d(0,0,-10.0));
     imagePoints3D.push_back(cv::Point3d(0,10.0,0));
     imagePoints3D.push_back(cv::Point3d(10.0,0,0));
     
       cv::projectPoints(imagePoints3D, rvec, tvec, camMat, distCoeff, imagePoints);
      //  std::cout << imagePoints;
    
    // Axis
    cv::line(filteredFrame, corner_Set[0], imagePoints[0], cv::Scalar(0, 0, 255), 2);
    cv::line(filteredFrame, corner_Set[0], imagePoints[1], cv::Scalar(0, 255, 0), 2);
    cv::line(filteredFrame, corner_Set[0], imagePoints[2], cv::Scalar(255, 0, 0), 2);

    return 0;
   }
  


