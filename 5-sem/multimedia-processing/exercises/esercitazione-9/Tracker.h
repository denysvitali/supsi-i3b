#include <utility>

#pragma once
#include <opencv2/opencv.hpp>

using namespace cv;

enum Direction {
	LEFT,
	RIGHT
};

class Tracker {
public:
	Tracker(std::string name, Rect trackerInitialPos, Direction dir);
	void track(Mat frame, Mat morph, int frameNumber);
	int carsCounter();

private:
	std::string m_name;
	Rect m_trackerpos;
	Rect m_originaltrackerpos;
	int first_seen = -1;
	int frame_length = 0;
	int car_count = 0;
	RotatedRect lastTrackerPos;
	Direction direction;
	Mat m_carPic;
};