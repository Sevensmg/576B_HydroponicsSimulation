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

    // Tunable parameters
        // ph Level
    double low_threshold;
    double high_threshold;
    sc_time control_period;

    SC_CTOR(Microcontroller) :
        // PH Level - Ideal is 5.5-6.5
        low_threshold(6 - 0.5),
        high_threshold(6 + 0.5),
        // Time Step
        control_period(sc_time(1, SC_SEC))
    {
        SC_THREAD(control_loop);
    }

private:
    void control_loop();
};

#endif