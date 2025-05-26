from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import sys
import os
import setuptools

class get_pybind_include:
    def __str__(self):
        import pybind11
        return pybind11.get_include()

vendored_eigen = os.path.join("vendor", "eigen")
include_dirs = [get_pybind_include()]

if os.path.exists(vendored_eigen):
    include_dirs.append(vendored_eigen)
else:
    include_dirs.append("/usr/include/eigen3")

ext_modules = [
    Extension(
        'eigen_pypi_template.eigen_pypi_template',
        ['eigen_pypi_template/core.cpp'],
        include_dirs=include_dirs,
        language='c++',
    ),
]

setup(
    name='eigen_pypi_template',
    version='0.1.0',
    author='Your Name',
    description='Minimal Eigen/pybind11 example as PyPI package',
    packages=['eigen_pypi_template'],
    ext_modules=ext_modules,
    zip_safe=False,
)
