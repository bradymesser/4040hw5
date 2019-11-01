/*
Brady Messer (wmesser@clemson.edu)
CPSC 4040 Fall 2019
This file contains the necessary globals for GLUT
The name of the keyboard callback function is: handleKey
The name of the drawImage callback function is: drawImage
The name of the reshape callback function is: handleReshape
*/

#ifndef GLOBALS
#define GLOBALS

#include "Helper.h"

int WIDTH = 500;
int HEIGHT = 500;

Image image = Image();
Image originalImage = Image();
Filter filt = Filter();
string out = "";

void handleKey(unsigned char key, int x, int y) {
  switch(key){
    case 'q':		// q - quit
    case 'Q':
    case 27:		// esc - quit
      exit(0);
    case 'w':
    case 'W': {
      if (out == "") {
        string temp;
        cout << "Enter the name of the output file: ";
        cin >> temp;
        image.writeImage(temp);
      } else {
        image.writeImage(out);
      }
      break;
    }
    case 'i':
    case 'I':
      image.invert();
      break;
    case 'c':
    case 'C':
      image.convolve(filt);
      break;
    case 'r':
    case 'R':
      image.copy(originalImage);
      break;
    case 'f':
    case 'F': {
      string temp;
      cout << "Enter the file name of the new filter: ";
      cin >> temp;
      char * writable = new char[temp.size() + 1];
      copy(temp.begin(), temp.end(), writable);
      writable[temp.size()] = '\0'; // don't forget the terminating 0
      filt = Filter(writable);
      delete[] writable;
      break;
    }
    default:		// not a valid key -- just ignore it
      return;
  }
}
// This should display the image on screen but I have not tested it yet
void drawImage() {
  // specify window clear (background) color to be opaque white
  glClearColor(1,1,1,1);

  // clear window to background color
  glClear(GL_COLOR_BUFFER_BIT);

	// Set window to be the same size as the image
  glutReshapeWindow(image.width, image.height);
  glutPostRedisplay();

	image.draw();
  // flush the OpenGL pipeline to the viewport
  glFlush();
}

void handleReshape(int w, int h) {
	// set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// define the drawing coordinate system on the viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
  glOrtho( 0, w, 0, h, 0.1, 1 );
  // flip the image to the correct orientation
  glPixelZoom( 1, -1 );
  glRasterPos3f(0, h - 1, -0.3);
}
#endif
