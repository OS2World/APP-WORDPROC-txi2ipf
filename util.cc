///////////////////////////////////////////////////////////////////////////////
// $Id: util.cc,v 1.7 1993/02/10 21:25:56 ak Exp $
///////////////////////////////////////////////////////////////////////////////
// $Log: util.cc,v $
// Revision 1.7  1993/02/10  21:25:56  ak
// *** empty log message ***
//
// Revision 1.6  1993/02/10  20:58:24  ak
// Pass menues.
//
// Revision 1.5  1993/02/06  00:09:58  ak
// *** empty log message ***
//
// Revision 1.4  1993/02/05  23:44:11  ak
// Bugfixes and consmetic changes.
//
// Revision 1.3  1993/02/04  17:51:22  ak
// *** empty log message ***
//
// Revision 1.2  1993/02/04  15:45:58  ak
// *** empty log message ***
//
// Revision 1.1.1.1  1993/02/04  15:22:01  ak
// Texinfo -> OS/2 IPF/INF converter.
//
// Revision 1.1  1993/02/04  15:21:58  ak
// Initial revision
//
///////////////////////////////////////////////////////////////////////////////

static char *rcsid = "$Id: util.cc,v 1.7 1993/02/10 21:25:56 ak Exp $";

#include "info.h"
#include <ctype.h>
#include <alloca.h>

static char *	old_font = "default";
static int	preface  = 1;

////////////////////////////////////////////////////////////////////////

static const char *fstack[10] = {"default"};
static int	   fstackx    = 0;

void
font(const char *name, const char *size)
{
	if (!name)
		name = fstack[fstackx];
	if (strcmp(name, "default") == 0) {
		PUTA(":font facename=default size=0x0.");
	} else
		PUTA(":font facename=" << name << " size=" << size << '.');
}

void
beg_example(const char *fontname)
{
	newpara = 0;
	++nofill;
	*out << ":lines align=left.";
	margin(+10);
	fstack[++fstackx] = fontname;
	font(0);
	PUTL();
	newpara = 0;
}

void
end_example()
{
	newpara = 0;
	--nofill;
	--fstackx;
	font(0);
	margin(-10);
	*out << ":elines.";
	PUTL();
	newpara = 0;
}

////////////////////////////////////////////////////////////////////////

void
words(String& line)
{
	int i = 0;
	for (const char *p1 = line.chars(), *end = p1 + line.length();;) {
		while (p1 < end && isspace(*p1))
			++p1;
		if (p1 == end)
			break;
		const char *p2 = p1;
		while (p2 < end && *p2 != ',')
			++p2;
		if (i < MaxW)
			w[i++] = String(p1, p2 - p1);
		if (p2 == end)
			break;
		p1 = p2 + 1;
	}
	while (i < MaxW)
		w[i++] = null;
}

////////////////////////////////////////////////////////////////////////

static int	hstack[6];
static int	hlevel = 0;

void
heading(int level, char *s)
{
	if (istackp != istack)
		return;
	if (f_node) {
		if (preface)
			PUT(":h2." << s << endl << ":lm margin=1.");
	} else {
		if (debug)
			cerr << "Heading, logical level=" << level
			     << " stack level=" << hlevel
			     << " stacked=" << hstack[hlevel];
		if (level > hstack[hlevel])
			hstack[++hlevel] = level;
		else while (level < hstack[hlevel])
			--hlevel;
		if (debug)
			cerr << " panel level=" << hlevel << endl;
		if (node_id) {
			panel_id = node_id;
			node_id = 0;
		} else
			panel_id = ++hdid;
		panel_name = s;
		PUT(":h" << hlevel << " id=hd" << panel_id << '.' << s
			 << endl << ":lm margin=1.");
	}
}


void
Menu::flush()
{
	if (line.length() == 0)
		return;
	int x1 = line.index("&colon.");
	if (x1 >= 0) {
		int x2 = line.index("&colon.", x1+7);
		if (x2 >= 0) {
			String name = line.at(x1+7, x2-x1-7);
			if (name.length() == 0)
				name = line.before(x1);
			if (!table.contains(name))
				table[name] = Name(++hdid);
			for (x2 += 7; x2 < line.length() && isspace(line[x2]); ++x2)
				;
			*out << ":pt.:link reftype=hd refid=hd" << table[name].id
			     << '.' << line.before(x1) << ":elink.:pd."
			     << line.from(x2) << endl;
		}
	}
	line = "";
}

void
node(String name, String next, String prev, String up)
{
	if (table.contains(up)) {
		if (f_node)
			hlevel = table[up].level + 1;
	} else if (name == "Top" || up.length() == 0) {
		if (f_node)
			hlevel = 0;
	} else {
		cerr << "<up> node undefined in '" << name << "', '" << next
			<< "', '" << prev << "', '" << up << '\'' << endl;
		cerr.flush();
		exit(1);
	}
	if (debug)
		cerr << "Define name='" << name << "' next='" << next
		     << "' prev='" << prev << "' up='" << up << "'";
	Name& entry = table[name];
	if (entry.id) {
		if (entry.defined) {
			cerr << "Node '" << name << "' redefined " << endl;
			cerr.flush();
			exit(1);
		}
		entry.defined = 1;
		if (debug)
			cerr << ", known id=" << entry.id << endl;
	} else {
		table[name] = Name(++hdid, 1, hlevel);
		if (debug)
			cerr << ", new id=" << hdid << endl;
	}
	if (f_node && hlevel >= 1 && hlevel <= 6 && istackp == istack) {
		preface = 0;
		PUT(":h" << hlevel << " id=hd" << entry.id << '.' << name
			 << endl << ":lm margin=1.");
	}
	node_name = name;
	node_id = entry.id;
}

