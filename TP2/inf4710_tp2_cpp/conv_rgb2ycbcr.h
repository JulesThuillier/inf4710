
#pragma once

#include "tp2.h"

// conv_rgb2ycbcr: converts an 8-bit-depth RGB image to Y'CbCr format using optional 4:2:0 subsampling
inline void conv_rgb2ycbcr(const cv::Mat& RGB, bool bSubsample, cv::Mat_<uchar>& Y, cv::Mat_<uchar>& Cb, cv::Mat_<uchar>& Cr) {
    CV_Assert(!RGB.empty() && RGB.type()==CV_8UC3 && RGB.isContinuous());
    Y.create(RGB.rows,RGB.cols);

    // @@@@ TODO
	if (!bSubsample) {
		Cb.create(RGB.rows, RGB.cols);
		Cr.create(RGB.rows, RGB.cols);

		for (int i = 0; i<RGB.rows; i++)
		{
			for (int j = 0; j<RGB.cols; j++)
			{
				uchar Y_, Cr_, Cb_;

				Y_ = cv::saturate_cast<uchar>(0.299*RGB.at<cv::Vec3b>(i, j)[0] + 0.587*RGB.at<cv::Vec3b>(i, j)[1] + 0.114*RGB.at<cv::Vec3b>(i, j)[2]);
				Cb_ = cv::saturate_cast<uchar>(128 + 0.564*(RGB.at<cv::Vec3b>(i, j)[2] - Y_));
				Cr_ = cv::saturate_cast<uchar>(128 + 0.713*(RGB.at<cv::Vec3b>(i, j)[0] - Y_));

				// Clamping
				Y.at<uchar>(i, j) = Y_;
				Cr.at<uchar>(i, j) = Cr_;
				Cb.at<uchar>(i, j) = Cb_;
			}
		}
	}
	else {
		Cb.create(RGB.rows/2, RGB.cols/2);
		Cr.create(RGB.rows/2, RGB.cols/2);

		for (int i = 0; i<RGB.rows; i++)
		{
			for (int j = 0; j<RGB.cols; j++)
			{
				uchar Y_, Cr_, Cb_;

				Y_ = cv::saturate_cast<uchar>(0.299*RGB.at<cv::Vec3b>(i, j)[0] + 0.587*RGB.at<cv::Vec3b>(i, j)[1] + 0.114*RGB.at<cv::Vec3b>(i, j)[2]);
				Cb_ = cv::saturate_cast<uchar>(128 + 0.564*(RGB.at<cv::Vec3b>(i, j)[2] - Y_));
				Cr_ = cv::saturate_cast<uchar>(128 + 0.713*(RGB.at<cv::Vec3b>(i, j)[0] - Y_));

				// Clamping
				Y.at<uchar>(i, j) = Y_;
				if (i%2==0 && j%2==0) {
					Cr.at<uchar>(floor(i / 2), floor(j / 2)) = Cr_;
					Cb.at<uchar>(floor(i / 2), floor(j / 2)) = Cb_;
				}
			}
		} 
	} 
}
