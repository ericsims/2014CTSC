#include "Cv.h"
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "Time.h"

using namespace cv;
using namespace std;

bool closeVideo = false;

void Cv::debug() {
	VideoCapture cap(0);
	if ( !cap.isOpened() ) {
		cout << "Cannot open the web cam" << endl;
		return;
	}

	namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

	int iLowH = 150;
	int iHighH = 180;

	int iLowS = 10;
	int iHighS = 175;

	int iLowV = 180;
	int iHighV = 255;

	//Create trackbars in "Control" window
	createTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	createTrackbar("HighH", "Control", &iHighH, 179);

	createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	createTrackbar("HighS", "Control", &iHighS, 255);

	createTrackbar("LowV", "Control", &iLowV, 255);//Value (0 - 255)
	createTrackbar("HighV", "Control", &iHighV, 255);

	int iLastX = -1;
	int iLastY = -1;

	//Capture a temporary image from the camera
	Mat imgTmp;
	cap.read(imgTmp);

	//Create a black image with the size as the camera output
	Mat imgLines = Mat::zeros( imgTmp.size(), CV_8UC3 );;


	while (!closeVideo) {
		Mat img;

		bool bSuccess = cap.read(img); // read a new frame from video
		if (!bSuccess) {
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		cv::Rect crop(img.cols/2-50, img.rows/2-50, 100, 100);

		Mat imgOriginal = img(crop).clone();

		Mat imgHSV;
		// Convert the captured frame from BGR to HSV
		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);

		Mat imgThresholded;
		// Threshold the image
		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);

		//morphological opening (removes small objects from the foreground)
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(2, 2)) );
		dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(2, 2)) );

		//morphological closing (removes small holes from the foreground)
		dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)) );
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)) );

		//Calculate the moments of the thresholded image
		Moments oMoments = moments(imgThresholded);

		double dM01 = oMoments.m01;
		double dM10 = oMoments.m10;
		double dArea = oMoments.m00;

		if (dArea > 1500 && dArea < 5000) {
			//calculate the position of the point
			int posX = (dM10 / dArea)+img.cols/2-50;
			int posY = (dM01 / dArea)+img.rows/2-50;

			if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0) {
				//Draw a red line from the previous point to the current point
				line(imgLines, Point(posX, posY), Point(iLastX, iLastY), Scalar(0,0,255), 2);
			}

			iLastX = posX;
			iLastY = posY;
		}

		imshow("Thresholded Image", imgThresholded); //show the thresholded image

		rectangle(imgLines, Point(img.cols/2-50, img.rows/2-50), Point(img.cols/2+50, img.rows/2+50), Scalar(255,0,0));
		img = img + imgLines;
		imshow("Original", img); //show the original image

		if (waitKey(30) == 27) { //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
			Cv::exitCleanly();
		}
	}
	cap.release();
}

void Cv::locatePoint(Cordinate &current, ErrorCall returnError) {
	Time timer(true);
	VideoCapture cap(-1);
	if ( !cap.isOpened() ) {
		cout << "Cannot open the web cam" << endl;
	}
	int iLowH = 150;
	int iHighH = 180;

	int iLowS = 10;
	int iHighS = 175;

	int iLowV = 180;
	int iHighV = 255;

	while (!closeVideo) {
		//Capture a temporary image from the camera
		Mat imgTmp;
		cap.read(imgTmp);

		Mat img;

		bool bSuccess = cap.read(img); // read a new frame from video
		if (!bSuccess) {
			cout << "Cannot read a frame from video stream" << endl;
			returnError("Cannot read a frame from video stream");
		}

		cv::Rect crop(img.cols/2-50, img.rows/2-50, 100, 100);

		Mat imgOriginal = img(crop).clone();

		Mat imgHSV;
		// Convert the captured frame from BGR to HSV
		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);

		Mat imgThresholded;
		// Threshold the image
		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);

		// morphological opening (removes small objects from the foreground)
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(2, 2)) );
		dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(2, 2)) );

		// morphological closing (removes small holes from the foreground)
		dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)) );
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)) );

		// Calculate the moments of the thresholded image
		Moments oMoments = moments(imgThresholded);

		double dM01 = oMoments.m01;
		double dM10 = oMoments.m10;
		double dArea = oMoments.m00;

		if (dArea > 1500 && dArea < 5000) {
			// calculate the position of the point
			int posX = (dM10 / dArea) + img.cols/2-50;
			int posY = (dM01 / dArea) + img.rows/2-50;

			Cordinate point(posX, posY);

			if (posX >= 0 && posY >= 0)
				current = point;
		}
		// cout << timer.getPerSecond() << endl;
	}
	cap.release();
}

void Cv::displacement(int &angle, ErrorCall returnError) {
	Mat src; Mat src_gray;
	int thresh = 100;
	bool initialized = false;
	Point lastPoint;
	int lastArea = 0, displacement[2] = {0, 0};
	RNG rng(12345);
	vector<vector<Point> > lastContours;

	Time timer(true);
	VideoCapture cap(-1);
	if ( !cap.isOpened() ) {
		cout << "Cannot open the web cam" << endl;
	}
	while(!closeVideo) {
		cap.read(src);

		//cvtColor( src, src, CV_BGR2GRAY );
		erode(src, src, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(src, src, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		blur(src, src, Size(3,3));

		Mat canny_output;
		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;

		/// Detect edges using canny
		Canny( src, canny_output, thresh, thresh*2, 3 );
		/// Find contours
		findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

		if(!initialized) {
			lastContours = contours;
			lastArea = 0;
			lastPoint = Point2f(0, 0);
			initialized = true;
			cout << "contours initialized" << endl;
		}

		Scalar color[] = {Scalar(100, 100, 0), Scalar(255, 0, 255), Scalar(0, 0, 255)};

		vector<Moments> mu(contours.size() );
		for( unsigned int i = 0; i < contours.size(); i++ )
			mu[i] = moments( contours[i], false );

		///  Get the mass centers:
		vector<Point2f> mc( contours.size() );
		for( unsigned int i = 0; i < contours.size(); i++ )
			mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 );

		/// Draw contours
		int max[2] = {0, 0};
		Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
		for( unsigned int i = 0; i< contours.size(); i++ ) {
			int area = contourArea(contours[i]);
			if(area > max[1]) {
				max[0] = i;
				max[1] = area;
			}
			drawContours( drawing, contours, i, color[0], 1, 8, hierarchy, 0, Point() );
		}
		int tempDis[2] = {(int)(mc[max[0]].x - lastPoint.x), (int)(mc[max[0]].y - lastPoint.y)};
		if(sqrt( (tempDis[0]^2) + (tempDis[1]^2) ) < 10 && abs(lastArea - max[1]) < 50) {
			displacement[0] += tempDis[0];
			cout << displacement[0] << endl;
			drawContours( drawing, contours, max[0], color[2], 8, 8, hierarchy, 0, Point() );
			circle( drawing, mc[max[0]], 4, color[1], -1, 8, 0 );
			line(drawing, lastPoint, mc[max[0]], color[2], 1, 8, 0);
		}
		lastArea = max[1];
		lastPoint = mc[max[0]];

		if(true) {
			/// Show in a window
			namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
			imshow( "Contours", drawing + src );
		}

		angle = displacement[0];
	}
	cap.release();
}

int Cv::exitCleanly() {
	cvDestroyAllWindows();
	closeVideo = true;
	return 1; // successful
}
