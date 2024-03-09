#include "lfs.h"


LIFFeedForwardState::LIFFeedForwardState(){}
LIFFeedForwardState::LIFFeedForwardState(din_10 v[M], din_10 i[M]){
    for (int k = 0; k < M; ++k) {
                this->i[k] = i[k];
                this->v[k] = v[k];
        }
}


//void LIFFeedForwardState::set(din_10 v[10], din_10 i[10]){
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
void LIFFeedForwardState::lif_feed_forward_step(hls::stream<din_8> &input_stream, hls::stream<din_1> &output_stream,
                                                                              //LIFFeedForwardState st,
                                                                              lif_param p,
																			  din_10 dt = 0.001)
{

	din_8 v_new[M] = {0.0};
	din_8 i_new[M] = {0.0};
    din_1 str_element = 0.0;
    din_8 dst[M] = {0.0};


//		for(i = 0; i < M; i++){
//			if(!input_stream.empty()){
//				input_stream.read(dst[i]);
//			}
//		}


		for (int n = 0; n < 10; n++)
		{
			/* code */
			for (int k = 0; k < M; ++k) {
			#pragma HLS PIPELINE
				if(!input_stream.empty() && n==0){
						input_stream.read(dst[k]);

				}
			   // dv[k] = dt * p.tau_mem_inv * ((p.v_leak - v1[k]) + i1[k]);

			   //v_decayed[k] = v1[k] + dt * p.tau_mem_inv * ((p.v_leak - v1[k]) + i1[k]);

			   //di[k] = -dt * p.tau_syn_inv * i1[k];

			   //i_decayed[k] = i1[k] + (-dt * p.tau_syn_inv * i1[k]);

			   //x[k] = v1[k] + dt * p.tau_mem_inv * ((p.v_leak - v1[k]) + i1[k]) - p.v_th;

			   if((v_new[k] + dt * p.tau_mem_inv * ((p.v_leak - v_new[k]) + i_new[k]) - p.v_th) > 0){
							   str_element = 1.0;
			   }
			   else{
							   str_element = 0.0;
			  }

			  v_new[k] =(1 - str_element) * (v_new[k] + dt * p.tau_mem_inv * ((p.v_leak - v_new[k]) + i_new[k])) + str_element * p.v_reset;

			  i_new[k] = i_new[k] + (-dt * p.tau_syn_inv * i_new[k]) + dst[k];

			  if(n == 9){
				  output_stream.write(str_element);
		   }
		}
	}
}
