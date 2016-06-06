#pragma once
#include <opencv2/opencv.hpp>

#include <iostream>
#include <sstream>
#include <Windows.h>
#include <time.h>

#define FILTERSIZE 5

using namespace std;


class ExecuteSpaceFiltering{
private:
public:
	vector<double> filter;
	ExecuteSpaceFiltering(double filter_size){
		double filter_value = 1 / filter_size;
		for (int i = 0; i < filter_size; i++)
			filter.push_back(filter_value);
	}
	~ExecuteSpaceFiltering(){}
	cv::Mat image2;

	void createNeighbour(int size, vector<pair<int, int>> &neighbour){
		// 範囲チェック
		if (size < 3) {
			size = 3;
		}
		if (size > 15) {
			size = 15;
		}
		size--;
		size /= 2;

		for (int y = -size; y <= size; y++) {
			for (int x = -size; x <= size; x++) {
				neighbour.push_back(make_pair(y, x));
			}
		}
	}

	void applyFiltering(int y, int x, vector<pair<int, int>> &neighbour, vector<double> &bgr, cv::Mat &image){
		for (int i = 0; i < neighbour.size(); i++){
			int dy = y + neighbour.at(i).first;
			int dx = x + neighbour.at(i).second;
			if (dy < 0 || dy >= image.rows || dx < 0 || dx >= image.cols) continue;
			bgr.at(0) += image.at<cv::Vec3b>(dy, dx)[0] * filter.at(i);
			bgr.at(1) += image.at<cv::Vec3b>(dy, dx)[1] * filter.at(i);
			bgr.at(2) += image.at<cv::Vec3b>(dy, dx)[2] * filter.at(i);
		}
	}

	//
	// 空間フィルタリングを用いた画像処理の例
	//
	void executeSpaceFiltering(cv::Mat &input1) {
		vector<pair<int, int>> neighbour;
		vector<double> bgr(3, 0.0);
		image2 = cv::Mat(input1.size(), input1.type(), cvScalarAll(255));
		int width = input1.cols;
		int height = input1.rows;

		int i, j, n1, n2;

		createNeighbour(FILTERSIZE, neighbour);
		
		//
		// 各スキャンラインごとに
		//
		for (i = 0; i < height; i++) {

			//
			// 各画素ごとに
			//
			for (j = 0; j < width; j++) {
				bgr = { 0.0, 0.0, 0.0 };
				int y = i;
				int x = j;
				applyFiltering(y, x, neighbour, bgr, input1);

				// valueR, valueG, valueB の値を0～255の範囲にする
				if (bgr.at(2) < 0.0) bgr.at(2) = 0.0;
				if (bgr.at(2) > 255.0) bgr.at(2) = 255.0;
				if (bgr.at(1) < 0.0) bgr.at(1) = 0.0;
				if (bgr.at(1) > 255.0) bgr.at(1) = 255.0;
				if (bgr.at(0) < 0.0) bgr.at(0) = 0.0;
				if (bgr.at(0) > 255.0) bgr.at(0) = 255.0;

				image2.at<cv::Vec3b>(y, x)[0] = bgr.at(0);
				image2.at<cv::Vec3b>(y, x)[1] = bgr.at(1);
				image2.at<cv::Vec3b>(y, x)[2] = bgr.at(2);
			}
		}
	}
};