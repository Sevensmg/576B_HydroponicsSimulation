#ifndef NUTRIENT_SENSOR_H
#define NUTRIENT_SENSOR_H

#include <systemc.h>

SC_MODULE(NutrientSensor) {
public:
    // Input from physical model (true environment value)
    sc_in<double> physical_nutrient_level_in;

    // Output to controller (measured sensor value)
    sc_out<double> sensor_nutrient_level_out;

    // Sensor parameters
    sc_time sample_period;
    double sensor_bias;
    double min_measurable_level;
    double max_measurable_level;

    SC_CTOR(NutrientSensor) :
        sample_period(sc_time(1, SC_SEC)),
        sensor_bias(0.0),
        min_measurable_level(0.0),
        max_measurable_level(100.0)
    {
        SC_THREAD(sample_loop);
    }

private:
    void sample_loop();
    double clamp(double value, double min_value, double max_value);
};

#endif
