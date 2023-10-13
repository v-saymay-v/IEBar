//////////////////////////////////////////////////////////////////////////////
//
//  MIME routines for ASJ Office
//
#if defined (__GNUC__) && (__GNUC__ >= 2) && (__GNUC_MINOR__ >= 7)
static char rcsid[] = "$Id: kanji.cpp,v 1.1 2004/04/19 09:39:29 hori Exp $";
// $Log: kanji.cpp,v $
// Revision 1.1  2004/04/19 09:39:29  hori
// No Message
//
//////////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include <mbctype.h>
#include "kanji.h"

#define MemoryCopy4(a,b) *(DWORD *)a = *(DWORD *)b

void JisToSJis(int* ph, int* pl)
{
	if (*ph & 1) {
		if (*pl < 0x60)
			*pl += 0x1F;
		else
			*pl += 0x20;
	} else {
		*pl += 0x7E;
	}

	if (*ph < 0x5F)
		*ph = (*ph + 0xE1) >> 1;
	else
		*ph = (*ph + 0x161) >> 1;
}

bool SKANJI(const unsigned char* p)
{
	return (_ismbblead((unsigned int)*p) != 0);
}

bool EKANJI(const unsigned char* p)
{
	unsigned char b1 = *p++;
	if(b1 >= 0xa1 && b1 <= 0xfe) {
		unsigned char b2 = *p;
		if(b2 >= 0xa1 && b2 <= 0xfe) {
			return true;
		}
	}
	return false;
}

unsigned int jhantozen(BYTE c)
{
	static unsigned int z[64] = {
		0x2121,0x2123,0x2156,0x2157,0x2122,0x2126,0x2572,0x2521,
		0x2523,0x2525,0x2527,0x2529,0x2563,0x2565,0x2567,0x2543,
		0x213c,0x2522,0x2524,0x2526,0x2528,0x252a,0x252b,0x252d,
		0x252f,0x2531,0x2533,0x2535,0x2537,0x2539,0x253b,0x253d,
		0x253f,0x2541,0x2544,0x2546,0x2548,0x254a,0x254b,0x254c,
		0x254d,0x254e,0x254f,0x2552,0x2555,0x2558,0x255b,0x255e,
		0x255f,0x2560,0x2561,0x2562,0x2564,0x2566,0x2568,0x2569,
		0x256a,0x256b,0x256c,0x256d,0x256f,0x2573,0x212b,0x212c};

	static unsigned short tbl[] = {
		0x2121,0x212a,0x2149,0x2174,0x2170,0x2173,0x2175,0x2147,
		0x214A,0x214B,0x2176,0x215C,0x2124,0x215d,0x2125,0x213F,
		0x2330,0x2331,0x2332,0x2333,0x2334,0x2335,0x2336,0x2337,
		0x2338,0x2339,0x2127,0x2128,0x2163,0x2161,0x2164,0x2129,
		0x2177,0x2341,0x2342,0x2343,0x2344,0x2345,0x2346,0x2347,
		0x2348,0x2349,0x234a,0x234b,0x234c,0x234d,0x234e,0x234f,
		0x2350,0x2351,0x2352,0x2353,0x2354,0x2355,0x2356,0x2357,
		0x2358,0x2359,0x235a,0x214E,0x2140,0x214f,0x224A,0x2132,
		0x2146,0x2361,0x2362,0x2363,0x2364,0x2365,0x2366,0x2367,
		0x2368,0x2369,0x236a,0x236b,0x236c,0x236d,0x236e,0x236f,
		0x2370,0x2371,0x2372,0x2373,0x2374,0x2375,0x2376,0x2377,
		0x2378,0x2379,0x237a,0x2150,0x2143,0x2151,0x2141 };

	if (c >= 0xa0 && c <= 0xdf)
		return z[c-0xa0];
	if (c < 0x20 || c >= 0x7F)
		return 0;
	return tbl[c-0x20];
}

unsigned int shantozen(BYTE c)
{
	if (!c) return c;
	unsigned int h = jhantozen(c);
	int hib = (h >> 8) & 0xff;
	int lob = h & 0xff;
	JisToSJis(&hib, &lob);
	return (hib << 8) | lob;
}

unsigned int jistosjis(unsigned int jis)
{
	int hib = (jis >> 8) & 0xff;
	int lob = jis & 0xff;
	JisToSJis(&hib, &lob);
	return (hib << 8) | lob;
}

unsigned int jistoeuc(unsigned int jis)
{
    return jis | 0x8080;
}

