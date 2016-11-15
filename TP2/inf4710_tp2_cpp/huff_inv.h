
#pragma once

#include "huff_common.h"

template<size_t N=64, typename T=short>
inline std::vector<std::array<T,N>> huff_inv(const HuffOutput<T>& oInput) {
    CV_Assert(!oInput.map.empty() && !oInput.string.empty());
    std::vector<std::array<T,N>> vvOutput;

    // @@@@ TODO
<<<<<<< HEAD
=======
   
>>>>>>> d1084ba4883325c73782719021fbdfa46b1063ca
    return vvOutput;
}
