///////////////////////////////////////////////////////////////////////////////
// $Id: main.cc,v 1.6 1993/02/10 20:58:21 ak Exp $
///////////////////////////////////////////////////////////////////////////////
// $Log: main.cc,v $
// Revision 1.6  1993/02/10  20:58:21  ak
// Pass menues.
//
// Revision 1.5  1993/02/06  00:09:56  ak
// *** empty log message ***
//
// Revision 1.4  1993/02/05  23:44:09  ak
// Bugfixes and cosmetic changes.
//
// Revision 1.3  1993/02/05  08:44:21  ak
// Statt -c besser Typ vom Output-File.
//
// Revision 1.2  1993/02/04  17:51:20  ak
// *** empty log message ***
//
// Revision 1.1.1.1  1993/02/04  15:21:36  ak
// Texinfo -> OS/2 IPF/INF converter.
//
// Revision 1.1  1993/02/04  15:21:33  ak
// Initial revision
//
///////////////////////////////////////////////////////////////////////////////

static char *rcsid = "$Id: main.cc,v 1.6 1993/02/10 20:58:21 ak Exp $";

#define EXTERN
#define INIT(x) = x
#include "info.h"
#include <fstream.h>
#include <stdio.h>
#include <ctype.h>
#include <getopt.h>
#include <process.h>

void
usage()
{
	cout <<"texi2ipf [options {in [out]]" << endl
	     <<" -Dflag	set Texinfo flag" << endl
	     <<" -Uflag	clear Texinfo flag" << endl
	     <<" -n	use @node to split into panels, not @chapter" << endl
	     <<" -d	debugging aid" << endl
	     <<" -f	flex scanner trace" << endl
	     <<" in	texinfo file, default=stdin" << endl
	     <<" out	inf file (*.inf) or ipf source (else)" << endl;
}

main(int argc, char **argv)
{
	int compile = 0;
	ofstream *outf = 0;

	extern int yy_flex_debug;
	yy_flex_debug = 0;

	GetOpt getopt(argc, argv, "dD:fnU:");
	for (int c; (c = getopt()) != EOF; )
		switch (c) {
		case 'd':
			++debug;
			break;
		case 'D':
			flags[getopt.optarg] = 1;
			break;
		case 'f':
			++yy_flex_debug;
			break;
		case 'n':
			++f_node;
			break;
		case 'U':
			flags[getopt.optarg] = 0;
			break;
		default:
			usage();
			exit(2);
		}
	if (getopt.optind < argc) {
		char *fn = argv[getopt.optind];
		if (freopen(fn, "r", stdin) == NULL) {
			perror(fn);
			exit(1);
		}
	}
	String ipfname, basename;
	if (++getopt.optind < argc) {
		ipfname = argv[getopt.optind];
		int ext = ipfname.index('.', -1);
		if (ext >= 0) {
			basename = ipfname.before(ext);
			if (fcompare(ipfname.from(ext), ".inf") == 0) {
				compile = 1;
				ipfname.from(ext) = ".ipf";
			}
		}
		out = outf = new ofstream(ipfname);
		if (!outf->good()) {
			perror(ipfname);
			exit(1);
		}
	}

	*out << ":userdoc." << endl
	     << ":docprof toc=123456." << endl;

	while ((c = yylex()) > 0)
		if (c == '\n')
			newline();
		else
			PUTS(c);

	*out << ":euserdoc." << endl;

	if (outf) {
		outf->close();

		if (compile) {
			Regex rpath ("[:\\\\/]");
			int split = basename.index(rpath, -1);
			if (split >= 0) {
				String path (basename.through(split));
				_chdrive(toupper(path[0])); // EMX library bug
				_chdir2(path);
				basename.del(0, split + 1);
			}
			int r = spawnlp(0, "ipfc", "ipfc",
				"/w1", "/codepage=850", "/inf",
				basename.chars(), NULL);
			if (r < 0) {
				perror("starting ipfc");
				exit(1);
			} else if (r == 0) {
				basename += ".ipf";
				remove(basename);
			}
		}
	}
			
	return c ? 1 : 0;
}
