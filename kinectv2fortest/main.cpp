#include <iostream>
#include <sstream>
#include <time.h>
#include "stdafx.h"
#include "Log.h"
#include "Gaussian.h"

void doGaussian(cv::Mat &img){
	Gaussian gaus;
	gaus.createKernel(3);
	cv::Mat img_cp;
	//img.convertTo(img_cp, CV_32FC3, 1.0 / 255);
	//cv::imshow("lena CV32FC3 image", img_cp);
	for (int y = 0; y < img.rows; y+=3)
		for (int x = 0; x < img.cols; x+=3){
			//if (!gaus.checkMat(img, y, x)) continue;
			gaus.GaussianBlur(img, y, x);
		}
}


void main() {
	try {
		Log log;
		log.Initialize("log.txt");
			cv::Mat src_img = cv::imread("lena.jpg", 0);
			cv::imshow("src_img", src_img);
			doGaussian(src_img);
			cv::imshow("complete image", src_img);
			cv::imwrite("comp.jpg", src_img);
			auto key = cv::waitKey(200000);

	}
	catch (exception& ex) {
		cout << ex.what() << endl;
		string s;
		cin >> s;
	}
}
