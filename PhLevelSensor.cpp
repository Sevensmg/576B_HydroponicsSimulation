#include "PhLevelSensor.h"
#include <iostream>
#include <iomanip>

double PhSensor::clamp(double value, double ph_min_value, double ph_max_value) {
    if (value < ph_min_value) {
        return ph_min_value;
    }
    if (value > ph_max_value) {
        return ph_max_value;
    }
    return value;
}

void PhSensor::sample_loop() {
    // Initialize output once at time 0
    double ph_true_level = physical_ph_level_in.read();
    double ph_measured_level = clamp(ph_true_level,
                                  ph_min_measurable_level,
                                  ph_max_measurable_level);
    sensor_ph_level_out.write(ph_measured_level);

    while (true) {
        ph_true_level = physical_ph_level_in.read();

        ph_measured_level = ph_true_level;

        // Clamp
        ph_measured_level = clamp(ph_measured_level,
                               ph_min_measurable_level,
                               ph_max_measurable_level);

        sensor_ph_level_out.write(ph_measured_level);

        std::cout << "[" << sc_time_stamp() << "] "
                  << "PhSensor: true_level="
                  << std::fixed << std::setprecision(2)
                  << ph_true_level
                  << ", measured_level="
                  << ph_measured_level
                  << std::endl;

        wait(sample_period);
    }
}