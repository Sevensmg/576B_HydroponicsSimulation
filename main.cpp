// Main Top-Level file for system implementation 
// Created 4-6-26

#include <systemc.h>
#include "Microcontroller.h"
#include "WaterAddSolenoid.h"
#include "PhysicalModel.h"
#include "WaterLevelSensor.h"
#include "NutrientPump.h"
#include "NutrientSensor.h"
#include "WaterPump.h"
#include "AirPump.h"

int sc_main(int argc, char* argv[]) {
    // Variables
        // Variables will either be sensor, actuator, or physical. The controller will read from sensor and send to actuator.
    sc_signal<double> sensor_water_level_sig;
    sc_signal<double> physical_water_level_sig;
    sc_signal<bool> actuator_water_add_cmd_sig;
    sc_signal<bool> actuator_water_add_active_sig;

    sc_signal<double> sensor_nutrient_level_sig;
    sc_signal<double> physical_nutrient_level_sig;
    sc_signal<bool> actuator_nutrient_pump_cmd_sig;
    sc_signal<bool> actuator_nutrient_pump_active_sig;

    sc_signal<bool> actuator_water_pump_cmd_sig;
    sc_signal<bool> actuator_water_pump_active_sig;
    sc_signal<bool> actuator_air_pump_active_sig;

    // Module Instantiation
    Microcontroller mc("mc");
    WaterAddSolenoid sol("sol");
    PhysicalModel phys("phys");
    WaterLevelSensor wsen("wsen");
    NutrientPump npump("npump");
    NutrientSensor nsen("nsen");
    WaterPump wpump("wpump");
    AirPump apump("apump");

    // Connect Ports on Modules
        // Controller
            // Microcontroller
    mc.sensor_water_level_in(sensor_water_level_sig);
    mc.sensor_nutrient_level_in(sensor_nutrient_level_sig);
    mc.actuator_water_add_cmd_out(actuator_water_add_cmd_sig);
    mc.actuator_water_pump_cmd_out(actuator_water_pump_cmd_sig);
    mc.actuator_nutrient_pump_cmd_out(actuator_nutrient_pump_cmd_sig);

        // Actuators
            // Water Add Solenoid
    sol.actuator_water_add_cmd_in(actuator_water_add_cmd_sig);
    sol.actuator_water_add_active_out(actuator_water_add_active_sig);

            // Nutrient Pump
    npump.actuator_nutrient_pump_cmd_in(actuator_nutrient_pump_cmd_sig);
    npump.actuator_nutrient_pump_active_out(actuator_nutrient_pump_active_sig);

            // Water Pump
    wpump.actuator_water_pump_cmd_in(actuator_water_pump_cmd_sig);
    wpump.actuator_water_pump_active_out(actuator_water_pump_active_sig);

            // Air Pump (triggered by water pump command)
    apump.actuator_air_pump_cmd_in(actuator_water_pump_cmd_sig);
    apump.actuator_air_pump_active_out(actuator_air_pump_active_sig);

        // Sensors
            // Water Level Sensor
    wsen.physical_water_level_in(physical_water_level_sig);
    wsen.sensor_water_level_out(sensor_water_level_sig);

            // Nutrient Sensor
    nsen.physical_nutrient_level_in(physical_nutrient_level_sig);
    nsen.sensor_nutrient_level_out(sensor_nutrient_level_sig);

        // Enviroment (Physical)
            // Water Level
    phys.actuator_water_add_active_in(actuator_water_add_active_sig);
    phys.actuator_nutrient_pump_active_in(actuator_nutrient_pump_active_sig);
    phys.physical_water_level_out(physical_water_level_sig);
    phys.physical_nutrient_level_out(physical_nutrient_level_sig);

    // Simulation 
    sc_start(24, SC_SEC);

    return 0;
}