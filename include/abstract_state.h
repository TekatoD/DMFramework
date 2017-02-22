/**
 *  @autor tekatod
 *  @date 2/2/17
 */
#pragma once

#include <string>

namespace DM {
    class abstract_state {
    public:
        abstract_state(const std::string& name);

        void set_name(const std::string &name);

        std::string get_name() const;

    private:
        std::string m_state_name;
    };
}

