# 576B_HydroponicsSimulation
Simulation of a simple hydroponics system for ECE576B at the University of Arizona.

# To run the simulation using SystemC 2.3.3
### 1. Start with a terminal from the cloned repo
```cd ~/path/to/576B_HydroponicsSimulation```

### 2. Create a folder for the SystemC Build
```mkdir -p build```

```cd build```

### 3. Run CMake to populate and configure the build folder
```cmake ..```

```cmake .. -DCMAKE_PREFIX_PATH="$HOME/.local/systemc-2.3.3"```

### 4. Compile the files into the simulation program
```cmake --build .```

### 5. Run the program
```./hydro_sim```
