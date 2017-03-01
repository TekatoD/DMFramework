//
// Created by tekatod on 3/1/17.
//

#pragma once

#include "transition_generator.h"
#include "relationship.h"

namespace DM {
    template <class D>
    class p_transition_generator : public transition_generator<D, double, relationship<D>> {
    public:
        p_transition_generator(std::initializer_list<relationship<D>> init) : transition_generator(init) { }

        std::shared_ptr<abstract_state> update(std::shared_ptr<abstract_state> current_state) {
            if(this->is_transitions_exist()) {
                auto temp = m_transition_list.end();
                for (auto t : m_transition_list) {
                    if (t->get_initial_state() == current_state || t->get_initial_state() == nullptr) {
                        if(temp == m_transition_list.end()) {
                            temp = t;
                        }
                        else if(t->get_transition_value() > temp->get_transition_value()) {
                            temp = t;
                        }
                    }
                }
                if(temp != m_transition_list.end()) {
                    return temp->get_end_state();
                }
                else {
                    return current_state;
                }
            }
            return current_state;
        }
    };
}
