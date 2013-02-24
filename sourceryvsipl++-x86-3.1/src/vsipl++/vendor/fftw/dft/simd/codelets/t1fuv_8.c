/*
 * Copyright (c) 2003, 2007-8 Matteo Frigo
 * Copyright (c) 2003, 2007-8 Massachusetts Institute of Technology
 *
 * See the file COPYING for license information.
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Mon Nov 10 20:37:29 EST 2008 */

#include "codelet-dft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_twiddle_c -fma -reorder-insns -schedule-for-pipeline -simd -compact -variables 4 -pipeline-latency 8 -n 8 -name t1fuv_8 -include t1fu.h */

/*
 * This function contains 33 FP additions, 24 FP multiplications,
 * (or, 23 additions, 14 multiplications, 10 fused multiply/add),
 * 36 stack variables, 1 constants, and 16 memory accesses
 */
#include "t1fu.h"

static void t1fuv_8(R *ri, R *ii, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DVK(KP707106781, +0.707106781186547524400844362104849039284835938);
     INT m;
     R *x;
     x = ri;
     for (m = mb, W = W + (mb * ((TWVL / VL) * 14)); m < me; m = m + VL, x = x + (VL * ms), W = W + (TWVL * 14), MAKE_VOLATILE_STRIDE(rs)) {
	  V T1, T2, Th, Tj, T5, T7, Ta, Tc;
	  T1 = LD(&(x[0]), ms, &(x[0]));
	  T2 = LD(&(x[WS(rs, 4)]), ms, &(x[0]));
	  Th = LD(&(x[WS(rs, 2)]), ms, &(x[0]));
	  Tj = LD(&(x[WS(rs, 6)]), ms, &(x[0]));
	  T5 = LD(&(x[WS(rs, 1)]), ms, &(x[WS(rs, 1)]));
	  T7 = LD(&(x[WS(rs, 5)]), ms, &(x[WS(rs, 1)]));
	  Ta = LD(&(x[WS(rs, 7)]), ms, &(x[WS(rs, 1)]));
	  Tc = LD(&(x[WS(rs, 3)]), ms, &(x[WS(rs, 1)]));
	  {
	       V T3, Ti, Tk, T6, T8, Tb, Td;
	       T3 = BYTWJ(&(W[TWVL * 6]), T2);
	       Ti = BYTWJ(&(W[TWVL * 2]), Th);
	       Tk = BYTWJ(&(W[TWVL * 10]), Tj);
	       T6 = BYTWJ(&(W[0]), T5);
	       T8 = BYTWJ(&(W[TWVL * 8]), T7);
	       Tb = BYTWJ(&(W[TWVL * 12]), Ta);
	       Td = BYTWJ(&(W[TWVL * 4]), Tc);
	       {
		    V Tq, T4, Tr, Tl, Tt, T9, Tu, Te, Tw, Ts;
		    Tq = VADD(T1, T3);
		    T4 = VSUB(T1, T3);
		    Tr = VADD(Ti, Tk);
		    Tl = VSUB(Ti, Tk);
		    Tt = VADD(T6, T8);
		    T9 = VSUB(T6, T8);
		    Tu = VADD(Tb, Td);
		    Te = VSUB(Tb, Td);
		    Tw = VSUB(Tq, Tr);
		    Ts = VADD(Tq, Tr);
		    {
			 V Tx, Tv, Tm, Tf;
			 Tx = VSUB(Tu, Tt);
			 Tv = VADD(Tt, Tu);
			 Tm = VSUB(Te, T9);
			 Tf = VADD(T9, Te);
			 {
			      V Tp, Tn, To, Tg;
			      ST(&(x[WS(rs, 2)]), VFMAI(Tx, Tw), ms, &(x[0]));
			      ST(&(x[WS(rs, 6)]), VFNMSI(Tx, Tw), ms, &(x[0]));
			      ST(&(x[0]), VADD(Ts, Tv), ms, &(x[0]));
			      ST(&(x[WS(rs, 4)]), VSUB(Ts, Tv), ms, &(x[0]));
			      Tp = VFMA(LDK(KP707106781), Tm, Tl);
			      Tn = VFNMS(LDK(KP707106781), Tm, Tl);
			      To = VFNMS(LDK(KP707106781), Tf, T4);
			      Tg = VFMA(LDK(KP707106781), Tf, T4);
			      ST(&(x[WS(rs, 5)]), VFNMSI(Tp, To), ms, &(x[WS(rs, 1)]));
			      ST(&(x[WS(rs, 3)]), VFMAI(Tp, To), ms, &(x[WS(rs, 1)]));
			      ST(&(x[WS(rs, 7)]), VFMAI(Tn, Tg), ms, &(x[WS(rs, 1)]));
			      ST(&(x[WS(rs, 1)]), VFNMSI(Tn, Tg), ms, &(x[WS(rs, 1)]));
			 }
		    }
	       }
	  }
     }
}

static const tw_instr twinstr[] = {
     VTW(0, 1),
     VTW(0, 2),
     VTW(0, 3),
     VTW(0, 4),
     VTW(0, 5),
     VTW(0, 6),
     VTW(0, 7),
     {TW_NEXT, VL, 0}
};

