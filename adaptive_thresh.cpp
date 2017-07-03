//
//  adaptive_thresh.cpp
//  Adaptive Threshold
//
//  Created by Graeme Rock on 6/15/17.
//
//

#include "adaptive_thresh.hpp"

//Takes the average of the entire picture and splits the image
//Pro: Fast and dirty
//Con: Loses significant detail
std::shared_ptr<uint8_t> meanThreshold(std::shared_ptr<uint8_t> imageBuffer, std::size_t numberOfColumns, std::size_t numberOfRows)
{
    std::size_t const numberOfPixels = numberOfRows * numberOfColumns;

    // Find average pixel intensity: sum of pixel intensities / # pixels
    int sum = 0;
    for (std::size_t i=0; i < numberOfPixels; i++)
        sum += imageBuffer.get()[i];
    std::size_t mean = sum / numberOfPixels;
    
    // Allocate storage space.
    std::shared_ptr<uint8_t> output_imageBuffer(new uint8_t[numberOfPixels],
                                         std::default_delete<uint8_t[]>());
    
    // If pixel intensity > avg, round up to 1, else: round down to 0
    for (std::size_t i=0; i < numberOfPixels; i++)
    {
        if( imageBuffer.get()[i] > mean)        // If the pixel intensity is greater than the mean rounded down,
            output_imageBuffer.get()[i] = 255;  // set to white
        else output_imageBuffer.get()[i] = 0;   // else default to black

    }
    
    return output_imageBuffer;
}


//Takes the average of box areas in the image and separates colors based on the average
//Pro: Less information lost outright
//Con: Grainy output
std::shared_ptr<uint8_t> adaptiveThreshold(std::shared_ptr<uint8_t> imageBuffer,
                                           std::size_t numberOfColumns, std::size_t numberOfRows, std::size_t boxSize){
    
    std::size_t const numberOfPixels = numberOfRows * numberOfColumns;
    std::size_t const numRowBoxes = numberOfRows / boxSize;             //Number of boxes of size boxSize per row
    std::size_t const numColBoxes = numberOfColumns / boxSize;          //Number of boxes of size boxSize per column
    
    // I am leaving these in as useful diagnostic info
    std::cout << "numRowBoxes " << numRowBoxes << " box*numrow " << numRowBoxes * boxSize << "\n";
    std::cout << "numColBoxes " << numColBoxes << " box*numcol " << numColBoxes * boxSize << "\n";
    
    // Allocate storage space.
    std::shared_ptr<uint8_t> output_imageBuffer(new uint8_t[numberOfPixels],
                                                std::default_delete<uint8_t[]>());
    
    // Iterate through every averaging box
    for(std::size_t i=0; i < numRowBoxes; i++)
    {
        for(std::size_t k=0; k < numColBoxes; k++)
        {
            int sum = 0;
            
            // Iterate through every pixel of each box
            
            // From left to right side of each box
            std::size_t rowLimit;
            if(i == numRowBoxes) rowLimit = numberOfRows;  // Edge condition: when box would overflow off edge of image frame
            else rowLimit = (i+1)*boxSize;                 // Normal condition: size of boxSize
            for(size_t m = i*boxSize; m < rowLimit; m++)
            {
                // From top to bottom of each box
                std::size_t colLimit;
                if(i == numRowBoxes) colLimit = numberOfColumns;    // Edge condition when box would overflows off edge of image frame
                else colLimit = (k+1)*boxSize;                      // Normal condition: size of boxSize
                for(size_t n = k*boxSize; n <colLimit; n++)
                {
                    sum += imageBuffer.get()[m*n]; // Sum up pixel intensities within box
                }

            }
            std::size_t mean = sum / (boxSize*boxSize); // Find average pixel intensity within box: sum of pixel intensities / # pixels
            // From left to right side of each box
            for(size_t m = i*boxSize; m <(i+1)*boxSize; m++)
            {
                // From top to bottom of each box
                for(size_t n = k*boxSize; n <(k+1)*boxSize; n++)
                {
                    if( imageBuffer.get()[m*n] > mean)      // If the pixel intensity is greater than the mean rounded down,
                        output_imageBuffer.get()[m*n] = 255;// set pixel in output image to white
                    else output_imageBuffer.get()[m*n] = 0; // else default to black
                }
            }

        }
    }
    
    return output_imageBuffer;
}

// If I were especially dedicated to this task, I would implement a Canny edge detector
// to find edges, to perform individualized processing on each body.
//Alternatively, k-means could be used to find pixels similar to each other to create groupings to be processed.

