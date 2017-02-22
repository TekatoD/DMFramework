/**
 *  @autor tekatod
 *  @date 2/2/17
 */
#include "include/abstract_state.h"

DM::abstract_state::abstract_state(const std::string& name) : m_state_name(name) { }

void DM::abstract_state::set_name(const std::string &name) {
    m_state_name = name;
}

std::string DM::abstract_state::get_name() const {
    return m_state_name;
}
