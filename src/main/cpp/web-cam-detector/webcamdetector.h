#ifndef WEBCAMDETECTOR_H
#define WEBCAMDETECTOR_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <boost/noncopyable.hpp>
#include <runtagdetector/detector/marker.h>

namespace nkdhny {

class WebcamDetector : boost::noncopyable
{
    typedef long (*MarkerAnalizer)(const cv::Mat&, int&);
public:
    WebcamDetector(unsigned camreId=0);
    WebcamDetector(MarkerAnalizer markerAnalizerFunction, unsigned cameraId=0);
    ~WebcamDetector();

    std::vector<nkdhny::Marker> apply();
    cv::Size getCaptureSize();
private:
    unsigned cameraId_;
    MarkerAnalizer markerAnalizerFunction_;
    cv::VideoCapture* capture_;
    cv::Size captureSize_;
};

}

#endif // WEBCAMDETECTOR_H
