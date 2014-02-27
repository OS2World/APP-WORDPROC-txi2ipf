/*****************************************************************************
 * $Id: String_int_AVLMap.h,v 1.1.1.1 1993/02/04 15:17:49 ak Exp $
 *****************************************************************************
 * $Log: String_int_AVLMap.h,v $
 * Revision 1.1.1.1  1993/02/04  15:17:49  ak
 * Please Edit this file to contain the RCS log information
 * to be associated with this file (please remove these lines)
 *
 * Revision 1.1  1993/02/04  15:17:47  ak
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


#ifndef _StringintAVLMap_h
#ifdef __GNUG__
#pragma interface
#endif
#define _StringintAVLMap_h 1

#include "String_int_Map.h"

struct StringintAVLNode
{
  StringintAVLNode*      lt;
  StringintAVLNode*      rt;
  String                 item;
  int                 cont;
  char                stat;
                      StringintAVLNode(String& h, int  c,
                                    StringintAVLNode* l=0, StringintAVLNode* r=0);
                      ~StringintAVLNode();
};

inline StringintAVLNode::StringintAVLNode(String& h, int  c,
                                    StringintAVLNode* l, StringintAVLNode* r)
     :item(h), cont(c), lt(l), rt(r), stat(0) {}

inline StringintAVLNode::~StringintAVLNode() {}

typedef StringintAVLNode* StringintAVLNodePtr;


class StringintAVLMap : public StringintMap
{
protected:
  StringintAVLNode*   root;

  StringintAVLNode*   leftmost();
  StringintAVLNode*   rightmost();
  StringintAVLNode*   pred(StringintAVLNode* t);
  StringintAVLNode*   succ(StringintAVLNode* t);
  void            _kill(StringintAVLNode* t);
  void            _add(StringintAVLNode*& t);
  void            _del(StringintAVLNode* p, StringintAVLNode*& t);

public:
                StringintAVLMap(int  dflt);
                StringintAVLMap(StringintAVLMap& a);
                ~StringintAVLMap();

  int&          operator [] (String& key);

  void          del(String& key);

  Pix           first();
  void          next(Pix& i);
  String&          key(Pix i);
  int&          contents(Pix i);

  Pix           seek(String& key);
  int           contains(String& key);

  void          clear();

  Pix           last();
  void          prev(Pix& i);

  int           OK();
};

inline StringintAVLMap::~StringintAVLMap()
{
  _kill(root);
}

inline StringintAVLMap::StringintAVLMap(int  dflt) :StringintMap(dflt)
{
  root = 0;
}

inline Pix StringintAVLMap::first()
{
  return Pix(leftmost());
}

inline Pix StringintAVLMap::last()
{
  return Pix(rightmost());
}

inline void StringintAVLMap::next(Pix& i)
{
  if (i != 0) i = Pix(succ((StringintAVLNode*)i));
}

inline void StringintAVLMap::prev(Pix& i)
{
  if (i != 0) i = Pix(pred((StringintAVLNode*)i));
}

inline String& StringintAVLMap::key(Pix i)
{
  if (i == 0) error("null Pix");
  return ((StringintAVLNode*)i)->item;
}

inline int& StringintAVLMap::contents(Pix i)
{
  if (i == 0) error("null Pix");
  return ((StringintAVLNode*)i)->cont;
}

inline void StringintAVLMap::clear()
{
  _kill(root);
  count = 0;
  root = 0;
}

inline int StringintAVLMap::contains(String& key)
{
  return seek(key) != 0;
}

#endif
