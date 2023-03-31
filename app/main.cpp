#include <iostream>
#include <Eigen/Core>
#include <memory>
#include "particle.hpp"
#include <CLI11.hpp>
#include <vector>
#include <tuple>
#include <string>

int main(int argc, char** argv) {

  CLI::App app{"Solar System Simulator"};

  // these will throw exceptions if not initialized
  double dt = 0.0;
  double t = 0.0;
  double epsilon = 0.0;
  int n = 0;

  // build parser
  app.add_option("-t, --time", t, "Total simulation time.");
  app.add_option("-s, --timestep", dt, "Time step for Euler integration.");
  app.add_option("-e, --epsilon", epsilon, "Softening factor for acceleration calculation.");
  app.add_option("-n, --nbody", n, "Specifies the number of bodies to simulate, if not set, the system is a randomly positioned solar system.");

  // throw exception by the parser if input format is invalid
  // otherwise parse input
  try{
    app.parse(argc, argv);
  } catch(const CLI::ParseError &e){
    return app.exit(e);
  }

  if(argc == 0 || dt<=0 || t<=0 || epsilon<0 || n < 0){
    std::cout << "No argument given, or arguments are wrong. For help execute solarSystemSimulator --help." << std::endl;
    return 0;
  }
  
  // create system generator
  randomSysGenerator randomGenerator = randomSysGenerator(n);
  solarSysGenerator solarGenerator = solarSysGenerator();

  // create timer
  Timer timer;

  // initialize system
  std::unique_ptr<pSystem> s1;
  if(n>0)
  {
    s1 = randomGenerator.generateInitialConditions();
  }else{
    s1 = solarGenerator.generateInitialConditions();
  }

  // print initial state
  std::cout << "Initial state of the system: " << std::endl;
  s1->printParticles();

  // evolve the system with total time t and timestep dt and epsilon=0.0
  s1->evolveSystem(t, dt, epsilon);

  // measure elapsed time
  double elapsed = timer.elapsed();

  // print final state
  std::cout << "Simulation done: " << std::endl;
  std::cout << "dt: " << dt << " runtime: " << elapsed << " /step: " << elapsed/int(t/dt) << std::endl;
  s1->printParticles();

  return 0;
}
