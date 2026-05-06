cmake_minimum_required(VERSION 3.16)
project(HydroponicsSimulation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(SYSTEMC_HOME "/home/luis/systemc/install")

add_executable(hydro_sim
    main.cpp
    Microcontroller.cpp
    PhAddSolenoid.cpp
    PhysicalModel.cpp
    PhLevelSensor.cpp
)

target_include_directories(hydro_sim PRIVATE
    ${SYSTEMC_HOME}/include
)

target_link_directories(hydro_sim PRIVATE
    ${SYSTEMC_HOME}/lib
)

target_link_libraries(hydro_sim PRIVATE systemc)

add_definitions(-DSC_INCLUDE_DYNAMIC_PROCESSES)
