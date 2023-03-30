#include "particle.hpp"


Particle::Particle(double in_mass, Eigen::Vector3d pos, Eigen::Vector3d vel) : mass{in_mass}, velocity{vel}, position{pos} {
    if(mass<0 || mass==0){
        std::string errorMessage = "Particle's mass must be >= 0.";
        throw std::invalid_argument(errorMessage);
    }
        
    acceleration(0) = 0;
    acceleration(1) = 0;
    acceleration(2) = 0;
};

double Particle::getMass() const{
    return mass;
}

const Eigen::Vector3d& Particle::getPosition() const {
    return position;
}
const Eigen::Vector3d& Particle::getVelocity() const {
    return velocity;
}
const Eigen::Vector3d& Particle::getAcceleration() const {
    return acceleration;
}

void Particle::print() const{
    Eigen::IOFormat CommaInitFmt(3, Eigen::DontAlignCols, ",",",", "", "", "(", ")");
    std::cout << "mass: " << mass << std::endl;
    std::cout << "position: " << position.format(CommaInitFmt) << std::endl;
    std::cout << "velocity: " << velocity.format(CommaInitFmt) << std::endl; 
}

void Particle::addAcceleration(Eigen::Vector3d a){
    acceleration += a;
}

void Particle::update(double dt){
    velocity += acceleration*dt;
    position += velocity*dt;
    // reset acceleration so the addAcceleration can start adding up contributions from 0
    acceleration(0) = 0;
    acceleration(1) = 0;
    acceleration(2) = 0;
}
pSystem::pSystem(){
    numParticles=0;
}

void pSystem::addParticle(Particle p){
    particles.push_back(p);
    numParticles += 1;
}

Particle& pSystem::getParticle(int n){
    // indexing error is handled internally by vector
    return particles.at(n);
}

void pSystem::printParticles(){
    for(int i=0; i<numParticles; i++){
        std::cout << "particle " << i << std::endl;
        particles.at(i).print();
        std::cout << "-------------------" << std::endl;
    }
}

void pSystem::deleteParticle(int n){
    // error with index input is handled internally by vector class
    particles.erase(particles.begin() + n);
    numParticles -= 1;
}

int pSystem::getNumOfParticles(){
    return numParticles;
}

// acceleration on particle1 due to particle2
Eigen::Vector3d pSystem::calcAcceleration(const Particle& p1, const Particle& p2, double epsilon){
    double distance = ((p2.getPosition()-p1.getPosition()).norm());
    Eigen::Vector3d acc = p2.getMass()*(p2.getPosition()-p1.getPosition())/std::pow((std::pow(distance,2.0)+std::pow(epsilon,2.0)),1.5);
    return acc;
}

void pSystem::updateAccelerations(){
    // first loop can be parallelized, do not need copy of classes since acceleration does not depend on the current value of acceleration
    // and other parameters do not change
    for(Particle& p : particles){
        for(Particle& k : particles){
            if(&p != &k)
                p.addAcceleration(calcAcceleration(p, k));
        }      
    }
}

void pSystem::updateVelPos(double dt){
    for(Particle& p : particles){
        p.update(dt);
    }
}

void pSystem::evolveSystem(double t, double dt){
    // both methods are parallelized themselves
    for(int i=0; i<t; i+=dt){
        updateAccelerations();
        // threads should wait for each other here
        updateVelPos(dt);
    }
}
