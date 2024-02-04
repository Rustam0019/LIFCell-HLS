#include "lif_param.h"

lif_param::lif_param(){}

lif_param::lif_param(ap_fixed<32,16> tau_syn_inv = 200.0,
                ap_fixed<32,16> tau_mem_inv = 100.0,
                ap_fixed<32,16> v_leak = 0.0,
                ap_fixed<32,16> v_th = 1.0,
                ap_fixed<32,16> v_reset = 0.0,
                //const char method[10] = "super",
                ap_fixed<32,16> alpha = 100.0)
{
     this->tau_syn_inv = tau_syn_inv;
     this->tau_mem_inv = tau_mem_inv;
     this->v_leak = v_leak;
     this->v_th = v_th;
     this->v_reset = v_reset;
     //this->method = method;
     this->alpha = alpha;

}
