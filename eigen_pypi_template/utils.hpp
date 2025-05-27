#pragma once

#include <Eigen/Dense>
#include <functional>

enum class Symmetry {
    None,
    Symmetric,
    SkewSymmetric
};

Eigen::MatrixXd columnpairwise_apply(
    const Eigen::MatrixXd& X,
    const std::function<double(const Eigen::VectorXd&, const Eigen::VectorXd&)>& f
);

Eigen::MatrixXd columnpairwise_symmetric_apply(
    const Eigen::MatrixXd& X,
    const std::function<double(const Eigen::VectorXd&, const Eigen::VectorXd&)>& f
);



