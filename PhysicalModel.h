#ifndef PHYSICAL_MODEL_H
#define PHYSICAL_MODEL_H

#include <systemc.h>

SC_MODULE(PhysicalModel) {
public:
    // Inputs
    sc_in<bool> actuator_ph_add_active_in;

    // Outputs
    sc_out<double> physical_ph_level_out;

    // Water level state and parameters
    double ph_level;
    double acid_increase_rate_per_step;
    double base_increase_rate_per_step;
    double min_ph_level;
    double max_ph_level;
    sc_time model_update_period;

    SC_CTOR(PhysicalModel) :
        // Water Level
        ph_level(6),                        // Start Level 
        acid_increase_rate_per_step(-0.10),           
        base_increase_rate_per_step(0.05),
        min_ph_level(0),                    
        max_ph_level(14),                    
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