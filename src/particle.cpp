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

double Particle::getMass() const {
    return mass;
}

Eigen::Vector3d Particle::getPosition(){
    return position;
}
Eigen::Vector3d Particle::getVelocity(){
    return velocity;
}
Eigen::Vector3d Particle::getAcceleration(){
    return acceleration;
}

void Particle::print(){
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