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
	cv::Mat image2;

	//
	// ��ԃt�B���^�����O��p�����摜�����̗�
	//
	void executeSpaceFiltering(cv::Mat &input1) {
		//
		// ��ԃt�B���^�����O��K�p����z��
		//
		double filter[9] = { 0.33333, 0, 0, 0, 0.33333, 0, 0, 0, 0.33333 };

		image2 = cv::Mat(input1.size(), input1.type(), cvScalarAll(255));
		int width = input1.cols;
		int height = input1.rows;

		int i, j, n1, n2;

		//
		// �摜�f�[�^�̃o�C�g���̒�`
		//
		int n = width * height * 3;

		//
		// �e�X�L�������C�����Ƃ�
		//
		for (i = 0, n1 = 0; i < height; i++) {

			//
			// �e��f���Ƃ�
			//
			for (j = 0; j < width; j++, n1 += 3) {
				double valueR = 0.0, valueG = 0.0, valueB = 0.0;

				//
				// ����̉�f�l�����Z
				//
				if (i > 0 && j > 0) {
					n2 = 3 * ((i - 1) * width + (j - 1));
					valueB += input1.at<cv::Vec3b>(i, j)[0] * filter[0];
					valueG += input1.at<cv::Vec3b>(i, j)[1] * filter[0];
					valueR += input1.at<cv::Vec3b>(i, j)[2] * filter[0];
				}

				//
				// ��̉�f�l�����Z
				//
				if (i > 0) {
					n2 = 3 * ((i - 1) * width + j);
					valueB += input1.at<cv::Vec3b>(i, j)[0] * filter[1];
					valueG += input1.at<cv::Vec3b>(i, j)[1] * filter[1];
					valueR += input1.at<cv::Vec3b>(i, j)[2] * filter[1];
				}

				//
				// �E��̉�f�l�����Z
				//
				if (i > 0 && j < (width - 1)) {
					n2 = 3 * ((i - 1) * width + (j + 1));
					valueB += input1.at<cv::Vec3b>(i, j)[0] * filter[2];
					valueG += input1.at<cv::Vec3b>(i, j)[1] * filter[2];
					valueR += input1.at<cv::Vec3b>(i, j)[2] * filter[2];
				}

				//
				// ���̉�f�l�����Z
				//
				if (j > 0) {
					n2 = 3 * (i * width + (j - 1));
					valueB += input1.at<cv::Vec3b>(i, j)[0] * filter[3];
					valueG += input1.at<cv::Vec3b>(i, j)[1] * filter[3];
					valueR += input1.at<cv::Vec3b>(i, j)[2] * filter[3];
				}

				//
				// ����ꏊ�̂̉�f�l�����Z
				//
				n2 = 3 * (i * width + j);
				valueB += input1.at<cv::Vec3b>(i, j)[0] * filter[4];
				valueG += input1.at<cv::Vec3b>(i, j)[1] * filter[4];
				valueR += input1.at<cv::Vec3b>(i, j)[2] * filter[4];

				//
				// �E�̉�f�l�����Z
				//
				if (j < (width - 1)) {
					n2 = 3 * (i * width + (j + 1));
					valueB += input1.at<cv::Vec3b>(i, j)[0] * filter[5];
					valueG += input1.at<cv::Vec3b>(i, j)[1] * filter[5];
					valueR += input1.at<cv::Vec3b>(i, j)[2] * filter[5];
				}

				//
				// �����̉�f�Ƃ̔�r
				//
				if (i < (height - 1) && j > 0) {
					n2 = 3 * ((i + 1) * width + (j - 1));
					valueB += input1.at<cv::Vec3b>(i, j)[0] * filter[6];
					valueG += input1.at<cv::Vec3b>(i, j)[1] * filter[6];
					valueR += input1.at<cv::Vec3b>(i, j)[2] * filter[6];
				}

				//
				// ���̉�f�Ƃ̔�r
				//
				if (i < (height - 1)) {
					n2 = 3 * ((i + 1) * width + j);
					valueB += input1.at<cv::Vec3b>(i, j)[0] * filter[7];
					valueG += input1.at<cv::Vec3b>(i, j)[1] * filter[7];
					valueR += input1.at<cv::Vec3b>(i, j)[2] * filter[7];
				}

				//
				// �E���̉�f�Ƃ̔�r
				//
				if (i < (height - 1) && j < (width - 1)) {
					n2 = 3 * ((i + 1) * width + (j + 1));
					valueB += input1.at<cv::Vec3b>(i, j)[0] * filter[8];
					valueG += input1.at<cv::Vec3b>(i, j)[1] * filter[8];
					valueR += input1.at<cv::Vec3b>(i, j)[2] * filter[8];
				}

				// valueR, valueG, valueB �̒l��0�`255�͈̔͂ɂ���
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