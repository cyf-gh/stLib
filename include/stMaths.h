/*

stMaths.h

*/

#ifndef __STLIB_MATHS_H__
#define __STLIB_MATHS_H__

#include <math.h>
#include "defs/stDef.h"

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

namespace stLib {

namespace Math {

static const f32 ST_PI = 3.141592654f;

/***********************************************************************

  Mathematical operations

***********************************************************************/

#define ST_MAX( num1, num2 ) num1 > num2 ? num1 : num2
#define ST_MIN( num1, num2 ) num1 > num2 ? num2 : num1

template<typename digit_type>
static ST_INLINE bool IsEqual( digit_type num1, digit_type num2 ) {
	return num1 == num2;
}

template<>
static ST_INLINE bool IsEqual( f64 num1, f64 num2 ) {
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

/* from id Software */
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

template<typename digit_type>
class stVec2 {

public:
	digit_type x;
	digit_type y;

	typedef digit_type trait_type;
public:
	stVec2 UnitVec() const {
		const digit_type base = inv_sqrt(x * x + y * y);

		return stVec2(x * base, y * base);
	}
	const digit_type Length()  const {
		const digit_type base = inv_sqrt(x * x + y * y);

		return ( !IsEqual( base, 0 ) ) ?
			( 1 / base ) : 0;
	}

	bool IsZero() const { return (IsEqual( x, 0 ) && IsEqual( y, 0 ) ); }

	stVec2 & Take( digit_type dLamda ) {
		x *= lmd;
		y *= lmd;
		return *this;
	}

	static bool	IsNegative(const stVec2 &v1, const stVec2 &v2) {
		return IsEqual(-v1.x, v2.x) && IsEqual(-v1.y, v2.y);
	}

	static bool	IsParallel(const stVec2 &v1, const stVec2 &v2) {
		return (v1.IsZero() || v2.IsZero()) ?
			true : IsEqual(v1.x / v2.x, v1.y / v2.y);
	}

	static bool	IsVertical(const stVec2 &v1, const stVec2 &v2) {
		return IsEqual(GetScalarProduct(v1, v2), 0);
	}

	static digit_type GetIncludeAngle(const stVec2 &v1, const stVec2 &v2) {
		return acos(GetScalarProduct(v1, v2) / (v1.Length() * v2.Length()));
	}

	static digit_type GetScalarProduct(const stVec2 &v1, const stVec2 &v2) {
		return (v1.x * v2.x) + (v1.y * v2.y);
	}

	static stVec2 Add(const stVec2 &v1, const stVec2 &v2) {
		return stVec2(v1.x + v2.x, v1.y + v2.y);
	}
	static stVec2 Sub(const stVec2 &v1, const stVec2 &v2) {
		return stVec2(v1.x - v2.x, v1.y - v2.y);
	}

	stVec2( const stVec2 &v ) { x = v.x; y = v.y; }
	stVec2( const digit_type x, const digit_type y )
		: x( x ), y( y ) { }
	stVec2()
		: x( 0 ), y( 0 ) { }
	virtual	~stVec2() { }
};

/***********************************************************************

  stRect

***********************************************************************/

template<typename digit_type>
class stRect {

public:
	stVec2<digit_type> a;		 // right top vector
	stVec2<digit_type> b; 		 // left bottom vector

public:
	bool IsIntersect(const stRect &r, stRect *pOut) {
		bool isIn = true;
		stRect tmpRect(ST_MAX(b.x, r.b.x), ST_MIN(a.y, r.a.y),
			ST_MIN(b.x, r.b.x), ST_MAX(a.y, r.a.y));

		*pout = (isIn = tmpRect.IsLegal()) ? tmpRect : *pout;
		return isIn;
	}

	bool IsLegal() const {
		return (a.x >= b.x && a.y <= b.y);
	}
	bool IsContain(const stVec2<digit_type> &v) const {
		return (v.x >= b.x && v.y <= b.y &&
			v.x <= a.x && v.y >= a.y);
	}

	stVec2<digit_type> Center() const {
		return stVec2<digit_type>::Add(b, a).Take(0.5);
	}
	const digit_type Width() const { return a.x - b.x; }
	const digit_type Height()const { return b.y - a.y; }

	stRect &FromRECT(const RECT &r) {
		a.x = static_cast<digit_type>(r.right);
		a.y = static_cast<digit_type>(r.top);
		b.x = static_cast<digit_type>(r.left);
		b.y = static_cast<digit_type>(r.bottom);
		return *this;
	}
	RECT ToRECT() {
		return RECT{
			static_cast<long>(b.x), static_cast<long>(a.y),
			static_cast<long>(a.x), static_cast<long>(b.y) };
	}

					stRect( const stRect<digit_type> &r ) { a = r.a; b = r.b; }
					stRect( const stVec2<digit_type> &v1, const stVec2<digit_type> &v2 )
						: a( v1 ), b( v2 ) { }

					stRect( const digit_type x1, const digit_type y1, const digit_type x2, const digit_type y2 )
						: a( x1, y1 ), b( x2, y2 ) { }

					stRect()
						: a(), b() { }

	virtual			~stRect() { }
};

} /* Maths */

} /* stLib */

#endif /* !__STLIB_MATHS_H__ */
