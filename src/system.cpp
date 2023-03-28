#include "system.hpp"

System::System(){
    numParticles=0;
    particles = new Particles();
}

void System::addParticle(Particle p){
    particles.push_back(p);
    numParticles += 1;
}

Particle System::getParticle(int n){
    return particles.at(n);
}

void System::printParticles(){
    for(int i=0; i<numParticles; i++){
        std::cout << "particle " << i << std::endl;
        std::cout << "mass: " << particles.at(i).getMass() << std::endl;
        std::cout << "position: " << particles.at(i).getPosition().transpose() << std::endl;
        std::cout << "velocity: " << particles.at(i).getPosition().transpose() << std::endl;
    }
}

