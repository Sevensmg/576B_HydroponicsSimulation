#include "NutrientPump.h"
#include <iostream>

void NutrientPump::run() {
    actuator_nutrient_pump_active_out.write(false);

    while (true) {
        bool cmd = actuator_nutrient_pump_cmd_in.read();

        if (actuator_delay > SC_ZERO_TIME) {
            wait(actuator_delay);
        }

        actuator_nutrient_pump_active_out.write(cmd);

        std::cout << "[" << sc_time_stamp() << "] "
                  << "NutrientPump: cmd=" << cmd
                  << ", active=" << cmd
                  << std::endl;

        wait(actuator_nutrient_pump_cmd_in.value_changed_event());
    }
}
