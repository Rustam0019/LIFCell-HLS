#ifndef TOP_H
#define TOP_H


#include <ap_int.h>
#include <ap_fixed.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "lif.h"
#include "data_types.h"


void arrayToStream(din_8 *arr, hls::stream<din_8>& input_stream);

void streamToArray(hls::stream<din_1> &output_stream, din_1 *arr);

void top_f(din_8 *data_in, din_1 *data_out);

#endif
