#include <iostream>
#include <Eigen/Core>
#include <memory>
#include "particle.hpp"

int main() {
  Particle p1 = Particle(100, Eigen::Vector3d(0,0,0), Eigen::Vector3d(1, 0, 0));
  Particle p2 = Particle(100, Eigen::Vector3d(1,1,1), Eigen::Vector3d(1, 1, 0));

  //particleSystem p3 = particleSystem();
  //particleSystem* s1 = new particleSystem();
  std::unique_ptr<pSystem> s1(new pSystem());
  s1->addParticle(Particle(100, Eigen::Vector3d(0,0,0), Eigen::Vector3d(1, 0, 0)));
  s1->addParticle(Particle(100, Eigen::Vector3d(1,1,1), Eigen::Vector3d(1, 1, 0)));

  s1->calcAcceleration(Particle(100, Eigen::Vector3d(0,0,0), Eigen::Vector3d(1, 0, 0)),
                       Particle(100, Eigen::Vector3d(1,1,1), Eigen::Vector3d(1, 1, 0)));
  //s1->printParticles();
  //s1->addParticle();
  //s1->deleteParticle();
  //s1->getNumOfParticles();
  //s1->getParticle();
  //s1->evolveSystem();
  //s1->updateAccelerations();
  //s1->updateVelPos();
  // calculate force between particles

  //


  return 0;
}
