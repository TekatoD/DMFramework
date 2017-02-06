/**
 *  @autor tekatod
 *  @date 2/6/17
 */

#include <gtest/gtest.h>
#include "include/DataHolderTestImpl.h"
#include "../../include/AbstractEvent.h"
#include "../../include/EventGenerator.h"

class EventGeneratorFixture : public ::testing::Test {
public:
    typedef DataHolderImpl<int, float, double>::DataHolderPtr dataHolder;
    EventGeneratorFixture() {
        mDataHolder = std::make_shared<DataHolderImpl<int, float, double>>();
        mDataHolder->set("x", (int)1);
        mDataHolder->set("y", (float)2);
        mDataHolder->set("z", (double)3);
        mEvent1 = std::make_shared<DM::AbstractEvent<bool, dataHolder>>([](dataHolder dH){
            return dH->getData<int>("x") == 1;
        });
        mEvent2 = std::make_shared<DM::AbstractEvent<bool, dataHolder>>([](dataHolder dH){
            return dH->getData<double>("z") > 2.0;
        });
    }

    ~EventGeneratorFixture() {
        //Destroy all the good members
    }

protected:
    dataHolder mDataHolder;
    std::shared_ptr<DM::AbstractEvent<bool, dataHolder>> mEvent1;
    std::shared_ptr<DM::AbstractEvent<bool, dataHolder>> mEvent2;
};

TEST_F(EventGeneratorFixture, SetEmptyTests) {
    DM::EventGenerator<bool, dataHolder> eventGenerator(mDataHolder);
    EXPECT_TRUE(eventGenerator.isEmpty());
    eventGenerator.set(mEvent1);
    EXPECT_FALSE(eventGenerator.isEmpty());
}

TEST_F(EventGeneratorFixture, UpdateTest) {
    DM::EventGenerator<bool, dataHolder> eventGenerator(mDataHolder);
    eventGenerator.set(mEvent1);
    eventGenerator.set(mEvent2);
    eventGenerator.update();
    EXPECT_TRUE(mEvent1->getResult());
    EXPECT_TRUE(mEvent2->getResult());
}

TEST_F(EventGeneratorFixture, RemoveTest) {
    DM::EventGenerator<bool, dataHolder> eventGenerator(mDataHolder);
    eventGenerator.set(mEvent1);
    eventGenerator.set(mEvent2);
    eventGenerator.update();
    mDataHolder->set("x", (int) 2);
    eventGenerator.remove(mEvent1);
    eventGenerator.remove(mEvent2);
    eventGenerator.update();
    EXPECT_TRUE(eventGenerator.isEmpty());
    EXPECT_TRUE(mEvent1->getResult());
}