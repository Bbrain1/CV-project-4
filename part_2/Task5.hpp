//
//  Task5.hpp
//  part_2
//
//  Created by Chandler Smith on 3/9/23.
//

#ifndef Task5_hpp
#define Task5_hpp

#include <stdio.h>


int Plot3D(cv::Mat filteredFrame, cv::Mat camMat, cv::Mat rvec, cv::Mat tvec,  cv::Mat distCoeff, std::vector<cv::Point2f> corner_Set);

#endif /* Task5_hpp */
