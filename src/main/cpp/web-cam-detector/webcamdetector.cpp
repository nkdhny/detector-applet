#include "webcamdetector.h"
#include <runtagdetector/code/hamming_secded_code.h>
#include <runtagdetector/marker/dense_marker.h>
#include <runtagdetector/detector/markerdetector.h>

namespace nkdhny {

using DefaultCode = nkdhny::HammingSECDEDCode<6>;


WebcamDetector::WebcamDetector(unsigned cameraId):
    markerAnalizerFunction_(nkdhny::DenseMarker<6, DefaultCode>::detect),
    cameraId_(cameraId)
{
    capture_ = new cv::VideoCapture(this->cameraId_);
}

WebcamDetector::WebcamDetector(MarkerAnalizer markerAnalizerFunction, unsigned cameraId):
    markerAnalizerFunction_(markerAnalizerFunction),
    cameraId_(cameraId)
{
    capture_ = new cv::VideoCapture(this->cameraId_);
}

WebcamDetector::~WebcamDetector() {
    if(this->capture_)
        delete this->capture_;
}

std::vector<nkdhny::Marker> WebcamDetector::apply(){
    cv::Mat img;

    if(this->capture_ && this->capture_->isOpened() && this->capture_->read(img)){
        std::vector<nkdhny::Marker> markers;
        captureSize_ = img.size();
        if(img.type()!=CV_8UC1) {
            cv::Mat grey;
            cv::cvtColor(img, grey, CV_BGR2GRAY);
            nkdhny::detect(grey, this->markerAnalizerFunction_, markers, false);
        } else {
            nkdhny::detect(img, this->markerAnalizerFunction_, markers, false);
        }

        return markers;
    } else {
        return std::vector<nkdhny::Marker>();
    }
}

cv::Size WebcamDetector::getCaptureSize() {
    return captureSize_;
}

}
