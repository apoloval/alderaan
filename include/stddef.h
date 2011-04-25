/*
 *  File        : include/stddef.h
 *  Description : This file provides basic macros and types
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
 
 #ifndef _STDDEF_H
 #define _STDDEF_H
 
 #include "stdint.h"
 
 #define NULL ((void*)0)
 
 #if _ALD_WSIZE == 64
 typedef uint64_t       size_t;
 #else
 typedef uint32_t       size_t;
 #endif
 
 /* Wide-character type. Current implementation considers simple ASCII
  * character. 
  */
 typedef char           wchar_t;
 
 /* Pointer diff type. Current implementation considers integer pointer
  * value.
  */
 typedef uintptr_t      ptrdiff_t;
 
 #endif
 
