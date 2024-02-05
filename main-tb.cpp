#include "main-tb.h"


int main() {

	int status = 0;


	ap_fixed<32, 16> data[5][2] = {{ 0.4349, 0.4579},
	                            {0.2204, 0.3197},
	                            {0.6553, 0.3135},
	                            {0.9603, 0.5636},
	                            {0.9445, 0.6054}};

//	ap_fixed<32, 16> data[5][2] = {{ 1.0751, -0.9220},
//			                                        {-1.2928, -0.1836},
//			                                         { 2.8694,  0.3140},
//			                                         { 0.0951, -0.9657},
//			                                         { 1.4173,  1.3812}};

	    lif_param p(ap_fixed<32, 16>(200.0),
	    			ap_fixed<32, 16> (100.0),
					ap_fixed<32, 16> (0.0),
					ap_fixed<32, 16> (1.0),
					ap_fixed<32, 16> (0.0),
					ap_fixed<32, 16>(100.0)
					);
	    LIFCell l(p);
	    ap_fixed<32, 16> output_arr[10][5][2];
	    LIFFeedForwardState state;
	    state = l.initial_state();



	    state.lif_feed_forward_step(data, output_arr, state, p, 0.001);


	std::ifstream refFile("reference_data.txt");
	    if (!refFile.is_open()) {
	        std::cerr << "Failed to open reference data file." << std::endl;
	        return -1;
	    }

	    for (int k = 0; k < 10; ++k) {
			for (int i = 0; i < 5; ++i) {
				for (int j = 0; j < 2; ++j) {
					ap_fixed<32, 16> refValue;
					refFile >> refValue;
					if (output_arr[k][i][j] != refValue) {
						std::cout << "Mismatch at [" << k << "][" << i << "][" << j << "]: HLS output = "
								  << output_arr[k][i][j] << ", Reference output = " << refValue << std::endl;
						status = 1;
					}
				}
			}
	    }
	    for (int k = 0; k < 10; ++k) {
	    	std::cout << "Iteration: " << k << std::endl;
			for (int i = 0; i < 5; ++i) {
						for (int j = 0; j < 2; ++j) {
								std::cout << output_arr[k][i][j] << " ";

						}
						std::cout <<  std::endl;
					}
			std::cout <<  std::endl;
	    	}

	    refFile.close();


	if (status == 0) {
		std::cout << "Test Passed" << std::endl;
	} else {
		std::cout << "Test Failed" << std::endl;
	}

	return status;
}
