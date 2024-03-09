#ifndef LFS_H
#define LFS_H

#include "lif_param.h"
#include <hls_stream.h>


//struct v_and_i_get {
//        din_10 vv[10];
//        din_10 i_array[10];
//        };


class LIFFeedForwardState{
    public:

        LIFFeedForwardState();
        LIFFeedForwardState(din_10 v[M], din_10 i[M]);


        //v_and_i_get get();
        //void set(din_10 v[M], din_10 i[M]);

        //template<int M>
        void lif_feed_forward_step(hls::stream<din_8> &input_stream, hls::stream<din_1> &output_stream,
                                                                            //LIFFeedForwardState st,
                                                                            lif_param p,
																			din_10 dt);

    private:
        din_10 v[M];
        din_10 i[M];

};


#endif
