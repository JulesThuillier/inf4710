
#pragma once

#include "tp2.h"

// conv_ycbcr2rgb: converts an 8-bit-depth YCbCr image to RGB format considering optional 4:2:0 subsampling
inline void conv_ycbcr2rgb(const cv::Mat_<uchar>& Y, const cv::Mat_<uchar>& Cb, const cv::Mat_<uchar>& Cr, bool bSubsample, cv::Mat& RGB) {
    CV_Assert(!Y.empty() && Y.isContinuous() && !Cb.empty() && Cb.isContinuous() && !Cr.empty() && Cr.isContinuous());
    CV_Assert(!bSubsample || (Y.rows/2==Cb.rows && Y.rows/2==Cr.rows && Y.cols/2==Cb.cols && Y.cols/2==Cr.cols));
    CV_Assert(bSubsample || (Y.rows==Cb.rows && Y.rows==Cr.rows && Y.cols==Cb.cols && Y.cols==Cr.cols));
    RGB.create(Y.size(),CV_8UC3);

	if (!bSubsample) {
		for (int i = 0; i<RGB.rows; i++)
		{
			for (int j = 0; j<RGB.cols; j++)
			{
				uchar R, G, B;
				
				R = Y.at<uchar>(i, j) + 1.403*(Cr.at<uchar>(i, j) - 128);
				G = Y.at<uchar>(i, j) - 0.714*(Cr.at<uchar>(i, j) - 128) - 0.344*(Cb.at<uchar>(i, j) - 128);
				B = Y.at<uchar>(i, j) + 1.773*(Cb.at<uchar>(i, j) - 128);

				// Clamping
				if (R < 0) { R = 0; } if (G < 0) { G = 0; } if (B < 0) { B = 0; }
				if (R > 255) { R = 255; } if (G > 255) { G = 255; } if (B > 255) { B = 255; }

				RGB.at<cv::Vec3b>(i, j)[0] = R;
				RGB.at<cv::Vec3b>(i, j)[1] = G;
				RGB.at<cv::Vec3b>(i, j)[2] = B;
			}
		}
	}
	else {
		for (int i = 0; i<RGB.rows; i++)
		{
			for (int j = 0; j<RGB.cols; j++)
			{
				uchar R, G, B;

				R = Y.at<uchar>(i, j) + 1.403*(Cr.at<uchar>(floor(i / 2), floor(j / 2)) - 128);
				G = Y.at<uchar>(i, j) - 0.714*(Cr.at<uchar>(floor(i / 2), floor(j / 2)) - 128) - 0.344*(Cb.at<uchar>(floor(i / 2), floor(j / 2)) - 128);
				B = Y.at<uchar>(i, j) + 1.773*(Cb.at<uchar>(floor(i / 2), floor(j / 2)) - 128);

				// Clamping
				if (R < 0) { R = 0; } if (G < 0) { G = 0; } if (B < 0) { B = 0; }
				if (R > 255) { R = 255; } if (G > 255) { G = 255; } if (B > 255) { B = 255; }

				RGB.at<cv::Vec3b>(i, j)[0] = R;
				RGB.at<cv::Vec3b>(i, j)[1] = G;
				RGB.at<cv::Vec3b>(i, j)[2] = B;
			}
		}
	}

    // @@@@ TODO

}
