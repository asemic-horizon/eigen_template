#include "utils.hpp"
#include <omp.h>

Eigen::MatrixXd columnpairwise_apply(
    const Eigen::MatrixXd& X,
    const std::function<double(const Eigen::VectorXd&, const Eigen::VectorXd&)>& f
) {
    int n = X.cols();
    Eigen::MatrixXd result(n, n);

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= n; ++j) {
            double val = f(X.col(i), X.col(j));
            result(i, j) = val;
        }
    }

    return result;
}

Eigen::MatrixXd columnpairwise_symmetric_apply(
    const Eigen::MatrixXd& X,
    const std::function<double(const Eigen::VectorXd&, const Eigen::VectorXd&)>& f
) {
    int n = X.cols();
    Eigen::MatrixXd result(n, n);

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            double val = f(X.col(i), X.col(j));
            result(i, j) = val;
            result(j, i) = val; 
        }
    }


    return result;
}
