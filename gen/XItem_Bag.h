/*****************************************************************************
 * $Id: XItem_Bag.h,v 1.1.1.1 1993/02/04 15:19:08 ak Exp $
 *****************************************************************************
 * $Log: XItem_Bag.h,v $
 * Revision 1.1.1.1  1993/02/04  15:19:08  ak
 * Please Edit this file to contain the RCS log information
 * to be associated with this file (please remove these lines)
 *
 * Revision 1.1  1993/02/04  15:19:05  ak
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


#ifndef _XItemBag_h
#ifdef __GNUG__
#pragma interface
#endif
#define _XItemBag_h 1

#include <Pix.h>
#include "XItem_defs.h"

class XItemBag
{
protected:
  int                   count;

public:
  virtual              ~XItemBag();

  int                   length();                // current number of items
  int                   empty();

  virtual Pix           add(XItem& item) = 0;      // add item; return Pix

  virtual void          del(XItem& item) = 0;      // delete 1 occurrence of item
  virtual void          remove(XItem& item);       // delete all occurrences
  virtual void          clear();                 // delete all items

  virtual int           contains(XItem& item);     // is item in Bag?
  virtual int           nof(XItem& item);          // how many in Bag?

  virtual Pix           first() = 0;             // Pix of first item or 0
  virtual void          next(Pix& i) = 0;        // advance to next or 0

  virtual XItem&          operator () (Pix i) = 0; // access item at i

  virtual Pix           seek(XItem& item, Pix from=0); // Pix of next occurrence
  virtual int           owns(Pix i);             // is i a valid Pix  ?

  void                  error(const char* msg);
  virtual int           OK() = 0;                // rep invariant
};

inline XItemBag::~XItemBag() {}

inline int XItemBag::length()
{
  return count;
}

inline int XItemBag::empty()
{
  return count == 0;
}

inline int XItemBag::contains(XItem& item)
{
  return seek(item) != 0;
}

#endif
