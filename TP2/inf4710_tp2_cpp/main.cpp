
// INF4710 A2016 TP2 v1

#include "tp2.h"

// one function per header to simplify grading (bad habit though)
#include "conv_rgb2ycbcr.h"
#include "conv_ycbcr2rgb.h"
#include "dct.h"
#include "dct_inv.h"
#include "decoup.h"
#include "decoup_inv.h"
#include "huff.h"
#include "huff_inv.h"
#include "quantif.h"
#include "quantif_inv.h"
#include "zigzag.h"
#include "zigzag_inv.h"

#define USE_SUBSAMPLING 0
#define USE_QUANT_QUALITY 90

int main(int /*argc*/, char** /*argv*/) {
    try {
        const std::vector<std::string> vsTestImagePaths = {
            {"data/airplane.png"},
            {"data/baboon.png"},
            {"data/cameraman.tif"},
            {"data/lena.png"},
            {"data/logo.tif"},
            {"data/logo_noise.tif"},
            {"data/peppers.png"},
        };
        for(const std::string& sTestImagePath : vsTestImagePaths) {
            const cv::Mat oInput = cv::imread(sTestImagePath);
            if(oInput.empty() || oInput.type()!=CV_8UC3)
                CV_Error_(-1,("Could not load image at '%s', check local paths",sTestImagePath.c_str()));
			
			// COMPRESSION
			cv::Mat_<uchar> Y, Cb, Cr;
			conv_rgb2ycbcr(oInput, USE_SUBSAMPLING, Y, Cb, Cr);
			const std::vector<cv::Mat_<uchar>> vBlocks_Y = decoup(Y);
			const std::vector<cv::Mat_<uchar>> vBlocks_Cb = decoup(Cb);
			const std::vector<cv::Mat_<uchar>> vBlocks_Cr = decoup(Cr);
			std::vector<cv::Mat_<uchar>> vBlocks;
			vBlocks.insert(vBlocks.end(), vBlocks_Y.begin(), vBlocks_Y.end());
			vBlocks.insert(vBlocks.end(), vBlocks_Cb.begin(), vBlocks_Cb.end());
			vBlocks.insert(vBlocks.end(), vBlocks_Cr.begin(), vBlocks_Cr.end());
			std::vector<cv::Mat_<float>> vDCTBlocks(vBlocks.size());
			for (size_t b = 0; b<vBlocks.size(); ++b)
				vDCTBlocks[b] = dct(vBlocks[b]);
			std::vector<cv::Mat_<short>> vQuantifDCTBlocks(vDCTBlocks.size());
			for (size_t b = 0; b<vDCTBlocks.size(); ++b)
				vQuantifDCTBlocks[b] = quantif(vDCTBlocks[b], USE_QUANT_QUALITY);
			std::vector<std::array<short, 8 * 8>> vInlinedBlocks(vQuantifDCTBlocks.size());
			for (size_t b = 0; b<vQuantifDCTBlocks.size(); ++b)
				vInlinedBlocks[b] = zigzag(vQuantifDCTBlocks[b]);
			const HuffOutput<short> oCode = huff(vInlinedBlocks);

<<<<<<< HEAD
			int inputSize = oInput.rows* oInput.cols * 3;
			// On prend en compte la taille de la map (first et second) ainsi que le vecteur de bool. 
			float outputSize = (oCode.string.size()*sizeof(oCode.string[0]) + oCode.map.size()*(sizeof(oCode.map.begin()->first) + sizeof(oCode.map.begin()->second))) / 8;

			float compression = 1 - outputSize / inputSize;
			std::cout << sTestImagePath.c_str() <<  ": Taux de compression " << compression <<  " taille d'entr�e: " << inputSize  << " taille de sortie: " << outputSize << std::endl;


			// NOTE A L'EXAMINATEUR: Il faut commenter la partie de Huffman pour builder la solution car nous n'avons pas reussi a faire l'inverse.

			// DECOMPRESSION
			const std::vector<std::array<short, 8 * 8>> vInlinedBlocks_decompr = huff_inv<8 * 8>(oCode); 
			std::vector<cv::Mat_<short>> vQuantifDCTBlocks_decompr(vInlinedBlocks_decompr.size());
			for (size_t b = 0; b<vInlinedBlocks_decompr.size(); ++b)
				vQuantifDCTBlocks_decompr[b] = zigzag_inv(vInlinedBlocks[b]); 
			std::vector<cv::Mat_<float>> vDCTBlocks_decompr(vQuantifDCTBlocks_decompr.size());
			for (size_t b = 0; b<vQuantifDCTBlocks_decompr.size(); ++b)
				vDCTBlocks_decompr[b] = quantif_inv(vQuantifDCTBlocks_decompr[b], USE_QUANT_QUALITY); 
			std::vector<cv::Mat_<uchar>> vBlocks_decompr(vDCTBlocks.size());
			for (size_t b = 0; b<vDCTBlocks.size(); ++b)
				vBlocks_decompr[b] = dct_inv(vDCTBlocks[b]);
			const std::vector<cv::Mat_<uchar>> vBlocks_Y_decompr(vBlocks_decompr.begin(), vBlocks_decompr.begin() + vBlocks_Y.size());
			const std::vector<cv::Mat_<uchar>> vBlocks_Cb_decompr(vBlocks_decompr.begin() + vBlocks_Y.size(), vBlocks_decompr.begin() + vBlocks_Y.size() + vBlocks_Cb.size());
			const std::vector<cv::Mat_<uchar>> vBlocks_Cr_decompr(vBlocks_decompr.begin() + vBlocks_Y.size() + vBlocks_Cb.size(), vBlocks_decompr.end());
			const cv::Mat_<uchar> Y_decompr = decoup_inv(vBlocks_Y_decompr, Y.size());
			const cv::Mat_<uchar> Cb_decompr = decoup_inv(vBlocks_Cb_decompr, Cb.size());
			const cv::Mat_<uchar> Cr_decompr = decoup_inv(vBlocks_Cr_decompr, Cr.size());
			cv::Mat oInput_decompr;
			conv_ycbcr2rgb(Y_decompr, Cb_decompr, Cr_decompr, USE_SUBSAMPLING, oInput_decompr);

			cv::Mat oDisplay;
			cv::hconcat(oInput, oInput_decompr, oDisplay);
			cv::Mat oDiff;
			cv::absdiff(oInput, oInput_decompr, oDiff);
			cv::hconcat(oDisplay, oDiff, oDisplay);
			cv::imshow(sTestImagePath.substr(sTestImagePath.find_last_of("/\\") + 1), oDisplay);
			cv::waitKey(1);
=======
            // COMPRESSION
            cv::Mat_<uchar> Y,Cb,Cr;
			  conv_rgb2ycbcr(oInput,USE_SUBSAMPLING,Y,Cb,Cr);
		/*	      const std::vector<cv::Mat_<uchar>> vBlocks_Y = decoup(Y);
            const std::vector<cv::Mat_<uchar>> vBlocks_Cb = decoup(Cb);
            const std::vector<cv::Mat_<uchar>> vBlocks_Cr = decoup(Cr);
            std::vector<cv::Mat_<uchar>> vBlocks;
			     vBlocks.insert(vBlocks.end(),vBlocks_Y.begin(),vBlocks_Y.end());
            vBlocks.insert(vBlocks.end(),vBlocks_Cb.begin(),vBlocks_Cb.end());
            vBlocks.insert(vBlocks.end(),vBlocks_Cr.begin(),vBlocks_Cr.end());
            std::vector<cv::Mat_<float>> vDCTBlocks(vBlocks.size());
            for(size_t b=0; b<vBlocks.size(); ++b)
                vDCTBlocks[b] = dct(vBlocks[b]);
			std::cout << "Image " << sTestImagePath.c_str() << " done" << std::endl; */
      /*   std::vector<cv::Mat_<short>> vQuantifDCTBlocks(vDCTBlocks.size());
            for(size_t b=0; b<vDCTBlocks.size(); ++b)
                vQuantifDCTBlocks[b] = quantif(vDCTBlocks[b],USE_QUANT_QUALITY);
            std::vector<std::array<short,8*8>> vInlinedBlocks(vQuantifDCTBlocks.size());
            for(size_t b=0; b<vQuantifDCTBlocks.size(); ++b)
                vInlinedBlocks[b] = zigzag(vQuantifDCTBlocks[b]);
            const HuffOutput<short> oCode = huff(vInlinedBlocks);

            // @@@@ TODO: check compression rate here...
*/
            // DECOMPRESSION
         /*   const std::vector<std::array<short,8*8>> vInlinedBlocks_decompr = huff_inv<8*8>(oCode);
            std::vector<cv::Mat_<short>> vQuantifDCTBlocks_decompr(vInlinedBlocks_decompr.size());
            for(size_t b=0; b<vInlinedBlocks_decompr.size(); ++b)
                vQuantifDCTBlocks_decompr[b] = zigzag_inv(vInlinedBlocks_decompr[b]);
            std::vector<cv::Mat_<float>> vDCTBlocks_decompr(vQuantifDCTBlocks_decompr.size());
            for(size_t b=0; b<vQuantifDCTBlocks_decompr.size(); ++b)
                vDCTBlocks_decompr[b] = quantif_inv(vQuantifDCTBlocks_decompr[b],USE_QUANT_QUALITY); */
       /*    std::vector<cv::Mat_<uchar>> vBlocks_decompr(vDCTBlocks.size());
            for(size_t b=0; b<vDCTBlocks.size(); ++b)
                vBlocks_decompr[b] = dct_inv(vDCTBlocks[b]);
            const std::vector<cv::Mat_<uchar>> vBlocks_Y_decompr(vBlocks_decompr.begin(),vBlocks_decompr.begin()+vBlocks_Y.size());
            const std::vector<cv::Mat_<uchar>> vBlocks_Cb_decompr(vBlocks_decompr.begin()+vBlocks_Y.size(),vBlocks_decompr.begin()+vBlocks_Y.size()+vBlocks_Cb.size());
            const std::vector<cv::Mat_<uchar>> vBlocks_Cr_decompr(vBlocks_decompr.begin()+vBlocks_Y.size()+vBlocks_Cb.size(),vBlocks_decompr.end());
            const cv::Mat_<uchar> Y_decompr = decoup_inv(vBlocks_Y_decompr,Y.size());
            const cv::Mat_<uchar> Cb_decompr = decoup_inv(vBlocks_Cb_decompr,Cb.size());
            const cv::Mat_<uchar> Cr_decompr = decoup_inv(vBlocks_Cr_decompr,Cr.size()); */
            cv::Mat oInput_decompr;
           // conv_ycbcr2rgb(Y_decompr,Cb_decompr,Cr_decompr,USE_SUBSAMPLING,oInput_decompr);
			conv_ycbcr2rgb(Y, Cb, Cr, USE_SUBSAMPLING, oInput_decompr);

            cv::Mat oDisplay;
            cv::hconcat(oInput,oInput_decompr,oDisplay);
            cv::Mat oDiff;
            cv::absdiff(oInput,oInput_decompr,oDiff);
            cv::hconcat(oDisplay,oDiff,oDisplay);
            cv::imshow(sTestImagePath.substr(sTestImagePath.find_last_of("/\\")+1),oDisplay);
            cv::waitKey(1); 
>>>>>>> 9a06530d2f4d942675d8ed8d8b1f7bef5e14c4b2
        }
        std::cout << "all done; press any key on a window to quit..." << std::endl;
		std::cin.get();
        cv::waitKey(0);
        return 0;
    }
    catch(const cv::Exception& e) {
        std::cerr << "Caught cv::Exceptions: " << e.what() << std::endl;
    }
    catch(const std::runtime_error& e) {
        std::cerr << "Caught std::runtime_error: " << e.what() << std::endl;
    }
    catch(...) {
        std::cerr << "Caught unhandled exception." << std::endl;
    }
    return 1;
}
