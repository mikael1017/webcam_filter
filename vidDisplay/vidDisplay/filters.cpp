//
//  filters.cpp
//  cs5330
//
//  Created by Jaewoo Cho on 9/27/22.
//

#include "filters.h"
#include <cstdio>
#include <cstring>
#include <math.h>
#include "opencv2/opencv.hpp"
#include <opencv2/core.hpp>

int greyscale( cv::Mat &src, cv::Mat &dst ) {
    int i, j, k;
    
    dst.create( src.size(), src.type() ); // allocates space for the dst image
    
//    a little faster, a little harder to understnad
    
    for (i=0;i<src.rows;i++) {
        const uchar *rptr = src.ptr<uchar>(i); // get the ith row of src image
        uchar *dptr = dst.ptr<uchar>(i); // get the ith row of dst image
        for (j=0;j<src.cols;j++) {
            k = j*3;
            int val = rptr[k+0]; // blue value
            val += rptr[k+1]; // green value
            val += rptr[k+2]; // red value
            val /= 3;
            dptr[k+0] = dptr[k+1] = dptr[k+2] = val;
        }
    }
    
//    a little slower, easier to code/understand
//    for (i = 0; i < src.rows; i++) {
//        for (j = 0; j < src.cols; j++) {
//            int val = src.at<cv::Vec3b>(i, j)[0] + src.at<cv::Vec3b>(i, j)[1] + src.at<cv::Vec3b>(i, j)[2];
//            val /= 3;
//            dst.at<cv::Vec3b>(i, j)[0] = val;
//            dst.at<cv::Vec3b>(i, j)[1] = val;
//            dst.at<cv::Vec3b>(i, j)[2] = val;
//        }
//    }
    return 0;
}



int blur5x5( cv::Mat &src, cv::Mat &dst ) {
    int i, j;
    dst.create( src.size(), src.type() );
    int gaussian[] = {1, 2, 4, 2, 1};
    
    
    for (i = 0; i < src.rows; i++) {
        
        for (j = 2; j < (src.cols - 2);j++) {
//            Adding up all B values
            int bVal = ((src.at<cv::Vec3b>(i, j-2)[0] * gaussian[0]) +
                (src.at<cv::Vec3b>(i, j-1)[0] * gaussian[1]) +
                (src.at<cv::Vec3b>(i, j)[0] * gaussian[2]) +
                (src.at<cv::Vec3b>(i, j+1)[0] * gaussian[3]) +
                (src.at<cv::Vec3b>(i, j+2)[0] * gaussian[4]));
            
//            Adding up all G values
            int gVal = ((src.at<cv::Vec3b>(i, j-2)[1] * gaussian[0]) +
                (src.at<cv::Vec3b>(i, j-1)[1] * gaussian[1]) +
                (src.at<cv::Vec3b>(i, j)[1] * gaussian[2]) +
                (src.at<cv::Vec3b>(i, j+1)[1] * gaussian[3]) +
                (src.at<cv::Vec3b>(i, j+2)[1] * gaussian[4]));
            
            
//            Adding up all R values
            int rVal = ((src.at<cv::Vec3b>(i, j-2)[2] * gaussian[0]) +
                (src.at<cv::Vec3b>(i, j-1)[2] * gaussian[1]) +
                (src.at<cv::Vec3b>(i, j)[2] * gaussian[2]) +
                (src.at<cv::Vec3b>(i, j+1)[2] * gaussian[3]) +
                (src.at<cv::Vec3b>(i, j+2)[2] * gaussian[4]));
            dst.at<cv::Vec3b>(i, j)[0] = (bVal/10);
            dst.at<cv::Vec3b>(i, j)[1] = (gVal/10);
            dst.at<cv::Vec3b>(i, j)[2] = (rVal/10);
        }
    }
    
    for (i = 2; i < (src.rows - 2); i++) {
        
        for (j = 0; j < src.cols;j++) {
//            Adding up all B values
            int bVal = ((src.at<cv::Vec3b>(i-2, j)[0] * gaussian[0]) +
                (src.at<cv::Vec3b>(i-1, j)[0] * gaussian[1]) +
                (src.at<cv::Vec3b>(i, j)[0] * gaussian[2]) +
                (src.at<cv::Vec3b>(i+1, j)[0] * gaussian[3]) +
                (src.at<cv::Vec3b>(i+2, j)[0] * gaussian[4]));
            
//            Adding up all G values
            int gVal = ((src.at<cv::Vec3b>(i-2, j)[1] * gaussian[0]) +
                (src.at<cv::Vec3b>(i-1, j)[1] * gaussian[1]) +
                (src.at<cv::Vec3b>(i, j)[1] * gaussian[2]) +
                (src.at<cv::Vec3b>(i+1, j)[1] * gaussian[3]) +
                (src.at<cv::Vec3b>(i+2, j)[1] * gaussian[4]));
            
            
//            Adding up all R values
            int rVal = ((src.at<cv::Vec3b>(i-2, j)[2] * gaussian[0]) +
                (src.at<cv::Vec3b>(i-1, j)[2] * gaussian[1]) +
                (src.at<cv::Vec3b>(i, j)[2] * gaussian[2]) +
                (src.at<cv::Vec3b>(i+1, j)[2] * gaussian[3]) +
                (src.at<cv::Vec3b>(i+2, j)[2] * gaussian[4]));
            dst.at<cv::Vec3b>(i, j)[0] = (bVal/10);
            dst.at<cv::Vec3b>(i, j)[1] = (gVal/10);
            dst.at<cv::Vec3b>(i, j)[2] = (rVal/10);
        }
    }
    
    
    return 0;
}

