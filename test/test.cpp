#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "particle.hpp"
#include "system.hpp"
#include <Eigen/Core>

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
        std::cout << i << std::endl;
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
        std::cout << i << std::endl;
        p4.addAcceleration(-p4.getPosition());
        p4.update(dt);
    }
    REQUIRE(p4.getPosition().isApprox(Eigen::Vector3d(1,0,0), 0.1));
}

TEST_CASE("System initialization works correctly", "[system_init]"){

}