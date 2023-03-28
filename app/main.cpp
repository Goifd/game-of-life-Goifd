#include <iostream>
#include <Eigen/Core>
#include <particle.hpp>

int main() {
  Eigen::Vector3d v{1, 0, 0};
  Eigen::Vector3d r{0,0,0};
  Particle p1 = Particle(100, r, v);
  
  std::cout << p1.getPosition() << std::endl;
  p1.update(1);
  std::cout << "---------------------" << std::endl;
  std::cout << p1.getVelocity() << std::endl;
  std::cout << "---------------------" << std::endl;
  std::cout << p1.getPosition() << std::endl;
  std::cout << "---------------------" << std::endl;
  std::cout << "Hello World!\n" << v << std::endl;

  return 0;
}
