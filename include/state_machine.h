/**
 *  @autor tekatod
 *  @date 3/2/17
 */
#pragma once

#include <memory>
#include "abstract_state.h"
#include "event_data_handler.h"
#include "relationship_generator.h"
#include <vector>
#include <typeinfo>
#include <type_traits>

namespace DM {
    template<class G>
    class state_machine {
    public:
        state_machine(G generator, event_data_handler<typename G::result_type, typename G::data_handler_type> event_generator,
                     std::shared_ptr<abstract_state<typename G::data_handler_type>> initial_state) : m_generator(generator),
                                                                         m_event_generator(event_generator),
                                                                         m_current_state(initial_state) { }

        state_machine(std::shared_ptr<typename G::data_handler_type> data_handler_ptr,
                      std::shared_ptr<abstract_state<typename G::data_handler_type>> initial_state) :
                m_event_generator(data_handler_ptr), m_current_state(initial_state) { }

        void add_event(std::shared_ptr<abstract_event<typename G::result_type, typename G::data_handler_type>> event) {
            m_event_generator.set(event);
        }

        void remove_event(std::shared_ptr<abstract_event<typename G::result_type, typename G::data_handler_type>> event) {
            m_event_generator.remove(event);
        }

        void add_transition(typename G::transition_type transition) {
            m_generator.set(transition);
        }

        void remove_transition(typename G::transition_type transition) {
            m_generator.remove(transition);
        }

        void run() {
            m_event_generator.update();
            m_current_state = m_generator.update(m_current_state);
            m_current_state->run();
        }

        template<typename = std::enable_if<std::is_same<G, relationship_generator<typename G::data_handler_type>>::value>>
        std::vector<double> get_factors() const {
            std::vector<double> factors;
            return m_generator.get_factors();
        }

        template<typename = std::enable_if<std::is_same<G, relationship_generator<typename G::data_handler_type>>::value>>
        void set_factors(std::vector<double> factors) {
            return m_generator.set_factors(factors);
        }

    private:
        G m_generator;
        event_data_handler<typename G::result_type, typename G::data_handler_type> m_event_generator;
        std::shared_ptr<abstract_state<typename G::data_handler_type>> m_current_state;
    };
}