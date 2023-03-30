//#ifndef system_h
//#define system_h

#include <Eigen/Core>
#include <vector>
#include "particle.hpp"

class particleSystem {
    public:
        particleSystem();
        // populate the system with the following functions
        void addParticle(Particle p);
        void deleteParticle(int n);
        Particle &getParticle(int n);
        void printParticles();
        int getNumOfParticles();

        // calculates acceleration between two particles
        Eigen::Vector3d calcAcceleration(Particle &p1, Particle &p2, double epsilon=0.0);

        // updates acceleration parameter for all particles in the system
        void updateAccelerations();

        // evolves the system
        void evolveSystem(double t, double dt);
        

    private:
        int numParticles;
        std::vector<Particle> particles;
};

//#endif