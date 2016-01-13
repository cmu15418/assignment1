// Define vector unit width here
#define VECTOR_WIDTH 4

#ifndef CMU418INTRIN_H_
#define CMU418INTRIN_H_

#include <cstdlib>
#include <cmath>
#include "logger.h"

//*******************
//* Type Definition *
//*******************

extern Logger CMU418Logger;

template <typename T>
struct __cmu418_vec {
  T value[VECTOR_WIDTH];
};

// Declare a mask with __cmu418_mask
struct __cmu418_mask : __cmu418_vec<bool> {};

// Declare a floating point vector register with __cmu418_vec_float
#define __cmu418_vec_float __cmu418_vec<float>

// Declare an integer vector register with __cmu418_vec_int
#define __cmu418_vec_int   __cmu418_vec<int>

//***********************
//* Function Definition *
//***********************

// Return a mask initialized to 1 in the first N lanes and 0 in the others
__cmu418_mask _cmu418_init_ones(int first = VECTOR_WIDTH);

// Return the inverse of maska
__cmu418_mask _cmu418_mask_not(__cmu418_mask &maska);

// Return (maska | maskb)
__cmu418_mask _cmu418_mask_or(__cmu418_mask &maska, __cmu418_mask &maskb);

// Return (maska & maskb)
__cmu418_mask _cmu418_mask_and(__cmu418_mask &maska, __cmu418_mask &maskb);

// Count the number of 1s in maska
int _cmu418_cntbits(__cmu418_mask &maska);

// Set register to value if vector lane is active
//  otherwise keep the old value
void _cmu418_vset_float(__cmu418_vec_float &vecResult, float value, __cmu418_mask &mask);
void _cmu418_vset_int(__cmu418_vec_int &vecResult, int value, __cmu418_mask &mask);
// For user's convenience, returns a vector register with all lanes initialized to value
__cmu418_vec_float _cmu418_vset_float(float value);
__cmu418_vec_int _cmu418_vset_int(int value);

// Copy values from vector register src to vector register dest if vector lane active
// otherwise keep the old value
void _cmu418_vmove_float(__cmu418_vec_float &dest, __cmu418_vec_float &src, __cmu418_mask &mask);
void _cmu418_vmove_int(__cmu418_vec_int &dest, __cmu418_vec_int &src, __cmu418_mask &mask);

// Load values from array src to vector register dest if vector lane active
//  otherwise keep the old value
void _cmu418_vload_float(__cmu418_vec_float &dest, float* src, __cmu418_mask &mask);
void _cmu418_vload_int(__cmu418_vec_int &dest, int* src, __cmu418_mask &mask);

// Store values from vector register src to array dest if vector lane active
//  otherwise keep the old value
void _cmu418_vstore_float(float* dest, __cmu418_vec_float &src, __cmu418_mask &mask);
void _cmu418_vstore_int(int* dest, __cmu418_vec_int &src, __cmu418_mask &mask);

// Return calculation of (veca + vecb) if vector lane active
//  otherwise keep the old value
void _cmu418_vadd_float(__cmu418_vec_float &vecResult, __cmu418_vec_float &veca, __cmu418_vec_float &vecb, __cmu418_mask &mask);
void _cmu418_vadd_int(__cmu418_vec_int &vecResult, __cmu418_vec_int &veca, __cmu418_vec_int &vecb, __cmu418_mask &mask);

// Return calculation of (veca - vecb) if vector lane active
//  otherwise keep the old value
void _cmu418_vsub_float(__cmu418_vec_float &vecResult, __cmu418_vec_float &veca, __cmu418_vec_float &vecb, __cmu418_mask &mask);
void _cmu418_vsub_int(__cmu418_vec_int &vecResult, __cmu418_vec_int &veca, __cmu418_vec_int &vecb, __cmu418_mask &mask);

// Return calculation of (veca * vecb) if vector lane active
//  otherwise keep the old value
void _cmu418_vmult_float(__cmu418_vec_float &vecResult, __cmu418_vec_float &veca, __cmu418_vec_float &vecb, __cmu418_mask &mask);
void _cmu418_vmult_int(__cmu418_vec_int &vecResult, __cmu418_vec_int &veca, __cmu418_vec_int &vecb, __cmu418_mask &mask);

// Return calculation of (veca / vecb) if vector lane active
//  otherwise keep the old value
void _cmu418_vdiv_float(__cmu418_vec_float &vecResult, __cmu418_vec_float &veca, __cmu418_vec_float &vecb, __cmu418_mask &mask);
void _cmu418_vdiv_int(__cmu418_vec_int &vecResult, __cmu418_vec_int &veca, __cmu418_vec_int &vecb, __cmu418_mask &mask);


// Return calculation of absolute value abs(veca) if vector lane active
//  otherwise keep the old value
void _cmu418_vabs_float(__cmu418_vec_float &vecResult, __cmu418_vec_float &veca, __cmu418_mask &mask);
void _cmu418_vabs_int(__cmu418_vec_int &vecResult, __cmu418_vec_int &veca, __cmu418_mask &mask);

// Return a mask of (veca > vecb) if vector lane active
//  otherwise keep the old value
void _cmu418_vgt_float(__cmu418_mask &vecResult, __cmu418_vec_float &veca, __cmu418_vec_float &vecb, __cmu418_mask &mask);
void _cmu418_vgt_int(__cmu418_mask &vecResult, __cmu418_vec_int &veca, __cmu418_vec_int &vecb, __cmu418_mask &mask);

// Return a mask of (veca < vecb) if vector lane active
//  otherwise keep the old value
void _cmu418_vlt_float(__cmu418_mask &vecResult, __cmu418_vec_float &veca, __cmu418_vec_float &vecb, __cmu418_mask &mask);
void _cmu418_vlt_int(__cmu418_mask &vecResult, __cmu418_vec_int &veca, __cmu418_vec_int &vecb, __cmu418_mask &mask);

// Return a mask of (veca == vecb) if vector lane active
//  otherwise keep the old value
void _cmu418_veq_float(__cmu418_mask &vecResult, __cmu418_vec_float &veca, __cmu418_vec_float &vecb, __cmu418_mask &mask);
void _cmu418_veq_int(__cmu418_mask &vecResult, __cmu418_vec_int &veca, __cmu418_vec_int &vecb, __cmu418_mask &mask);

// Adds up adjacent pairs of elements, so
//  [0 1 2 3] -> [0+1 0+1 2+3 2+3]
void _cmu418_hadd_float(__cmu418_vec_float &vecResult, __cmu418_vec_float &vec);

// Performs an even-odd interleaving where all even-indexed elements move to front half
//  of the array and odd-indexed to the back half, so
//  [0 1 2 3 4 5 6 7] -> [0 2 4 6 1 3 5 7]
void _cmu418_interleave_float(__cmu418_vec_float &vecResult, __cmu418_vec_float &vec);

// Add a customized log to help debugging
void addUserLog(const char * logStr);

#endif
