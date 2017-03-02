/**
 *  @autor tekatod
 *  @date 2/6/17
 */

#include <gtest/gtest.h>
#include "include/data_handler_impl.h"
#include "abstract_event.h"
#include "event_data_handler.h"

class event_generator_fixture : public ::testing::Test {
public:
    typedef std::shared_ptr<data_handler_impl> dh_ptr;
    typedef DM::abstract_event<bool, data_handler_impl> ev;
    event_generator_fixture() {
        m_data_holder = std::make_shared<data_handler_impl>();
        m_data_holder->update();
        m_event1 = std::make_shared<ev>([](dh_ptr dH){
            return dH->get_x() == 6.0;
        });
        m_event2 = std::make_shared<ev>([](dh_ptr dH){
            return dH->get_t();
        });

    }

    ~event_generator_fixture() {
        //Destroy all the good members
    }

protected:
    std::shared_ptr<ev> m_event1;
    std::shared_ptr<ev> m_event2;
    dh_ptr m_data_holder;
};

TEST_F(event_generator_fixture, set_empty) {
    DM::event_data_handler<bool, data_handler_impl> event_generator(m_data_holder);
    EXPECT_TRUE(event_generator.is_events_list_empty());
    event_generator.set(m_event1);
    EXPECT_FALSE(event_generator.is_events_list_empty());
}

TEST_F(event_generator_fixture, update) {
    DM::event_data_handler<bool, data_handler_impl> eventGenerator(m_data_holder);
    eventGenerator.set(m_event1);
    eventGenerator.set(m_event2);
    eventGenerator.update();
    EXPECT_TRUE(m_event1->get_result());
    EXPECT_TRUE(m_event2->get_result());
}

TEST_F(event_generator_fixture, remove) {
    DM::event_data_handler<bool, data_handler_impl> eventGenerator(m_data_holder);
    eventGenerator.set(m_event1);
    eventGenerator.set(m_event2);
    eventGenerator.update();
    eventGenerator.remove(m_event1);
    eventGenerator.remove(m_event2);
    eventGenerator.update();
    EXPECT_TRUE(eventGenerator.is_events_list_empty());
    EXPECT_TRUE(m_event1->get_result());
}

TEST_F(event_generator_fixture, initializer_list_constructor) {
    DM::event_data_handler<bool, data_handler_impl> eventGenerator(m_data_holder, {m_event1, m_event2});
    eventGenerator.update();
    EXPECT_TRUE(m_event1->get_result());
    EXPECT_TRUE(m_event2->get_result());
}