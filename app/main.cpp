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
  app.add_option("-s, --timestep", dt, "Time step for Euler integration.");

  // throw exception by the parser if input format is invalid
  // otherwise parse input
  try{
    app.parse(argc, argv);
  } catch(const CLI::ParseError &e){
    return app.exit(e);
  }

  // create timer
  
  // create system generator
  sysGenerator generator = sysGenerator();

  // initialize solar system
  std::unique_ptr<pSystem> s1 = generator.getSystem();

  // the system with random initial conditions
  std::cout << "The system before the evolution: " << std::endl;
  s1->printParticles();

  // evolve the system with total time t and timestep dt and epsilon=0.0
  s1->evolveSystem(2*M_PI, dt, t);

  // the system after the evolution
  std::cout << "The system after evolving for t: " << t << " and with dt: " << dt << std::endl;
  s1->printParticles();

  

  

  int returnStatus = EXIT_FAILURE;

  return returnStatus;
}
