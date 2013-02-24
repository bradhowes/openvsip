/*
 * Copyright (c) 2003, 2007-8 Matteo Frigo
 * Copyright (c) 2003, 2007-8 Massachusetts Institute of Technology
 *
 * See the file COPYING for license information.
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Mon Nov 10 20:36:24 EST 2008 */

#include "codelet-dft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_notw -fma -reorder-insns -schedule-for-pipeline -simd -compact -variables 4 -pipeline-latency 8 -n 8 -name n2sv_8 -with-ostride 1 -include n2s.h -store-multiple 4 */

/*
 * This function contains 52 FP additions, 8 FP multiplications,
 * (or, 44 additions, 0 multiplications, 8 fused multiply/add),
 * 58 stack variables, 1 constants, and 36 memory accesses
 */
#include "n2s.h"

static void n2sv_8(const R *ri, const R *ii, R *ro, R *io, stride is, stride os, INT v, INT ivs, INT ovs)
{
     DVK(KP707106781, +0.707106781186547524400844362104849039284835938);
     INT i;
     for (i = v; i > 0; i = i - (2 * VL), ri = ri + ((2 * VL) * ivs), ii = ii + ((2 * VL) * ivs), ro = ro + ((2 * VL) * ovs), io = io + ((2 * VL) * ovs), MAKE_VOLATILE_STRIDE(is), MAKE_VOLATILE_STRIDE(os)) {
	  V TF, TJ, TD, TR, TS, TT, TU, TV, TW, TE, TX, TY, TK, TI, TZ;
	  V T10, T11, T12;
	  {
	       V Tb, Tn, T3, TC, Ti, TB, T6, To, Tl, Tc, Tw, Tx, T8, T9, Tr;
	       V Ts;
	       {
		    V T1, T2, Tg, Th, T4, T5, Tj, Tk;
		    T1 = LD(&(ri[0]), ivs, &(ri[0]));
		    T2 = LD(&(ri[WS(is, 4)]), ivs, &(ri[0]));
		    Tg = LD(&(ii[0]), ivs, &(ii[0]));
		    Th = LD(&(ii[WS(is, 4)]), ivs, &(ii[0]));
		    T4 = LD(&(ri[WS(is, 2)]), ivs, &(ri[0]));
		    T5 = LD(&(ri[WS(is, 6)]), ivs, &(ri[0]));
		    Tj = LD(&(ii[WS(is, 2)]), ivs, &(ii[0]));
		    Tk = LD(&(ii[WS(is, 6)]), ivs, &(ii[0]));
		    Tb = LD(&(ri[WS(is, 7)]), ivs, &(ri[WS(is, 1)]));
		    Tn = VSUB(T1, T2);
		    T3 = VADD(T1, T2);
		    TC = VSUB(Tg, Th);
		    Ti = VADD(Tg, Th);
		    TB = VSUB(T4, T5);
		    T6 = VADD(T4, T5);
		    To = VSUB(Tj, Tk);
		    Tl = VADD(Tj, Tk);
		    Tc = LD(&(ri[WS(is, 3)]), ivs, &(ri[WS(is, 1)]));
		    Tw = LD(&(ii[WS(is, 7)]), ivs, &(ii[WS(is, 1)]));
		    Tx = LD(&(ii[WS(is, 3)]), ivs, &(ii[WS(is, 1)]));
		    T8 = LD(&(ri[WS(is, 1)]), ivs, &(ri[WS(is, 1)]));
		    T9 = LD(&(ri[WS(is, 5)]), ivs, &(ri[WS(is, 1)]));
		    Tr = LD(&(ii[WS(is, 1)]), ivs, &(ii[WS(is, 1)]));
		    Ts = LD(&(ii[WS(is, 5)]), ivs, &(ii[WS(is, 1)]));
	       }
	       {
		    V TL, T7, TP, Tm, Tz, TH, Te, Tf, TO, TQ, TG, Tu, Tp, TA;
		    {
			 V Td, Tv, TN, Ty, Ta, Tq, TM, Tt;
			 TL = VSUB(T3, T6);
			 T7 = VADD(T3, T6);
			 Td = VADD(Tb, Tc);
			 Tv = VSUB(Tb, Tc);
			 TN = VADD(Tw, Tx);
			 Ty = VSUB(Tw, Tx);
			 Ta = VADD(T8, T9);
			 Tq = VSUB(T8, T9);
			 TM = VADD(Tr, Ts);
			 Tt = VSUB(Tr, Ts);
			 TP = VADD(Ti, Tl);
			 Tm = VSUB(Ti, Tl);
			 Tz = VSUB(Tv, Ty);
			 TH = VADD(Tv, Ty);
			 Te = VADD(Ta, Td);
			 Tf = VSUB(Td, Ta);
			 TO = VSUB(TM, TN);
			 TQ = VADD(TM, TN);
			 TG = VSUB(Tt, Tq);
			 Tu = VADD(Tq, Tt);
		    }
		    TF = VSUB(Tn, To);
		    Tp = VADD(Tn, To);
		    TJ = VSUB(TC, TB);
		    TD = VADD(TB, TC);
		    TR = VSUB(Tm, Tf);
		    STM4(&(io[6]), TR, ovs, &(io[0]));
		    TS = VADD(Tf, Tm);
		    STM4(&(io[2]), TS, ovs, &(io[0]));
		    TT = VADD(T7, Te);
		    STM4(&(ro[0]), TT, ovs, &(ro[0]));
		    TU = VSUB(T7, Te);
		    STM4(&(ro[4]), TU, ovs, &(ro[0]));
		    TV = VADD(TP, TQ);
		    STM4(&(io[0]), TV, ovs, &(io[0]));
		    TW = VSUB(TP, TQ);
		    STM4(&(io[4]), TW, ovs, &(io[0]));
		    TE = VSUB(Tz, Tu);
		    TA = VADD(Tu, Tz);
		    TX = VADD(TL, TO);
		    STM4(&(ro[2]), TX, ovs, &(ro[0]));
		    TY = VSUB(TL, TO);
		    STM4(&(ro[6]), TY, ovs, &(ro[0]));
		    TK = VADD(TG, TH);
		    TI = VSUB(TG, TH);
		    TZ = VFMA(LDK(KP707106781), TA, Tp);
		    STM4(&(ro[1]), TZ, ovs, &(ro[1]));
		    T10 = VFNMS(LDK(KP707106781), TA, Tp);
		    STM4(&(ro[5]), T10, ovs, &(ro[1]));
	       }
	  }
	  T11 = VFMA(LDK(KP707106781), TK, TJ);
	  STM4(&(io[1]), T11, ovs, &(io[1]));
	  T12 = VFNMS(LDK(KP707106781), TK, TJ);
	  STM4(&(io[5]), T12, ovs, &(io[1]));
	  {
	       V T13, T14, T15, T16;
	       T13 = VFMA(LDK(KP707106781), TE, TD);
	       STM4(&(io[3]), T13, ovs, &(io[1]));
	       STN4(&(io[0]), TV, T11, TS, T13, ovs);
	       T14 = VFNMS(LDK(KP707106781), TE, TD);
	       STM4(&(io[7]), T14, ovs, &(io[1]));
	       STN4(&(io[4]), TW, T12, TR, T14, ovs);
	       T15 = VFMA(LDK(KP707106781), TI, TF);
	       STM4(&(ro[3]), T15, ovs, &(ro[1]));
	       STN4(&(ro[0]), TT, TZ, TX, T15, ovs);
	       T16 = VFNMS(LDK(KP707106781), TI, TF);
	       STM4(&(ro[7]), T16, ovs, &(ro[1]));
	       STN4(&(ro[4]), TU, T10, TY, T16, ovs);
	  }
     }
}

