/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_FAD_MATH_H
#define HK_FAD_MATH_H

#include <Common/Base/System/Io/OStream/hkOStream.h>
#include <Common/Base/Container/String/hkStringBuf.h>

namespace hkFad
{	
	//
	// Helpers
	//

	// Deduce the type of a binary operation.
	template <typename LOP_Type, typename ROP_Type> struct BinaryType {};

	template <> struct BinaryType< hkSimdReal, hkSimdReal >		{ typedef hkSimdReal Result; };
	template <> struct BinaryType< hkVector4, hkVector4 >		{ typedef hkVector4 Result; };
	template <> struct BinaryType< hkSimdReal, hkVector4 >		{ typedef hkVector4 Result; };
	template <> struct BinaryType< hkVector4, hkSimdReal >		{ typedef hkVector4 Result; };
	template <> struct BinaryType< hkMatrix3, hkMatrix3 >		{ typedef hkMatrix3 Result; };
	template <> struct BinaryType< hkMatrix3, hkVector4 >		{ typedef hkVector4 Result; };
	template <> struct BinaryType< hkMatrix3, hkSimdReal >		{ typedef hkMatrix3 Result; };
	template <> struct BinaryType< hkSimdReal, hkMatrix3 >		{ typedef hkMatrix3 Result; };

	// Deduce the type of a dot product.
	template <typename A, typename B> struct DotType {};
	template <> struct DotType<hkVector4,hkVector4> { typedef hkSimdReal Result; };
	template <> struct DotType<hkMatrix3,hkVector4> { typedef hkVector4 Result; };
	template <> struct DotType<hkVector4,hkMatrix3> { typedef hkVector4 Result; };
	template <> struct DotType<hkMatrix3,hkMatrix3> { typedef hkMatrix3 Result; };
	
	//
	// Expression building.
	//
	
	// Zero
	struct Zero
	{
		typedef hkSimdReal Type;
		template <typename EVALUATOR> HK_FORCE_INLINE static Type	eval( const EVALUATOR& ) { return hkSimdReal_0; }
		static void													toString( hkStringBuf& str ) { str.append("0"); }
		template <typename VAR> struct diff { typedef Zero Result; };
	};

	// One
	struct One
	{
		typedef hkSimdReal Type;
		template <typename EVALUATOR> HK_FORCE_INLINE static Type	eval( const EVALUATOR& ) { return hkSimdReal_1; }
		static void													toString( hkStringBuf& str ) { str.append("1"); }
		template <typename VAR> struct diff { typedef Zero Result; };
	};

	// Scalar (Q).
	template <int NUM, int DEN = 1>
	struct Scalar
	{
		typedef hkSimdReal Type;
		template <typename EVALUATOR> HK_FORCE_INLINE static Type	eval( const EVALUATOR& evaluator ) { return DEN == 1 ? Type(NUM) : Type(NUM) / Type(DEN); }
		static void													toString( hkStringBuf& str ) { if( DEN == 1 ) str.appendPrintf("%d",NUM); else str.appendPrintf("(%d/%d)",NUM,DEN); }
		template <typename VAR> struct diff { typedef Zero Result; };
	};
	
	// Vector3 (R3)
	template <typename X, typename Y, typename Z>
	struct Vector3
	{
		typedef hkVector4	Type;
		template <typename EVALUATOR> HK_FORCE_INLINE static Type	eval( const EVALUATOR& evaluator ) { hkVector4 ret; ret.set( X::eval( evaluator ), Y::eval( evaluator ), Z::eval( evaluator ) ); return ret; }
		static void													toString( hkStringBuf& str ) { str.append("{ "); X::toString( str ); str.append(" , "); Y::toString( str ); str.append(" , "); Z::toString( str ); str.append(" }"); }
	};

	// Matrix3 (M3, column major)
	template <typename X, typename Y, typename Z>
	struct Matrix3
	{
		typedef hkMatrix3	Type;
		template <typename EVALUATOR> HK_FORCE_INLINE static Type	eval( const EVALUATOR& evaluator ) { hkMatrix3 ret; ret.setCols( X::eval( evaluator ), Y::eval( evaluator ), Z::eval( evaluator ) ); return ret; }		
		static void													toString( hkStringBuf& str ) { str.append("Transpose[{ "); X::toString( str ); str.append(" , "); Y::toString( str ); str.append(" , "); Z::toString( str ); str.append(" }]"); }
	};
		
