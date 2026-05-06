// Header File for the Microcontroller

#ifndef MICROCONTROLLER_H
#define MICROCONTROLLER_H

#include <systemc.h>

SC_MODULE(Microcontroller) {
public:
    // Inputs
    sc_in<double> sensor_ph_level_in;

    // Outputs
    sc_out<bool> actuator_ph_add_cmd_out;
  
        // ph Level
    double ph_low_threshold;
    double ph_high_threshold;
  
    sc_out<bool> actuator_water_add_cmd_out;
    sc_out<bool> actuator_led_cmd_out;

    // Tunable parameters
        // Water Level
    double low_threshold;
    double full_threshold;
        // LED
    bool led_cmd;
    sc_time control_period;

    SC_CTOR(Microcontroller) :
        // PH Level - Ideal is 5.5-6.5
        ph_low_threshold(6 - 0.5),
        ph_high_threshold(6 + 0.5),
        // Water Level - Ideal is 88.88-%
        low_threshold(88.88 - 5),
        full_threshold(88.88 + 3),
        // Time Step
        control_period(sc_time(1, SC_SEC))
    {
        SC_THREAD(control_loop);
    }

private:
    void control_loop();
};

#endif