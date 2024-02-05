#include "lfs.h"



LIFFeedForwardState::LIFFeedForwardState(){}
LIFFeedForwardState::LIFFeedForwardState(ap_fixed<32,16> v[5][2], ap_fixed<32,16> i[5][2]){
    for (int k = 0; k < 5; ++k) {
            for (int j = 0; j < 2; ++j) {
                this->i[k][j] = i[k][j];
                this->v[k][j] = v[k][j];
            }
        }
}


void LIFFeedForwardState::set(ap_fixed<32,16> v1[5][2], ap_fixed<32,16> i1[5][2]){
    for (int k = 0; k < 5; ++k) {
            for (int j = 0; j < 2; ++j) {
                i[k][j] = i1[k][j];
                v[k][j] = v1[k][j];
            }
        }
}


v_and_i_get LIFFeedForwardState::get(){
            v_and_i_get v_and_i_g;
            for (int k = 0; k < 5; ++k) {
                for (int j = 0; j < 2; ++j) {
                    v_and_i_g.i_array[k][j] = i[k][j];
                    v_and_i_g.vv[k][j] = v[k][j];
                }
            }
            return v_and_i_g;
        }

//template<size_t N, size_t M>
void LIFFeedForwardState::lif_feed_forward_step(ap_fixed<32,16> input_tn[5][2], ap_fixed<32,16> (&output_arr)[10][5][2],
                                                                              LIFFeedForwardState st,
                                                                              lif_param p,
                                                                              ap_fixed<32,16> dt = 0.0001)
{

	#pragma HLS INTERFACE ap_none port=input_tn // check axi interface
	#pragma HLS INTERFACE ap_none port=st
	#pragma HLS INTERFACE ap_none port=p
	#pragma HLS INTERFACE ap_none port=dt
	#pragma HLS INTERFACE ap_ctrl_none port=return
    // 10 times data and state should be calculated here
    //ap_fixed<32,16> z_new, v_new, i_new;
    ap_fixed<32,16> dv[5][2];
    ap_fixed<32,16> v_decayed[5][2];
    ap_fixed<32,16> di[5][2];
    ap_fixed<32,16> i_decayed[5][2];
    ap_fixed<32,16> z_new[5][2];
    ap_fixed<32,16> v_new[5][2];
    ap_fixed<32,16> i_new[5][2];


    ap_fixed<32,16> v1[5][2];
    ap_fixed<32,16> i1[5][2];

    for (int n = 0; n < 10; n++)
    {
        /* code */
    	ap_fixed<32,16> x[5][2];
        v_and_i_get v_and_i_g = st.get();
        for (int k = 0; k < 5; ++k) {
                for (int j = 0; j < 2; ++j) {
                   i1[k][j] = v_and_i_g.i_array[k][j];

                   v1[k][j] = v_and_i_g.vv[k][j];

                   dv[k][j] = dt * p.tau_mem_inv * ((p.v_leak - v1[k][j]) + i1[k][j]);

                   v_decayed[k][j] = v1[k][j] + dv[k][j];

                   di[k][j] = -dt * p.tau_syn_inv * i1[k][j];

                   i_decayed[k][j] = i1[k][j] + di[k][j];

                   x[k][j] = v_decayed[k][j] - p.v_th;

                   if(x[k][j] > 0){
								   z_new[k][j] = 1.0;
                   }
                   else{
								   z_new[k][j] = 0.0;
				  }

                  v_new[k][j] =(1 - z_new[k][j]) * v_decayed[k][j] + z_new[k][j] * p.v_reset;

                  i_new[k][j] = i_decayed[k][j] + input_tn[k][j];

                  output_arr[n][k][j] = z_new[k][j];
                }
            }

    st.set(v_new, i_new);
    }
}
