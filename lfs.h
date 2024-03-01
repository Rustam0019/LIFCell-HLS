#ifndef LFS_H
#define LFS_H

#include "lif_param.h"
#include <hls_stream.h>


//struct v_and_i_get {
//        ap_fixed<32,16> vv[10];
//        ap_fixed<32,16> i_array[10];
//        };


class LIFFeedForwardState{
    public:

        LIFFeedForwardState();
        LIFFeedForwardState(ap_fixed<32,16> v[M], ap_fixed<32,16> i[M]);


        v_and_i_get get();
        void set(ap_fixed<32,16> v[M], ap_fixed<32,16> i[M]);

        //template<int M>
        void lif_feed_forward_step(hls::stream<ap_fixed<32, 16>> &input_stream, hls::stream<ap_fixed<32, 16>> &output_stream,
                                                                            //LIFFeedForwardState st,
                                                                            lif_param p,
                                                                            ap_fixed<32,16> dt);

    private:
        ap_fixed<32,16> v[M];
        ap_fixed<32,16> i[M];

};


#endif
