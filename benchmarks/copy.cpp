//
// Copyright (c) 2005, 2006 by CodeSourcery
// Copyright (c) 2013 Stefan Seefeld
// All rights reserved.
//
// This file is part of OpenVSIP. It is made available under the
// license contained in the accompanying LICENSE.GPL file.

/// Description
///   Benchmark for view copy.

#include <iostream>

#include <vsip/initfin.hpp>
#include <vsip/support.hpp>
#include <vsip/math.hpp>
#include <vsip/map.hpp>
#include <vsip/parallel.hpp>
#include "benchmark.hpp"
#include "create_map.hpp"
#include <cstring>

using namespace vsip;

struct Impl_assign;				// normal assignment
struct Impl_sa;					// Assignment object
struct Impl_memcpy;				// use memcpy
template <typename Impl> struct Impl_pa;	// Assignment<Impl> object
template <typename Impl> struct Impl_pa_na;	//  " " (not amortized)

template <typename T,
	  typename SrcMapT,
	  typename DstMapT,
	  typename ImplTag>
struct t_vcopy;



/***********************************************************************
  Vector copy - normal assignment
***********************************************************************/

template <typename T,
	  typename SrcMapT,
	  typename DstMapT>
struct t_vcopy<T, SrcMapT, DstMapT, Impl_assign> : Benchmark_base
{
  typedef Dense<1, T, row1_type, SrcMapT> src_block_t;
  typedef Dense<1, T, row1_type, DstMapT> dst_block_t;
  
  char const* what() { return "t_vcopy<..., Impl_assign>"; }
  int ops_per_point(length_type)  { return 1; }
  int riob_per_point(length_type) { return 1*sizeof(T); }
  int wiob_per_point(length_type) { return 1*sizeof(T); }
  int mem_per_point(length_type)  { return 1*sizeof(T); }

  void operator()(length_type size, length_type loop, float& time)
  {
    Vector<T, src_block_t>   A(size, T(), src_map_);
    Vector<T, dst_block_t>   Z(size,      dst_map_);

    for (index_type i=0; i<A.local().size(); ++i)
    {
      index_type g_i = global_from_local_index(A, 0, i);
      A.local().put(i, T(g_i));
    }
    
    if (pre_sync_)
      barrier();
    
    timer t1;
    for (index_type l=0; l<loop; ++l)
      Z = A;
    time = t1.elapsed();

    for (index_type i=0; i<Z.local().size(); ++i)
    {
      index_type g_i = global_from_local_index(Z, 0, i);
      if (!equal(Z.local().get(i), T(g_i)))
      {
	std::cout << "ERROR: at location " << i << std::endl
		  << "       expected: " << T(g_i) << std::endl
		  << "       got     : " << Z.local().get(i) << std::endl;
      }
      test_assert(equal(Z.local().get(i), T(g_i)));
    }
  }

  void diag()
  {
    using namespace ovxx;
    length_type const size = 256;

    Vector<T, src_block_t>   A(size, T(), src_map_);
    Vector<T, dst_block_t>   Z(size,      dst_map_);

    std::cout << assignment::diagnostics(Z, A) << std::endl;
  }

  t_vcopy(SrcMapT src_map, DstMapT dst_map, bool pre_sync)
    : src_map_(src_map), dst_map_(dst_map), pre_sync_(pre_sync)
  {}

  // Member data.
  SrcMapT	src_map_;
  DstMapT	dst_map_;
  bool          pre_sync_;
};



/***********************************************************************
  Vector copy - parallel::Assignment ImplTag (setup amortized to zero)
***********************************************************************/

template <typename T,
	  typename SrcMapT,
	  typename DstMapT,
	  typename ParAssignImpl>
struct t_vcopy<T, SrcMapT, DstMapT, Impl_pa<ParAssignImpl> > : Benchmark_base
{
  char const* what() { return "t_vcopy<..., Impl_pa>"; }
  int ops_per_point(length_type)  { return 1; }
  int riob_per_point(length_type) { return 1*sizeof(T); }
  int wiob_per_point(length_type) { return 1*sizeof(T); }
  int mem_per_point(length_type)  { return 1*sizeof(T); }

