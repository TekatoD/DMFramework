/**
 *  @autor tekatod
 *  @date 2/6/17
 */
#pragma once

#include <memory>
#include <forward_list>
#include "abstract_state.h"
#include "abstract_event.h"
#include <iostream>

namespace DM {
    template <class R, class D>
    class transition {
    public:
        transition(std::shared_ptr<abstract_state> initial_state, std::shared_ptr<abstract_state> end_state) :
                m_initial_state(initial_state), m_end_state(end_state), m_triggered(false) { }

        template<class... abstract_event>
        transition(std::shared_ptr<abstract_state> initial_state, std::shared_ptr<abstract_state> end_state,
                   abstract_event... events) : m_initial_state(initial_state), m_end_state(end_state),
                                                    m_events{events...}, m_triggered(false) { }

        std::shared_ptr<abstract_state> get_initial_state() const {
            return m_initial_state;
        }

        std::shared_ptr<abstract_state> get_end_state() const {
            return m_end_state;
        }

        bool is_triggered() const {
            return m_triggered;
        }

        void set(std::shared_ptr<abstract_event<R, D>> event) {
            m_events.push_front(event);
        }

        void remove(std::shared_ptr<abstract_event<R, D>> event) {
            m_events.remove(event);
        }

        bool is_events_list_empty() const {
            return m_events.empty();
        }

        void update() {
            if(!this->is_events_list_empty()) {
                m_triggered = true;
                for (auto event : m_events) {
                    m_triggered *= event->get_result();
                }
            }
        }

    private:
        std::shared_ptr<abstract_state> m_initial_state;
        std::shared_ptr<abstract_state> m_end_state;
        std::forward_list<std::shared_ptr<abstract_event<R, D>>> m_events;
        bool m_triggered;
    };
}