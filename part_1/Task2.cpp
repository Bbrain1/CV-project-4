//
//  Task2.cpp
//  Project4
//
//  Created by Bennett Brain.

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "Task2.h"

// Generate the point set

int genPointSet(std::vector<cv::Vec3f> &point_set, cv::Size patternSize) {
	for (int j = 0; j < patternSize.height; j++) {
		for (int i = 0; i < patternSize.width; i++) {
			cv::Vec3f thisPoint;
			thisPoint[0] = i;
			thisPoint[1] = -j;
			thisPoint[2] = 0;
			point_set.push_back(thisPoint);
		}
	}

	return 0;
}