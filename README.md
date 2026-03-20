# OpenVSIP Fork Info

This is a WIP fork of the [OpenVSIP](https://github.com/sefanseefeld/openvsip) repository for use on macOS 26.3 (Tahoe).
It works with GCC and Clang C++ 17 compilers and uses Apple's Accelerate framework for LAPACK and CBLAS routines.

At the time of the fork, the original had outdated `config.guess` and `config.sub` which caused failures on macOS. This
repo has up-to-date values that were obtained from using `libtool` -- a better approach might be to depend on `libtool`
being run perhaps from within the `autogen.sh` script that currently generates the `configure` script. There are also
some custom test scripts to overcome the lack of a working QMTest setup (requires Python 2 and perhaps Windows).

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
