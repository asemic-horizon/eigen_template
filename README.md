# Eigen PyPI Template

This is a minimal Python package using C++ and [Eigen](https://eigen.tuxfamily.org/) for matrix operations, exposed via [pybind11](https://github.com/pybind/pybind11). The default function adds two NumPy arrays using Eigen.

## Usage

```bash
pip install .
```

Then in Python:

```python
import numpy as np
from eigen_pypi_template import add_matrices

A = np.eye(2)
B = np.ones((2, 2))
print(add_matrices(A, B))
```

## Installing Eigen

You have two options:

### (1) System-wide install (Linux/macOS)

```bash
sudo apt install libeigen3-dev  # Debian/Ubuntu
# OR on macOS (with Homebrew)
brew install eigen
```

Make sure Eigen headers are installed under `/usr/include/eigen3` or `/opt/homebrew/include/eigen3`.

### (2) Vendored Eigen (portable)

Clone Eigen into the `vendor/eigen/` directory:

```bash
mkdir -p vendor
git clone --depth 1 https://gitlab.com/libeigen/eigen.git vendor/eigen
```

You don’t need to build anything—Eigen is header-only.

Your structure should now look like:

```
vendor/
└── eigen/
    └── Eigen/
        └── Core, Dense, ...
```

The build system will detect this automatically.
