/**
 *  @autor tekatod
 *  @date 2/2/17
 */
#include "include/AbstractState.h"

DM::AbstractState::AbstractState(const std::string& name) : mStateName(name) { }

void DM::AbstractState::setName(const std::string& name) {
    mStateName = name;
}

std::string DM::AbstractState::getName() const {
    return mStateName;
}
