#include <Eigen/Core>
#include <vector>
#include "particle.hpp"

class System {
    public:
        System();
        void addParticle(Particle p);
        void deleteParticle(int n);
        Particle &getParticle(int n);
        void printParticles();
        int getNumOfParticles();
        Eigen::Vector3d calcAcceleration(Particle &p1, Particle &p2);
        

    private:
        int numParticles;
        std::vector<Particle> particles;
};