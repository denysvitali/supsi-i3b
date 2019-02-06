#include "Tracker.h"

Tracker::Tracker(std::string name, Rect trackerInitialPos, Direction dir) {
	m_originaltrackerpos = std::move(trackerInitialPos);
	m_trackerpos = m_originaltrackerpos;
	direction = dir;
	m_name = name;
}

bool inFrame(Mat frame, Rect rect){
	return
			rect.tl().x >= 0 && rect.tl().x <= frame.size[0] &&
			rect.br().x >= 0 && rect.br().x <= frame.size[0] &&
			rect.tl().y >= 0 && rect.tl().y <= frame.size[1] &&
			rect.br().y >= 0 && rect.br().y <= frame.size[1];
}

void Tracker::track(Mat frame, Mat morph, int frameNumber) {
	frame_length++;
	if(first_seen == -1) {
		first_seen = frameNumber;
	}
	RotatedRect rect = CamShift(morph, m_trackerpos, TermCriteria{TermCriteria::EPS | TermCriteria::COUNT, 1000, 0.001});
	Mat output;

	bool iteration_end = false;

	if(rect.size.area() == 0){
		m_trackerpos = m_originaltrackerpos;
		frame_length = 0;
		frame.copyTo(output);
	} else {

		Rect br = rect.boundingRect();
		Rect ltbr = lastTrackerPos.boundingRect();

		switch(direction){
			case LEFT:
				if(br.tl().x > ltbr.tl().x){
					// Moving in the opposite direction
					m_trackerpos = m_originaltrackerpos;
					frame_length = 0;
				} else if(br.tl().x <= 0) {
					// Touched the edge
					m_trackerpos = m_originaltrackerpos;
					iteration_end = true;
				}
				break;
			case RIGHT:
				if(br.tl().x < ltbr.tl().x){
					// Moving in the opposite direction
					m_trackerpos = m_originaltrackerpos;
					frame_length = 0;
				} else if(br.tl().x + br.width >= frame.cols) {
					// Touched the edge
					m_trackerpos = m_originaltrackerpos;
					iteration_end = true;
				}
				break;
		}

		if(frame_length > 0){
			if(inFrame(frame, br)){
				Mat carPic;
				Mat carMask = Mat::zeros(frame.size.operator()(), CV_8U);
				rectangle(carMask, br, Scalar(255,255,255), FILLED);
				frame.copyTo(carPic, carMask);
				carPic(br).copyTo(m_carPic);
			}
		} else {
			first_seen = -1;
			frame_length = 0;
		}

		if(iteration_end){
			std::cout << m_name << " - Car " << car_count << " seen for " << frame_length << " frames (from frame " << first_seen << ")." << std::endl;
			frame_length = 0;
			car_count++;

			std::stringstream output_path;
			output_path << "../recognition_results/" << (direction == RIGHT ? "right" : "left") << "_" << car_count << "_" << first_seen << ".jpg";

			Mat output;
			std::stringstream ss;
			ss << "#" << car_count << ": " << first_seen << " - " << first_seen + frame_length << " " << (direction == Direction::RIGHT ? "right" : "left");
			m_carPic.copyTo(output);
			putText(output, ss.str(), Point(0,30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255, 0, 0));

			imwrite(output_path.str(), output);
		}
		Mat temp;
		frame.copyTo(temp);
		Point2f pts[4];
		lastTrackerPos.points(pts);

		for (int i = 0; i < 4; i++)
			line(temp, pts[i], pts[(i+1)%4], Scalar(0,255,0));

		temp.copyTo(output);
	}

	rectangle(output, m_trackerpos, Scalar(255, 0, 0));

	imshow(m_name, output);

	lastTrackerPos = rect;
}

int Tracker::carsCounter() {
	return car_count;
}
