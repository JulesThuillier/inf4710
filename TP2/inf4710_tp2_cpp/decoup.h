
#pragma once

#include "tp2.h"

// decoup: reformats a 2D image (i.e. always single channel) to a block array
template<size_t nBlockSize=8, typename T=uchar>
inline std::vector<cv::Mat_<T>> decoup(const cv::Mat_<T>& oImage) {
    CV_Assert(!oImage.empty() && (oImage.rows%nBlockSize)==0 && (oImage.cols%nBlockSize)==0 && oImage.isContinuous());
    std::vector<cv::Mat_<T>> vOutput;

    // @@@@ TODO
	cv::Mat_<T>& temp;
	for (int l = 0; l < oImage.rows; l += 8;)
	{
		for (int k = 0; k < oImage.cols; k += 8;)
		{
			for (int j = 0; j < 8; j++)
			{
				for (int i = 0; i < 8; i++)
				{
					temp[i][j] = oImage[k + i][l + j];
				}
			}
			vOutput.push_back(temp);
		}
	}
	

    return vOutput;
}
