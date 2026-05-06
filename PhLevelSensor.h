#ifndef PH_LEVEL_SENSOR_H
#define PH_LEVEL_SENSOR_H

#include <systemc.h>

SC_MODULE(PhSensor) {
public:
    // Input from physical model (true environment value)
    sc_in<double> physical_ph_level_in;

    // Output to controller (measured sensor value)
    sc_out<double> sensor_ph_level_out;

    // Sensor parameters
    sc_time sample_period;

    double ph_min_measurable_level;
    double ph_max_measurable_level;

    SC_CTOR(PhSensor) :
        sample_period(sc_time(1, SC_SEC)),
        min_measurable_level(0.0),
        max_measurable_level(14.0)
    {
        SC_THREAD(sample_loop);
    }

private:
    void sample_loop();
    double clamp(double value, double ph_min_value, double ph_max_value);
};

#endif