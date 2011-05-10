/*
 *  File        : kernel/i386/boot.S
 *  Description : This file provides assembler code for booting from
 *                a multiboot-compliant boot loader
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

#include <config.h>
#include <i386/multiboot.h>

#define MBOOT_H_FLAGS (MBOOT_H_INCMEM | MBOOT_H_INCMEM | MBOOT_H_IMGPAR)


            .text
            .globl      _start
_start:      jmp         skipHeader

            .align 4
mbootHeader:
            .long       MULTIBOOT_HEADER_MAGIC
            .long       MBOOT_H_FLAGS
            .long       -(MULTIBOOT_HEADER_MAGIC + MBOOT_H_FLAGS)
            .long       mbootHeader
            .long       start_text
            .long       end_data
            .long       end_bss
            .long       skipHeader

skipHeader: 
            /* Configure the stack */
            movl        $(kstack + KERNEL_STACK_SIZE), %esp
            
            /* Reset EFLAGS by pushing and poping an arbitrary value. */
            pushl       $0
            popf
            
            /* Push boot info and magic values for kernel init. */
            pushl       %ebx
            pushl       %eax

            call        kernelEntryPoint
            
loop:
            /* kernelEntryPoint() must never return. Halt the machine in
             * such a case */
            hlt
            jmp         loop
            
            
            /* Stack declaration. */
            .comm       kstack, KERNEL_STACK_SIZE


