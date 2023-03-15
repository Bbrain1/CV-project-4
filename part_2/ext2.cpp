//
//  ext2.cpp
//  part_2
//
//  Created by Chandler Smith on 3/15/23.
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
#include "ext2.hpp"


int complexObject(cv::Mat filteredFrame, cv::Mat camMat, cv::Mat rvec, cv::Mat tvec,  cv::Mat distCoeff, std::vector<cv::Point2f> corner_Set, float xstart, float ystart){
    
    // get object points initialize inside the function
    std::vector<cv::Point2d> imagePoints;
    std::vector<cv::Point3d> imagePoints3D;
    
    // Note that xstart and ystart are intialized when c is pressed.
    
    // Bottom Hexagon Points
     imagePoints3D.push_back(cv::Point3d(xstart,ystart + 0.3,0));
     imagePoints3D.push_back(cv::Point3d(xstart,ystart + 0.71,0));
     imagePoints3D.push_back(cv::Point3d(xstart + 0.3, ystart + 1.0, 0));
     imagePoints3D.push_back(cv::Point3d(xstart + 0.71, ystart + 1.0, 0));
     imagePoints3D.push_back(cv::Point3d(xstart +1.0,ystart + 0.71,0));
     imagePoints3D.push_back(cv::Point3d(xstart +1.0,ystart + 0.3,0));
     imagePoints3D.push_back(cv::Point3d(xstart +0.7,ystart + 0.0,0));
     imagePoints3D.push_back(cv::Point3d(xstart +0.3,ystart + 0,0));
    // Top Hexagon Points
    float height = -0.3;
    imagePoints3D.push_back(cv::Point3d(xstart + 0,ystart + 0.3,height));
    imagePoints3D.push_back(cv::Point3d(xstart + 0,ystart + 0.71,height));
    imagePoints3D.push_back(cv::Point3d(xstart + 0.3,ystart + 1.0,height));
    imagePoints3D.push_back(cv::Point3d(xstart + 0.71,ystart + 1.0,height));
    imagePoints3D.push_back(cv::Point3d(xstart + 1.0,ystart + 0.71,height));
    imagePoints3D.push_back(cv::Point3d(xstart + 1.0,ystart + 0.3,height));
    imagePoints3D.push_back(cv::Point3d(xstart + 0.7,ystart + 0.0,height));
    imagePoints3D.push_back(cv::Point3d(xstart + 0.3,ystart + 0,height));
    
    // Convert to 2D
    cv::projectPoints(imagePoints3D, rvec, tvec, camMat, distCoeff, imagePoints);
    
    std::vector<cv::Point> hexPoints;
    // Hexagon bottom lines
    for(int i = 0; i<7; i++){
        cv::line(filteredFrame, imagePoints[i], imagePoints[i+1], cv::Scalar(236 , 219, 137), 2);
    }
    cv::line(filteredFrame, imagePoints[7], imagePoints[0], cv::Scalar(236 , 219, 137), 2);
    
    // Hexagon Top lines
    for(int i = 8; i<15; i++){
        cv::line(filteredFrame, imagePoints[i], imagePoints[i+1], cv::Scalar(236 , 219, 137), 2);
    }
    cv::line(filteredFrame, imagePoints[8], imagePoints[15], cv::Scalar(236 , 219, 137), 2);
    // Hexagon connection points
    for(int i = 0; i<8; i++){
        cv::line(filteredFrame, imagePoints[i], imagePoints[i+8], cv::Scalar(236 , 219, 137), 2);
    }
    return 0;
   }
    
  

