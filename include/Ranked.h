/**
 *  @autor tekatod
 *  @date 1/30/17
 */
#pragma once

namespace DM {
    class Ranked {
    public:

        Ranked();

        Ranked(double probability, double factor = 1.0);

        void setProbability(double value);

        double getProbability() const;

        void setFactor(double factor);

        double getFactor() const;

    private:
        double mProbability;
        double mFactor;
    };
}