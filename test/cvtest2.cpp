#include <cv.h>
#include <highgui.h>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;

int main()
{
	int iLowH = 24;
	int iHighH = 103;

	int iLowS = 6;
	int iHighS = 91;

	int iLowV = 190;
	int iHighV = 255;

	IplImage* file = cvLoadImage("test.png");

	Mat imgOriginal = cv::cvarrToMat(file);

	//show the original image
	cvNamedWindow("Raw");
	cvShowImage("Raw",file);

	Mat imgHSV;

	cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

	cv::Mat imgThresholded;

	inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

	//morphological opening (remove small objects from the foreground)
	erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(2, 2)));
	dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(2, 2)));

	//morphological closing (fill small holes in the foreground)
	dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(8, 8)));
	erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(8, 8)));


	CvSeq* contours;  //hold the pointer to a contour in the memory block
	CvSeq* result;   //hold sequence of points of a contour
	CvMemStorage *storage = cvCreateMemStorage(0); //storage area for all contours

	//IplImage* imgArray = &imgThresholded.operator IplImage();
	IplImage imgArray = imgThresholded;
	//finding all contours in the image
	cvFindContours(&imgArray, storage, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));

	//iterating through each contour
	while(contours)
	{
		//obtain a sequence of points of contour, pointed by the variable 'contour'
		result = cvApproxPoly(contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02, 0);

		//if there are 3  vertices  in the contour(It should be a triangle)
		if(result->total >= 4 )
		{
			//iterating through each point
			CvPoint *pt[3];
			for(int i=0;i<3;i++){
				pt[i] = (CvPoint*)cvGetSeqElem(result, i);
			}

			cvCircle(&imgArray, *pt[0], 20, cvScalar(0,0,255), 4, 8, 0);

		}

		//obtain the next contour
		contours = contours->h_next;
	}

	//show the image in which identified shapes are marked
	cvNamedWindow("Tracked");
	cvShowImage("Tracked",&imgArray);

	cvWaitKey(0); //wait for a key press

	//cleaning up
	cvDestroyAllWindows();
	cvReleaseMemStorage(&storage);
	//cvReleaseImage(&imgOriginal);
	//cvReleaseImage(&imgThresholded);

	return 0;
}