static const ct_desc desc = { 8, "t1fuv_8", twinstr, &GENUS, {23, 14, 10, 0}, 0, 0, 0 };

void X(codelet_t1fuv_8) (planner *p) {
     X(kdft_dit_register) (p, t1fuv_8, &desc);
}
#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_twiddle_c -simd -compact -variables 4 -pipeline-latency 8 -n 8 -name t1fuv_8 -include t1fu.h */

/*
 * This function contains 33 FP additions, 16 FP multiplications,
 * (or, 33 additions, 16 multiplications, 0 fused multiply/add),
 * 24 stack variables, 1 constants, and 16 memory accesses
 */
#include "t1fu.h"

static void t1fuv_8(R *ri, R *ii, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DVK(KP707106781, +0.707106781186547524400844362104849039284835938);
     INT m;
     R *x;
     x = ri;
     for (m = mb, W = W + (mb * ((TWVL / VL) * 14)); m < me; m = m + VL, x = x + (VL * ms), W = W + (TWVL * 14), MAKE_VOLATILE_STRIDE(rs)) {
	  V T4, Tq, Tm, Tr, T9, Tt, Te, Tu, T1, T3, T2;
	  T1 = LD(&(x[0]), ms, &(x[0]));
	  T2 = LD(&(x[WS(rs, 4)]), ms, &(x[0]));
	  T3 = BYTWJ(&(W[TWVL * 6]), T2);
	  T4 = VSUB(T1, T3);
	  Tq = VADD(T1, T3);
	  {
	       V Tj, Tl, Ti, Tk;
	       Ti = LD(&(x[WS(rs, 2)]), ms, &(x[0]));
	       Tj = BYTWJ(&(W[TWVL * 2]), Ti);
	       Tk = LD(&(x[WS(rs, 6)]), ms, &(x[0]));
	       Tl = BYTWJ(&(W[TWVL * 10]), Tk);
	       Tm = VSUB(Tj, Tl);
	       Tr = VADD(Tj, Tl);
	  }
	  {
	       V T6, T8, T5, T7;
	       T5 = LD(&(x[WS(rs, 1)]), ms, &(x[WS(rs, 1)]));
	       T6 = BYTWJ(&(W[0]), T5);
	       T7 = LD(&(x[WS(rs, 5)]), ms, &(x[WS(rs, 1)]));
	       T8 = BYTWJ(&(W[TWVL * 8]), T7);
	       T9 = VSUB(T6, T8);
	       Tt = VADD(T6, T8);
	  }
	  {
	       V Tb, Td, Ta, Tc;
	       Ta = LD(&(x[WS(rs, 7)]), ms, &(x[WS(rs, 1)]));
	       Tb = BYTWJ(&(W[TWVL * 12]), Ta);
	       Tc = LD(&(x[WS(rs, 3)]), ms, &(x[WS(rs, 1)]));
	       Td = BYTWJ(&(W[TWVL * 4]), Tc);
	       Te = VSUB(Tb, Td);
	       Tu = VADD(Tb, Td);
	  }
	  {
	       V Ts, Tv, Tw, Tx;
	       Ts = VADD(Tq, Tr);
	       Tv = VADD(Tt, Tu);
	       ST(&(x[WS(rs, 4)]), VSUB(Ts, Tv), ms, &(x[0]));
	       ST(&(x[0]), VADD(Ts, Tv), ms, &(x[0]));
	       Tw = VSUB(Tq, Tr);
	       Tx = VBYI(VSUB(Tu, Tt));
	       ST(&(x[WS(rs, 6)]), VSUB(Tw, Tx), ms, &(x[0]));
	       ST(&(x[WS(rs, 2)]), VADD(Tw, Tx), ms, &(x[0]));
	       {
		    V Tg, To, Tn, Tp, Tf, Th;
		    Tf = VMUL(LDK(KP707106781), VADD(T9, Te));
		    Tg = VADD(T4, Tf);
		    To = VSUB(T4, Tf);
		    Th = VMUL(LDK(KP707106781), VSUB(Te, T9));
		    Tn = VBYI(VSUB(Th, Tm));
		    Tp = VBYI(VADD(Tm, Th));
		    ST(&(x[WS(rs, 7)]), VSUB(Tg, Tn), ms, &(x[WS(rs, 1)]));
		    ST(&(x[WS(rs, 3)]), VADD(To, Tp), ms, &(x[WS(rs, 1)]));
		    ST(&(x[WS(rs, 1)]), VADD(Tg, Tn), ms, &(x[WS(rs, 1)]));
		    ST(&(x[WS(rs, 5)]), VSUB(To, Tp), ms, &(x[WS(rs, 1)]));
	       }
	  }
     }
}

static const tw_instr twinstr[] = {
     VTW(0, 1),
     VTW(0, 2),
     VTW(0, 3),
     VTW(0, 4),
     VTW(0, 5),
     VTW(0, 6),
     VTW(0, 7),
     {TW_NEXT, VL, 0}
};

static const ct_desc desc = { 8, "t1fuv_8", twinstr, &GENUS, {33, 16, 0, 0}, 0, 0, 0 };

void X(codelet_t1fuv_8) (planner *p) {
     X(kdft_dit_register) (p, t1fuv_8, &desc);
}
#endif				/* HAVE_FMA */
