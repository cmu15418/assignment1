#include "CMU418intrin.h"
#include "logger.h"

//******************
//* Implementation *
//******************

__cmu418_mask _cmu418_init_ones(int first) {
  __cmu418_mask mask;
  for (int i=0; i<VECTOR_WIDTH; i++) {
    mask.value[i] = (i<first) ? true : false;
  }
  return mask;
}

__cmu418_mask _cmu418_mask_not(__cmu418_mask &maska) {
  __cmu418_mask resultMask;
  for (int i=0; i<VECTOR_WIDTH; i++) {
    resultMask.value[i] = !maska.value[i];
  }
  CMU418Logger.addLog("masknot", _cmu418_init_ones(), VECTOR_WIDTH);
  return resultMask;
}

__cmu418_mask _cmu418_mask_or(__cmu418_mask &maska, __cmu418_mask &maskb) {
  __cmu418_mask resultMask;
  for (int i=0; i<VECTOR_WIDTH; i++) {
    resultMask.value[i] = maska.value[i] | maskb.value[i];
  }
  CMU418Logger.addLog("maskor", _cmu418_init_ones(), VECTOR_WIDTH);
  return resultMask;
}

__cmu418_mask _cmu418_mask_and(__cmu418_mask &maska, __cmu418_mask &maskb) {
  __cmu418_mask resultMask;
  for (int i=0; i<VECTOR_WIDTH; i++) {
    resultMask.value[i] = maska.value[i] && maskb.value[i];
  }
  CMU418Logger.addLog("maskand", _cmu418_init_ones(), VECTOR_WIDTH);
  return resultMask;
}

int _cmu418_cntbits(__cmu418_mask &maska) {
  int count = 0;
  for (int i=0; i<VECTOR_WIDTH; i++) {
    if (maska.value[i]) count++;
  }
  CMU418Logger.addLog("cntbits", _cmu418_init_ones(), VECTOR_WIDTH);
  return count;
}

template <typename T>
void _cmu418_vset(__cmu418_vec<T> &vecResult, T value, __cmu418_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    vecResult.value[i] = mask.value[i] ? value : vecResult.value[i];
  }
  CMU418Logger.addLog("vset", mask, VECTOR_WIDTH);
}

template void _cmu418_vset<float>(__cmu418_vec_float &vecResult, float value, __cmu418_mask &mask);
template void _cmu418_vset<int>(__cmu418_vec_int &vecResult, int value, __cmu418_mask &mask);

void _cmu418_vset_float(__cmu418_vec_float &vecResult, float value, __cmu418_mask &mask) { _cmu418_vset<float>(vecResult, value, mask); }
void _cmu418_vset_int(__cmu418_vec_int &vecResult, int value, __cmu418_mask &mask) { _cmu418_vset<int>(vecResult, value, mask); }

__cmu418_vec_float _cmu418_vset_float(float value) {
  __cmu418_vec_float vecResult;
  __cmu418_mask mask = _cmu418_init_ones();
  _cmu418_vset_float(vecResult, value, mask);
  return vecResult;
}
__cmu418_vec_int _cmu418_vset_int(int value) {
  __cmu418_vec_int vecResult;
  __cmu418_mask mask = _cmu418_init_ones();
  _cmu418_vset_int(vecResult, value, mask);
  return vecResult;
}

template <typename T>
void _cmu418_vmove(__cmu418_vec<T> &dest, __cmu418_vec<T> &src, __cmu418_mask &mask) {
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        dest.value[i] = mask.value[i] ? src.value[i] : dest.value[i];
    }
    CMU418Logger.addLog("vmove", mask, VECTOR_WIDTH);
}

template void _cmu418_vmove<float>(__cmu418_vec_float &dest, __cmu418_vec_float &src, __cmu418_mask &mask);
template void _cmu418_vmove<int>(__cmu418_vec_int &dest, __cmu418_vec_int &src, __cmu418_mask &mask);

void _cmu418_vmove_float(__cmu418_vec_float &dest, __cmu418_vec_float &src, __cmu418_mask &mask) { _cmu418_vmove<float>(dest, src, mask); }
void _cmu418_vmove_int(__cmu418_vec_int &dest, __cmu418_vec_int &src, __cmu418_mask &mask) { _cmu418_vmove<int>(dest, src, mask); }

