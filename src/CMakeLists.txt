include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_executable(ResizeImage resizeimage.cpp)

target_link_libraries(ResizeImage optimized opencv_core opencv_highgui opencv_imgproc opencv_imgcodecs )

install(TARGETS ResizeImage DESTINATION install)
