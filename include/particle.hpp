#ifndef particle_h
#define particle_h

#include <Eigen/Core>
#include <iostream>
#include <string>
#include <vector>

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

class pSystem {
    public:
        pSystem();
        // populate the system with the following functions
        void addParticle(Particle p);
        void deleteParticle(int n);
        Particle &getParticle(int n);
        void printParticles();
        int getNumOfParticles();

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

#endif