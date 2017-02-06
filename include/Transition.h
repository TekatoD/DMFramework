/**
 *  @autor tekatod
 *  @date 2/6/17
 */
#pragma once

#include <memory>
#include <forward_list>
#include "AbstractState.h"
#include "AbstractEvent.h"
#include <iostream>

namespace DM {
    template <class R, class D>
    class Transition {
    public:
        Transition(std::shared_ptr<AbstractState> initialState, std::shared_ptr<AbstractState> endState) :
                mInitialState(initialState), mEndState(endState), mTriggered(false) { }

        //TODO:: This must be of particular type
        template<class... Args>
        Transition(std::shared_ptr<AbstractState> initialState, std::shared_ptr<AbstractState> endState,
                   Args... events) : mInitialState(initialState), mEndState(endState),
                                                    mEvents{events...}, mTriggered(false) { }

        std::shared_ptr<AbstractState> getInitialState() const {
            return mInitialState;
        }

        std::shared_ptr<AbstractState> getEndState() const {
            return mEndState;
        }

        bool isTriggered() const {
            return mTriggered;
        }

        void set(std::shared_ptr<AbstractEvent<R, D>> event) {
            mEvents.push_front(event);
        }

        void remove(std::shared_ptr<AbstractEvent<R, D>> event) {
            mEvents.remove(event);
        }

        bool isEmpty() const {
            return mEvents.empty();
        }

        void update() {
            if(!this->isEmpty()) {
                mTriggered = true;
                for (auto event : mEvents) {
                    mTriggered *= event->getResult();
                }
            }
        }

    private:
        std::shared_ptr<AbstractState> mInitialState;
        std::shared_ptr<AbstractState> mEndState;
        std::forward_list<std::shared_ptr<AbstractEvent<R, D>>> mEvents;
        bool mTriggered;
    };
}