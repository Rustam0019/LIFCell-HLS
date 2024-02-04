#include "lfs.h"

//using znew = std::array<int, 10>;
//using v_and_i = std::array<std::array<int, 2>, 5>;


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
outp LIFFeedForwardState::lif_feed_forward_step(ap_fixed<32,16> input_tn[5][2],
                                                                              LIFFeedForwardState st,
                                                                              lif_param p,
                                                                              ap_fixed<32,16> dt = 0.0001)
{

	#pragma HLS INTERFACE ap_none port=input_tn
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
    //torch::Tensor v1, i1;

    ap_fixed<32,16> v1[5][2];
    ap_fixed<32,16> i1[5][2];
    outp o;

    for (int n = 0; n < 10; n++)
    {
        /* code */
        v_and_i_get v_and_i_g = st.get();
        for (int k = 0; k < 5; ++k) {
                for (int j = 0; j < 2; ++j) {
                   i1[k][j] = v_and_i_g.i_array[k][j];
                   v1[k][j] = v_and_i_g.vv[k][j];
                }
            }

    for (int k = 0; k < 5; ++k) {
                for (int j = 0; j < 2; ++j) {
                   dv[k][j] = dt * p.tau_mem_inv * ((p.v_leak - v1[k][j]) + i1[k][j]);
                }
            }
    //dv = dt * p.tau_mem_inv * ((p.v_leak - v1) + i1);

    for (int k = 0; k < 5; ++k) {
                for (int j = 0; j < 2; ++j) {
                   v_decayed[k][j] = v1[k][j] + dv[k][j];
                }
            }
    //v_decayed = v1 + dv;

    for (int k = 0; k < 5; ++k) {
                for (int j = 0; j < 2; ++j) {
                   di[k][j] = -dt * p.tau_syn_inv * i1[k][j];
                }
            }
    //di = -dt * p.tau_syn_inv * i1;

    for (int k = 0; k < 5; ++k) {
                for (int j = 0; j < 2; ++j) {
                   i_decayed[k][j] = i1[k][j] + di[k][j];
                }
            }

    //i_decayed = i1 + di;

    //torch::Tensor result = (v_decayed - p.v_th) > torch::tensor(0.0);
    //bool comparison_result = result.item<bool>();

    // if(comparison_result){
    //     z_new = torch::tensor(1.0);
    // }else{
    //     z_new = torch::tensor(0.0);
    // }

    ap_fixed<32,16> x[5][2];

    for (int k = 0; k < 5; ++k) {
                for (int j = 0; j < 2; ++j) {
                   x[k][j] = v_decayed[k][j] - p.v_th;
                }
            }

    //auto x = (v_decayed - p.v_th);
    for (int k = 0; k < 5; ++k) {
                for (int j = 0; j < 2; ++j) {
                   if(x[k][j] > 0){
                        z_new[k][j] = 1.0;
                   }else{
                        z_new[k][j] = 0.0;
                   }
                }
            }
    //z_new = torch::where(x > 0, torch::ones_like(x), torch::zeros_like(x));
    //((v_decayed - p.v_th) > 0).type_as(z_new);
    //z_new = ((v_decayed - p.v_th) > torch::tensor(0.0)) ? torch::tensor(1.0) : torch::tensor(0.0); //f(v_decayed - p.v_th, p.alpha);

    for (int k = 0; k < 5; ++k) {
                for (int j = 0; j < 2; ++j) {
                   v_new[k][j] =(1 - z_new[k][j]) * v_decayed[k][j] + z_new[k][j] * p.v_reset;
                }
            }

    //v_new = (1 - z_new) * v_decayed + z_new * p.v_reset;

    for (int k = 0; k < 5; ++k) {
                for (int j = 0; j < 2; ++j) {
                   i_new[k][j] = i_decayed[k][j] + input_tn[k][j];
                }
            }

    //i_new = i_decayed + input_tn;


    for (int k = 0; k < 5; ++k) {
                for (int j = 0; j < 2; ++j) {
                   o.array1[n][k][j] = z_new[k][j];
                   //o_and_s.array2[k][j] = v_new[k][j];
                   //o_and_s.array3[k][j] = i_new[k][j];
                }
            }
    st.set(v_new, i_new);
    }



    return o;
}
