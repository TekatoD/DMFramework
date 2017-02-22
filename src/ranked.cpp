/**
 *  @autor tekatod
 *  @date 1/30/17
 */

#include "include/ranked.h"

DM::ranked::ranked() : m_probability(0.0), m_factor(1.0) { }

DM::ranked::ranked(double probability, double factor)  : m_probability(probability), m_factor(factor) { }

void DM::ranked::set_probability(double value) {
    if(value < 0.0) {
        value = 0.0;
    } else if(value >= 1.0) {
        value = 1.0;
    }
    m_probability = value;
}

double DM::ranked::get_probability() const {
    return m_probability;
}

void DM::ranked::set_factor(double factor) {
    m_factor = factor;
}

double DM::ranked::get_factor() const {
    return m_factor;
}
