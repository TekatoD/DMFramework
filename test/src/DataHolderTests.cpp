/**
 *  @autor tekatod
 *  @date 1/30/17
 */

#include <gtest/gtest.h>
#include "include/DataHolderTestImpl.h"


TEST(DataHolderTests, SetGetTest) {
    DataHolderImpl<int, float, double> dataHolder;
    dataHolder.set("x", 0);
    auto x = dataHolder.getField("x");
    auto ptr = x.get<std::shared_ptr<int>>();
    EXPECT_EQ(*ptr, (int)0);
}

TEST(DataHolderTests, TempalteGetTest) {
    DataHolderImpl<int, float, double> dataHolder;
    dataHolder.set("x", 0);
    auto x = dataHolder.getPointer<int>("x");
    EXPECT_EQ(*x, (int)0);
    int x1 = dataHolder.getData<int>("x");
    EXPECT_EQ(x1, (int)0);
}