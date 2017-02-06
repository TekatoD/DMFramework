/**
 *  @autor tekatod
 *  @date 2/3/17
 */

#include <gtest/gtest.h>
#include "include/DataHolderTestImpl.h"
#include "../../include/AbstractEvent.h"

class AbstractEventFixture : public ::testing::Test {
public:
    typedef DataHolderImpl<int, float, double>::DataHolderPtr dataHolder;
    AbstractEventFixture() {
        mDataHolder = std::make_shared<DataHolderImpl<int, float, double>>();
        mDataHolder->set("x", (int)1);
        mDataHolder->set("y", (float)2);
        mDataHolder->set("z", (double)3);
    }

    ~AbstractEventFixture() {
        //Destroy all the good members
    }

protected:
    dataHolder mDataHolder;
};

TEST_F(AbstractEventFixture, BasicTest1) {
    DM::AbstractEvent<bool, dataHolder> abstractEvent([](dataHolder dH){
        return dH->getData<int>("x") == 1;
    });
    abstractEvent.update(mDataHolder);
    EXPECT_TRUE(abstractEvent.getResult());
}

TEST_F(AbstractEventFixture, BasicTest2) {
    DM::AbstractEvent<double, dataHolder> abstractEvent([](dataHolder dH){
        return dH->getData<float>("y") * dH->getData<double>("z");
    });
    abstractEvent.update(mDataHolder);
    EXPECT_EQ(abstractEvent.getResult(), (double) 6.0);
}