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

TEST_CASE("Gravitational force between particles is as expected"){
    std::unique_ptr<pSystem> s1(new pSystem());

    Eigen::Vector3d acc1 = s1->calcAcceleration(Particle(100, Eigen::Vector3d(0,0,0), Eigen::Vector3d(1, 0, 0)),
                       Particle(10, Eigen::Vector3d(1,1,1), Eigen::Vector3d(1, 1, 0)));
    REQUIRE(acc1.isApprox(Eigen::Vector3d(1.92,1.92,1.92), 0.01));

    Eigen::Vector3d acc2 = s1->calcAcceleration(Particle(100.5, Eigen::Vector3d(3.23,30.0,0.0), Eigen::Vector3d(1, 0, 0)),
                       Particle(10.0, Eigen::Vector3d(1.0,1.2,1.0), Eigen::Vector3d(1, 1, 0)));
    REQUIRE(acc2.isApprox(Eigen::Vector3d(-0.0009235,-0.0119273,0.0004141), 0.0001));

    Eigen::Vector3d acc3 = s1->calcAcceleration(Particle(1005.0, Eigen::Vector3d(0,0,0), Eigen::Vector3d(1, 0, 0)),
                       Particle(10.0, Eigen::Vector3d(1.0,1.2,1.0), Eigen::Vector3d(1, 1, 0)),1.0);
    std::cout << acc3 << std::endl;
    REQUIRE(acc3.isApprox(Eigen::Vector3d(1.068871,1.282645,1.068871), 0.0001));
}



