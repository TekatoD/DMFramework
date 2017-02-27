//
// Created by tekatod on 2/27/17.
//

#pragma once

#include "abstract_event.h"

namespace DM {
    template <class D>
    class probability_event : public abstract_event<double, D> {
        probability_event(std::function<double(std::shared_ptr<D>)> function) : abstract_event(function) { };
    };
}