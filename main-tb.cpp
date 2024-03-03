#include "main-tb.h"


void arrayToStream(din_8 arr[M], hls::stream<din_8>& input_stream) {

    for (int i = 0; i < M; ++i) {
    	input_stream.write(arr[i]);
    }
}

int main() {

	int status = 0;



//	din_10 data[M] = { 0.4349, 0.4579,
//		                           0.2204, 0.3197,
//		                           0.6553, 0.3135,
//		                           0.9603, 0.5636,   // 1d array
//		                           0.9445, 0.6054 };


	din_8 data[M] = 	{-0.1275,  1.0850,  1.1706,  0.6911, -1.0093, -0.3453,  0.4496,  0.3735,
								  0.5290, -0.1385,
								 1.1778,  0.3190,  0.0250, -1.6974,  1.3271, -1.1673,  0.7690, -0.2278,
								  1.0657,  1.4825,
								-0.7259, -1.3599, -0.7988, -0.1788,  0.9070,  0.8914, -1.3225,  1.2517,
								 -1.0614,  0.1967,
								-0.9897,  0.1132,  1.8821, -1.5708,  0.5735, -0.6633,  0.1611,  3.1482,
								  0.4047, -2.0186,
								-0.3786,  1.5728,  0.1792,  0.8038, -2.6131,  0.0814,  0.4212,  0.1536,
								  1.7478, -0.4660,
								 1.0880,  1.4890, -0.0470,  0.4425,  1.0394, -0.6182, -1.6549,  1.4933,
								 -1.4083,  0.5717,
								 1.7876,  1.2907,  0.0239,  0.3989, -1.7468, -0.8827,  0.9700, -0.3688,
								  0.9276, -1.1989,
								 2.3598, -1.5015, -1.0639,  0.2363,  0.2574, -1.7734,  0.5262, -0.1707,
								 -0.1130,  1.2934};



	    hls::stream<din_8> input_stream;
		hls::stream<din_2> output_stream;

		arrayToStream(data, input_stream);
		top_f(input_stream, output_stream);


	std::ifstream refFile("reference_data1.txt");
	    if (!refFile.is_open()) {
	        std::cerr << "Failed to open reference data file." << std::endl;
	        return -1;
	    }

	    din_2 out_val[M];

		for (int k = 0; k < M; ++k) {

				din_2 refValue;
				refFile >> refValue;
				if(output_stream.read_nb(out_val[k])){
					std::cout << out_val[k] << " ";
					if(k % 10 == 0 && k > 0){
						std::cout << std::endl;
					}
					if ( out_val[k] != refValue) {
						std::cout << "Mismatch at [" << k << "]: HLS output = "
								  << out_val[k] << ", Reference output = " << refValue << std::endl;
						status = 1;
					}
				}

		}

	    refFile.close();

	std::cout << std::endl;
	if (status == 0) {
		std::cout << "Test Passed" << std::endl;
	} else {
		std::cout << "Test Failed" << std::endl;
	}

	return status;
}
