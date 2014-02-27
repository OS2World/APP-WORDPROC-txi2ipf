/*****************************************************************************
 * $Id: String_XEntry_AVLMap.h,v 1.1.1.1 1993/02/04 15:18:48 ak Exp $
 *****************************************************************************
 * $Log: String_XEntry_AVLMap.h,v $
 * Revision 1.1.1.1  1993/02/04  15:18:48  ak
 * Please Edit this file to contain the RCS log information
 * to be associated with this file (please remove these lines)
 *
 * Revision 1.1  1993/02/04  15:18:45  ak
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


#ifndef _StringXEntryAVLMap_h
#ifdef __GNUG__
#pragma interface
#endif
#define _StringXEntryAVLMap_h 1

#include "String_XEntry_Map.h"

struct StringXEntryAVLNode
{
  StringXEntryAVLNode*      lt;
  StringXEntryAVLNode*      rt;
  String                 item;
  XEntry                 cont;
  char                stat;
                      StringXEntryAVLNode(String& h, XEntry& c,
                                    StringXEntryAVLNode* l=0, StringXEntryAVLNode* r=0);
                      ~StringXEntryAVLNode();
};

inline StringXEntryAVLNode::StringXEntryAVLNode(String& h, XEntry& c,
                                    StringXEntryAVLNode* l, StringXEntryAVLNode* r)
     :item(h), cont(c), lt(l), rt(r), stat(0) {}

inline StringXEntryAVLNode::~StringXEntryAVLNode() {}

typedef StringXEntryAVLNode* StringXEntryAVLNodePtr;


class StringXEntryAVLMap : public StringXEntryMap
{
protected:
  StringXEntryAVLNode*   root;

  StringXEntryAVLNode*   leftmost();
  StringXEntryAVLNode*   rightmost();
  StringXEntryAVLNode*   pred(StringXEntryAVLNode* t);
  StringXEntryAVLNode*   succ(StringXEntryAVLNode* t);
  void            _kill(StringXEntryAVLNode* t);
  void            _add(StringXEntryAVLNode*& t);
  void            _del(StringXEntryAVLNode* p, StringXEntryAVLNode*& t);

public:
                StringXEntryAVLMap(XEntry& dflt);
                StringXEntryAVLMap(StringXEntryAVLMap& a);
                ~StringXEntryAVLMap();

  XEntry&          operator [] (String& key);

  void          del(String& key);

  Pix           first();
  void          next(Pix& i);
  String&          key(Pix i);
  XEntry&          contents(Pix i);

  Pix           seek(String& key);
  int           contains(String& key);

  void          clear();

  Pix           last();
  void          prev(Pix& i);

  int           OK();
};

inline StringXEntryAVLMap::~StringXEntryAVLMap()
{
  _kill(root);
}

inline StringXEntryAVLMap::StringXEntryAVLMap(XEntry& dflt) :StringXEntryMap(dflt)
{
  root = 0;
}

inline Pix StringXEntryAVLMap::first()
{
  return Pix(leftmost());
}

inline Pix StringXEntryAVLMap::last()
{
  return Pix(rightmost());
}

inline void StringXEntryAVLMap::next(Pix& i)
{
  if (i != 0) i = Pix(succ((StringXEntryAVLNode*)i));
}

inline void StringXEntryAVLMap::prev(Pix& i)
{
  if (i != 0) i = Pix(pred((StringXEntryAVLNode*)i));
}

inline String& StringXEntryAVLMap::key(Pix i)
{
  if (i == 0) error("null Pix");
  return ((StringXEntryAVLNode*)i)->item;
}

inline XEntry& StringXEntryAVLMap::contents(Pix i)
{
  if (i == 0) error("null Pix");
  return ((StringXEntryAVLNode*)i)->cont;
}

inline void StringXEntryAVLMap::clear()
{
  _kill(root);
  count = 0;
  root = 0;
}

inline int StringXEntryAVLMap::contains(String& key)
{
  return seek(key) != 0;
}

#endif
