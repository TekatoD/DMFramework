/**
 *  @autor tekatod
 *  @date 2/22/17
 */
#pragma once

#include "data_handler.h"

class data_handler_impl : public DM::data_handler {
public:
    data_handler_impl() = default;

    void update() {
        m_x = 3 * 2;
        m_y = m_x * 1.5;
        m_t = true ;
    }

    double get_x() {
        return m_x;
    }

    double get_y() {
        return m_y;
    }

    bool get_t() {
        return m_t;
    }

    void set_curr_state(const std::string& name) {
        m_curr_state = name;
    }

    std::string get_curr_state() {
        return m_curr_state;
    }

private:
    double m_x;
    double m_y;
    bool m_t;
    std::string m_curr_state;
};