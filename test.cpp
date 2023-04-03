#include "cuda_runtime.h"
#include "device_launch_parameters.h"
 
#include <iostream>
#include <stdio.h>
#include <cuComplex.h>
#include <cstdint>
 
 
int main()
{
   //Create size of data...
   const int uint_16_t_2_size = sizeof(uint16_t) * 2;
   const int float2_size = sizeof(cuComplex);
   const int MAX_ARRAY_SIZE = 40960000; // Create MAX size.
 
   const int final_data_size = 2000000; // 2,000,000 not 200,000
 
   //create device ptrs
   void* d_final_result_int2;
   void* d_final_result_float2;
 
   //allocate MAX data memory on device
   cudaMalloc(&d_final_result_int2, MAX_ARRAY_SIZE * uint_16_t_2_size);
   cudaMalloc(&d_final_result_float2, MAX_ARRAY_SIZE * float2_size);
 
   //allocate host memory
   void* h_final_int_result = new int2[final_data_size];
   void* h_final_float_result = new cuComplex[final_data_size];
 
   //Set memory on device to something
   cudaMemset(d_final_result_int2, 5, MAX_ARRAY_SIZE * uint_16_t_2_size);
   cudaMemset(d_final_result_float2, 42, MAX_ARRAY_SIZE * float2_size);
 
   //memcpy final_data_size down from device to host...
   cudaMemcpy(h_final_int_result, d_final_result_int2, final_data_size * uint_16_t_2_size, cudaMemcpyDeviceToHost); //~8M of data
 
   cudaMemcpy(h_final_float_result, d_final_result_float2, final_data_size * float2_size, cudaMemcpyDeviceToHost); //~16M of data.


	std::cout << "unit2 size = " << uint_16_t_2_size << std::endl;
	std::cout << "memcpy size = " << final_data_size * uint_16_t_2_size << std::endl;
	std::cout << "f2 size = " << float2_size << std::endl;
	std::cout << "memcpy size = " << final_data_size * float2_size << std::endl;

	const unsigned int i = 1;
	std::cout << "size uint = " << sizeof(i) << std::endl;
	const float f = 1.0;
	std::cout << "size float = " << sizeof(f) << std::endl;
	//std::cout << h_final_int_result[0] << std::endl;

	std::cout << "done!" << std::endl;
 
	return 0;
}


