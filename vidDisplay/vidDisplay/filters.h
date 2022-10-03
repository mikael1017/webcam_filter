//
//  filters.h
//  cs5330
//
//  Created by Jaewoo Cho on 9/27/22.
//

#ifndef FILTERS_H
#define FILTERS_H
#include "opencv2/opencv.hpp"
#include <opencv2/core.hpp>

int greyscale( cv::Mat &src, cv::Mat &dst );
int blur5x5( cv::Mat &src, cv::Mat &dst );
int sobelX3x3( cv::Mat &src, cv::Mat &dst );
int sobelY3x3( cv::Mat &src, cv::Mat &dst );
int magnitude( cv::Mat &sx, cv::Mat &sy, cv::Mat &dst );
int blurQuantize( cv::Mat &src, cv::Mat &dst, int levels );
int cartoon( cv::Mat &src, cv::Mat &dst, int levels, int magThreshold );
int changeBrightness( cv::Mat &src, cv::Mat &dst, int brightness);
int glow ( cv::Mat &src, cv::Mat &dst, int radius, double strength);
int sharpen (cv::Mat &src, cv::Mat &dst);
int emboss (cv::Mat &src, cv::Mat &dst);
int negativeImage( cv::Mat &src, cv::Mat &dst);

/* OpenCV nomenclature for types
     cv::CV_8U      -> 1 byte per pixel image (greyscale)
     cv::CV_8U3C    -> 1 byte per color channel, 3 color channels (regular RGB image)
     cv::CV_16S     -> 2 bytes (signed) per pixel image (useful for doing math)
     cv::CV_16S3C   -> 2 bytes (signed) per color channel, 3 color channels (useful for doing math, holding negative values)
    know what data type your cv::Mat is holding
    some openCV functions return specific types, some return the input type (read the documentation)
 */

#endif /* filters_h */
