#include <iostream>
#include <Eigen/Core>
#include <memory>
#include "particle.hpp"
#include <CLI11.hpp>
#include <vector>

int main(int argc, char** argv) {

  CLI::App app{"Solar System Simulator"};

  // these will throw exceptions if not initialized
  double dt = 0;
  double t = 0;

  // build parser
  app.add_option("-t, --time", t, "Total simulation time.");
  app.add_option("-dt, --timestep", dt, "Time step for Euler integration.");

  // throw exception by the parser if input format is invalid
  // otherwise parse input
  try{
    app.parse(argc, argv);
  } catch(const CLI::ParseError &e){
    return app.exit(e);
  }

  // Solar System data
  std::vector<double> masses{1.,1./6023600,1./408524,1./332946.038,1./3098710,1./1047.55,1./3499,1./22962,1./19352};
  std::vector<double> distances{0.0, 0.4, 0.7, 1, 1.5, 5.2, 9.5, 19.2, 30.1};

  // Create Solar System
  std::unique_ptr<pSystem> s1(new pSystem());

  // add sun manually 
  s1->addParticle(Particle(masses[0], Eigen::Vector3d(0,0,0), Eigen::Vector3d(0, 0, 0)));
  // add other planets with random initial conditions
  for(int i=0; i<9; i++){
    
    s1->addParticle(Particle(masses[i], Eigen::Vector3d(0,0,0), Eigen::Vector3d(1, 0, 0)));
  }

  int returnStatus = EXIT_FAILURE;

  return returnStatus;
}
