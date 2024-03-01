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


//void LIFCell::initial_state(){
////     ap_fixed<32,16> v[10] = {pr.v_leak};
////     ap_fixed<32,16> i[10] = {0};
//
//     //LIFFeedForwardState state(v,i);
//
//     //return state;
//}


//template<int M>
void LIFCell::calc(hls::stream<ap_fixed<32, 16>> &input_stream, hls::stream<ap_fixed<32, 16>> &output_stream, lif_param p){
	LIFFeedForwardState state;

	state.lif_feed_forward_step(input_stream, output_stream, p, 0.001);
}

