# OpenVSIP Fork Info

This is a WIP fork of the [OpenVSIP](https://github.com/sefanseefeld/openvsip) repository for use on macOS 26.3 (Tahoe).
It works with GCC and Clang C++ 17 compilers and uses Apple's Accelerate framework for LAPACK and CBLAS routines. It
builds with the following packages:

* OpenMPI v5.0.9
* FFTW v3.3.10
* LAPACK from Apple's Accelerate framework

### Changes

* At the time of the fork, the original had outdated `config.guess` and `config.sub` files which caused failures on macOS. This
repo has up-to-date version that were obtained by using `libtool`. A better approach might be to depend on `libtool`
being run perhaps from within the `autogen.sh` script that currently generates the `configure` script.
* The `configure.ac` file disables checking for exceptions and hardcodes them enabled.
* There are crude custom test scripts to overcome the lack of a working QMTest setup (requires Python 2 and perhaps Windows).
* Various code fixes to handle compiler errors due to the absence of previously-deprecated STL classes/functions.

### To Use

1. Clone this repo: `git clone https://github.com/bradhowes/openvsip`
2. Enter repo directory: `cd openvsip`
3. Create configure script: `./autogen.sh`
4. Create `objdir` and enter it: `mkdir objdir && cd objdir`
5. Run `configure`: `../configure --with-fftw-prefix=/opt/homebrew --with-lapack=apple --prefix=/opt/homebrew`
6. Build: `make install`
7. Test (WIP): `cd tests; bash ../../tests/brh_tests`

> Be aware: there are some test failures including crashes, but a vast majority run OK, as does some old code I have
that uses the vsip library.

## Welcome to OpenVSIP

[![Build Status](https://travis-ci.org/stefanseefeld/openvsip.svg)](https://travis-ci.org/stefanseefeld/openvsip)

OpenVSIP is a high-quality implementation of the 
[VSIPL++ standard](http://portals.omg.org/hpec/content/specifications), originally
developed by CodeSourcery as Sourcery VSIPL++.

This library is free software. For license information please refer to the file [LICENSE](LICENSE).

For a quick overview of the project please refer to the [Getting Started](doc/getting-started.md) document.
