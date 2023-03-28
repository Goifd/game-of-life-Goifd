#include "particle.hpp"


Particle::Particle(double in_mass, Eigen::Vector3d pos, Eigen::Vector3d vel) : mass{in_mass}, velocity{vel}, position{pos} {
    acceleration = 0;
};

double Particle::getMass() const {
    return mass;
}

Eigen::Vector3d& Particle::getPosition(){
    return position;
}
Eigen::Vector3d& Particle::getVelocity(){
    return velocity;
}
Eigen::Vector3d& Particle::getAcceleration(){
    return acceleration;
}

void Particle::print(){
    
}

void Particle::addAcceleration(Eigen::Vector3d a){
    acceleration += a;
}

void Particle::update(double dt){
    velocity += acceleration*dt;
    position += velocity*dt;
    // reset acceleration so the addAcceleration can start adding up contributions from 0
    acceleration = 0;
}