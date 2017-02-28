/**
 *  @autor tekatod
 *  @date 2/6/17
 */

#include <gtest/gtest.h>
#include "include/data_handler_impl.h"
#include "include/state_impl.h"
#include "../../include/abstract_event.h"
#include "../../include/event_data_handler.h"
#include "../../include/transition.h"

class transition_fixture : public ::testing::Test {
public:
    typedef std::shared_ptr<data_handler_impl> dh_ptr;
    typedef DM::abstract_event<bool, data_handler_impl> ev;
    transition_fixture() : m_data_holder(std::make_shared<data_handler_impl>()), m_event_generator(m_data_holder) {
        m_data_holder->update();
        m_event1 = std::make_shared<ev>([](dh_ptr dH){
            return dH->get_x() == 6.0;
        });
        m_event2 = std::make_shared<ev>([](dh_ptr dH){
            return dH->get_t();
        });
        m_event_generator.set(m_event1);
        m_event_generator.set(m_event2);

    }

    ~transition_fixture() {
        //Destroy all the good members
    }

protected:
    std::shared_ptr<ev> m_event1;
    std::shared_ptr<ev> m_event2;
    dh_ptr m_data_holder;
    DM::event_data_handler<bool, data_handler_impl> m_event_generator;
};

TEST_F(transition_fixture, constructor_update) {
    std::shared_ptr<state_impl> state1 = std::make_shared<state_impl>("state1", m_data_holder);
    std::shared_ptr<state_impl> state2 = std::make_shared<state_impl>("state2", m_data_holder);
    DM::event_data_handler<bool, data_handler_impl> eventGenerator(m_data_holder);
    DM::transition<bool, data_handler_impl> transition{state1, state2, m_event1, m_event2};
    m_event_generator.update();
    transition.update();
    EXPECT_FALSE(transition.is_events_list_empty());
    EXPECT_TRUE(transition.get_transition_value());
}

TEST_F(transition_fixture, constructor_set) {
    std::shared_ptr<state_impl> state1 = std::make_shared<state_impl>("state1", m_data_holder);
    std::shared_ptr<state_impl> state2 = std::make_shared<state_impl>("state2", m_data_holder);
    DM::transition<bool, data_handler_impl> transition{state1, state2};
    transition.set(m_event1);
    transition.set(m_event2);
    m_event_generator.update();
    transition.update();
    EXPECT_FALSE(transition.is_events_list_empty());
    EXPECT_TRUE(transition.get_transition_value());
}

TEST_F(transition_fixture, remove_empty) {
    std::shared_ptr<state_impl> state1 = std::make_shared<state_impl>("state1", m_data_holder);
    std::shared_ptr<state_impl> state2 = std::make_shared<state_impl>("state2", m_data_holder);
    DM::transition<bool, data_handler_impl> transition{state1, state2, m_event1, m_event2};
    transition.remove(m_event1);
    transition.remove(m_event2);
    m_event_generator.update();
    transition.update();
    EXPECT_TRUE(transition.is_events_list_empty());
    EXPECT_FALSE(transition.get_transition_value());
}