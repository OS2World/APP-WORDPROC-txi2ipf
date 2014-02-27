/*****************************************************************************
 * $Id: String_XEntry_Map.h,v 1.1.1.1 1993/02/04 15:18:58 ak Exp $
 *****************************************************************************
 * $Log: String_XEntry_Map.h,v $
 * Revision 1.1.1.1  1993/02/04  15:18:58  ak
 * Please Edit this file to contain the RCS log information
 * to be associated with this file (please remove these lines)
 *
 * Revision 1.1  1993/02/04  15:18:56  ak
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


#ifndef _StringXEntryMap_h
#ifdef __GNUG__
#pragma interface
#endif
#define _StringXEntryMap_h 1

#include <Pix.h>
#include "String_defs.h"

class StringXEntryMap
{
protected:
  int                   count;
  XEntry                   def;

public:
                        StringXEntryMap(XEntry& dflt);
  virtual              ~StringXEntryMap();

  int                   length();                // current number of items
  int                   empty();

  virtual int           contains(String& key);      // is key mapped?

  virtual void          clear();                 // delete all items

  virtual XEntry&          operator [] (String& key) = 0; // access contents by key

  virtual void          del(String& key) = 0;       // delete entry

  virtual Pix           first() = 0;             // Pix of first item or 0
  virtual void          next(Pix& i) = 0;        // advance to next or 0
  virtual String&          key(Pix i) = 0;          // access key at i
  virtual XEntry&          contents(Pix i) = 0;     // access contents at i

  virtual int           owns(Pix i);             // is i a valid Pix  ?
  virtual Pix           seek(String& key);          // Pix of key

  XEntry&                  dflt();                  // access default val

  void                  error(const char* msg);
  virtual int           OK() = 0;                // rep invariant
};


inline StringXEntryMap::~StringXEntryMap() {}

inline int StringXEntryMap::length()
{
  return count;
}

inline int StringXEntryMap::empty()
{
  return count == 0;
}

inline XEntry& StringXEntryMap::dflt()
{
  return def;
}

inline StringXEntryMap::StringXEntryMap(XEntry& dflt) :def(dflt)
{
  count = 0;
}

#endif
