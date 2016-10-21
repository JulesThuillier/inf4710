
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

				Y_ = 0.299*RGB.at<cv::Vec3b>(i, j)[0] + 0.587*RGB.at<cv::Vec3b>(i, j)[1] + 0.114*RGB.at<cv::Vec3b>(i, j)[2];
				Cr_ = 128 + 0.564*(RGB.at<cv::Vec3b>(i, j)[2] - Y_);
				Cb_ = 128 + 0.713*(RGB.at<cv::Vec3b>(i, j)[0] - Y_);

				// Clamping
				if (Y_ < 0) { Y_ = 0; } if (Cr_ < 0) { Cr_ = 0; } if (Cb_ < 0) { Cb_ = 0; }
				if (Y_ > 255) { Y_ = 255; } if (Cr_ > 255) { Cr_ = 255; } if (Cb_ > 255) { Cb_ = 255; }

				Y.at<cv::Vec3b>(i, j) = Y_;
				Cr.at<cv::Vec3b>(i, j) = Cr_;
				Cb.at<cv::Vec3b>(i, j) = Cb_;
			}
		}
	}

	// If subsample enabled, we create Cb and Cr matrix 4 times smaller 
	else {
		Cb.create(RGB.rows/2, RGB.cols/2);
		Cr.create(RGB.rows/2, RGB.cols/2);

		for (int i = 0; i<RGB.rows; i++)
		{
			for (int j = 0; j<RGB.cols; j++)
			{
				uchar Y_;

				Y_ = 0.299*RGB.at<cv::Vec3b>(i, j)[0] + 0.587*RGB.at<cv::Vec3b>(i, j)[1] + 0.114*RGB.at<cv::Vec3b>(i, j)[2];
				

				// Clamping
				if (Y_ < 0) { Y_ = 0; }
				if (Y_ > 255) { Y_ = 255; } 

				Y.at<cv::Vec3b>(floor(i), floor(j)) = Y_;

				// Calculte Cr and Cb only when needed (1/4 times) 
				if (i%2==0 && j%2==0) {
					uchar  Cr_, Cb_;

					Cr_ = 128 + 0.564*(RGB.at<cv::Vec3b>(i, j)[2] - Y_);
					Cb_ = 128 + 0.713*(RGB.at<cv::Vec3b>(i, j)[0] - Y_);

					if (Cr_ < 0) { Cr_ = 0; } if (Cb_ < 0) { Cb_ = 0; }
					if (Cr_ > 255) { Cr_ = 255; } if (Cb_ > 255) { Cb_ = 255; }

					Cr.at<cv::Vec3b>(i / 2, j / 2) = Cr_;
					Cb.at<cv::Vec3b>(i / 2, j / 2) = Cb_;
				}
			}
		}
	}
}
