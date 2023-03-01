//
//  Task4.cpp
//  Project4
//
//  Created by Bennett Brain.

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "Task4.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include <filesystem>

// Reads the camera and distortion matrices
int readMats(cv::Mat &camMat, cv::Mat &distMat) {

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

	cv::FileStorage fs(fileName, cv::FileStorage::READ);

	fs["CameraMatrix"] >> camMat;
	fs["DistortionCoeffs"] >> distMat;

	return 0;
}

