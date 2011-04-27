/*
 *  File        : kernel/i386/bootterm.h
 *  Description : This file provides the implementation for i386 boot 
 *                terminal. See <kernel/streams.h> for more details. 
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

#ifndef _I386_BOOTTERM_H_
#define _I386_BOOTTERM_H_

#include <streams.h>
#include <stdint.h>
#include <cpp-runtime.h>

namespace kalderaan { namespace intel386 {

#define SCREEN_COLUMNS			80
#define SCREEN_LINES          25
#define SCREEN_ATTRIBUTE		0x3f
#define SCREEN_ADDR           0xb8000

class BootTerminal : public ::kalderaan::BootTerminal
{
public:

   BootTerminal() : vmem((unsigned char*) 0xb8000), xpos(0), ypos(0) {}

   /* Write nbytes from data to the stream. */
   virtual void write(const void *data, size_t nbytes)
   {
      const char *p = (const char*) data;
      for (size_t i = 0; i < nbytes; i++)
      {
         char c = *p++;
         if (c == '\n' || c == '\r')
         {
            newline:
            xpos = 0;
            ypos++;
            if (ypos >= SCREEN_LINES)
            {
               for (int i = SCREEN_COLUMNS * 2; 
                    i < SCREEN_COLUMNS * SCREEN_LINES * 2; i += 2)
               {
                  *(vmem + i - SCREEN_COLUMNS * 2) = *(vmem + i);
                  *(vmem + i - SCREEN_COLUMNS * 2 + 1) = *(vmem + i + 1);
               }
               for (int i = SCREEN_COLUMNS * (SCREEN_LINES - 1) * 2; 
                    i < SCREEN_COLUMNS * SCREEN_LINES * 2; i += 2)
               {
                  *(vmem + i) = 0;
                  *(vmem + i + 1) = SCREEN_ATTRIBUTE;
               }
               ypos--;      
            }
            continue;
         }
         *(vmem + (xpos + ypos * SCREEN_COLUMNS) * 2) = c & 0xff;
         *(vmem + (xpos + ypos * SCREEN_COLUMNS) * 2 + 1) = SCREEN_ATTRIBUTE;

         xpos++;
         if (xpos >= SCREEN_COLUMNS)
            goto newline;
      }   
   }


   virtual void clear()
   {
      for (int i = 0; i < SCREEN_COLUMNS * SCREEN_LINES * 2; i += 2)
      {
         *(vmem + i) = 0;
         *(vmem + i + 1) = SCREEN_ATTRIBUTE;
      }

      xpos = 0;
      ypos = 0;
   }

private:

  uint8_t *vmem;
  int xpos;
  int ypos;  

};

static uint8_t bootTermMem[sizeof(BootTerminal)];
static BootTerminal *bootTermInstance = 0;


}}; // namespace kalderaan::i386

namespace kalderaan {

BootTerminal&
BootTerminal::instance()
{
   using namespace ::kalderaan::intel386;
   if (!bootTermInstance)
   {
      bootTermInstance = new ((void*) bootTermMem) intel386::BootTerminal();
   }
   return *bootTermInstance;
}

}; // namespace kaldeaan

#endif

