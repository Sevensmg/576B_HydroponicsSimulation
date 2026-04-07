#include "Microcontroller.h"
#include <iostream>
#include <iomanip>

void Microcontroller::control_loop() {
    // Safe startup state
    actuator_water_add_cmd_out.write(false);

    while (true) {
        double level = sensor_water_level_in.read();
        bool cmd = actuator_water_add_cmd_out.read();

        // Hysteresis-style fill logic
        if (level < low_threshold) {
            cmd = true;
        } else if (level >= full_threshold) {
            cmd = false;
        }

        actuator_water_add_cmd_out.write(cmd);

        std::cout << "[" << sc_time_stamp() << "] "
                  << "MCU: water_level=" << std::fixed << std::setprecision(2)
                  << level << "%, water_add_cmd=" << cmd
                  << std::endl;

        wait(control_period);
    }
}