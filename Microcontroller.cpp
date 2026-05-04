#include "Microcontroller.h"
#include <iostream>
#include <iomanip>

void Microcontroller::control_loop() {
    // Start off in case of no signal
    actuator_water_add_cmd_out.write(false);
    actuator_water_pump_cmd_out.write(false);
    actuator_nutrient_pump_cmd_out.write(false);

    while (true) {
        double level = sensor_water_level_in.read();
        double n_level = sensor_nutrient_level_in.read();
        bool cmd = actuator_water_add_cmd_out.read();
        bool n_cmd = actuator_nutrient_pump_cmd_out.read();

        // Water Fill logic
        if (level < low_threshold) {
            cmd = true;
        } else if (level >= full_threshold) {
            cmd = false;
        }

        // Nutrient logic
        if (n_level < nutrient_low_threshold) {
            n_cmd = true;
        } else if (n_level >= nutrient_full_threshold) {
            n_cmd = false;
        }

        // Water Pump Schedule logic
        if (sc_time_stamp() >= next_pump_event) {
            pump_state = !pump_state;
            if (pump_state) {
                next_pump_event = sc_time_stamp() + pump_on_time;
            } else {
                next_pump_event = sc_time_stamp() + pump_off_time;
            }
        }

        actuator_water_add_cmd_out.write(cmd);
        actuator_water_pump_cmd_out.write(pump_state);
        actuator_nutrient_pump_cmd_out.write(n_cmd);

        std::cout << "[" << sc_time_stamp() << "] "
                  << "MCU: water_level=" << std::fixed << std::setprecision(2)
                  << level << "%, nutrient_level=" << n_level
                  << ", water_cmd=" << cmd << ", nutrient_cmd=" << n_cmd
                  << ", pump_cmd=" << pump_state
                  << std::endl;

        wait(control_period);
    }
}