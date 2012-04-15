// 1.6
// Given an image represented by an NxN matrix, where each pixel in the image
// is 4 bytes, write a method to rotate the image by 90 degrees Can you do this
// in place?

#ifndef _CHAP1_6_ROTATE_MATRIX_H_
#define _CHAP1_6_ROTATE_MATRIX_H_

void rotate_matrix_ez(int* data, size_t n, bool clockwise=true); // Use extra memory

void rotate_matrix(int* data, size_t n, bool clockwise=true);

#endif

