/*****************************************************************************
 * $Id: info.h,v 1.5 1993/02/10 20:58:26 ak Exp $
 *****************************************************************************
 * $Log: info.h,v $
 * Revision 1.5  1993/02/10  20:58:26  ak
 * Pass menues.
 *
 * Revision 1.4  1993/02/06  00:09:51  ak
 * *** empty log message ***
 *
 * Revision 1.3  1993/02/05  23:44:04  ak
 * Bugfixes and cosmetic changes.
 *
 * Revision 1.2  1993/02/05  08:48:40  ak
 * *** empty log message ***
 *
 * Revision 1.1.1.1  1993/02/04  15:21:30  ak
 * Texinfo -> OS/2 IPF/INF converter.
 *
 * Revision 1.1  1993/02/04  15:21:27  ak
 * Initial revision
 *
 *****************************************************************************/

#include <iostream.h>
#include <Strng.h>
#include <stdlib.h>
#include <string.h>

#define FontSize	"17x10"

const int	MaxW	= 20;

#ifndef EXTERN
 #define EXTERN extern
 #define INIT(x)
#endif

struct Name {
	Name (int i, int d = 0, int l = 0)  { id = i; defined = d; level = l; }
	int	defined;
	int	id;
	int	level;
};

struct XItem {
	XItem ()			: title("?") { id = 0; }
	XItem (String& str, int num)	: title(str) { id = num; }

	String title;
	int id;
};

#include "XItem_SLBag.h"

typedef class XItemSLBag XEntry;

#include "String_XEntry_AVLMap.h"

typedef class StringXEntryAVLMap XClassT;

struct XClass {
	XClass ()  : entries(XEntry()) {}
	XClassT entries;
};

#include "String_XClass_VHMap.h"

typedef class StringXClassVHMap Index;

typedef class StringNameAVLMap Table;
typedef class StringintAVLMap Flags;

#include "String_Name_AVLMap.h"
#include "String_int_AVLMap.h"

EXTERN int	fnid	INIT(0);		// footnote id
EXTERN int	hdid	INIT(0);		// heading id

EXTERN String	node_name;			// name of last node
EXTERN int	node_id;			// heading id of last node

EXTERN String	panel_name;			// heading name of last panel
EXTERN int	panel_id;			// heading id of last panel

EXTERN int	yylineno INIT(1);		// input line number

EXTERN Flags	flags	INIT(Flags(0));			// TexInfo flags
EXTERN Table	table	INIT(Table(Name(0, 0, 0)));	// table of menu nodes
EXTERN Index	indexes	INIT(Index(XClass(), 10));	// 2-dim index
						
EXTERN ostream *out	INIT(&cout);		// current output stream
						
EXTERN String	w[MaxW];			// result of words()
EXTERN String	null	INIT("");		// the null string

EXTERN int	debug;				// trace parser
EXTERN int	f_node;				// use chapters(0) or nodes(1)

	// scan.l
extern int	yylex();
extern void	newline();

	// util.cc
extern void	words(String&);
extern void	heading(int level, char *s);
extern void	footnote();
extern void	item_begin (const char *beg, int it, char *ic);
extern void	item_end (const char *end);
extern void	node(String name, String next, String prev, String up);
extern void	xref(char *see, String name, String entry, String topic, String file, String manual);
extern void	define(String& type, String& name, String *args, String& category);

extern void	font(const char *name, const char *size = FontSize);
extern void	beg_example(const char *);
extern void	end_example();
extern int	margin(int);
extern void	single_word(char *text);
extern void	para();

extern void	printindex(String& name);

struct Item {
	Item (char *name = 0, int num = 0, char *text = 0)
		{ fontname = name; hpnumber = num; delimiter = text; }
	char *	fontname;	// item font
	int	hpnumber;	// :hp number
	char *	delimiter;	// delimiter text
};

struct ItemType {
	Item	beg;		// before item
	Item	end;		// after item
	int	type;		// 'o' = ordered list, 'l' = unordered list,
				// 'p' = parameters
	char *	cat;		// "Function", "Variable", 0
	short	indent;		// indentation level
	short	nested;		// is nested
	short	count;		// item counter

	void item (const char *text);
};

struct Menu {
	String	line;
	void	flush();
};

EXTERN Menu	menu;

EXTERN int	nofill;				// don't care about paragraphs

EXTERN ItemType   istack[50];
EXTERN ItemType * istackp INIT(istack);

EXTERN int	plines[10];			// line number where arg starts
EXTERN int	plevel;				// scanner level (index to plines)
EXTERN int	newpara;			// new paragraph required
EXTERN int	lastnl;				// last is newline

#define PUT(x)	{*out << x; lastnl = 0;}
#define PUTS(x)	{if (newpara) para(); *out << x; lastnl = 0;}
#define PUTA(x)	{if (!plevel) { if (newpara) para(); *out << x; lastnl = 0;}}
#define PUTL()	{*out << endl; lastnl = 1;}

