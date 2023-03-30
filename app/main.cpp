#include <iostream>
#include <Eigen/Core>
#include <particle.hpp>

int main() {
  Eigen::Vector3d v{1, 0, 0};
  Eigen::Vector3d r{0,0,0};
  Particle p1 = Particle(100, r, v);
  
  p1.print();
  std::cout << "---------------------" << std::endl;
  p1.update(1);
  p1.print();
  std::cout << "---------------------" << std::endl;
  p1.update(0.1);
  p1.print();
  std::cout << "---------------------" << std::endl;
  p1.update(0);
  p1.print();
  std::cout << "---------------------" << std::endl;

  return 0;
}
