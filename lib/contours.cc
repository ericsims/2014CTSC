#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace cv;
using namespace std;

Mat src; Mat src_gray;
int thresh = 70;
int max_thresh = 255;
bool initialized = false;
Point lastPoint[2];
int lastArea[2], displacement[2];
RNG rng(12345);
vector<vector<Point> > lastContours;

/// Function header
void thresh_callback(int, void* );

/** @function main */
int main( int argc, char** argv )
{

	VideoCapture cap(0);
	/// Load source image and convert it to gray
	while(true) {
		cap.read(src);
		erode(src, src, getStructuringElement(MORPH_ELLIPSE, Size(2, 2)));
		dilate(src, src, getStructuringElement(MORPH_ELLIPSE, Size(2, 2)));
		//dilate(src, src, getStructuringElement(MORPH_ELLIPSE, Size(2, 2)) );
		//erode(src, src, getStructuringElement(MORPH_ELLIPSE, Size(2, 2)) );
		cvtColor( src, src_gray, CV_BGR2GRAY );
 		blur( src_gray, src_gray, Size(3,3) );

		thresh_callback( 0, 0 );

		waitKey(0);
	}
	return(0);
}

/** @function thresh_callback */
void thresh_callback(int, void* ) {
	Mat canny_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	/// Detect edges using canny
	Canny( src, canny_output, thresh, thresh*2, 3 );
	/// Find contours
	findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

	if(!initialized) {
		lastContours = contours;
		lastArea[0] = 0;
		lastArea[1] = 0;
		lastPoint[0] = Point2f(0, 0);
		lastPoint[1] = Point2f(0, 0);
		initialized = true;
		cout << "contours initialized" << endl;
	}

	Scalar color[] = {Scalar(100, 100, 0), Scalar(255, 0, 255), Scalar(0, 0, 255)};

	vector<Moments> mu(contours.size() );
	for( int i = 0; i < contours.size(); i++ )
		mu[i] = moments( contours[i], false );

	///  Get the mass centers:
	vector<Point2f> mc( contours.size() );
	for( int i = 0; i < contours.size(); i++ )
		mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 );

	/// Draw contours
	int max[2][2] = {{0, 0}, {0, 0}};
	Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
	for( int i = 0; i< contours.size(); i++ ) {
		int area = contourArea(contours[i]);
		if(area > max[0][1]) {
			max[0][0] = i;
			max[0][1] = area;
		} else if (area < max[1][1]) {
			max[1][0] = i;
			max[1][1] = area;
		}
		drawContours( drawing, contours, i, color[0], 1, 8, hierarchy, 0, Point() );
	}
	int tempDis[2][2] = {{(mc[max[0][0]].x - lastPoint[0].x), (mc[max[0][0]].y - lastPoint[0].y)},
			{(mc[max[1][0]].x - lastPoint[1].x), (mc[max[1][0]].y - lastPoint[1].y)}};
	if (sqrt( (tempDis[0][0]^2) + (tempDis[0][1]^2) ) < 20 && abs(lastArea[0] - max[0][1]) < 50){
		displacement[0] += tempDis[0][0];
		cout << displacement[0] << endl;
		drawContours( drawing, contours, max[0][0], color[2], 8, 8, hierarchy, 0, Point() );
		circle( drawing, mc[max[0][0]], 4, color[1], -1, 8, 0 );
		//line(drawing, lastPoint[0], mc[max[0][0]], color[2], 1, 8, 0);
	}
	/*if (sqrt( (tempDis[1][0]^2) + (tempDis[1][1]^2) ) < 10 && abs(lastArea[1] - max[1][1]) < 50){
		//displacement[0] += tempDis[1][0];
		drawContours( drawing, contours, max[1][0], color[2], 8, 8, hierarchy, 0, Point() );
		circle( drawing, mc[max[1][0]], 4, color[1], -1, 8, 0 );
		//line(drawing, lastPoint[1], mc[max[1][0]], color[2], 1, 8, 0);
	}*/
	lastArea[0] = max[0][1];
	lastPoint[0] = mc[max[0][0]];
	lastArea[1] = max[1][1];
	lastPoint[1] = mc[max[1][0]];

	/// Show in a window
	namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
	imshow( "Contours", drawing + src );
}
