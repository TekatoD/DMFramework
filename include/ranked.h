/**
 *  @autor tekatod
 *  @date 1/30/17
 */
#pragma once

namespace DM {
    class ranked {
    public:

        ranked();

        ranked(double probability, double factor = 1.0);

        void set_probability(double value);

        double get_probability() const;

        void set_factor(double factor);

        double get_factor() const;

    private:
        double m_probability;
        double m_factor;
    };
}