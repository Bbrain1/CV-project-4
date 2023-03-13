//
//  Task6.cpp
//  part_2
//
//  Created by Chandler Smith on 3/10/23.
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
#include "Task6.hpp"

int virtualObject(cv::Mat filteredFrame, cv::Mat camMat, cv::Mat rvec, cv::Mat tvec,  cv::Mat distCoeff, std::vector<cv::Point2f> corner_Set){
    
    // get object points initialize inside the function
    std::vector<cv::Point2d> imagePoints;
    std::vector<cv::Point3d> imagePoints3D;
    
    // Origin
     imagePoints3D.push_back(cv::Point3d(0,0,-10.0));
     imagePoints3D.push_back(cv::Point3d(0,10.0,0));
     imagePoints3D.push_back(cv::Point3d(10.0,0,0));
    
    //Point Prism top in top right square
    imagePoints3D.push_back(cv::Point3d(0.5,0.5,-2.0));
    
    // Inverse Prism point for opposite corner
    imagePoints3D.push_back(cv::Point3d(0.5,1,2.0));

       cv::projectPoints(imagePoints3D, rvec, tvec, camMat, distCoeff, imagePoints);
    
    // Shape - Prism 1 over square 1
    // Prism Bottom
    cv::line(filteredFrame, corner_Set[0], (corner_Set[1]), cv::Scalar(170 , 40, 120), 2);
    cv::line(filteredFrame, corner_Set[1], (corner_Set[7]), cv::Scalar(170 , 40, 120), 2);
    cv::line(filteredFrame, corner_Set[7], (corner_Set[6]), cv::Scalar(170 , 40, 120), 2);
    cv::line(filteredFrame, corner_Set[6], (corner_Set[0]), cv::Scalar(170 , 40, 120), 2);
    
    // Prism Top
    cv::line(filteredFrame, (corner_Set[0]), (imagePoints[3]), cv::Scalar(170 , 40, 120), 2);
    cv::line(filteredFrame, (corner_Set[1]), (imagePoints[3]), cv::Scalar(170 , 40, 120), 2);
    cv::line(filteredFrame, (corner_Set[7]), (imagePoints[3]), cv::Scalar(170 , 40, 120), 2);
    cv::line(filteredFrame, (corner_Set[6]), (imagePoints[3]), cv::Scalar(170 , 40, 120), 2);
    
    // Shape - Prism 2 over square 2
    // Prism Bottom
    cv::line(filteredFrame, corner_Set[6], (corner_Set[7]), cv::Scalar(149 , 219, 19), 2);
    cv::line(filteredFrame, corner_Set[7], (corner_Set[13]), cv::Scalar(149 , 219, 19), 2);
    cv::line(filteredFrame, corner_Set[13], (corner_Set[12]), cv::Scalar(149 , 219, 19), 2);
    cv::line(filteredFrame, corner_Set[12], (corner_Set[6]), cv::Scalar(149 , 219, 19), 2);
    
    // Prism Top
    cv::line(filteredFrame, (corner_Set[6]), (imagePoints[4]), cv::Scalar(149 , 219, 19), 2);
    cv::line(filteredFrame, (corner_Set[7]), (imagePoints[4]), cv::Scalar(149 , 219, 19), 2);
    cv::line(filteredFrame, (corner_Set[13]), (imagePoints[4]), cv::Scalar(149 , 219, 19), 2);
    cv::line(filteredFrame, (corner_Set[12]), (imagePoints[4]), cv::Scalar(149 , 219, 19), 2);
    

    return 0;
   }
  
