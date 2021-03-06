//
// Copyright (c) 2010 by CodeSourcery
// Copyright (c) 2013 Stefan Seefeld
// All rights reserved.
//
// This file is part of OpenVSIP. It is made available under the
// license contained in the accompanying LICENSE.GPL file.

/// Description
///   VSIPL++ Library: Matrix product benchmark base class

#ifndef mprod_hpp_
#define mprod_hpp_

#include <vsip/support.hpp>

template <typename T>
struct t_mprod_base : Benchmark_base
{
  static vsip::length_type const Dec = 1;

  float ops_total(vsip::length_type M, vsip::length_type N, vsip::length_type P)
  {
    float ops = M * N * P * 
      (ovxx::ops_count::traits<T>::mul + ovxx::ops_count::traits<T>::add);

    return ops;
  }

  float riob_total(vsip::length_type M, vsip::length_type N, vsip::length_type P)
    { return ((M * N) + (N * P)) * sizeof(T); }

  float wiob_total(vsip::length_type M, vsip::length_type P)
    { return M * P * sizeof(T); }

  float mem_total(vsip::length_type M, vsip::length_type N, vsip::length_type P)
    { return riob_total(M, N, P) + wiob_total(M, P); } 
};

#endif
