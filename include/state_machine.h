/**
 *  @autor tekatod
 *  @date 3/2/17
 */
#pragma once

#include <bits/shared_ptr.h>
#include "abstract_state.h"
#include "event_data_handler.h"
#include "relationship_generator.h"
#include <vector>
#include <typeinfo>

namespace DM {
    template<class G>
    class state_machine {
    public:
        state_machine(G generator, event_data_handler<G::result_type, G::data_handler_type> event_generator,
                     std::shared_ptr<abstract_state<G::data_handler_type>> initial_state) : m_generator(generator),
                                                                         m_event_generator(event_generator),
                                                                         m_current_state(initial_state) { }

        state_machine(std::shared_ptr<G::data_handler_type> data_handler_ptr,
                      std::shared_ptr<abstract_state<G::data_handler_type>> initial_state) :
                m_event_generator(data_handler_ptr), m_current_state(initial_state) { }

        void add_event(std::shared_ptr<abstract_event<G::result_type, G::data_handler_type>> event) {
            m_event_generator.set(event);
        }

        void remove_event(std::shared_ptr<abstract_event<G::result_type, G::data_handler_type>> event) {
            m_event_generator.remove(event);
        }

        void add_transition(G::transition_type transition) {
            m_generator->set(transition);
        }

        void remove_transition(G::transition_type transition) {
            m_generator->remove(transition);
        }

        void run() {
            m_event_generator.update();
            m_current_state = m_generator.update(m_current_state);
            m_current_state->run();
        }

        std::vector<double> get_factors() const {
            std::vector<double> factors;
            if(typeid(G) == typeid(relationship_generator)) {
                return m_generator.get_factors();
            }
            return std::move(factors);
        }

        void set_factors(std::vector<double> factors) {
            if(typeid(G) == typeid(relationship_generator)) {
                return m_generator.set_factors(factors);
            }
        }

    private:
        G m_generator;
        event_data_handler<G::result_type, G::data_handler_type> m_event_generator;
        std::shared_ptr<abstract_state<G::data_handler_type>> m_current_state;
    };
}