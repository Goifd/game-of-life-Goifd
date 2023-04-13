#ifndef particle_h
#define particle_h

#include <Eigen/Core>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <random>
#include <math.h>
#include <chrono>
#include <tuple>

// Basic data type for simulation particle=body in the solar system
// only functionality is the update method, other system evolution functionalities are implemented
// in pSystem class
class Particle {
    public:
        Particle(double in_mass, Eigen::Vector3d pos, Eigen::Vector3d vel);
        double getMass() const;
        // return by value to avoid unintentional editing 
        const Eigen::Vector3d& getPosition() const;
        const Eigen::Vector3d& getVelocity() const;
        const Eigen::Vector3d& getAcceleration() const;
        void addAcceleration(Eigen::Vector3d a);
        void update(double dt);
        void print() const;
        

    private:
        double mass;
        Eigen::Vector3d position;
        Eigen::Vector3d velocity;
        Eigen::Vector3d acceleration;
        
};


// container to store a system of interacting particles
// system can be manually populated with particles, and then the evolveSystem
// function handles everything evolution related
class pSystem {
    public:
        pSystem();
        // populate the system with the following functions
        void addParticle(Particle p);
        void deleteParticle(int n);
        Particle &getParticle(int n);
        void printParticles();
        int getNumOfParticles();
        std::tuple<double, double> getEnergy();

        // calculates acceleration between two particles
        Eigen::Vector3d calcAcceleration(const Particle& p1, const Particle& p2, double epsilon);

        // updates acceleration parameter for all particles in the system
        void updateAccelerations(double epsilon);

        // updates velocity and position of all particles in the system
        void updateVelPos(double dt);

        // evolves the system
        void evolveSystem(double t, double dt, double epsilon=0.0);
        

    private:
        int numParticles;
        std::vector<Particle> particles;
};

// template to enforce Generator uniformity, they must return a unique_ptr to the a pSystem
class InitialConditionGenerator{
    public:
        virtual std::unique_ptr<pSystem> generateInitialConditions() = 0;

    protected:
        // System to return by generateInitialConditions
        std::unique_ptr<pSystem> s1 = std::make_unique<pSystem>();
};

// generates our solar system with stable orbits
class solarSysGenerator : public InitialConditionGenerator{

    public:
        solarSysGenerator();
        // return the unique pointer
        std::unique_ptr<pSystem> generateInitialConditions();

    private:
        // Solar System data
        std::vector<double> masses{1.,1./6023600,1./408524,1./332946.038,1./3098710,1./1047.55,1./3499,1./22962,1./19352};
        std::vector<double> distances{0.0, 0.4, 0.7, 1, 1.5, 5.2, 9.5, 19.2, 30.1};    
};

// generates a random solar system with n particles, all on stable orbits
class randomSysGenerator : public InitialConditionGenerator{

    public:
        randomSysGenerator(int n);
        // return the unique pointer
        std::unique_ptr<pSystem> generateInitialConditions();
};

// timer class from the UCL PHAS0100 course, OpenMP week 8 example.
class Timer {
    public:
        void reset();
        double elapsed() const;

    private:
        using Clock = std::chrono::high_resolution_clock;
        using Second = std::chrono::duration<double, std::ratio<1> >;
        std::chrono::time_point<Clock> curr{Clock::now()};
};

#endif