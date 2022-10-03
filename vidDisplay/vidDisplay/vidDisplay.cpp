//
//  vidDisplay.cpp
//  cs5330
//
//  Created by Jaewoo Cho on 9/22/22.
//

#include <string>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include "filters.h"

using namespace std;

int main(int argc, char *argv[]) {
//    (*capdev).isOpened()  capdev->isOpened()
    cv::VideoCapture *capdev;

    // open the video device
    capdev = new cv::VideoCapture(0);
    if( !capdev->isOpened() ) {
            printf("Unable to open video device\n");
            return(-1);
    }

    // get some properties of the image
    cv::Size refS( (int) capdev->get(cv::CAP_PROP_FRAME_WIDTH ),
                   (int) capdev->get(cv::CAP_PROP_FRAME_HEIGHT));
    printf("Expected size: %d %d\n", refS.width, refS.height);

    cv::namedWindow("Video", 1); // identifies a window
    cv::Mat frame;
    cv::Mat filtered;
    cv::Mat filtered2;
    cv::Mat filtered3;
    cv::Mat filtered_8U;
    cv::Mat filtered_8U3C;
    cv::Mat display;
    cv::Mat captured;
    int brightness = 0;
    int img_counter = 0;
    char lastClicked = ' ';


    for(int f=0;;f++) {
        *capdev >> frame; // get a new frame from the camera, treat as a stream
        if( frame.empty() ) {
          printf("frame is empty\n");
          break;
        }
        
        switch(lastClicked) {
            case ' ':
                filtered_8U3C = frame;
                brightness = 0;
                break;
            case 'p':
                sharpen(frame, filtered_8U3C);
                break;
            case 'e':
                emboss(frame, filtered_8U3C);
                break;
            case 'n':
                negativeImage( frame, filtered_8U3C);
                break;
            case 'g':
                cv::cvtColor( frame, filtered_8U3C, cv::COLOR_BGR2GRAY );
                break;
            case 'h':
                greyscale( frame, filtered_8U3C);
                break;
            case 'b':
                blur5x5( frame, filtered_8U3C);
                break;
            case 'x':
                sobelX3x3( frame, filtered);
                filtered += 128;
                filtered /= 2;
                filtered.convertTo(filtered2, CV_8U);
                cv::cvtColor(filtered2, filtered_8U3C, cv::COLOR_GRAY2BGR);
                break;
            case 'y':
                sobelY3x3( frame, filtered );
                filtered += 128;
                filtered /= 2;
                filtered.convertTo(filtered2, CV_8U);
                cv::cvtColor(filtered2, filtered_8U3C, cv::COLOR_GRAY2BGR);
                break;
            case 'm':
                sobelX3x3(frame, filtered );
                sobelY3x3(frame, filtered2);
                magnitude( filtered, filtered2, filtered3);
                filtered3 += 128;
                filtered3 /= 2;
                filtered3.convertTo(filtered_8U, CV_8U);
                cv::cvtColor(filtered_8U, filtered_8U3C, cv::COLOR_GRAY2BGR);
                break;
            case 'l':
                blurQuantize(frame, filtered_8U3C, 15);
                break;
            
            case 'c':
                cartoon(frame, filtered_8U3C, 15, 15);
                break;
                
            case 'k':
//                increase the brightness
                brightness += 10;
                lastClicked = '\0';
                break;
            case 'j':
//                decrease the brightness
                brightness -= 10;
                lastClicked = '\0';
                break;
            
        }
        changeBrightness( filtered_8U3C, filtered_8U3C, brightness);
        display = filtered_8U3C;
        cv::imshow("Video", display);
        // see if there is a waiting keystroke
        char key = cv::waitKey(10);
        if( key == 'q') {
            break;
        } else if ( key == 's' ) {
//                capture the video and save the image
            std::string name = "/Users/jaewoocho/Desktop/hw1_" + std::to_string(img_counter) + ".png";
            cv::imwrite(name, filtered_8U3C);
            img_counter += 1;
            key = '\0';
        }
        else if ( key == 'g' || key == 'h' || key == 'b' || key == 'c' || key == ' ' || key == 'x' || key == 'y' || key =='m' || key == 'l' || key == 'k' || key == 'j' || key == 'p' || key == 'e' || key == 'n') {
            lastClicked = key;
        }
    } // end of loop
    
    printf("Terminating\n");
    delete capdev;
    return(0);
}
