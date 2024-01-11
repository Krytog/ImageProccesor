cmake_minimum_required(VERSION 3.16)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(image_processor
        image_processor.cpp
        Parser/parser.cpp
        BmpHandler/bmp_handler.cpp Image/image.cpp Filters/Crop/crop.cpp FilterHandler/filter_handler.cpp Filters/Filter/filter.cpp Filters/Grayscale/grayscale.cpp Filters/Negative/negative.cpp Filters/Sharpening/sharpening.cpp Filters/EdgeDetection/edge_detection.cpp Filters/GaussianBlur/gaussian_blur.cpp Filters/Zhmih/zhmih.cpp Filters/UltraZhmih/ultra_zhmih.cpp Filters/Minecraft/minecraft.cpp)
