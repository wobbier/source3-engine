/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_FAD_MATH_SIMPLIFICATION_RULES_INTERNALS_H
#define HK_FAD_MATH_SIMPLIFICATION_RULES_INTERNALS_H

namespace hkFad
{	
	//
	// Simplification rules.
	//	
	namespace SimplificationRules
	{
		#define SIMPLIFY(_OP_) typename Simplify<_OP_>::Result

		// pass-through.
		template <typename OP>
		struct Simplify
		{
			typedef OP	Result;
		};

		// Scalar<0,x> => Zero
		template <int D>
		struct Simplify< Scalar<0,D> >
		{
			typedef Zero Result;
		};

		
		// {0,0,0} => Zero (this allows to reuse most scalar simplification rules for vectors)
		template <>
		struct Simplify< Vector3_0 >
		{
			typedef Zero Result;
		};

		// {{0,0,0},{0,0,0},{0,0,0}} => Zero (this allows to reuse most scalar simplification rules for matrices)
		template <>
		struct Simplify< Matrix3_0 >
		{
			typedef Zero Result;
		};
		
		// pass-through.
		template <typename OP, int POWER>
		struct Simplify< Pow< OP, POWER > >
		{
			typedef Pow< SIMPLIFY(OP), POWER> Result;
		};

		// pass-through.
		template <typename OP>
		struct Simplify< Neg< OP > >
		{
			typedef Neg< SIMPLIFY(OP) > Result;
		};

		// -(Q) => (-Q)
		template <int N, int D>
		struct Simplify< Neg< Scalar<N,D> > >
		{
			typedef Scalar<-N,D> Result;
		};

		// -(1) => -1
		template <>
		struct Simplify< Neg< One > >
		{
			typedef Scalar<-1,1> Result;
		};

		// -(0) => 0
		template <>
		struct Simplify< Neg< Zero > >
		{
			typedef Zero Result;
		};
		
		// -(-x) => x
		template <typename OP>
		struct Simplify< Neg< Neg< OP > > >
		{
			typedef SIMPLIFY(OP) Result;
		};

		// -(Q * x) => -Q * x
		template <int N, int D, typename ROP>
		struct Simplify< Neg< Mul< Scalar<N,D>, ROP > > >
		{
			typedef Mul< Scalar<-N,D>, SIMPLIFY(ROP) > Result;
		};
	
		// x^1 => x
		template <typename OP>
		struct Simplify< Pow< OP, 1 > >
		{
			typedef SIMPLIFY(OP) Result;
		};

		// (x^N)^M => x^(N*M)
		template <typename OP, int N, int M>
		struct Simplify< Pow< Pow< OP, N >, M > >
		{
			typedef Pow< SIMPLIFY(OP), N*M > Result;
		};

		// pass-through.
		template <typename LOP, typename ROP>
		struct Simplify< Add< LOP, ROP > >
		{
			typedef Add< SIMPLIFY(LOP), SIMPLIFY(ROP) > Result;
		};

		// x + 0 => x
		template <typename LOP>
		struct Simplify< Add< LOP, Zero > >
		{
			typedef SIMPLIFY(LOP) Result;
		};

		// 0 + x => x
		template <typename ROP>
		struct Simplify< Add< Zero, ROP > >
		{
			typedef SIMPLIFY(ROP) Result;
		};

		// 0 + 0 => 0
		template <>
		struct Simplify< Add< Zero, Zero > >
		{
			typedef Zero Result;
		};
		
		// pass-through.
		template <typename LOP, typename ROP>
		struct Simplify< Sub< LOP, ROP > >
		{
			typedef Sub< SIMPLIFY(LOP), SIMPLIFY(ROP) > Result;
		};

		// x - 0 => x
		template <typename LOP>
		struct Simplify< Sub< LOP, Zero > >
		{
			typedef SIMPLIFY(LOP) Result;
		};

		// 0 - x => -x
		template <typename ROP>
		struct Simplify< Sub< Zero, ROP > >
		{
			typedef Neg< SIMPLIFY(ROP) > Result;
		};

		// 0 - 0 => 0
		template <>
		struct Simplify< Sub< Zero, Zero > >
		{
			typedef Zero Result;
		};

		// pass-through.
		template <typename LOP, typename ROP>
		struct Simplify< Mul< LOP, ROP > >
		{
			typedef Mul< SIMPLIFY(LOP), SIMPLIFY(ROP) > Result;
		};

		// x * 1 => x
		template <typename LOP>
		struct Simplify< Mul< LOP, One > >
		{
			typedef SIMPLIFY(LOP) Result;
		};

		// x * 0 => 0
		template <typename LOP>
		struct Simplify< Mul< LOP, Zero > >
		{
			typedef typename GetTypedZero<typename LOP::Type>::Result Result;
		};

		// 1 * x => x
		template <typename ROP>
		struct Simplify< Mul< One, ROP > >
		{
			typedef SIMPLIFY(ROP) Result;
		};

