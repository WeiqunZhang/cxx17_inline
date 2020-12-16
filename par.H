#ifndef FOO_H_
#define FOO_H_

#if defined(USE_INLINE_CONSTANT)
inline __constant__ int d_a;
inline __constant__ int d_b[2];
#else
inline __device__ int d_a;
inline __device__ int d_b[2];
#endif

#endif
