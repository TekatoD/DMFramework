/**
 *  @autor tekatod
 *  @date 2/2/17
 */
#pragma once

#include "AbstractEvent.h"

namespace DM {
    template<class... Args>
    class Condition : public AbstractEvent<bool(Args...)> {
        Condition(std::function<bool(Args...)> function) : AbstractEvent(function) {};

    };

}