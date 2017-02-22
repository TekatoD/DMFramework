/**
 *  @autor tekatod
 *  @date 2/2/17
 */
#pragma once

#include <string>
#include "data_handler.h"

namespace DM {
    class abstract_state {
    public:
        abstract_state(const std::string& name);

        void set_name(const std::string &name);

        std::string get_name() const;

        template<class D>
        virtual void run(std::shared_ptr<D> d) = 0;

    private:
        std::string m_state_name;
    };
}

