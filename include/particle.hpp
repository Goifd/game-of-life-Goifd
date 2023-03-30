#ifndef particle_h
#define particle_h

#include <Eigen/Core>
#include <iostream>
#include <string>

class Particle {
    public:
        Particle(double in_mass, Eigen::Vector3d pos, Eigen::Vector3d vel);
        double getMass() const;
        // return by value to avoid unintentional editing 
        Eigen::Vector3d getPosition();
        Eigen::Vector3d getVelocity();
        Eigen::Vector3d getAcceleration();
        void addAcceleration(Eigen::Vector3d a);
        void update(double dt);
        void print();

    private:
        const double mass;
        Eigen::Vector3d position;
        Eigen::Vector3d velocity;
        Eigen::Vector3d acceleration;
};

#endif