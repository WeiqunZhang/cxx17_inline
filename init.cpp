#include "init.H"
#include "par.H"

#if defined(__HIP__)
#include <hip/hip_runtime.h>
#endif

#include <array>

void init ()
{
    int h_a = 1;
    std::array<int,2> h_b{2,3};

#if defined(__CUDACC__)
    cudaMemcpyToSymbol(d_a, &h_a, sizeof(int));
    cudaMemcpyToSymbol(d_b, h_b.data(), sizeof(int)*h_b.size());
    cudaDeviceSynchronize();
#else
    hipMemcpyToSymbol(d_a, &h_a, sizeof(int));
    hipMemcpyToSymbol(d_b, h_b.data(), sizeof(int)*h_b.size());
    hipDeviceSynchronize();
#endif
}
