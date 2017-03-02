/**
 *  @autor tekatod
 *  @date 2/22/17
 */
#pragma once

#include <algorithm>
#include "transition.h"

//TODO:: Test
namespace DM {
    template<class D, class R = bool, class T = transition <D, R>>
    class transition_generator {
    public:
        using result_type = R;
        using transition_type = T;
        using data_handler_type = D;

        transition_generator() = default;

        transition_generator(std::initializer_list<T> init) : m_transition_list(init) {
            static_assert(std::is_base_of<data_handler, D>::value, "class must be derived from data_handler and implement run");
        };

        void set(T t) {
            m_transition_list.emplace_front(t);
        }

        void remove(T t) {
            m_transition_list.remove(t);
        }

        bool is_transitions_exist() const {
            return !m_transition_list.empty();
        }

        std::shared_ptr<abstract_state<D>> update(std::shared_ptr<abstract_state<D>> current_state) {
            if (this->is_transitions_exist()) {
                auto temp = std::find_if(m_transition_list.begin(), m_transition_list.end(),
                                         [&current_state](auto& el) {
                                             if (el.get_initial_state() == current_state ||
                                                 el.get_initial_state() == nullptr) {
                                                 el.update();
                                                 return el.get_transition_value();
                                             } else {
                                                 return false;
                                             }
                                         });
                if (temp != m_transition_list.end()) {
                    return temp->get_end_state();
                } else {
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