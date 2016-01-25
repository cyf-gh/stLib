/*

Base class and methods for maths.  Provides 2D vector class, rectangle class.

*/

#ifndef __STLIB_MATHS_H__
#define __STLIB_MATHS_H__

#include <math.h>
#include "..\core\Def.h"

/***********************************************************************

  Maths

***********************************************************************/

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

static const f32 ST_PI = 3.141592654f;

/***********************************************************************

  Mathematical operations

***********************************************************************/

#define ST_MAX( num1, num2 ) num1 > num2 ? num1 : num2
#define ST_MIN( num1, num2 ) num1 > num2 ? num2 : num1

static ST_INLINE bool IsEqualF( f64 num1, f64 num2 ) {
	return fabs( num1 - num2 ) < 0.000001;
}

static ST_INLINE bool IsIn( f64 numMin, f64 numMax, f64 numCmp ) {
	return ( ( numCmp >= numMin ) && ( numMax <= numCmp ) );
}

static ST_INLINE bool IsPositive( f64 dNum ) {
	return ( dNum > 0 );
}

static ST_INLINE f64 Avg( f64 num1, f64 num2 ) {
	return ( num1 + num2 ) / 2;
}

static ST_INLINE f64 Abs( f64 dNum ) {
	return dNum > 0 ? dNum : -dNum;
}

static ST_INLINE n32 Avg( n32 nNum1, n32 nNum2 ) {
	return ( nNum1 >> 1 ) + ( nNum2 >> 1 );
}

static ST_INLINE n32 Half( n32 nNum ) {
	return ( nNum >> 1 );
}

static ST_INLINE n32 Twofold( n32 nNum ) {
	return ( nNum << 1 );
}

static ST_INLINE n32 Opposite( n32 nNum ) {
	return ( ~nNum + 1 );
}

static ST_INLINE n32 Abs( n32 nNum ) {
	const n32 nTmp = ( nNum >> 31 );
	return ( ( nNum ^ nTmp ) - nTmp );
}

/* Quote id Software */
static ST_INLINE f32 inv_sqrt( f32 x ) {
	f32 xhalf = 0.5f * x;
	int i = * ( int * ) &x;
	i = 0x5f3759df - (i >> 1);
	x = *( f32 * ) &i;
	x = x * ( 1.5f - xhalf * x * x);
	return x;
}

/***********************************************************************

  stVec2

***********************************************************************/

class stVec2 {

public:
	f64				x;
	f64				y;

public:
	stVec2			UnitVec() const;
	const f64		Length()  const;
	bool			IsZero()  const			  { return ( IsEqualF( x, 0 ) && IsEqualF( y, 0 ) ); }
	stVec2 &	 	Take( f64 dLamda );

	static bool		IsNegative( const stVec2 &v1, const stVec2 &v2 );
	static bool		IsParallel( const stVec2 &v1, const stVec2 &v2 );
	static bool		IsVertical( const stVec2 &v1, const stVec2 &v2 );
	static f64		GetIncludeAngle( const stVec2 &v1, const stVec2 &v2 );
	static f64		GetScalarProduct( const stVec2 &v1, const stVec2 &v2 );

	static stVec2   Add( const stVec2 &v1, const stVec2 &v2 );
	static stVec2   Sub( const stVec2 &v1, const stVec2 &v2 );

					stVec2( const stVec2 &v ) { x = v.x; y = v.y; }
					stVec2( f64 x, f64 y )
						: x( x ), y( y ) { }
					stVec2()
						: x( 0 ), y( 0 ) { }
	virtual			~stVec2() { }
};

/***********************************************************************

  stRect

***********************************************************************/

class stRect {

public:
	stVec2			a;		 // right top vector
	stVec2			b; 		 // left bottom vector

public:
	bool			IsIntersect( const stRect &r, stRect *pOut );
	bool			IsLegal()					 const;
	bool			IsContain( const stVec2 &v ) const;
	stVec2			Center()					 const;
	const f64		Width()						 const { return a.x - b.y; }
	const f64		Height()					 const { return b.y - a.y; }

	static void		Set( stRect *prect, const RECT &r );
	static RECT		Get( const stRect &rect );

					stRect( const stRect &r ) { a = r.a; b = r.b; }
					stRect( const stVec2& v1, const stVec2& v2 )
						: a( v1 ), b( v2 ) { }
					stRect( const f64 x1, const f64 y1, const f64 x2, const f64 y2 )
						: a( x1, y1 ), b( x2, y2 ) { }
					stRect()
						: a(), b() { }
	virtual			~stRect();
};

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

ST_INLINE void stRect::Set( stRect *rect, const RECT &r ) {
	rect->a.x = r.right;
	rect->a.y = r.top;
	rect->b.x = r.left;
	rect->b.y = r.bottom;
}

ST_INLINE RECT stRect::Get( const stRect &rect ) {
	return RECT{ ( long )rect.b.x, ( long )rect.a.y, ( long )rect.a.x, ( long )rect.b.y };
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
