/* Copyright (c) 2010 by CodeSourcery.  All rights reserved. */

/// VSIPL++ Library: QR solver example.
///
/// This example illustrates how to use the VSIPL++ QR Solver facility.
///
/// Given a matrix equation A X = B, solve for X.  A is
/// n-by-n; B and X are n-by-p.  The "QR" method first
/// decomposes A into an n-by-n othoganal matrix Q and an
/// n-by-n upper triangular matrix R, such that A = Q R.
/// That is, transpose(Q) Q = I, where I is the identity
/// matrix; R has only zeroes below the diagonal.
///
/// To solve the original equation, which is now Q R X = B,
/// first solve the equation Q Y = B for Y.  Second, solve
/// the equation R X = Y for X.
///
/// The QR method is efficient when solving with several B
/// matrices and one A.  That is, A is decomposed only once.
///
/// The expected result is
///   x = 
///     0:  13.3333
///     1:  -6.33333
///     2:  -9.22222

#include <iostream>
#include <vsip/initfin.hpp>
#include <vsip/support.hpp>
#include <vsip/signal.hpp>
#include <vsip/math.hpp>
#include <vsip/solvers.hpp>
#include <vsip_csl/output.hpp>


using namespace vsip;


int
main(int argc, char **argv)
{
  vsipl init(argc, argv);

  length_type m =  3;   // Rows in A.
  length_type n =  3;	// Cols in A; rows in b.
  length_type p =  1;	// Cols in b.

  // Create some inputs, a 3x3 matrix and a 3x1 matrix.
  Matrix<float> A(m, n);
  Matrix<float> b(n, p);

  // Initialize the inputs.
  A(0, 0) =  1; A(0, 1) = -2; A(0, 2) =  3;
  A(1, 0) =  4; A(1, 1) =  0; A(1, 2) =  6;
  A(2, 0) =  2; A(2, 1) = -1; A(2, 2) =  3;

  b(0, 0) =  1; b(1, 0) = -2; b(2, 0) = -1;
  
  // Create a 3x1 matrix for output.
  Matrix<float> x(n, p);

  // Build the solver.
  qrd<float, by_reference> qr(m, n, qrd_nosaveq);

  // Factor A.
  qr.decompose(A);

  // Solve A x = b.
  qr.covsol(b, x);

  // Display the results.
  std::cout
    << std::endl
    << "QR Solver example" << std::endl
    << "-----------------" << std::endl
    << "A = " << std::endl << A << std::endl
    << "b = " << std::endl << b << std::endl
    << "x = " << std::endl << x << std::endl;

  return 0;
}
