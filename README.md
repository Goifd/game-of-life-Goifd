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

The simulation has two modes:
1. Simulating our solar system on stable orbits, but random initial conditions.
e.g. ./build/solarSystemSimulator -t 6.2831 -s 0.0001 simulates our solar system with random initial conditions and for 1 year

2. Simulating a solar system with n bodies on stable orbits and random initial condition.
e.g. ./build/solarSystemSimulator -n 256 -t 6.2831 -s 0.0001 simulates a solar system with 1 star and 255 planets for 1 year

To specify the mode use the -n or --nbody flag: if the flag is not specified the program will simulate our solar system, if the flag is specified it will simulate a system with n bodies, where n is given by running the command: 
./build/solarSystemSimulator -n 5 -t 100 -s 0.01

Further details MUST be specified for both type of simulations using the flags:
-s / --timestep: specify the timestep used for the Euler integration process
-t / --time: specify for how long the system should be simulated
IMPORTANT: The simulation is normalized so that t=2PI corresponds to one year.

Optional flag:
-e / --epsilon: specify softening factor, helps when particles are very close, default value is 0
e.g. ./build/solarSystemSimulator -n 256 -t 6.2831 -s 0.0001 -e 0.001

Other flags:
-h / --help: prints out the flag options

Data and physics background:

The system is normalized so that Earth will be 1 unit away from the Sun and 2*PI corresponds to one year.

The following data is used for our solar system's initialization:
// Masses in order Sun, Mercury, Venus, etc
{1.,1./6023600,1./408524,1./332946.038,1./3098710,1./1047.55,1./3499,1./22962,1./19352}
// Distances from Sun
{0.0, 0.4, 0.7, 1, 1.5, 5.2, 9.5, 19.2, 30.1}

stable orbits are generated using:
r_x = r*sin(theta)
r_y = r*cos(theta)
v_x = -1/sqrt(r)*cos(theta)
v_y = 1/sqrt(r)*sin(theta)

theta is randomly specified between 0 and 2Pi, r is the distance from the Sun given by the above list

## Credits

This project is maintained by Dr. Jamie Quinn as part of UCL ARC's course, Research Computing in C++.

## Exercise 1.3.d Output:
The system before the evolution: 

particle 0
mass: 1
position: (0,0,0)
velocity: (0,0,0)

particle 1
mass: 1.66014e-07
position: (-0.00707,0.4,0)
velocity: (-1.58,-0.028,0)

particle 2
mass: 2.44784e-06
position: (-0.288,0.638,0)
velocity: (-1.09,-0.491,0)

particle 3
mass: 3.00349e-06
position: (0.721,0.693,0)
velocity: (-0.693,0.721,0)

particle 4
mass: 3.22715e-07
position: (-0.00904,1.5,0)
velocity: (-0.816,-0.00492,0)

particle 5
mass: 0.000954608
position: (5.18,0.454,0)
velocity: (-0.0383,0.437,0)

particle 6
mass: 0.000285796
position: (5.75,-7.56,0)
velocity: (0.258,0.196,0)

particle 7
mass: 4.35502e-05
position: (12.4,-14.6,0)
velocity: (0.174,0.148,0)

particle 8
mass: 5.16742e-05
position: (-26.4,-14.5,0)
velocity: (0.0881,-0.16,0)



Total number of steps: 629
Time taken to run the simulation: 0.002608
The system after evolving for t: 6.28 and with dt: 0.01


particle 0
mass: 1
position: (0.000676,0.00014,0)
velocity: (0.000217,5.64e-05,0)

particle 1
mass: 1.66014e-07
position: (0.111,0.387,0)
velocity: (-1.51,0.432,0)

particle 2
mass: 2.44784e-06
position: (0.694,0.131,0)
velocity: (-0.208,1.17,0)

particle 3
mass: 3.00349e-06
position: (0.717,0.698,0)
velocity: (-0.698,0.716,0)

particle 4
mass: 3.22715e-07
position: (0.443,-1.43,0)
velocity: (0.781,0.236,0)

particle 5
mass: 0.000954608
position: (4.24,3.01,0)
velocity: (-0.254,0.357,0)

