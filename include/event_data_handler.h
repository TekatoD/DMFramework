/**
 *  @autor tekatod
 *  @date 2/6/17
 */
#pragma once

#include <forward_list>
#include <memory>
#include "abstract_event.h"
#include "data_handler.h"

namespace DM {
    template<class R, class D>
    class event_data_handler {
    public:
        event_data_handler(std::shared_ptr<D> data_handler_ptr) : m_data_handler_ptr(data_handler_ptr) {
            static_assert(std::is_base_of<data_handler, D>::value, "class must be derived from data_handler and implement run");
        }

        event_data_handler(std::shared_ptr<D> data_handler_ptr,
                           std::initializer_list<std::shared_ptr<abstract_event<R, D>>> init) :
                                m_data_handler_ptr(data_handler_ptr), m_event_list(init) {
                                    static_assert(std::is_base_of<data_handler, D>::value, "class must be derived from data_handler and implement run");
                                }

        void set(std::shared_ptr<abstract_event<R, D>> event) {
            m_event_list.push_front(event);
        }

        void remove(std::shared_ptr<abstract_event<R, D>> event) {
            m_event_list.remove(event);
        }

        bool is_events_list_empty() const {
            return m_event_list.empty();
        }

        void update() {
            if (!this->is_events_list_empty()) {
                m_data_handler_ptr->update();
                for (auto& event : m_event_list) {
                    event->update(m_data_handler_ptr);
                }
            }
        }

        //TODO:: Test
        std::shared_ptr<D> get_data_handler() const {
            return m_data_handler_ptr;
        }

    private:
        std::shared_ptr<D> m_data_handler_ptr;
        std::forward_list<std::shared_ptr<abstract_event<R, D>>> m_event_list;
    };
}