  void operator()(length_type size, length_type loop, float& time)
  {
    dimension_type const dim = 1;
    typedef Dense<1, T, row1_type, SrcMapT> src_block_t;
    typedef Dense<1, T, row1_type, DstMapT> dst_block_t;
    Vector<T, src_block_t>   A(size, T(), src_map_);
    Vector<T, dst_block_t>   Z(size,      dst_map_);

    for (index_type i=0; i<A.local().size(); ++i)
    {
      index_type g_i = global_from_local_index(A, 0, i);
      A.local().put(i, T(g_i));
    }
    
    ovxx::parallel::Assignment<dim, dst_block_t, src_block_t, ParAssignImpl>
      cpa(Z, A);

    if (pre_sync_)
      barrier();

    timer t1;
    for (index_type l=0; l<loop; ++l)
    {
      cpa();
    }
    time = t1.elapsed();
    
    for (index_type i=0; i<Z.local().size(); ++i)
    {
      index_type g_i = global_from_local_index(Z, 0, i);
      test_assert(equal(Z.local().get(i), T(g_i)));
    }
  }

  t_vcopy(SrcMapT src_map, DstMapT dst_map, bool pre_sync)
    : src_map_(src_map), dst_map_(dst_map), pre_sync_(pre_sync)
  {}

  // Member data.
  SrcMapT	src_map_;
  DstMapT	dst_map_;
  bool          pre_sync_;
};



/***********************************************************************
  Vector copy - parallel assignment ImplTag (setup not amortized)
***********************************************************************/

template <typename T,
	  typename SrcMapT,
	  typename DstMapT,
	  typename ParAssignImpl>
struct t_vcopy<T, SrcMapT, DstMapT, Impl_pa_na<ParAssignImpl> >
  : Benchmark_base
{
  char const* what() { return "t_vcopy<..., Impl_pa_na>"; }
  int ops_per_point(length_type)  { return 1; }
  int riob_per_point(length_type) { return 1*sizeof(T); }
  int wiob_per_point(length_type) { return 1*sizeof(T); }
  int mem_per_point(length_type)  { return 1*sizeof(T); }

  void operator()(length_type size, length_type loop, float& time)
  {
    dimension_type const dim = 1;
    typedef Dense<1, T, row1_type, SrcMapT> src_block_t;
    typedef Dense<1, T, row1_type, DstMapT> dst_block_t;
    Vector<T, src_block_t>   A(size, T(), src_map_);
    Vector<T, dst_block_t>   Z(size,      dst_map_);

    for (index_type i=0; i<A.local().size(); ++i)
    {
      index_type g_i = global_from_local_index(A, 0, i);
      A.local().put(i, T(g_i));
    }
    
    if (pre_sync_)
      barrier();

    timer t1;
    for (index_type l=0; l<loop; ++l)
    {
      ovxx::parallel::Assignment<dim, dst_block_t, src_block_t, ParAssignImpl>
	cpa(Z, A);
      cpa();
    }
    time = t1.elapsed();
    
    for (index_type i=0; i<Z.local().size(); ++i)
    {
      index_type g_i = global_from_local_index(Z, 0, i);
      test_assert(equal(Z.local().get(i), T(g_i)));
    }
  }

  t_vcopy(SrcMapT src_map, DstMapT dst_map, bool pre_sync)
    : src_map_(src_map), dst_map_(dst_map), pre_sync_(pre_sync)
  {}

  // Member data.
  SrcMapT	src_map_;
  DstMapT	dst_map_;
  bool          pre_sync_;
};

/***********************************************************************
  Vector copy - use memcpy
***********************************************************************/

template <typename T>
struct t_vcopy<T, Local_map, Local_map, Impl_memcpy> : Benchmark_base
{
  typedef Local_map SrcMapT;
  typedef Local_map DstMapT;
  typedef Dense<1, T, row1_type, SrcMapT> src_block_t;
  typedef Dense<1, T, row1_type, DstMapT> dst_block_t;
  
  char const* what() { return "t_vcopy<..., Impl_memcpy>"; }
  int ops_per_point(length_type)  { return 1; }
  int riob_per_point(length_type) { return 1*sizeof(T); }
  int wiob_per_point(length_type) { return 1*sizeof(T); }
  int mem_per_point(length_type)  { return 1*sizeof(T); }

