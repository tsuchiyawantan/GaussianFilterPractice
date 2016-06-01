#pragma once
#include <opencv2/opencv.hpp>

#include <iostream>
#include <sstream>
#include <Windows.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;


class ExecuteSpaceFiltering{
private:
public:
	ExecuteSpaceFiltering(){}
	~ExecuteSpaceFiltering(){}


	//
	// 空間フィルタリングを用いた画像処理の例
	//
	void executeSpaceFiltering(cv::Mat &input1) {
		//
		// 空間フィルタリングを適用する配列
		//
		double filter[9] = { 0.33333, 0, 0, 0, 0.33333, 0, 0, 0, 0.33333 };

		cv::Mat image2 = cv::Mat(input1.size(), input1.type(), cvScalarAll(255));
		int width = input1.cols;
		int height = input1.rows;

		int i, j, n1, n2;

		//
		// 画像データのバイト数の定義
		//
		int n = width * height * 3;

		//
		// 各スキャンラインごとに
		//
		for (i = 0, n1 = 0; i < height; i++) {

			//
			// 各画素ごとに
			//
			for (j = 0; j < width; j++, n1 += 3) {
				double valueR = 0.0, valueG = 0.0, valueB = 0.0;

				//
				// 左上の画素値を加算
				//
				if (i > 0 && j > 0) {
					n2 = 3 * ((i - 1) * width + (j - 1));
					valueB += input1.at<cv::Vec3b>(i, j)[0] * filter[0];
					valueG += input1.at<cv::Vec3b>(i, j)[1] * filter[0];
					valueR += input1.at<cv::Vec3b>(i, j)[2] * filter[0];
				}

				//
				// 上の画素値を加算
				//
				if (i > 0) {
					n2 = 3 * ((i - 1) * width + j);
					valueB += input1.at<cv::Vec3b>(i, j)[0] * filter[1];
					valueG += input1.at<cv::Vec3b>(i, j)[1] * filter[1];
					valueR += input1.at<cv::Vec3b>(i, j)[2] * filter[1];
				}

				//
				// 右上の画素値を加算
				//
				if (i > 0 && j < (width - 1)) {
					n2 = 3 * ((i - 1) * width + (j + 1));
					valueB += input1.at<cv::Vec3b>(i, j)[0] * filter[2];
					valueG += input1.at<cv::Vec3b>(i, j)[1] * filter[2];
					valueR += input1.at<cv::Vec3b>(i, j)[2] * filter[2];
				}

				//
				// 左の画素値を加算
				//
				if (j > 0) {
					n2 = 3 * (i * width + (j - 1));
					valueB += input1.at<cv::Vec3b>(i, j)[0] * filter[3];
					valueG += input1.at<cv::Vec3b>(i, j)[1] * filter[3];
					valueR += input1.at<cv::Vec3b>(i, j)[2] * filter[3];
				}

				//
				// 同一場所のの画素値を加算
				//
				n2 = 3 * (i * width + j);
				valueB += input1.at<cv::Vec3b>(i, j)[0] * filter[4];
				valueG += input1.at<cv::Vec3b>(i, j)[1] * filter[4];
				valueR += input1.at<cv::Vec3b>(i, j)[2] * filter[4];

				//
				// 右の画素値を加算
				//
				if (j < (width - 1)) {
					n2 = 3 * (i * width + (j + 1));
					valueB += input1.at<cv::Vec3b>(i, j)[0] * filter[5];
					valueG += input1.at<cv::Vec3b>(i, j)[1] * filter[5];
					valueR += input1.at<cv::Vec3b>(i, j)[2] * filter[5];
				}

				//
				// 左下の画素との比較
				//
				if (i < (height - 1) && j > 0) {
					n2 = 3 * ((i + 1) * width + (j - 1));
					valueB += input1.at<cv::Vec3b>(i, j)[0] * filter[6];
					valueG += input1.at<cv::Vec3b>(i, j)[1] * filter[6];
					valueR += input1.at<cv::Vec3b>(i, j)[2] * filter[6];
				}

				//
				// 下の画素との比較
				//
				if (i < (height - 1)) {
					n2 = 3 * ((i + 1) * width + j);
					valueB += input1.at<cv::Vec3b>(i, j)[0] * filter[7];
					valueG += input1.at<cv::Vec3b>(i, j)[1] * filter[7];
					valueR += input1.at<cv::Vec3b>(i, j)[2] * filter[7];
				}

				//
				// 右下の画素との比較
				//
				if (i < (height - 1) && j < (width - 1)) {
					n2 = 3 * ((i + 1) * width + (j + 1));
					valueB += input1.at<cv::Vec3b>(i, j)[0] * filter[8];
					valueG += input1.at<cv::Vec3b>(i, j)[1] * filter[8];
					valueR += input1.at<cv::Vec3b>(i, j)[2] * filter[8];
				}

				// valueR, valueG, valueB の値を0～255の範囲にする
				if (valueR < 0.0) valueR = 0.0;
				if (valueR > 255.0) valueR = 255.0;
				if (valueG < 0.0) valueG = 0.0;
				if (valueG > 255.0) valueG = 255.0;
				if (valueB < 0.0) valueB = 0.0;
				if (valueB > 255.0) valueB = 255.0;

				image2.at<cv::Vec3b>(i, j)[0] = valueB;
				image2.at<cv::Vec3b>(i, j)[1] = valueG;
				image2.at<cv::Vec3b>(i, j)[2] = valueR;
			}
		}
	}
};