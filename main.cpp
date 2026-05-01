// Main Top-Level file for system implementation 
// Created 4-6-26

#include <systemc.h>
#include "Microcontroller.h"
#include "PhAddSolenoid.h"
#include "PhysicalModel.h"
#include "PhLevelSensor.h"

int sc_main(int argc, char* argv[]) {
    // Variables
        // Variables will either be sensor, actuator, or physical. The controller will read from sensor and send to actuator.
    sc_signal<double> sensor_ph_level_sig;
    sc_signal<double> physical_ph_level_sig;
    sc_signal<bool> actuator_ph_add_cmd_sig;
    sc_signal<bool> actuator_ph_add_active_sig;
 
    // Module Instantiation
    Microcontroller mc("mc");
    PhAddSolenoid phsol("phsol");
    PhysicalModel phys("phys");
    PhSensor phsen("phsen");

    // Connect Ports on Modules
        // Controller
            // Microcontroller
    mc.sensor_ph_level_in(sensor_ph_level_sig);
    mc.actuator_ph_add_cmd_out(actuator_ph_add_cmd_sig);

        // Actuators
            // Acid Add Solenoid
    phsol.actuator_ph_add_cmd_in(actuator_ph_add_cmd_sig);
    phsol.actuator_ph_add_active_out(actuator_ph_add_active_sig);

        // Sensors
            // PH Level Sensor
    phsen.physical_ph_level_in(physical_ph_level_sig);
    phsen.sensor_ph_level_out(sensor_ph_level_sig);

        // Enviroment (Physical)
            // PH Level
    phys.actuator_ph_add_active_in(actuator_ph_add_active_sig);
    phys.physical_ph_level_out(physical_ph_level_sig);

    // Simulation 
    sc_start(40, SC_SEC);

    return 0;
}