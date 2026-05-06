#include "AirPump.h"
#include <iostream>

void AirPump::run() {
    actuator_air_pump_active_out.write(false);

    while (true) {
        bool cmd = actuator_air_pump_cmd_in.read();

        if (actuator_delay > SC_ZERO_TIME) {
            wait(actuator_delay);
        }

        actuator_air_pump_active_out.write(cmd);

        std::cout << "[" << sc_time_stamp() << "] "
                  << "AirPump: cmd=" << cmd
                  << ", active=" << cmd
                  << std::endl;

        wait(actuator_air_pump_cmd_in.value_changed_event());
    }
}
