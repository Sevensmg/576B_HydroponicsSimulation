#include "Microcontroller.h"
#include <iostream>
#include <iomanip>

void Microcontroller::control_loop() {
    // Start off in case of no signal
    actuator_water_add_cmd_out.write(false);
    actuator_nutrient_pump_cmd_out.write(false);

    while (true) {
        double level = sensor_water_level_in.read();
        bool water_cmd = actuator_water_add_cmd_out.read();
        bool nutrient_cmd = actuator_nutrient_pump_cmd_out.read();

        // Fill logic
        if (level < low_threshold) {
            water_cmd = true;
        } else if (level >= full_threshold) {
            water_cmd = false;
        }

        // Simple Nutrient logic: Add nutrients whenever water is being added
        nutrient_cmd = water_cmd;

        actuator_water_add_cmd_out.write(water_cmd);
        actuator_nutrient_pump_cmd_out.write(nutrient_cmd);

        std::cout << "[" << sc_time_stamp() << "] "
                  << "MCU: water_level=" << std::fixed << std::setprecision(2)
                  << level << "%, water_cmd=" << water_cmd
                  << ", nutrient_cmd=" << nutrient_cmd
                  << std::endl;

        wait(control_period);
    }
}