void
xref(char *see, String name, String entry, String topic, String file, String manual)
{
	if (debug)
		cerr << "Refer to name='" << name << "' entry='" << entry
		     << "' topic='" << topic << "' file='" << file
		     << "' manual='" << manual << "'";
	if (see)
		PUTS(see);
	if (file.empty()) {
		if (!table.contains(name)) {
			table[name] = Name(++hdid);
			if (debug)
				cerr << " new id=" << hdid << endl;
		} else
			if (debug)
				cerr << " known id=" << table[name].id << endl;
		PUTS(":link reftype=hd refid=hd" << table[name].id << '.');
		if (topic.length()) {
			PUT(topic);
		} else
			PUT(name);
		if (entry.length())
			PUT(": " << entry);
		PUT(":elink.");
	} else
		PUTS("Section " << topic << " of :hp1." << manual << ":ehp1.");
}

////////////////////////////////////////////////////////////////////////

static int current_margin = 0;

static void
set_margin(int indent)
{
	current_margin = indent;
	PUTA(":lm margin=" << (1 + current_margin) << '.');
}

	// > 0: indent
	// < 0: extend
	// = 0: reset
int
margin(int delta)
{
	int old = current_margin;
	if (delta) {
		current_margin += delta;
		if (current_margin < 0)
			current_margin = 0;
	} else
		current_margin = 0;
	PUTA(":lm margin=" << (1 + current_margin) << '.');
	return old;
}

void
item_begin(const char *text, int it, char *ic)
{
	if (istackp == istack) {
		istackp->indent = current_margin;
		istackp->nested = 1;
	}
	++istackp;
	istackp->type = it;
	istackp->cat = ic;
	istackp->beg = Item();
	istackp->end = Item();
	istackp->indent = current_margin;
	switch (it) {
	case 'o':
		istackp->indent += 3;
		break;
	case 'u':
		istackp->indent += 5;
		break;
	case 'p':
		istackp->indent += 12;
		break;
	}
	istackp->nested = 0;
	istackp->count = 0;
	for (ItemType *p = istack; p < istackp; ++p)
		if (p->type == 'p')
			++istackp->nested;
	PUTL();
	if (!istackp->nested)
		PUT(text);
	newpara = 0;
}

void
ItemType::item(const char *text)
{
	newpara = 0;

	if (nested) {
		set_margin((istackp-1)->indent);
		*out << ":p.";
		switch (type) {
		case 'o':
			margin(+1);
			*out << ".&larrow.";
			margin(+2);
			break;
		case 'u':
			margin(+2);
			*out << ++count << '.';
			margin(+3);
			break;
		}
	} else if (type == 'p')
		*out << ":pt.";
	else
		*out << ":li.";

	if (text && *text) {
		if (beg.fontname)
			*out << ":font facename=" << beg.fontname
			     << " size=" FontSize ".";
		if (beg.hpnumber)
			*out << ":hp" << beg.hpnumber << '.';
		if (beg.delimiter)
			*out << beg.delimiter;

		*out << text;

		if (end.delimiter)
			*out << end.delimiter;
		if (end.hpnumber)
			*out << ":ehp" << end.hpnumber << '.';
		if (end.fontname)
			*out << ":font facename=" << end.fontname
			     << " size=" FontSize ".";
	}

	if (type == 'p') {
		if (nested)
			margin(+12);
		else
			*out << ":pd.";
	}
}

void
item_end(const char *text)
{
	PUTL();
	if (istackp->nested)
		newpara = 1;
	else {
		PUT(text);
		newpara = 0;
	}
	--istackp;
	set_margin(istackp->indent);
}

////////////////////////////////////////////////////////////////////////

void
define(String& type, String& name, String *args, String& category)
{
	PUT("!!define "
	 << " type=" << type
	 << " name=" << name
	 << " category=" << category);
	if (args) {
		PUT(" args=");
		for (int i = 0; args[i] != null; ++i)
			PUT(args[i]);
	}
	PUT("!!" << endl);
}

////////////////////////////////////////////////////////////////////////

void
printindex(String& classname)
{
	XClassT& xc = indexes[classname].entries;
	PUT(":parml tsize=50 break=none compact." << endl);
	for (Pix entry = xc.first(); entry; xc.next(entry)) {
		PUT(":pt." << xc.key(entry) << endl << ":pd.");
		XEntry& xe = xc.contents(entry);
		int ne = 0;
		for (Pix item = xe.first(); item; xe.next(item)) {
			if (ne++)
				PUT(".br" << endl);
			XItem& xi = xe(item);
			PUT(":link reftype=hd refid=hd" << xi.id << '.'
			 << xi.title << ":elink." << endl);
		}
	}
	PUT(":eparml.");
	PUTL();
}

////////////////////////////////////////////////////////////////////////

void
single_word(char *text)
{
	int ipf = 0;
	while (*text) {
		char c = *text++;
		switch (c) {
		case ' ':
			if (ipf)
				break;
			PUTS("&rbl.");
			continue;
		case ':':
		case '&':
			ipf = 1;
			break;
		}
		PUTS(c);
	}
}

////////////////////////////////////////////////////////////////////////

void
para()
{
	if (!plevel) {
		*out << ":p.";
		newpara = 0;
	}
}

