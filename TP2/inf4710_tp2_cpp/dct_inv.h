<<<<<<< HEAD

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
	float cu, cv, C, cos1, cos2, arg1, arg2, sum, sums;
	float rac1 =(float)sqrt((float)1/ (float)oBlock.rows);
	float rac2 = (float)sqrt((float)2/(float)oBlock.rows);

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
					if (u == 0 || v == 0) {
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

					C = oBlock.at<Tin>(u,v);
					arg1 = cos((PI*(2 * i + 1) * u) / (2 * oBlock.cols));
					arg2 = cos((PI*(2 * j + 1) * v) / (2 * oBlock.cols));

					sum = cu * cv * C * arg1 * arg2;
					sums += sum;
				}
			}

			oOutput.at<Tout>(i,j) = (Tout)(sums);
			
		}
	}
    return oOutput;
}
=======

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
	float cu, cv, C, cos1, cos2, sum, sums;

	for (int i = 0; i < oBlock.rows; i++) {
		for (int j = 0; j < oBlock.cols; j++) {

			//Initialisation
			cu = 0;
			cv = 0;
			
			//Calcul des sommations
			sums = 0;
			for (int u = 1; u <= oBlock.rows; u++)
			{
				for (int v = 1; v <= oBlock.cols; v++)
				{
					//Calcul de c(u) et c(v)
					if (u == 1) {
						cu = (float)sqrt((float)1 / (float)oBlock.rows);
					}
					else {
						cu = (float)sqrt((float)2 / (float)oBlock.rows);
					}

					if (v == 1) {
						cv = (float)sqrt((float)1 / (float)oBlock.cols);
					}
					else {
						cv = (float)sqrt((float)2 / (float)oBlock.cols);
					}


					index = u * oBlock.cols + v;

					C = (int)oBlock.data[index];
					arg1 = cos((PI*(2 * (i - 1) + 1)*(u - 1)) / (2 * oBlock.rows));
					arg2 = cos((PI*(2 * (j - 1) + 1)*(v - 1)) / (2 * oBlock.cols));

					sum = cu * cv * C * arg1 * arg2;
					sums += sum;
				}
			}

			//Calcul du resultat
			index = i * oBlock.cols + j;
			oOutput.data[index] = (uchar)(sums);
		}
	}


    return oOutput;
}
>>>>>>> d1084ba4883325c73782719021fbdfa46b1063ca
