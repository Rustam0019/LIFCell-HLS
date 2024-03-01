#include "main-tb.h"


void arrayToStream(ap_fixed<32, 16> arr[M], hls::stream<ap_fixed<32, 16>>& input_stream) {

    for (int i = 0; i < M; ++i) {
    	input_stream.write(arr[i]);
    }
}

int main() {

	int status = 0;



	ap_fixed<32, 16> data[M] = { 0.4349, 0.4579,
		                           0.2204, 0.3197,
		                           0.6553, 0.3135,
		                           0.9603, 0.5636,   // 1d array
		                           0.9445, 0.6054 };


//	ap_fixed<32, 16> data[5][2] = {{ 1.0751, -0.9220},
//			                                        {-1.2928, -0.1836},
//			                                         { 2.8694,  0.3140},
//			                                         { 0.0951, -0.9657},
//			                                         { 1.4173,  1.3812}};

//	    lif_param p(ap_fixed<32, 16>(200.0),
//	    			ap_fixed<32, 16> (100.0),
//					ap_fixed<32, 16> (0.0),
//					ap_fixed<32, 16> (1.0),
//					ap_fixed<32, 16> (0.0),
//					ap_fixed<32, 16>(100.0)
//					);
//	    LIFCell l(p);
//
//	    //ap_fixed<32, 16> output_arr[M];
	    hls::stream<ap_fixed<32, 16>> input_stream;
		hls::stream<ap_uint<4>> output_stream;

		arrayToStream(data, input_stream);
		top_f(input_stream, output_stream);

//	    l.calc(input_stream, output_stream, p);


	std::ifstream refFile("reference_data.txt");
	    if (!refFile.is_open()) {
	        std::cerr << "Failed to open reference data file." << std::endl;
	        return -1;
	    }

//	    for (int k = 0; k < 10; ++k) {
//
//				ap_fixed<32, 16> refValue;
//				refFile >> refValue;
//				if (output_arr[k]!= refValue) {
//					std::cout << "Mismatch at [" << k << "]: HLS output = "
//							  << output_arr[k] << ", Reference output = " << refValue << std::endl;
//					status = 1;
//			}
//	    }
//	    std::cout <<  "Output: ";
//	    for (int k = 0; k < 10; ++k) {
//	    	//std::cout << "Iteration: " << k << std::endl;
//			std::cout << output_arr[k] << " ";
//
//			//std::cout <<  std::endl;
//	    	}


	    ap_uint<4> out_val[M];

		for (int k = 0; k < 10; ++k) {

				ap_uint<4> refValue;
				refFile >> refValue;
				if(output_stream.read_nb(out_val[k])){
					std::cout << out_val[k] << " ";
					if ( out_val[k] != refValue) {
						std::cout << "Mismatch at [" << k << "]: HLS output = "
								  << out_val[k] << ", Reference output = " << refValue << std::endl;
						status = 1;
					}
				}

		}

	    refFile.close();


	if (status == 0) {
		std::cout << "Test Passed" << std::endl;
	} else {
		std::cout << "Test Failed" << std::endl;
	}

	return status;
}
