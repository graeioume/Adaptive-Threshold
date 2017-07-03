//
//  adaptive_thresh.hpp
//  Adaptive Threshold
//
//  Created by Graeme Rock on 6/15/17.
//
//

#ifndef adaptive_thresh_hpp
#define adaptive_thresh_hpp

#include <cstdint>
#include <memory>
#include <iostream>

//#include <iomanip>

//Takes the average of the entire picture and splits the image into black or white
//Pro: Fast and dirty
//Con: Loses significant detail
std::shared_ptr<uint8_t> meanThreshold(std::shared_ptr<uint8_t> imageBuffer, std::size_t numberOfColumns, std::size_t numberOfRows);

//Takes the average of box areas in the image and separates colors based on the average
//Pro: Less information lost outright
//Con: Grainy output
std::shared_ptr<uint8_t> adaptiveThreshold(std::shared_ptr<uint8_t> imageBuffer,
                                           std::size_t numberOfColumns, std::size_t numberOfRows, std::size_t boxSize);


#endif /* adaptive_thresh_hpp */
