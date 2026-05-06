#ifndef NUTRIENT_PUMP_H
#define NUTRIENT_PUMP_H

#include <systemc.h>

SC_MODULE(NutrientPump) {
public:
    // Inputs
    sc_in<bool> actuator_nutrient_pump_cmd_in;

    // Outputs
    sc_out<bool> actuator_nutrient_pump_active_out;

    // Optional actuator delay
    sc_time actuator_delay;

    SC_CTOR(NutrientPump)
        : actuator_delay(sc_time(0, SC_SEC))
    {
        SC_THREAD(run);
    }

private:
    void run();
};

#endif