//output needs to be type 16S (signed short)
int sobelX3x3( cv::Mat &src, cv::Mat &dst ) {
    int vertical[] = {1, 2, 1};
    int horizontal[] = {-1, 0, 1};
    int i, j;
    dst.create( src.size(), CV_16S );
    for (i = 1; i < (src.rows - 1); i++) {
        
        for (j = 0; j < src.cols; j++) {
//            Adding up all B values
            int bVal = ((src.at<cv::Vec3b>(i-1, j)[0] * vertical[0]) +
                (src.at<cv::Vec3b>(i, j)[0] * vertical[1]) +
                (src.at<cv::Vec3b>(i+1, j)[0] * vertical[2]));
            
//            Adding up all G values
            int gVal = ((src.at<cv::Vec3b>(i-1, j)[1] * vertical[0]) +
                (src.at<cv::Vec3b>(i, j)[1] * vertical[1]) +
                (src.at<cv::Vec3b>(i+1, j)[1] * vertical[2]));
            
            
//            Adding up all R values
            int rVal = ((src.at<cv::Vec3b>(i-1, j)[2] * vertical[0]) +
                (src.at<cv::Vec3b>(i, j)[2] * vertical[1]) +
                (src.at<cv::Vec3b>(i+1, j)[2] * vertical[2]));
            
            dst.at<short>(i, j) = (bVal + gVal + rVal);
        }
    }
    for (i = 0; i < src.rows; i++) {
        
        for (j = 1; j < (src.cols - 1); j++) {
//            Adding up all B values
            int bVal = ((src.at<cv::Vec3b>(i, j-1)[0] * horizontal[0]) +
                (src.at<cv::Vec3b>(i, j)[0] * horizontal[1]) +
                (src.at<cv::Vec3b>(i, j+1)[0] * horizontal[2]));
            
//            Adding up all G values
            int gVal = ((src.at<cv::Vec3b>(i, j-1)[1] * horizontal[0]) +
                (src.at<cv::Vec3b>(i, j)[1] * horizontal[1]) +
                (src.at<cv::Vec3b>(i, j+1)[1] * horizontal[2]));
            
            
//            Adding up all R values
            int rVal = ((src.at<cv::Vec3b>(i, j-1)[2] * horizontal[0]) +
                (src.at<cv::Vec3b>(i, j)[2] * horizontal[1]) +
                (src.at<cv::Vec3b>(i, j+1)[2] * horizontal[2]));
            dst.at<short>(i, j) = (bVal +gVal + rVal);
        }
    }
    
    return 0;
}

//output needs to be type 16S (signed short)
int sobelY3x3( cv::Mat &src, cv::Mat &dst ) {
    int vertical[] = {1, 0, -1};
    int horizontal[] = {1, 2, 1};
    int i, j;
    dst.create( src.size(), CV_16S );
    for (i = 0; i < src.rows; i++) {
        
        for (j = 1; j < (src.cols - 1); j++) {
//            Adding up all B values
            int bVal = ((src.at<cv::Vec3b>(i, j-1)[0] * horizontal[0]) +
                (src.at<cv::Vec3b>(i, j)[0] * horizontal[1]) +
                (src.at<cv::Vec3b>(i, j+1)[0] * horizontal[2]));
            
//            Adding up all G values
            int gVal = ((src.at<cv::Vec3b>(i, j-1)[1] * horizontal[0]) +
                (src.at<cv::Vec3b>(i, j)[1] * horizontal[1]) +
                (src.at<cv::Vec3b>(i, j+1)[1] * horizontal[2]));
            
            
//            Adding up all R values
            int rVal = ((src.at<cv::Vec3b>(i, j-1)[2] * horizontal[0]) +
                (src.at<cv::Vec3b>(i, j)[2] * horizontal[1]) +
                (src.at<cv::Vec3b>(i, j+1)[2] * horizontal[2]));
            dst.at<short>(i, j) = (bVal +gVal + rVal);
        }
    }
    for (i = 1; i < (src.rows - 1); i++) {
        
        for (j = 0; j < src.cols; j++) {
//            Adding up all B values
            int bVal = ((src.at<cv::Vec3b>(i-1, j)[0] * vertical[0]) +
                (src.at<cv::Vec3b>(i, j)[0] * vertical[1]) +
                (src.at<cv::Vec3b>(i+1, j)[0] * vertical[2]));
            
//            Adding up all G values
            int gVal = ((src.at<cv::Vec3b>(i-1, j)[1] * vertical[0]) +
                (src.at<cv::Vec3b>(i, j)[1] * vertical[1]) +
                (src.at<cv::Vec3b>(i+1, j)[1] * vertical[2]));
            
            
//            Adding up all R values
            int rVal = ((src.at<cv::Vec3b>(i-1, j)[2] * vertical[0]) +
                (src.at<cv::Vec3b>(i, j)[2] * vertical[1]) +
                (src.at<cv::Vec3b>(i+1, j)[2] * vertical[2]));
            
            dst.at<short>(i, j) = (bVal + gVal + rVal);
        }
    }
    return 0;
}