unsigned int sjistojis(unsigned int sjis)
{
	unsigned int hib, lob;

	hib = (sjis >> 8) & 0xff;
	lob = sjis & 0xff;

	if (hib <= 0x9f) {
		if (lob < 0x9f)
			hib = (hib << 1) - 0xe1;
		else
			hib = (hib << 1) - 0xe0;
	}else {
		if (lob < 0x9f)
			hib = (hib << 1) - 0x161;
		else
			hib = (hib << 1) - 0x160;
	}

	if (lob < 0x7f)
		lob -= 0x1f;
	else if (lob < 0x9f)
		lob -= 0x20;
	else
		lob -= 0x7e;

	return (hib << 8) | lob;
}

unsigned int sjistoeuc(unsigned int sjis)
{
	unsigned int hib, lob;

	hib = (sjis >> 8) & 0xff;
	lob = sjis & 0xff;

	if (hib <= 0x9f) {
		if (lob < 0x9f)
			hib = (hib << 1) - 0xe1;
		else
			hib = (hib << 1) - 0xe0;
	} else {
		if (lob < 0x9f)
			hib = (hib << 1) - 0x161;
		else
			hib = (hib << 1) - 0x160;
	}

	if (lob < 0x7f)
		lob -= 0x1f;
	else if (lob < 0x9f)
		lob -= 0x20;
	else
		lob -= 0x7e;

	hib |= 0x80;
	lob |= 0x80;

	return (hib << 8) | lob;
}

void sjis2euc(const unsigned char* buf, unsigned char* str)
{
	unsigned int t, t1, t2, s, s2;
	int i, j;

	i = 0;
	for (j = 0; buf[j]; j++) {
		s = buf[j];
		if (s >= 0x81 && s <= 0x9f || s >= 0xe0 && s <= 0xfc) {
			s2 = buf[++j];
			if (s2 >= 0x40 && s2 <= 0xfc && s2 != 0x7f) {
				s = (s << 8) | s2;
				t = sjistoeuc(s);
				t1 = (t >> 8);
				t2 = t - (t1 << 8);
				str[i++] = t1;
				str[i++] = t2;
				continue;
			} else {
				str[i++] = s;
				--j;
				continue;
			}
		} else if (s>=0xa1 && s<=0xdf) {
			str[i++] = 0x8e;
			str[i++] = s;
			continue;
		} else {
			str[i++] = s;
			continue;
		}
	}
	str[i] = '\0';
}

void euctosjis( unsigned char& knj1, unsigned char& knj2 )
{
	if( knj1 & 0x01 ){
		knj1 >>= 1;
		if( knj1 < 0x6F )
			knj1 += 0x31;
		else
			knj1 += 0x71;
		if( knj2 > 0xDF )
			knj2 -= 0x60;
		else
			knj2 -= 0x61;
	}else{
		knj1 >>= 1;
		if( knj1 < 0x6F )
			knj1 += 0x30;
		else
			knj1 += 0x70;
		knj2 -= 0x02;
	}
}

void euc2sjis(unsigned char* str)
{
	for (unsigned char * ptr=str; *ptr; ptr++) {
		if( *ptr < 0x80 )
			continue;
		if( !(*++ptr) )
			break;
		if ( *(ptr-1) == 0x8E ) {
			WORD euc = jhantozen(*ptr);
			WORD sjis = jistosjis(euc);
			*(ptr-1) = HIBYTE(sjis);
			*ptr = LOBYTE(sjis);
		} else {
			euctosjis( *(ptr-1), *ptr );
		}
	}
}

unsigned int euctojis(unsigned int euc)
{
	unsigned int jis;

	if ((euc & 0xff00) == 0x8e00)
		jis = jhantozen(euc & 0xff);
	else
		jis = euc & ~0x8080;
	return jis;
}

static int _xbase64_(int a)
{
	#define not_base64_char -59

	if(a >= 'A' && a <= 'Z')
		return a - 'A';
	if(a >= 'a' && a <= 'z')
		return a - 'a' + 26;
	if(a >= '0' && a <= '9')
		return a - '0' + 52;
	if(a == '/')
		return 63;
	if(a == '+')
		return 62;
	if(a == '=')
		return -1;
	return not_base64_char;
}

static int _base64_dec4(char *q, const char *p)
{
	int a , b, c, d;

	a = _xbase64_(p[0]);
	b = _xbase64_(p[1]);
	if(a >= 0 && b >= 0)
		q[0] = (a << 2) | (b >> 4);
	else
		return 0;

	c = _xbase64_(p[2]);
	if(c >= 0)
		q[1] = ((b & 15) << 4) | (c >> 2);
	else
		return 1;

	d = _xbase64_(p[3]);
	if(d >= 0)
		q[2] = ((c & 3) << 6) | d;
	else
		return 2;

	return 3;
}

