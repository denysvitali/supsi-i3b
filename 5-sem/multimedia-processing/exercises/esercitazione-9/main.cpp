#include <iostream>
#include <opencv2/opencv.hpp>
#include "Tracker.h"

using namespace std;
using namespace cv;

#define REALTIME_VIDEO true
#define SHOW_ROI false

int main() {
	VideoCapture cap{"/home/dvitali/Documents/supsi/I3B/5-sem/multimedia-processing/files/videoauto.mp4"};

	if(!cap.isOpened()){
		return -1;
	}

	namedWindow("floatme: video", 1);
	namedWindow("floatme: tr1", 1);
	namedWindow("floatme: tr2", 1);
	//namedWindow("floatme: mask", 1);

	if(SHOW_ROI) {
		namedWindow("floatme: roi", 1);
	}

	int fps = static_cast<int>(cap.get(CAP_PROP_FPS));

	int w = cap.get(CAP_PROP_FRAME_WIDTH);
	int h = cap.get(CAP_PROP_FRAME_HEIGHT);

	cout << "Size: " << w << " x " << h << endl;

	if(!REALTIME_VIDEO) {
		char tb_name[50];
		sprintf(tb_name, "FPS: %d", fps);
		createTrackbar(tb_name, "video", &fps, 1000, nullptr);
	}

	cout << "FPS: " << fps << endl;

	Mat frame, gray, fgMaskMOG2, morph, output;
	Ptr<BackgroundSubtractor> pMOG2;
	pMOG2 = createBackgroundSubtractorMOG2();

	Rect hotzone_left = Rect{80, 180, 120, 60};
	Rect hotzone_right = Rect{w - 250, 130, 60, 60};

	Tracker tl = Tracker{"floatme: tr1", hotzone_left, Direction::RIGHT};
	Tracker tr = Tracker{"floatme: tr2", hotzone_right, Direction::LEFT};

	int frameNumber = 0;

	for(;;){
		frameNumber++;
		cap >> frame;

		if (frame.rows == 0 && frame.cols == 0){
			cout << "Last Frame!" << endl;
			break;
		}

		cvtColor(frame, gray, COLOR_BGR2GRAY);
		pMOG2->apply(gray, fgMaskMOG2);

		Mat element = getStructuringElement(MORPH_CROSS, Size(3,3), Point(1,1));
		Mat element2 = getStructuringElement(MORPH_RECT, Size(10,10), Point(1,1));

		erode(fgMaskMOG2, morph, element, Point(-1, -1), 3);
		adaptiveThreshold(morph, morph, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 11, 1);
		dilate(morph, morph, element2, Point(-1, -1), 3);
		dilate(morph, morph, element2, Point(-1, -1), 3);

		tl.track(frame, morph, frameNumber);
		tr.track(frame, morph, frameNumber);

		if(REALTIME_VIDEO){
			if (waitKey(static_cast<int>(1.0 / fps * 1000)) == (int) 'a') break;
		} else {
			if (waitKey(1.0/fps * 1000) >= 0) break;
		}
	}

	std::cout << "Left: " << tr.carsCounter() << " cars" << std::endl;
	std::cout << "Right: " << tl.carsCounter() << " cars" << std::endl;
	std::cout << "Total: " << tr.carsCounter() + tl.carsCounter() << " cars" << std::endl;

	return 0;
}