template <typename T>
void _cmu418_vload(__cmu418_vec<T> &dest, T* src, __cmu418_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    dest.value[i] = mask.value[i] ? src[i] : dest.value[i];
  }
  CMU418Logger.addLog("vload", mask, VECTOR_WIDTH);
}

template void _cmu418_vload<float>(__cmu418_vec_float &dest, float* src, __cmu418_mask &mask);
template void _cmu418_vload<int>(__cmu418_vec_int &dest, int* src, __cmu418_mask &mask);

void _cmu418_vload_float(__cmu418_vec_float &dest, float* src, __cmu418_mask &mask) { _cmu418_vload<float>(dest, src, mask); }
void _cmu418_vload_int(__cmu418_vec_int &dest, int* src, __cmu418_mask &mask) { _cmu418_vload<int>(dest, src, mask); }

template <typename T>
void _cmu418_vstore(T* dest, __cmu418_vec<T> &src, __cmu418_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    dest[i] = mask.value[i] ? src.value[i] : dest[i];
  }
  CMU418Logger.addLog("vstore", mask, VECTOR_WIDTH);
}

template void _cmu418_vstore<float>(float* dest, __cmu418_vec_float &src, __cmu418_mask &mask);
template void _cmu418_vstore<int>(int* dest, __cmu418_vec_int &src, __cmu418_mask &mask);

void _cmu418_vstore_float(float* dest, __cmu418_vec_float &src, __cmu418_mask &mask) { _cmu418_vstore<float>(dest, src, mask); }
void _cmu418_vstore_int(int* dest, __cmu418_vec_int &src, __cmu418_mask &mask) { _cmu418_vstore<int>(dest, src, mask); }

template <typename T>
void _cmu418_vadd(__cmu418_vec<T> &vecResult, __cmu418_vec<T> &veca, __cmu418_vec<T> &vecb, __cmu418_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    vecResult.value[i] = mask.value[i] ? (veca.value[i] + vecb.value[i]) : vecResult.value[i];
  }
  CMU418Logger.addLog("vadd", mask, VECTOR_WIDTH);
}

template void _cmu418_vadd<float>(__cmu418_vec_float &vecResult, __cmu418_vec_float &veca, __cmu418_vec_float &vecb, __cmu418_mask &mask);
template void _cmu418_vadd<int>(__cmu418_vec_int &vecResult, __cmu418_vec_int &veca, __cmu418_vec_int &vecb, __cmu418_mask &mask);

void _cmu418_vadd_float(__cmu418_vec_float &vecResult, __cmu418_vec_float &veca, __cmu418_vec_float &vecb, __cmu418_mask &mask) { _cmu418_vadd<float>(vecResult, veca, vecb, mask); }
void _cmu418_vadd_int(__cmu418_vec_int &vecResult, __cmu418_vec_int &veca, __cmu418_vec_int &vecb, __cmu418_mask &mask) { _cmu418_vadd<int>(vecResult, veca, vecb, mask); }

template <typename T>
void _cmu418_vsub(__cmu418_vec<T> &vecResult, __cmu418_vec<T> &veca, __cmu418_vec<T> &vecb, __cmu418_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    vecResult.value[i] = mask.value[i] ? (veca.value[i] - vecb.value[i]) : vecResult.value[i];
  }
  CMU418Logger.addLog("vsub", mask, VECTOR_WIDTH);
}

template void _cmu418_vsub<float>(__cmu418_vec_float &vecResult, __cmu418_vec_float &veca, __cmu418_vec_float &vecb, __cmu418_mask &mask);
template void _cmu418_vsub<int>(__cmu418_vec_int &vecResult, __cmu418_vec_int &veca, __cmu418_vec_int &vecb, __cmu418_mask &mask);

void _cmu418_vsub_float(__cmu418_vec_float &vecResult, __cmu418_vec_float &veca, __cmu418_vec_float &vecb, __cmu418_mask &mask) { _cmu418_vsub<float>(vecResult, veca, vecb, mask); }
void _cmu418_vsub_int(__cmu418_vec_int &vecResult, __cmu418_vec_int &veca, __cmu418_vec_int &vecb, __cmu418_mask &mask) { _cmu418_vsub<int>(vecResult, veca, vecb, mask); }