int DecodeIso2022jp(char *buf, const char *pszstr)
{
	int i, j;
	int nMode = 0;
	const char *p, *q;
	for(p = pszstr, i = 0; *p != 0;) {
		if(_strnicmp(p, "=?ISO-2022-JP?B?", 16) == 0) {
			q = strstr(p, "?=");
			if (!q) {
				buf[i] = *p;
				i++;
				p++;
				nMode = 0;
			} else {
				for(p += 16, j = 0; strncmp(p, "?=", 2);) {
					j += _base64_dec4(buf + i + j, p);
					p += 4;
					if (p > q)
						p = q;
				}
				p += 2;
				i = i + j;
				nMode = 1;
			}
/////
		} else if(_strnicmp(p, "=?SHIFT_JIS?B?", 14) == 0) {
			q = strstr(p, "?=");
			if (!q) {
				i++;
				p++;
				nMode = 0;
			} else {
				for(p += 14, j = 0; strncmp(p, "?=", 2);) {
					j += _base64_dec4(buf + i + j, p);
					p += 4;
				}
				p += 2;
				i = i + j;
				nMode = 1;
			}
/////
		} else if(_strnicmp(p, "=?euc_jp?B?", 11) == 0) {
			q = strstr(p, "?=");
			if (!q) {
				i++;
				p++;
				nMode = 0;
			} else {
				for(p += 11, j = 0; strncmp(p, "?=", 2);) {
					j += _base64_dec4(buf + i + j, p);
					p += 4;
				}
				p += 2;
				i = i + j;
				nMode = 1;
			}
/////
		} else {
			buf[i] = *p;
			i++;
			p++;
			nMode = 0;
		}
	}
	buf[i] = 0;
	return nMode;
}

static unsigned int ToKatakana(unsigned char *pStr, int *pnStep)
{
	if (!_ismbbkana((unsigned int)*pStr))
		return 0;
	++pStr;
	*pnStep = 2;
	return shantozen(*pStr);
}

static bool ConvertExtensionJISChar(char *buffer, DWORD dwCode)
{
	const char *cvrt[] = {
		"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "",
		"ミリ", "キロ", "センチ", "メートル", "グラム", "トン", "アール",
		"ヘクタール", "リットル", "ワット", "カロリー", "ドル", "セント",
		"パーセント", "ミリバール", "ページ", "mm", "cm", "km", "mg", "kg",
		"cc", "平方メートル",
		"", "", "", "", "", "", "", "",
		"平成", "”", "”", "No.", "K.K", "TEL", "(上)", "(中)", "(下)",
		"(左)", "(右)", "(株)", "(有)", "(代)", "明治", "大正", "昭和",
		"≒", "≡", "∫", "円積分", "シグマ", "√",
		"⊥", "∠", "Ｌ", "デルタ", "∵", "∩", "∪"};

	const char *cvrt2[] = {
		"", "i", "ii", "iii", "iv", "v", "vi", "vii", "viii", "ix", "x",
		"￢", "｜", "’", "”", ""};

	char buf[256], sh_buf[256];
	char *p = NULL;
	int n;

	if (dwCode >= 0x2D20 && dwCode <= 0x2D34) {       // 2D20～2D34 : 
		sprintf_s(buf, sizeof(buf), "(%lx)", dwCode - 0x2D20);
	} else if (dwCode >= 0x2D35 && dwCode <= 0x2D7C) { // 2D35～2D7C
		strcpy_s(buf, sizeof(buf), cvrt[dwCode - 0x2D35]);
	} else if (dwCode >= 0x7C70 && dwCode <= 0x7C7F) { // 7C70～7C7F
		strcpy_s(buf, sizeof(buf), cvrt2[dwCode - 0x7C70]);
	} else if (dwCode >= 0x2C24 && dwCode <= 0x2C2F) { // 2C24～2C6F : 
		const char *keisen0[] = {"│", "─"};
		strcpy_s(buf, sizeof(buf), keisen0[((dwCode - 0x2C24) / 2) & 1]);
	} else if (dwCode >= 0x2C30 && dwCode <= 0x2C3F) {
		const char *keisen1[] = {"┌", "┐", "└", "┘"};
		strcpy_s(buf, sizeof(buf), keisen1[(dwCode - 0x2C30) / 4]);
	} else if (dwCode >= 0x2C40 && dwCode <= 0x2C47) {
		p = "├";
	} else if (dwCode >= 0x2C48 && dwCode <= 0x2C4F) {
		p = "┤";
	} else if (dwCode >= 0x2C50 && dwCode <= 0x2C57) {
		p = "┬";
	} else if (dwCode >= 0x2C58 && dwCode <= 0x2C5F) {
		p = "┴";
	} else if (dwCode >= 0x2C60 && dwCode <= 0x2C6F) {
		p = "┼";
	} else if(dwCode >= 0x7921 && dwCode <= 0x7C6E) {
		printf("[JIS:%lu]\n", dwCode);
		return false; // Ver.1.73
	} else {
		return false;
	}

	if (p != NULL)
		strcpy_s(buf, sizeof(buf), p);

	GetISO2022JPStr(sh_buf + 3, buf);

	if (sh_buf[3] == 0x1B && sh_buf[4] == '$' && sh_buf[5] == 'B') {
		 p = sh_buf + 6;
	} else {
		sh_buf[0] = 0x1B; sh_buf[1] = '('; sh_buf[2] = 'B';
		p = sh_buf;
	}

	n = strlen(p);
	if (p[n - 3] == 0x1B && p[n - 2] == '(' && p[n - 1] == 'B') {
		p[n - 3] = 0;
	} else {
		p[n] = 0x1B; p[n + 1] = '$'; p[n + 2] = 'B'; p[n + 3] = 0;
	}

	strcpy_s(buffer, sizeof(buffer), p);
	return true;
}

