
#include <ap_int.h>
#include <ap_fixed.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "lif.h"




void top_f(hls::stream<ap_fixed<32, 16>> &input_stream, hls::stream<ap_fixed<32, 16>> &output_stream) {



	    lif_param p(ap_fixed<32, 16>(200.0),
	    			ap_fixed<32, 16> (100.0),
					ap_fixed<32, 16> (0.0),
					ap_fixed<32, 16> (1.0),
					ap_fixed<32, 16> (0.0),
					ap_fixed<32, 16>(100.0)
					);
	    LIFCell l(p);


		l.calc(input_stream, output_stream, p);

}

