#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "particle.hpp"
#include <Eigen/Core>
#include <memory>

using Catch::Matchers::WithinRel;

TEST_CASE( "Particle sets arguments correctly", "[particle_set]" ) {
    Particle p1{3.14, Eigen::Vector3d(1,2,3), Eigen::Vector3d(1,2,3)};
    REQUIRE_THAT( p1.getMass(), WithinRel(3.14, 0.01) );
    REQUIRE(p1.getVelocity().isApprox(Eigen::Vector3d(1,2,3)));
    REQUIRE(p1.getPosition().isApprox(Eigen::Vector3d(1,2,3)));

    REQUIRE_THROWS(Particle(0, Eigen::Vector3d(1,2,3), Eigen::Vector3d(1,2,3)));
    REQUIRE_THROWS(Particle(-1, Eigen::Vector3d(1,2,3), Eigen::Vector3d(1,2,3)));
}

TEST_CASE( "Particle update function works correctly", "[particle_update]" ) {
    // no acceleration
    Particle p1{1, Eigen::Vector3d(0,0,0), Eigen::Vector3d(0,0,0)};
    p1.update(1);
    REQUIRE(p1.getVelocity().isApprox(Eigen::Vector3d(0,0,0)));
    REQUIRE(p1.getPosition().isApprox(Eigen::Vector3d(0,0,0)));

    Particle p2{1, Eigen::Vector3d(0,0,0), Eigen::Vector3d(1,1,1)};
    p2.update(2);
    REQUIRE(p2.getVelocity().isApprox(Eigen::Vector3d(1,1,1)));
    REQUIRE(p2.getPosition().isApprox(Eigen::Vector3d(2,2,2)));

    // constant acceleration
    Particle p3{1, Eigen::Vector3d(0,0,0), Eigen::Vector3d(0,0,0)};
    double dt = 0.01;
    double t = 5;
    for(double i=0; i<t; i+=dt){
        p3.addAcceleration(Eigen::Vector3d(1,0,0));
        p3.update(dt);
    }
    REQUIRE(p3.getVelocity().isApprox(Eigen::Vector3d(5,0,0), 0.1));
    REQUIRE(p3.getPosition().isApprox(Eigen::Vector3d(25/2,0,0), 0.1));

    // artificial acceleration
    Particle p4{1, Eigen::Vector3d(1,0,0), Eigen::Vector3d(0,1,0)};
    dt = 0.001;
    t = 2*3.1415;
    for(double i=0; i<t; i+=dt){
        p4.addAcceleration(-p4.getPosition());
        p4.update(dt);
    }
    REQUIRE(p4.getPosition().isApprox(Eigen::Vector3d(1,0,0), 0.1));
}

TEST_CASE("System initialization and modification works correctly", "[system_init]"){
    std::unique_ptr<pSystem> s1(new pSystem());
    REQUIRE(s1->getNumOfParticles()==0);

    s1->addParticle(Particle(100, Eigen::Vector3d(0,0,0), Eigen::Vector3d(1, 0, 0)));
    s1->addParticle(Particle(200, Eigen::Vector3d(1,1,1), Eigen::Vector3d(1, 1, 0)));
    s1->addParticle(Particle(300, Eigen::Vector3d(1,1,1), Eigen::Vector3d(1, 1, 0)));
    REQUIRE(s1->getNumOfParticles()==3);

    s1->deleteParticle(1);
    REQUIRE(s1->getNumOfParticles()==2);
}

