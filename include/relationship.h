//
// Created by tekatod on 2/27/17.
//

#pragma once

#include "transition.h"

namespace DM {
    template<class D>
    class relationship : public transition<double, D> {
    public:
        relationship(std::shared_ptr<abstract_state<D>> initial_state, std::shared_ptr<abstract_state<D>> end_state) :
                transition(initial_state, end_state), m_factor(1.0) { }

        template<class... abstract_event>
        transition(std::shared_ptr<abstract_state<D>> initial_state, std::shared_ptr<abstract_state<D>> end_state,
                abstract_event... events) : transition(initial_state, end_state, events...), m_factor(1.0) { }

        relationship(std::shared_ptr<abstract_state<D>> initial_state, std::shared_ptr<abstract_state<D>> end_state, double factor) :
                transition(initial_state, end_state), m_factor(factor) { }

        template<class... abstract_event>
        transition(std::shared_ptr<abstract_state<D>> initial_state, std::shared_ptr<abstract_state<D>> end_state, double factor,
                abstract_event... events) : transition(initial_state, end_state, events...), m_factor(factor) { }

        void set_factor(double factor) {
            m_factor = factor;
        }

        double get_factor() const {
            return m_factor;
        }

        double is_triggered() const {
            return this->m_triggered * m_factor;
        }

    private:
        double m_factor;
    };
}