char *GetISO2022JPStr(char *buf, const char *pstr)
{
	const unsigned char *KI = (const unsigned char*)"\x1B$B";
	const unsigned char *KO = (const unsigned char*)"\x1B(B";
	unsigned char *internal_buf, cvbuf[40];
	const unsigned char *p = (unsigned char *)pstr;
	unsigned char *q;
	int nMode = 0, kc, n;

	internal_buf = (unsigned char *)malloc(strlen(pstr) * 7 + 10);
	if (internal_buf == NULL)
		return NULL;

	memset((char*)internal_buf, 0, strlen(pstr) * 7 + 10);
	q = internal_buf + 8;

	for(; *p; p++, q++) {
		if(SKANJI(p)) {
			if(nMode == 0) {
				if(strcmp((const char*)q - 3, (const char*)KO) == 0) q -= 3;
				else MemoryCopy4((char*)q, (const char*)KI), q += 3;
				nMode = 1;
			}

			WORD w = sjistojis((WORD)(p[0] * 0x100 + p[1]));
			if(ConvertExtensionJISChar((char*)cvbuf, w)) {
				int nLen;
				nLen = strlen((const char*)cvbuf) - 1;
				strcpy_s((char*)q, strlen((const char*)cvbuf), (const char*)cvbuf);
				q += nLen;
			} else {
				q[0] = w / 0x100;
				q[1] = w & 0xff;
				q++;
			}
			p++;
		} else {
			kc = (int)ToKatakana((unsigned char *)p, &n);
			if (kc == 0) {
				if(nMode) {
					if (strcmp((const char*)q - 3, (const char*)KI) == 0) {
						q -= 3;
					} else {
						MemoryCopy4((char*)q, (const char*)KO);
						q += 3;
					}
					nMode = 0;
				}
				*q = *p;
			} else {
				if (nMode == 0) {
					if (strcmp((const char*)q - 3, (const char*)KO) == 0) {
						q -= 3;
					} else {
						MemoryCopy4((char*)q, (const char*)KO);
						q += 3;
					}
					nMode = 1;
				}
				q[0] = kc >> 8;
				q[1] = kc & 255;
				q++;
				p = p + n - 1;
			}
		}
	}

	if (nMode) {
		MemoryCopy4((char*)q, (const char*)KO);
	} else {
		*q = 0;
	}

	if (buf != NULL) {
		strcpy_s(buf, strlen((const char*)internal_buf) - 8, (const char*)internal_buf + 8);
		free(internal_buf);
		return buf;
	}

	return (char*)internal_buf + 8;
}

