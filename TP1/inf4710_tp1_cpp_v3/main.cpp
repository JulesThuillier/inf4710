
#include "tp1.hpp"

using ImagePathFlag = std::pair<std::string,int>; // first = image path, second = cv::imread flag

int main(int /*argc*/, char** /*argv*/) {
    try {
		std::cout << "Hello this is test" << std::endl;
		std::vector<uint8_t> datatest = { 0,0,1,0,1,0,2,1,0,2,1,0,2,1,2,4,0,1,0,1,0,2,1,0,0 };
		std::vector<LZ77Code> encodedData =  lz77_encode(datatest, 18, 9);
		for (int i = 0; i < encodedData.size(); i++) {
			std::cout << encodedData[i].to_string() << std::endl;
		}

		for (int i = 0; i < datatest.size(); i++) {
			std::cout << (int)datatest[i] << ", ";
		}
		std::cout << std::endl;
		std::vector<uint8_t> decodedDate = lz77_decode(encodedData, 18, 9);
		for (int i = 0; i < decodedDate.size(); i++) {
			std::cout << (int)decodedDate[i] << ", ";
		}
		std::cout << std::endl;
	
        // note: by default, imread always returns 3-ch images unless the cv::IMREAD_GRAYSCALE flag is set (here we hardcode it based on prior knowledge)
        const std::vector<ImagePathFlag> vsTestImages = {
            {"data/test1.png",cv::IMREAD_GRAYSCALE},
            {"data/test2.png",cv::IMREAD_GRAYSCALE},
            {"data/test3.png",cv::IMREAD_GRAYSCALE},
            {"data/test4.png",cv::IMREAD_COLOR},
            {"data/test5.png",cv::IMREAD_COLOR},
            {"data/test6.png",cv::IMREAD_COLOR},
            {"data/test7.png",cv::IMREAD_COLOR},
            {"data/test8.jpg",cv::IMREAD_COLOR},
            {"data/test9.bmp",cv::IMREAD_COLOR},
            {"data/test10.bmp",cv::IMREAD_COLOR},
        };

		std::cout << "image : " << vsTestImages.size() << std::endl;
        for(const ImagePathFlag& oImagePathFlag : vsTestImages) {
            cv::Mat oInputImg = cv::imread(oImagePathFlag.first,oImagePathFlag.second);
            if(oInputImg.empty())
                CV_Error_(-1,("Could not load image at '%s', check local paths",oImagePathFlag.first.c_str()));

            // ... @@@@ TODO (make sure decoding also provides the original image!)
			std::cout << "IMAGE :" << std::endl;
			std::vector<uint8_t> orig_img = format_signal(oInputImg);
			std::cout << "		Original img size : " << orig_img.size() << std::endl;
			std::vector<LZ77Code> encoded_img = lz77_encode(orig_img, 100, 50);
			std::cout << "		Encoded img size WARNING : " << encoded_img.size() << std::endl;
			std::cin;
			std::vector<uint8_t> decoded_img = lz77_decode(encoded_img, 100, 50);
			std::cout << "		Decoded img size : " << decoded_img.size() << std::endl;
			std::cin;
			std::vector<uint8_t> final_image = reformat_image(decoded_img, oInputImg.size());
			std::cout << "		Final img size : " << final_image.size() << std::endl;
            
        }
    }
    catch(const cv::Exception& e) {
        std::cerr << "Caught cv::Exceptions: " << e.what() << std::endl;
		std::cin;
    }
    catch(const std::runtime_error& e) {
        std::cerr << "Caught std::runtime_error: " << e.what() << std::endl;
		std::cin;
    }
    catch(...) {
        std::cerr << "Caught unhandled exception." << std::endl;
		std::cin;
    }
    return 0;
}