	// Add (+)
	template <typename LOP, typename ROP>
	struct Add
	{
		typedef typename BinaryType<typename LOP::Type,typename ROP::Type>::Result Type;

		static HK_FORCE_INLINE hkSimdReal							apply( const hkSimdReal& x, const hkSimdReal& y ) { return x + y; }
		static HK_FORCE_INLINE hkVector4							apply( const hkSimdReal& x, const hkVector4& y ) { hkVector4 r; r.setAll(x); r.add(y); return r; }
		static HK_FORCE_INLINE hkVector4							apply( const hkVector4& x, const hkSimdReal& y ) { hkVector4 r; r.setAdd(x,y); return r; }
		static HK_FORCE_INLINE hkVector4							apply( const hkVector4& x, const hkVector4& y ) { hkVector4 r; r.setAdd(x,y); return r; }
		static HK_FORCE_INLINE hkMatrix3							apply( const hkMatrix3& x, const hkMatrix3& y ) { hkMatrix3 r = x; r.add(y); return r; }
		template <typename EVALUATOR> HK_FORCE_INLINE static Type	eval( const EVALUATOR& evaluator ) { return apply( LOP::eval(evaluator) , ROP::eval( evaluator ) ); }
		static void													toString( hkStringBuf& str ) { str.append("("); LOP::toString( str ); str.append("+"); ROP::toString( str ); str.append(")"); }
	};

	// Sub (-)
	template <typename LOP, typename ROP>
	struct Sub
	{
		typedef typename BinaryType<typename LOP::Type,typename ROP::Type>::Result Type;

		static HK_FORCE_INLINE hkSimdReal							apply( const hkSimdReal& x, const hkSimdReal& y ) { return x - y; }
		static HK_FORCE_INLINE hkVector4							apply( const hkSimdReal& x, const hkVector4& y ) { hkVector4 r; r.setAll(x); r.sub(y); return r; }
		static HK_FORCE_INLINE hkVector4							apply( const hkVector4& x, const hkSimdReal& y ) { hkVector4 r; r.setSub(x,y); return r; }
		static HK_FORCE_INLINE hkVector4							apply( const hkVector4& x, const hkVector4& y ) { hkVector4 r; r.setSub(x,y); return r; }
		template <typename EVALUATOR> HK_FORCE_INLINE static Type	eval( const EVALUATOR& evaluator ) { return apply( LOP::eval(evaluator) , ROP::eval( evaluator ) ); }
		static void													toString( hkStringBuf& str ) { str.append("("); LOP::toString( str ); str.append("-"); ROP::toString( str ); str.append(")"); }
	};

	// Mul (*)
	template <typename LOP, typename ROP>
	struct Mul
	{
		typedef typename BinaryType<typename LOP::Type,typename ROP::Type>::Result Type;

		static HK_FORCE_INLINE hkSimdReal							apply( const hkSimdReal& x, const hkSimdReal& y ) { return x * y; }
		static HK_FORCE_INLINE hkVector4							apply( const hkSimdReal& x, const hkVector4& y ) { hkVector4 r; r.setMul(y,x); return r; }
		static HK_FORCE_INLINE hkVector4							apply( const hkVector4& x, const hkSimdReal& y ) { hkVector4 r; r.setMul(x,y); return r; }
		static HK_FORCE_INLINE hkVector4							apply( const hkVector4& x, const hkVector4& y ) { hkVector4 r; r.setMul(x,y); return r; }
		template <typename EVALUATOR> HK_FORCE_INLINE static Type	eval( const EVALUATOR& evaluator ) { return apply( LOP::eval(evaluator) , ROP::eval( evaluator ) ); }
		static void													toString( hkStringBuf& str ) { str.append("("); LOP::toString( str ); str.append("*"); ROP::toString( str ); str.append(")"); }
	};
	
	// Div (/)
	template <typename LOP, typename ROP>
	struct Div
	{
		typedef typename BinaryType<typename LOP::Type,typename ROP::Type>::Result Type;

