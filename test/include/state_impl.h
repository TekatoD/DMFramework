/**
 *  @autor tekatod
 *  @date 2/22/17
 */

#include <memory>
#include "abstract_state.h"

class state_impl : public DM::abstract_state<data_handler_impl> {
public:
    state_impl(std::string name, std::shared_ptr<data_handler_impl> d) : abstract_state(name, d) { }

    void run() {
        this->m_data_holder_ptr->set_curr_state(this->get_name());
    }

};