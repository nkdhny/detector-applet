#include <iostream>
#include "webcamdetector.h"
#include <runtagdetector/detector/marker.h>
#include <vector>

using namespace std;

int main()
{
    nkdhny::WebcamDetector detector;
    std::cout << "Capturing from default camra using default code..."<<std::endl;

    while(true) {
        std::vector<nkdhny::Marker> markers = detector.apply();

        for(auto m: markers) {
            std::cout << m.id()<<" ";
        }
        if(!markers.empty()) {
            std::cout << std::endl;
        }
    }

    return 0;
}

