
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
	float rac1 = (float)sqrt((float)1 / (float)oBlock.rows);
	float rac2 = (float)sqrt((float)2 / (float)oBlock.rows);
	
<<<<<<< HEAD

	for (int u = 0; u < oBlock.rows; u++) {
		for (int v = 0; v < oBlock.cols; v++) {

			//Initialisation
			cu = 0;
			cv = 0;

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

			//Calcul des sommations
			sums = 0;
			for (int i = 0; i < oBlock.rows; i++)
			{
				for (int j = 0; j < oBlock.cols; j++)
				{

					F = (int)oBlock.at<Tin>(i,j);
					float arg1 = cos((PI*(2 * i + 1)*u) / (2 * oBlock.rows));
					float arg2 = cos((PI*(2 * j + 1)*v) / (2 * oBlock.cols));

					sum = F * arg1 * arg2;
					sums += sum;
				}
			}

			//Calcul du resultat
			//index = u * oBlock.cols + v;
			oOutput.at<Tout>(u,v) = (Tout)cu*cv*sums;
		}
	}	
=======
>>>>>>> 9a06530d2f4d942675d8ed8d8b1f7bef5e14c4b2

	for (int u = 0; u < oBlock.rows; u++) {
		for (int v = 0; v < oBlock.cols; v++) {

			//Initialisation
			cu = 0;
			cv = 0;

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

			//Calcul des sommations
			sums = 0;
			for (int i = 0; i < oBlock.rows; i++)
			{
				for (int j = 0; j < oBlock.cols; j++)
				{

					F = (int)oBlock.at<Tin>(i,j);
					float arg1 = cos((PI*(2 * i + 1)*u) / (2 * oBlock.rows));
					float arg2 = cos((PI*(2 * j + 1)*v) / (2 * oBlock.cols));

					sum = F * arg1 * arg2;
					sums += sum;
				}
			}

			//Calcul du resultat
			//index = u * oBlock.cols + v;
			oOutput.at<Tout>(u,v) = (Tout)cu*cv*sums;
		}
	}	
	//cv::Mat_<Tout> opencvdct;
	//cv::Mat opencvdct = cv::Mat::zeros(oBlock.rows, oBlock.cols, CV_32F);
	//cv::dct(oBlock, opencvdct);

/*	cv::Mat fimage;
	oBlock.convertTo(fimage, CV_32F, 1.0 / 255);
	cv::Mat dimage;
	cv::dct(fimage, dimage);
	std::cout << "Input: " << std::endl << oBlock << std::endl;
	std::cout << "Calculated DCT: " << std::endl << oOutput << std::endl;
	std::cout << "OpenCV DCT: " << std::endl << dimage << std::endl;*/
    return oOutput;


}
