/**
 *  @autor tekatod
 *  @date 2/22/17
 */
#pragma once

#include "transition.h"

//TODO:: Test
namespace DM {
    template<class R, class D>
    class transition_generator {
    public:
        transition_generator() = default;

        transition_generator(std::initializer_list<transition<R, D>> init) : m_transition_list(init) { };

        void set(transition<R, D> t) {
            m_transition_list.emplace_front(t);
        }

        void remove(transition<R, D> t) {
            m_transition_list.remove(t);
        }

        bool is_transitions_exist() const {
            return m_transition_list.empty();
        }

        std::shared_ptr<abstract_state> update() {
            if (this->is_transitions_exist()) {
                for(auto t : m_transition_list) {
                    t->update();
                    if(t->is_triggered()) {
                        return t->get_initial_state();
                    }
                }
                return nullptr;
            } else {
                return nullptr;
            }
        }



    private:
        std::forward_list<transition<R, D>> m_transition_list;
    };
}