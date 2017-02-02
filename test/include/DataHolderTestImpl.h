/**
 *  @autor tekatod
 *  @date 2/2/17
 */
#pragma once

#include "../include/DataHolder.h"

template<class... Classes>
class DataHolderImpl : public DM::DataHolder<Classes...> {
public:
    void update() {

    }
};