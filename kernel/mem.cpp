/*
 *  File        : kernel/mem.cpp
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

#include <mem.h> 

namespace kalderaan {

/* Return the length of a null-terminated string. */
size_t
strlen(const char *str)
{
   int l = 0;
   char c;
   
   while ((c = *str++) != 0)
      l++;
   return l;
}

void
MemoryManager::registerHole(uint32_t base, size_t len)
{
   Hole *tmp = mUnassigned->next;
   
   mUnassigned->base = base;
   mUnassigned->length = len;
   mUnassigned->next = mFree;
   
   mFree = mUnassigned;
   mUnassigned = tmp;
}

MemoryManager MemoryManager::mSingleton;

MemoryManager::MemoryManager()
 : mFree(0), mUsed(0), mUnassigned(mHoles)
{
   for (int i = 0; i < MAX_MEM_HOLES - 1; i++)
      mHoles[i].next = &mHoles[i + 1];
   mHoles[MAX_MEM_HOLES - 1].next = 0;
}
 
}; // namespace kalderaan

