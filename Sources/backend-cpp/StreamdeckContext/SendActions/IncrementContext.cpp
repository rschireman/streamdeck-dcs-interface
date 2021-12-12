// Copyright 2021 Charles Tytler

#include "IncrementContext.h"

#include "ElgatoSD/EPLJSONUtils.h"

void IncrementContext::handleButtonPressedEvent(const std::unique_ptr<SimulatorInterface> &simulator_interface,
                                                ESDConnectionManager *mConnectionManager,
                                                const json &inPayload)
{
    const auto send_address = EPLJSONUtils::GetStringByName(inPayload["settings"], "send_address");

    const auto send_command = determineSendValue(inPayload["settings"]);
    if (send_command) {
        simulator_interface->send_simulator_command(send_address, send_command.value());
    }
}

void IncrementContext::handleButtonReleasedEvent(const std::unique_ptr<SimulatorInterface> &simulator_interface,
                                                 ESDConnectionManager *mConnectionManager,
                                                 const json &inPayload)
{
    // The Streamdeck will by default change a context's state after a KeyUp event, so a force send of the current
    // context's state will keep the button state in sync with the plugin.
    forceSendState(mConnectionManager);

    // Nothing sent to DCS on release.
}

std::optional<std::string> IncrementContext::determineSendValue(const json &settings)
{
    const auto increment_cmd_value_str = EPLJSONUtils::GetStringByName(settings, "increment_value");
    const auto increment_min_str = EPLJSONUtils::GetStringByName(settings, "increment_min");
    const auto increment_max_str = EPLJSONUtils::GetStringByName(settings, "increment_max");
    const bool cycling_is_allowed = EPLJSONUtils::GetBoolByName(settings, "increment_cycle_allowed_check");

    if (is_number(increment_cmd_value_str) && is_number(increment_min_str) && is_number(increment_max_str)) {
        const auto value = increment_monitor_.get_increment_after_command(Decimal(increment_cmd_value_str),
                                                                          Decimal(increment_min_str),
                                                                          Decimal(increment_max_str),
                                                                          cycling_is_allowed);
        return value.str();
    }
    return std::nullopt;
}