<<<<<<< HEAD

#pragma once

#include "tp2.h"

// zigzag: returns a (NxN)-element 1D array created by zig-zagging through a NxN block
template<int nBlockSize=8, typename T=short>
inline std::array<T,nBlockSize*nBlockSize> zigzag(const cv::Mat_<T>& oBlock) {
	CV_Assert(!oBlock.empty() && oBlock.rows==oBlock.cols && oBlock.rows==nBlockSize);
    std::array<T,nBlockSize*nBlockSize> aZigzag;

    // @@@@ TODO

	int index = 0;
	for (int i = 0; i < aZigzag.size(); i++) {
		if (i % 2 == 0) {
			for (int x = i; x >= 0; x--) {
				// valid matrix index
				if ((x < nBlockSize) && (i - x < nBlockSize)) {
					aZigzag[index] = oBlock.at<T>(x,i - x);
					index++;
				}
			}
		}
		else {
			for (int x = 0; x <= i; x++) {
				if ((x < nBlockSize) && (i - x < nBlockSize)) {
					aZigzag[index] = oBlock.at<T>(x, i - x);
					index++;
				}
			}
		}
	}
	
	return aZigzag;
}
=======

#pragma once

#include "tp2.h"

// zigzag: returns a (NxN)-element 1D array created by zig-zagging through a NxN block
template<int nBlockSize=8, typename T=short>
inline std::array<T,nBlockSize*nBlockSize> zigzag(const cv::Mat_<T>& oBlock) {
	CV_Assert(!oBlock.empty() && oBlock.rows==oBlock.cols && oBlock.rows==nBlockSize);
    std::array<T,nBlockSize*nBlockSize> aZigzag;

    // @@@@ TODO
	
	return aZigzag;
}
>>>>>>> d1084ba4883325c73782719021fbdfa46b1063ca
