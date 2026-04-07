// Main Top-Level file for system implementation 
// Created 4-6-26

#include <systemc.h>
#include "Microcontroller.h"
#include "WaterAddSolenoid.h"
#include "PhysicalModel.h"

int sc_main(int argc, char* argv[]) {
    sc_signal<double> water_level_sig;
    sc_signal<bool> water_add_cmd_sig;
    sc_signal<bool> water_add_active_sig;

    Microcontroller mc("mc");
    WaterAddSolenoid sol("sol");
    PhysicalModel phys("phys");

    mc.sensor_water_level_in(water_level_sig);
    mc.actuator_water_add_cmd_out(water_add_cmd_sig);

    sol.actuator_water_add_cmd_in(water_add_cmd_sig);
    sol.actuator_water_add_active_out(water_add_active_sig);

    phys.actuator_water_add_active_in(water_add_active_sig);
    phys.sensor_water_level_out(water_level_sig);

    sc_start(24, SC_SEC);
    return 0;
}