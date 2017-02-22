/**
 *  @autor tekatod
 *  @date 2/22/17
 */

#include <memory>
#include "../include/abstract_state.h"

class state_impl : public DM::abstract_state {
public:
    state_impl(std::string name) : abstract_state(name) { }

    template <class D>
    void run(std::shared_ptr<D> d) { }

};