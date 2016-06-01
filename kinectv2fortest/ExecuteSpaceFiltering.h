#pragma once
#include <opencv2/opencv.hpp>

#include <iostream>
#include <sstream>
#include <Windows.h>
#include <time.h>

#define FILTERSIZE 3

using namespace std;


class ExecuteSpaceFiltering{
private:
public:
	ExecuteSpaceFiltering(){}
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

	//
	// 空間フィルタリングを用いた画像処理の例
	//
	void executeSpaceFiltering(cv::Mat &input1) {
		//
		// 空間フィルタリングを適用する配列
		//
		double filter[9] = { 0.33333, 0, 0, 0, 0.33333, 0, 0, 0, 0.33333 };
		vector<pair<int, int>> neighbour;
		image2 = cv::Mat(input1.size(), input1.type(), cvScalarAll(255));
		int width = input1.cols;
		int height = input1.rows;

		int i, j, n1, n2;

		//
		// 画像データのバイト数の定義
		//
		int n = width * height * 3;
		createNeighbour(FILTERSIZE, neighbour);
		//
		// 各スキャンラインごとに
		//
		for (i = 0; i < height; i++) {

			//
			// 各画素ごとに
			//
			for (j = 0; j < width; j++) {
				double valueR = 0.0, valueG = 0.0, valueB = 0.0;
				int y = i;
				int x = j;
				//
				// 左上の画素値を加算
				//
				if (i > 0 && j > 0) {
					y = i + neighbour.at(0).first;
					x = j + neighbour.at(0).second;
					valueB += input1.at<cv::Vec3b>(y, x)[0] * filter[0];
					valueG += input1.at<cv::Vec3b>(y, x)[1] * filter[0];
					valueR += input1.at<cv::Vec3b>(y, x)[2] * filter[0];
				}

				//
				// 上の画素値を加算
				//
				if (i > 0) {
					y = i + neighbour.at(1).first;
					x = j + neighbour.at(1).second;
					valueB += input1.at<cv::Vec3b>(y, x)[0] * filter[1];
					valueG += input1.at<cv::Vec3b>(y, x)[1] * filter[1];
					valueR += input1.at<cv::Vec3b>(y, x)[2] * filter[1];
				}

				//
				// 右上の画素値を加算
				//
				if (i > 0 && j < (width - 1)) {
					y = i + neighbour.at(2).first;
					x = j + neighbour.at(2).second;
					valueB += input1.at<cv::Vec3b>(y, x)[0] * filter[2];
					valueG += input1.at<cv::Vec3b>(y, x)[1] * filter[2];
					valueR += input1.at<cv::Vec3b>(y, x)[2] * filter[2];
				}

				//
				// 左の画素値を加算
				//
				if (j > 0) {
					y = i + neighbour.at(3).first;
					x = j + neighbour.at(3).second;
					valueB += input1.at<cv::Vec3b>(y, x)[0] * filter[3];
					valueG += input1.at<cv::Vec3b>(y, x)[1] * filter[3];
					valueR += input1.at<cv::Vec3b>(y, x)[2] * filter[3];
				}

				//
				// 同一場所のの画素値を加算
				//
				y = i + neighbour.at(4).first;
				x = j + neighbour.at(4).second;
				valueB += input1.at<cv::Vec3b>(y, x)[0] * filter[4];
				valueG += input1.at<cv::Vec3b>(y, x)[1] * filter[4];
				valueR += input1.at<cv::Vec3b>(y, x)[2] * filter[4];

				//
				// 右の画素値を加算
				//
				if (j < (width - 1)) {
					y = i + neighbour.at(5).first;
					x = j + neighbour.at(5).second;
					valueB += input1.at<cv::Vec3b>(y, x)[0] * filter[5];
					valueG += input1.at<cv::Vec3b>(y, x)[1] * filter[5];
					valueR += input1.at<cv::Vec3b>(y, x)[2] * filter[5];
				}

				//
				// 左下の画素との比較
				//
				if (i < (height - 1) && j > 0) {
					y = i + neighbour.at(6).first;
					x = j + neighbour.at(6).second;
					valueB += input1.at<cv::Vec3b>(y, x)[0] * filter[6];
					valueG += input1.at<cv::Vec3b>(y, x)[1] * filter[6];
					valueR += input1.at<cv::Vec3b>(y, x)[2] * filter[6];
				}

				//
				// 下の画素との比較
				//
				if (i < (height - 1)) {
					y = i + neighbour.at(7).first;
					x = j + neighbour.at(7).second;
					valueB += input1.at<cv::Vec3b>(y, x)[0] * filter[7];
					valueG += input1.at<cv::Vec3b>(y, x)[1] * filter[7];
					valueR += input1.at<cv::Vec3b>(y, x)[2] * filter[7];
				}

				//
				// 右下の画素との比較
				//
				if (i < (height - 1) && j < (width - 1)) {
					y = i + neighbour.at(8).first;
					x = j + neighbour.at(8).second;
					valueB += input1.at<cv::Vec3b>(y, x)[0] * filter[8];
					valueG += input1.at<cv::Vec3b>(y, x)[1] * filter[8];
					valueR += input1.at<cv::Vec3b>(y, x)[2] * filter[8];
				}

				// valueR, valueG, valueB の値を0～255の範囲にする
				if (valueR < 0.0) valueR = 0.0;
				if (valueR > 255.0) valueR = 255.0;
				if (valueG < 0.0) valueG = 0.0;
				if (valueG > 255.0) valueG = 255.0;
				if (valueB < 0.0) valueB = 0.0;
				if (valueB > 255.0) valueB = 255.0;

				y = i;
				x = j;
				image2.at<cv::Vec3b>(y, x)[0] = valueB;
				image2.at<cv::Vec3b>(y, x)[1] = valueG;
				image2.at<cv::Vec3b>(y, x)[2] = valueR;
			}
		}
	}
};