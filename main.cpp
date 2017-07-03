//
//  main.cpp
//  Carnegie Robotics Coding Challenge
//
//  Created by Graeme Rock on 6/17/17.
//
//

#include <iostream>
#include "adaptive_thresh.hpp"
#include "PGM8_loadsave.hpp"
//#include "opencv_io.h"

int main(int argc, const char * argv[]) {
    
    std::string filename;
    std::size_t numColumns;
    std::size_t numRows;
    
    //Image 0
    filename = "testimage0.pgm";
    std::cout << filename << "\n";
    std::shared_ptr<uint8_t> image =  readAndAllocatePGM8(numRows, numColumns, filename);
    std::cout <<  "columns " << numColumns << " rows " << numRows <<"\n";
    // The following two lines break pattern with Image1 for reason #5:
    // http://www.acodersjourney.com/2016/05/top-10-dumb-mistakes-avoid-c-11-smart-pointers/
    std::shared_ptr<uint8_t> mean_image = meanThreshold(image, numColumns, numRows);
    std::shared_ptr<uint8_t> adaptive_image = adaptiveThreshold(image, numColumns, numRows, 10);
    filename = filename.substr(0, filename.find_last_of(".")); //Remove extension // https://stackoverflow.com/questions/6417817/easy-way-to-remove-extension-from-a-filename
    writePGM8(filename + "_mean.pgm", mean_image, numRows, numColumns);
    writePGM8(filename + "_adaptive_10.pgm", adaptive_image, numRows, numColumns);


    //Image 1
    filename = "testimage1.pgm";
    std::cout << filename << "\n";
    image =  readAndAllocatePGM8(numRows, numColumns, filename);
    std::cout <<  "columns " << numColumns << " rows " << numRows <<"\n";
    mean_image = meanThreshold(image, numColumns, numRows);
    adaptive_image = adaptiveThreshold(image, numColumns, numRows, 10);
    filename = filename.substr(0, filename.find_last_of(".")); //Remove extension // https://stackoverflow.com/questions/6417817/easy-way-to-remove-extension-from-a-filename
    writePGM8(filename + "_mean.pgm", mean_image, numRows, numColumns);
    writePGM8(filename + "_adaptive_10.pgm", adaptive_image, numRows, numColumns);
    
    
    return 0;
}
