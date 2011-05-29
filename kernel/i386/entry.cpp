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
#include <config.h>

/* Kernel entry point is declared as a C-function to make it easier to
 * be invoked from assembler code. 
 */
extern "C" void kernelEntryPoint(uint32_t magic, struct BootInfo *bi);

/* External symbols provided by linker. They indicate the addresses where
 * constructos and destructors start and ends, respectively. 
 */
extern uint32_t start_ctors, end_ctors, start_dtors, end_dtors;
extern uint32_t lma_kstart; //, kstack;

#define FLAG_ENABLED(flags, bit) ((flags) & (1 << (bit)))

void
kernelEntryPoint(uint32_t magic, struct BootInfo *bi)
{
   using namespace kalderaan;
   
   /* Prepare the kernel page tables. This action cannot be executed from
    * a C++ class since all they are mapped to 0xc0000000. Memory paging
    * must be enabled before accesing any C++ code. */
   /* TODO: write the code! */
   uint32_t *pdir = (uint32_t*) 0x10000;
   uint32_t *ptab1 = (uint32_t*) 0x11000;
   uint32_t *ptab2 = (uint32_t*) 0x12000;
   
   // Clear directory and tables filling with zeroes
   for (int i = 0; i < 1024; i++)
      pdir[i] = ptab1[i] = ptab2[i] = 0x2;
   
   // Make 1:1 translation for memory under 2MB
   for (int i = 0; i < 512; i++)
      ptab1[i] = (0x1000 * i) | 0x3;
   
   // Make translation to kernel memory
   for (int i = 0; i < 1024; i++)
      ptab2[i] = (((uint32_t) &lma_kstart) + (i * 0x1000)) | 0x3;
      
   // Prepare the page directory
   pdir[0]     = ((uint32_t) ptab1) | 0x3;
   pdir[0x300] = ((uint32_t) ptab2) | 0x3;
   
   // Enable paging
   asm volatile("mov %0, %%cr3;" :: "r"(pdir));
   uint32_t cr0;
   asm volatile("mov %%cr0, %0;" : "=r"(cr0));
   cr0 |= 0x80000001;
   asm volatile("mov %0, %%cr0;" :: "r"(cr0));

   // Invoke constructors for each static variable of the kernel image
   for(uint32_t *cons(&start_ctors); cons < &end_ctors; ++cons)
     ((void(*)(void)) (*cons))();
   
   // Prepare the boot terminal
   BootTerminal &term = BootTerminal::instance();
   term.clear();

   // Print the welcome message
   StringPrinter tp(&term);
   tp.print("Booting Alderaan operating system v%d.%d... \n",
      KERNEL_MAJOR_VERSION,
      KERNEL_MINOR_VERSION);
   
   if (FLAG_ENABLED(bi->flags, 6))
   {
      tp.print("Loading memory map... \n");
      MemoryMapEntry *mmap;
           
      for (mmap = (MemoryMapEntry*) bi->memMapAddr;
           (unsigned long) mmap < bi->memMapAddr + bi->memMapLen;
           mmap = (MemoryMapEntry*) ((unsigned long) mmap
                                         + mmap->size + sizeof (mmap->size)))
      {
         if (mmap->type == 1)
            tp.print("   Memory hole at 0x%x (%d bytes)\n", 
                     mmap->addrLow, mmap->lenLow);
      }
   }
   else
   {
      tp.print("Warning: no memory map available\n");
   }
      
   // TODO: continue kernel loading
   for (;;) {}
}


