/**
 *  @autor tekatod
 *  @date 1/30/17
 */

#include <gtest/gtest.h>
#include "../../include/DataHolder.h"


TEST(DataHolderTests, SetGetTests) {
    DM::DataHolder<int, float, double> dataHolder;
    dataHolder.set("x", 0);
    auto x = dataHolder.getField("x");
    auto ptr = x.get<std::shared_ptr<int>>();
    EXPECT_EQ(*ptr, (int)0);
}