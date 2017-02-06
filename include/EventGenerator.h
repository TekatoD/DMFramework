/**
 *  @autor tekatod
 *  @date 2/6/17
 */
#pragma once

#include <forward_list>
#include <memory>
#include "AbstractEvent.h"

namespace DM {
    template<class R, class D>
    class EventGenerator {
    public:
        EventGenerator(D dataHolderPtr) : mDataHolderPtr(dataHolderPtr) { }

        void set(std::shared_ptr<AbstractEvent<R, D>> event) {
            mEventList.push_front(event);
        }

        void remove(std::shared_ptr<AbstractEvent<R, D>> event) {
            mEventList.remove(event);
        }

        bool isEmpty() const {
            return mEventList.empty();
        }

        void update() {
            for(auto event : mEventList) {
                event->update(mDataHolderPtr);
            }
        }

    private:
        D mDataHolderPtr;
        std::forward_list<std::shared_ptr<AbstractEvent<R, D>>> mEventList;
    };
}