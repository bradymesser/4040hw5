/*
Brady Messer (wmesser@clemson.edu)
CPSC 4040 HW1 Fall 2019
This file contains the Image object and some helper functions to read and write images
The name of the keyboard callback function is: handleKey
The name of the drawImage callback function is: drawImage
The name of the reshape callback function is: handleReshape
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

// The class that represents an image
class Image {
  private:
    int DEFAULT_OUT_OF_BOUNDS_VALUE;
  public:
    int width;
    int height;
    int channels;
    unsigned char * pixels;
    string ext;

    //default constructor
    Image();
    // overloaded constructor, reads in an image
    Image(string file);
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

// #ifndef GLOBALS
// #define GLOBALS
//
// Image image = Image();
// Image originalImage = Image();
// Filter filt = Filter();
// string out = "";
//
// void handleKey(unsigned char key, int x, int y) {
//   switch(key){
//     case 'q':		// q - quit
//     case 'Q':
//     case 27:		// esc - quit
//       exit(0);
//     case 'w':
//     case 'W': {
//       if (out == "") {
//         string temp;
//         cout << "Enter the name of the output file: ";
//         cin >> temp;
//         image.writeImage(temp);
//       } else {
//         image.writeImage(out);
//       }
//       break;
//     }
//     case 'i':
//     case 'I':
//       image.invert();
//       break;
//     case 'c':
//     case 'C':
//       image.convolve(filt);
//       break;
//     case 'r':
//     case 'R':
//       image.copy(originalImage);
//       break;
//     case 'f':
//     case 'F': {
//       string temp;
//       cout << "Enter the file name of the new filter: ";
//       cin >> temp;
//       char * writable = new char[temp.size() + 1];
//       copy(temp.begin(), temp.end(), writable);
//       writable[temp.size()] = '\0'; // don't forget the terminating 0
//       filt = Filter(writable);
//       delete[] writable;
//       break;
//     }
//     default:		// not a valid key -- just ignore it
//       return;
//   }
// }
// // This should display the image on screen but I have not tested it yet
// void drawImage() {
//   // specify window clear (background) color to be opaque white
//   glClearColor(1,1,1,1);
//
//   // clear window to background color
//   glClear(GL_COLOR_BUFFER_BIT);
//
// 	// Set window to be the same size as the image
//   glutReshapeWindow(image.width, image.height);
//   glutPostRedisplay();
//
// 	image.draw();
//   // flush the OpenGL pipeline to the viewport
//   glFlush();
// }
//
// void handleReshape(int w, int h) {
// 	// set the viewport to be the entire window
// 	glViewport(0, 0, w, h);
//
// 	// define the drawing coordinate system on the viewport
// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();
//   glOrtho( 0, w, 0, h, 0.1, 1 );
//   // flip the image to the correct orientation
//   glPixelZoom( 1, -1 );
//   glRasterPos3f(0, h - 1, -0.3);
// }
// #endif
#endif
