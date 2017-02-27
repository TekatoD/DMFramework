/**
 *  @autor tekatod
 *  @date 2/2/17
 */
#pragma once

#include <string>
#include <memory>
#include "data_handler.h"

namespace DM {
    template<class D>
    class abstract_state {
    public:
        abstract_state(const std::string& name) : m_state_name(name), m_data_holder_ptr(nullptr) { }

        abstract_state(const std::string& name, std::shared_ptr<D> d) : m_data_holder_ptr(d), m_state_name(name) {
            static_assert(std::is_base_of<data_handler, D>::value);
        }

        void set_name(const std::string &name) {
            m_state_name = name;
        }

        std::string get_name() const {
            return m_state_name;
        }

        virtual void run() = 0;

    protected:
        std::shared_ptr<D> m_data_holder_ptr;
    private:
        std::string m_state_name;
    };
}

