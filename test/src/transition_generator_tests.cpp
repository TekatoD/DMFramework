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
#include "transition_generator.h"

class transition_generator_fixture : public ::testing::Test {
public:
    typedef std::shared_ptr<data_handler_impl> dh_ptr;
    typedef DM::abstract_event<bool, data_handler_impl> ev;
    transition_generator_fixture() : m_data_holder(std::make_shared<data_handler_impl>()), m_event_generator(m_data_holder) {
        m_data_holder->update();
        m_event1 = std::make_shared<ev>([](dh_ptr dH){
            return dH->get_x() == 6.0;
        });
        m_event2 = std::make_shared<ev>([](dh_ptr dH){
            return dH->get_t();
        });
        m_event_generator.set(m_event1);
        m_event_generator.set(m_event2);
        m_state1 = std::make_shared<state_impl>("state1", m_data_holder);
        m_state2 = std::make_shared<state_impl>("state2", m_data_holder);
    }

    ~transition_generator_fixture() {
        //Destroy all the good members
    }

protected:
    std::shared_ptr<ev> m_event1;
    std::shared_ptr<ev> m_event2;
    dh_ptr m_data_holder;
    DM::event_data_handler<bool, data_handler_impl> m_event_generator;
    std::shared_ptr<state_impl> m_state1;
    std::shared_ptr<state_impl> m_state2;
};

TEST_F(transition_generator_fixture, constructor_update) {
    DM::transition<data_handler_impl> transition{m_state1, m_state2, m_event1, m_event2};
    DM::transition_generator<data_handler_impl> transitionGenerator({transition});
    m_event_generator.update();
    std::shared_ptr<DM::abstract_state<data_handler_impl>> curr = transitionGenerator.update(m_state1);
    EXPECT_TRUE(transitionGenerator.is_transitions_exist());
    EXPECT_EQ(curr, m_state2);
    curr = transitionGenerator.update(m_state2);
    EXPECT_EQ(curr, m_state2);
}

TEST_F(transition_generator_fixture, constructor_set) {
    DM::transition<data_handler_impl> transition{m_state1, m_state2, m_event1, m_event2};
    DM::transition_generator<data_handler_impl> transitionGenerator;
    transitionGenerator.set(transition);
    m_event_generator.update();
    std::shared_ptr<DM::abstract_state<data_handler_impl>> curr = transitionGenerator.update(m_state1);
    EXPECT_TRUE(transitionGenerator.is_transitions_exist());
    EXPECT_EQ(curr, m_state2);
    curr = transitionGenerator.update(m_state2);
    EXPECT_EQ(curr, m_state2);
}

TEST_F(transition_generator_fixture, r_value_constructor_update) {
    DM::transition_generator<data_handler_impl> transitionGenerator({DM::transition<data_handler_impl>{m_state1,
                                                                                                       m_state2,
                                                                                                       m_event1,
                                                                                                       m_event2}});
    m_event_generator.update();
    std::shared_ptr<DM::abstract_state<data_handler_impl>> curr = transitionGenerator.update(m_state1);
    EXPECT_TRUE(transitionGenerator.is_transitions_exist());
    EXPECT_EQ(curr, m_state2);
    curr = transitionGenerator.update(m_state2);
    EXPECT_EQ(curr, m_state2);
}

TEST_F(transition_generator_fixture, constructor_r_value_set) {
    DM::transition_generator<data_handler_impl> transitionGenerator;
    transitionGenerator.set(DM::transition<data_handler_impl>{m_state1, m_state2, m_event1, m_event2});
    m_event_generator.update();
    std::shared_ptr<DM::abstract_state<data_handler_impl>> curr = transitionGenerator.update(m_state1);
    EXPECT_TRUE(transitionGenerator.is_transitions_exist());
    EXPECT_EQ(curr, m_state2);
    curr = transitionGenerator.update(m_state2);
    EXPECT_EQ(curr, m_state2);
}

TEST_F(transition_generator_fixture, remove_empty) {
    DM::transition_generator<data_handler_impl> transitionGenerator;
    transitionGenerator.set(DM::transition<data_handler_impl>{m_state1, m_state2, m_event1, m_event2});
    m_event_generator.update();
    transitionGenerator.remove(DM::transition<data_handler_impl>{m_state1, m_state2, m_event1, m_event2});
    std::shared_ptr<DM::abstract_state<data_handler_impl>> curr = transitionGenerator.update(m_state1);
    EXPECT_FALSE(transitionGenerator.is_transitions_exist());
    EXPECT_NE(curr, m_state2);
}