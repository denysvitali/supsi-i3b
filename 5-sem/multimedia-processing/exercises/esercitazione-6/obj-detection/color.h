//
// Created by dvitali on 13.11.18.
//

#ifndef OBJ_DETECTION_COLOR_H
#define OBJ_DETECTION_COLOR_H

#include <opencv2/opencv.hpp>

class Color {
public:
    Color(cv::Scalar& color);
    Color(int r, int g, int b);
    Color(int r, int g, int b, const char *label);
    std::string label();
    int R();
    int G();
    int B();
    static std::vector<Color> colors();

private:
    int m_r, m_g, m_b = 0;
    std::string m_label = "";
    void recognize_color();
};



#endif //OBJ_DETECTION_COLOR_H
