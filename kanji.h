//////////////////////////////////////////////////////////////////////////////
//
//  MIME routines for ASJ Office
//
// $Id: kanji.h,v 1.1 2004/04/19 09:39:29 hori Exp $
// $Log: kanji.h,v $
// Revision 1.1  2004/04/19 09:39:29  hori
// No Message
//
// Revision 1.10  2004/04/06 02:44:14  hori
// *** empty log message ***
//
// Revision 1.9  2004/03/11 10:23:57  hori
// no message
//
// Revision 1.8  2004/02/06 10:18:23  hori
// no message
//
// Revision 1.7  2003/10/30 16:15:38  hori
// address
//
// Revision 1.6  2003/10/29 10:45:52  hori
// no message
//
// Revision 1.5  2003/10/02 10:06:25  hori
// mail
//
// Revision 1.4  2003/09/26 11:16:16  hori
// no message
//
// Revision 1.2  2003/09/18 01:25:15  hori
// Fix around Kanji.
//
// Revision 1.1  2003/09/17 12:34:32  hori
// temp add
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __KANJI_H__
#define __KANJI_H__

void JisToSJis(int* ph, int* pl);
bool EKANJI(const unsigned char* p);
bool SKANJI(const unsigned char* p);
unsigned int jhantozen(unsigned char hankaku);
unsigned int shantozen(unsigned char hankaku);
unsigned int jistosjis(unsigned int jis);
unsigned int jistoeuc(unsigned int jis);
unsigned int sjistojis(unsigned int sjis);
unsigned int sjistoeuc(unsigned int sjis);
void sjis2euc(const unsigned char* buf, unsigned char* str);
void euctosjis(unsigned char& knj1, unsigned char& knj2);
void euc2sjis(unsigned char* str);
unsigned int euctojis(unsigned int euc);

int DecodeIso2022jp(char *buf, const char *pszstr);
char* GetISO2022JPStr(char *buf, const char *pstr);
char* EncodeIso2022jp(char *buffer, const char *pszstr);

#endif
