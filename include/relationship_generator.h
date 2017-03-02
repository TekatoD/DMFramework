//
// Created by tekatod on 3/1/17.
//

#pragma once

#include <vector>
#include "transition_generator.h"
#include "relationship.h"

namespace DM {
    template <class D>
    class relationship_generator : public transition_generator<D, double, relationship<D>> {
    public:
        relationship_generator(std::initializer_list<relationship<D>> init) :
                transition_generator<D, double, relationship<D>> (init) { }

        relationship_generator() : transition_generator<D, double, relationship<D>>() { }

        //TODO:: There is a costil, fix it
        std::shared_ptr<abstract_state<D>> update(std::shared_ptr<abstract_state<D>> current_state) {
            if(this->is_transitions_exist()) {
                auto temp = this->m_transition_list.end();
                auto current_it = this->m_transition_list.begin();
                for (auto& t : this->m_transition_list) {
                    if (t.get_initial_state() == current_state || t.get_initial_state() == nullptr) {
                        t.update();
                        if(temp == this->m_transition_list.end()) {
                            temp = current_it;
                        }
                        else if(t.get_transition_value() > temp->get_transition_value()) {
                            temp = current_it;
                        }
                    }
                    ++current_it;
                }
                if(temp != this->m_transition_list.end()) {
                    return temp->get_end_state();
                }
                else {
                    return current_state;
                }
            }
            return current_state;
        }

        std::vector<double> get_factors() const {
            std::vector<double> factors;
            factors.reserve((unsigned long)std::distance(this->m_transition_list.begin(), this->m_transition_list.end()));
            for(const auto& x : this->m_transition_list) {
                factors.push_back(x.get_factor());
            }
            return std::move(factors);
        }

        void set_factors(std::vector<double> factors) {
            if((unsigned long)std::distance(this->m_transition_list.begin(), this->m_transition_list.end()) == factors.size()) {
                size_t i = 0;
                for(auto& x : this->m_transition_list) {
                    x.set_factor(factors[i]);
                    ++i;
                }
            }
        }
    };
}
