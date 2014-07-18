#include "Cv.h"
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "Time.h"

using namespace cv;
using namespace std;

void Cv::debug() {
	VideoCapture cap(0);
	if ( !cap.isOpened() ) {
		cout << "Cannot open the web cam" << endl;
		return;
	}

	namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

	int iLowH = 20;
	int iHighH = 123;

	int iLowS = 10;
	int iHighS = 100;

	int iLowV = 220;
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


	while (true) {
		Mat img;

		bool bSuccess = cap.read(img); // read a new frame from video
		if (!bSuccess) {
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		cv::Rect crop(img.cols/2-50, img.rows/2-50, 100, 100);

		Mat imgOriginal = img(crop).clone();

		Mat imgHSV;

		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

		Mat imgThresholded;

		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

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

		if (dArea > 1 && dArea < 1000) {
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

		img = img + imgLines;
		imshow("Original", img); //show the original image

		if (waitKey(30) == 27) { //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
			cvDestroyAllWindows();
			break;
		}
	}
}

void Cv::locatePoint(Cordinate &current, ErrorCall returnError) {
	Time timer(true);
	VideoCapture cap(0);
	if ( !cap.isOpened() ) {
		cout << "Cannot open the web cam" << endl;
	}
	int iLowH = 20;
	int iHighH = 123;

	int iLowS = 10;
	int iHighS = 100;

	int iLowV = 10; //220
	int iHighV = 255;

	bool found = false;

	do {
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

		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

		Mat imgThresholded;

		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

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

		if (dArea > 1 && dArea < 100000) {
			//calculate the position of the point
			int posX = (dM10 / dArea) + img.cols/2-50;
			int posY = (dM01 / dArea) + img.rows/2-50;

			Cordinate point(posX, posY);

			if (posX >= 0 && posY >= 0) {
				current = point;
				found = true;
			} else
				found = false;
		} else
			found = false;
		//cout << timer.getPerSecond() << endl;
	} while (true);
}
