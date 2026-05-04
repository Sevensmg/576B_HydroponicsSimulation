#include "WaterPump.h"
#include <iostream>

void WaterPump::run() {
    actuator_water_pump_active_out.write(false);

    while (true) {
        bool cmd = actuator_water_pump_cmd_in.read();

        if (actuator_delay > SC_ZERO_TIME) {
            wait(actuator_delay);
        }

        actuator_water_pump_active_out.write(cmd);

        std::cout << "[" << sc_time_stamp() << "] "
                  << "WaterPump: cmd=" << cmd
                  << ", active=" << cmd
                  << std::endl;

        wait(actuator_water_pump_cmd_in.value_changed_event());
    }
}
