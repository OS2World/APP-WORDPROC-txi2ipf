%{
/*****************************************************************************
 * $Id: scan.l,v 1.8 1993/02/10 21:25:53 ak Exp $
 *****************************************************************************
 * $Log: scan.l,v $
 * Revision 1.8  1993/02/10  21:25:53  ak
 * *** empty log message ***
 *
 * Revision 1.7  1993/02/10  20:58:19  ak
 * Pass menues.
 *
 * Revision 1.6  1993/02/06  00:15:13  ak
 * *** empty log message ***
 *
 * Revision 1.5  1993/02/06  00:09:53  ak
 * *** empty log message ***
 *
 * Revision 1.4  1993/02/05  23:44:06  ak
 * Bugfixes and cosmetic changes.
 *
 * Revision 1.3  1993/02/04  17:51:18  ak
 * *** empty log message ***
 *
 * Revision 1.2  1993/02/04  15:28:58  ak
 * *** empty log message ***
 *
 * Revision 1.1.1.1  1993/02/04  15:21:54  ak
 * Texinfo -> OS/2 IPF/INF converter.
 *
 * Revision 1.1  1993/02/04  15:21:51  ak
 * Initial revision
 *
 *****************************************************************************/

static char *rcsid = "$Id: scan.l,v 1.8 1993/02/10 21:25:53 ak Exp $";

#include "info.h"
#include <ctype.h>
#include <io.h>
#include <strstream.h>
extern "C" char *strupr(char *);

String & arg();
String & eol();
void unexpected(const char *);
void footnote();
void skip();
void dot();
void include(const char *);

const int	MaxIncl = 10;
YY_BUFFER_STATE inclstack[MaxIncl];
int		incllevel = 0;
%}

%x	TABLE MENU FALSE IGNORE TEX TITLE

%%

@\*			PUTS(endl << ".br"); PUTL();
@\.			PUTS('.');
@\:			;
@@			PUTS('@');
@\{			PUTS('{');
@\}			PUTS('}');

