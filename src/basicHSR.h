#ifdef _CH_
#pragma package <opencv>
#endif

#ifndef _EiC
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "opencv/ml.h"
#include <stdio.h>
#include <ctype.h>
#include <string>
#endif

class basicHSR{
	public:
		float classify(IplImage* img,int showResult, bool speak);
		basicHSR ();
		void init();
		void test();
		std::string sampleDatasetPath;
		int classes;
		int size;
		int trainSamples;
		int testSampleNumber;
		int testSampleStart;
	private:
		const int K=10;
		CvMat* trainData;
		CvMat* trainClasses;
		CvKNearest *knn;
		void getData();
		void train();
};