TEST_CASE("Gravitational force calculation between particles works correctly", "[calcAcceleration]"){
    std::unique_ptr<pSystem> s1(new pSystem());

    Eigen::Vector3d acc1 = s1->calcAcceleration(Particle(100, Eigen::Vector3d(0,0,0), Eigen::Vector3d(1, 0, 0)),
                                                Particle(10, Eigen::Vector3d(1,1,1), Eigen::Vector3d(1, 1, 0)),
                                                0.0);
    REQUIRE(acc1.isApprox(Eigen::Vector3d(1.92,1.92,1.92), 0.01));

    Eigen::Vector3d acc2 = s1->calcAcceleration(Particle(100.5, Eigen::Vector3d(3.23,30.0,0.0), Eigen::Vector3d(1, 0, 0)),
                                                Particle(10.0, Eigen::Vector3d(1.0,1.2,1.0), Eigen::Vector3d(1, 1, 0)),
                                                0.0);
    REQUIRE(acc2.isApprox(Eigen::Vector3d(-0.0009235,-0.0119273,0.0004141), 0.0001));

    Eigen::Vector3d acc3 = s1->calcAcceleration(Particle(1005.0, Eigen::Vector3d(0,0,0), Eigen::Vector3d(1, 0, 0)),
                                                Particle(10.0, Eigen::Vector3d(1.0,1.2,1.0), Eigen::Vector3d(1, 1, 0)),
                                                1.0);
    REQUIRE(acc3.isApprox(Eigen::Vector3d(1.068871,1.282645,1.068871), 0.0001));

    REQUIRE_THROWS(s1->calcAcceleration(Particle(100, Eigen::Vector3d(0,0,0), Eigen::Vector3d(1, 0, 0)),
                                        Particle(10, Eigen::Vector3d(1,1,1), Eigen::Vector3d(1, 1, 0)),
                                         -10));
}

TEST_CASE("Gravitational force calculation between more than 2 particles works correctly", "[updateAcceleration]"){
    // checks the equally sized case and also if the particle calculates its acceleration due to itself 
    // due to code structure
    std::unique_ptr<pSystem> s1(new pSystem());
    s1->addParticle(Particle(100, Eigen::Vector3d(0,0,0), Eigen::Vector3d(1, 0, 0)));
    s1->addParticle(Particle(100, Eigen::Vector3d(1,0,0), Eigen::Vector3d(1, 0, 0)));
    s1->addParticle(Particle(100, Eigen::Vector3d(-1,0,0), Eigen::Vector3d(1, 0, 0)));

    s1->updateAccelerations(0.0);

    REQUIRE(s1->getParticle(0).getAcceleration().isApprox(Eigen::Vector3d(0,0,0),0.0001));
    REQUIRE(s1->getParticle(1).getAcceleration().isApprox(Eigen::Vector3d(-125,0,0),0.0001));
    REQUIRE(s1->getParticle(2).getAcceleration().isApprox(Eigen::Vector3d(125,0,0),0.0001));
}

// function to compare the position and velocity vectors for random initialization
bool compareVector3d(Eigen::Vector3d v1, Eigen::Vector3d v2, double range){
    if(v1(0)>=(v2(0)-range) && v1(0)<=(v2(0)+range) &&
       v1(1)>=(v2(1)-range) && v1(1)<=(v2(1)+range) &&
       v1(2)>=(v2(2)-range) && v1(0)<=(v2(2)+range)){

        return true;
    }
    return false;
}

