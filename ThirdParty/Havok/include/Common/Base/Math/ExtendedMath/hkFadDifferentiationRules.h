/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_FAD_MATH_DIFFERENTIATION_RULES_INTERNALS_H
#define HK_FAD_MATH_DIFFERENTIATION_RULES_INTERNALS_H

namespace hkFad
{	
	//
	// Differentiation rules.
	//
	namespace DifferentiationRules
	{
		// Delegate rule (usually maps to Zero, Scalar or vector derived types).
		template <typename VAR, typename OP>
		struct Diff
		{
			typedef typename OP::template diff<VAR>::Result Result;
		};

		// Seed rule.
		template <typename VAR>
		struct Diff<VAR,VAR>
		{
			typedef One	Result;
		};

		// Vector rule.
		template <typename VAR, typename X, typename Y, typename Z>
		struct Diff<VAR, Vector3<X,Y,Z> >
		{
			typedef Vector3< typename Diff<VAR,X>::Result, typename Diff<VAR,Y>::Result, typename Diff<VAR,Z>::Result >	Result;
		};

		// Matrix rule.
		template <typename VAR, typename X, typename Y, typename Z>
		struct Diff<VAR, Matrix3<X,Y,Z> >
		{
			typedef Matrix3< typename Diff<VAR,X>::Result, typename Diff<VAR,Y>::Result, typename Diff<VAR,Z>::Result >	Result;
		};

		// Power rule ( f(x)^n => n * f(x)^(n-1) * f'(x) ).
		template <typename VAR, typename OP, int POWER>
		struct Diff<VAR, Pow<OP,POWER> >
		{
			typedef Mul< Mul< Scalar<POWER>, Pow<OP,POWER-1> >, typename Diff<VAR,OP>::Result > Result;
		};

		// Square root rule ( sqrt(f(x)) => f'(x) / 2 * sqrt(f(x)) ).
		template <typename VAR, typename OP>
		struct Diff<VAR, Sqrt<OP> >
		{
			typedef Div< typename Diff<VAR,OP>::Result, Mul< Scalar<2>, Sqrt<OP> > > Result;
		};

		// Sin rule ( sin(f(x)) => cos(f(x)) * f'(x) ).
		template <typename VAR, typename OP>
		struct Diff<VAR, Sin<OP> >
		{
			typedef Mul< Cos< OP >, typename Diff<VAR,OP>::Result > Result;
		};

		// Cos rule ( cos(f(x)) => -sin(f(x)) * f'(x) ).
		template <typename VAR, typename OP>
		struct Diff<VAR, Cos<OP> >
		{
			typedef Mul< Neg< Sin< OP > >, typename Diff<VAR,OP>::Result > Result;
		};

		// Neg rule.
		template <typename VAR, typename OP>
		struct Diff<VAR, Neg<OP> >
		{
			typedef Neg<typename Diff<VAR,OP>::Result> Result;
		};

		// Addition rule.
		template <typename VAR, typename LOP, typename ROP>
		struct Diff<VAR, Add<LOP,ROP> >
		{
			typedef Add< typename Diff<VAR,LOP>::Result, typename Diff<VAR,ROP>::Result  > Result;
		};

		// Subtraction rule.
		template <typename VAR, typename LOP, typename ROP>
		struct Diff<VAR, Sub<LOP,ROP> >
		{
			typedef Sub< typename Diff<VAR,LOP>::Result, typename Diff<VAR,ROP>::Result  > Result;
		};

		// Product rules.		
		template <typename VAR, typename LOP, typename ROP>
		struct Diff<VAR, Mul<LOP,ROP> >
		{
			typedef typename Diff<VAR,LOP>::Result	dL;
			typedef typename Diff<VAR,ROP>::Result	dR;
			typedef Add< Mul< dL, ROP >, Mul< LOP, dR > >	Result;
		};
		
		// Quotient rule.
		template <typename VAR, typename LOP, typename ROP>
		struct Diff<VAR, Div<LOP,ROP> >
		{
			typedef typename Diff<VAR,LOP>::Result	dL;
			typedef typename Diff<VAR,ROP>::Result	dR;
			typedef Div< Sub< Mul< dL, ROP >, Mul< LOP, dR > >, Pow<ROP,2> >	Result;
		};

		// Norm rule.
		template <typename VAR, typename OP>
		struct Diff<VAR, Norm<OP> >
		{			
			typedef Div< Dot< OP, typename Diff<VAR,OP>::Result >, Norm<OP> > Result;
		};

		// Cross rule.
		template <typename VAR, typename LOP, typename ROP>
		struct Diff<VAR, Cross<LOP,ROP> >
		{
			typedef typename Diff<VAR,LOP>::Result dL;
			typedef typename Diff<VAR,ROP>::Result dR;
			typedef Add< Cross<dL,ROP>, Cross<LOP,dR> > Result;
		};

		// Dot rule.
		template <typename VAR, typename LOP, typename ROP>
		struct Diff<VAR, Dot<LOP,ROP> >
		{
			typedef typename Diff<VAR,LOP>::Result dL;
			typedef typename Diff<VAR,ROP>::Result dR;
			typedef Add< Dot<dL,ROP>, Dot<LOP,dR> > Result;
		};
	}
}

#endif // HK_FAD_MATH_DIFFERENTIATION_RULES_INTERNALS_H

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
