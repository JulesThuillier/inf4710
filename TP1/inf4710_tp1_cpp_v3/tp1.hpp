
//
// INF4710 TP1 A2016 v1.0
// Auteurs:
//     @@@@@@@@@@@@@@@@@@@@@@@
//     @@@@@@@@@@@@@@@@@@@@@@@
//

#pragma once

#include <exception>
#include <iostream>
#include <string>
#include <deque>
#include <opencv2/opencv.hpp>

struct LZ77Code {
    uint8_t nIdx; // in-dictionary index offset for first match
    uint8_t nLength; // total consecutive match count
    uint8_t nNextSymbol; // next unmatched symbol
    inline std::string to_string() const {
        return std::string("(")+std::to_string(nIdx)+","+std::to_string(nLength)+",'"+std::to_string(nNextSymbol)+"'),";
    }
};

inline std::vector<LZ77Code> lz77_encode(const std::vector<uint8_t>& vSignal, size_t N, size_t n1) {
    CV_Assert(N>0 && n1>0 && N>n1 && n1<UCHAR_MAX && !vSignal.empty());
    std::vector<LZ77Code> vCode;
    // ... @@@@@ TODO (encode vSignal using lz77, and put triplets in vCode)

	// Initialize Searching Window with 0
	std::deque<uint8_t> window(N,0);
	int signalIndex = 0;

	// Fill in right windows with Datas from vSignal
	for (int i = 0; i < N - n1; i++) {
		window.pop_front();
		window.push_back(vSignal[signalIndex]);
		signalIndex++;
	}

	while (signalIndex < vSignal.size() + (N - n1)) {
		LZ77Code code = {};
		code.nLength = 1;

		// Iterate through left window to find first match
		bool found = false;
		for (int i = n1 - 1; i > 0; i--) {
			if (window[i] == window[n1]) {
				code.nIdx = n1 - i;
				found = true;
				break;
			}
		}
		if (found) {
			// Find Length
			for (int i = 1; i < N - n1 && i < (N - n1) - (signalIndex - vSignal.size()); i++) { // Search within right windows max length, stop before end of vSignal
				if (window[n1 - code.nIdx + i] == window[n1 + i]) {
					code.nLength++;
				}
				// Serie if different from here, max length found
				else {
					code.nNextSymbol = window[n1 + i];
					break;
				}
				//handle case when it matches until the end of the right window
				if (i + 1 == N - n1) {
					code.nNextSymbol = vSignal.back();
				}
			}
		}

		// Symbol not fond in window
		else {
			code.nLength = 0;
			code.nIdx = 0;
			code.nNextSymbol = window[n1];
		}

		// Push data in window to the left and append new data from signal
		for (int i = 0; i < code.nLength + 1 && signalIndex < vSignal.size() + (N - n1); i++) {
			window.pop_front();
			// There is still data in vSignal
			if (signalIndex < vSignal.size()) {
				window.push_back(vSignal[signalIndex]);
			}
			// No more data in vSignal, but still need to empty the right windows
			else {
				window.push_back(0);
			}
			signalIndex++;
		}

		vCode.push_back(code);
	}
    return vCode;
}

inline std::vector<uint8_t> lz77_decode(const std::vector<LZ77Code>& vCode, size_t N, size_t n1) {
    CV_Assert(N>0 && n1>0 && N>n1 && n1<UCHAR_MAX && !vCode.empty());
    std::vector<uint8_t> vSignal;
    // ... @@@@@ TODO (decode vCode triplets using lz77, and put original values in vSignal)
	
	std::vector<uint8_t> dict(n1,0);
	// Iterate over vCode
	for (int j = 0; j < vCode.size(); j++) {
		uint8_t length = vCode[j].nLength;

		// Getting the serie of symbols
		std::vector<uint8_t> serie;
		for (int i = 0; i < length && i < vCode[j].nIdx; i++) {
			serie.push_back(dict[(dict.size() - vCode[j].nIdx) + i]);
		}


		// Pushing the serie, repeating for the all length required 
		for (int i = 0; i < length; i++) {
			dict.push_back(serie[i%serie.size()]);
			vSignal.push_back(serie[i%serie.size()]);
		}

		// Adding next symbol at the end
		dict.push_back(vCode[j].nNextSymbol);
		vSignal.push_back(vCode[j].nNextSymbol);
	}
    return vSignal;
}

inline std::vector<uint8_t> format_signal(const cv::Mat& oInputImage) {
    CV_Assert(!oInputImage.empty() && oInputImage.isContinuous() && (oInputImage.type()==CV_8UC1 || oInputImage.type()==CV_8UC3));
    std::vector<uint8_t> vSignal;
    // ... @@@@@ TODO (put oInputImage data in vSignal in correct order/format)

	// B&W Image
	if (oInputImage.type() == CV_8UC1) {
		vSignal.assign(oInputImage.data, oInputImage.data + oInputImage.cols*oInputImage.rows);
	}

	//RGB Image
	else if (oInputImage.type() == CV_8UC3) {
		cv::Mat BGR_3[3];
		cv::split(oInputImage, BGR_3);
		vSignal.assign(BGR_3[0].data, BGR_3[0].data + BGR_3[0].cols*BGR_3[0].rows);
		vSignal.insert(vSignal.end(), BGR_3[1].data, BGR_3[1].data + BGR_3[1].cols*BGR_3[1].rows);
		vSignal.insert(vSignal.end()
			, BGR_3[2].data, BGR_3[2].data + BGR_3[2].cols*BGR_3[2].rows);
	}

    return vSignal;
}

inline cv::Mat reformat_image(const std::vector<uint8_t>& vSignal, const cv::Size& oOrigImageSize) {
    CV_Assert(!vSignal.empty() && oOrigImageSize.area()>0 && (oOrigImageSize.area()==vSignal.size() || oOrigImageSize.area()*3==vSignal.size())); // output can only be 1-channel (CV_8UC1) or 3-channel (CV_8UC3)
    if(oOrigImageSize.area()==vSignal.size()) // if the image is single-channel (CV_8UC1), reassemble inline as cv::Mat data is row-major
        return cv::Mat(oOrigImageSize,CV_8UC1,(void*)vSignal.data()).clone();
    std::vector<cv::Mat> voChannels(3); // otherwise, use cv::merge to reinterlace individual CV_8UC1 matrices into a CV_8UC3 one
    for(size_t c=0; c<3; ++c)
        voChannels[c] = cv::Mat(oOrigImageSize,CV_8UC1,(void*)(vSignal.data()+c*oOrigImageSize.area())); // no need for a clone here, we will not modify the original data
    cv::Mat oOrigImage; // will be created/sized automatically by cv::merge
    cv::merge(voChannels,oOrigImage);
    return oOrigImage;
}
