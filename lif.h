#ifndef LIF_H
#define LIF_H

#include "lif_param.h"
#include "lfs.h"

class LIFCell{
    public:
        LIFCell(lif_param p);

        //template<size_t N, size_t M>
        void initial_state();
        //template<int M>
        void calc(hls::stream<ap_fixed<32, 16>> &input_stream, hls::stream<ap_uint<4>> &output_stream, lif_param p);

    private:
        lif_param pr;

};

#endif
