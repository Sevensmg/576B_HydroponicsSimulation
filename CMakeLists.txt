cmake_minimum_required(VERSION 3.16)
project(HydroponicsSimulation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# Point CMake at your local SystemC install
set(CMAKE_PREFIX_PATH "$ENV{HOME}/.local/systemc-2.3.3")

add_executable(hydro_sim
    main.cpp
    Microcontroller.cpp
    PhAddSolenoid.cpp
    PhysicalModel.cpp
    PhLevelSensor.cpp
    WaterLevelSensor.cpp
    WaterAddSolenoid.cpp
    LEDController.cpp
)

target_include_directories(hydro_sim PRIVATE
    ${SYSTEMC_HOME}/include
)

target_link_directories(hydro_sim PRIVATE
    ${SYSTEMC_HOME}/lib
)

target_link_libraries(hydro_sim PRIVATE systemc)

