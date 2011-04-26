/*
 *  File        : kernel/config.h
 *  Description : This file provides configuration parameters for building
 *                Alderaan kernel
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
 
 #ifndef _CONFIG_H
 #define _CONFIG_H
 
 #define KERNEL_MAJOR_VERSION 0
 #define KERNEL_MINOR_VERSION 1
 
 /* The following constant indicates a verbose booting process (1) or a 
  * silent one (0)
  */
 #ifndef KERNEL_VERBOSE
 #define KERNEL_VERBOSE 1
 #endif
 
 /* The following constant indicates the kernel stack size. */
 #ifndef KERNEL_STACK_SIZE
 #define KERNEL_STACK_SIZE 0x4000 
 #endif
 
 #endif
 
