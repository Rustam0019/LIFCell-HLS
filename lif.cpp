#include "lif.h"

LIFCell::LIFCell(lif_param p)
{
     pr.tau_syn_inv = p.tau_syn_inv;
     pr.tau_mem_inv = p.tau_mem_inv;
     pr.v_leak = p.v_leak;
     pr.v_th = p.v_th;
     pr.v_reset = p.v_reset;
     pr.alpha = p.alpha;

}

//template<size_t N, size_t M>
LIFFeedForwardState LIFCell::initial_state(){
     ap_fixed<32,16> v[5][2];
     ap_fixed<32,16> i[5][2];

     for (int k = 0; k < 5; ++k) {
            for (int j = 0; j < 2; ++j) {
                i[k][j] = 0;
                v[k][j] = pr.v_leak;
            }
        }

     LIFFeedForwardState state(v,i);

     return state;
}
