/// \brief Base class and methods for maths.  Provides 2D vector class, rectangle class.
#ifndef __STLIB_MATHS_H__
#define __STLIB_MATHS_H__

#include <math.h>
#include "..\core\Def.h"

/// \defgroup maths Stuff Maths
/// \brief Mathematical operations.
/// \{
#ifndef _ST_PLATFORM_WIN32
typedef struct _RECT {
	n32		left;
	n32		top;
	n32		right;
	n32		bottom;
} RECT;
#endif /* !_ST_PLATFORM_WIN32 */

namespace stLibUtils {

namespace Maths {

static const f32 ST_PI = 3.141592654f; ///< \brief Circumference ratio.

/// \brief		Gets bigger one.
/// \param num1 Number1.
/// \param num2 Number2.
#define ST_MAX( num1, num2 ) num1 > num2 ? num1 : num2

/// \brief		Gets smaller one.
/// \param num1 Number1.
/// \param num2 Number2.
#define ST_MIN( num1, num2 ) num1 > num2 ? num2 : num1

/// \brief			Checks whether two double number is equal.
/// \note			The offset is 0.000001.
/// \param[in] num1 Number1.
/// \param[in] num2 Number2.
/// \return			Is two double number equal.
static ST_INLINE bool IsEqualF( f64 num1, f64 num2 ) {
	return fabs( num1 - num2 ) < 0.000001;
}

/// \brief			  Is a number in the range.
/// \param[in] numMin Left.
/// \param[in] numMax Right.
/// \param[in] numCmp Number to compare.
/// \return			  Is numCmp in range.
static ST_INLINE bool IsIn( f64 numMin, f64 numMax, f64 numCmp ) {
	return ( ( numCmp >= numMin ) && ( numMax <= numCmp ) );
}

/// \brief	   Is a number positive.
/// \param[in] dNum Number to check.
/// \return	   Is dNum positive.
static ST_INLINE bool IsPositive( f64 dNum ) {
	return ( dNum > 0 );
}

/// \brief			Gets average value of two numbers.
/// \param[in] num1 Number1.
/// \param[in] num2 Number2.
/// \return			Average number.
static ST_INLINE f64 Avg( f64 num1, f64 num2 ) {
	return ( num1 + num2 ) / 2;
}

/// \brief			Get the absolute value.
/// \param[in]	num Number.
/// \return			Taken absolute value.
static ST_INLINE f64 Abs( f64 num ) {
	return num > 0 ? num : -num;
}

/// \brief			Gets average value of two integer.
/// \param[in] num1 Number1.
/// \param[in] num2 Number2.
/// \return			Average number.
static ST_INLINE n32 Avg( n32 num1, n32 num2 ) {
	return ( num1 >> 1 ) + ( num2 >> 1 );
}

/// \brief			Gets half of a integer.
/// \param[in] num	Number.
/// \return			Taken half number.
static ST_INLINE n32 Half( n32 num ) {
	return ( num >> 1 );
}

/// \brief			Gets two fold of a integer.
/// \param[in] num	Number.
/// \return			Taken two fold number.
static ST_INLINE n32 Twofold( n32 num ) {
	return ( num << 1 );
}

/// \brief			Gets opposite number of one.
/// \param[in] num	Number.
/// \return			Taken opposite number.
static ST_INLINE n32 Opposite( n32 num ) {
	return ( ~num + 1 );
}

/// \brief			Get the absolute value.
/// \param[in]	num Number.
/// \return			Using absolute value.
static ST_INLINE n32 Abs( n32 num ) {
	const n32 nTmp = ( num >> 31 );
	return ( ( num ^ nTmp ) - nTmp );
}

/// \brief Get Inverted sqrt of a digit.
/// \note  3X faster than the one in C std.
/// \quote id Software(Copyright)
static ST_INLINE f32 inv_sqrt( f32 x ) {
	f32 xhalf = 0.5f * x;
	int i = * ( int * ) &x;
	i = 0x5f3759df - (i >> 1);
	x = *( f32 * ) &i;
	x = x * ( 1.5f - xhalf * x * x);
	return x;
}

/// \brief 2D vector
class stVec2 {

public:
	f64				x;  ///< \brief x
	f64				y;  ///< \brief y

public:
	stVec2			UnitVec() const;
	const f64		Length()  const;
	bool			IsZero()  const			  { return ( IsEqualF( x, 0 ) && IsEqualF( y, 0 ) ); }

	/// \brief			  Vector take operation.
	/// \param[in] dLamda Lamda.
	/// \return			  this pointer.
	stVec2 &Take( f64 dLamda );

	static bool		IsNegative( const stVec2 &v1, const stVec2 &v2 );
	static bool		IsParallel( const stVec2 &v1, const stVec2 &v2 );
	static bool		IsVertical( const stVec2 &v1, const stVec2 &v2 );
	static f64		GetIncludeAngle( const stVec2 &v1, const stVec2 &v2 );
	static f64		GetScalarProduct( const stVec2 &v1, const stVec2 &v2 );

