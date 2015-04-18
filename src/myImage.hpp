#ifndef _MYIMAGE_
#define _MYIMAGE_ 

#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

// Class to keep all the things related to tracking and detection clean
// Refer to comments in cpp file for explanations

class MyImage{
	public:
		MyImage(int webCamera);
		MyImage();
		// Low resolution image of the source image
		Mat srcLR;
		// Source image
		Mat src;
		// Black and white image of the source
		Mat bw;
		vector<Mat> bwList;
		// Capture from camera
		VideoCapture cap;		
		// Which camera to open
		int cameraSrc; 
		void initWebCamera(int i);
};



#endif