TEST_CASE("Initial condition generator works correctly","[initCondGenerator]"){
// create system generator
  solarSysGenerator generator = solarSysGenerator();

  // initialize solar system
  std::unique_ptr<pSystem> s1 = generator.generateInitialConditions();

  // test masses
  REQUIRE(s1->getParticle(0).getMass() == 1.);
  REQUIRE(s1->getParticle(1).getMass() == 1./6023600);
  REQUIRE(s1->getParticle(2).getMass() == 1./408524);
  REQUIRE(s1->getParticle(3).getMass() == 1./332946.038);
  REQUIRE(s1->getParticle(4).getMass() == 1./3098710);
  REQUIRE(s1->getParticle(5).getMass() == 1./1047.55);
  REQUIRE(s1->getParticle(6).getMass() == 1./3499);
  REQUIRE(s1->getParticle(7).getMass() == 1./22962);
  REQUIRE(s1->getParticle(8).getMass() == 1./19352);

  // test velocities and position (sin and cos is between -1 and 1, test final vel and pos values to be between the bound)
  REQUIRE(s1->getParticle(0).getVelocity().isApprox(Eigen::Vector3d(0,0,0),0.0001));
  REQUIRE(s1->getParticle(0).getPosition().isApprox(Eigen::Vector3d(0,0,0),0.0001));

  REQUIRE(compareVector3d(s1->getParticle(1).getVelocity(), Eigen::Vector3d(0,0,0), 1.0/std::pow(0.4,0.5)));
  REQUIRE(compareVector3d(s1->getParticle(1).getPosition(), Eigen::Vector3d(0,0,0),0.4));

  REQUIRE(compareVector3d(s1->getParticle(2).getVelocity(), Eigen::Vector3d(0,0,0), 1.0/std::pow(0.7,0.5)));
  REQUIRE(compareVector3d(s1->getParticle(2).getPosition(), Eigen::Vector3d(0,0,0),0.7));

  REQUIRE(compareVector3d(s1->getParticle(3).getVelocity(), Eigen::Vector3d(0,0,0), 1.0/std::pow(1.0,0.5)));
  REQUIRE(compareVector3d(s1->getParticle(3).getPosition(), Eigen::Vector3d(0,0,0),1.0));

  REQUIRE(compareVector3d(s1->getParticle(4).getVelocity(), Eigen::Vector3d(0,0,0), 1.0/std::pow(1.5,0.5)));
  REQUIRE(compareVector3d(s1->getParticle(4).getPosition(), Eigen::Vector3d(0,0,0),1.5));

  REQUIRE(compareVector3d(s1->getParticle(5).getVelocity(), Eigen::Vector3d(0,0,0), 1.0/std::pow(5.2,0.5)));
  REQUIRE(compareVector3d(s1->getParticle(5).getPosition(), Eigen::Vector3d(0,0,0),5.2));

  REQUIRE(compareVector3d(s1->getParticle(6).getVelocity(), Eigen::Vector3d(0,0,0), 1.0/std::pow(9.5,0.5)));
  REQUIRE(compareVector3d(s1->getParticle(6).getPosition(), Eigen::Vector3d(0,0,0),9.5));

  REQUIRE(compareVector3d(s1->getParticle(7).getVelocity(), Eigen::Vector3d(0,0,0), 1.0/std::pow(19.2,0.5)));
  REQUIRE(compareVector3d(s1->getParticle(7).getPosition(), Eigen::Vector3d(0,0,0),19.2));

  REQUIRE(compareVector3d(s1->getParticle(8).getVelocity(), Eigen::Vector3d(0,0,0), 1.0/std::pow(30.1,0.5)));
  REQUIRE(compareVector3d(s1->getParticle(8).getPosition(), Eigen::Vector3d(0,0,0),30.1));
}

TEST_CASE("Solar system evolves correctly", "[solarSys]"){
// create system generator
  solarSysGenerator generator = solarSysGenerator();

  // initialize solar system
  std::unique_ptr<pSystem> s1 = generator.generateInitialConditions();

  // save Earth's initial pos
  Eigen::Vector3d p = s1->getParticle(3).getPosition();
  // evolve for one year
  s1->evolveSystem(6.283185, 0.0001);

  // check if Earth's initial position matches its position after one year
  REQUIRE(s1->getParticle(3).getPosition().isApprox(p, 0.01));
}

