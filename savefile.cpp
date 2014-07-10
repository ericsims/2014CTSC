#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
//#include <stdafx.h>
#include <cv.h>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
	VideoCapture cap(0); //capture the video from web cam

	if ( !cap.isOpened() )  // if not success, exit program
	{
		cout << "Cannot open the web cam" << endl;
		return -1;
	}

	//namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

	int iLowH = 24;
	int iHighH = 103;

	int iLowS = 6;
	int iHighS = 91;

	int iLowV = 190;
	int iHighV = 255;

	/*
	//Create trackbars in "Control" window
	cvCreateTrackbar("LowH", "Control", &iLowH, 255); //Hue (0 - 230)
	cvCreateTrackbar("HighH", "Control", &iHighH, 255);

	cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighS", "Control", &iHighS, 255);

	cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
	cvCreateTrackbar("HighV", "Control", &iHighV, 255);
	 */
	Mat imgOrig;

	bool bSuccess = cap.read(imgOrig); // read a new frame from video

	if (!bSuccess) //if not success, break loop
	{
		cout << "Cannot read a frame from video stream" << endl;

	}

	cv::Rect crop(imgOrig.cols/2-50, imgOrig.rows/2-50, 100, 100);

	Mat img = imgOrig(crop).clone();


	vector<int> compression_params; //vector that stores the compression parameters of the image

	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION); //specify the compression technique

	compression_params.push_back(98); //specify the compression quality



	bool bSuccess2 = imwrite("test.png", img, compression_params); //write the image to file



	if ( !bSuccess2 )

	{

		cout << "ERROR : Failed to save the image" << endl;

		//system("pause"); //wait for a key press

	}


	imshow("img", img); //display the image which is stored in the 'img' in the "MyWindow" window
	imshow("imgOrig", imgOrig); //display the image which is stored in the 'img' in the "MyWindow" window

	waitKey(0);  //wait for a keypress

	destroyWindow("img"); //destroy the window with the name, "MyWindow"
	destroyWindow("imgOrig"); //destroy the window with the name, "MyWindow"

	return 0;
}
