//
// Created by caoyifan on 8/9/18.
//

#ifndef STLIB_STMEM_H
#define STLIB_STMEM_H

#include <malloc.h>
#include <utility>
#include <unordered_map>
#include "stDef.h"

namespace stLib_Mem {

	template<typename T> ST_INLINE static T *st_new() { return new T; }
	template<typename T> ST_INLINE static void st_delete( T **pt ) { st_safe_del( *pt ); }

	namespace Pointer_Infos {
		struct ptr_compare{
			bool operator()( void * const& a, void * const& b ) const {
				return ( a == b );
			}
		};	
		struct ptr_hash{
			size_t operator()( void * const& p ) const {
				return reinterpret_cast<size_t>(p);
			}
		};
		static std::unordered_map<void *, un32, ptr_hash, ptr_compare> map_pointer_infos;
	
	}
	template<typename T> 
	ST_INLINE static T *st_new( const un32 objNum ) { 
		T *p = new T[ objNum ];

		// Pointer_Infos::map_pointer_infos.insert( std::unordered_map<void *, un32>::value_type( static_cast<void *>( p ), objNum ) );
		Pointer_Infos::map_pointer_infos[static_cast<void *>( p )] = objNum;
		return p; 
	}

	template<typename T> 
	ST_INLINE static void st_delete_arr( T **pp ) { 
		Pointer_Infos::map_pointer_infos.erase( static_cast<void *>( *pp ) );
		st_safe_del_arr( *pp ); 
	}

	template<typename type>
	static un32 st_msize( type *pt ) {
		return Pointer_Infos::map_pointer_infos[ static_cast<void *>( pt ) ];
	}

	template<typename type>
	static bool st_is_alloced_pt( type *pt ) {
		return Pointer_Infos::map_pointer_infos[ static_cast<void *>( pt ) ];
	}
} // stLib_Mem
#endif //STLIB_STMEM_H
