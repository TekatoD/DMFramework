/**
 *  @autor tekatod
 *  @date 2/3/17
 */

#include <gtest/gtest.h>
#include "include/data_handler_impl.h"
#include "abstract_event.h"

class abstract_event_fixture : public ::testing::Test {
public:
    typedef std::shared_ptr<data_handler_impl> dh_ptr;
    abstract_event_fixture() {
        m_data_holder = std::make_shared<data_handler_impl>();
        m_data_holder->update();
    }

    ~abstract_event_fixture() {
        //Destroy all the good members
    }

protected:
    dh_ptr m_data_holder;
};

TEST_F(abstract_event_fixture, basic) {
    DM::abstract_event<bool, data_handler_impl> abstractEvent([](dh_ptr dH){
        return dH->get_x() == 6.0;
    });
    abstractEvent.update(m_data_holder);
    EXPECT_TRUE(abstractEvent.get_result());
}