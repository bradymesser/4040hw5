/*
Brady Messer (wmesser@clemson.edu)
CPSC 4040 Fall 2019
This file contains the Image object and Filter object
*/
#ifndef HELPER
#define HELPER

#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <OpenImageIO/imageio.h>
#include <string>
#include <math.h>
using namespace std;
OIIO_NAMESPACE_USING;

void RGBtoHSV(int r,int g,int b,double &h,double &s,double &v);

// A filter used for convolving
class Filter {
  private:
    bool flipped;
  public:
    int size;
    float ** array;
    float sum;
    int offset;

    Filter();
    Filter(char * file);
    void print();
    void flip();
    bool isFlipped();
};

// The struct that represents an individual pixel
struct Pixel {
	unsigned char * pix;
};

// The class that represents an image
class Image {
  private:
    int DEFAULT_OUT_OF_BOUNDS_VALUE;
    void convertTo2DPixels();
  public:
    int width;
    int height;
    int channels;
    unsigned char * pixels;
    Pixel ** pixels2D;
    string ext;

    //default constructor
    Image();
    // overloaded constructor, reads in an image
    Image(string file);
    // overloaded constructor, creates image of size w*h*chan
    Image(int w, int h, int chan);
    // copy function
    void copy(const Image& img);
    // //writes the object to a file
    void writeImage(string filename);
    // // Inverts the colors of the image
    void invert();
    // // This just draws the pixels, it cannot be used as the callback function for drawing
    void draw();
    // // Converts to a 4 channel image
    void convertToFourChannels();
    // Chromakey the image based on hsv values and the thresholds defined in thresholds.txt
    void chromaKey();
    // Uses the current image object as the background (B), and overlays the parameter image (A)
    // The result is an image with A composited onto B (A over B)
    void composite(Image A);
    // Convolves the image with a specified filter
    void convolve(Filter filter);
};

#endif
