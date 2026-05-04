// Header File for the Microcontroller

#ifndef MICROCONTROLLER_H
#define MICROCONTROLLER_H

#include <systemc.h>

SC_MODULE(Microcontroller) {
public:
    // Inputs
    sc_in<double> sensor_water_level_in;
    sc_in<double> sensor_nutrient_level_in;

    // Outputs
    sc_out<bool> actuator_water_add_cmd_out;
    sc_out<bool> actuator_water_pump_cmd_out;
    sc_out<bool> actuator_nutrient_pump_cmd_out;

    // Tunable parameters
        // Water Level
    double low_threshold;
    double full_threshold;

        // Nutrient Level
    double nutrient_low_threshold;
    double nutrient_full_threshold;

        // Pump Timing
    sc_time pump_on_time;
    sc_time pump_off_time;
    sc_time next_pump_event;
    bool pump_state;

    sc_time control_period;

    SC_CTOR(Microcontroller) :
        // Water Level - Ideal is 88.88-%
        low_threshold(88.88 - 5),
        full_threshold(88.88 + 3),
        // Nutrient Level - Ideal is 100
        nutrient_low_threshold(95.0),
        nutrient_full_threshold(105.0),
        // Pump Timing - Run for 5s every 15s
        pump_on_time(sc_time(5, SC_SEC)),
        pump_off_time(sc_time(10, SC_SEC)),
        pump_state(false),
        next_pump_event(SC_ZERO_TIME),
        // Time Step
        control_period(sc_time(1, SC_SEC))
    {
        SC_THREAD(control_loop);
    }

private:
    void control_loop();
};

#endif