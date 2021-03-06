//
// Copyright (c) 2005, 2006 by CodeSourcery
// Copyright (c) 2013 Stefan Seefeld
// All rights reserved.
//
// This file is part of OpenVSIP. It is made available under the
// license contained in the accompanying LICENSE.GPL file.

#include <iostream>

#include <vsip/initfin.hpp>
#include <vsip/support.hpp>
#include <vsip/matrix.hpp>
#include <vsip/tensor.hpp>
#include <vsip/math.hpp>
#include <test/ref/matvec.hpp>
#include <test.hpp>
#include "prod.hpp"

using namespace ovxx;

template <typename T0,
	  typename T1>
void
test_prod_mv(length_type m, length_type n)
{
  typedef typename Promotion<T0, T1>::type return_type;
  typedef typename scalar_of<return_type>::type scalar_type;

  Matrix<T0> a(m, n, T0());
  Vector<T1> b1(n, T1());
  Vector<T1> b2(m, T1());

  test::randm(a);
  test::randv(b1);
  test::randv(b2);

#if VERBOSE
  cout << "[" << m << "x" << n << "]"  << endl;
  cout << "a     =\n" << a;
  cout << "b1    =\n" << b1;
  cout << "b2    =\n" << b2;
#endif

  Vector<return_type> r1(m);
  Vector<return_type> chk1(m);
  Vector<scalar_type> gauge1(m);

  r1 = prod( a, b1 );
  chk1 = test::ref::prod( a, b1 );
  gauge1 = test::ref::prod( mag(a), mag(b1) );

  for (index_type i=0; i<gauge1.size(0); ++i)
    if (!(gauge1(i) > scalar_type()))
      gauge1(i) = scalar_type(1);

  check_prod( r1, chk1, gauge1 );

  Vector<return_type> r2(n);
  Vector<return_type> chk2(n);
  Vector<scalar_type> gauge2(n);

  r2 = prod( trans(a), b2 );
  chk2 = test::ref::prod( trans(a), b2 );
  gauge2 = test::ref::prod( mag(trans(a)), mag(b2) );

  for (index_type i=0; i<gauge2.size(0); ++i)
    if (!(gauge2(i) > scalar_type()))
      gauge2(i) = scalar_type(1);

  check_prod( r2, chk2, gauge2 );
}


template <typename T0,
	  typename T1>
void
test_prod_vm(length_type m, length_type n)
{
  typedef typename Promotion<T0, T1>::type return_type;
  typedef typename scalar_of<return_type>::type scalar_type;

  Vector<T1> a1(m, T1());
  Vector<T1> a2(n, T1());
  Matrix<T0> b(m, n, T0());

  test::randv(a1);
  test::randv(a2);
  test::randm(b);

#if VERBOSE
  cout << "[" << m << "x" << n << "]"  << endl;
  cout << "a1    =\n" << a1;
  cout << "a2    =\n" << a2;
  cout << "b     =\n" << b;
#endif

  Vector<return_type> r1(n);
  Vector<return_type> chk1(n);
  Vector<scalar_type> gauge1(n);

  r1 = prod( a1, b );
  chk1 = test::ref::prod( a1, b );
  gauge1 = test::ref::prod( mag(a1), mag(b) );

  for (index_type i=0; i<gauge1.size(0); ++i)
    if (!(gauge1(i) > scalar_type()))
      gauge1(i) = scalar_type(1);

  check_prod( r1, chk1, gauge1 );

  Vector<return_type> r2(m);
  Vector<return_type> chk2(m);
  Vector<scalar_type> gauge2(m);

  r2 = prod( a2, trans(b) );
  chk2 = test::ref::prod( a2, trans(b) );
  gauge2 = test::ref::prod( mag(a2), mag(trans(b)) );

  for (index_type i=0; i<gauge2.size(0); ++i)
    if (!(gauge2(i) > scalar_type()))
      gauge2(i) = scalar_type(1);

  check_prod( r2, chk2, gauge2 );
}


/// Test matrix-matrix products using sub-views

