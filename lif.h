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
        void calc(hls::stream<din_8> &input_stream, hls::stream<din_1> &output_stream, lif_param p);

    private:
        lif_param pr;

};

#endif
