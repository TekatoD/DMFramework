/**
 *  @autor tekatod
 *  @date 2/2/17
 */
#pragma once

#include "abstract_event.h"

namespace DM {
    template <class D>
    class condition : public abstract_event<bool, D> {
        condition(std::function<bool(std::shared_ptr<D>)> function) : abstract_event(function) {};
    };
}