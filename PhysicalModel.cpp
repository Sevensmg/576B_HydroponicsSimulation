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
    physical_ph_level_out.write(ph_level);

    while (true) {
        bool solenoid_active = actuator_ph_add_active_in.read();

        // Natural water alkalinization
        ph_level += base_increase_rate_per_step;
        //Assuming our plants make water more alkaline
        //Need to model increase acidity
        // Acid addition from solenoid
        if (solenoid_active) {
            ph_level += acid_increase_rate_per_step;
        }

        // Clamp to valid bounds
        ph_level = clamp(
            ph_level,
            min_ph_level,
            max_ph_level
        );

        // Publish updated water level
        physical_ph_level_out.write(ph_level);

        std::cout << "[" << sc_time_stamp() << "] "
                  << "PhysicalModel: ph_level="
                  << std::fixed << std::setprecision(2)
                  << ph_level << " solenoid_active="
                  << solenoid_active
                  << std::endl;

        wait(model_update_period);
    }
}