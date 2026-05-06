// Main Top-Level file for system implementation 
// Created 4-6-26

#include <systemc.h>
#include "Microcontroller.h"
#include "PhysicalModel.h"
#include "PhAddSolenoid.h"
#include "PhLevelSensor.h"
#include "WaterAddSolenoid.h"
#include "WaterLevelSensor.h"
#include "LEDController.h"

int sc_main(int argc, char* argv[]) {
    // Variables
        // Variables will either be sensor, actuator, or physical. The controller will read from sensor and send to actuator.
    sc_signal<double> sensor_ph_level_sig;
    sc_signal<double> physical_ph_level_sig;
    sc_signal<double> sensor_water_level_sig;
    sc_signal<double> physical_water_level_sig;
    sc_signal<bool> actuator_ph_add_cmd_sig;
    sc_signal<bool> actuator_ph_add_active_sig;
    sc_signal<bool> actuator_water_add_cmd_sig;
    sc_signal<bool> actuator_water_add_active_sig;
    sc_signal<bool> actuator_led_cmd_sig;
    sc_signal<bool> actuator_led_state_sig;

    // Module Instantiation
    Microcontroller mc("mc");
    PhAddSolenoid phsol("phsol");
    WaterAddSolenoid sol("sol");
    LEDController led("led");
    PhysicalModel phys("phys");
    PhSensor phsen("phsen");
    WaterLevelSensor wsen("wsen");

    // Connect Ports on Modules
        // Controller
            // Microcontroller
    mc.sensor_ph_level_in(sensor_ph_level_sig);
    mc.actuator_ph_add_cmd_out(actuator_ph_add_cmd_sig);

    mc.sensor_water_level_in(sensor_water_level_sig);
    mc.actuator_water_add_cmd_out(actuator_water_add_cmd_sig);

    mc.actuator_led_cmd_out(actuator_led_cmd_sig);

        // Actuators
            // Acid Add Solenoid
    phsol.actuator_ph_add_cmd_in(actuator_ph_add_cmd_sig);
    phsol.actuator_ph_add_active_out(actuator_ph_add_active_sig);

        // Water Add Solenoid
    sol.actuator_water_add_cmd_in(actuator_water_add_cmd_sig);
    sol.actuator_water_add_active_out(actuator_water_add_active_sig);

            // LEDs
    led.actuator_led_cmd_in(actuator_led_cmd_sig);
    led.actuator_led_state_out(actuator_led_state_sig);

        // Sensors
            // PH Level Sensor
    phsen.physical_ph_level_in(physical_ph_level_sig);
    phsen.sensor_ph_level_out(sensor_ph_level_sig);

            // Water Level Sensor
    wsen.physical_water_level_in(physical_water_level_sig);
    wsen.sensor_water_level_out(sensor_water_level_sig);

        // Enviroment (Physical)
            // PH Level
    phys.actuator_ph_add_active_in(actuator_ph_add_active_sig);
    phys.physical_ph_level_out(physical_ph_level_sig);
    
            // Water Level
    phys.actuator_water_add_active_in(actuator_water_add_active_sig);
    phys.physical_water_level_out(physical_water_level_sig);
    phys.actuator_led_state_in(actuator_led_state_sig);

    // Simulation 
    sc_start(40, SC_SEC);

    return 0;
}