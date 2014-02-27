///////////////////////////////////////////////////////////////////////////////
// $Id: XItem_SLBag.cc,v 1.1.1.1 1993/02/04 15:19:18 ak Exp $
///////////////////////////////////////////////////////////////////////////////
// $Log: XItem_SLBag.cc,v $
// Revision 1.1.1.1  1993/02/04  15:19:18  ak
// Please Edit this file to contain the RCS log information
// to be associated with this file (please remove these lines)
//
// Revision 1.1  1993/02/04  15:19:15  ak
// Initial revision
//
///////////////////////////////////////////////////////////////////////////////

static char *rcsid = "$Id: XItem_SLBag.cc,v 1.1.1.1 1993/02/04 15:19:18 ak Exp $";

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

#ifdef __GNUG__
#pragma implementation
#endif
#include "info.h"

int XItemSLBag::OK()
{
  int v = p.OK();
  v &= count == p.length();
  if (!v) error("invariant failure");
  return v;
}

Pix XItemSLBag::seek(XItem& item, Pix i)
{
  if (i == 0) i = first(); else next(i);
  for (; i != 0 && (!(XItemEQ(p(i), item))); p.next(i));
  return i;
}

int XItemSLBag::nof(XItem& item)
{
  int n = 0;
  for (Pix p = first(); p; next(p)) if (XItemEQ((*this)(p), item)) ++n;
  return n;
}


void XItemSLBag::del(XItem& item)
{
  Pix i = p.first();
  if (i == 0)
    return;
  else if (XItemEQ(p(i), item))
  {
    --count;
    p.del_front();
  }
  else
  {
    Pix trail = i;
    p.next(i);
    while (i != 0)
    {
      if (XItemEQ(p(i), item))
      {
        --count;
        p.del_after(trail);
        return;
      }
      trail = i;
      p.next(i);
    }
  }
}

void XItemSLBag::remove(XItem& item)
{
  Pix i = p.first();
  while (i != 0 && XItemEQ(p(i), item))
  {
    --count;
    p.del_front();
    i = p.first();
  }
  if (i != 0)
  {
    Pix trail = i;
    p.next(i);
    while (i != 0)
    {
      if (XItemEQ(p(i), item))
      {
        --count;
        p.del_after(trail);
        i = trail;
        p.next(i);
      }
      else
      {
        trail = i;
        p.next(i);
      }
    }
  }
}

