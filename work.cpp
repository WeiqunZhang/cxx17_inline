#include "work.H"
#include "par.H"

#if defined(__HIP__)
#include <hip/hip_runtime.h>
#endif

#include <iostream>

template <class F> __global__ void launch_global (F f) { f(); }

void work ()
{
    int* p = nullptr;
#if defined(__CUDACC__)
    cudaHostAlloc((void**)&(p), sizeof(int)*3, cudaHostAllocMapped);
#else
    hipHostMalloc((void**)&(p), sizeof(int)*3, hipHostMallocMapped);
#endif

    launch_global<<<1,1>>>([=] __device__ ()
    {
        p[0] = d_a;
        p[1] = d_b[0];
        p[2] = d_b[1];
    });

#if defined(__CUDACC__)
    cudaDeviceSynchronize();
#else
    hipDeviceSynchronize();
#endif

    if (p[0] == 1 && p[1] == 2 && p[2] == 3) {
        std::cout << "Pass." << std::endl;
    } else {
        std::cout << "Fail. It should print 1, 2, 3. Instead it prints "
              << p[0] << ", " << p[1] << ", " << p[2] << std::endl;
    }

#if defined(__CUDACC__)
    cudaFreeHost(p);
#else
    hipHostFree(p);
#endif
}
