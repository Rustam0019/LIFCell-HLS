#ifndef LIF_PARAM
#define LIF_PARAM

#define M 10
#include <ap_fixed.h>

class lif_param{
    public:
        lif_param();
        lif_param(ap_fixed<32,16> tau_syn_inv,
               ap_fixed<32,16> tau_mem_inv,
               ap_fixed<32,16> v_leak,
               ap_fixed<32,16> v_th,
               ap_fixed<32,16> v_reset,
               ap_fixed<32,16> alpha
        );


        ap_fixed<32,16> tau_syn_inv;
        ap_fixed<32,16> tau_mem_inv;
        ap_fixed<32,16> v_leak;
        ap_fixed<32,16> v_th;
        ap_fixed<32,16> v_reset;
        ap_fixed<32,16> alpha;

};

#endif
