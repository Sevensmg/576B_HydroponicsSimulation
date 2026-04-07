cmake_minimum_required(VERSION 3.16)
project(HydroponicsSimulation CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Point CMake at your local SystemC install
set(CMAKE_PREFIX_PATH "$ENV{HOME}/.local/systemc-2.3.3")

find_package(SystemCLanguage CONFIG REQUIRED)

add_executable(hydro_sim
    main.cpp
    Microcontroller.cpp
    WaterAddSolenoid.cpp
    PhysicalModel.cpp
)

target_link_libraries(hydro_sim PRIVATE SystemC::systemc)