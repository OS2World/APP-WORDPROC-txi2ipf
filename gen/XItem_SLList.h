/*****************************************************************************
 * $Id: XItem_SLList.h,v 1.1.1.1 1993/02/04 15:19:35 ak Exp $
 *****************************************************************************
 * $Log: XItem_SLList.h,v $
 * Revision 1.1.1.1  1993/02/04  15:19:35  ak
 * Please Edit this file to contain the RCS log information
 * to be associated with this file (please remove these lines)
 *
 * Revision 1.1  1993/02/04  15:19:32  ak
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


#ifndef _XItemSLList_h
#ifdef __GNUG__
#pragma interface
#endif
#define _XItemSLList_h 1

#include <Pix.h>
#include "XItem_defs.h"

#ifndef _XItemSLListNode_h
#define _XItemSLListNode_h 1

struct XItemSLListNode
{
  XItemSLListNode*         tl;
  XItem                    hd;
                         XItemSLListNode() { }
                         XItemSLListNode(const XItem& h, XItemSLListNode* t = 0);
                         ~XItemSLListNode() { }
};


inline XItemSLListNode::XItemSLListNode(const XItem& h, XItemSLListNode* t)
:hd(h), tl(t) {}

typedef XItemSLListNode* XItemSLListNodePtr;

#endif


class XItemSLList
{
protected:
  XItemSLListNode*        last;

public:
                        XItemSLList();
                        XItemSLList(const XItemSLList& a);
                        ~XItemSLList();

  XItemSLList&            operator = (const XItemSLList& a);

  int                   empty();
  int                   length();

  void                  clear();

  Pix                   prepend(XItem& item);
  Pix                   append(XItem& item);

  void                  join(XItemSLList&);

  Pix                   prepend(XItemSLListNode*);
  Pix                   append(XItemSLListNode*);

  XItem&                  operator () (Pix p);
  Pix                   first();
  void                  next(Pix& p);
  int                   owns(Pix p);
  Pix                   ins_after(Pix p, XItem& item);
  void                  del_after(Pix p);

  XItem&                  front();
  XItem&                  rear();
  XItem                   remove_front();
  int                   remove_front(XItem& x);
  void                  del_front();

  void                  error(const char* msg);
  int                   OK();
};

inline XItemSLList::~XItemSLList()
{
  clear();
}

inline XItemSLList::XItemSLList()
{
  last = 0;
}

inline int XItemSLList::empty()
{
  return last == 0;
}


inline Pix XItemSLList::first()
{
  return (last == 0)? 0 : Pix(last->tl);
}

inline void XItemSLList::next(Pix& p)
{
  p = (p == 0 || p == last)? 0 : Pix(((XItemSLListNode*)(p))->tl);
}

inline XItem& XItemSLList::operator () (Pix p)
{
  if (p == 0) error("null Pix");
  return ((XItemSLListNode*)(p))->hd;
}

inline XItem& XItemSLList::front()
{
  if (last == 0) error("front: empty list");
  return last->tl->hd;
}

inline XItem& XItemSLList::rear()
{
  if (last == 0) error("rear: empty list");
  return last->hd;
}

#endif
