# A Virtual Solar System

This is the starting repository for assignment 2 of PHAS0100: Research Computing with C++. You may add or remove C++ files in any directory. You should organise the files as you see fit but do read the Folder Structure section below to understand the intended use of the existing folders.

## Installing dependencies

We are using the package manager Conan to install the dependencies Catch2 and Eigen. In order to use CMake's `Release` target for performance and `Debug` for debugging, the libraries must be installed twice with:

```
conan install . --output-folder=build --build=missing -s build_type=Debug
conan install . --output-folder=build --build=missing -s build_type=Release
```

If you delete the `build` directory to clean your build, you may have to install the dependencies again.

## Building

To build from the project root directory you should run:

```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

If you wish to debug your code, you should replace `Release` with `Debug`. For performance measurements, ensure you have built with the `Release` target.

## Testing

Once the project has been built, it can be tested by running:

```
cd build
ctest
```

## Folder structure

The project is split into four main parts aligning with the folder structure described in [the relevant section in Modern CMake](https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html):

- `app/` contains all code implementing the command-line application.
- `lib/` contains all non-app code. Only code in this directory can be accessed by the unit tests.
- `include/` contains all `.hpp` files.
- `test/` contains all unit tests.

You are expected to edit the `CMakeLists.txt` file in each folder to add or remove sources as necessary. For example, if you create a new file `test/particle_test.cpp`, you must add `particle_test.cpp` to the line `add_executable(tests test.cpp)` in `test/CMakeLists.txt`. Please ensure you are comfortable editing these files well before the submission deadline. If you feel you are struggling with the CMake files, please see the Getting Help section of the assignment instructions.

## Usage Instructions

You should fill in the instructions for using the app here.

## Credits

This project is maintained by Dr. Jamie Quinn as part of UCL ARC's course, Research Computing in C++.

## Exercise 1.3.d Output:
The system before the evolution: 

particle 0
mass: 1
position: (0,0,0)
velocity: (0,0,0)
-------------------
particle 1
mass: 1.66014e-07
position: (-0.00707,0.4,0)
velocity: (-1.58,-0.028,0)
-------------------
particle 2
mass: 2.44784e-06
position: (-0.288,0.638,0)
velocity: (-1.09,-0.491,0)
-------------------
particle 3
mass: 3.00349e-06
position: (0.721,0.693,0)
velocity: (-0.693,0.721,0)
-------------------
particle 4
mass: 3.22715e-07
position: (-0.00904,1.5,0)
velocity: (-0.816,-0.00492,0)
-------------------
particle 5
mass: 0.000954608
position: (5.18,0.454,0)
velocity: (-0.0383,0.437,0)
-------------------
particle 6
mass: 0.000285796
position: (5.75,-7.56,0)
velocity: (0.258,0.196,0)
-------------------
particle 7
mass: 4.35502e-05
position: (12.4,-14.6,0)
velocity: (0.174,0.148,0)
-------------------
particle 8
mass: 5.16742e-05
position: (-26.4,-14.5,0)
velocity: (0.0881,-0.16,0)
-------------------


Total number of steps: 629
Time taken to run the simulation: 0.002608
The system after evolving for t: 6.28 and with dt: 0.01


particle 0
mass: 1
position: (0.000676,0.00014,0)
velocity: (0.000217,5.64e-05,0)
-------------------
particle 1
mass: 1.66014e-07
position: (0.111,0.387,0)
velocity: (-1.51,0.432,0)
-------------------
particle 2
mass: 2.44784e-06
position: (0.694,0.131,0)
velocity: (-0.208,1.17,0)
-------------------
particle 3
mass: 3.00349e-06
position: (0.717,0.698,0)
velocity: (-0.698,0.716,0)
-------------------
particle 4
mass: 3.22715e-07
position: (0.443,-1.43,0)
velocity: (0.781,0.236,0)
-------------------
particle 5
mass: 0.000954608
position: (4.24,3.01,0)
velocity: (-0.254,0.357,0)
-------------------
particle 6
mass: 0.000285796
position: (7.23,-6.16,0)
velocity: (0.211,0.247,0)
-------------------
particle 7
mass: 4.35502e-05
position: (13.5,-13.7,0)
velocity: (0.162,0.16,0)
-------------------
particle 8
mass: 5.16742e-05
position: (-25.8,-15.5,0)
velocity: (0.0941,-0.156,0)
-------------------


## Exercise 2.1 energy results

### Summarized
dt  % E decrease
--------------
1.0         75.8915 % 
0.5         59.1017 % 
0.3         49.8256 % 
0.2         43.739 % 
0.1         33.3735 % 
0.08        31.1696 % 
0.04        21.09 % 
0.01        8.83165 % 
0.005       5.65817 % 
0.001       2.3165 % 
0.0001      0.64172 % 
0.00005     0.393049 % 
0.00001     0.103788 % 
0.000005    0.0549349 % 
0.000001    0.0116069 % 

Which is as expected, the smaller the timestep the smaller the energy loss. Note that the energy loss is worse than linear.

### Detailed outputs

dt: 1
Initial E_tot = -0.00011243
After the evolution E_tot = -2.71051e-05
E drop: -8.53248e-05 --> 75.8915 % 

dt: 0.5
Initial E_tot = -0.00011243
After the evolution E_tot = -4.59819e-05
E drop: -6.6448e-05 --> 59.1017 % 

dt: 0.3
Initial E_tot = -0.00011243
After the evolution E_tot = -5.64111e-05
E drop: -5.60188e-05 --> 49.8256 % 

dt: 0.2
Initial E_tot = -0.00011243
After the evolution E_tot = -6.32542e-05
E drop: -4.91757e-05 --> 43.739 % 

dt: 0.1
Initial E_tot = -0.00011243
After the evolution E_tot = -7.49081e-05
E drop: -3.75218e-05 --> 33.3735 % 

dt: 0.08
Initial E_tot = -0.00011243
After the evolution E_tot = -7.7386e-05
E drop: -3.50439e-05 --> 31.1696 % 

dt: 0.04
Initial E_tot = -0.00011243
After the evolution E_tot = -8.87185e-05
E drop: -2.37115e-05 --> 21.09 %  

dt: 0.01
Initial E_tot = -0.00011243
After the evolution E_tot = -0.000102501
E drop: -9.92942e-06 --> 8.83165 % 

dt: 0.005
Initial E_tot = -0.00011243
After the evolution E_tot = -0.000106068
E drop: -6.36147e-06 --> 5.65817 % 

dt: 0.001
Initial E_tot = -0.00011243
After the evolution E_tot = -0.000109825
E drop: -2.60444e-06 --> 2.3165 % 

dt: 0.0001
Initial E_tot = -0.00011243
After the evolution E_tot = -0.000111708
E drop: -7.21485e-07 --> 0.64172 % 

## Exercise 2.2

// without optimization
dt: 0.0001 runtime: 775.441 /step: 0.000123415

// with optimization

dt: 0.1 runtime: 0.0215727 /step: 3.4335e-06

dt: 0.05 runtime: 0.0336548 /step: 2.67824e-06

dt: 0.01 runtime: 0.179502 /step: 2.8569e-06

dt: 0.005 runtime: 0.331951 /step: 2.64159e-06

dt: 0.001 runtime: 1.6483 /step: 2.62335e-06

dt: 0.0005 runtime: 3.41846 /step: 2.72033e-06

dt: 0.0001 runtime: 15.3947 /step: 2.45015e-06

dt: 0.00005 runtime: 33.2303 /step: 2.64438e-06

dt: 0.00001 runtime: 171.915 /step: 2.73611e-06

dt: 0.000005 runtime: 358.138 /step: 2.84997e-06

dt: 0.000001 runtime: 1878.75 /step: 2.99013e-06

Optimization for the dt=0.0001 case sped up the code from 775s to 15s which is more than a 50 times improvement. This is likely due to the fact that optimization speeds up loops quite a bit, and the slow part of this code is exactly those, loops.