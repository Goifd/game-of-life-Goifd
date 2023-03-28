#include <Eigen/Core>

class Particle {
    public:
        Particle(double in_mass, Eigen::Vector3d pos, Eigen::Vector3d vel);
        double getMass() const;
        // return by reference as these values are often accessed during simulation process
        Eigen::Vector3d& getPosition();
        Eigen::Vector3d& getVelocity();
        Eigen::Vector3d& getAcceleration();
        void addAcceleration(Eigen::Vector3d a);
        void update(double dt);
        void print();

    private:
        const double mass;
        Eigen::Vector3d position;
        Eigen::Vector3d velocity;
        Eigen::Vector3d acceleration;
};