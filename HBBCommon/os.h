//////////////////////////////////////////////////////////////////////////////
//
//  MIME routines for ASJ Office(“ú–{Œê)
//
// $Id: os.h,v 1.2 2004/05/27 10:18:41 hori Exp $
// $Log: os.h,v $
// Revision 1.2  2004/05/27 10:18:41  hori
// NoMess
//
// Revision 1.1  2004/05/21 10:19:51  hori
// Add
//
// Revision 1.2  2004/04/20 10:09:24  hori
// No Message
//
// Revision 1.1  2004/04/14 10:31:59  hori
// add new staff.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __OS_H__
#define __OS_H__

int getopt(int nargc, LPCTSTR* nargv, LPCTSTR ostr);
LPTSTR strnstr(LPCTSTR s, LPCTSTR find, size_t slen);
int strcasecmp(LPCTSTR s1, LPCTSTR s2);
int strncasecmp(LPCTSTR s1, LPCTSTR s2, size_t len);
int vasprintf(LPTSTR* ret, LPCTSTR format, va_list ap);
int asprintf(LPTSTR* ret, LPCTSTR format, ...);

#endif
