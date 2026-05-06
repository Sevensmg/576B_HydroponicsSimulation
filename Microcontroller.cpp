#include "Microcontroller.h"
#include <iostream>
#include <iomanip>

void Microcontroller::control_loop() {
    // Start off in case of no signal
    actuator_water_add_cmd_out.write(false);
    actuator_led_cmd_out.write(false);
    actuator_ph_add_cmd_out.write(false);

    while (true) {
        // Water Level
        double level = sensor_water_level_in.read();
        bool water_add_cmd = actuator_water_add_cmd_out.read();
        double ph_level = sensor_ph_level_in.read();
        bool ph_cmd = actuator_ph_add_cmd_out.read();

        // LEDs
        led_cmd = actuator_led_cmd_out.read();


        // Water Fill logic
        if (level < low_threshold) {
            water_add_cmd = true;
        } else if (level >= full_threshold) {
            water_add_cmd = false;
        }
      
              // ph logic
        if ((ph_level < low_threshold || ph_level > high_threshold)) {

            ph_cmd = true;
        } 
        
        else{//if (level > low_threshold && level < high_threshold) {
            ph_cmd = false;
        }

        // LED Logic | on 16 then off 8
        unsigned long elapsed_seconds = static_cast<unsigned long>(sc_time_stamp().to_seconds());
        unsigned long seconds_in_day = elapsed_seconds % (24 * 60 * 60);
        led_cmd = seconds_in_day < (16 * 60 * 60);

        // Write to actuators
        actuator_water_add_cmd_out.write(water_add_cmd);
        actuator_led_cmd_out.write(led_cmd);

        actuator_ph_add_cmd_out.write(ph_cmd);
       
        std::cout << "[" << sc_time_stamp() << "] "
                  << "MCU: ph_level=" << std::fixed << std::setprecision(2)
                  << ph_level << " ph_add_cmd=" << ph_cmd
                  << "MCU: water_level=" << std::fixed << std::setprecision(2)
                  << level << "%, water_add_cmd=" << water_add_cmd
                  << std::endl;

        wait(control_period);
    }
}