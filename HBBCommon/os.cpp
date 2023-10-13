//////////////////////////////////////////////////////////////////////////////
//
//  Database Utility for ASJ Office
//
static char rcsid[] = "$Id: os.cpp,v 1.2 2004/05/27 10:18:40 hori Exp $";
// $Log: os.cpp,v $
// Revision 1.2  2004/05/27 10:18:40  hori
// NoMess
//
// Revision 1.1  2004/05/21 10:19:51  hori
// Add
//
// Revision 1.3  2004/04/20 10:09:24  hori
// No Message
//
// Revision 1.2  2004/04/19 15:41:42  hori
// no message
//
// Revision 1.1  2004/04/14 10:31:59  hori
// add new staff.
//
//////////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "os.h"

int	opterr = 1,		/* if error message should be printed */
	optind = 1,		/* index into parent argv vector */
	optopt,			/* character checked for validity */
	optreset;		/* reset getopt */
LPCTSTR optarg;		/* argument associated with option */

#define	BADCH	_T('?')
#define	BADARG	_T(':')
#define	EMSG	_T("")

/*
 * getopt --
 *	Parse argc/argv argument vector.
 */
int getopt(int nargc, LPCTSTR* nargv, LPCTSTR ostr)
{
	static LPCTSTR place = EMSG;		/* option letter processing */
	LPCTSTR oli;				/* option letter list index */

	if (optreset || !*place) {		/* update scanning pointer */
		optreset = 0;
		if (optind >= nargc || *(place = nargv[optind]) != '-') {
			place = EMSG;
			return (-1);
		}
		if (place[1] && *++place == '-') {	/* found "--" */
			++optind;
			place = EMSG;
			return (-1);
		}
	}					/* option letter okay? */
	if ((optopt = (int)*place++) == (int)':' ||
	    !(oli = _tcschr(ostr, optopt))) {
		/*
		 * if the user didn't specify '-' as an option,
		 * assume it means -1.
		 */
		if (optopt == (int)'-')
			return (-1);
		if (!*place)
			++optind;
		if (opterr && *ostr != ':' && optopt != BADCH)
			(void)fprintf(stderr, "%s: illegal option -- %c\n",
			    nargv[0], optopt);
		return (BADCH);
	}
	if (*++oli != ':') {			/* don't need argument */
		optarg = NULL;
		if (!*place)
			++optind;
	}
	else {					/* need an argument */
		if (*place)			/* no white space */
			optarg = place;
		else if (nargc <= ++optind) {	/* no arg */
			place = EMSG;
			if (*ostr == ':')
				return (BADARG);
			if (opterr)
				(void)fprintf(stderr,
				    "%s: option requires an argument -- %c\n",
				    nargv[0], optopt);
			return (BADCH);
		}
	 	else				/* white space */
			optarg = nargv[optind];
		place = EMSG;
		++optind;
	}
	return (optopt);			/* dump back option letter */
}

int strcasecmp(LPCTSTR s1, LPCTSTR s2)
{
	return _tcsicmp(s1, s2);
}

int strncasecmp(LPCTSTR s1, LPCTSTR s2, size_t len)
{
	return _tcsnicmp(s1, s2, len);
}

LPTSTR strnstr(LPCTSTR s, LPCTSTR find, size_t slen)
{
	TCHAR c, sc;
	size_t len;

	if ((c = *find++) != '\0') {
		len = _tcslen(find);
		do {
			do {
				if ((sc = *s++) == '\0' || slen-- < 1)
					return (NULL);
			} while (sc != c);
			if (len > slen)
				return (NULL);
		} while (_tcsncmp(s, find, len) != 0);
		s--;
	}
	return ((LPTSTR)s);
}

static int int_vasprintf(LPTSTR* result, LPCTSTR format, va_list *args)
{
	LPCTSTR p = format;
	/* Add one to make sure that it is never zero, which might cause malloc
	   to return NULL.  */
	int total_width = _tcslen(format) + 1;
	va_list ap;

	memcpy (&ap, args, sizeof (va_list));

	while (*p != '\0') {
		if (*p++ == '%') {
			while (strchr ("-+ #0", *p))
				++p;
			if (*p == '*') {
				++p;
				total_width += abs (va_arg (ap, int));
			} else {
				total_width += _tcstoul(p, (LPTSTR*)&p, 10);
			}
			if (*p == '.') {
				++p;
				if (*p == '*') {
					++p;
					total_width += abs(va_arg (ap, int));
				} else {
					total_width += _tcstoul(p, (LPTSTR*) &p, 10);
				}
			}
			while (_tcschr (_T("hlL"), *p))
				++p;
			/* Should be big enough for any format specifier except %s and floats.  */
			total_width += 30;
			switch (*p) {
			case _T('d'):
			case _T('i'):
			case _T('o'):
			case _T('u'):
			case _T('x'):
			case _T('X'):
			case _T('c'):
				(void) va_arg(ap, int);
				break;
			case _T('f'):
			case _T('e'):
			case _T('E'):
			case _T('g'):
			case _T('G'):
				(void) va_arg(ap, double);
				/* Since an ieee double can have an exponent of 307, we'll
				   make the buffer wide enough to cover the gross case. */
				total_width += 307;
				break;
			case 's':
				total_width += _tcslen(va_arg (ap, LPTSTR));
				break;
			case 'p':
			case 'n':
				(void) va_arg(ap, LPTSTR);
				break;
			}
			p++;
		}
	}
	*result = (LPTSTR)malloc (total_width * sizeof(TCHAR));
	if (*result != NULL)
		return _vstprintf_s(*result, total_width * sizeof(TCHAR), format, *args);
	return 0;
}

int vasprintf(LPTSTR* result, LPCTSTR format, va_list args)
{
	return int_vasprintf (result, format, &args);
}

int asprintf(LPTSTR* ret, LPCTSTR format, ...)
{
	int res;
	va_list ap;

	va_start(ap, format);
	res = vasprintf(ret, format, ap);
	va_end(ap);

	return res;
}
