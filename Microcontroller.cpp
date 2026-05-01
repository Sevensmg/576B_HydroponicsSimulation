#include "Microcontroller.h"
#include <iostream>
#include <iomanip>

void Microcontroller::control_loop() {
    // Start off in case of no signal
    actuator_ph_add_cmd_out.write(false);;
    
    while (true) {

        double level = sensor_ph_level_in.read();
        bool cmd = actuator_ph_add_cmd_out.read();
       
        // Fill logic
        if ((level < low_threshold || level > high_threshold)) {

            cmd = true;
        } 
        
        else{//if (level > low_threshold && level < high_threshold) {
            cmd = false;
        }

       actuator_ph_add_cmd_out.write(cmd);
       
        std::cout << "[" << sc_time_stamp() << "] "
                  << "MCU: ph_level=" << std::fixed << std::setprecision(2)
                  << level << " ph_add_cmd=" << cmd
                  << std::endl;

        wait(control_period);
    }
}