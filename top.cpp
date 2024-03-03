#include "top.h"




void top_f(hls::stream<din_8> &input_stream, hls::stream<din_2> &output_stream) {





	    lif_param p(din_10(200.0),
	    			din_10 (100.0),
					din_10 (0.0),
					din_10 (1.0),
					din_10 (0.0),
					din_10(100.0)
					);
	    LIFCell l(p);


		l.calc(input_stream, output_stream, p);

}

