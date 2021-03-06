//
// Copyright (c) 2005, 2006 by CodeSourcery
// Copyright (c) 2013 Stefan Seefeld
// All rights reserved.
//
// This file is part of OpenVSIP. It is made available under the
// license contained in the accompanying LICENSE.GPL file.

/// Description
///   Tests for math reductions, floating-point types.

#include "reductions.hpp"

using namespace ovxx;

void
simple_tests()
{
  Vector<float> vec(4);

  vec(0) = 0.;
  vec(1) = 1.;
  vec(2) = 2.;
  vec(3) = 3.;

  test_assert(equal(sumval(vec),    6.0f));
  test_assert(equal(meanval(vec),   1.5f));
  test_assert(equal(sumsqval(vec), 14.0f));
  test_assert(equal(meansqval(vec), 3.5f));

  test_assert(equal(sumval(vec+vec), 12.0f));

  Matrix<double> mat(2, 2);

  mat(0, 0) = 1.;
  mat(0, 1) = 2.;
  mat(1, 0) = 3.;
  mat(1, 1) = 4.;

  test_assert(equal(sumval(mat),   10.0));
  test_assert(equal(meanval(mat),   2.5));
  test_assert(equal(sumsqval(mat), 30.0));
  test_assert(equal(meansqval(mat), 7.5));

  Tensor<float> ten(2, 1, 2);

  ten(0, 0, 0) = 2.;
  ten(0, 0, 1) = 3.;
  ten(1, 0, 0) = 4.;
  ten(1, 0, 1) = 5.;

  test_assert(equal(sumval(ten),    14.0f));
  test_assert(equal(meanval(ten),    3.5f));
  test_assert(equal(sumsqval(ten),  54.0f));
  test_assert(equal(meansqval(ten), 13.5f));

  Vector<complex<float> > cvec(2);

  cvec(0) = complex<float>(3.f,  4.f); // -7 + 24i
  cvec(1) = complex<float>(3.f, -4.f); // -7 - 24i

  test_assert(equal(sumval(cvec),    complex<float>(6.0f, 0.0f)));
  // test_assert(equal(meanval(cvec), complex<float>(3.f, 0.f)));
  test_assert(equal(sumsqval(cvec),  complex<float>(-14.0f, 0.0f)));
  test_assert(equal(meansqval(cvec), 25.0f));


  Vector<bool> bvec(4);

  bvec(0) = true;
  bvec(1) = true;
  bvec(2) = false;
  bvec(3) = true;

  test_assert(equal(sumval(bvec), static_cast<length_type>(3)));

  // Simple test for alternate form.
  Vector<unsigned short> uvec(4);

  uvec(0) = 65535;
  uvec(1) = 1;
  uvec(2) = 2;
  uvec(3) = 3;

  // TODO: implement missing API
#if 0
  typedef unsigned long W;

  test_assert(equal(sumval(uvec, W()), W(65541)));
  test_assert(equal(meanval(uvec, W()), W(65541/4)));
  uvec(0) = 256;
  test_assert(equal(sumsqval(uvec, W()), W(65550)));
  W w = meansqval(uvec, W());
  if( !equal(w, W(65550/4)) )
    std::cout << "w=" << w << ", expected=" << W(65550/4) << "\n";
  test_assert(equal(w, W(65550/4)));
#endif
}



int
main(int argc, char** argv)
{
  vsipl init(argc, argv);

  simple_tests();
#if OVXX_PARALLEL
  par_cover_sumval<float, Replicated_map<1> >();
  par_cover_sumval<float, Map<Block_dist> >();
#endif
  cover_sumval<float>();
  cover_sumval<complex<float> >();

  cover_sumsqval<float>();
  cover_sumsqval<complex<float> >();

  cover_meanval<float>();
  cover_meanval<complex<float> >();

  cover_meansqval<float>();
  cover_meansqval<complex<float> >();

#if VSIP_IMPL_TEST_DOUBLE
  cover_sumval<double>();
  cover_sumval<complex<double> >();

  cover_sumsqval<double>();
  cover_sumsqval<complex<double> >();

  cover_meanval<double>();

  cover_meansqval<double>();
  cover_meansqval<complex<double> >();
#endif
}
