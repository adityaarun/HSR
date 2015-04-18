/*
 ============================================================================
 Name        : ocr.c
 Author      : Aditya
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#ifdef _CH_
#pragma package <opencv>
#endif

#ifndef _EiC
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <iostream>
#endif

using namespace cv;
using namespace std;

#include "basicHSR.h"
#include "preprocessing.h"

/*int main( int argc, char** argv )
{
	IplImage *img;
	printf("Main called %s\n", argv[1]);
	img = cvLoadImage(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	printf("Image Loaded\n");
	cvNamedWindow("Input Image", CV_WINDOW_AUTOSIZE);
	basicHSR hsr;
	printf("Object created\n");
	hsr.classify(img,1);
	waitKey(0);

    return 0;
}*/

#ifdef _EiC
main(1,"mouseEvent.c");
#endif
