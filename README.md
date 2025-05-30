# Eigen PyPI Template

This is a minimal Python package using C++ and [Eigen](https://eigen.tuxfamily.org/) for matrix operations, exposed via [pybind11](https://github.com/pybind/pybind11). You can think of Eigen as a matrix-oriented DSL that's hosted in C++ but saves you the heartache of dealing with manual memory management. 

When should you use this type of solution?

* Problems are difficult or impossible to express in terms of NumPy/Jax/Pytorch etc. vectorized primitives
* Data is large enough to make naive Python solutions impractical both in terms of memory and time.
* Loop-oriented code is close to self-documenting.
* There are some easy parallelization wins (think of computing correlation matrices) that you can hang on loops using OpenMP

When shouldn't you use this?

* Vibecoding. Even with Eigen, C++ is still dangerous enough to be dangerous if you don't know what you're doing, and error messages may not be traceable to deep causes.
* Your problem space is a better fit for out-of-core map/reduce-y solutions.
* Your problems are massively parallel enough that you'd benefit from using the GPU
* This README and its examples are not very clear to you.  

## Usage in Python

```bash
pip install .
```


As a placeholder, a function is included that adds two NumPy arrays using Eigen:

```python
import numpy as np
from eigen_pypi_template import add_matrices

A = np.eye(2)
B = np.ones((2, 2))
print(add_matrices(A, B))
```

## Writing C++/Eigen functions

Eigen is [quite comprehensively documented](https://eigen.tuxfamily.org/dox/), but for some things reading some starter codes (or asking your AI chatbot) may be enough. `add_matrices` is simply

```cpp
Eigen::MatrixXd add_matrices(const Eigen::MatrixXd& A, 
                             const Eigen::MatrixXd& B) {
    return A + B;
}
```

Included in this project template are some OpenMP-enabled utility functions to populate matrices from functions of matrix columns. For example, if you define the correlation coefficient as

```cpp
double corr_coeff(const Eigen::VectorXd& x, const Eigen::VectorXd& y) {
    double xy = x.dot(y);
    double xx = x.dot(x);
    double yy = y.dot(y);
    return xy / std::sqrt(xx * yy);
}
```

a correlation matrix may be obtained by simply saying

```cpp
Eigen::MatrixXd correlation_matrix(const Eigen::MatrixXd& X) {
    return columnpairwise_apply(X, corr_coeff);
}
```

or, to exploit the fact that correlation is symmetric,

```cpp
Eigen::MatrixXd correlation_matrix(const Eigen::MatrixXd& X) {
    return columnpairwise_symmetric_apply(X, corr_coeff);
}
```

(You should explore [core.cpp](eigen_pypi_template/core.cpp) to see how these utilities are defined.)

## Installing Eigen

You have two options:

### (1) System-wide install

This is the best option if your package is for local use only, or if you're using something like a Dockerfile that automates this.

```bash
sudo apt install libeigen3-dev  # Debian/Ubuntu-like
```

Make sure Eigen headers are installed under `/usr/include/eigen3` or `/opt/homebrew/include/eigen3`.

### (2) Vendored Eigen

This is the best option if you want your package to be `pip install`able anywhere. Since Eigen is header-only, there's no building step (we just copy the files into our project)

Clone Eigen into the `vendor/eigen/` directory:

```bash
mkdir -p vendor
git clone --depth 1 https://gitlab.com/libeigen/eigen.git vendor/eigen
```

It's probably a good idea to acknowledge Eigen in your `LICENSE` file, e.g.

```This project bundles the Eigen C++ template library (MPL2.0). See https://eigen.tuxfamily.org for details.```