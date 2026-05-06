#include "Microcontroller.h"
#include <iostream>
#include <iomanip>

void Microcontroller::control_loop() {
    // Start off in case of no signal
    actuator_water_add_cmd_out.write(false);
    actuator_led_cmd_out.write(false);
    actuator_ph_add_cmd_out.write(false);
    actuator_water_pump_cmd_out.write(false);
    actuator_nutrient_pump_cmd_out.write(false);

    while (true) {
        // Water Level
        double level = sensor_water_level_in.read();
        bool water_add_cmd = actuator_water_add_cmd_out.read();
        bool cmd = actuator_water_add_cmd_out.read();
        // pH
        double ph_level = sensor_ph_level_in.read();
        bool ph_cmd = actuator_ph_add_cmd_out.read();
        // LEDs
        led_cmd = actuator_led_cmd_out.read();
        // Nutrients
        double n_level = sensor_nutrient_level_in.read();
        bool n_cmd = actuator_nutrient_pump_cmd_out.read();

        // Water Fill logic
        if (level < low_threshold) {
            water_add_cmd = true;
        } else if (level >= full_threshold) {
            water_add_cmd = false;
        }
      
              // ph logic
        if ((ph_level < ph_low_threshold || ph_level > ph_high_threshold)) {

            ph_cmd = true;
        } 
        
        else{//if (level > low_threshold && level < high_threshold) {
            ph_cmd = false;
        }

        // LED Logic | on 16 then off 8
        unsigned long elapsed_seconds = static_cast<unsigned long>(sc_time_stamp().to_seconds());
        unsigned long seconds_in_day = elapsed_seconds % (24 * 60 * 60);
        led_cmd = seconds_in_day < (16 * 60 * 60);
        
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

        // Write to actuators
        actuator_water_add_cmd_out.write(water_add_cmd);
        actuator_led_cmd_out.write(led_cmd);

        actuator_ph_add_cmd_out.write(ph_cmd);
       
        std::cout << "[" << sc_time_stamp() << "] "
                  << "MCU: ph_level= " << std::fixed << std::setprecision(2)
                  << ph_level << " ph_add_cmd=" << ph_cmd
                  << "MCU: water_level=" << std::fixed << std::setprecision(2)
                  << level << "%, water_add_cmd=" << water_add_cmd
                  << level << "%, nutrient_level=" << n_level
                  << ", water_cmd=" << cmd << ", nutrient_cmd=" << n_cmd
                  << ", pump_cmd=" << pump_state
                  << std::endl;

        wait(control_period);
    }
}