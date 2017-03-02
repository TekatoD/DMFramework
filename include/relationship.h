//
// Created by tekatod on 2/27/17.
//

#pragma once

#include "transition.h"

namespace DM {
    template<class D>
    class relationship : public transition<D, double> {
    public:
        relationship(std::shared_ptr<abstract_state<D>> initial_state, std::shared_ptr<abstract_state<D>> end_state) :
                transition<D, double>(initial_state, end_state), m_factor(1.0) { }

        template<class... abstract_event>
        relationship(std::shared_ptr<abstract_state<D>> initial_state, std::shared_ptr<abstract_state<D>> end_state,
                abstract_event... events) : transition<D, double>(initial_state, end_state, events...), m_factor(1.0) { }

        relationship(std::shared_ptr<abstract_state<D>> initial_state, std::shared_ptr<abstract_state<D>> end_state, double factor) :
                transition<D, double>(initial_state, end_state), m_factor(factor) { }

        template<class... abstract_event>
        relationship(std::shared_ptr<abstract_state<D>> initial_state, std::shared_ptr<abstract_state<D>> end_state, double factor,
                abstract_event... events) : transition<D, double>(initial_state, end_state, events...), m_factor(factor) { }

        void set_factor(double factor) {
            m_factor = factor;
        }

        double get_factor() const {
            return m_factor;
        }

        double get_transition_value() const {
            double temp = this->m_triggered * m_factor;
            if (temp > 1.0) {
                return 1.0;
            } else if (temp < 0.0) {
                return 0.0;
            } else {
                return temp;
            }
        }

    private:
        double m_factor;
    };
}
