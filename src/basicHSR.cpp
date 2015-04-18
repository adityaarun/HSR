#ifdef _CH_
#pragma package <opencv>
#endif

#ifndef _EiC
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string>
#endif

#include "preprocessing.h"
#include "basicHSR.h"

#define DEBUG true

void basicHSR::getData()
{
	printf("Getdata called\n");
	IplImage* src_image;
	IplImage prs_image;
	CvMat row,data;
	std::string file;
	int i,j;
	for(i =0; i<classes; i++){
		for( j = 0; j< trainSamples; j++){
			std::string s;
			std::stringstream istr, jstr;
			istr << i;
			jstr << j;
			file = sampleDatasetPath+"/"+istr.str()+"/"+jstr.str()+".jpg";
			std::cout<<"Processing file : "+file<<"\n";
			src_image = cvLoadImage(file.c_str(),0);
			if(!src_image){
				std::cout<<"Error: Cant load image "<<file<<"\n";
				exit(-1);
			}
			//process file
			prs_image = preprocessing(src_image, size, size);

			//Set class label
			cvGetRow(trainClasses, &row, i*trainSamples + j);
			cvSet(&row, cvRealScalar(i));
			//Set data 
			cvGetRow(trainData, &row, i*trainSamples + j);

			IplImage* img = cvCreateImage( cvSize( size, size ), IPL_DEPTH_32F, 1 );
			//convert 8 bits image to 32 float image
			cvConvertScale(&prs_image, img, 0.0039215, 0);

			cvGetSubRect(img, &data, cvRect(0,0, size,size));

			CvMat row_header, *row1;
			//convert data matrix sizexsize to vecor
			row1 = cvReshape( &data, &row_header, 0, 1 );
			cvCopy(row1, &row, NULL);
		}
	}
}

void basicHSR::train()
{
	knn=new CvKNearest( trainData, trainClasses, 0, false, K );
}

float basicHSR::classify(IplImage* img, int showResult, bool speak)
{
	IplImage prs_image;
	CvMat data;
	CvMat* nearest=cvCreateMat(1,K,CV_32FC1);
	float result;
	//process file
	prs_image = preprocessing(img, size, size);

	//Set data 
	IplImage* img32 = cvCreateImage( cvSize( size, size ), IPL_DEPTH_32F, 1 );
	cvConvertScale(&prs_image, img32, 0.0039215, 0);
	cvGetSubRect(img32, &data, cvRect(0,0, size,size));
	CvMat row_header, *row1;
	row1 = cvReshape( &data, &row_header, 0, 1 );

	result=knn->find_nearest(row1,K,0,0,nearest,0);

	int accuracy=0;
	for(int i=0;i<K;i++){
		if( nearest->data.fl[i] == result)
			accuracy++;
	}
	float pre=100*((float)accuracy/(float)K);
	if(showResult==1){
		printf(" ---------------------------------------------------------------\n");
		printf("|\tClass\t|\tPrecision\t|\tAccuracy\t|\n");
		printf("|\t%.0f\t| \t%.2f%%  \t| \t%d of %d \t| \n",result,pre,accuracy,K);
		printf(" ---------------------------------------------------------------\n");
	}
	if(speak){
		std::string speakCommand;
		std::string s;
		std::stringstream istr;
		istr << result;
		speakCommand = "echo '"+istr.str()+"' | festival --tts";
		std::system(speakCommand.c_str());
	}
	return result;

}

void basicHSR::test(){
	IplImage* src_image;
	IplImage prs_image;
	CvMat row,data;
	std::string file;
	int i,j;
	int error=0;
	int testCount=0;
	for(i =0; i<classes; i++){
		for( j = testSampleStart; j< testSampleStart+testSampleNumber; j++){
			std::string s;
			std::stringstream istr, jstr;
			istr << i;
			jstr << j;
			file = sampleDatasetPath+"/"+istr.str()+"/"+jstr.str()+".jpg";
			std::cout<<"Processing file : "+file<<"\n";
			src_image = cvLoadImage(file.c_str(),0);
			if(!src_image){
				std::cout<<"Error: Cant load image "+file<<"\n";
				exit(-1);
			}
			//process file
			prs_image = preprocessing(src_image, size, size);
			float r=classify(&prs_image,0,false);
			if((int)r!=i)
				error++;

			testCount++;
		}
	}
	float totalerror=100*(float)error/(float)testCount;
	printf("System Error: %.2f%%\n", totalerror);

}

void basicHSR::init(){
	//initial
	size=40;
	trainData = cvCreateMat(trainSamples*classes, size*size, CV_32FC1);
	trainClasses = cvCreateMat(trainSamples*classes, 1, CV_32FC1);
	//Get data (get images and process it)
	getData();
	//train	
	train();
	//Test	
	test();
}

basicHSR::basicHSR()
{

}


