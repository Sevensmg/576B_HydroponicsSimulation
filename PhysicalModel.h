#ifndef PHYSICAL_MODEL_H
#define PHYSICAL_MODEL_H

#include <systemc.h>

SC_MODULE(PhysicalModel) {
public:
    // Inputs
    sc_in<bool> actuator_water_add_active_in;
    sc_in<bool> actuator_nutrient_pump_active_in;

    // Outputs
    sc_out<double> physical_water_level_out;

    // Water level state and parameters
    double water_level;
    double water_loss_rate_per_step;
    double water_fill_rate_per_step;
    double nutrient_level;
    double nutrient_consumption_rate_per_step;
    double nutrient_addition_rate_per_step;
    double min_water_level;
    double max_water_level;
    sc_time model_update_period;

    SC_CTOR(PhysicalModel) :
        // Water Level
        water_level(40),                        // Start Level 
        water_loss_rate_per_step(0.05),           
        water_fill_rate_per_step(0.50),
        nutrient_level(100),                    // Start Level (percentage or arbitrary units)
        nutrient_consumption_rate_per_step(0.01),
        nutrient_addition_rate_per_step(0.10),
        min_water_level(0),                    
        max_water_level(45),                    // Max: ~5 L/plant * 8 plants = 40L + 5L (buffer) = 45L 
        // Time Step
        model_update_period(sc_time(1, SC_SEC))
    {
        SC_THREAD(update_model);
    }

private:
    void update_model();
    double clamp(double value, double min_value, double max_value);
};

#endif