		static HK_FORCE_INLINE hkSimdReal							apply( const hkSimdReal& x, const hkSimdReal& y ) { return x / y; }
		static HK_FORCE_INLINE hkVector4							apply( const hkSimdReal& x, const hkVector4& y ) { hkVector4 r; r.setAll(x); r.div(y); return r; }
		static HK_FORCE_INLINE hkVector4							apply( const hkVector4& x, const hkSimdReal& y ) { hkVector4 d; d.setAll(y); hkVector4 r; r.setDiv(x,d); return r; }
		static HK_FORCE_INLINE hkVector4							apply( const hkVector4& x, const hkVector4& y ) { hkVector4 r; r.setDiv(x,y); return r; }
		template <typename EVALUATOR> HK_FORCE_INLINE static Type	eval( const EVALUATOR& evaluator ) { return apply( LOP::eval(evaluator) , ROP::eval( evaluator ) ); }
		static void													toString( hkStringBuf& str ) { str.append("("); LOP::toString( str ); str.append("/"); ROP::toString( str ); str.append(")"); }
	};
	
	// Negate (-)
	template <typename OP>
	struct Neg
	{
		typedef typename OP::Type Type;
		static HK_FORCE_INLINE hkSimdReal							apply( const hkSimdReal& x ) { return -x; }
		static HK_FORCE_INLINE hkVector4							apply( const hkVector4& x ) { hkVector4 r; r.setNeg<3>(x); return r; }
		template <typename EVALUATOR> HK_FORCE_INLINE static Type	eval( const EVALUATOR& evaluator ) { return apply( OP::eval( evaluator ) ); }
		static void													toString( hkStringBuf& str ) { str.append("(-"); OP::toString( str ); str.append(")"); }
	};

	// Power (^)
	template <typename OP, int POWER>
	struct Pow
	{
		typedef typename OP::Type Type;
		template <typename EVALUATOR> HK_FORCE_INLINE static Type	eval( const EVALUATOR& evaluator ) { return hkMath::pow<POWER>( OP::eval( evaluator ) ); }
		static void													toString( hkStringBuf& str ) { str.append("("); OP::toString( str ); str.appendPrintf("^%d)",POWER); }
	};

	// Square root
	template <typename OP>
	struct Sqrt
	{
		typedef typename OP::Type Type;
		template <typename EVALUATOR> HK_FORCE_INLINE static Type	eval( const EVALUATOR& evaluator ) { return hkMath::sqrt( OP::eval( evaluator ) ); }
		static void													toString( hkStringBuf& str ) { str.append("Sqrt["); OP::toString( str ); str.append("]"); }
	};

	// Sine
	template <typename OP>
	struct Sin
	{
		typedef typename OP::Type Type;
		template <typename EVALUATOR> HK_FORCE_INLINE static Type	eval( const EVALUATOR& evaluator ) { return hkMath::sin( OP::eval( evaluator ) ); }
		static void													toString( hkStringBuf& str ) { str.append("Sin["); OP::toString( str ); str.append("]"); }
	};

	// Cosine
	template <typename OP>
	struct Cos
	{
		typedef typename OP::Type Type;
		template <typename EVALUATOR> HK_FORCE_INLINE static Type	eval( const EVALUATOR& evaluator ) { return hkMath::cos( OP::eval( evaluator ) ); }
		static void													toString( hkStringBuf& str ) { str.append("Cos["); OP::toString( str ); str.append("]"); }
	};

	// Cross product
	template <typename LOP, typename ROP>
	struct Cross
	{
		typedef hkVector4 Type;
		template <typename EVALUATOR> HK_FORCE_INLINE static Type	eval( const EVALUATOR& evaluator )
		{
			const hkVector4 l = LOP::eval( evaluator );
			const hkVector4 r = ROP::eval( evaluator );
			hkVector4		c; c.setCross( l, r );
			return c;
		}
		static void													toString( hkStringBuf& str ) { str.append("Cross["); LOP::toString( str ); str.append(","); ROP::toString( str ); str.append("]"); }
	};

	// Dot product.
	template <typename LOP, typename ROP>
	struct Dot
	{
		typedef typename DotType<typename LOP::Type, typename ROP::Type>::Result Type;

		static HK_FORCE_INLINE hkSimdReal							apply( const hkVector4& x, const hkVector4& y ) { return x.dot<3>(y); }
		static HK_FORCE_INLINE hkVector4							apply( const hkMatrix3& x, const hkVector4& y ) { hkVector4 r; x.multiplyVector( y, r ); return r; }
		static HK_FORCE_INLINE hkVector4							apply( const hkVector4& x, const hkMatrix3& y ) { hkMatrix3 t; t._setTranspose(y); hkVector4 r; t.multiplyVector( x, r ); return r; }
		static HK_FORCE_INLINE hkMatrix3							apply( const hkMatrix3& x, const hkMatrix3& y ) { hkMatrix3 r; r._setMul( x, y ); return r; }

