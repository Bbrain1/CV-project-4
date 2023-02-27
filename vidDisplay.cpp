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
#include "vidDisplay.h"
#include "filter.h"
#include <fstream>
#include <iostream>

const std::string csvFileName = "data.csv";

int displayLiveVideoFeed(cv::VideoCapture *capdev){
    cv::namedWindow("Live Video", 1);
    cv::Mat originalFrame;
    cv::Mat filteredFrame;
    // get some size of image
   cv::Size refS( (int) capdev->get(cv::CAP_PROP_FRAME_WIDTH ),
                  (int) capdev->get(cv::CAP_PROP_FRAME_HEIGHT));
   printf("Expected size: %d %d\n", refS.width, refS.height);

   //// open a csv file for writing
   // std::ofstream csvFile;
   // csvFile.open(csvFileName, std::ios::out | std::ios::app);
   // if (!csvFile.is_open()) {
   //     printf("Error opening csv file.\n");
   //     return -1;
   // }
   // 
   // // open a csv file for reading
   // std::fstream readCsvFile;
   // readCsvFile.open(csvFileName, std::ios::in);
   // if(!readCsvFile.is_open()){
   //     printf("Error opening csv file.\n");
   //     return -1;
   // }
    
    //// creating a caching DB
    //std::vector<std::vector<std::string>> database;
    //std::string line;
    //while(getline(readCsvFile,line)){
    //    std::vector<std::string> row;
    //    std::stringstream ss(line);
    //    std::string cell;
    //    while(getline(ss,cell,',')){
    //        row.push_back(cell);
    //    }
    //    database.push_back(row);
    //}
    
    // turn filter on/off
    bool filterOn;
    // store the char for the filter selected
    char lastFilterSelected;
    filterOn = false;
    // o --> original
    lastFilterSelected = 'o';
    for(;;) {
        *capdev >> originalFrame; // get a new frame from the camera, treat as a stream
        if(originalFrame.empty()) {
            printf("Frame is empty\n");
            break;
        }
        //if filter is on display filter frame
        if (filterOn && lastFilterSelected != 'o') {
            if(lastFilterSelected == '1'){
                std::vector<cv::Point2f> corner_set;

                cv::Size patternSize = cv::Size(6, 9); //example given board to use is 7x10

                bool patternFound = cv::findChessboardCorners(originalFrame, patternSize, corner_set);

                std::cout << corner_set.size() << std::endl;

                filteredFrame = originalFrame.clone();

                cv::drawChessboardCorners(filteredFrame, patternSize, corner_set, patternFound);
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
        else if (key == 's'){
            // to save a frame
            std::string filename;
            filename = currentDateTime();
            filename = filename.append(".jpeg");
            cv::imwrite(filename, originalFrame);
            printf("Screenshot saved!\n");
        }
        // get original feed in color
        else if (key == 'o'){
            filterOn = false;
            lastFilterSelected = key;
        }
        else if(key == '1'){
            // thresholding
            filterOn = !filterOn;
            lastFilterSelected = key;
        }
        else if (key == '2') {
            // thresholding + cleaning up
            filterOn = !filterOn;
            lastFilterSelected = key;
        }
        else if (key == '3') {
            // thresholding + cleaning up + CCA
            filterOn = !filterOn;
            lastFilterSelected = key;
        }
        else if (key == '4') {
                    // thresholding + cleaning up + CCA + feature generation
                    filterOn = !filterOn;
                    lastFilterSelected = key;
                }
        else if (key == '5'){
            // saving to database and csv
            filterOn = !filterOn;
            lastFilterSelected = key;
        }
        else if (key == '6'){
            // classifying the image based on nearest neighbour
            filterOn = !filterOn;
            lastFilterSelected = key;
        }
        else if (key == '7'){
            // knn-classifying the image
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
