#ifndef LIF_H
#define LIF_H

#include "lif_param.h"
#include "lfs.h"

class LIFCell{
    public:
        LIFCell(lif_param p);

        //template<size_t N, size_t M>
        LIFFeedForwardState initial_state();

    private:
        lif_param pr;

};

#endif
