#include <ap_int.h>
#include <ap_fixed.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "lif.h"



void top_f(ap_fixed<32, 16> (&output_arr) [10][5][2]) {



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

	    LIFFeedForwardState state;
	    state = l.initial_state();



	    state.lif_feed_forward_step(data, output_arr, state, p, 0.001);

}