template <typename T>
void
test_mv_prod_subview( const length_type m, 
                      const length_type n )
{
  typedef typename Matrix<T>::subview_type matrix_subview_type;
  typedef typename Vector<T>::subview_type vector_subview_type;
  typedef typename scalar_of<T>::type scalar_type;

  {
    // non-unit strides - non-dense rows/vectors, dense columns
    Matrix<T> aa(m*2, n, T());
    Vector<T> bb(n*3, T());
    matrix_subview_type a = aa(Domain<2>(
                                Domain<1>(0, 2, m), Domain<1>(0, 1, n)));
    vector_subview_type b = bb(Domain<1>(0, 3, n));

    test::randm(a);
    test::randv(b);

    Vector<T> res(m);
    Vector<T> chk(m);
    Vector<scalar_type> gauge(m);

    res = prod( a, b );
    chk = test::ref::prod( a, b );
    gauge = test::ref::prod(mag(a), mag(b));

    for (index_type i=0; i<gauge.size(0); ++i)
      if (!(gauge(i) > scalar_type()))
        gauge(i) = scalar_type(1);

    check_prod( res, chk, gauge );
  }

  {
    // non-unit strides - dense rows, non-dense columns/vectors
    Matrix<T> aa(m*2, n, T());
    Vector<T> bb(m*3, T());
    matrix_subview_type a = aa(Domain<2>(
                                Domain<1>(0, 2, m), Domain<1>(0, 1, n)));
    vector_subview_type b = bb(Domain<1>(0, 3, m));

    test::randm(a);
    test::randv(b);

    Vector<T> res(n);
    Vector<T> chk(n);
    Vector<scalar_type> gauge(n);

    res = prod( trans(a), b );
    chk = test::ref::prod( trans(a), b );
    gauge = test::ref::prod(mag(trans(a)), mag(b));

    for (index_type i=0; i<gauge.size(0); ++i)
      if (!(gauge(i) > scalar_type()))
        gauge(i) = scalar_type(1);

    check_prod( res, chk, gauge );
  }
}


/// Test matrix-matrix products using sub-views

template <typename T>
void
test_vm_prod_subview( const length_type m, 
                      const length_type n )
{
  typedef typename Matrix<T>::subview_type matrix_subview_type;
  typedef typename Vector<T>::subview_type vector_subview_type;
  typedef typename scalar_of<T>::type scalar_type;

  {
    // non-unit strides - non-dense rows/vectors, dense columns
    Vector<T> aa(m*3, T());
    Matrix<T> bb(m*2, n, T());
    vector_subview_type a = aa(Domain<1>(0, 3, m));
    matrix_subview_type b = bb(Domain<2>(
                                Domain<1>(0, 2, m), Domain<1>(0, 1, n)));

    test::randv(a);
    test::randm(b);

    Vector<T> res(n);
    Vector<T> chk(n);
    Vector<scalar_type> gauge(n);

    res = prod( a, b );
    chk = test::ref::prod( a, b );
    gauge = test::ref::prod(mag(a), mag(b));

    for (index_type i=0; i<gauge.size(0); ++i)
      if (!(gauge(i) > scalar_type()))
        gauge(i) = scalar_type(1);

    check_prod( res, chk, gauge );
  }

  {
    // non-unit strides - dense rows, non-dense columns/vectors
    Vector<T> aa(n*3, T());
    Matrix<T> bb(m*2, n, T());
    vector_subview_type a = aa(Domain<1>(0, 3, n));
    matrix_subview_type b = bb(Domain<2>(
                                Domain<1>(0, 2, m), Domain<1>(0, 1, n)));

    test::randv(a);
    test::randm(b);

    Vector<T> res(m);
    Vector<T> chk(m);
    Vector<scalar_type> gauge(m);

    res = prod( a, trans(b) );
    chk = test::ref::prod( a, trans(b) );
    gauge = test::ref::prod(mag(a), mag(trans(b)));

    for (index_type i=0; i<gauge.size(0); ++i)
      if (!(gauge(i) > scalar_type()))
        gauge(i) = scalar_type(1);

    check_prod( res, chk, gauge );
  }
}




template <typename T0,
	  typename T1>
void
prod_cases()
{
  test_prod_mv<T0, T1>(5, 7);
  test_prod_vm<T0, T1>(5, 7);
}


template <typename T>
void
prod_subview_cases()
{
  test_mv_prod_subview<T>(5, 7);
  test_vm_prod_subview<T>(5, 7);
}

int
main(int argc, char** argv)
{
  vsipl init(argc, argv);

  test::precision<float>::init();
  test::precision<double>::init();


  prod_cases<float,  float>();

  prod_cases<complex<float>, complex<float> >();
  prod_cases<float,          complex<float> >();
  prod_cases<complex<float>, float          >();

  prod_subview_cases<float>();
  prod_subview_cases<complex<float> >();

#if VSIP_IMPL_TEST_DOUBLE
  prod_cases<double, double>();
  prod_cases<float,  double>();
  prod_cases<double, float>();
#endif
}
