/**
 *  @autor tekatod
 *  @date 1/30/17
 */

#include "include/Ranked.h"

MD::Ranked::Ranked() : mProbability(0.0), mFactor(1.0) { }

MD::Ranked::Ranked(double probability, double factor)  : mProbability(probability), mFactor(factor) { }

void MD::Ranked::setProbability(double value) {
    if(value < 0.0) {
        value = 0.0;
    } else if(value >= 1.0) {
        value = 1.0;
    }
    mProbability = value;
}

double MD::Ranked::getProbability() const {
    return mProbability;
}

void MD::Ranked::setFactor(double factor) {
    mFactor = factor;
}

double MD::Ranked::getFactor() const {
    return mFactor;
}
