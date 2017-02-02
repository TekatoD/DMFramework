/**
 *  @autor tekatod
 *  @date 2/2/17
 */
#pragma once

#include <functional>

namespace DM {
    template<class R, class... Args, class... Names, Names... names>
    class AbstractEvent {
    public:
        AbstractEvent(std::function<R(Args...)> function) : mFunction(function) { }

        template<class D>
        void update(D dataHolderPointer) {
            mResult = mFunction(dataHolderPointer->getData<Args>(names)...);
        };

        R getResult() const {
            return mResult;
        }


    private:
        std::function<R(Args...)> mFunction;
        R mResult;
    };
}

