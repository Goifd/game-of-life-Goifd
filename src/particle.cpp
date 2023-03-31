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
    if(epsilon<0)
        throw std::invalid_argument("Parameter epsilon must be larger than or equal to zero.");
    double distance = ((p2.getPosition()-p1.getPosition()).norm());
    Eigen::Vector3d acc = p2.getMass()*(p2.getPosition()-p1.getPosition())/std::pow((std::pow(distance,2.0)+std::pow(epsilon,2.0)),1.5);
    return acc;
}

void pSystem::updateAccelerations(double epsilon){
    // first loop can be parallelized, do not need copy of classes since acceleration does not depend on the current value of acceleration
    // and other parameters do not change
    for(Particle& p : particles){
        for(Particle& k : particles){
            if(&p != &k)
                p.addAcceleration(calcAcceleration(p, k, epsilon));
        }      
    }
}

void pSystem::updateVelPos(double dt){
    for(Particle& p : particles){
        p.update(dt);
    }
}

void pSystem::evolveSystem(double t, double dt, double epsilon){
    // both methods are parallelized themselves
    int steps = 0;
    for(double i=0; i<=t; i+=dt){
        //std::cout << t << std::endl;
        // function calculates acceleration on all particles
        updateAccelerations(epsilon);
        // function updates velocity and position of particles
        updateVelPos(dt);
        steps +=1;
    }
    std::cout << "\n" << std::endl;
    std::cout << "Total number of steps: " << steps << std::endl;
}

sysGenerator::sysGenerator(){
    // set up random number generator
    std::mt19937 rng_mt(1);
    std::uniform_real_distribution<double> distribution(0, 2*M_PI);
    auto dice = std::bind(distribution, rng_mt);

    // add sun manually 
    s1->addParticle(Particle(masses[0], Eigen::Vector3d(0,0,0), Eigen::Vector3d(0, 0, 0)));

    double theta = 0.0;
    double r = 0.0;
    double m = 0.0;

    // add other planets with random initial conditions
    for(int i=1; i<9; i++){
        theta = dice();
        r = distances[i];
        m = masses[i];

        double r_x = r*std::sin(theta);
        double r_y = r*std::cos(theta);
        double v_x = -1/std::pow(r,0.5)*std::cos(theta);
        double v_y = 1/std::pow(r,0.5)*std::sin(theta);

        s1->addParticle(Particle(m, Eigen::Vector3d(r_x, r_y, 0.0), Eigen::Vector3d(v_x, v_y, 0.0)));
    }
}

std::unique_ptr<pSystem> sysGenerator::getSystem(){
    return move(s1);
}

void Timer::reset(){
    curr = Clock::now();
}

double Timer::elapsed() const{
    return std::chrono::duration_cast<Second>(Clock::now() - curr).count();
}
