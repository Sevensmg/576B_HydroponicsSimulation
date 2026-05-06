#include "LEDController.h"
#include <iostream>

void LEDController::run() {
    actuator_led_state_out.write(0);

    while (true) {
        bool led_cmd = actuator_led_cmd_in.read();

        // Pass information on
        actuator_led_state_out.write(led_cmd);

        // Output to Console
        std::cout << "[" << sc_time_stamp() << "] "
                  << "WaterAddSolenoid: led_cmd=" << led_cmd
                  << ", active=" << led_cmd
                  << std::endl;

        wait(actuator_led_cmd_in.value_changed_event());
    }
}