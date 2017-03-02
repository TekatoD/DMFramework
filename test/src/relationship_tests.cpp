/**
 *  @autor tekatod
 *  @date 3/2/17
 */
#include <gtest/gtest.h>
#include "include/data_handler_impl.h"
#include "include/state_impl.h"
#include "abstract_event.h"
#include "event_data_handler.h"
#include "transition.h"
#include "relationship.h"

class relationship_fixture : public ::testing::Test {
public:
    typedef std::shared_ptr<data_handler_impl> dh_ptr;
    typedef DM::abstract_event<double, data_handler_impl> ev;
    relationship_fixture() : m_data_holder(std::make_shared<data_handler_impl>()), m_event_generator(m_data_holder) {
        m_data_holder->update();
        m_event1 = std::make_shared<ev>([](dh_ptr dH){
            return 1.0 / dH->get_x();
        });
        m_event2 = std::make_shared<ev>([](dh_ptr dH){
            return 1.0 / dH->get_y();
        });
        m_event_generator.set(m_event1);
        m_event_generator.set(m_event2);

    }

    ~relationship_fixture() {
        //Destroy all the good members
    }

protected:
    std::shared_ptr<ev> m_event1;
    std::shared_ptr<ev> m_event2;
    dh_ptr m_data_holder;
    DM::event_data_handler<double, data_handler_impl> m_event_generator;
};

TEST_F(relationship_fixture, constructor_update) {
    std::shared_ptr<state_impl> state1 = std::make_shared<state_impl>("state1", m_data_holder);
    std::shared_ptr<state_impl> state2 = std::make_shared<state_impl>("state2", m_data_holder);
    DM::relationship<data_handler_impl> transition{state1, state2, m_event1, m_event2};
    m_event_generator.update();
    transition.update();
    EXPECT_FALSE(transition.is_events_list_empty());
    EXPECT_EQ(transition.get_transition_value(), (double)((1 / 6.0) * (1 / 9.0)));
}

TEST_F(relationship_fixture, constructor_set) {
    std::shared_ptr<state_impl> state1 = std::make_shared<state_impl>("state1", m_data_holder);
    std::shared_ptr<state_impl> state2 = std::make_shared<state_impl>("state2", m_data_holder);
    DM::relationship<data_handler_impl> transition{state1, state2};
    transition.set(m_event1);
    transition.set(m_event2);
    m_event_generator.update();
    transition.update();
    EXPECT_FALSE(transition.is_events_list_empty());
    EXPECT_EQ(transition.get_transition_value(), (double)((1 / 6.0) * (1 / 9.0)));
}

TEST_F(relationship_fixture, remove_empty) {
    std::shared_ptr<state_impl> state1 = std::make_shared<state_impl>("state1", m_data_holder);
    std::shared_ptr<state_impl> state2 = std::make_shared<state_impl>("state2", m_data_holder);
    DM::relationship<data_handler_impl> transition{state1, state2, m_event1, m_event2};
    transition.remove(m_event1);
    transition.remove(m_event2);
    m_event_generator.update();
    transition.update();
    EXPECT_TRUE(transition.is_events_list_empty());
    EXPECT_FALSE(transition.get_transition_value());
}