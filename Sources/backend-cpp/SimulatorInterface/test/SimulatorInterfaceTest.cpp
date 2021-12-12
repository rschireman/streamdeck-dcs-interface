// Copyright 2020 Charles Tytler

#include "gtest/gtest.h"

#include "SimulatorInterface/SimulatorInterface.h"

namespace test
{
TEST(SimulatorInterfaceTest, invalid_connection_port_settings)
{
    const SimulatorConnectionSettings connection_settings = {"19ab", "abc", "127.0.0.1", ""};
    EXPECT_THROW(SimulatorInterface simulator_interface(connection_settings), std::runtime_error);
}

TEST(SimulatorInterfaceTest, udp_connect_on_construction_without_multicast)
{
    const SimulatorConnectionSettings connection_settings = {"1908", "1909", "127.0.0.1", ""};
    SimulatorInterface simulator_interface(connection_settings);
    // Expect no errors thrown.
    EXPECT_TRUE(simulator_interface.connection_settings_match(connection_settings));
}

TEST(SimulatorInterfaceTest, udp_connect_on_construction_with_multicast)
{
    const SimulatorConnectionSettings connection_settings = {"1908", "1909", "0.0.0.0", "239.255.50.10"};
    SimulatorInterface simulator_interface(connection_settings);
    // Expect no errors thrown.
    EXPECT_TRUE(simulator_interface.connection_settings_match(connection_settings));
}

TEST(SimulatorInterfaceTest, connection_settings_match_false)
{
    const SimulatorConnectionSettings connection_settings = {"1908", "1909", "127.0.0.1", ""};
    SimulatorInterface simulator_interface(connection_settings);
    SimulatorConnectionSettings mismatched_connection_settings = {"1111", "2222", "127.0.0.1", ""};
    EXPECT_FALSE(simulator_interface.connection_settings_match(mismatched_connection_settings));
}

TEST(SimulatorInterfaceTest, empty_game_state_on_initialization)
{
    SimulatorInterface simulator_interface(SimulatorConnectionSettings{"1908", "1909", "127.0.0.1", ""});
    // Test that current game state initializes as empty.
    std::unordered_map<int, std::string> current_game_state = simulator_interface.debug_get_current_game_state();
    EXPECT_EQ(0, current_game_state.size());
}

TEST(SimulatorInterfaceTest, get_current_module_initial_value)
{
    SimulatorInterface simulator_interface(SimulatorConnectionSettings{"1908", "1909", "127.0.0.1", ""});
    // Test that the default value of an empty string is returned after initialization.
    EXPECT_EQ("", simulator_interface.get_current_simulator_module());
}

TEST(SimulatorInterfaceTest, get_value_of_default_constructed_simulator_state)
{
    SimulatorInterface simulator_interface(SimulatorConnectionSettings{"1908", "1909", "127.0.0.1", ""});
    EXPECT_FALSE(simulator_interface.get_value_of_simulator_object_state(999));
}

TEST(SimulatorInterfaceTest, get_decimal_of_default_constructed_simulator_state)
{
    SimulatorInterface simulator_interface(SimulatorConnectionSettings{"1908", "1909", "127.0.0.1", ""});
    EXPECT_FALSE(simulator_interface.get_decimal_of_simulator_object_state(999));
}

} // namespace test