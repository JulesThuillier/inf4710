
#pragma once

#include "tp2.h"

// dct_inv: computes the inverse discrete cosinus tranform of a matrix
template<typename Tin=float,typename Tout=uchar>
inline cv::Mat_<Tout> dct_inv(const cv::Mat_<Tin>& oBlock) {
    CV_Assert(!oBlock.empty() && oBlock.rows==oBlock.cols && (oBlock.rows%2)==0 && oBlock.isContinuous());
    cv::Mat_<Tout> oOutput(oBlock.size());

    // @@@@ TODO
	const float PI = 3.1415927;
	int index;
	float cu, cv, C, cos1, cos2, sum, sums, arg1, arg2;
	float rac1 = (float)sqrt((float)1 / (float)oBlock.rows);
	float rac2 = (float)sqrt((float)2 / (float)oBlock.rows);

	for (int i = 0; i < oBlock.rows; i++) {
		for (int j = 0; j < oBlock.cols; j++) {

			//Initialisation
			cu = 0;
			cv = 0;
			
			//Calcul des sommations
			sums = 0;
			for (int u = 0; u < oBlock.rows; u++)
			{
				for (int v = 0; v < oBlock.cols; v++)
				{
					//Calcul de c(u) et c(v)
					if (u == 0) {
						cu = rac1;
					}
					else {
						cu = rac2;
					}

					if (v == 0) {
						cv = rac1;
					}
					else {
						cv = rac2;
					}


				//	index = u * oBlock.cols + v;

					C = oBlock.at<uchar>(u,v);
					arg1 = cos((PI*(2 * i + 1) * u) / (2 * oBlock.cols));
					arg2 = cos((PI*(2 * j + 1) * v) / (2 * oBlock.cols));

					sum = cu * cv * C * arg1 * arg2;
					sums += sum;
				}
			}

			//Calcul du resultat
		//	index = i * oBlock.cols + j;
			std::cout << "sums: " << sums << std::endl;
			oOutput.at<uchar>(i,j) = (uchar)(sums);
			
		}
	}
	std::cout << "Calculated Invert DCT: " << std::endl << oOutput << std::endl;
	cv::Mat fimage;
	oBlock.convertTo(fimage, CV_32F, 1.0 / 255);
	cv::Mat dimage;
	cv::dct(fimage, dimage, cv::DCT_INVERSE);
	std::cout << "OpenCV invert: " << std::endl << dimage << std::endl;
	cv::Mat image;
	dimage.convertTo(image, CV_8U);
	
	std::cout << "OpenCV invert 2: " << std::endl << image << std::endl;
    return oOutput;
}
