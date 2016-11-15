
#include "utils.hpp"

cv::Mat tp3::convo(const cv::Mat& oImage, const cv::Mat_<float>& oKernel) {
    CV_Assert(!oImage.empty() && oImage.type()==CV_8UC3 && oImage.isContinuous());
    CV_Assert(!oKernel.empty() && oKernel.cols==oKernel.rows && oKernel.isContinuous());
    CV_Assert(oImage.cols>oKernel.cols && oImage.rows>oKernel.rows);
    cv::Mat oResult(oImage.size(),CV_32FC3);

    int kCenterX = oKernel.cols/2.0;
	int kCenterY = oKernel.rows/2.0;
	int ii, jj, mm, nn;
	float out;

    for (int i = 0; i < oImage.rows; ++i) {
		for (int j = 0; j < oImage.cols; ++j) {
			for (int k = 0; k < oImage.channels(); ++k) {

				out = 0.0f;
				for (int m = 0; m < oKernel.rows; ++m) {

					mm = oKernel.rows - 1 - m; // row index of flipped kernel

					for (int n = 0; n < oKernel.cols; ++n) {\

						nn = oKernel.cols - 1 - n;  // column index of flipped kernel

						// index of input signal, used for checking boundary
		                ii = i + (m - kCenterY);
		                jj = j + (n - kCenterX);

		                // ignore input samples which are out of bound
						if(ii >= 0 && ii < rows && jj >= 0 && jj < cols){
							out += oImage.at<uchar>(ii, jj, k)*oKernel.at<float>(m + floor(kCenterY), n + floor(kCenterX));
						}

					}
				}
				oResult.at<float>(i,j,k) = out;
			}
		}
	}

    return oResult;
}