		template <typename EVALUATOR> HK_FORCE_INLINE static Type	eval( const EVALUATOR& evaluator ) { return apply( LOP::eval( evaluator ), ROP::eval( evaluator ) ); }
		static void													toString( hkStringBuf& str ) { str.append("Dot["); LOP::toString( str ); str.append(","); ROP::toString( str ); str.append("]"); }
	};

	// Vector norm.
	template <typename OP>
	struct Norm
	{
		typedef hkSimdReal Type;
		template <typename EVALUATOR> HK_FORCE_INLINE static Type	eval( const EVALUATOR& evaluator ) { return OP::eval( evaluator ).length<3,HK_ACC_FULL,HK_SQRT_SET_ZERO>(); }
		static void													toString( hkStringBuf& str ) { str.append("Norm["); OP::toString( str ); str.append("]"); }
	};

	//
	// Constants
	//

	// Pi (Q, approx. 11 decimals).
	typedef Scalar<833719,265381> Scalar_Pi;

	// E (Q, approx. 11 decimals).
	typedef Scalar<1084483,398959> Scalar_E;
	
	// Zero (R3).
	typedef Vector3<Zero,Zero,Zero> Vector3_0;

	// Zero (M3).
	typedef Matrix3<Vector3_0,Vector3_0,Vector3_0> Matrix3_0;

	// Get typed zero.
	template <typename T> struct GetTypedZero {};
	template <> struct GetTypedZero<hkSimdReal> { typedef Zero Result; };
	template <> struct GetTypedZero<hkVector4> { typedef Vector3_0 Result; };
	template <> struct GetTypedZero<hkMatrix3> { typedef Matrix3_0 Result; };
	
	//
	// Helpers.
	//

	// Declare a Scalar variable.
	#define hkFad_ScalarVariable( _type_name_, _string_name_ , _field_name_ ) \
	struct _type_name_ \
	{ \
		typedef hkSimdReal Type; \
		template <typename PARMS> \
		HK_FORCE_INLINE static const hkSimdReal& eval(const PARMS& parms) { return parms. ##_field_name_ ; } \
		static void toString( hkStringBuf& str) { str.append(_string_name_); } \
		template <typename VAR> struct diff { typedef ::hkFad::Zero Result; }; \
	}
	
	// Declare a Vector3 variable (and its individual x,y and z components).
	#define hkFad_Vector3Variable( _type_name_, _string_name_ , _field_name_ ) \
	struct _type_name_\
	{ \
		hkFad_ScalarVariable( x, _string_name_ "x", _field_name_.getComponent<0>() ); \
		hkFad_ScalarVariable( y, _string_name_ "y", _field_name_.getComponent<1>() ); \
		hkFad_ScalarVariable( z, _string_name_ "z", _field_name_.getComponent<2>() ); \
		typedef ::hkFad::Vector3<x,y,z> VectorType; \
		typedef hkVector4 Type; \
		template <typename PARMS> \
		HK_FORCE_INLINE static const hkVector4& eval(const PARMS& parms) { return parms. ##_field_name_ ; } \
		static void toString( hkStringBuf& str) { VectorType::toString( str ); } \
		template <typename VAR> struct diff { typedef typename ::hkFad::DifferentiationRules::Diff<VAR, VectorType >::Result Result; }; \
	}

	// Declare a Matrix3 variable (and its individual X,Y and Z columns).
	#define hkFad_Matrix3Variable( _type_name_, _string_name_ , _field_name_ ) \
	struct _type_name_\
	{ \
		hkFad_Vector3Variable( X, _string_name_ "X", _field_name_.getColumn<0>() ); \
		hkFad_Vector3Variable( Y, _string_name_ "Y", _field_name_.getColumn<1>() ); \
		hkFad_Vector3Variable( Z, _string_name_ "Z", _field_name_.getColumn<2>() ); \
		typedef ::hkFad::Matrix3<X,Y,Z> MatrixType; \
		typedef hkMatrix3 Type; \
		template <typename PARMS> \
		HK_FORCE_INLINE static const hkMatrix3& eval(const PARMS& parms) { return parms. ##_field_name_ ; } \
		static void toString( hkStringBuf& str) { MatrixType::toString( str ); } \
		template <typename VAR> struct diff { typedef typename ::hkFad::DifferentiationRules::Diff<VAR, MatrixType >::Result Result; }; \
	}

