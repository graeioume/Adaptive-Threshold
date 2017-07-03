//
//  PGM_loadsave.hpp
//  Adaptive Threshold
//
//  Created by Graeme Rock on 6/30/17.
//
//

#ifndef PGM8_loadsave_hpp
#define PGM8_loadsave_hpp

#include <iostream>
#include <cstdint>
#include <fstream>
#include <memory>
#include <string>

// This function simply reads from an input stream until the next character
// is not the specified comment delimiter.  It is used by readAndAllocatePGM8(),
// below.
void discardComments(std::istream& inputStream,
                     std::istream::char_type commentCharacter);

// This function returns the pixel data of an input PGM file via a shared
// pointer to uint8_t.  If anything goes wrong, the returned pointer will
// be null.  The size of the image will be returned via output arguments
// numberOfRows and numberOfColumns, and the returned pointer (if it
// isn't \ull) will point to the beginning of an array of (numberOfRows
// * numberOfColumns) pixel values, in raster order.
std::shared_ptr<uint8_t> readAndAllocatePGM8(std::size_t& numberOfRows,
                                             std::size_t& numberOfColumns,
                                             std::string const& fileName);

// This function writes a pgm image to the file specified by input
// argument fileName.  Argument imageBuffer must point to an array
// of at least (numberOfRows * numberOfColumns) pixel values in
// raster order.  The function returns 0 on success, nonzero otherwise.
int writePGM8(std::string const& fileName, std::shared_ptr<uint8_t> const imageBuffer,
              std::size_t numberOfRows, std::size_t numberOfColumns);

#endif /* PGM8_loadsave_hpp */
