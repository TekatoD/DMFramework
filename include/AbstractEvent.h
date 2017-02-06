/**
 *  @autor tekatod
 *  @date 2/2/17
 */
#pragma once

#include <functional>
#include <vector>

namespace DM {
    template<class R, class D>
    class AbstractEvent {
    public:
        AbstractEvent(std::function<R(D)> function) : mFunction(function) { }

        void update(D dataHolderPointer) {
            mResult = mFunction(dataHolderPointer);
        };

        R getResult() const {
            return mResult;
        }

    private:
        std::function<R(D)> mFunction;
        R mResult;
    };
}

