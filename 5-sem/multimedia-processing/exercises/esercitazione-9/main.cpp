#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define REALTIME_VIDEO false

void on_trackbar( int, void* )
{

}

int main() {
	VideoCapture cap{"/home/dvitali/Documents/supsi/I3B/5-sem/multimedia-processing/files/videoauto.mp4"};

	if(!cap.isOpened()){
		return -1;
	}

	namedWindow("video", 1);
	namedWindow("mask", 1);

	int fps = static_cast<int>(cap.get(CAP_PROP_FPS));

	if(!REALTIME_VIDEO) {
		char tb_name[50];
		sprintf(tb_name, "FPS: %d", fps);
		createTrackbar(tb_name, "video", &fps, 1000, on_trackbar);
	}

	cout << "FPS: " << fps << endl;

	Mat frame;
	Mat gray;
	Mat fgMaskMOG2;
	Ptr<BackgroundSubtractor> pMOG2;
	pMOG2 = createBackgroundSubtractorMOG2();

	for(;;){
		cap >> frame;
		if (frame.rows == 0 && frame.cols == 0){
			cout << "Last Frame!" << endl;
			break;
		}

		pMOG2->apply(frame, fgMaskMOG2, -3);
		Mat output, mask, mask2;

		cv::morphologyEx(fgMaskMOG2, mask, MORPH_ERODE, getStructuringElement(MORPH_RECT, Size(8,8)), Point(-1, -1), 1,
				BORDER_CONSTANT, 1);

		//cvtColor(fgMaskMOG2, gray, cv::COLOR_BGR2GRAY);

		//cv::blur(mask, mask2, Size(20, 20));
		cv::adaptiveThreshold(mask, mask2, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 31, -3);
		/*cv::morphologyEx(mask2, mask, MORPH_OPEN,
						 getStructuringElement(MORPH_ELLIPSE, Size(5,5)),
						 Point(-1, -1), 1, BORDER_CONSTANT, 1);*/


		cv::morphologyEx(mask2, mask, MORPH_DILATE,
						 getStructuringElement(MORPH_RECT, Size(15,15)),
						 Point(-1, -1), 1, BORDER_CONSTANT, 1);

		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;

		cv::blur(mask, mask2, Size(5, 5));
		cv::adaptiveThreshold(mask2, mask2, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 81, -3);
		cv::dilate(mask2, mask2, getStructuringElement(MORPH_RECT, Size(40, 40)));

		mask = mask2;

		cv::findContours(mask2,contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

		vector<Point> carPoints = vector<Point>{};

		for(auto& contour : contours){
			cout << contour << endl;
			vector<Point> approxCurve;
			double perimeter = cv::arcLength(contour, true);
			approxPolyDP(contour, approxCurve, perimeter * 0.01, true);

			if(contour.size() == 0){
				continue;
			}

			RotatedRect rr = cv::minAreaRect(approxCurve);
			Rect r = rr.boundingRect();


			if(r.area() >= frame.cols * frame.rows * 0.9){
				continue;
			}

			carPoints.emplace_back(r.tl());
			carPoints.emplace_back(Point(r.tl().x + r.width, r.tl().y));
			carPoints.emplace_back(Point(r.br().x - r.width, r.br().y));
			carPoints.emplace_back(r.br());
		}

		if(carPoints.size() != 0){
			RotatedRect rr = minAreaRect(carPoints);
			Rect rect = rr.boundingRect();

			const Point p_1 = rect.tl();
			const Point p_2 = Point(p_1.x + rect.width, p_1.y);
			const Point p_4 = rect.br();
			const Point p_3 = Point(p_4.x - rect.width, p_4.y);

			const Point* points[4] = {&p_1, &p_2, &p_3, &p_4};
			int* npoints = new int{4};

			//mask = mask2;

			//cv::GaussianBlur(fgMaskMOG2, mask, Size(5, 5), 10, 10);
			fillPoly(mask, points, npoints, 1, cv::Scalar(255, 255 , 255 ));
		}

		bitwise_and(frame, frame, output, mask);


		imshow("video", output);
		imshow("mask", mask2);
		//imshow("mask", mask);

		if(REALTIME_VIDEO){
			if (waitKey(static_cast<int>(1.0 / fps * 1000)) >= 0) break;
		} else {
			if (waitKey(1.0/fps * 1000) >= 0) break;
		}
	}
	return 0;
}