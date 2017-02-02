/**
 *  @autor tekatod
 *  @date 2/2/17
 */
#pragma once

#include <string>

namespace DM {
    class AbstractState {
    public:
        AbstractState(const std::string& name);

        void setName(const std::string& name);

        std::string getName() const;

    private:
        std::string mStateName;
    };
}

