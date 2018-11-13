#include <iostream>
#include <opencv2/opencv.hpp>
#include "LegoBrick.h"

using namespace std;

int main() {
    cv::Mat image = cv::imread("/home/dvitali/Documents/supsi/I3B/5-sem/multimedia-processing/files/img-serie-5/lego.png");

    if(!image.data){
        cout << "Unable to open image" << endl;
        return 1;
    }

    cv::Mat greyMat, outputMat, erodedMat;
    cv::imshow("Original Image", image);

    cv::cvtColor(image, greyMat, CV_BGR2GRAY);
    cv::adaptiveThreshold(greyMat, outputMat, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C,
            cv::THRESH_BINARY, 11, 2);

    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(40, 40));

    cv::morphologyEx(outputMat, erodedMat, cv::MORPH_OPEN, kernel);
    vector<vector<cv::Point>> contours{};
    vector<cv::RotatedRect> rectangles{};
    cv::findContours(erodedMat, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

    printf("Found %d contours\n", static_cast<int>(contours.size()));

    int imageArea = image.rows * image.cols;
    double smallestArea = imageArea;
    auto* smallestRectangle = new cv::RotatedRect{};

    for(auto &i : contours){
        cout << "Contour: " << endl;
        double perimeter = cv::arcLength(i, true);

        vector<cv::Point> rectangle{};
        cv::approxPolyDP(i, rectangle, perimeter * 0.01, true);

        cv::RotatedRect rect = cv::minAreaRect(rectangle);

        double area = rect.size.area();

        if(area >= 0.8 * imageArea){
            continue;
        }

        if(area <= 0.001 * imageArea){
            continue;
        }

        if(area < smallestArea){
            smallestArea = area;
            *smallestRectangle = rect;
        }

        rectangles.push_back(rect);
    }

    auto* referenceBrick = new LegoBrick{*smallestRectangle};
    referenceBrick->setSize(2, 1);
    vector<LegoBrick*> bricks{};

    for(auto& rect : rectangles){
        if(rect.center == smallestRectangle->center){
            continue;
        }

        cout << "Rect=(Center=" << rect.center << ", Size=" << rect.size << ")" << endl;

        auto* brick = new LegoBrick{rect};
        brick->setBrickReference(referenceBrick);
        bricks.push_back(brick);
    }

    for(LegoBrick* brick : bricks){
        brick->draw(image);
    }

    referenceBrick->draw(image);



    // Draw Smallest Rectangle
    /*vector<vector<cv::Point>> smallRectangles;
    smallRectangles.push_back(smallestRectangle);
    cv::drawContours(image, smallRectangles, -1, color, -1);*/

    cv::imshow("Final Image", image);
    cv::waitKey(40 * 1000);
    return 0;
}