int magnitude( cv::Mat &sx, cv::Mat &sy, cv::Mat &dst ) {
    int i, j;
    dst.create( sx.size(), CV_16S );
    for (i = 0; i < sx.rows; i++) {
        for (j = 0; j < sx.cols; j++) {
            int sxVal = sx.at<short>(i, j);
            int syVal = sy.at<short>(i, j);
            int val = sqrt((sxVal * sxVal) + (syVal * syVal));
            dst.at<short>(i, j) = val;
        }
    }
    return 0;
}

int blurQuantize( cv::Mat &src, cv::Mat &dst, int levels = 15) {
    dst.create( src.size(), src.type());
    int i, j;
    cv::Mat blurred;
    blurred.create( src.size(), src.type());
    blur5x5(src, blurred);
    int b = 255 / levels;
    for (i = 0; i < blurred.rows; i++) {
        for (j = 0; j < blurred.cols; j++) {
            int bVal = (blurred.at<cv::Vec3b>(i, j)[0] / b) * b;
            int gVal = (blurred.at<cv::Vec3b>(i, j)[1] / b) * b;
            int rVal = (blurred.at<cv::Vec3b>(i, j)[2] / b) * b;
            dst.at<cv::Vec3b>(i,j)[0] = bVal;
            dst.at<cv::Vec3b>(i,j)[1] = gVal;
            dst.at<cv::Vec3b>(i,j)[2] = rVal;
        }
    }
    return 0;
}

int cartoon( cv::Mat &src, cv::Mat&dst, int levels, int magThreshold ) {
    cv::Mat sobelX;
    cv::Mat sobelY;
    cv::Mat gradientMat;
    cv::Mat filtered;
    sobelX3x3(src, sobelX);
    sobelY3x3(src, sobelY);
    magnitude(sobelX, sobelY, gradientMat);
    blurQuantize(src, filtered, levels);
    dst = filtered.clone();
    int i, j;
    for (i = 0; i < filtered.rows; i++) {
        for (j = 0; j < filtered.cols; j++) {
            if (gradientMat.at<short>(i, j) > magThreshold) {
                dst.at<cv::Vec3b>(i,j)[0] = 0;
                dst.at<cv::Vec3b>(i,j)[1] = 0;
                dst.at<cv::Vec3b>(i,j)[2] = 0;
            }
        }
    }
    return 0;
}

int truncate( int value, int brightness ) {
    int newVal = value + brightness;
    if (newVal < 0) {
        return 0;
    } else if (newVal > 255) {
        return 255;
    }
    return newVal;
}

int changeBrightness( cv::Mat &src, cv::Mat &dst, int brightness) {
    int i, j;
    dst.create(src.size(), src.type());
    for (i = 0; i < src.rows; i++) {
        for (j = 0; j < src.cols; j++) {
            dst.at<cv::Vec3b>(i,j)[0] = truncate(dst.at<cv::Vec3b>(i,j)[0], brightness);
            dst.at<cv::Vec3b>(i,j)[1] = truncate(dst.at<cv::Vec3b>(i,j)[1], brightness);
            dst.at<cv::Vec3b>(i,j)[2] = truncate(dst.at<cv::Vec3b>(i,j)[2], brightness);
        }
    }
    return 0;
}

int sharpen( cv::Mat &src, cv::Mat &dst) {
    dst.create(src.size(), src.type());
    float data[] = {-1, -1, -1, -1, 9, -1, -1, -1, -1};
    cv::Mat kernel;
    kernel = cv::Mat(3, 3, CV_32F, data);
    cv::filter2D(src, dst, -1, kernel);
    
    return 0;
}

int emboss( cv::Mat &src, cv::Mat &dst) {
    dst.create(src.size(), src.type());
    float data[] = {-2, -1, 0, -1, 1, 1, 0, 1, 2};
    cv::Mat kernel;
    kernel = cv::Mat(3, 3, CV_32F, data);
    cv::filter2D(src, dst, -1, kernel);
    
    return 0;
}

int negativeImage( cv::Mat &src, cv::Mat &dst) {
    dst.create(src.size(), src.type());
    dst = 255 - src;
    return 0;
}
