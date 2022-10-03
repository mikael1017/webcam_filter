//
//  main.cpp
//  imgDisplay
//
//  Created by Jaewoo Cho on 9/27/22.
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


int main(int argc, const char * argv[]) {
    using namespace cv;
    // insert code here...
    std::cout << "Hello, World!\n";
    cv::Mat image;
    image = cv::imread("/Users/jaewoocho/Desktop/School work/CS 5330/projects/dog.jpeg", 1);
    
    if (!image.data) {
        printf("no image");
        return -1;
    }
    cv::imshow("START PROJECT WITH OPENCV", image);
//    cv::waitKey(0);
    
    while (true) {
        if (waitKey(1) == 113) {
            break;
        }
    }
    return 0;
}
