#include <iostream>
#include <sstream>
#include <time.h>
#include "stdafx.h"
#include "Log.h"
#include "Gaussian.h"
#include "ExecuteSpaceFiltering.h"

#define FILTERSIZE 25

void doExecuteSpaceFiltering(cv::Mat &img){
		ExecuteSpaceFiltering spaceFilter(FILTERSIZE);
		spaceFilter.executeSpaceFilteringAll(img);
		cv::imshow("Space Filtering result", spaceFilter.image2);
}

void main() {
	try {
		cv::Mat src_img = cv::imread("lena.jpg", -1);
		cv::imshow("src_img", src_img);
		doExecuteSpaceFiltering(src_img);
		cv::waitKey(20000);
		system("pause");
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
		string s;
		cin >> s;
	}
}
