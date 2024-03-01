#include "lfs.h"


LIFFeedForwardState::LIFFeedForwardState(){}
LIFFeedForwardState::LIFFeedForwardState(ap_fixed<32,16> v[M], ap_fixed<32,16> i[M]){
    for (int k = 0; k < M; ++k) {
                this->i[k] = i[k];
                this->v[k] = v[k];
        }
}


//void LIFFeedForwardState::set(ap_fixed<32,16> v[10], ap_fixed<32,16> i[10]){
//    for (int k = 0; k < 10; ++k) {
//                i[k] = i1[k];
//                v[k] = v1[k];
//        }
//}
//
//
//v_and_i_get LIFFeedForwardState::get(){
//            v_and_i_get v_and_i_g;
//            for (int k = 0; k < 10; ++k) {
//                    v_and_i_g.i_array[k] = i[k];
//                    v_and_i_g.vv[k] = v[k];
//            }
//            return v_and_i_g;
//        }


//template<int M>
void LIFFeedForwardState::lif_feed_forward_step(hls::stream<ap_fixed<32, 16>> &input_stream, hls::stream<ap_uint<4>> &output_stream,
                                                                              //LIFFeedForwardState st,
                                                                              lif_param p,
                                                                              ap_fixed<32,16> dt = 0.001)
{

    ap_fixed<32,16> v_new[M] = {0.0};
    ap_fixed<32,16> i_new[M] = {0.0};
    ap_uint<4> str_element = 0.0;
    ap_fixed<32,16> dst[M] = {0.0};

    int i = 0;
    	while(!input_stream.empty()){
    		input_stream.read(dst[i]);
    		i++;
    	}

		for (int n = 0; n < M; n++)
		{
			/* code */
			for (int k = 0; k < M; ++k) {


					   // dv[k] = dt * p.tau_mem_inv * ((p.v_leak - v1[k]) + i1[k]);

					   //v_decayed[k] = v1[k] + dt * p.tau_mem_inv * ((p.v_leak - v1[k]) + i1[k]);

					   //di[k] = -dt * p.tau_syn_inv * i1[k];

					   //i_decayed[k] = i1[k] + (-dt * p.tau_syn_inv * i1[k]);

					   //x[k] = v1[k] + dt * p.tau_mem_inv * ((p.v_leak - v1[k]) + i1[k]) - p.v_th;

					   if((v_new[k] + dt * p.tau_mem_inv * ((p.v_leak - v_new[k]) + i_new[k]) - p.v_th) > 0){
									   if(n == 9){
						   	   	   	   output_stream.write(1.0);
									   }
									   str_element = 1.0;
					   }
					   else{
									   if(n == 9){
									   output_stream.write(0.0);
									   }
									   str_element = 0.0;
					  }

					  v_new[k] =(1 - str_element) * (v_new[k] + dt * p.tau_mem_inv * ((p.v_leak - v_new[k]) + i_new[k])) + str_element * p.v_reset;

					  i_new[k] = i_new[k] + (-dt * p.tau_syn_inv * i_new[k]) + dst[k];
				}

			}
}
