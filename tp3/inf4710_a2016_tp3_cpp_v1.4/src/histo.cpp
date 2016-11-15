
#include "utils.hpp"

cv::Mat tp3::histo(const cv::Mat& oImage, size_t N) {
	CV_Assert(!oImage.empty() && oImage.type() == CV_8UC3 && oImage.isContinuous());
	CV_Assert(N > 1 && N <= 256);
	cv::Mat oHist(3, (int)N, CV_32FC1, cv::Scalar_<float>(0.0f));

	for (int i = 0; i < oImage.rows; i++)
		for (int j = 0; j < oImage.cols; j++)
		{
			Vec3b intensity = image.at<Vec3b>(Point(j, i));
			for (int k = 0; k < oImage.channels(); ++k) {
				oHist.at<float>(k, channels[k]) += (1.0f / (oImage.cols * oImage.rows));
			}
		}
	}	
	return oHist;
}