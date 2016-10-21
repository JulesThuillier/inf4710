
#pragma once

#include "tp2.h"

// dct: computes the discrete cosinus tranform of a matrix
template<typename Tin=uchar,typename Tout=float>
inline cv::Mat_<Tout> dct(const cv::Mat_<Tin>& oBlock) {
    CV_Assert(!oBlock.empty() && oBlock.rows==oBlock.cols && (oBlock.rows%2)==0 && oBlock.isContinuous());
    cv::Mat_<Tout> oOutput(oBlock.size());

    // @@@@ TODO
	const float PI = 3.1415927;
	int index;
	float cu, cv, F, cos1, cos2, sum, sums;

	for (int u = 0; u < oBlock.rows; u++) {
		for (int v = 0; v < oBlock.cols; v++) {

			//Initialisation
			cu = 0;
			cv = 0;

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

			//Calcul des sommations
			sums = 0;
			for (int i = 1; i <= oBlock.rows; i++)
			{
				for (int j = 1; j <= oBlock.cols; j++)
				{
					index = i * oBlock.cols + j;

					F = (int)oBlock.data[index];
					float arg1 = cos((PI*(2 * (i - 1) + 1)*(u - 1)) / (2 * oBlock.rows));
					float arg2 = cos((PI*(2 * (j - 1) + 1)*(v - 1)) / (2 * oBlock.cols));

					sum = F * arg1 * arg2;
					sums += sum;
				}
			}

			//Calcul du resultat
			index = u * oBlock.cols + v;
			oOutput.data[index] = cu*cv*sums;
		}
	}	

    return oOutput;


}
