/**
 *  @autor tekatod
 *  @date 2/6/17
 */

#include <gtest/gtest.h>
#include "include/DataHolderTestImpl.h"
#include "../../include/AbstractEvent.h"
#include "../../include/EventGenerator.h"
#include "../../include/AbstractState.h"
#include "../../include/Transition.h"

class TransitionFixture : public ::testing::Test {
public:
    typedef DataHolderImpl<int, float, double>::DataHolderPtr dataHolder;
    TransitionFixture() : mDataHolder(std::make_shared<DataHolderImpl<int, float, double>>()), mEventGenerator(mDataHolder) {
        mDataHolder->set("x", (int)1);
        mDataHolder->set("y", (float)2);
        mDataHolder->set("z", (double)3);
        mEvent1 = std::make_shared<DM::AbstractEvent<bool, dataHolder>>([](dataHolder dH){
            return dH->getData<int>("x") == 1;
        });
        mEvent2 = std::make_shared<DM::AbstractEvent<bool, dataHolder>>([](dataHolder dH){
            return dH->getData<double>("z") > 2.0;
        });
        mEventGenerator.set(mEvent1);
        mEventGenerator.set(mEvent2);
    }

    ~TransitionFixture() {
        //Destroy all the good members
    }

protected:
    dataHolder mDataHolder;
    std::shared_ptr<DM::AbstractEvent<bool, dataHolder>> mEvent1;
    std::shared_ptr<DM::AbstractEvent<bool, dataHolder>> mEvent2;
    DM::EventGenerator<bool, dataHolder> mEventGenerator;
};

TEST_F(TransitionFixture, ConstructorUpdateTest) {
    std::shared_ptr<DM::AbstractState> state1 = std::make_shared<DM::AbstractState>("state1");
    std::shared_ptr<DM::AbstractState> state2 = std::make_shared<DM::AbstractState>("state2");
    DM::Transition<bool, dataHolder> transition{state1, state2, mEvent1, mEvent2};
    mEventGenerator.update();
    transition.update();
    EXPECT_FALSE(transition.isEmpty());
    EXPECT_TRUE(transition.isTriggered());
}

TEST_F(TransitionFixture, ConstructorSetTest) {
    std::shared_ptr<DM::AbstractState> state1 = std::make_shared<DM::AbstractState>("state1");
    std::shared_ptr<DM::AbstractState> state2 = std::make_shared<DM::AbstractState>("state2");
    DM::Transition<bool, dataHolder> transition{state1, state2};
    transition.set(mEvent1);
    transition.set(mEvent2);
    mEventGenerator.update();
    transition.update();
    EXPECT_FALSE(transition.isEmpty());
    EXPECT_TRUE(transition.isTriggered());
}

TEST_F(TransitionFixture, RemoveEmptyTest) {
    std::shared_ptr<DM::AbstractState> state1 = std::make_shared<DM::AbstractState>("state1");
    std::shared_ptr<DM::AbstractState> state2 = std::make_shared<DM::AbstractState>("state2");
    DM::Transition<bool, dataHolder> transition{state1, state2, mEvent1, mEvent2};
    transition.remove(mEvent1);
    transition.remove(mEvent2);
    mEventGenerator.update();
    transition.update();
    EXPECT_TRUE(transition.isEmpty());
    EXPECT_FALSE(transition.isTriggered());
}