#pragma once

#define EXPORTED __declspec ( dllexport )
#define NAKED __declspec ( naked )

#ifdef _MSC_VER
#define ALWAYS_INLINE __forceinline
#else
#define ALWAYS_INLINE __attribute__ ( ( always_inline ) ) inline
#endif

namespace __sdk_constant_holder { template < auto _value > inline constexpr auto k_value = _value; }

#define CONSTANT( constant ) __sdk_constant_holder::k_value< constant >

#define INSERT_ENUM_UNDERLYING_OPERATOR( enum_t ) \
	ALWAYS_INLINE constexpr auto operator -( const enum_t value ) { \
		return static_cast< std::underlying_type_t< enum_t > >( value ); \
	} \

#define INSERT_ENUM_BIT_OPERATOR( enum_t, operand, ret_underlying ) \
	ALWAYS_INLINE constexpr auto operator operand( const enum_t lhs, const enum_t rhs ) { \
		using underlying_t = std::underlying_type_t< enum_t >; \
		\
		using ret_t = std::conditional_t< ret_underlying, underlying_t, enum_t >; \
		\
		return static_cast< ret_t >( \
			static_cast< underlying_t >( lhs ) operand static_cast< underlying_t >( rhs ) \
		); \
	} \
	\
	ALWAYS_INLINE auto& operator operand##=( enum_t& lhs, const enum_t rhs ) { \
		using underlying_t = std::underlying_type_t< enum_t >; \
		\
		using ret_t = std::conditional_t< ret_underlying, underlying_t, enum_t >; \
		\
		return reinterpret_cast< ret_t& >( \
			reinterpret_cast< underlying_t& >( lhs ) operand##= static_cast< underlying_t >( rhs ) \
		); \
	} \

#define INSERT_ENUM_BIT_OPERATORS( enum_t, ret_underlying ) \
	INSERT_ENUM_BIT_OPERATOR( enum_t, |, ret_underlying ) \
	\
	INSERT_ENUM_BIT_OPERATOR( enum_t, &, ret_underlying ) \
	\
	INSERT_ENUM_BIT_OPERATOR( enum_t, ^, ret_underlying ) \
	\
	ALWAYS_INLINE constexpr auto operator ~( const enum_t value ) { \
		using underlying_t = std::underlying_type_t< enum_t >; \
		\
		using ret_t = std::conditional_t< ret_underlying, underlying_t, enum_t >; \
		\
		return static_cast< ret_t >( ~static_cast< underlying_t >( value ) ); \
	} \

#if defined( _WIN32 ) || defined( _WIN64 )
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#endif

#include <intrin.h>

#include <fstream>
#include <array>
#include <vector>
#include <deque> /* fuck these no ptr stable niggers */
#include <thread>
#include <algorithm>
#include <functional>
#include <optional>
#include <filesystem>
#include <type_traits>

#include <json.hpp>

#include "src/mem/mem.hpp"
#include "src/util/util.hpp"
#include "src/math/math.hpp"

#include "src/cfg/cfg.hpp"