	// Declare a Scalar variable and its member.
	#define hkFad_ScalarVariableAndMember( _type_name_, _string_name_ , _field_name_ ) hkSimdReal _field_name_; hkFad_ScalarVariable( _type_name_, _string_name_, _field_name_ )

	// Declare a Vector3 variable (and its individual x,y and z components) as well as its member.
	#define hkFad_Vector3VariableAndMember( _type_name_, _string_name_ , _field_name_ ) hkVector4 _field_name_; hkFad_Vector3Variable( _type_name_, _string_name_, _field_name_)

	// Declare a Matrix3 variable (and its individual X,Y and Z columns) as well as its member.
	#define hkFad_Matrix3VariableAndMember( _type_name_, _string_name_ , _field_name_ ) hkMatrix3 _field_name_; hkFad_Matrix3Variable( _type_name_, _string_name_, _field_name_)
}

#include <Common/Base/Math/ExtendedMath/hkFadDifferentiationRules.h>
#include <Common/Base/Math/ExtendedMath/hkFadSimplificationRules.h>

namespace hkFad
{	
	//
	// Simplify function (basic pattern matching mostly aimed at simplifying Diff output).
	// Keep applying internal simplification rules until the function is unchanged.
	//
	template <typename FUNCTION>
	struct Simplify
	{
		template <typename POP, typename COP>
		struct Recurse
		{
			typedef typename SimplificationRules::Simplify<COP>::Result sOP;
			typedef typename Recurse<COP,sOP>::Result Result;
		};

		template <typename OP>
		struct Recurse<OP,OP>
		{
			typedef OP Result;
		};

		typedef typename Recurse<FUNCTION,typename SimplificationRules::Simplify<FUNCTION>::Result>::Result Result;
	};
		
	//
	// Differentiate function w.r.t. VAR. and simplify the result.
	//
	template <typename VAR, typename FUNCTION>
	struct Diff
	{
		// Differentiate and simplify.
		typedef typename Simplify<typename DifferentiationRules::Diff<VAR,FUNCTION>::Result>::Result	Result;
	};

	//
	// Jacobian of a function w.r.t. VAR.
	//
	
	// f : ? -> ?
	template <typename VAR_TYPE, typename FUNCTION_TYPE, typename VAR, typename FUNCTION> struct BuildJacobian {};

	// f : R -> R
	template <typename VAR, typename FUNCTION> struct BuildJacobian<hkSimdReal,hkSimdReal,VAR,FUNCTION>
	{
		typedef typename Diff<VAR,FUNCTION>::Result				Result;
	};

	// f : R -> R3
	template <typename VAR, typename FUNCTION> struct BuildJacobian<hkSimdReal,hkVector4,VAR,FUNCTION>
	{
		typedef typename Diff<VAR,FUNCTION>::Result				Result;
	};

	// f : R3 -> R
	template <typename VAR, typename FUNCTION> struct BuildJacobian<hkVector4,hkSimdReal,VAR,FUNCTION>
	{
		typedef typename Diff<typename VAR::x,FUNCTION>::Result	dX;
		typedef typename Diff<typename VAR::y,FUNCTION>::Result	dY;
		typedef typename Diff<typename VAR::z,FUNCTION>::Result	dZ;
		typedef Vector3<dX,dY,dZ>								Result;
	};

	// f : R3 -> R3
	template <typename VAR, typename FUNCTION> struct BuildJacobian<hkVector4,hkVector4,VAR,FUNCTION>
	{
		typedef typename Diff<typename VAR::x,FUNCTION>::Result	dX;
		typedef typename Diff<typename VAR::y,FUNCTION>::Result	dY;
		typedef typename Diff<typename VAR::z,FUNCTION>::Result	dZ;
		typedef Matrix3<dX,dY,dZ>								Result;
	};

	//
	template <typename VAR, typename FUNCTION>
	struct Jacobian
	{
		typedef typename BuildJacobian<typename VAR::Type,typename FUNCTION::Type,VAR,FUNCTION>::Result Result;
	};

}

#endif // HK_FAD_MATH_H

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
