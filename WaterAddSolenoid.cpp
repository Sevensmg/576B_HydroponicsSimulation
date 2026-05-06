#include "WaterAddSolenoid.h"
#include <iostream>

void WaterAddSolenoid::run() {
    actuator_water_add_active_out.write(false);

    while (true) {
        bool cmd = actuator_water_add_cmd_in.read();

        if (actuator_delay > SC_ZERO_TIME) {
            wait(actuator_delay);
        }

        actuator_water_add_active_out.write(cmd);

        std::cout << "[" << sc_time_stamp() << "] "
                  << "WaterAddSolenoid: cmd=" << cmd
                  << ", active=" << cmd
                  << std::endl;

        wait(actuator_water_add_cmd_in.value_changed_event());
    }
}