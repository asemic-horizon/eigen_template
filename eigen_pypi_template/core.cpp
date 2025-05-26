#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <Eigen/Dense>

Eigen::MatrixXd add_matrices(const Eigen::MatrixXd& A, const Eigen::MatrixXd& B) {
    return A + B;
}

PYBIND11_MODULE(eigen_pypi_template, m) {
    m.def("add_matrices", &add_matrices, "Add two matrices");
}