static int Base64Encode(const char *pBin, int nLength, int *pn, int *pnStat)
{
	unsigned int w=0, c0, c1;

	if(*pn >= nLength)
	{
		if(*pnStat)
		{
			*pnStat = (*pnStat + 1) & 3;
			(*pn)++;
			return '=';
		}
		else return 0;
	}

	c0 = (unsigned char)pBin[*pn];
	if(*pn + 1 == nLength) c1 = 0; else c1 = (unsigned char)pBin[*pn + 1];

	switch(*pnStat)
	{
	case 0:
		w = c0 >> 2, *pnStat = 1;              /* OOOOOO-- -------- */
		break;

	case 1:
		w = (c0 & 3) << 4; (*pn)++;
		w = (w | (c1 >> 4)) & 63, *pnStat = 2; /* ------OO OOOO---- */
		break;

	case 2:
		w = (c0 & 15) << 2; (*pn)++;
		w = (w | (c1 >> 6)) & 63, *pnStat = 3; /* ----OOOO OO------ */
		break;

	case 3:
		w = c0 & 63; (*pn)++; *pnStat = 0;     /* --OOOOOO -------- */
		break;
	}

	if(w <= 25) return (int)w + 'A';
	if(w <= 51) return (int)w - 26 + 'a';
	if(w <= 61) return (int)w - 52 + '0';
	if(w == 62) return '+';
	return '/';

}

/* ヘッダフィールドのエンコード */
char* EncodeIso2022jp(char *buffer, const char *pszstr)
{
	const char *header = "=?ISO-2022-JP?B?" "GyRC"; // 20

	char *buf, enc[9];
	char *q = buffer;
	int nLength = 0, nKanji, nStat, n, m;

	buf = (char*)malloc( strlen(pszstr) * 7 + 10 );
	char *p = buf;

	GetISO2022JPStr(buf, pszstr);
	while(*p) {
		if(*p == 0x1b && *(WORD *)(p + 1) == *(WORD *)"$B") {
			/* ISO-2022-JP */
			p += 3; /* ESC$B */

			for(nKanji = 0;
				p[nKanji] != 0x1b
				||  (*(WORD *)(p + nKanji + 1) != *(WORD *)"(B" && *(WORD *)(p + nKanji + 1) != *(WORD *)"(J");
				nKanji += 2);

			if(nKanji > 0) {
				nKanji += 3; /* ESC(B */

				if(nLength >= 56 - 8 - 2) {
					if(q != buffer)
						if(*(q - 1) == ' ')
							q--;

					MemoryCopy4((char*)q, "\xD\xA \0");
					q += 3;
					nLength = 1;
				}

				strcpy_s((char*)q, strlen((const char*)header), (const char*)header);
				q += 20;
				nLength += 20;

				for(n = nStat = 0; (enc[0] = Base64Encode(p, nKanji, &n, &nStat)) != 0;) {
					enc[1] = Base64Encode(p, nKanji, &n, &nStat);
					enc[2] = Base64Encode(p, nKanji, &n, &nStat);
					enc[3] = Base64Encode(p, nKanji, &n, &nStat);
					enc[4] = Base64Encode(p, nKanji, &n, &nStat);
					enc[5] = Base64Encode(p, nKanji, &n, &nStat);
					enc[6] = Base64Encode(p, nKanji, &n, &nStat);
					enc[7] = Base64Encode(p, nKanji, &n, &nStat);
					enc[8] = 0;

					m = strlen((const char*)enc);
					if(nLength <= 76 - m - 2 - 4) {
						strcpy_s(q, strlen(enc), enc);
						q += m;
						nLength += m;
					} else {
						if(m == 8) {
							strcpy_s(q, strlen("GyhC?=\xD\xA" " =?ISO-2022-JP?B?GyRC"), "GyhC?=\xD\xA" " =?ISO-2022-JP?B?GyRC");
							q = q + (4 + 4) + (17 + 4);
							nLength = (17 + 4);

							strcpy_s(q, strlen(enc), enc);
							q += m;
							nLength += m;
						} else {
							strcpy_s(q, strlen(enc), enc);
							q += m;
							nLength += m;
						}
					}
				}
				MemoryCopy4((char*)q, "?=");
				q += 2;
				p += nKanji;
			}
		} else {
			/* ASCII */
			for(n = 0; p[n] != 0; n++) {
				if(p[n] == ' ') break;
				if(p[n] == 0x1b && *(WORD *)(p + 1 + n) == *(WORD *)"$B")
					break;
			}

			if(nLength + n > 76) {
				if(q != buffer)
					if(*(q - 1) == ' ')
						q--;

				MemoryCopy4((char*)q, "\xD\xA \0");
				q += 3;
				nLength = 1;
			}

			if(p[n] == ' ')
				n++;

		//	CopyMemory(q, p, n);
			memcpy(q, p, n);
			//q[n] = 0;
			//myprintf("%s_", q);
			q += n;
			nLength += n;

			if(n) p += n;
			else  p++;
		}
	}
	*q = 0;
	free(buf);

	return buffer;
}
