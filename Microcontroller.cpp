#include "Microcontroller.h"
#include <iostream>
#include <iomanip>

void Microcontroller::control_loop() {
    // Start off in case of no signal
    actuator_ph_add_cmd_out.write(false);;
    
    while (true) {

        double ph_level = sensor_ph_level_in.read();
        bool ph_cmd = actuator_ph_add_cmd_out.read();
       
        // Fill logic
        if ((ph_level < low_threshold || ph_level > high_threshold)) {

            ph_cmd = true;
        } 
        
        else{//if (level > low_threshold && level < high_threshold) {
            ph_cmd = false;
        }

       actuator_ph_add_cmd_out.write(ph_cmd);
       
        std::cout << "[" << sc_time_stamp() << "] "
                  << "MCU: ph_level=" << std::fixed << std::setprecision(2)
                  << ph_level << " ph_add_cmd=" << ph_cmd
                  << std::endl;

        wait(control_period);
    }
}