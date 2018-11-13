//
// Created by dvitali on 12.11.18.
//

#ifndef OBJ_DETECTION_LEGOBRICK_H
#define OBJ_DETECTION_LEGOBRICK_H

#include <vector>
#include <opencv2/opencv.hpp>

class LegoBrick {
public:
    LegoBrick(cv::RotatedRect& rect);
    LegoBrick(cv::RotatedRect& rect, LegoBrick* ref);
    void setBrickReference(LegoBrick* ref);
    int getWidth();
    int getHeight();
    void setSize(int w, int h);
    void draw(cv::Mat& image);
    cv::Point2f getCenter();

private:
    cv::RotatedRect m_rect;
    LegoBrick* m_ref;
    int m_width;
    int m_height;
    cv::Scalar m_color{0.0, 255.0, 0};
    float m_bl = -1.0;
};

#endif //OBJ_DETECTION_LEGOBRICK_H
