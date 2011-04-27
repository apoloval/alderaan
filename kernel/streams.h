/*
 *  File        : kernel/streams.h
 *  Description : This file provides abstract classes representing data
 *                streams and utility classes for support input and output.
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

#ifndef _STREAMS_H
#define _STREAMS_H

#include <stddef.h>

namespace kalderaan {

/* Input stream class. This class represents a stream that accepts data
 * input.
 */
class InputStream
{
public:

   /* Read nbytes from stream and store them in data. */
   virtual void read(void *data, size_t nbytes) = 0;

};

/* Output stream class. This class represents a stream that accepts data
 * output.
 */
class OutputStream
{
public:

   /* Write nbytes from data to the stream. */
   virtual void write(const void *data, size_t nbytes) = 0;

};

/* String printer class. Objects of this class wraps an OutputStream
 * object in order to extend it with string printing operations. 
 */
class StringPrinter
{
public:

   /* Constructor. */
   inline StringPrinter(OutputStream *ostream) : os(ostream) {}

   /* Prints a formatted message into output stream. */
   void print(const char *format, ...);   

private:

   /* The output stream to print strings to. */
   OutputStream *os;

};

/* Boot terminal class. This stream class represents the boot console. 
 * This class is expected to be extended by concrete implementations for
 * each architecture in <arch>/bootterm.cpp file. */
class BootTerminal : public OutputStream
{
public:

   /* Obtain boot terminal instance for current architecture. */
   static BootTerminal &instance();

   /* Clean the terminal and reset the cursor to top-left position. */
   virtual void clear() = 0;
   
};

}; // namespace kalderaan

#endif