  void operator()(length_type size, length_type loop, float& time)
  {
    Vector<T, src_block_t>   A(size, T(), src_map_);
    Vector<T, dst_block_t>   Z(size,      dst_map_);

    for (index_type i=0; i<A.local().size(); ++i)
    {
      index_type g_i = global_from_local_index(A, 0, i);
      A.local().put(i, T(g_i));
    }
    
    if (pre_sync_)
      barrier();

    {
      dda::Data<src_block_t, dda::in> src_ext(A.block());
      dda::Data<dst_block_t, dda::out> dst_ext(Z.block());
    
      timer t1;
      for (index_type l=0; l<loop; ++l)
	std::memcpy(dst_ext.ptr(), src_ext.ptr(), size*sizeof(T));
      time = t1.elapsed();
    }

    for (index_type i=0; i<Z.local().size(); ++i)
    {
      index_type g_i = global_from_local_index(Z, 0, i);
      test_assert(equal(Z.local().get(i), T(g_i)));
    }
  }

  void diag()
  {
  }

  t_vcopy(SrcMapT src_map, DstMapT dst_map, bool pre_sync)
    : src_map_(src_map), dst_map_(dst_map), pre_sync_(pre_sync)
  {}

  // Member data.
  SrcMapT	src_map_;
  DstMapT	dst_map_;
  bool          pre_sync_;
};



/***********************************************************************
  Local/Distributed wrappers
***********************************************************************/

template <typename T,
	  typename ImplTag>
struct t_vcopy_local : t_vcopy<T, Local_map, Local_map, ImplTag>
{
  typedef t_vcopy<T, Local_map, Local_map, ImplTag> base_type;
  t_vcopy_local()
    : base_type(Local_map(), Local_map(), false) 
  {}
};

template <typename T,
	  typename ImplTag>
struct t_vcopy_root : t_vcopy<T, Map<>, Map<>, ImplTag>
{
  typedef t_vcopy<T, Map<>, Map<>, ImplTag> base_type;
  t_vcopy_root()
    : base_type(Map<>(), Map<>(), false)
  {}
};

template <typename T,
	  typename ImplTag>
struct t_vcopy_redist : t_vcopy<T, Map<>, Map<>, ImplTag>
{
  typedef t_vcopy<T, Map<>, Map<>, ImplTag> base_type;
  t_vcopy_redist(char src_dist, char dst_dist, bool pre_sync)
    : base_type(create_map<1, Map<> >(src_dist),
		create_map<1, Map<> >(dst_dist),
		pre_sync)
  {}
};



void
defaults(Loop1P&)
{
}