@appendix		heading(1, eol());
@appendixsec		heading(2, eol());
@appendixsection	heading(2, eol());
@appendixsubsec		heading(3, eol());
@appendixsubsubsec	heading(4, eol());
@asis			;
@author			PUTA(":hp5."); PUT(eol()); PUTA(":ehp5.");
@b\{			PUTA(":hp2."); PUT(arg()); PUTA(":ehp2.");
@bullet\{\}		PUTS("&sqbul.");
@bye			return 0;
@c			skip();
@cartouche		;
@end\ cartouche		;
@center			PUTA(":lines align=center."); PUT(eol()); PUTA(":elines.");
@chapheading		heading(1, eol());
@chapter		heading(1, eol());
@cindex			indexes["cp"].entries[eol()].add(XItem(panel_name, panel_id));
@cite\{			PUTA(":hp1."); PUT(arg()); PUTA(":ehp1.");
@clear			flags[eol()] = 1;
@code\{			font("Courier"); PUT(arg()); font(0);
@comment		eol();
@contents		;
@copyright\{\}		PUTS("(C)");
@cropmarks		/*!!*/;
			/*	  	class/type	name	args	category	*/
@defcv			words(eol()); define(w[1],	w[2],	0,	w[0]);
@deffn			words(eol()); define(null,	w[1],	w+2,	w[0]);
@deffnx			words(eol()); define(null,	w[1],	w+2,	w[0]);
@defivar		words(eol()); define(w[0],	w[1],	0,	"Instance Variable");
@defmac			words(eol()); define(null,	w[0],	w+1,	"Macro");
@defmethod		words(eol()); define(w[0],	w[1],	w+2,	"Method");
@defop			words(eol()); define(w[1],	w[2],	w+3,	w[0]);
@defopt			words(eol()); define(null,	w[0],	0,	"User Option");
@defspec		words(eol()); define(null,	w[0],	w+1,	"Special Form");
@deftp			words(eol()); define(null,	w[1],	w+2,	w[0]);
@deftypefn		words(eol()); define(w[1],	w[2],	w+3,	w[0]);
@deftypefun		words(eol()); define(w[0],	w[1],	w+2,	"Function");
@deftypevr		words(eol()); define(w[1],	w[2],	0,	w[0]);
@deftypevar		words(eol()); define(w[0],	w[1],	0,	"Variable");
@defun			words(eol()); define(null,	w[0],	w+1,	"Function");
@defvar			words(eol()); define(null,	w[0],	0,	"Variable");
@defvr			words(eol()); define(null,	w[1],	0,	w[0]);
@end\ def[a-z]+		;

@dfn\{			PUTA(":hp1."); PUT(arg()); PUTA(":ehp1.");
@display		beg_example("default");
@end\ display		end_example();
@dmn\{			PUTS(' ' << arg());
@dots\{\}		PUTS("&dot.&dot.&dot.");
@emph\{			PUTA(":hp1."); PUT(arg()); PUTA(":ehp1.");
@enumerate		item_begin(":ol.", 'o',0); skip();
@end\ enumerate		item_end(":eol.");
@equiv\{\}		PUTS("==");
@error\{\}		PUTA(":hp8."); PUTS("ERROR: "); PUTA(":ehp8.");
@evenfooting		eol();
@evenheading		eol();
@everyfooting		eol();
@everyheading		eol();
@example		beg_example("Courier");
@end\ example		end_example();
@exdent			{ int old=margin(0); PUTS(eol()); margin(old); }
@expansion\{\}		PUTS("==>");
@file\{			font("Courier"); PUTS("&apos." << arg() << "&apos."); font(0);
@finalout		;
@findex			indexes["fn"].entries[eol()].add(XItem(panel_name, panel_id));
@flushleft		;
@end\ flushleft		;
@flushright		PUTA(":lines align=right.");
@end\ flushright	PUTA(":elines.");
@footnote\{		footnote();
@footnotestyle		;
@format			PUTA(":lines align=left.");
@end\ format		PUTA(":elines.");
@ftable			item_begin(":parml break=fit.", 'p',"Function"); BEGIN(TABLE);
@end\ ftable		item_end(":eparml.");
<TABLE>@code		istackp->beg = Item("Courier"); istackp->end = Item("default");
<TABLE>@kbd		istackp->beg = 0; istackp->end = 0;
<TABLE>@key		istackp->beg = 0; istackp->end = 0;
<TABLE>@samp		istackp->beg = Item("Courier", 0, "&apos."); istackp->end = Item("default", 0, "&apos.");
<TABLE>@var		istackp->beg = Item(0, 1); istackp->end = Item(0, 1);
<TABLE>@file		istackp->beg = Item("Courier"); istackp->end =Item("default");
<TABLE>@dfn		istackp->beg = Item(0, 1); istackp->end = Item(0, 1);
<TABLE>@cite		istackp->beg = Item(0, 1); istackp->end = Item(0, 1);
<TABLE>@asis		istackp->beg = 0; istackp->end = 0;
<TABLE>@b		istackp->beg = Item(0, 2); istackp->end = Item(0, 2);
<TABLE>@i		istackp->beg = Item(0, 1); istackp->end = Item(0, 1);
<TABLE>@r		istackp->beg = Item("'Tms Rmn'"); istackp->end = Item("default");
<TABLE>@t		istackp->beg = Item("Courier"); istackp->end = Item("default");
<TABLE>@emph		istackp->beg = Item(0, 1); istackp->end = Item(0, 1);
<TABLE>[ \t]		;
<TABLE>\n		BEGIN(0); ++yylineno;
@group			;
@end\ group		;
@heading		heading(2, eol());
@headings		eol();
@i\{			PUTA(":hp1."); PUT(arg()); PUTA(":ehp1.");
@ifclear		if (flags[eol()]) BEGIN(FALSE);
@end\ ifclear		;
<FALSE>@end\ if[a-z]+	BEGIN(0); eol();
<FALSE>\n		++yylineno;
<FALSE>.		;
@ifinfo			;
@end\ ifinfo		;
@ifset			if (!flags[eol()]) BEGIN(FALSE);
@end\ ifset		;
@iftex			BEGIN(0);
@end\ iftex		;
@ignore			BEGIN(IGNORE);
<IGNORE>@end\ ignore	BEGIN(0); eol();
<IGNORE>\n		++yylineno;
<IGNORE>.		;
@include		include(eol());	BEGIN(INITIAL);
<<EOF>>			{ if (--incllevel < 0)
				yyterminate();
			  else
				yy_switch_to_buffer(inclstack[incllevel]);
			}
@inforef		eol();
\\input			eol();
@item			istackp->item(eol());
@itemize		item_begin(":ul.", 'u',0); skip();
@end\ itemize		item_end(":eul.");
@itemx			istackp->item(eol());
@kbd\{			PUTS(arg());
@key\{			PUTS(arg());
@kindex			indexes["ky"].entries[eol()].add(XItem(panel_name, panel_id));
@lisp			beg_example("Courier");
@end\ lisp		end_example();
@majorheading		eol();
@menu			eol(); BEGIN(MENU); menu.line = ""; PUTS(":parml tsize=30 break=none compact.");
<MENU>@end\ menu	BEGIN(0); eol(); menu.flush(); PUTS(":eparml.");
<MENU>\*[ \t]+		menu.flush(); menu.line = eol();
<MENU>[ \t]+		menu.line += ' '; menu.line += eol();
<MENU>\n[ \t]*\n	menu.flush(); PUTL(); ++yylineno;
<MENU>\n		++yylineno;
<MENU>.			menu.flush(); PUTS(yytext[0]); PUTS(eol()); PUTL();
@minus\{\}		PUTS("&emdash.");
@need			eol();
@node			words(eol()); node(w[0], w[1], w[2], w[3]);
@noindent		newpara = 0; PUTS(endl << ".br"); PUTL();
@oddfooting		eol();
@oddheading		eol();
@page			;
@paragraphindent	eol();
@pindex			indexes["pg"].entries[eol()].add(XItem(panel_name, panel_id));
@point\{\}		PUTS('*');
@print\{\}		PUTS("&bxh.&bxri.");
@printindex		printindex(eol());
@pxref\{		words(arg()); xref("see ", w[0], w[1], w[2], w[3], w[4]);
@quotation		margin(+10); PUTA(":rm margin=4.");
@end\ quotation		margin(-10); PUTA(":rm margin=1.");
@r\{			font("'Tms Rmn'"); PUTS(arg()); font(0);
@ref\{			words(arg()); xref(0, w[0], w[1], w[2], w[3], w[4]);
@refill			;
@result\{\}		PUTS("=>");
@samp\{			font("Courier"); PUTS("&apos." << arg() << "&apos."); font(0);
@sc\{			{ char *cp = arg(); strupr(cp); font("Helv", "8x4"); PUTS(cp); font(0); }
@section		heading(2, eol());
@set			flags[eol()] = 1;
@setchapternewpage	eol();
@setfilename		eol();
@settitle		PUT(":title." << eol() << endl << ":h1.-Preface-"); PUTL();
@shortcontents		;
@smallbook		;
@smallexample		beg_example("Courier");
@end\ smallexample	end_example();
@smalllisp		beg_example("Courier");
@end\ smalllisp		end_example();
@sp			{ int n = atoi(eol()); while (n--) PUTS(endl << ".br" << endl); lastnl = 1; }
@strong\{		PUTA(":hp2."); PUTS(arg()); PUTA(":ehp2.");
@subheading		heading(3, eol());
@subsection		heading(3, eol());
@subsubheading		heading(4, eol());
@subsubsection		heading(4, eol());
@subtitle		eol();
@summarycontents	;
@syncodeindex		eol();
@synindex		eol();
@t\{			font("Courier"); PUTS(arg()); font(0);
@tt\{			font("Courier"); PUTS(arg()); font(0);
@table			BEGIN(TABLE); item_begin(":parml break=fit.", 'p',0); BEGIN(TABLE);
@end\ table		item_end(":eparml.");
@TeX\{\}		PUTS("TeX");
@tex			BEGIN(TEX);
<TEX>@end\ tex		BEGIN(0); eol();
<TEX>\n			++yylineno;
<TEX>.			;
@thischapter		;
@thischaptername	;
@thisfile		;
@thispage		;
@thistitle		;
@tindex			indexes["tp"].entries[eol()].add(XItem(panel_name, panel_id));
@title			;
@titlefont\{		arg();
@titlepage		BEGIN(TITLE);
<TITLE>@end\ titlepage	BEGIN(0); eol();
<TITLE>\n		++yylineno;
<TITLE>.		;
@today\{\}
@top			table["Top"] = Name(++hdid, 1, 0); heading(1, eol());
@unnumbered		heading(1, eol());
@unnumberedsec		heading(2, eol());
@unnumberedsubsec	heading(3, eol());
@unnumberedsubsubsec	heading(4, eol());
@var\{			PUTA(":hp1."); PUTS(arg()); PUTA(":ehp1.");
@vindex			indexes["vr"].entries[eol()].add(XItem(panel_name, panel_id));
@vskip			eol();
@vtable			BEGIN(TABLE);  item_begin(":parml break=fit.", 'p',"Variable");
@end\ vtable		item_end(":eparml.");
@w\{			single_word(arg());
@xref\{			words(arg()); xref("See ", w[0], w[1], w[2], w[3], w[4]);

@end\ [-a-zA-Z0-9_$]+	{ cerr << "Unknown control " << yytext << " in line " << yylineno << endl; }
@[-a-zA-Z0-9_$]+	{ cerr << "Unknown control " << yytext << " in line " << yylineno << endl; }

\&			PUTS("&amp.");
\n			++yylineno; return '\n';
\r			;
:			PUTS("&colon.");
\.			dot();
\{			PUTS(arg());
\}			return '}';
.			PUTS(yytext[0]);


%%

static String	buffer;

String &
arg()
{
	ostrstream ostr;
	ostream *old = out;
	out = &ostr;

	if (plevel == 9)
		unexpected(0);
	plines[++plevel] = yylineno;
	if (yy_flex_debug)
		fprintf(stderr, "++push to %d\n", plevel);

	int old_start = yy_start;
	int old_np = newpara;
	int old_nl = lastnl;
	BEGIN(0);
	newpara = 0;
	for (;;) {
		switch (yylex()) {
		case 0:
			unexpected("EOF");
		case '}':
			break;
		case '\n':
			if (ostr.pcount() > 100) {
				PUTL();
			} else
				PUT(' ');
			++yylineno;
			continue;
		default:
			continue;
		}
		break;
	}
	yy_start = old_start;
	newpara = old_np;
	lastnl = old_nl;

	if (yy_flex_debug)
		fprintf(stderr, "++pop from %d\n", plevel);
	--plevel;

	buffer = String(ostr.str(), ostr.pcount());
	while (buffer.length() && isspace(buffer[0]))
		buffer.del(0, 1);
	out = old;
	return buffer;
}

String &
eol()
{
	ostrstream ostr;
	ostream *old = out;
	out = &ostr;
	
	if (plevel == 9)
		unexpected(0);
	plines[++plevel] = yylineno;
	if (yy_flex_debug)
		fprintf(stderr, "++push to %d\n", plevel);

	int old_start = yy_start;
	int old_np = newpara;
	int old_nl = lastnl;
	BEGIN(0);
	newpara = 0;
	for (;;) {
		switch (yylex()) {
		case 0:
			unexpected("EOF");
		case '}':
			unput('}');
			break;
		case '\n':
			unput('\n');
			break;
		default:
			continue;
		}
		break;
	}
	yy_start = old_start;
	newpara = old_np;
	lastnl = old_nl;

	if (yy_flex_debug)
		fprintf(stderr, "++pop from %d\n", plevel);
	--plevel;

	buffer = String(ostr.str(), ostr.pcount());
	while (buffer.length() && isspace(buffer[0]))
		buffer.del(0, 1);
	out = old;
	return buffer;
}

void
unexpected(const char *msg)
{
	if (msg)
		cerr << "Unexpected EOF in line " << yylineno << endl;
	else
		cerr << "Nesting overflow in line " << yylineno << endl;
	for (; plevel; --plevel)
		cerr << "\tunterminated argument starting in line "
		     << plines[plevel] << endl;
	cerr.flush();
	exit(1);
}

void
footnote()
{
	++fnid;
	PUTS(":fn id=fn" << fnid << '.' << arg() << ":efn. "
	  << ":link reftype=fn refid=fn" << fnid << ".(" << fnid << "):elink.");
}

void
newline()
{
	if (!lastnl) {
		lastnl = 1;
		*out << endl;
	}
	if (!nofill) {
		int c = yyinput();
		if (c == '\n') {
			newpara = 1;
			do ++yylineno; while ((c = yyinput()) == '\n');
		}
		unput(c);
	}
}	

void
skip()
{
	for (int c; (c = yyinput()) != '\n'; )
		;
	++yylineno;
}

void
dot()
{
	int c = yyinput();
	if (c == '.') {
		PUTS("&dot.");
		do { PUT("&dot."); } while ((c = yyinput()) == '.');
	} else if (lastnl) {
		PUTS("&dot.");
	} else
		PUTS('.');
	unput(c);
}

void
include(const char *fname)
{
	if (incllevel >= MaxIncl) {
		fprintf(stderr, "Includes nested too deeply\n");
		exit(1);
	}
	inclstack[incllevel++] = YY_CURRENT_BUFFER;

	char name[FILENAME_MAX+1];
	strcpy(name, fname);
	char *namep = strtok(name, " \t");	// strip any blanks
	yyin = fopen(namep, "r");
	if (!yyin) {
		char *dotp = strrchr(namep, '.');
		if (dotp && !strpbrk(dotp, ":\\/") && strlen(dotp) > 4)
			dotp[4] = 0;		// truncate .texi to .tex
		yyin = fopen(namep, "r");
	}
	if (!yyin) {
		fprintf(stderr, "Cannot open include file %s\n", namep);
		exit(1);
	}

	yy_switch_to_buffer(yy_create_buffer(yyin, YY_BUF_SIZE));
}
