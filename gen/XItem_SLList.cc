///////////////////////////////////////////////////////////////////////////////
// $Id: XItem_SLList.cc,v 1.1.1.1 1993/02/04 15:19:30 ak Exp $
///////////////////////////////////////////////////////////////////////////////
// $Log: XItem_SLList.cc,v $
// Revision 1.1.1.1  1993/02/04  15:19:30  ak
// Please Edit this file to contain the RCS log information
// to be associated with this file (please remove these lines)
//
// Revision 1.1  1993/02/04  15:19:26  ak
// Initial revision
//
///////////////////////////////////////////////////////////////////////////////

static char *rcsid = "$Id: XItem_SLList.cc,v 1.1.1.1 1993/02/04 15:19:30 ak Exp $";

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
#include <values.h>
#include <stream.h>
#include <builtin.h>
#include "info.h"

void XItemSLList::error(const char* msg)
{
  (*lib_error_handler)("SLList", msg);
}

int XItemSLList::length()
{
  int l = 0;
  XItemSLListNode* t = last;
  if (t != 0) do { ++l; t = t->tl; } while (t != last);
  return l;
}

XItemSLList::XItemSLList(const XItemSLList& a)
{
  if (a.last == 0)
    last = 0;
  else
  {
    XItemSLListNode* p = a.last->tl;
    XItemSLListNode* h = new XItemSLListNode(p->hd);
    last = h;
    for (;;)
    {
      if (p == a.last)
      {
        last->tl = h;
        return;
      }
      p = p->tl;
      XItemSLListNode* n = new XItemSLListNode(p->hd);
      last->tl = n;
      last = n;
    }
  }
}

XItemSLList& XItemSLList::operator = (const XItemSLList& a)
{
  if (last != a.last)
  {
    clear();
    if (a.last != 0)
    {
      XItemSLListNode* p = a.last->tl;
      XItemSLListNode* h = new XItemSLListNode(p->hd);
      last = h;
      for (;;)
      {
        if (p == a.last)
        {
          last->tl = h;
          break;
        }
        p = p->tl;
        XItemSLListNode* n = new XItemSLListNode(p->hd);
        last->tl = n;
        last = n;
      }
    }
  }
  return *this;
}

void XItemSLList::clear()
{
  if (last == 0)
    return;

  XItemSLListNode* p = last->tl;
  last->tl = 0;
  last = 0;

  while (p != 0)
  {
    XItemSLListNode* nxt = p->tl;
    delete(p);
    p = nxt;
  }
}


Pix XItemSLList::prepend(XItem& item)
{
  XItemSLListNode* t = new XItemSLListNode(item);
  if (last == 0)
    t->tl = last = t;
  else
  {
    t->tl = last->tl;
    last->tl = t;
  }
  return Pix(t);
}


Pix XItemSLList::prepend(XItemSLListNode* t)
{
  if (t == 0) return 0;
  if (last == 0)
    t->tl = last = t;
  else
  {
    t->tl = last->tl;
    last->tl = t;
  }
  return Pix(t);
}


Pix XItemSLList::append(XItem& item)
{
  XItemSLListNode* t = new XItemSLListNode(item);
  if (last == 0)
    t->tl = last = t;
  else
  {
    t->tl = last->tl;
    last->tl = t;
    last = t;
  }
  return Pix(t);
}

Pix XItemSLList::append(XItemSLListNode* t)
{
  if (t == 0) return 0;
  if (last == 0)
    t->tl = last = t;
  else
  {
    t->tl = last->tl;
    last->tl = t;
    last = t;
  }
  return Pix(t);
}

void XItemSLList::join(XItemSLList& b)
{
  XItemSLListNode* t = b.last;
  b.last = 0;
  if (last == 0)
    last = t;
  else if (t != 0)
  {
    XItemSLListNode* f = last->tl;
    last->tl = t->tl;
    t->tl = f;
    last = t;
  }
}

Pix XItemSLList::ins_after(Pix p, XItem& item)
{
  XItemSLListNode* u = (XItemSLListNode*)p;
  XItemSLListNode* t = new XItemSLListNode(item);
  if (last == 0)
    t->tl = last = t;
  else if (u == 0) // ins_after 0 means prepend
  {
    t->tl = last->tl;
    last->tl = t;
  }
  else
  {
    t->tl = u->tl;
    u->tl = t;
    if (u == last)
      last = t;
  }
  return Pix(t);
}


void XItemSLList::del_after(Pix p)
{
  XItemSLListNode* u = (XItemSLListNode*)p;
  if (last == 0 || u == last) error("cannot del_after last");
  if (u == 0) u = last; // del_after 0 means delete first
  XItemSLListNode* t = u->tl;
  if (u == t)
    last = 0;
  else
  {
    u->tl = t->tl;
    if (last == t)
      last = u;
  }
  delete t;
}

int XItemSLList::owns(Pix p)
{
  XItemSLListNode* t = last;
  if (t != 0 && p != 0)
  {
    do
    {
      if (Pix(t) == p) return 1;
      t = t->tl;
    } while (t != last);
  }
  return 0;
}

XItem XItemSLList::remove_front()
{
  if (last == 0) error("remove_front of empty list");
  XItemSLListNode* t = last->tl;
  XItem res = t->hd;
  if (t == last)
    last = 0;
  else
    last->tl = t->tl;
  delete t;
  return res;
}

int XItemSLList::remove_front(XItem& x)
{
  if (last == 0)
    return 0;
  else
  {
    XItemSLListNode* t = last->tl;
    x = t->hd;
    if (t == last)
      last = 0;
    else
      last->tl = t->tl;
    delete t;
    return 1;
  }
}


void XItemSLList::del_front()
{
  if (last == 0) error("del_front of empty list");
  XItemSLListNode* t = last->tl;
  if (t == last)
    last = 0;
  else
    last->tl = t->tl;
  delete t;
}

int XItemSLList::OK()
{
  int v = 1;
  if (last != 0)
  {
    XItemSLListNode* t = last;
    long count = MAXLONG;      // Lots of chances to find last!
    do
    {
      count--;
      t = t->tl;
    } while (count > 0 && t != last);
    v &= count > 0;
  }
  if (!v) error("invariant failure");
  return v;
}