	static stVec2   Add( const stVec2 &v1, const stVec2 &v2 );
	static stVec2   Sub( const stVec2 &v1, const stVec2 &v2 );

					stVec2( const stVec2 &v ) { x = v.x; y = v.y; }
					stVec2( const f64 x, const f64 y )
						: x( x ), y( y ) { }
					stVec2()
						: x( 0 ), y( 0 ) { }
	virtual			~stVec2() { }
};

/// \brief Pixel rect.
class stRect {

public:
	stVec2			a;		 ///< \brief right top vector
	stVec2			b; 		 ///< \brief left bottom vector

public:
	bool			IsIntersect( const stRect &r, stRect *pOut );
	bool			IsLegal()					 const; /// <brief Is the rect exist.
	bool			IsContain( const stVec2 &v ) const;
	stVec2			Center()					 const;
	const f64		Width()						 const { return a.x - b.y; }
	const f64		Height()					 const { return b.y - a.y; }

	stRect &		FromRECT( const RECT &r );
	RECT			ToRECT();

					stRect( const stRect &r ) { a = r.a; b = r.b; }
					stRect( const stVec2 &v1, const stVec2 &v2 )
						: a( v1 ), b( v2 ) { }
					stRect( const f64 x1, const f64 y1, const f64 x2, const f64 y2 )
						: a( x1, y1 ), b( x2, y2 ) { }
					stRect()
						: a(), b() { }
					~stRect() { }
};
/// \}

ST_INLINE stVec2 &stVec2::Take( f64 lmd ) {
	x *= lmd;
	y *= lmd;
	return *this;
}

ST_INLINE stVec2 stVec2::Add( const stVec2 &v1, const stVec2 &v2 ) {
	return stVec2( v1.x + v2.x, v1.y + v2.y );
}

ST_INLINE stVec2 stVec2::Sub( const stVec2 &v1, const stVec2 &v2 ) {
	return stVec2( v1.x - v2.x, v1.y - v2.y );
}

ST_INLINE bool stVec2::IsNegative( const stVec2 &v1, const stVec2 &v2 ) {
	return IsEqualF( -v1.x, v2.x ) && IsEqualF( -v1.y, v2.y );
}

ST_INLINE bool stVec2::IsParallel( const stVec2 &v1, const stVec2 &v2 ) {
	return ( v1.IsZero() || v2.IsZero() ) ?
		true : IsEqualF( v1.x / v2.x, v1.y / v2.y );
}

ST_INLINE bool stVec2::IsVertical( const stVec2 &v1, const stVec2 &v2 ) {
	return IsEqualF( GetScalarProduct( v1, v2 ), 0 );
}

ST_INLINE f64 stVec2::GetIncludeAngle( const stVec2 &v1, const stVec2 &v2 ) {
	return acos( GetScalarProduct( v1, v2 ) / ( v1.Length() * v2.Length() ) );
}

ST_INLINE f64 stVec2::GetScalarProduct( const stVec2 &v1, const stVec2 &v2 ) {
	return ( v1.x * v2.x ) + ( v1.y * v2.y );
}

ST_INLINE stVec2 stVec2::UnitVec() const {
	const f64 base = inv_sqrt( x * x + y * y );

	return stVec2( x * base, y * base );
}

ST_INLINE const f64	stVec2::Length() const {
	const f64 base = inv_sqrt( x * x + y * y );

	return ( !IsEqualF( base , 0 ) ) ?
		( 1 / base ) : 0;
}

ST_INLINE stRect &stRect::FromRECT( const RECT &r ) {
	a.x = static_cast<f64>( r.right );
	a.y = static_cast<f64>( r.top );
	b.x = static_cast<f64>( r.left );
	b.y = static_cast<f64>( r.bottom );
	return *this;
}

ST_INLINE RECT stRect::ToRECT() {
	return RECT{ 
		static_cast<long>( b.x ), static_cast<long>( a.y ), 
		static_cast<long>( a.x ), static_cast<long>( b.y ) };
}

ST_INLINE bool stRect::IsLegal() const {
	return ( a.x >= b.x && a.y <= b.y );
}

ST_INLINE bool stRect::IsContain( const stVec2 &v ) const {
	return ( v.x >= b.x && v.y <= b.y &&
		     v.x <= a.x && v.y >= a.y );
}

ST_INLINE stVec2 stRect::Center() const {
	return stVec2::Add( b, a ).Take( 0.5 );
}

ST_INLINE bool stRect::IsIntersect( const stRect &r, stRect *pout ) {
	bool isIn = true;
	stRect tmpRect( ST_MAX( b.x, r.b.x ), ST_MIN( a.y, r.a.y ),
                    ST_MIN( b.x, r.b.x ), ST_MAX( a.y, r.a.y ) );

	*pout = ( isIn = tmpRect.IsLegal() ) ? tmpRect : *pout;
	return isIn;
}

} /* Maths */

} /* stLibUtils */

#endif /* !__STLIB_MATHS_H__ */
