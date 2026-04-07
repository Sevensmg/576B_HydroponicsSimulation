#include "PhysicalModel.h"
#include <iostream>
#include <iomanip>

double PhysicalModel::clamp(double value, double min_value, double max_value) {
    if (value < min_value) {
        return min_value;
    }
    if (value > max_value) {
        return max_value;
    }
    return value;
}

void PhysicalModel::update_model() {
    // Write initial condition
    sensor_water_level_out.write(water_level_percent);

    while (true) {
        bool solenoid_active = actuator_water_add_active_in.read();

        // Natural water loss
        water_level_percent -= water_loss_rate_per_step;

        // Water addition from solenoid
        if (solenoid_active) {
            water_level_percent += water_fill_rate_per_step;
        }

        // Clamp to valid bounds
        water_level_percent = clamp(
            water_level_percent,
            min_water_level,
            max_water_level
        );

        // Publish updated water level
        sensor_water_level_out.write(water_level_percent);

        std::cout << "[" << sc_time_stamp() << "] "
                  << "PhysicalModel: water_level="
                  << std::fixed << std::setprecision(2)
                  << water_level_percent << "%, solenoid_active="
                  << solenoid_active
                  << std::endl;

        wait(model_update_period);
    }
}