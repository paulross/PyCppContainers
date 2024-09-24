#!/bin/bash
#
# Builds cPyCppContainers for distribution
# Ref: https://packaging.python.org/tutorials/packaging-projects/
#
# Other references:
# https://kvz.io/bash-best-practices.html
# https://bertvv.github.io/cheat-sheets/Bash.html

set -o errexit  # abort on nonzero exitstatus
set -o nounset  # abort on unbound variable
set -o pipefail # don't hide errors within pipes

# https://devguide.python.org/versions/
PYTHON_VERSIONS=('3.8' '3.9' '3.10' '3.11' '3.12' '3.13')
#PYTHON_VERSIONS=('3.10' '3.11' '3.12' '3.13')
PYTHON_VENV_ROOT="${HOME}/pyenvs"
# Used for venvs
PROJECT_NAME="cPyCppContainers"
CPP_EXECUTABLE="PythonCppHomogeneousContainers"


#printf "%-8s %8s %10s %10s %12s\n" "Ext" "Files" "Lines" "Words" "Bytes"

build_cpp() {
  echo "---> C++ clean debug"
  cmake --build cmake-build-debug --target clean -- -j 6
  echo "---> C++ build debug"
  cmake --build cmake-build-debug --target ${CPP_EXECUTABLE} -- -j 6
  echo "---> C++ clean release"
  cmake --build cmake-build-release --target clean -- -j 6
  echo "---> C++ build release"
  cmake --build cmake-build-release --target ${CPP_EXECUTABLE} -- -j 6
}

run_cpp_tests() {
  echo "---> C++ debug tests"
  cmake-build-debug/${CPP_EXECUTABLE}
  echo "---> C++ release tests"
  cmake-build-release/${CPP_EXECUTABLE}
}

deactivate_virtual_environment() {
  # https://stackoverflow.com/questions/42997258/virtualenv-activate-script-wont-run-in-bash-script-with-set-euo
  set +u
  if command -v deactivate &>/dev/null; then
    deactivate
  fi
  set -u
}

create_virtual_environments() {
  deactivate_virtual_environment
  for version in ${PYTHON_VERSIONS[*]}; do
    echo "---> Create virtual environment for Python version ${version}"
    venv_path="${PYTHON_VENV_ROOT}/${PROJECT_NAME}_${version}"
    if [ ! -d "${venv_path}" ]; then
      # Control will enter here if directory not exists.
      echo "---> Creating virtual environment at: ${venv_path}"
      "python${version}" -m venv "${venv_path}"
    fi
  done
}

remove_virtual_environments() {
  deactivate_virtual_environment
  for version in ${PYTHON_VERSIONS[*]}; do
    echo "---> For Python version ${version}"
    venv_path="${PYTHON_VENV_ROOT}/${PROJECT_NAME}_${version}"
    if [ -d "${venv_path}" ]; then
      # Control will enter here if directory exists.
      echo "---> Removing virtual environment at: ${venv_path}"
      #rm --recursive --force -- "${venv_path}"
      rm -rf -- "${venv_path}"
    fi
  done
}

create_bdist_wheel() {
  echo "---> Creating bdist_wheel for all versions..."
  for version in ${PYTHON_VERSIONS[*]}; do
    echo "---> For Python version ${version}"
    deactivate_virtual_environment
    venv_path="${PYTHON_VENV_ROOT}/${PROJECT_NAME}_${version}"
    if [ ! -d "${venv_path}" ]; then
      # Control will enter here if directory doesn't exist.
      echo "---> Creating virtual environment at: ${venv_path}"
      "python${version}" -m venv "${venv_path}"
    fi
    # https://stackoverflow.com/questions/42997258/virtualenv-activate-script-wont-run-in-bash-script-with-set-euo
    set +u
    source "${venv_path}/bin/activate"
    set -u
    echo "---> Python version:"
    python -VV
    echo "---> Installing everything via pip:"
    pip install -U pip setuptools wheel
    pip install -r requirements-dev.txt
    echo "---> Result of pip install:"
    pip list
    echo "---> Running python setup.py develop:"
    MACOSX_DEPLOYMENT_TARGET=10.9 CC=clang CXX=clang++ python setup.py develop
    echo "---> Running tests:"
    # Fail fast with -x
    pytest tests -x
    # Run all tests (slow).
    pytest tests -vs --runslow --pymemtrace
    echo "---> Running setup for bdist_wheel:"
    python setup.py bdist_wheel
  done
}

create_sdist() {
  echo "---> Running setup for sdist:"
  python setup.py sdist
}

report_all_versions_and_setups() {
  echo "---> Reporting all versions..."
  for version in ${PYTHON_VERSIONS[*]}; do
    echo "---> For Python version ${version}"
    deactivate_virtual_environment
    venv_path="${PYTHON_VENV_ROOT}/${PROJECT_NAME}_${version}"
    if [ ! -d "${venv_path}" ]; then
      # Control will enter here if directory doesn't exist.
      echo "---> Creating virtual environment at: ${venv_path}"
      "python${version}" -m venv "${venv_path}"
    fi
      echo "---> Virtual environment at: ${venv_path}"
    # https://stackoverflow.com/questions/42997258/virtualenv-activate-script-wont-run-in-bash-script-with-set-euo
    set +u
    source "${venv_path}/bin/activate"
    set -u
    echo "---> Python version:"
    python -VV
    echo "---> pip list:"
    pip list
  done
}

show_results_of_dist() {
  echo "---> dist/:"
  ls -l "dist"
  echo "---> twine check dist/*:"
  twine check dist/*
  # Test from Test PyPi
  # pip install -i https://test.pypi.org/simple/orderedstructs
  echo "---> Ready for upload to test PyPi:"
  echo "---> pip install twine"
  echo "---> twine upload --repository testpypi dist/*"
  echo "---> Or PyPi:"
  echo "---> twine upload dist/*"
}

echo "===> Clean and build C++ code"
build_cpp
echo "===> Running C++ tests"
run_cpp_tests
echo "===> Removing build/ and dist/"
#rm --recursive --force -- "build" "dist"
rm -rf -- "build" "dist"
remove_virtual_environments
create_virtual_environments
create_bdist_wheel
create_sdist
report_all_versions_and_setups
show_results_of_dist
#pip install twine
echo "===> All done"
