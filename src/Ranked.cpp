/**
 *  @autor tekatod
 *  @date 1/30/17
 */

#include "include/Ranked.h"

DM::Ranked::Ranked() : mProbability(0.0), mFactor(1.0) { }

DM::Ranked::Ranked(double probability, double factor)  : mProbability(probability), mFactor(factor) { }

void DM::Ranked::setProbability(double value) {
    if(value < 0.0) {
        value = 0.0;
    } else if(value >= 1.0) {
        value = 1.0;
    }
    mProbability = value;
}

double DM::Ranked::getProbability() const {
    return mProbability;
}

void DM::Ranked::setFactor(double factor) {
    mFactor = factor;
}

double DM::Ranked::getFactor() const {
    return mFactor;
}
