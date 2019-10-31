#ifndef FILTER
#define FILTER

#include "Helper.h"

int WIDTH = 500;
int HEIGHT = 500;

Filter::Filter() {
  size = 0;
  array = NULL;
  flipped = false;
}

Filter::Filter(char * file) {
  ifstream in;
  in.open(file);
  in >> size;
  array = new float*[size];
  for(int i = 0; i < size; ++i) {
      array[i] = new float[size];
  }
  float sumPos = 0;
  float sumNeg = 0;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      in >> array[i][j];
      if (array[i][j] > 0)
        sumPos += array[i][j];
      else
        sumNeg += array[i][j];
    }
  }

  sum = sumPos;
  offset = 0;

  if (sumPos < abs(sumNeg))
    sum = sumNeg;
  else if (sumPos == abs(sumNeg)) {
    sum = 1;
    offset = 128;
  }

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      array[i][j] /= sum;
    }
  }
  sum = sumPos;
  flipped = false;
}

//for debug purposes
void Filter::print() {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      cout << array[i][j] << " ";
    }
    cout << endl;
  }
}

void Filter::flip() {
  float temp[size][size];
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      temp[i][j] = array[size-1-i][size-1-j];
    }
  }
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      array[i][j] = temp[i][j];
    }
  }
  flipped = !flipped;
}

bool Filter::isFlipped() {
  return flipped;
}

#endif
