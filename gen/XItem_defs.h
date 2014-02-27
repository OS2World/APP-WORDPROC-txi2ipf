/*****************************************************************************
 * $Id: XItem_defs.h,v 1.1.1.1 1993/02/04 15:19:13 ak Exp $
 *****************************************************************************
 * $Log: XItem_defs.h,v $
 * Revision 1.1.1.1  1993/02/04  15:19:13  ak
 * Please Edit this file to contain the RCS log information
 * to be associated with this file (please remove these lines)
 *
 * Revision 1.1  1993/02/04  15:19:10  ak
 * Initial revision
 *
 *****************************************************************************/

// This may look like C code, but it is really -*- C++ -*-
/*
Copyright (C) 1988 Free Software Foundation
    written by Doug Lea (dl@rocky.oswego.edu)

This file is part of the GNU C++ Library.  This library is free
software; you can redistribute it and/or modify it under the terms of
the GNU Library General Public License as published by the Free
Software Foundation; either version 2 of the License, or (at your
option) any later version.  This library is distributed in the hope
that it will be useful, but WITHOUT ANY WARRANTY; without even the
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the GNU Library General Public License for more details.
You should have received a copy of the GNU Library General Public
License along with this library; if not, write to the Free Software
Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
*/


#ifndef _XItemdefs_h
#define _XItemdefs_h 1

#define XItemEQ(a,b) ((a).title == (b).title)

// equality operator
#ifndef XItemEQ
#define XItemEQ(a, b)  ((a) == (b))
#endif

// less-than-or-equal
#ifndef XItemLE
#define XItemLE(a, b)  ((a) <= (b))
#endif

// comparison : less-than -> < 0; equal -> 0; greater-than -> > 0
#ifndef XItemCMP
#define XItemCMP(a, b) ( ((a) <= (b))? (((a) == (b))? 0 : -1) : 1 )
#endif

// hash function
#ifndef XItemHASH
extern unsigned int hash(XItem&);
#define XItemHASH(x)  hash(x)
#endif

// initial capacity for structures requiring one

#ifndef DEFAULT_INITIAL_CAPACITY
#define DEFAULT_INITIAL_CAPACITY 100
#endif


#endif
