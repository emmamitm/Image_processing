//
// Created by Emma Mitchell on 3/16/22.
//

#ifndef PROJECT2_IMAGE_PROCESSING_HEADER_H
#define PROJECT2_IMAGE_PROCESSING_HEADER_H

#include <iostream>
#include <iostream>
#include "fstream"
#include "vector"
#include "sstream"
#pragma once
#include "string"

using namespace std;
struct header{
public:

    //vector<colorsNode> colorNodes; //making a vector of the pixels from the image

    char idlength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short coloraMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;



};
struct colorsNode {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};
class Image {
public:
    unsigned long imageData;
    vector<colorsNode> colorsInImage;
    header headerObj;
};




#endif //PROJECT2_IMAGE_PROCESSING_HEADER_H
