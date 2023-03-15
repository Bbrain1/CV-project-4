//
//  ext1.cpp
//  part_2
//
//  Created by Bennett Brain on 3/15/23
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
#include "ext1.h"

int hideChessboard(cv::Mat filteredFrame, cv::Mat camMat, cv::Mat rvec, cv::Mat tvec, cv::Mat distCoeff, cv::Size patternSize) {
    
    // intialize real-world points and image points vectors
    std::vector<cv::Point2d> imagePoints;
    std::vector<cv::Point3d> imagePoints3D;

    imagePoints3D.push_back(cv::Point3d(-1, -1, 0));
    imagePoints3D.push_back(cv::Point3d(-1, patternSize.height, 0));
    imagePoints3D.push_back(cv::Point3d(patternSize.width, patternSize.height, 0));
    imagePoints3D.push_back(cv::Point3d(patternSize.width, -1, 0));

    cv::projectPoints(imagePoints3D, rvec, tvec, camMat, distCoeff, imagePoints);

    std::vector<cv::Point> cornerPoints;

    cornerPoints.push_back(imagePoints[0]);
    cornerPoints.push_back(imagePoints[1]);
    cornerPoints.push_back(imagePoints[2]);
    cornerPoints.push_back(imagePoints[3]);
    cv::fillPoly(filteredFrame, cornerPoints, 128);

    return 0;
}