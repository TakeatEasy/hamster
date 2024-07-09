#include "NumCpp.hpp"
#include <cuda_runtime.h>
#include <cstdlib>
#include <iostream>
 
__global__ void add_vectors(int *d_a) {
    d_a[threadIdx.x] += 1;
}

int main()
{
    auto a = nc::random::randInt<int>({10, 10}, 0, 100);
    std::cout << a;

    int* d_a;
    cudaMalloc(&d_a, sizeof(int) * 100);
    cudaMemcpy(d_a, a.data(), 100*sizeof(int), cudaMemcpyHostToDevice);

    add_vectors<<<1, 100>>>(d_a);
    cudaMemcpy(a.data(), d_a, 100*sizeof(int), cudaMemcpyDeviceToHost);
    std::cout << "After kernel\n";
    std::cout << a;
    cudaFree(d_a);
 
    return EXIT_SUCCESS;
}
