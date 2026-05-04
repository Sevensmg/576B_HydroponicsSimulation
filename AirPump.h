#ifndef AIR_PUMP_H
#define AIR_PUMP_H

#include <systemc.h>

SC_MODULE(AirPump) {
public:
    // Inputs
    sc_in<bool> actuator_air_pump_cmd_in;

    // Outputs
    sc_out<bool> actuator_air_pump_active_out;

    // Optional actuator delay
    sc_time actuator_delay;

    SC_CTOR(AirPump)
        : actuator_delay(sc_time(0, SC_SEC))
    {
        SC_THREAD(run);
    }

private:
    void run();
};

#endif
