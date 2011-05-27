/*
 *  File        : kernel/mem.h
 *  Description : This file implements kernel memory management
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

#ifndef _MEM_H_
#define _MEM_H_

#include <stddef.h>

#define MAX_MEM_HOLES 512

namespace kalderaan
{

/* Return the length of a null-terminated string. */
/* TODO: This function is a good candidate to be moved to string.h. */
size_t strlen(const char *str);

/* Memory manager class. This class manages the system memory, allocating
 * blocks for kernel and user-space processes. 
 */
class MemoryManager
{
public:

   /* Hole owner. */
   enum HoleOwner
   {
      KERNEL_STATIC,
      KERNEL_HEAP,
      KERNEL_MODULE,
      USERSPACE_PROCESS,
   };

   /* Memory hole, i.e. a region of memory available. */
   struct Hole
   {
      uint32_t base;
      size_t length;
      HoleOwner owner;
      Hole *next;
   };

   //! Obtain singleton instance
   MemoryManager &instance();
   
   /* Register a new hole. */
   void registerHole(uint32_t base, size_t len);

private:

   /* Singleton instance. */
   static MemoryManager mSingleton;
   
   /* Private constructor. */
   MemoryManager();

   /* Memory holes. */
   Hole mHoles[MAX_MEM_HOLES];
   
   /* Pointer to the free mem holes. */
   Hole *mFree;
   
   /* Pointer to the used mem holes. */
   Hole *mUsed;
   
   /* Pointer to the unasigned mem holes. */
   Hole *mUnassigned;

};
 
}; // namespace kalderaan

#endif

