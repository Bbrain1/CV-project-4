//
//  vidDisplay.cpp
//  Project1
//
//  Created by Bennett Brain on 2/27/23
//  Initially adapted from project 3 code by Bennett and Dhruv

#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/calib3d/calib3d_c.h>
#include "vidDisplay.h"
#include "filter.h"
#include "Task2.h"
#include "Task4.h"
#include <fstream>
#include <iostream>

const std::string csvFileName = "data.csv";

int displayLiveVideoFeed(cv::VideoCapture *capdev){
    cv::namedWindow("Live Video", 1);
    cv::Mat originalFrame;
    cv::Mat filteredFrame;
    // get size of image
   cv::Size refS( (int) capdev->get(cv::CAP_PROP_FRAME_WIDTH ),
                  (int) capdev->get(cv::CAP_PROP_FRAME_HEIGHT));
   printf("Expected size: %d %d\n", refS.width, refS.height);
    
    // turn filter on/off
    bool filterOn;
    // store the char for the filter selected
    char lastFilterSelected;

    cv::Size patternSize = cv::Size(6, 9); //example given board to use is 7x10
    std::vector<cv::Vec3f> point_set;
    genPointSet(point_set, patternSize);
    filterOn = false;
    bool patternFound;
    std::vector<cv::Point2f> corner_set;
    // o --> original
    lastFilterSelected = 'o';

    cv::Mat camMat;
    cv::Mat distCoeff;
    readMats(camMat, distCoeff);


    for(;;) {
        *capdev >> originalFrame; // get a new frame from the camera, treat as a stream
        if(originalFrame.empty()) {
            printf("Frame is empty\n");
            break;
        }
        //if filter is on display filter frame
        if (filterOn && lastFilterSelected != 'o') {

            filteredFrame = originalFrame.clone();
            if(lastFilterSelected == '4'){
                patternFound = cv::findChessboardCorners(originalFrame, patternSize, corner_set);
                std::cout << corner_set.size() << std::endl;
                if (patternFound) {
                    cv::Mat grey;
                    cv::cvtColor(originalFrame, grey, CV_BGR2GRAY);
                    cv::cornerSubPix(grey,corner_set, cv::Size(5, 5), cv::Size(-1, -1),
                        cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
                    cv::drawChessboardCorners(filteredFrame, patternSize, corner_set, patternFound);

                    cv::Mat rvec,tvec;

                    cv::solvePnP(point_set, corner_set, camMat, distCoeff, rvec,tvec);

                    std::cout << "Rotation vector: " << rvec << std::endl;
                    std::cout << "Translation vector: " << tvec << std::endl;


                }

                else {
                    std::cout << "pattern not found" << std::endl;
                    lastFilterSelected = 'o';
                    filterOn = false;
                }
                
            }

            
            
            originalFrame = filteredFrame;
        }
        cv::imshow("Live Video", originalFrame);
        
        // see if there is a waiting keystroke
        char key = cv::waitKey(10);
        if( key == 'q') {
            // to quit
            delete capdev;
            /*csvFile.close();*/
            cv::destroyWindow("Live Video");
            return 0;
        }
        // get original feed
        else if (key == 'o'){
            filterOn = false;
            lastFilterSelected = key;
        }
        else if(key == '4'){
            // thresholding
            filterOn = !filterOn;
            lastFilterSelected = key;
        }
    }
    return 0;
}


// method to get current date and time so we can use it name the screenshot and save it.
const std::string currentDateTime() {
    // Current date/time based on current system
    time_t now = time(0);
    struct tm  tstruct;
    char temp[80];
    // Convert now to tm struct for local timezone
    tstruct = *localtime(&now);
    strftime(temp, sizeof(temp), "%Y-%m-%d %X", &tstruct);
    return temp;
}