template <typename T>
void _cmu418_vmult(__cmu418_vec<T> &vecResult, __cmu418_vec<T> &veca, __cmu418_vec<T> &vecb, __cmu418_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    vecResult.value[i] = mask.value[i] ? (veca.value[i] * vecb.value[i]) : vecResult.value[i];
  }
  CMU418Logger.addLog("vmult", mask, VECTOR_WIDTH);
}

template void _cmu418_vmult<float>(__cmu418_vec_float &vecResult, __cmu418_vec_float &veca, __cmu418_vec_float &vecb, __cmu418_mask &mask);
template void _cmu418_vmult<int>(__cmu418_vec_int &vecResult, __cmu418_vec_int &veca, __cmu418_vec_int &vecb, __cmu418_mask &mask);

void _cmu418_vmult_float(__cmu418_vec_float &vecResult, __cmu418_vec_float &veca, __cmu418_vec_float &vecb, __cmu418_mask &mask) { _cmu418_vmult<float>(vecResult, veca, vecb, mask); }
void _cmu418_vmult_int(__cmu418_vec_int &vecResult, __cmu418_vec_int &veca, __cmu418_vec_int &vecb, __cmu418_mask &mask) { _cmu418_vmult<int>(vecResult, veca, vecb, mask); }

template <typename T>
void _cmu418_vdiv(__cmu418_vec<T> &vecResult, __cmu418_vec<T> &veca, __cmu418_vec<T> &vecb, __cmu418_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    vecResult.value[i] = mask.value[i] ? (veca.value[i] / vecb.value[i]) : vecResult.value[i];
  }
  CMU418Logger.addLog("vdiv", mask, VECTOR_WIDTH);
}

template void _cmu418_vdiv<float>(__cmu418_vec_float &vecResult, __cmu418_vec_float &veca, __cmu418_vec_float &vecb, __cmu418_mask &mask);
template void _cmu418_vdiv<int>(__cmu418_vec_int &vecResult, __cmu418_vec_int &veca, __cmu418_vec_int &vecb, __cmu418_mask &mask);

void _cmu418_vdiv_float(__cmu418_vec_float &vecResult, __cmu418_vec_float &veca, __cmu418_vec_float &vecb, __cmu418_mask &mask) { _cmu418_vdiv<float>(vecResult, veca, vecb, mask); }
void _cmu418_vdiv_int(__cmu418_vec_int &vecResult, __cmu418_vec_int &veca, __cmu418_vec_int &vecb, __cmu418_mask &mask) { _cmu418_vdiv<int>(vecResult, veca, vecb, mask); }

template <typename T>
void _cmu418_vabs(__cmu418_vec<T> &vecResult, __cmu418_vec<T> &veca, __cmu418_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    vecResult.value[i] = mask.value[i] ? (abs(veca.value[i])) : vecResult.value[i];
  }
  CMU418Logger.addLog("vabs", mask, VECTOR_WIDTH);
}

template void _cmu418_vabs<float>(__cmu418_vec_float &vecResult, __cmu418_vec_float &veca, __cmu418_mask &mask);
template void _cmu418_vabs<int>(__cmu418_vec_int &vecResult, __cmu418_vec_int &veca, __cmu418_mask &mask);

void _cmu418_vabs_float(__cmu418_vec_float &vecResult, __cmu418_vec_float &veca, __cmu418_mask &mask) { _cmu418_vabs<float>(vecResult, veca, mask); }
void _cmu418_vabs_int(__cmu418_vec_int &vecResult, __cmu418_vec_int &veca, __cmu418_mask &mask) { _cmu418_vabs<int>(vecResult, veca, mask); }

template <typename T>
void _cmu418_vgt(__cmu418_mask &maskResult, __cmu418_vec<T> &veca, __cmu418_vec<T> &vecb, __cmu418_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    maskResult.value[i] = mask.value[i] ? (veca.value[i] > vecb.value[i]) : maskResult.value[i];
  }
  CMU418Logger.addLog("vgt", mask, VECTOR_WIDTH);
}

template void _cmu418_vgt<float>(__cmu418_mask &maskResult, __cmu418_vec_float &veca, __cmu418_vec_float &vecb, __cmu418_mask &mask);
template void _cmu418_vgt<int>(__cmu418_mask &maskResult, __cmu418_vec_int &veca, __cmu418_vec_int &vecb, __cmu418_mask &mask);

