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
    physical_water_level_out.write(water_level);
  
    while (true) {
      
        bool ph_solenoid_active = actuator_ph_add_active_in.read();
        physical_water_level_out.write(water_level);
        physical_nutrient_level_out.write(nutrient_level);

        bool solenoid_active = actuator_water_add_active_in.read();
        bool nutrient_pump_active = actuator_nutrient_pump_active_in.read();

    // Water
      
        // Natural water loss
        water_level -= water_loss_rate_per_step;

        // Water addition from solenoid
        if (solenoid_active) {
            water_level += water_fill_rate_per_step;
        }

        // Natural water alkalinization
        //ph_level += natural_base_increase_rate_per_step;

        // Natural water acidification
        ph_level += natural_acid_increase_rate_per_step;

        //Assuming our plants make water more alkaline
   
        // Acid addition from solenoid
        if (ph_solenoid_active && ph_level > 6.5) {
            ph_level += acid_increase_rate_per_step;
        }

         if (ph_solenoid_active && ph_level < 5.5) {
            ph_level += base_increase_rate_per_step;
         }
        // Natural nutrient consumption
        nutrient_level -= nutrient_consumption_rate_per_step;

        // Nutrient addition from pump
        if (nutrient_pump_active) {
            nutrient_level += nutrient_add_rate_per_step;
        }

        // Clamp to valid bounds
        ph_level = clamp(
            ph_level,
            min_ph_level,
            max_ph_level
        );
      
             // Clamp to valid bounds
        water_level = clamp(
            water_level,
            min_water_level,
            max_water_level
        );

        // LEDs
        led_state = actuator_led_state_in.read();

        if (led_state) {
            //update temperature
        }

        // Publish updated water level
        physical_water_level_out.write(water_level);
        // Publish updated pH
        physical_ph_level_out.write(ph_level);

        std::cout << "[" << sc_time_stamp() << "] "
                  << "PhysicalModel: ph_level="
                  << std::fixed << std::setprecision(2)
                  << ph_level << " ph solenoid_active="
                  << ph_solenoid_active
                  << " , LED_active=" << led_state
                  << std::endl;
        nutrient_level = clamp(
            nutrient_level,
            min_nutrient_level,
            max_nutrient_level
        );

        // Publish updated values
        physical_water_level_out.write(water_level);
        physical_nutrient_level_out.write(nutrient_level);

        std::cout << "[" << sc_time_stamp() << "] "
                  << "PhysicalModel: water_level="
                  << std::fixed << std::setprecision(2)
                  << water_level << "L, solenoid_active="
                  << solenoid_active
                  << " , LED_active=" << led_state
                  << water_level << "L, nutrient_level="
                  << nutrient_level << ", sol=" << solenoid_active
                  << ", n_pump=" << nutrient_pump_active
                  << std::endl;

        wait(model_update_period);
    }
}