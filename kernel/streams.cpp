/*
 *  File        : kernel/streams.cpp
 *  Description : This file provides abstract classes representing data
 *                streams and utility classes for support input and output..
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

#include <streams.h>

#include <stdint.h>
#include <mem.h>

namespace kalderaan {

/* Convert the integer D to a string and save the string in BUF. If
 * BASE is equal to 'd', interpret that D is decimal, and if BASE is
 * equal to 'x', interpret that D is hexadecimal. Return the number of
 * characters writen to buf (null end-mark not included)
 */
static int
itoa(char *buf, int base, int d)
{
   char *p = buf;
   char *p1, *p2;
   unsigned long ud = d;
   int divisor = 10;
   int nwriten = 0;
  
   /* If %d is specified and D is minus, put `-' in the head.  */
   if (base == 'd' && d < 0)
   {
      *p++ = '-';
      buf++;
      ud = -d;
      nwriten++;
   }
   else if (base == 'x')
      divisor = 16;

   /* Divide UD by DIVISOR until UD == 0.  */
   do
   {
      int remainder = ud % divisor;
      
      *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
      nwriten++;
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
   return nwriten;
}

void
StringPrinter::print(const char *format, ...)
{
   uint32_t *arg = (uint32_t*) &format;
   arg++;
   
   const char *base = format, *p;
   char c;
   int nbytes = 0;
   char buf[32];
   while ((c = *format++) != 0)
   {
      if (c == '%')
      {
         // Directive found, let's print the previously read data
         if (nbytes)
            os->write(base, nbytes);
         
         // Let's print the directive
         c = *format++;
         switch (c)
         {
            case 'd':
            case 'u':
            case 'x':
               nbytes = itoa(buf, c, *((int *) arg++));
               os->write(buf, nbytes);
               break;
            case 's':
               p = *((const char**) arg++);
               if (! p) p = (const char*) "(null)";
               os->write(p, strlen(p));
               break;
            default:
               os->write(*((void**) arg++), 1);
               break;
         }
         
         // Update base and nbytes to point to the next slice of the string
         base = format;
         nbytes = 0;
      }
      else
         nbytes++;
   }
   // Print the previous analized data
   if (nbytes)
      os->write(base, nbytes);
}

}; // namespace kalderaan

