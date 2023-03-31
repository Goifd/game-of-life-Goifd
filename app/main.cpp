#include <iostream>
#include <Eigen/Core>
#include <memory>
#include "particle.hpp"
#include <CLI11.hpp>
#include <vector>
#include <tuple>

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

  if(argc == 0 || dt<=0 || t<=0){
    std::cout << "No argument given, or arguments are wrong. For help execute solarSystemSimulator --help." << std::endl;
    return 0;
  }
  
  // create system generator
  sysGenerator generator = sysGenerator();

  // initialize solar system
  std::unique_ptr<pSystem> s1 = generator.getSystem();

  // the system with random initial conditions
  std::tuple<double, double> E = s1->getEnergy();
  std::cout << "Initial E_kin = " << std::get<0>(E) << std::endl;
  std::cout << "Initial E_pot = " << std::get<1>(E) << std::endl;
  std::cout << "Initial E_tot = " << std::get<0>(E) + std::get<1>(E) << std::endl;
  std::cout << "The system before the evolution: \n" << std::endl;
  s1->printParticles();

  // create timer
  Timer timer;
  // evolve the system with total time t and timestep dt and epsilon=0.0
  s1->evolveSystem(t, dt);
  // measure elapsed time
  double elapsed = timer.elapsed();

  // the system after the evolution
  std::cout << "Time taken to run the simulation: " << elapsed << std::endl;
  std::cout << "The system after evolving for t: " << t << " and with dt: " << dt << std::endl;
  std::tuple<double, double> E_after = s1->getEnergy();
  std::cout << "After the evolution E_kin = " << std::get<0>(E_after) << std::endl;
  std::cout << "After the evolution E_pot = " << std::get<1>(E_after) << std::endl;
  std::cout << "After the evolution E_tot = " << std::get<0>(E_after) + std::get<1>(E_after) << std::endl;
  std::cout << "\n" << std::endl;;
  s1->printParticles();

  std::cout << std::endl;
  std::cout << "Initial E_tot = " << std::get<0>(E) + std::get<1>(E) << std::endl;
  std::cout << "After the evolution E_tot = " << std::get<0>(E_after) + std::get<1>(E_after) << std::endl;
  std::cout << "E drop: " << (std::get<0>(E) + std::get<1>(E))-(std::get<0>(E_after) + std::get<1>(E_after)) << std::endl;  

  

  

  int returnStatus = EXIT_FAILURE;

  return returnStatus;
}
