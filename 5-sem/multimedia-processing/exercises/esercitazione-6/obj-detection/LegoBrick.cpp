//
// Created by dvitali on 12.11.18.
//

#include "LegoBrick.h"

LegoBrick::LegoBrick(cv::RotatedRect& rect) : LegoBrick{rect, nullptr} {}

LegoBrick::LegoBrick(cv::RotatedRect& rect, LegoBrick *ref) {
    m_rect = rect;
    m_ref = ref;
}

void LegoBrick::setBrickReference(LegoBrick* ref) {
    this->m_ref = ref;
}

int LegoBrick::getWidth() {
    return this->m_width;
}

int LegoBrick::getHeight() {
    return this->m_height;
}

void LegoBrick::draw(cv::Mat &image) {
    std::cout << "Drawing..." << std::endl;

    auto* pts = new cv::Point2f[4];
    m_rect.points(pts);

    const cv::Point points[4] = {pts[0], pts[1], pts[2], pts[3]};
    const cv::Point* points_arr[1] = {points};

    int* npoints = new int{4};

    cv::Mat1b mask(image.rows, image.cols, uchar(0));
    cv::fillPoly(mask, points_arr, npoints, 1, cv::Scalar(255));

    cv::Scalar mean = cv::mean(image, mask);

    for (int i = 0; i < 4; i++) {
        cv::line(image, pts[i], pts[(i + 1) % 4], mean, 2);
    }

    cv::fillPoly(image, points_arr, npoints, 1, mean);
}