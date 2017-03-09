/**
 *  @autor tekatod
 *  @date 3/9/17
 */
#include <gtest/gtest.h>
#include <state_machine.h>
#include "include/data_handler_impl.h"
#include "include/state_impl.h"

class state_machine_fixture : public ::testing::Test {
public:
    typedef std::shared_ptr<data_handler_impl> dh_ptr;
    typedef DM::abstract_event<bool, data_handler_impl> ev;
    typedef DM::abstract_event<double , data_handler_impl> ev2;
    state_machine_fixture() : m_data_holder(std::make_shared<data_handler_impl>()), m_event_generator(m_data_holder),
                              m_event1(std::make_shared<ev>([](dh_ptr dH){
                                  return dH->get_x() == 6.0;
                              })),
                              m_event2(std::make_shared<ev>([](dh_ptr dH){
                                  return dH->get_t();
                              })),
                              m_state1(std::make_shared<state_impl>("state1", m_data_holder)),
                              m_state2(std::make_shared<state_impl>("state2", m_data_holder)),
                              m_state3(std::make_shared<state_impl>("state3", m_data_holder)),
                              m_transition(m_state1, m_state2, m_event1, m_event2),
                              m_transition_generator({m_transition}){
        m_data_holder->update();
        m_event_generator.set(m_event1);
        m_event_generator.set(m_event2);
    }

    ~state_machine_fixture() {
        //Destroy all the good members
    }

protected:
    std::shared_ptr<ev> m_event1;
    std::shared_ptr<ev> m_event2;
    dh_ptr m_data_holder;
    DM::event_data_handler<bool, data_handler_impl> m_event_generator;
    std::shared_ptr<state_impl> m_state1;
    std::shared_ptr<state_impl> m_state2;
    std::shared_ptr<state_impl> m_state3;
    DM::transition<data_handler_impl> m_transition;
    DM::transition_generator<data_handler_impl> m_transition_generator;
};

TEST_F(state_machine_fixture, first_constructor) {
    DM::state_machine<DM::transition_generator<data_handler_impl>> s_m(m_transition_generator, m_event_generator, m_state1);
    s_m.run();
    EXPECT_EQ(m_data_holder->get_curr_state(), m_state2->get_name());
}

TEST_F(state_machine_fixture, second_constructor_setters) {
    DM::state_machine<DM::transition_generator<data_handler_impl>> s_m(m_data_holder, m_state1);
    s_m.add_event(m_event1);
    s_m.add_event(m_event2);
    s_m.add_transition(m_transition);
    s_m.remove_transition(m_transition);
    s_m.run();
    EXPECT_NE(m_data_holder->get_curr_state(), m_state2->get_name());
    s_m.add_transition(m_transition);
    s_m.run();
    EXPECT_EQ(m_data_holder->get_curr_state(), m_state2->get_name());
}

TEST_F(state_machine_fixture, realtionship_tests) {
    DM::state_machine<DM::relationship_generator<data_handler_impl>> s_m(m_data_holder, m_state1);
    EXPECT_TRUE(s_m.get_factors().empty());
    std::shared_ptr<ev2> event1  = std::make_shared<ev2>([](dh_ptr dH){
        return 1.0 / dH->get_x();
    });
    std::shared_ptr<ev2> event2 = std::make_shared<ev2>([](dh_ptr dH){
        return 1.0 / dH->get_y();
    });
    std::shared_ptr<ev2> event3 = std::make_shared<ev2>([](dh_ptr dH){
        return 0.0;
    });
    s_m.add_event(event1);
    s_m.add_event(event2);
    s_m.add_event(event3);
    s_m.add_transition(DM::relationship<data_handler_impl>{m_state1, m_state2, event1, event2});
    s_m.add_transition(DM::relationship<data_handler_impl>{m_state1, m_state3, event3});
    s_m.run();
    EXPECT_EQ(m_data_holder->get_curr_state(), m_state2->get_name());
    s_m.run();
    EXPECT_EQ(m_data_holder->get_curr_state(), m_state2->get_name());
}
