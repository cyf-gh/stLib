//
// Created by caoyifan on 8/9/18.
//

#ifndef STLIB_STMEM_H
#define STLIB_STMEM_H

#include <malloc.h>
#include <utility>
#include <unordered_map>
#include <vector>
#include "_stdefs.h"

namespace_stLib_Mem {

	template<typename T> ST_INLINE static T *st_new() { return new T; }
	template<typename T> ST_INLINE static void st_delete( T **pt ) { st_safe_del( *pt ); }

class stAllocator {
private:
	struct ptr_compare {
		bool operator()( void * const& a, void * const& b ) const {
			return ( a == b );
		}
	};	
	struct ptr_hash {
		size_t operator()( void * const& p ) const {
			return reinterpret_cast<size_t>(p);
		}
	};
	std::unordered_map<void *, un32, ptr_hash, ptr_compare> ptrs_using;
	std::vector<std::pair<void *, un32>> ptrs_usable;

	void * toUsable( std::pair<void *, un32> tpair ) {
		ptrs_usable.push_back( tpair );
		ptrs_using.erase( tpair.first );
		return static_cast<void *>( tpair.first );
	}
	void * toUsing( const un32 usableIndex, std::pair<void *, un32> tpair ) {
		ptrs_using.insert(tpair);
		ptrs_usable.erase( ptrs_usable.begin() + usableIndex );
		return static_cast<void *>( tpair.first );
	}
public:
	template<typename T> 
	ST_INLINE void DeleteArr( T **pp ) { 
		if ( IsAlloced( *pp ) ) {
			toUsable( std::pair<void *, un32>( static_cast<void *>( *pp ), ptrs_using[static_cast<void *>( *pp )] ) );
			return;
		} else {
			st_safe_del_arr( *pp );
		} 
	}
	template<typename T>
	ST_INLINE T *NewArr( const un32 objNum ) { 
		T *p = nullptr;
		
		// try to get usable pointer
		for ( un32 i = 0; i < ptrs_usable.size(); ++i ) {
			if ( ptrs_usable.at( i ).second >= objNum ) {
				return static_cast<T *>( toUsing( i, ptrs_usable.at( i ) ) );
			}
		}
		p = new T[objNum];
		ptrs_using.insert( std::make_pair(static_cast<void *>(p), objNum ) );
		return p; 
	}
	template<typename type>
	un32 msizeOf( type *pt ) {
		return ptrs_using[ static_cast<void *>( pt ) ];
	}

	template<typename type>
	bool IsAlloced( type *pt ) {
		return ptrs_using[ static_cast<void *>( pt ) ];
	}
};

static stAllocator st_allocator;

} // stLib_Mem
#endif //STLIB_STMEM_H
