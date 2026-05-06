#ifndef WATER_ADD_SOLENOID_H
#define WATER_ADD_SOLENOID_H

#include <systemc.h>

SC_MODULE(WaterAddSolenoid) {
public:
    // Inputs
    sc_in<bool> actuator_water_add_cmd_in;

    // Outputs
    sc_out<bool> actuator_water_add_active_out;

    // Optional actuator delay
    sc_time actuator_delay;

    SC_CTOR(WaterAddSolenoid)
        : actuator_delay(sc_time(0, SC_SEC))
    {
        SC_THREAD(run);
    }

private:
    void run();
};

#endif