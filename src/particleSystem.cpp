#include "particleSystem.hpp"

particleSystem::particleSystem(){
    numParticles=0;
    particles = new Particles();
}

void particleSystem::addParticle(Particle p){
    particles.push_back(p);
    numParticles += 1;
}

Particle& particleSystem::getParticle(int n){
    // indexing error is handled internally by vector
    return particles.at(n);
}

void particleSystem::printParticles(){
    for(int i=0; i<numParticles; i++){
        std::cout << "particle " << i << std::endl;
        particles.at(i).print()
        std::cout << "-------------------" << std::endl;
    }
}

void particleSystem::deleteParticle(int n){
    // error with index input is handled internally by vector class
    particles.erase(particles.begin(), + n);
}

int particleSystem::getNumOfParticles(){
    return numParticles;
}

// acceleration on particle1 due to particle2
Eigen::Vector3d System::calcAcceleration(Particle &p1, Particle &p2, double epsilon=0.0){
    p2.print()
    double distance = ((p2.getPosition()-p1.getPosition()).norm())
    p2.print()
    Eigen::Vector3d acc = p2.getMass()*(p2.getPosition()-p1.getPosition())/(distance**2+epsilon**2)*(3/2)
    return acc;
}

void particleSystem::updateAccelerations(){
    // first loop can be parallelized, do not need copy of classes since acceleration does not depend on the current value of acceleration
    // and other parameters do not change
    for(const Particle& p : particles){
        for(const Particle& k : particles){
            if(&p != &k)
                p.addAcceleration(calcAcceleration(p, k));
        }      
    }
}

void particleSystem::updateVelPos(dt){
    for(const Particle& p : particles){
        p.update(dt);
    }
}

void particleSystem::evolveSystem(double t, double dt){
    // both methods are parallelized themselves
    for(int i=0; i<t; i+=dt){
        updateAcceleration(dt);
        // threads should wait for each other here
        updateVelPos();
    }
}



