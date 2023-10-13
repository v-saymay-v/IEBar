//////////////////////////////////////////////////////////////////////////////
//
//  CRC32 (“ú–{Œê)
//
// $Id: encrypt.h,v 1.1 2004/05/21 10:19:51 hori Exp $
// $Log: encrypt.h,v $
// Revision 1.1  2004/05/21 10:19:51  hori
// Add
//
// Revision 1.1  2004/05/09 16:01:42  hori
// no message
//
// Revision 1.2  2004/01/05 10:08:06  hori
// no message
//
// Revision 1.1  2003/09/26 11:16:11  hori
// no message
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ENCRYPT_H__
#define __ENCRYPT_H__

void encrypt(char* textarray, const char* pass, char** strbuf);
void decrypt(const char* text, const char* pass, char** arraybuf);

#endif