TEST_CASE("evolveSystem function works correctly", "[evolveSystem]"){
    // create simple system of three bodies
    std::unique_ptr<pSystem> s1(new pSystem());
    s1->addParticle(Particle(100, Eigen::Vector3d(0,0,0), Eigen::Vector3d(0, 0, 0)));
    s1->addParticle(Particle(100, Eigen::Vector3d(1,0,0), Eigen::Vector3d(0, 0, 0)));
    s1->addParticle(Particle(100, Eigen::Vector3d(-1,0,0), Eigen::Vector3d(0, 0, 0)));

    s1->evolveSystem(0.1,0.1);

    REQUIRE(s1->getParticle(0).getVelocity().isApprox(Eigen::Vector3d(0, 0, 0), 0.001));
    REQUIRE(s1->getParticle(1).getVelocity().isApprox(Eigen::Vector3d(-12.5, 0, 0), 0.001));
    REQUIRE(s1->getParticle(2).getVelocity().isApprox(Eigen::Vector3d(12.5, 0, 0), 0.001));

    REQUIRE(s1->getParticle(0).getPosition().isApprox(Eigen::Vector3d(0, 0, 0), 0.001));
    REQUIRE(s1->getParticle(1).getPosition().isApprox(Eigen::Vector3d(1, 0, 0), 0.001));
    REQUIRE(s1->getParticle(2).getPosition().isApprox(Eigen::Vector3d(-1, 0, 0), 0.001));

    s1->evolveSystem(0.1,0.1);

    REQUIRE(s1->getParticle(0).getVelocity().isApprox(Eigen::Vector3d(0, 0, 0), 0.001));
    REQUIRE(s1->getParticle(1).getVelocity().isApprox(Eigen::Vector3d(-25, 0, 0), 0.001));
    REQUIRE(s1->getParticle(2).getVelocity().isApprox(Eigen::Vector3d(25, 0, 0), 0.001));

    REQUIRE(s1->getParticle(0).getPosition().isApprox(Eigen::Vector3d(0, 0, 0), 0.001));
    REQUIRE(s1->getParticle(1).getPosition().isApprox(Eigen::Vector3d(-0.25, 0, 0), 0.001));
    REQUIRE(s1->getParticle(2).getPosition().isApprox(Eigen::Vector3d(0.25, 0, 0), 0.001));  
}

TEST_CASE("Parallelization works correctly", "[parallelization]"){
    // create simple system of three bodies
    std::unique_ptr<pSystem> s1(new pSystem());
    s1->addParticle(Particle(100, Eigen::Vector3d(0,0,0), Eigen::Vector3d(0, 0, 0)));
    s1->addParticle(Particle(100, Eigen::Vector3d(1,1,0), Eigen::Vector3d(0, 0, 0)));
    s1->addParticle(Particle(100, Eigen::Vector3d(-1,-1,0), Eigen::Vector3d(0, 0, 0)));
    s1->addParticle(Particle(100, Eigen::Vector3d(-1,1,0), Eigen::Vector3d(0, 0, 0)));
    s1->addParticle(Particle(100, Eigen::Vector3d(1,-1,0), Eigen::Vector3d(0, 0, 0)));

    s1->evolveSystem(6.2832,0.0001);

    REQUIRE(s1->getParticle(0).getVelocity().isApprox(Eigen::Vector3d(0, 0, 0), 0.001));
    // symmetric system so absolute value of velocity and pos of four corner particles should always be equal
    Eigen::Vector3d v1 = s1->getParticle(1).getVelocity().cwiseAbs();
    Eigen::Vector3d v2 = s1->getParticle(2).getVelocity().cwiseAbs();
    Eigen::Vector3d v3 = s1->getParticle(3).getVelocity().cwiseAbs();
    Eigen::Vector3d v4 = s1->getParticle(4).getVelocity().cwiseAbs();
    REQUIRE(v1.isApprox(v2));
    REQUIRE(v2.isApprox(v3));
    REQUIRE(v3.isApprox(v4));

    Eigen::Vector3d r1 = s1->getParticle(1).getPosition().cwiseAbs();
    Eigen::Vector3d r2 = s1->getParticle(2).getPosition().cwiseAbs();
    Eigen::Vector3d r3 = s1->getParticle(3).getPosition().cwiseAbs();
    Eigen::Vector3d r4 = s1->getParticle(4).getPosition().cwiseAbs();
    REQUIRE(r1.isApprox(r2));
    REQUIRE(r2.isApprox(r3));
    REQUIRE(r3.isApprox(r4));

}


