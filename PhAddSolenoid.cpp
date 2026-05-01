#include "PhAddSolenoid.h"
#include <iostream>

void PhAddSolenoid::run() {
    actuator_ph_add_active_out.write(0);

    while (true) {
        bool cmd = actuator_ph_add_cmd_in.read();

        if (actuator_delay > SC_ZERO_TIME) {
            wait(actuator_delay);
        }

        actuator_ph_add_active_out.write(cmd);

        std::cout << "[" << sc_time_stamp() << "] "
                  << "PhAddSolenoid: cmd=" << cmd
                  << ", active=" << cmd
                  << std::endl;

        wait(actuator_ph_add_cmd_in.value_changed_event());
    }
}