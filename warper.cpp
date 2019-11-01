/*
 * Program sample to warp an image using matrix-based warps
 *
 * Command line parameters are as follows:
 *
 * warper infile.png [outfile.png]
 *
 * Author: Ioannis Karamouzas, 10/20/19
 */

#include "matrix.h"
#include "Helper.h"
#include "Globals.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;
using std::string;

/*
Multiply M by a rotation matrix of angle theta
*/

void Rotate(Matrix3D &M, float theta) {
	int row, col;
	Matrix3D R;
	double rad, c, s;
	rad = PI * theta / 180.0;
	c = cos(rad);
	s = sin(rad);
	R[0][0] = c;
	R[0][1] = s;
	R[1][0] = -s;
	R[1][1] = c;

	M = R * M;

}


/*
Build a transformation matrix from input text
*/
void read_input(Matrix3D &M) {
	string cmd;

	/* prompt for user input */
	do
	{
		cout << "> ";
		cin >> cmd;
		if (cmd.length() != 1){
			cout << "invalid command, enter r, s, t, h, f, p, d\n";
		}
		else {
			switch (cmd[0]) {
				case 'r':		/* Rotation, accept angle in degrees */
					float theta;
					cin >> theta;
					if (cin) {
						cout << "calling rotate\n";
						Rotate(M, theta);
					}
					else {
						cerr << "invalid rotation angle\n";
						cin.clear();
					}
					break;
				case 's':		/* scale, accept scale factors */
					float scaleX;
					float scaleY;
					cin >> scaleX >> scaleY;
					if (cin) {
						cout << "scaling\n";
						M[0][0] = scaleX;
						M[1][1] = scaleY;
					}
					else {
						cerr << "invalid scale\n";
						cin.clear();
					}
					break;
				case 't':		/* Translation, accept translations */
					break;
				case 'h':		/* Shear, accept shear factors */
					break;
				case 'f':		/* Flip, accept flip factors */
					break;
				case 'p':		/* Perspective, accept perspective factors */
					break;
				case 'd':		/* Done, that's all for now */
					break;
				default:
					cout << "invalid command, enter r, s, t, h, f, p, d\n";
			}
		}
	} while (cmd.compare("d")!=0);

}

struct Pixel {
	unsigned char * pix;
};

/*
   Main program to read an image file, then ask the user
   for transform information, transform the image and display
   it using the appropriate warp.  Optionally save the transformed
   images in  files.
*/
int main(int argc, char *argv[]){

	// initialize transformation matrix to identity
	Matrix3D M;

   //your code to read in the input image
	 if (argc < 2 || argc > 3) {
	 	cout << "Valid usages are: \n./warper input.image\n./warper input.image output.image\n";
		exit(1);
	} else {
		image = Image(argv[1]);
		originalImage = Image(argv[1]);
	}

   //build the transformation matrix based on user input
   read_input(M);


	// printout the final matrix
    cout << "Accumulated Matrix: " << endl;
    M.print();

   // your code to perform inverse mapping (4 steps)
	 // 1)compute bounding box
	 // 2)allocate output image
	 // 3)compute inverse Matrix
	 // 4)apply inverse map

	 // 1)
	 Vector2D corners[4];
	 corners[0] = Vector2D(0,0);
	 corners[1] = Vector2D(image.width,0);
	 corners[2] = Vector2D(0,image.height);
	 corners[3]= Vector2D(image.width,image.height);
	 Vector3D temp = M * corners[0];
	 if (temp.z != 1) {
		 temp.x /= temp.z;
		 temp.y /= temp.z;
		 temp.z /= temp.z;
	 }
	 float minX = temp.x;
	 float minY = temp.y;
	 float maxX = temp.x;
	 float maxY = temp.y;

	 for (int i = 0; i < 3; i++) {
		 temp = M * corners[i];
		 if (temp.z != 1) {
			 temp.x /= temp.z;
			 temp.y /= temp.z;
			 temp.z /= temp.z;
		 }
		 if (temp.x < minX)
		 	minX = temp.x;
		 else if (temp.x > maxX)
		 	maxX = temp.x;
		 if (temp.y < minY)
		 	minY = temp.y;
		 else if (temp.y > maxY)
		  maxY = temp.y;
	 }

	 //2)
	 int w = maxX - minX;
	 int h = maxY - minY;
	 cout << "In image size : " << image.width << "x" << image.height << endl;
	 cout << "Out image size: " << w << "x" << h << endl;
	 cout << "MinXxMinY: " << minX << "x" << minY << endl;
	 Image img = Image(w,h,image.channels);

	 //3)
	 Matrix3D inv = M.inverse();
	 inv.print();
	 //4)
	 Vector3D origin = Vector3D(minX, minY, 1);
	 Vector3D t;
	 cout << "Origin: " << (int)origin.x << "," << (int)origin.y << endl;
	 /*
	   | 0 | 1 | 2
	 0 | 0 | 1 | 2
	 1 | 3 | 4 | 5
	 2 | 6 | 7 | 8
	 */
// (row * width) + column
	 Pixel p;
	 Pixel pix[image.height][image.width];
	 int k = 0;
   int l = 0;

	 for (int i = 0; i < image.width * image.height * image.channels; i+=image.channels) {
		 pix[k][l].pix = new unsigned char (image.channels);
		 // cout << "*" << k << "," << l<<endl;
		 for (int j = 0; j < image.channels; j++) {
			 // cout << j << "k: " << k << "l: " << l << "i: " << i;
			 pix[k][l].pix[j] = image.pixels[i + j];
			 // cout << "e" << endl;
		 }
     l++;
     if (l == image.width) {
       l = 0;
       k++;
     }
   }
	 k = 0;
	 l = 0;

	 for (int i = 0; i < img.width * img.height * img.channels; i+=img.channels) {
		 Vector3D pixel_out(l,k,1);
		 pixel_out.x += origin.x;
		 pixel_out.y += origin.y;
		 Vector3D pixel_in = inv * pixel_out;

		 float u = pixel_in.x / pixel_in.z;
		 float v = pixel_in.y / pixel_in.z;
		 // cout << "u: " << u << "v: " << v << "i: " << i << endl;
		 if (v >= 0 && v < image.height && u >= 0 && u < image.width) {
			 for (int j = 0; j < image.channels; j++) {
				 // if (v > 0 && v < img.height && u > 0 && u < img.width)
			 		img.pixels[i+j] = pix[(int)v][(int)u].pix[j];
		 	}
	 	}
     l++;
     if (l == img.width) {
       l = 0;
       k++;
     }
   }

	 image = img;	// the most important line

   //your code to display the warped image
	 glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGBA);
   glutInitWindowSize(WIDTH, HEIGHT);
   glutCreateWindow("WARPER");

   glutDisplayFunc(drawImage);	  // display callback
   glutKeyboardFunc(handleKey);
   glutReshapeFunc(handleReshape); // window resize callback

   glutMainLoop();
   return 0;
}