		// 0 * x => 0
		template <typename ROP>
		struct Simplify< Mul< Zero, ROP > >
		{
			typedef typename GetTypedZero<typename ROP::Type>::Result Result;
		};
		
		// Q0 * (Q1 * x) => (Q0*Q1) * x
		template <int N0, int D0, int N1, int D1, typename ROP >
		struct Simplify< Mul< Scalar<N0,D0>, Mul< Scalar<N1,D1>, ROP > > >
		{
			typedef Mul< Scalar< N0*N1, D0*D1 >, SIMPLIFY(ROP) > Result;
		};
		
		// (Q0) * (Q1) => (Q0*Q1)
		template <int N0, int D0, int N1, int D1 >
		struct Simplify< Mul< Scalar<N0,D0>, Scalar<N1,D1> > >
		{
			typedef Scalar< N0*N1, D0*D1 > Result;
		};

		// (Q0 * x) * (Q1 * y) => (Q0 * Q1) * (x * y)
		template <int N0, int D0, typename OP0, int N1, int D1, typename OP1 >
		struct Simplify< Mul< Mul< Scalar<N0,D0>, OP0 >, Mul< Scalar<N1,D1>, OP1 > > >
		{
			typedef Mul< Mul< Scalar<N0,D0>, Scalar<N1,D1> >, Mul< SIMPLIFY(OP0), SIMPLIFY(OP1) > > Result;
		};		

		// x * -1 => -x
		template <typename LOP>
		struct Simplify< Mul< LOP, Scalar<-1> > >
		{
			typedef Neg< SIMPLIFY(LOP) > Result;
		};

		// -1 * x  => -x
		template <typename ROP>
		struct Simplify< Mul< Scalar<-1>, ROP > >
		{
			typedef Neg< SIMPLIFY(ROP) > Result;
		};

		// pass-through.
		template <typename LOP, typename ROP>
		struct Simplify< Div< LOP, ROP > >
		{
			typedef Div< SIMPLIFY(LOP), SIMPLIFY(ROP) > Result;
		};

		// 0 / x => 0
		template <typename ROP>
		struct Simplify< Div< Zero, ROP > >
		{
			typedef Zero Result;
		};

		// (Q0) / (Q1) => (Q0/Q1)
		template <int N0, int D0, int N1, int D1 >
		struct Simplify< Div< Scalar<N0,D0>, Scalar<N1,D1> > >
		{
			typedef Scalar<D1*N0,D0*N1> Result;
		};

		// Q0 / ( Q1 * x ) => (Q0 / Q1) / x
		template <int N0, int D0, int N1, int D1, typename ROP>
		struct Simplify< Div< Scalar<N0,D0>, Mul< Scalar<N1,D1>, ROP > > >
		{
			typedef Div< Div< Scalar<N0,D0>, Scalar<N1,D1> >, SIMPLIFY(ROP) > Result;
		};
		
		// pass-through.
		template <typename LOP, typename ROP>
		struct Simplify< Cross< LOP, ROP > >
		{
			typedef Cross< SIMPLIFY(LOP), SIMPLIFY(ROP) > Result;
		};

		// 0 x {X,Y,Z} => 0
		template <typename ROP>
		struct Simplify< Cross< Zero, ROP > >
		{
			typedef Zero Result;
		};

		// {X,Y,Z} x 0 => 0
		template <typename LOP>
		struct Simplify< Cross< LOP, Zero > >
		{
			typedef Zero Result;
		};

		// pass-through.
		template <typename OP>
		struct Simplify< Norm< OP > >
		{
			typedef Norm< SIMPLIFY(OP) > Result;
		};

		// pass-through.
		template <typename LOP, typename ROP>
		struct Simplify< Dot< LOP, ROP > >
		{
			typedef Dot< SIMPLIFY(LOP), SIMPLIFY(ROP) > Result;
		};

		// {x,y,z} . 0 => 0
		template <typename LOP >
		struct Simplify< Dot< LOP, Zero > >
		{
			typedef Zero Result;
		};

		// 0 . {x,y,z} => 0
		template <typename ROP >
		struct Simplify< Dot< Zero, ROP > >
		{
			typedef Zero Result;
		};

		#undef SIMPLIFY
	}
}

#endif // HK_FAD_MATH_SIMPLIFICATION_RULES_INTERNALS_H

/*
 * Havok SDK - NO SOURCE PC DOWNLOAD, BUILD(#20140907)
 * 
 * Confidential Information of Havok.  (C) Copyright 1999-2014
 * Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
 * Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
 * rights, and intellectual property rights in the Havok software remain in
 * Havok and/or its suppliers.
 * 
 * Use of this software for evaluation purposes is subject to and indicates
 * acceptance of the End User licence Agreement for this product. A copy of
 * the license is included with this software and is also available at www.havok.com/tryhavok.
 * 
 */
