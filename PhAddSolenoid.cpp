#include "PhAddSolenoid.h"
#include <iostream>

void PhAddSolenoid::run() {
    actuator_ph_add_active_out.write(0);

    while (true) {
        bool ph_cmd = actuator_ph_add_cmd_in.read();

        if (actuator_delay > SC_ZERO_TIME) {
            wait(actuator_delay);
        }

        actuator_ph_add_active_out.write(ph_cmd);

        std::cout << "[" << sc_time_stamp() << "] "
                  << "PhAddSolenoid: cmd=" << ph_cmd
                  << ", active=" << ph_cmd
                  << std::endl;

        wait(actuator_ph_add_cmd_in.value_changed_event());
    }
}