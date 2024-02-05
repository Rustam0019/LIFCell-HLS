#ifndef LFS_H
#define LFS_H

#include "lif_param.h"

#define ArraySize1 10
#define ArraySize2 5
#define ArraySize3 2

struct v_and_i_get {
        ap_fixed<32,16> vv[5][2];
        ap_fixed<32,16> i_array[ArraySize1][ArraySize2];
        };

class LIFFeedForwardState{
    public:

        LIFFeedForwardState();
        //template<size_t N, size_t M>
        LIFFeedForwardState(ap_fixed<32,16> v[5][2], ap_fixed<32,16> i[5][2]);
        //template<size_t N, size_t M>
        void lif_feed_forward_step(ap_fixed<32,16> input_tn[5][2], ap_fixed<32,16> (&output_arr)[10][5][2],
                                                                    LIFFeedForwardState st,
                                                                    lif_param p,
                                                                    ap_fixed<32,16> dt);

        v_and_i_get get();
        void set(ap_fixed<32,16> v1[5][2], ap_fixed<32,16> i1[5][2]);

    private:
        ap_fixed<32,16> v[5][2];
        ap_fixed<32,16> i[5][2];

};

#endif
