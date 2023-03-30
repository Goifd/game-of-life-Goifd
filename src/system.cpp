#include "system.hpp"

System::System(){
    numParticles=0;
    particles = new Particles();
}

void System::addParticle(Particle p){
    particles.push_back(p);
    numParticles += 1;
}

Particle& System::getParticle(int n){
    // indexing error is handled internally by vector
    return particles.at(n);
}

void System::printParticles(){
    for(int i=0; i<numParticles; i++){
        std::cout << "particle " << i << std::endl;
        particles.at(i).print()
        std::cout << "-------------------" << std::endl;
    }
}

void System::deleteParticle(int n){
    // error with index input is handled internally by vector class
    particles.erase(particles.begin(), + n);
}

int System::getNumOfParticles(){
    return numParticles;
}



