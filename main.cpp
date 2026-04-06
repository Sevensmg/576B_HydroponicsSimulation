// Main Top-Level file for system implementation 
// Created 4-6-26 -7

#include <systemc.h>
#include "Microcontroller.h"
#include "WaterAddSolenoid.h"
#include "PhysicalModel.h"

int sc_main(int argc, char* argv[]) {
    sc_signal<double> water_level_sig;
    sc_signal<bool> solenoid_cmd_sig;
    sc_signal<bool> solenoid_active_sig;

    Microcontroller mc("mc");
    WaterAddSolenoid sol("sol");
    PhysicalModel phys("phys");

    mc.water_level_in(water_level_sig);
    mc.water_add_cmd_out(solenoid_cmd_sig);

    sol.cmd_in(solenoid_cmd_sig);
    sol.active_out(solenoid_active_sig);

    phys.solenoid_active_in(solenoid_active_sig);
    phys.water_level_out(water_level_sig);

    sc_start(24, SC_HOUR);
    return 0;
}