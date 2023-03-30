#include <iostream>
#include <Eigen/Core>
#include <memory>
#include "particle.hpp"
#include "particleSystem.hpp"

int main() {
  Particle p1 = Particle(100, Eigen::Vector3d(0,0,0), Eigen::Vector3d(1, 0, 0));
  Particle p2 = Particle(100, Eigen::Vector3d(1,1,1), Eigen::Vector3d(1, 1, 0));

  //particleSystem* s1 = new particleSystem();
  std::unique_ptr<particleSystem> s1(new particleSystem());
  //s1->addParticle(Particle(100, Eigen::Vector3d(0,0,0), Eigen::Vector3d(1, 0, 0)));
  //s1->addParticle(Particle(100, Eigen::Vector3d(1,1,1), Eigen::Vector3d(1, 1, 0)));


  return 0;
}
