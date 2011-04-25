/*
 *  File        : include/stdint.h
 *  Description : This file provides declarations for integer types as
 *                specified by C99 standard, section 7.18.
 *  Author      : Alvaro Polo <apoloval@gmail.com>
 *
 *  Revisions   :
 *
 *  Copyright (C) 2011 Alvaro Polo Valdenebro
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
 
#ifndef _STDINT_H
#define _STDINT_H
 
// Check architecture word size 
#ifdef __LP64__
#define _ALD_WSIZE 64
#else
#define _ALD_WSIZE 32
#endif

// Declarations for exact-width integer types 
typedef char               int8_t;
typedef unsigned char      uint8_t;
typedef short              int16_t;
typedef unsigned short     uint16_t;
typedef int                int32_t;
typedef unsigned int       uint32_t;
#if _ALD_WSIZE == 64
typedef long long          int64_t;
typedef unsigned long long uint64_t;
#endif

#define INT8_MAX           127
#define INT8_MIN           -128
#define UINT8_MAX          255
#define INT16_MAX          32767
#define INT16_MIN          -32768
#define UINT16_MAX         65535
#define INT32_MAX          2147483647
#define INT32_MIN          -2147483648
#define UINT32_MAX         4294967295
#if _ALD_WSIZE == 64
#define INT64_MAX          9223372036854775807LL
#define INT64_MIN          9223372036854775808LL
#define UINT64_MAX         18446744073709551615LL
#endif

// Declarations for minimum-width integer types
typedef int8_t             int_least8_t;
typedef uint8_t            uint_least8_t;
typedef int16_t            int_least16_t;
typedef uint16_t           uint_least16_t;
typedef int32_t            int_least32_t;
typedef uint32_t           uint_least32_t;
#if _ALD_WSIZE == 64
typedef int64_t            int_least64_t;
typedef uint64_t           uint_least64_t;
#endif

#define INT_LEAST8_MAX     INT8_MAX
#define INT_LEAST8_MIN     INT8_MIN
#define UINT_LEAST8_MAX    UINT8_MAX
#define INT_LEAST16_MAX    INT16_MAX
#define INT_LEAST16_MIN    INT16_MIN
#define UINT_LEAST16_MAX   UINT16_MAX
#define INT_LEAST32_MAX    INT32_MAX
#define INT_LEAST32_MIN    INT32_MIN
#define UINT_LEAST32_MAX   UINT32_MAX
#if _ALD_WSIZE == 64
#define INT_LEAST64_MAX    INT64_MAX
#define INT_LEAST64_MIN    INT64_MIN
#define UINT_LEAST64_MAX   UINT64_MAX
#endif

/* Declarations for fastest minimum-width integer types. This
 * implementation considers that fast and non-fast minumum-width
 * are the same
 */
typedef int8_t             int_fast8_t;
typedef uint8_t            uint_fast8_t;
typedef int16_t            int_fast16_t;
typedef uint16_t           uint_fast16_t;
typedef int32_t            int_fast32_t;
typedef uint32_t           uint_fast32_t;
#if _ALD_WSIZE == 64
typedef int64_t            int_fast64_t;
typedef uint64_t           uint_fast64_t;
#endif

#define INT_FAST8_MAX      INT8_MAX
#define INT_FAST8_MIN      INT8_MIN
#define UINT_FAST8_MAX     UINT8_MAX
#define INT_FAST16_MAX     INT16_MAX
#define INT_FAST16_MIN     INT16_MIN
#define UINT_FAST16_MAX    UINT16_MAX
#define INT_FAST32_MAX     INT32_MAX
#define INT_FAST32_MIN     INT32_MIN
#define UINT_FAST32_MAX    UINT32_MAX
#if _ALD_WSIZE == 64
#define INT_FAST64_MAX     INT64_MAX
#define INT_FAST64_MIN     INT64_MIN
#define UINT_FAST64_MAX    UINT64_MAX
#endif

// Integer values big enough to hold pointers
#if _ALD_SIZE == 64
typedef int64_t            intptr_t;
typedef uint64_t           uintptr_t;

#define INTPTR_MAX         INT64_MAX
#define INTPTR_MIN         INT64_MIN
#define UINTPTR_MAX        UINT64_MAX

#else
typedef int32_t            intptr_t;
typedef uint32_t           uintptr_t;

#define INTPTR_MAX         INT32_MAX
#define INTPTR_MIN         INT32_MIN
#define UINTPTR_MAX        UINT32_MAX

#endif

// Greatest-width integer types
#if _ALD_SIZE == 64
typedef int64_t            intmax_t;
typedef uint64_t           uintmax_t;

#define INTMAX_MAX         INT64_MAX
#define INTMAX_MIN         INT64_MIN
#define UINTMAX_MAX        UINT64_MAX

#else
typedef int32_t            intmax_t;
typedef uint32_t           uintmax_t;

#define INTMAX_MAX         INT32_MAX
#define INTMAX_MIN         INT32_MIN
#define UINTMAX_MAX        UINT32_MAX

#endif


#endif
 
