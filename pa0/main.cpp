#include <Eigen/Core>
#include <cmath>
#include <iostream>

int main() {
    Eigen::Vector3d P;
    P << 2, 1, 1;

    const double sqrt2_2 = sqrt(2) / 2;

    Eigen::Matrix3d R45;
    R45 << sqrt2_2, -sqrt2_2, 0, sqrt2_2, sqrt2_2, 0, 0, 0, 1;

    Eigen::Matrix3d T12;
    T12 << 1, 0, 1, 0, 1, 2, 0, 0, 1;

    auto P_prime = T12 * R45 * P;

    std::cout << P_prime << std::endl;

    return 0;
}
