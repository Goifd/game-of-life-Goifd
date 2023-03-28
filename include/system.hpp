#include <Eigen/Core>
#include <vector>
#include "particle.hpp"

class System {
    public:
        System();
        void addParticle(Particle p);
        Particle getParticle(int n);
        void printParticles();

    private:
        int numParticles;
        std::vector<Particle> particles;
};