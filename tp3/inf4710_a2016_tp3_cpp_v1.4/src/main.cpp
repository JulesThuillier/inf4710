
// INF4710 A2016 TP3 v1.4

#include "utils.hpp"

int main(int /*argc*/, char** /*argv*/) {
    try {
        cv::VideoCapture oCap("../data/TP3_video.avi");
        CV_Assert(oCap.isOpened());
        for(int i=0; i<(int)oCap.get(cv::CAP_PROP_FRAME_COUNT); ++i) {
            cv::Mat oImg;
            oCap >> oImg;
            cv::imshow("oImg",oImg);
            cv::waitKey(1);
            // ... @@@@ TODO
        }
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
    return 0;
}
