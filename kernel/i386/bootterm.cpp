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

namespace kalderaan { namespace intel386 {

#define SCREEN_COLUMNS			80
#define SCREEN_LINES          25
#define SCREEN_ATTRIBUTE		0x3f
#define SCREEN_ADDR           0xb8000

/* Convert the integer D to a string and save the string in BUF. If
 * BASE is equal to 'd', interpret that D is decimal, and if BASE is
 * equal to 'x', interpret that D is hexadecimal.
 */
static void
itoa(char *buf, int base, int d)
{
   char *p = buf;
   char *p1, *p2;
   unsigned long ud = d;
   int divisor = 10;
  
   /* If %d is specified and D is minus, put `-' in the head.  */
   if (base == 'd' && d < 0)
   {
      *p++ = '-';
      buf++;
      ud = -d;
   }
   else if (base == 'x')
      divisor = 16;

   /* Divide UD by DIVISOR until UD == 0.  */
   do
   {
      int remainder = ud % divisor;
      
      *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
   }
   while (ud /= divisor);

   /* Terminate BUF.  */
   *p = 0;
  
   /* Reverse BUF.  */
   p1 = buf;
   p2 = p - 1;
   while (p1 < p2)
   {
      char tmp = *p1;
      *p1 = *p2;
      *p2 = tmp;
      p1++;
      p2--;
   }
}

class BootTerminal : public ::kalderaan::BootTerminal
{
public:

   BootTerminal() : vmem((unsigned char*) 0xb8000), xpos(0), ypos(0) {}

   /* Write nbytes from data to the stream. */
   virtual void write(void *data, size_t nbytes)
   {
      /* As output stream, this writes the bytes in current cursor position. */
      
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

   virtual void print(char c)
   {
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
         return;
      }

      *(vmem + (xpos + ypos * SCREEN_COLUMNS) * 2) = c & 0xFF;
      *(vmem + (xpos + ypos * SCREEN_COLUMNS) * 2 + 1) = SCREEN_ATTRIBUTE;

      xpos++;
      if (xpos >= SCREEN_COLUMNS)
      goto newline;
   }

   virtual void print(const char *format, ...)
   {
      char **arg = (char **) &format;
      int c;
      char buf[20];

      arg++;
   
      while ((c = *format++) != 0)
      {
         if (c != '%')
            print(c);
         else
         {
            char *p;
      
            c = *format++;
            switch (c)
            {
               case 'd':
               case 'u':
               case 'x':
                  itoa (buf, c, *((int *) arg++));
                  p = buf;
                  goto string;
                  break;
               case 's':
                  p = *arg++;
                  if (! p) p = (char*) "(null)";
                  string: while (*p)
                     print(*p++);
                  break;
               default:
                  print(*((int *) arg++));
                  break;
            }
         }
      }
   }

private:

  uint8_t *vmem;
  int xpos;
  int ypos;  

};

BootTerminal bootTermInstance;

}}; // namespace kalderaan::i386

namespace kalderaan {

BootTerminal&
BootTerminal::instance()
{
   return kalderaan::intel386::bootTermInstance;
}

}; // namespace kaldeaan

#endif

