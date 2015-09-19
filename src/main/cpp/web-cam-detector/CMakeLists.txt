project(web-cam-detector)
cmake_minimum_required(VERSION 2.8)

add_definitions(-std=c++11)

find_package( OpenCV REQUIRED )
find_package( JNI )

include_directories( ${RUNTAG_HOME}/include ${JAVA_INCLUDE_PATH} ${JAVA_INCLUDE_PATH2} )
link_directories( ${RUNTAG_HOME} )


add_library(runtagwebcamdetector SHARED webcamdetector.cpp)
target_link_libraries(runtagwebcamdetector runtagdetector runtagcodes ${OpenCV_LIBS})

add_executable(webcamdetectortest main.cpp)
target_link_libraries(webcamdetectortest runtagwebcamdetector)

add_library(jruntagwebcamdetector SHARED jwebcamdetector.cpp)
target_link_libraries(jruntagwebcamdetector runtagwebcamdetector ${JNI_LIBRARIES} ${OpenCV_LIB})

