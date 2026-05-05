#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <systemc.h>

SC_MODULE(LEDController) {
public:
    // Inputs
    sc_in<bool> actuator_led_cmd_in;

    // Outputs
    sc_out<bool> actuator_led_state_out;

private:
    void run();
};

#endif