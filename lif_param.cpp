#include "lif_param.h"

lif_param::lif_param(){}

lif_param::lif_param(ap_fixed<32,16> tau_syn_inv,
                ap_fixed<32,16> tau_mem_inv,
                ap_fixed<32,16> v_leak,
                ap_fixed<32,16> v_th,
                ap_fixed<32,16> v_reset,
                ap_fixed<32,16> alpha)
{
     this->tau_syn_inv = tau_syn_inv;
     this->tau_mem_inv = tau_mem_inv;
     this->v_leak = v_leak;
     this->v_th = v_th;
     this->v_reset = v_reset;
     this->alpha = alpha;

}
