#include "NutrientSensor.h"
#include <iostream>
#include <iomanip>

double NutrientSensor::clamp(double value, double min_value, double max_value) {
    if (value < min_value) {
        return min_value;
    }
    if (value > max_value) {
        return max_value;
    }
    return value;
}

void NutrientSensor::sample_loop() {
    // Initialize output once at time 0
    double true_level = physical_nutrient_level_in.read();
    double measured_level = clamp(true_level + sensor_bias,
                                  min_measurable_level,
                                  max_measurable_level);
    sensor_nutrient_level_out.write(measured_level);

    while (true) {
        true_level = physical_nutrient_level_in.read();

        // Measurement model: Assume 1:1 for nutrient concentration for now
        measured_level = true_level + sensor_bias;

        // Clamp
        measured_level = clamp(measured_level,
                               min_measurable_level,
                               max_measurable_level);

        sensor_nutrient_level_out.write(measured_level);

        std::cout << "[" << sc_time_stamp() << "] "
                  << "NutrientSensor: true_level="
                  << std::fixed << std::setprecision(2)
                  << true_level
                  << ", measured_level="
                  << measured_level
                  << std::endl;

        wait(sample_period);
    }
}