int
benchmark(Loop1P& loop, int what)
{
  typedef float F;

  // Typedefs for parallel assignment algorithms.
#if OVXX_PARALLEL_API == 1
  typedef ovxx::parallel::Chained_assign  Ca;
  typedef ovxx::parallel::Blkvec_assign   Bva;
#endif

  // typedef fors pre-sync barrier policy.
  bool const ps = (loop.user_param_) ? true : false;

  switch (what)
  {
  case  1: loop(t_vcopy_local<float, Impl_assign>()); break;
#if OVXX_PARALLEL_API == 1
  case  2: loop(t_vcopy_root<float, Impl_assign>()); break;
  case  4: loop(t_vcopy_root<float, Impl_pa<Ca> >()); break;
#endif
  case  5: loop(t_vcopy_local<float, Impl_memcpy>()); break;

#if OVXX_PARALLEL_API == 1
  case 10: loop(t_vcopy_redist<float, Impl_assign>('1', '1', ps)); break;
  case 11: loop(t_vcopy_redist<float, Impl_assign>('1', 'a', ps));  break;
  case 12: loop(t_vcopy_redist<float, Impl_assign>('a', '1', ps)); break;
  case 13: loop(t_vcopy_redist<float, Impl_assign>('a', 'a', ps));  break;
  case 14: loop(t_vcopy_redist<float, Impl_assign>('1', '2', ps)); break;
  case 15: loop(t_vcopy_redist<float, Impl_assign>('1', 'b', ps)); break;

  case 16: loop(t_vcopy_redist<complex<float>, Impl_assign>('1', '2', ps)); break;

  case 100: loop(t_vcopy_redist<F, Impl_pa<Ca> >('1', '1', ps)); break;
  case 101: loop(t_vcopy_redist<F, Impl_pa<Ca> >('1', 'a', ps)); break;
  case 102: loop(t_vcopy_redist<F, Impl_pa<Ca> >('a', '1', ps)); break;
  case 103: loop(t_vcopy_redist<F, Impl_pa<Ca> >('a', 'a', ps)); break;
  case 104: loop(t_vcopy_redist<F, Impl_pa<Ca> >('1', '2', ps)); break;
  case 105: loop(t_vcopy_redist<F, Impl_pa<Ca> >('1', 'b', ps)); break;

  case 110: loop(t_vcopy_redist<F, Impl_pa<Bva> >('1', '1', ps)); break;
  case 111: loop(t_vcopy_redist<F, Impl_pa<Bva> >('1', 'a', ps)); break;
  case 112: loop(t_vcopy_redist<F, Impl_pa<Bva> >('a', '1', ps)); break;
  case 113: loop(t_vcopy_redist<F, Impl_pa<Bva> >('a', 'a', ps)); break;
  case 114: loop(t_vcopy_redist<F, Impl_pa<Bva> >('1', '2', ps)); break;
  case 115: loop(t_vcopy_redist<F, Impl_pa<Bva> >('1', 'b', ps)); break;

  case 150: loop(t_vcopy_redist<F, Impl_pa_na<Ca> >('1', '1', ps)); break;
  case 151: loop(t_vcopy_redist<F, Impl_pa_na<Ca> >('1', 'a', ps)); break;
  case 152: loop(t_vcopy_redist<F, Impl_pa_na<Ca> >('a', '1', ps)); break;
  case 153: loop(t_vcopy_redist<F, Impl_pa_na<Ca> >('a', 'a', ps)); break;
  case 154: loop(t_vcopy_redist<F, Impl_pa_na<Ca> >('1', '2', ps)); break;
  case 155: loop(t_vcopy_redist<F, Impl_pa_na<Ca> >('1', 'b', ps)); break;

  case 160: loop(t_vcopy_redist<F, Impl_pa_na<Bva> >('1', '1', ps)); break;
  case 161: loop(t_vcopy_redist<F, Impl_pa_na<Bva> >('1', 'a', ps)); break;
  case 162: loop(t_vcopy_redist<F, Impl_pa_na<Bva> >('a', '1', ps)); break;
  case 163: loop(t_vcopy_redist<F, Impl_pa_na<Bva> >('a', 'a', ps)); break;
  case 164: loop(t_vcopy_redist<F, Impl_pa_na<Bva> >('1', '2', ps)); break;
  case 165: loop(t_vcopy_redist<F, Impl_pa_na<Bva> >('1', 'b', ps)); break;
#endif


  case 0:
    std::cout
      << "copy -- vector copy\n"
      << "   -1 -- local copy (A = B))\n"
      << "   -5 -- local copy (memcpy))\n"
      << " Using assignment (A = B):\n"
      << "  -10 -- float root copy      (root -> root)\n"
      << "  -11 -- float scatter        (root -> all)\n"
      << "  -12 -- float gather         (all  -> root)\n"
      << "  -13 -- float dist copy      (all  -> all)\n"
      << "  -14 -- float point-to-point (p0   -> p1)\n"
      << "  -15 -- float scatter2       (root -> all non-root)\n"
      << " Using Setup_assign:\n"
      << "  -20 -- float root copy      (root -> root)\n"
      << "  -21 -- float scatter        (root -> all)\n"
      << "  -22 -- float gather         (all  -> root)\n"
      << "  -23 -- float dist copy      (all  -> all)\n"
      << "  -24 -- float point-to-point (p0   -> p1)\n"
      << "  -25 -- float scatter2       (root -> all non-root)\n"
      << "\n MPI low-level parallel assignment directly:\n"
      << "  -100-105 -- Chained_assign\n"
      << "  -110-115 -- Blkvec_assign\n"
      << "  -150-155 -- Chained_assign (non-amortized setup)\n"
      << "  -160-165 -- Blkvec_assign (non-amortized setup)\n"
      ;

  default:
    return 0;
  }
  return 1;
}