void _cmu418_vgt_float(__cmu418_mask &maskResult, __cmu418_vec_float &veca, __cmu418_vec_float &vecb, __cmu418_mask &mask) { _cmu418_vgt<float>(maskResult, veca, vecb, mask); }
void _cmu418_vgt_int(__cmu418_mask &maskResult, __cmu418_vec_int &veca, __cmu418_vec_int &vecb, __cmu418_mask &mask) { _cmu418_vgt<int>(maskResult, veca, vecb, mask); }

template <typename T>
void _cmu418_vlt(__cmu418_mask &maskResult, __cmu418_vec<T> &veca, __cmu418_vec<T> &vecb, __cmu418_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    maskResult.value[i] = mask.value[i] ? (veca.value[i] < vecb.value[i]) : maskResult.value[i];
  }
  CMU418Logger.addLog("vlt", mask, VECTOR_WIDTH);
}

template void _cmu418_vlt<float>(__cmu418_mask &maskResult, __cmu418_vec_float &veca, __cmu418_vec_float &vecb, __cmu418_mask &mask);
template void _cmu418_vlt<int>(__cmu418_mask &maskResult, __cmu418_vec_int &veca, __cmu418_vec_int &vecb, __cmu418_mask &mask);

void _cmu418_vlt_float(__cmu418_mask &maskResult, __cmu418_vec_float &veca, __cmu418_vec_float &vecb, __cmu418_mask &mask) { _cmu418_vlt<float>(maskResult, veca, vecb, mask); }
void _cmu418_vlt_int(__cmu418_mask &maskResult, __cmu418_vec_int &veca, __cmu418_vec_int &vecb, __cmu418_mask &mask) { _cmu418_vlt<int>(maskResult, veca, vecb, mask); }

template <typename T>
void _cmu418_veq(__cmu418_mask &maskResult, __cmu418_vec<T> &veca, __cmu418_vec<T> &vecb, __cmu418_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    maskResult.value[i] = mask.value[i] ? (veca.value[i] == vecb.value[i]) : maskResult.value[i];
  }
  CMU418Logger.addLog("veq", mask, VECTOR_WIDTH);
}

template void _cmu418_veq<float>(__cmu418_mask &maskResult, __cmu418_vec_float &veca, __cmu418_vec_float &vecb, __cmu418_mask &mask);
template void _cmu418_veq<int>(__cmu418_mask &maskResult, __cmu418_vec_int &veca, __cmu418_vec_int &vecb, __cmu418_mask &mask);

void _cmu418_veq_float(__cmu418_mask &maskResult, __cmu418_vec_float &veca, __cmu418_vec_float &vecb, __cmu418_mask &mask) { _cmu418_veq<float>(maskResult, veca, vecb, mask); }
void _cmu418_veq_int(__cmu418_mask &maskResult, __cmu418_vec_int &veca, __cmu418_vec_int &vecb, __cmu418_mask &mask) { _cmu418_veq<int>(maskResult, veca, vecb, mask); }

template <typename T>
void _cmu418_hadd(__cmu418_vec<T> &vecResult, __cmu418_vec<T> &vec) {
  for (int i=0; i<VECTOR_WIDTH/2; i++) {
    T result = vec.value[2*i] + vec.value[2*i+1];
    vecResult.value[2 * i] = result;
    vecResult.value[2 * i + 1] = result;
  }
}

template void _cmu418_hadd<float>(__cmu418_vec_float &vecResult, __cmu418_vec_float &vec);

void _cmu418_hadd_float(__cmu418_vec_float &vecResult, __cmu418_vec_float &vec) { _cmu418_hadd<float>(vecResult, vec); }

template <typename T>
void _cmu418_interleave(__cmu418_vec<T> &vecResult, __cmu418_vec<T> &vec) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    int index = i < VECTOR_WIDTH/2 ? (2 * i) : (2 * (i - VECTOR_WIDTH/2) + 1);
    vecResult.value[i] = vec.value[index];
  }
}

template void _cmu418_interleave<float>(__cmu418_vec_float &vecResult, __cmu418_vec_float &vec);

void _cmu418_interleave_float(__cmu418_vec_float &vecResult, __cmu418_vec_float &vec) { _cmu418_interleave<float>(vecResult, vec); }

void addUserLog(const char * logStr) {
  CMU418Logger.addLog(logStr, _cmu418_init_ones(), 0);
}

