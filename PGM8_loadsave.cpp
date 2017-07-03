//
//  PGM_loadsave.cpp
//  Adaptive Threshold
//
//  Created by Graeme Rock on 6/30/17.
//
//

#include "PGM8_loadsave.hpp"

// This function simply reads from an input stream until the next character
// is not the specified comment delimiter.  It is used by readAndAllocatePGM8(),
// below.
void discardComments(std::istream& inputStream,
                     std::istream::char_type commentCharacter)
{
    std::istream::char_type inputCharacter;
    // Loop until we find a non-comment line.
    while(1) {
        // This line reads the next non-whitespace character. Whitespace
        // is discarded by the stream input operator.
        inputStream >> inputCharacter;
        if(inputCharacter == commentCharacter) {
            // We found a comment.  Throw away the rest of the line.
            std::string dummyString;
            getline(inputStream, dummyString);
        } else {
            inputStream.putback(inputCharacter);
            
            break;
        }
    }
}


// This function returns the pixel data of an input PGM file via a shared
// pointer to uint8_t.  If anything goes wrong, the returned pointer will
// be null.  The size of the image will be returned via output arguments
// numberOfRows and numberOfColumns, and the returned pointer (if it
// isn't \ull) will point to the beginning of an array of (numberOfRows
// * numberOfColumns) pixel values, in raster order.
std::shared_ptr<uint8_t> readAndAllocatePGM8(std::size_t& numberOfRows,
                                             std::size_t& numberOfColumns,
                                             std::string const& fileName)
{
    std::ifstream inputStream(fileName.c_str(), std::ios::binary);
    if(!inputStream)
    {
        return nullptr; // Example code has no real error handling.
    }
    // Read the header.
    std::string magic;
    std::size_t imageMax;
    inputStream >> magic;
    
    if(magic !=  "P5" )
    {
        return nullptr; // Example code has no real error handling.
    }
    //    discardComments(inputStream, '#');
    inputStream >> numberOfColumns >> numberOfRows;
    discardComments(inputStream, '#');
    inputStream >> imageMax;
    // Image data starts after the next newline.
    std::string dummy;
    std::getline(inputStream, dummy);
    // Check for errors.
    if(!inputStream) {
        return nullptr; // Example code has no real error handling.
    }
    
    // Check that this image will fit in an 8-bit pixel array.
    if(imageMax > 255) {
        return nullptr; // Example code has no real error handling.
    }
    // Allocate storage space.
    std::size_t const numberOfPixels = numberOfRows * numberOfColumns;
    std::shared_ptr<uint8_t> imageBuffer(new uint8_t[numberOfPixels],
                                         std::default_delete<uint8_t[]>());
    // Read the pixels.
    inputStream.read(reinterpret_cast<char*>(imageBuffer.get()), numberOfPixels);
    
    // Check for errors.
    if(!inputStream) {
        return nullptr; // Example code has no real error handling.
    }
    
    // All done!
    inputStream.close();
    return imageBuffer;
}


// This function writes a pgm image to the file specified by input
// argument fileName.  Argument imageBuffer must point to an array
// of at least (numberOfRows * numberOfColumns) pixel values in
// raster order.  The function returns 0 on success, nonzero otherwise.
int writePGM8(std::string const& fileName, std::shared_ptr<uint8_t> const imageBuffer,
              std::size_t numberOfRows, std::size_t numberOfColumns)

{
    std::ofstream outputStream(fileName.c_str(), std::ios::binary);
    if(!outputStream)
    {
        return -1;
    }
    // Write the header.
    outputStream << "P5\n"
    << numberOfColumns << " " << numberOfRows << "\n"
    << "255\n";
    // Check for errors.
    if(!outputStream) {
        return -2;
    }
    // Write the pixels.
    std::size_t const numberOfPixels = numberOfRows * numberOfColumns;
    outputStream.write(reinterpret_cast<const char*>(imageBuffer.get()),
                       numberOfPixels);
    
    // Check for errors.
    if(!outputStream) {
        return -3;
    }
    // All done!
    outputStream.close();
    
    return 0;
}
