/**
 *  @autor tekatod
 *  @date 2/22/17
 */
#pragma once

#include <algorithm>
#include "transition.h"

//TODO:: Test
namespace DM {
    template<class D, class R = bool, class T = transition<R, D>>
    class transition_generator {
    public:
        transition_generator() = default;

        transition_generator(std::initializer_list<T> init) : m_transition_list(init) {
            static_assert(std::is_base_of<data_handler, D>::value);
        };

        void set(T t) {
            m_transition_list.emplace_front(t);
        }

        void remove(T t) {
            m_transition_list.remove(t);
        }

        bool is_transitions_exist() const {
            return m_transition_list.empty();
        }

        std::shared_ptr<abstract_state> update(std::shared_ptr<abstract_state> current_state) {
            if (this->is_transitions_exist()) {
                auto temp = std::find_if(m_transition_list.begin(), m_transition_list.end(),
                                         [&current_state](const auto& el) {
                    return el->is_triggered() && (el->get_initial_state() == current_state ||
                                                 el->get_initial_state() == nullptr);
                });
                if(temp != m_transition_list.end()) {
                    return temp->get_end_state();
                }
                else {
                    return current_state;
                }
            } else {
                return current_state;
            }
        }

    protected:
        std::forward_list<T> m_transition_list;
    };
}