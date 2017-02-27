/**
 *  @autor tekatod
 *  @date 2/2/17
 */
#pragma once

#include <functional>
#include <memory>
#include "data_handler.h"

namespace DM {
    template<class R, class D>
    class abstract_event {
    public:
        abstract_event(std::function<R(std::shared_ptr<D>)> function) : m_function(function) {
            static_assert(std::is_base_of<data_handler, D>::value);
        }

        void update(std::shared_ptr<D> event_data_handler_pointer) {
            m_result = m_function(event_data_handler_pointer);
        };

        R get_result() const {
            return m_result;
        }

    private:
        std::function<R(std::shared_ptr<D>)> m_function;
        R m_result;
    };
}

