//
//  Task3.cpp
//  Project4
//
//  Created by Bennett Brain.

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "Task3.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include <filesystem>

// generate the initial camera matrix

int genCamMat(cv::Mat& camMat, cv::Size frameSize) {

	cv::Size cmSize = cv::Size(3, 3);
	camMat = cv::Mat::zeros(cmSize, CV_64FC1);

	camMat.at<double>(0, 0) = 1;
	camMat.at<double>(2, 0) = frameSize.width / static_cast<double>(2);
	camMat.at<double>(1, 1) = 1;
	camMat.at<double>(2, 1) = frameSize.height / static_cast<double>(2);
	camMat.at<double>(2, 2) = 1;
	return 0;
}

int printMats(cv::Mat camMat, cv::Mat distMat){

	std::string name = "";
	printf("Enter your name: ");
	std::cin >> name;
	while (name == "")
	{
		printf("Invalid name. Please try again.\n");
		printf("Enter your name: ");
		std::cin >> name;
	}

	std::string fileName = name + "_calibration.json";

	cv::FileStorage fs(fileName, cv::FileStorage::WRITE);
	fs << "CameraMatrix" << camMat;
	fs << "DistortionCoeffs" << distMat;

	

	return 0;
}