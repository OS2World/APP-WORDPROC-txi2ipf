/*****************************************************************************
 * $Id: String_Name_AVLMap.h,v 1.1.1.1 1993/02/04 15:18:08 ak Exp $
 *****************************************************************************
 * $Log: String_Name_AVLMap.h,v $
 * Revision 1.1.1.1  1993/02/04  15:18:08  ak
 * Please Edit this file to contain the RCS log information
 * to be associated with this file (please remove these lines)
 *
 * Revision 1.1  1993/02/04  15:18:05  ak
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


#ifndef _StringNameAVLMap_h
#ifdef __GNUG__
#pragma interface
#endif
#define _StringNameAVLMap_h 1

#include "String_Name_Map.h"

struct StringNameAVLNode
{
  StringNameAVLNode*      lt;
  StringNameAVLNode*      rt;
  String                 item;
  Name                 cont;
  char                stat;
                      StringNameAVLNode(String& h, Name& c,
                                    StringNameAVLNode* l=0, StringNameAVLNode* r=0);
                      ~StringNameAVLNode();
};

inline StringNameAVLNode::StringNameAVLNode(String& h, Name& c,
                                    StringNameAVLNode* l, StringNameAVLNode* r)
     :item(h), cont(c), lt(l), rt(r), stat(0) {}

inline StringNameAVLNode::~StringNameAVLNode() {}

typedef StringNameAVLNode* StringNameAVLNodePtr;


class StringNameAVLMap : public StringNameMap
{
protected:
  StringNameAVLNode*   root;

  StringNameAVLNode*   leftmost();
  StringNameAVLNode*   rightmost();
  StringNameAVLNode*   pred(StringNameAVLNode* t);
  StringNameAVLNode*   succ(StringNameAVLNode* t);
  void            _kill(StringNameAVLNode* t);
  void            _add(StringNameAVLNode*& t);
  void            _del(StringNameAVLNode* p, StringNameAVLNode*& t);

public:
                StringNameAVLMap(Name& dflt);
                StringNameAVLMap(StringNameAVLMap& a);
                ~StringNameAVLMap();

  Name&          operator [] (String& key);

  void          del(String& key);

  Pix           first();
  void          next(Pix& i);
  String&          key(Pix i);
  Name&          contents(Pix i);

  Pix           seek(String& key);
  int           contains(String& key);

  void          clear();

  Pix           last();
  void          prev(Pix& i);

  int           OK();
};

inline StringNameAVLMap::~StringNameAVLMap()
{
  _kill(root);
}

inline StringNameAVLMap::StringNameAVLMap(Name& dflt) :StringNameMap(dflt)
{
  root = 0;
}

inline Pix StringNameAVLMap::first()
{
  return Pix(leftmost());
}

inline Pix StringNameAVLMap::last()
{
  return Pix(rightmost());
}

inline void StringNameAVLMap::next(Pix& i)
{
  if (i != 0) i = Pix(succ((StringNameAVLNode*)i));
}

inline void StringNameAVLMap::prev(Pix& i)
{
  if (i != 0) i = Pix(pred((StringNameAVLNode*)i));
}

inline String& StringNameAVLMap::key(Pix i)
{
  if (i == 0) error("null Pix");
  return ((StringNameAVLNode*)i)->item;
}

inline Name& StringNameAVLMap::contents(Pix i)
{
  if (i == 0) error("null Pix");
  return ((StringNameAVLNode*)i)->cont;
}

inline void StringNameAVLMap::clear()
{
  _kill(root);
  count = 0;
  root = 0;
}

inline int StringNameAVLMap::contains(String& key)
{
  return seek(key) != 0;
}

#endif
