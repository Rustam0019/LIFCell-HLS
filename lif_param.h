#ifndef LIF_PARAM
#define LIF_PARAM

#define M 80
#include "data_types.h"

class lif_param{
    public:
        lif_param();
        lif_param(din_10 tau_syn_inv,
               din_10 tau_mem_inv,
               din_10 v_leak,
               din_10 v_th,
               din_10 v_reset,
               din_10 alpha
        );


        din_10 tau_syn_inv;
        din_10 tau_mem_inv;
        din_10 v_leak;
        din_10 v_th;
        din_10 v_reset;
        din_10 alpha;

};

#endif
