#pragma once
#include <opencv2/opencv.hpp>

#include <iostream>
#include <sstream>
#include <Windows.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

class Gaussian{
private:
public:
	vector<float> kernel;
	vector<pair<int, int>> var_yx;
	Gaussian(){}
	~Gaussian(){}

	boolean checkMat(cv::Mat &img, int y, int x){
		for (int i = 0; i < var_yx.size(); i++) {
			int dy = y + var_yx.at(i).first;
			int dx = x + var_yx.at(i).second;
			if (dy < 0 || dy >= img.rows || dx < 0 || dx >= img.cols) return false;
		}
		return true;
	}

	void createKernel(int size){
		// 範囲チェック
		if (size < 3) {
			size = 3;
		}
		if (size > 15) {
			size = 15;
		}
		size--;
		size /= 2;

		float sigma = 2.0;
		float sum = 0;
		//kernel.reserve((size * 2 + 1) * (size * 2 + 1));
		for (int y = -size; y <= size; y++) {
			for (int x = -size; x <= size; x++) {
				float gf = GaussianF(x, y, sigma);
				kernel.push_back(gf);
				var_yx.push_back(make_pair(y, x));
				sum += gf;
			}
		}
		for (int i = 0; i < kernel.size(); i++) {
			kernel.at(i) /= sum;
		}
	}
	boolean kernelCheck(){
		double sum = 0;
		for (int i = 0; i < kernel.size(); i++) sum += kernel.at(i);

		if (1.0 == sum) return true;
		return false;
	}
	
	// ガウス分布のメソッド
	double GaussianF(int y, int x, float sigma) {
		float pi = (float)M_PI;
		float sigma2 = sigma * sigma;
		double gauss_const = 1.0 / (2.0 * pi * sigma * sigma);
		double f = gauss_const * exp(-(x * x + y * y) / (2.0 * sigma * sigma));
		return f;

	}
	
	// ガウシアンフィルタを適用する
	void GaussianBlur(cv::Mat &img, int y, int x) {
		for (int i = 0; i < var_yx.size(); i++){
			int dy = y + var_yx.at(i).first;
			int dx = x + var_yx.at(i).second;
			if (dy < 0 || dy >= img.rows || dx < 0 || dx >= img.cols) continue;	
			/*
			img.at<cv::Vec3b>(dy, dx)[0] = img.at<cv::Vec3b>(dy, dx)[0] * kernel.at(i); // b; //青
			img.at<cv::Vec3b>(dy, dx)[1] = img.at<cv::Vec3b>(dy, dx)[1] * kernel.at(i); // g; //緑
			img.at<cv::Vec3b>(dy, dx)[2] = img.at<cv::Vec3b>(dy, dx)[2] * kernel.at(i); // r; //赤	
		*/
			unsigned char value = img.at<uchar>(dy, dx) * kernel.at(i);
			img.at<uchar>(dy, dx) = value;
		}
	}

};