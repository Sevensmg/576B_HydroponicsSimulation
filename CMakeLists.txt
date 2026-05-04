cmake_minimum_required(VERSION 3.16)
project(HydroponicsSimulation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Point CMake at local SystemC install on Windows
set(CMAKE_PREFIX_PATH "C:/Users/cemcc/Documents/systemc-2.3.3/systemc_install")

find_package(SystemCLanguage CONFIG REQUIRED)

add_executable(hydro_sim
    main.cpp
    Microcontroller.cpp
    WaterAddSolenoid.cpp
    PhysicalModel.cpp
    WaterLevelSensor.cpp
    NutrientPump.cpp
    NutrientSensor.cpp
    WaterPump.cpp
    AirPump.cpp
)

target_link_libraries(hydro_sim PRIVATE SystemC::systemc)