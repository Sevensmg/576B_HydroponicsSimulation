// Main Top-Level file for system implementation 
// Created 4-6-26

#include <systemc.h>
#include "Microcontroller.h"
#include "WaterAddSolenoid.h"
#include "WaterPump.h"
#include "PhysicalModel.h"
#include "WaterLevelSensor.h"

int sc_main(int argc, char* argv[]) {
    // Variables
        // Variables will either be sensor, actuator, or physical. The controller will read from sensor and send to actuator.
    sc_signal<double> sensor_water_level_sig;
    sc_signal<double> physical_water_level_sig;
    sc_signal<bool> actuator_water_add_cmd_sig;
    sc_signal<bool> actuator_water_add_active_sig;
    sc_signal<bool> actuator_water_pump_cmd_sig;
    sc_signal<bool> actuator_water_pump_active_sig;

    // Module Instantiation
    Microcontroller mc("mc");
    WaterAddSolenoid sol("sol");
    WaterPump pump("pump");
    PhysicalModel phys("phys");
    WaterLevelSensor wsen("wsen");

    // Connect Ports on Modules
        // Controller
            // Microcontroller
    mc.sensor_water_level_in(sensor_water_level_sig);
    mc.actuator_water_add_cmd_out(actuator_water_add_cmd_sig);
    mc.actuator_water_pump_cmd_out(actuator_water_pump_cmd_sig);

        // Actuators
            // Water Add Solenoid
    sol.actuator_water_add_cmd_in(actuator_water_add_cmd_sig);
    sol.actuator_water_add_active_out(actuator_water_add_active_sig);

            // Water Pump
    pump.actuator_water_pump_cmd_in(actuator_water_pump_cmd_sig);
    pump.actuator_water_pump_active_out(actuator_water_pump_active_sig);

        // Sensors
            // Water Level Sensor
    wsen.physical_water_level_in(physical_water_level_sig);
    wsen.sensor_water_level_out(sensor_water_level_sig);

        // Enviroment (Physical)
            // Water Level
    phys.actuator_water_add_active_in(actuator_water_add_active_sig);
    phys.actuator_water_pump_active_in(actuator_water_pump_active_sig);
    phys.physical_water_level_out(physical_water_level_sig);

    // Simulation 
    sc_start(24, SC_SEC);

    return 0;
}