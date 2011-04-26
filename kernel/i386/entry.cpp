/*
 *  File        : kernel/i386/entry.cpp
 *  Description : This file provides code for the entry point of the kernel.
 *                It is supported by a multiboot boot manager, so it depends
 *                on i386 architecture. The main objective of this code is
 *                to prepare the kernel initiatization by abstracting the
 *                resource management in objects implementing abstract classes.
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

#include <stdint.h>
#include <streams.h>
#include <i386/multiboot.h>

/* Kernel entry point is declared as a C-function to make it easier to
 * be invoked from assembler code. 
 */
extern "C" void kernelEntryPoint(uint32_t magic, struct BootInfo *bi);

void
kernelEntryPoint(uint32_t magic, struct BootInfo *bi)
{
   using namespace kalderaan;
   
   BootTerminal &term = BootTerminal::instance();
   term.print("Booting Alderaan operating system... \n");
}


