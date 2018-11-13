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

    if(m_ref->m_bl < 0){
        float r_w = m_ref->m_rect.size.width;
        float r_h = m_ref->m_rect.size.height;

        std::cout << "r_w=" << r_w << std::endl;
        std::cout << "r_h=" << r_h << std::endl;

        float longEdge = r_w > r_h ? r_w : r_h;
        float brickLength = longEdge/m_ref->m_width; // Minimum brick is 2x1
        m_ref->m_bl = brickLength;
    }

    std::cout << "m_ref->m_bl = " << m_ref->m_bl << std::endl;

    this->m_bl = m_ref->m_bl;

    std::cout << this->m_bl << std::endl;

    this->m_width = static_cast<int>(round(m_rect.size.width * 1.0 / m_bl));
    this->m_height = static_cast<int>(round(m_rect.size.height * 1.0 / m_bl));
}

int LegoBrick::getWidth() {
    return this->m_width;
}

int LegoBrick::getHeight() {
    return this->m_height;
}

void LegoBrick::draw(cv::Mat &image) {
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


    std::stringstream text{};
    text << this->getWidth() << "x" << this->getHeight();

    cv::String cvStr{text.str()};
    int* baseline = new int{};
    auto size = cv::getTextSize(text.str(), cv::FONT_HERSHEY_PLAIN, 2.0, 1, baseline);
    cv::Point textCenter = cv::Point{static_cast<int>(getCenter().x - size.width / 2),
                                     static_cast<int>(getCenter().y + size.height / 2)};
    cv::putText(image, cvStr, textCenter, cv::FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(0, 0, 255.0));
}

cv::Point2f LegoBrick::getCenter() {
    return this->m_rect.center;
}

void LegoBrick::setSize(int w, int h) {
    m_width = w;
    m_height = h;
}
