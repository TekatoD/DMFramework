/**
 *  @autor tekatod
 *  @date 2/22/17
 */
#pragma once

#include "transition.h"

//TODO:: Test
namespace DM {
    template<class D>
    class transition_generator {
    public:
        transition_generator() = default;

        transition_generator(std::initializer_list<transition<bool, D>> init) : m_transition_list(init) {
            static_assert(std::is_base_of<data_handler, D>::value);
        };

        void set(transition<bool, D> t) {
            m_transition_list.emplace_front(t);
        }

        void remove(transition<bool, D> t) {
            m_transition_list.remove(t);
        }

        bool is_transitions_exist() const {
            return m_transition_list.empty();
        }

        std::shared_ptr<abstract_state> update(std::shared_ptr<abstract_state> current_state) {
            if (this->is_transitions_exist()) {
                for(auto t : m_transition_list) {
                    t->update();
                    if(t->is_triggered() and t->get_initial_state() == current_state) {
                        return t->get_initial_state();
                    }
                }
                return nullptr;
            } else {
                return nullptr;
            }
        }
        
    private:
        std::forward_list<transition<bool, D>> m_transition_list;
    };
}