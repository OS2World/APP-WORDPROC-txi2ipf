/*****************************************************************************
 * $Id: String_XClass_VHMap.h,v 1.1.1.1 1993/02/04 15:18:38 ak Exp $
 *****************************************************************************
 * $Log: String_XClass_VHMap.h,v $
 * Revision 1.1.1.1  1993/02/04  15:18:38  ak
 * Please Edit this file to contain the RCS log information
 * to be associated with this file (please remove these lines)
 *
 * Revision 1.1  1993/02/04  15:18:36  ak
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


#ifndef _StringXClassVHMap_h
#ifdef __GNUG__
#pragma interface
#endif
#define _StringXClassVHMap_h 1

#include "String_XClass_Map.h"


class StringXClassVHMap : public StringXClassMap
{
protected:
  String*           tab;
  XClass*           cont;
  char*          status;
  unsigned int   size;

public:
                StringXClassVHMap(XClass& dflt,unsigned int sz=DEFAULT_INITIAL_CAPACITY);
                StringXClassVHMap(StringXClassVHMap& a);
                ~StringXClassVHMap();

  XClass&          operator [] (String& key);

  void          del(String& key);

  Pix           first();
  void          next(Pix& i);
  String&          key(Pix i);
  XClass&          contents(Pix i);

  Pix           seek(String& key);
  int           contains(String& key);

  void          clear();
  void          resize(unsigned int newsize = 0);

  int           OK();
};

inline StringXClassVHMap::~StringXClassVHMap()
{
  delete [] tab;
  delete [] cont;
  delete [] status;
}

inline int StringXClassVHMap::contains(String& key)
{
  return seek(key) != 0;
}

inline String& StringXClassVHMap::key(Pix i)
{
  if (i == 0) error("null Pix");
  return *((String*)i);
}

inline XClass& StringXClassVHMap::contents(Pix i)
{
  if (i == 0) error("null Pix");
  return cont[((unsigned)(i) - (unsigned)(tab)) / sizeof(String)];
}

#endif
