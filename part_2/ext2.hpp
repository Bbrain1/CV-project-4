//
//  ext2.hpp
//  part_2
//
//  Created by Chandler Smith on 3/15/23.
//

#ifndef ext2_hpp
#define ext2_hpp

#include <stdio.h>

int complexObject(cv::Mat filteredFrame, cv::Mat camMat, cv::Mat rvec, cv::Mat tvec,  cv::Mat distCoeff, std::vector<cv::Point2f> corner_Set, float xstart, float ystart);

#endif /* ext2_hpp */

