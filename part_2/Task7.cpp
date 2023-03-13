//
//  Task7.cpp
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
#include <xfeatures2d.hpp>
#include <fstream>
#include <string>
#include <dirent.h>
#include <filesystem>
#include "Task7.hpp"

int surf(cv::Mat filteredFrame){
    // cite - code study blog for inspiration
    //std::cout << "SURF PROGRAM";
    cv::Ptr<cv::xfeatures2d::SURF> surf;
    // Hessian threshold = 400
    surf = cv::xfeatures2d::SURF::create(1000);
    //surf-> std::setHassianThreshold(5000);
    std::vector<cv::KeyPoint> kp;
    cv::Mat des, vidKP;

    surf->detect(filteredFrame, kp);
    
    cv::Mat img_keypoints;
    cv::drawKeypoints(filteredFrame, kp, filteredFrame);
    
    return 0;
}