particle 6
mass: 0.000285796
position: (7.23,-6.16,0)
velocity: (0.211,0.247,0)

particle 7
mass: 4.35502e-05
position: (13.5,-13.7,0)
velocity: (0.162,0.16,0)

particle 8
mass: 5.16742e-05
position: (-25.8,-15.5,0)
velocity: (0.0941,-0.156,0)



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

Which is as expected, the smaller the time step the smaller the energy loss. Note that the energy loss is worse than linear.

## Exercise 2.2

// without optimization -O0
dt: 0.0001 runtime: 775.441 /step: 0.000123415

// with optimization -O2

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

## Exercise 2.3 
Summary, where n is the number of particles in the system:

Simulation done: 
n: 8
%E change: 0.00175464% t: 6.2832 dt: 0.001 runtime: 0.0155922s  /step: 2.48165e-06s

Simulation done: 
n: 64
%E change: 0.394413% t: 6.2832 dt: 0.001 runtime: 0.960916s  /step: 0.000152939s

Simulation done: 
n: 256
%E change: 6.62508% t: 6.2832 dt: 0.001 runtime: 14.9335s  /step: 0.00237681s

Simulation done: 
n: 1024
%E change: 15.5554% t: 6.2832 dt: 0.001 runtime: 254.082s  /step: 0.0404396s

Simulation done: 
n: 2048
%E change: 47.1344% t: 6.2832 dt: 0.001 runtime: 1010.95s  /step: 0.160902s

It seems like the total runtime scales with n^2 since the /step time scales with n^2 and that the energy loss largely depends on the size
of the system and it gets worse for large systems. This makes sense as for every velocity and position update the loss increases, and the more particles the more of these additions. I suspect that it's not linear in n as the error in one step depends on the error in the previous step, and due to this accumulation it could be a higher order polynomial or exponential.

## Exercise 2.4
### a
Parallelization has been added to the code at two places

1. updateVelPos(double dt): 

2. updateAccelerations(double epsilon)
In this case using the collapse(2) function leads to a data-race and errors in the simulations since in the second loop
the threads are trying to access the same variable, acceleration. This could probably be solved if the acceleration was stored in a
POD type eg. double ax, double ay, double az, but implementing this would come with the refactoring of a large part of the code 
and the project specifically asks to use the Eigen::Vector3d container.

Schedule(dynamic) is slower than schedule(static) likely because the iterations are similar in execution time, and the extra 
effort to try to dynamically allocate the iterations between the threads only causes a computational overhead without any 
speedup. This is shown by the following results:

schedule testing with n=256 t=62.831 dt=0.001 epsilon=0.0 on 4 threads

schedule(static) 

Simulation done: 
n: 256
%E change: 247.108% t: 62.831 dt: 0.001 runtime: 67.5888s  /step: 0.0

Simulation done: 
n: 300
%E change: 4267.32% t: 62.831 dt: 0.001 runtime: 78.4764s  /step: 0.00124901s

schedule(dynamic) 

Simulation done: 
n: 256
%E change: 247.108% t: 62.831 dt: 0.001 runtime: 90.8499s  /step: 0.00144594s

Simulation done: 
n: 300
%E change: 4267.32% t: 62.831 dt: 0.001 runtime: 107.53s  /step: 0.00171141s

### b
All tests were ran with -O2 compiler optimization.
CPU specification: 4 cores 8 threads
Strong scaling benchmarking was done with ./build/solarSystemSimulator -t 6.2831 -s 0.0001 -n 128.
Weak scaling benchmarking was done with ./build/solarSystemSimulator -t 6.2831 -s 0.0001 -n <input>.

STRONG SCALING
|'OMP_NUM_THREADS | Time (s) | Seedup |
|---|-------|----|
| 1 | 39.5s | x  |
| 2 | 21.6s |1.83|
| 3 | 16.8s |2.35|
| 4 | 15.2s |2.60|
| 8 | 51.0s |0.77|

WEAK SCALING
|'OMP_NUM_THREADS | Num Particles | Time (s) | Seedup |
|---|---|--------|----|
| 1 |128| 39.5s  | x  |
| 2 |256| 86.43s |0.46|
| 3 |384| 192.96s|0.25|
| 4 |512| 271.73s|0.15|