static const kdft_desc desc = { 8, "n2sv_8", {44, 0, 8, 0}, &GENUS, 0, 1, 0, 0 };
void X(codelet_n2sv_8) (planner *p) {
     X(kdft_register) (p, n2sv_8, &desc);
}

#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_notw -simd -compact -variables 4 -pipeline-latency 8 -n 8 -name n2sv_8 -with-ostride 1 -include n2s.h -store-multiple 4 */

/*
 * This function contains 52 FP additions, 4 FP multiplications,
 * (or, 52 additions, 4 multiplications, 0 fused multiply/add),
 * 34 stack variables, 1 constants, and 36 memory accesses
 */
#include "n2s.h"

static void n2sv_8(const R *ri, const R *ii, R *ro, R *io, stride is, stride os, INT v, INT ivs, INT ovs)
{
     DVK(KP707106781, +0.707106781186547524400844362104849039284835938);
     INT i;
     for (i = v; i > 0; i = i - (2 * VL), ri = ri + ((2 * VL) * ivs), ii = ii + ((2 * VL) * ivs), ro = ro + ((2 * VL) * ovs), io = io + ((2 * VL) * ovs), MAKE_VOLATILE_STRIDE(is), MAKE_VOLATILE_STRIDE(os)) {
	  V T3, Tn, Ti, TC, T6, TB, Tl, To, Td, TN, Tz, TH, Ta, TM, Tu;
	  V TG;
	  {
	       V T1, T2, Tj, Tk;
	       T1 = LD(&(ri[0]), ivs, &(ri[0]));
	       T2 = LD(&(ri[WS(is, 4)]), ivs, &(ri[0]));
	       T3 = VADD(T1, T2);
	       Tn = VSUB(T1, T2);
	       {
		    V Tg, Th, T4, T5;
		    Tg = LD(&(ii[0]), ivs, &(ii[0]));
		    Th = LD(&(ii[WS(is, 4)]), ivs, &(ii[0]));
		    Ti = VADD(Tg, Th);
		    TC = VSUB(Tg, Th);
		    T4 = LD(&(ri[WS(is, 2)]), ivs, &(ri[0]));
		    T5 = LD(&(ri[WS(is, 6)]), ivs, &(ri[0]));
		    T6 = VADD(T4, T5);
		    TB = VSUB(T4, T5);
	       }
	       Tj = LD(&(ii[WS(is, 2)]), ivs, &(ii[0]));
	       Tk = LD(&(ii[WS(is, 6)]), ivs, &(ii[0]));
	       Tl = VADD(Tj, Tk);
	       To = VSUB(Tj, Tk);
	       {
		    V Tb, Tc, Tv, Tw, Tx, Ty;
		    Tb = LD(&(ri[WS(is, 7)]), ivs, &(ri[WS(is, 1)]));
		    Tc = LD(&(ri[WS(is, 3)]), ivs, &(ri[WS(is, 1)]));
		    Tv = VSUB(Tb, Tc);
		    Tw = LD(&(ii[WS(is, 7)]), ivs, &(ii[WS(is, 1)]));
		    Tx = LD(&(ii[WS(is, 3)]), ivs, &(ii[WS(is, 1)]));
		    Ty = VSUB(Tw, Tx);
		    Td = VADD(Tb, Tc);
		    TN = VADD(Tw, Tx);
		    Tz = VSUB(Tv, Ty);
		    TH = VADD(Tv, Ty);
	       }
	       {
		    V T8, T9, Tq, Tr, Ts, Tt;
		    T8 = LD(&(ri[WS(is, 1)]), ivs, &(ri[WS(is, 1)]));
		    T9 = LD(&(ri[WS(is, 5)]), ivs, &(ri[WS(is, 1)]));
		    Tq = VSUB(T8, T9);
		    Tr = LD(&(ii[WS(is, 1)]), ivs, &(ii[WS(is, 1)]));
		    Ts = LD(&(ii[WS(is, 5)]), ivs, &(ii[WS(is, 1)]));
		    Tt = VSUB(Tr, Ts);
		    Ta = VADD(T8, T9);
		    TM = VADD(Tr, Ts);
		    Tu = VADD(Tq, Tt);
		    TG = VSUB(Tt, Tq);
	       }
	  }
	  {
	       V TR, TS, TT, TU, TV, TW, TX, TY;
	       {
		    V T7, Te, TP, TQ;
		    T7 = VADD(T3, T6);
		    Te = VADD(Ta, Td);
		    TR = VSUB(T7, Te);
		    STM4(&(ro[4]), TR, ovs, &(ro[0]));
		    TS = VADD(T7, Te);
		    STM4(&(ro[0]), TS, ovs, &(ro[0]));
		    TP = VADD(Ti, Tl);
		    TQ = VADD(TM, TN);
		    TT = VSUB(TP, TQ);
		    STM4(&(io[4]), TT, ovs, &(io[0]));
		    TU = VADD(TP, TQ);
		    STM4(&(io[0]), TU, ovs, &(io[0]));
	       }
	       {
		    V Tf, Tm, TL, TO;
		    Tf = VSUB(Td, Ta);
		    Tm = VSUB(Ti, Tl);
		    TV = VADD(Tf, Tm);
		    STM4(&(io[2]), TV, ovs, &(io[0]));
		    TW = VSUB(Tm, Tf);
		    STM4(&(io[6]), TW, ovs, &(io[0]));
		    TL = VSUB(T3, T6);
		    TO = VSUB(TM, TN);
		    TX = VSUB(TL, TO);
		    STM4(&(ro[6]), TX, ovs, &(ro[0]));
		    TY = VADD(TL, TO);
		    STM4(&(ro[2]), TY, ovs, &(ro[0]));
	       }
	       {
		    V TZ, T10, T11, T12;
		    {
			 V Tp, TA, TJ, TK;
			 Tp = VADD(Tn, To);
			 TA = VMUL(LDK(KP707106781), VADD(Tu, Tz));
			 TZ = VSUB(Tp, TA);
			 STM4(&(ro[5]), TZ, ovs, &(ro[1]));
			 T10 = VADD(Tp, TA);
			 STM4(&(ro[1]), T10, ovs, &(ro[1]));
			 TJ = VSUB(TC, TB);
			 TK = VMUL(LDK(KP707106781), VADD(TG, TH));
			 T11 = VSUB(TJ, TK);
			 STM4(&(io[5]), T11, ovs, &(io[1]));
			 T12 = VADD(TJ, TK);
			 STM4(&(io[1]), T12, ovs, &(io[1]));
		    }
		    {
			 V TD, TE, T13, T14;
			 TD = VADD(TB, TC);
			 TE = VMUL(LDK(KP707106781), VSUB(Tz, Tu));
			 T13 = VSUB(TD, TE);
			 STM4(&(io[7]), T13, ovs, &(io[1]));
			 STN4(&(io[4]), TT, T11, TW, T13, ovs);
			 T14 = VADD(TD, TE);
			 STM4(&(io[3]), T14, ovs, &(io[1]));
			 STN4(&(io[0]), TU, T12, TV, T14, ovs);
		    }
		    {
			 V TF, TI, T15, T16;
			 TF = VSUB(Tn, To);
			 TI = VMUL(LDK(KP707106781), VSUB(TG, TH));
			 T15 = VSUB(TF, TI);
			 STM4(&(ro[7]), T15, ovs, &(ro[1]));
			 STN4(&(ro[4]), TR, TZ, TX, T15, ovs);
			 T16 = VADD(TF, TI);
			 STM4(&(ro[3]), T16, ovs, &(ro[1]));
			 STN4(&(ro[0]), TS, T10, TY, T16, ovs);
		    }
	       }
	  }
     }
}

static const kdft_desc desc = { 8, "n2sv_8", {52, 4, 0, 0}, &GENUS, 0, 1, 0, 0 };
void X(codelet_n2sv_8) (planner *p) {
     X(kdft_register) (p, n2sv_8, &desc);
}

#endif				/* HAVE_FMA */
