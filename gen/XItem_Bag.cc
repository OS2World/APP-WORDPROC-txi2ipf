///////////////////////////////////////////////////////////////////////////////
// $Id: XItem_Bag.cc,v 1.1.1.1 1993/02/04 15:19:03 ak Exp $
///////////////////////////////////////////////////////////////////////////////
// $Log: XItem_Bag.cc,v $
// Revision 1.1.1.1  1993/02/04  15:19:03  ak
// Please Edit this file to contain the RCS log information
// to be associated with this file (please remove these lines)
//
// Revision 1.1  1993/02/04  15:19:01  ak
// Initial revision
//
///////////////////////////////////////////////////////////////////////////////

static char *rcsid = "$Id: XItem_Bag.cc,v 1.1.1.1 1993/02/04 15:19:03 ak Exp $";

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
#include <builtin.h>
#include "info.h"

// error handling

void XItemBag::error(const char* msg)
{
  (*lib_error_handler)("Bag", msg);
}


Pix XItemBag::seek(XItem& item, Pix i)
{
  if (i == 0)
    i = first();
  else
    next(i);
  for (;i != 0 && (!(XItemEQ((*this)(i), item))); next(i));
  return i;
}

int XItemBag::owns(Pix p)
{
  if (p == 0) return 0;
  for (Pix i = first(); i != 0; next(i)) if (i == p) return 1;
  return 0;
}

void XItemBag::remove(XItem& item)
{
  int i = nof(item);
  while (i-- > 0) del(item);
}


int XItemBag::nof(XItem& item)
{
  int n = 0;
  for (Pix p = first(); p; next(p)) if (XItemEQ((*this)(p), item)) ++n;
  return n;
}

void XItemBag::clear()
{
  Pix i = first();
  while (i != 0)
  {
    del((*this)(i));
    i = first();
  }
}


