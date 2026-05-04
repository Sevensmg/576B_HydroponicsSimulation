#include "Microcontroller.h"
#include <iostream>
#include <iomanip>

void Microcontroller::control_loop() {
    // Start off in case of no signal
    actuator_water_add_cmd_out.write(false);
    actuator_water_pump_cmd_out.write(false);

    while (true) {
        double level = sensor_water_level_in.read();
        bool cmd = actuator_water_add_cmd_out.read();

        // Fill logic
        if (level < low_threshold) {
            cmd = true;
        } else if (level >= full_threshold) {
            cmd = false;
        }

        actuator_water_add_cmd_out.write(cmd);

        // Pump logic (simple duty cycle)
        sc_time current_time = sc_time_stamp();

        if (pump_cmd) {
            if (current_time - last_pump_toggle >= pump_on_time) {
                pump_cmd = false;
                last_pump_toggle = current_time;
            }
        } else {
            if (current_time - last_pump_toggle >= pump_off_time) {
                pump_cmd = true;
                last_pump_toggle = current_time;
            }
        }
        actuator_water_pump_cmd_out.write(pump_cmd);

        std::cout << "[" << sc_time_stamp() << "] "
                  << "MCU: water_level=" << std::fixed << std::setprecision(2)
                  << level << "%, water_add_cmd=" << cmd
                  << ", water_pump_cmd=" << pump_cmd
                  << std::endl;

        wait(control_period);
    }
}