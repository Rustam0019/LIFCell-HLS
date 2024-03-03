#include "lif_param.h"

lif_param::lif_param(){}

lif_param::lif_param(din_10 tau_syn_inv,
                din_10 tau_mem_inv,
                din_10 v_leak,
                din_10 v_th,
                din_10 v_reset,
                din_10 alpha)
{
     this->tau_syn_inv = tau_syn_inv;
     this->tau_mem_inv = tau_mem_inv;
     this->v_leak = v_leak;
     this->v_th = v_th;
     this->v_reset = v_reset;
     this->alpha = alpha;

}
