//
//  main.cpp
//  Project3
//
//  Created by Bennett Brain on 2/27/23
//  Based on code from project 3 by Bennett and Dhruv
//

#include <opencv2/opencv.hpp>
#include "vidDisplay.h"
#include <stdio.h>
using namespace cv;

int main(int argc, char* argv[]) {

       cv::VideoCapture *capdev;
       capdev = new cv::VideoCapture(0);
       if( !capdev->isOpened() ) {
               printf("Unable to open video device\n");
               return(-1);
       }
       // liveEnded = 1  ----> not ended
       // liveEnded = 0  ----> ended
       int liveEnded = 1;
       liveEnded = displayLiveVideoFeed(capdev);
       // for loop to keep the program running
       for(;;){
           // check if live ended
           if(liveEnded == 0){
               std::printf("Quitting\n");
               break;
           }
           // wait for a key press
           char key;
           key = (char) cv::waitKey(0);
           // handle quit condition
           if(key == 'q'){
               std::printf("Quitting\n");
               break;
           }
           // handle wrong key stroke
           else{
               std::printf("Wrong Key Entered: %c\n",key);
           }
       }
       cv::destroyAllWindows();  
       return 0;
}
