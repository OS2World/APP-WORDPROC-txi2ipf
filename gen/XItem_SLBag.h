/*****************************************************************************
 * $Id: XItem_SLBag.h,v 1.1.1.1 1993/02/04 15:19:23 ak Exp $
 *****************************************************************************
 * $Log: XItem_SLBag.h,v $
 * Revision 1.1.1.1  1993/02/04  15:19:23  ak
 * Please Edit this file to contain the RCS log information
 * to be associated with this file (please remove these lines)
 *
 * Revision 1.1  1993/02/04  15:19:20  ak
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


#ifndef _XItemSLBag_h
#ifdef __GNUG__
#pragma interface
#endif
#define _XItemSLBag_h 1

#include "XItem_Bag.h"
#include "XItem_SLList.h"

class XItemSLBag : public XItemBag
{
protected:
  XItemSLList     p;

public:
                XItemSLBag();
                XItemSLBag(const XItemSLBag&);

  Pix           add(XItem& item);
  void          del(XItem& item);
  void          remove(XItem&item);
  int           contains(XItem& item);
  int           nof(XItem& item);

  void          clear();

  Pix           first();
  void          next(Pix& i);
  XItem&          operator () (Pix i);
  int           owns(Pix i);
  Pix           seek(XItem& item, Pix from = 0);

  int           OK();
};


inline XItemSLBag::XItemSLBag() : p() { count = 0; }

inline XItemSLBag::XItemSLBag(const XItemSLBag& s) : p(s.p) { count = s.count; }

inline Pix XItemSLBag::first()
{
  return p.first();
}

inline void XItemSLBag::next(Pix  & idx)
{
  p.next(idx);
}

inline XItem& XItemSLBag::operator ()(Pix   idx)
{
  return p(idx);
}

inline void XItemSLBag::clear()
{
  count = 0;  p.clear();
}

inline int XItemSLBag::owns (Pix   idx)
{
  return p.owns(idx);
}

inline Pix XItemSLBag::add(XItem& item)
{
  ++count;
  return p.append(item);
}

inline int XItemSLBag::contains(XItem& item)
{
  return seek(item) != 0;
}

#endif
