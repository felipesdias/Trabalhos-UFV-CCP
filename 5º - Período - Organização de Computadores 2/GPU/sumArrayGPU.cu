#include <stdio.h>
#include <iostream>

__global__
void sumArrayGPU(int n, float *I, float *R, float *C, int vet) {

  int i = blockIdx.x * blockDim.x + threadIdx.x; 

  if(vet == 1)
  	i = I[i];
  else
    i = R[i];

  if (i < n)
    C[i] = I[i] + R[i];

}

int main(int argc, char const *argv[]) {

  srand((unsigned) time(NULL));	

  long N = 1 << (argc > 1 ? atol(argv[1]) : 20);
  int block_aux = argc > 2 ? atoi(argv[2]) : 512;
  int unroll = argc > 3 ? atoi(argv[3]) : 1;
  int vet = argc > 4 ? atoi(argv[4]) : 1;

  int n = N / sizeof(float);

std::cout << N << std::endl << n << std::endl << std::endl;

  float *I, *R, *C, *d_I, *d_R, *d_C;

  I = new float[n];
  R = new float[n];
  C = new float[n];
  
  cudaMalloc(&d_I, N);
  cudaMalloc(&d_R, N);
  cudaMalloc(&d_C, N);

  for (int i = 0; i < n; i++) {
    I[i] = i + 0.0f;
    R[i] = (float)( rand() & 0xFF ) / 10.0f;
	C[i] = 0;
  }

  cudaMemcpy(d_I, I, N, cudaMemcpyHostToDevice);
  cudaMemcpy(d_R, R, N, cudaMemcpyHostToDevice);
  cudaMemcpy(d_C, C, N, cudaMemcpyHostToDevice);

  dim3 block (block_aux);
  dim3 grid  ((n + block.x - 1) / block.x);

  sumArrayGPU<<<grid, block>>>(n, d_I, d_R, d_C, vet);

  cudaMemcpy(C, d_C, N, cudaMemcpyDeviceToHost);

  printf("Soma executada com sucesso");

}
