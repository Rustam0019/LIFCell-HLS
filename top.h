#ifndef TOP_H
#define TOP_H


#include <ap_int.h>
#include <ap_fixed.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "lif.h"
#include "data_types.h"

void top_f(hls::stream<din_8> &input_stream, hls::stream<din_2> &output_stream);

#endif
