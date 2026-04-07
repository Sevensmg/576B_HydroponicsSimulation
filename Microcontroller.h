// Header File for the Microcontroller

#ifndef MICROCONTROLLER_H
#define MICROCONTROLLER_H

#include <systemc.h>

SC_MODULE(Microcontroller) {
public:
    // Inputs
    sc_in<double> sensor_water_level_in;

    // Outputs
    sc_out<bool> actuator_water_add_cmd_out;

    // Tunable parameters
        // Water Level
    double low_threshold;
    double full_threshold;
    sc_time control_period;

    SC_CTOR(Microcontroller) :
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