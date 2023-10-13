#include "StdAfx.h"
#include <io.h>
//#include <schannel.h>
#define SECURITY_WIN32
#include <security.h>
#include <sspi.h>
#include <Wininet.h>
#include <Mswsock.h>
#include "os.h"
#include "httppost.h"
/*
#define SSL_PORT 443
#define IO_BUFFER_SIZE  0x10000
#define DLL_NAME _T("Secur32.dll")
#define NT4_DLL_NAME _T("Security.dll")
*/
#ifndef WC_NO_BEST_FIT_CHARS
//	#define WC_NO_BEST_FIT_CHARS	0x00000400
	#define WC_NO_BEST_FIT_CHARS	0
#endif
BOOL			fUseProxy      = FALSE;
CHAR			pszProxyServer[256] = "proxy";
INT				iProxyPort     = 80;
/*
INT				iPortNumber    = SSL_PORT;
LPSTR			pszUserName    = NULL;
DWORD			dwProtocol     = 0;
ALG_ID			aiKeyExch      = 0;
HCERTSTORE		hMyCertStore   = NULL;
HMODULE			g_hSecurity    = NULL;
SCHANNEL_CRED	SchannelCred;
PSecurityFunctionTable g_pSSPI;
*/
extern "C" VOID PASCAL EXPORT DbgMessageBox(LPCTSTR format, ...);

int Http_Head_Get_Result(const TCHAR* chp_host, char** chpp_result)
{
	#define BUF_SIZ 65536

	int err;
	int len;
	SOCKET sd;
	LPTSTR chp_header;
	LPSTR chp_buf;
	LPSTR chp_str;
	char cha_temp[4096];
	struct sockaddr_in sa;
	struct hostent *he;
	struct servent *service;

	WSADATA wsadata;
	err = WSAStartup(2, &wsadata);
	if (err) {
		err = WSAStartup(1, &wsadata);
		if (err) {
			return err;
		}
	} else if (LOBYTE(wsadata.wVersion) < 2) {
	    WSACleanup();
		err = WSAStartup(1, &wsadata);
		if (err) {
			return err;
		}
	}
	*chpp_result = NULL;

	sd = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, NULL, 0);
	if (sd == INVALID_SOCKET) {
		err = WSAGetLastError();
	    WSACleanup();
		return err;
	}

#ifdef _UNICODE
	ZeroMemory(cha_temp, sizeof(cha_temp));
	WideCharToMultiByte(CP_THREAD_ACP, WC_NO_BEST_FIT_CHARS, chp_host, _tcslen(chp_host), cha_temp, ARRAYSIZE(cha_temp)-1, NULL, NULL);
#else
	strcpy(cha_temp, chp_host);
#endif
	cha_temp[_tcslen(chp_host)] = 0;
	he = gethostbyname(cha_temp);
	if (!he) {
		err = WSAGetLastError();
	    WSACleanup();
		return err;
	}

	memset(&sa, 0, sizeof(sa));
	sa.sin_family = AF_INET;
	memcpy(&sa.sin_addr, he->h_addr_list[0], he->h_length);
	service = getservbyname("http","tcp");
	if (service){
		/* 成功したらポート番号をコピー */
		sa.sin_port = service->s_port;
	} else {
		/* 失敗したら80番に決め打ち */
		sa.sin_port = 80;
	}
	err = WSAConnect(sd, (struct sockaddr *)&sa, sizeof(sa), NULL, NULL, NULL, NULL);
	if (err == SOCKET_ERROR){
		err = WSAGetLastError();
		closesocket(sd);
	    WSACleanup();
		return err;
	}

	asprintf(&chp_header, _T("HEAD / HTTP/1.0\r\nHost: %s\r\n\r\n"), chp_host);
#ifdef _UNICODE
	ZeroMemory(cha_temp, sizeof(cha_temp));
	WideCharToMultiByte(CP_THREAD_ACP, WC_NO_BEST_FIT_CHARS, chp_header, _tcslen(chp_header), cha_temp, ARRAYSIZE(cha_temp)-1, NULL, NULL);
#else
	strcpy(cha_temp, chp_header);
#endif
    free(chp_header);

	len = send(sd, cha_temp, strlen(cha_temp), 0);
	if (len == SOCKET_ERROR) {
		err = WSAGetLastError();
		closesocket(sd);
	    WSACleanup();
		return 1;
	}

	chp_buf = (LPSTR)malloc(BUF_SIZ+1);
	memset(chp_buf, '\0', BUF_SIZ+1);
	chp_str = chp_buf;
	while (true) {
		int siz = BUF_SIZ - (chp_str - chp_buf);
		if (siz <= 0)
			break;
		len = recv(sd, chp_str, siz, 0);
		if (!len) {
			break;
		} else if (len == SOCKET_ERROR) {
			err = WSAGetLastError();
			closesocket(sd);
			WSACleanup();
			free(chp_buf);
			return err;
		}
		chp_str += len;
	}
	*chp_str = '\0';

	closesocket(sd);
    WSACleanup();

	*chpp_result = chp_buf;

	return 0;
}

#ifdef _UNICODE
int Http_Head_Get_Result(const TCHAR* chp_host, TCHAR** chpp_result)
{
	char* chp_buf;
	int err = Http_Head_Get_Result(chp_host, &chp_buf);
	if (err)
		return err;

	*chpp_result = (LPTSTR)malloc((strlen(chp_buf) + 1)*sizeof(TCHAR));
	ZeroMemory(*chpp_result, (strlen(chp_buf) + 1)*sizeof(TCHAR));
	MultiByteToWideChar(CP_THREAD_ACP, MB_COMPOSITE, chp_buf, strlen(chp_buf), *chpp_result, strlen(chp_buf) + 1);
	free(chp_buf);
	return 0;
}
#endif

int Http_Post_Get_Result(const TCHAR* chp_host, const TCHAR* chp_path, const TCHAR* chp_params, const TCHAR* chp_cookie, char** chpp_result)
{
	#define BUF_SIZ 65536

	int len;
	int err;
	SOCKET sd;
	LPTSTR chp_header;
	LPSTR chp_buf;
	LPSTR chp_str;
	char cha_temp[4096];
	struct sockaddr_in sa;
	struct hostent *he;
	struct servent *service;

	WSADATA wsadata;
	err = WSAStartup(2, &wsadata);
	if (err) {
		err = WSAStartup(1, &wsadata);
		if (err) {
			return err;
		}
	} else if (LOBYTE(wsadata.wVersion) < 2) {
	    WSACleanup();
		err = WSAStartup(1, &wsadata);
		if (err) {
			return err;
		}
	}
	*chpp_result = NULL;

	sd = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, NULL, 0);
	if (sd == INVALID_SOCKET) {
		err = WSAGetLastError();
	    WSACleanup();
		return err;
	}

#ifdef _UNICODE
	ZeroMemory(cha_temp, sizeof(cha_temp));
	WideCharToMultiByte(CP_THREAD_ACP, WC_NO_BEST_FIT_CHARS, chp_host, _tcslen(chp_host), cha_temp, ARRAYSIZE(cha_temp)-1, NULL, NULL);
#else
	strcpy(cha_temp, chp_host);
#endif
	cha_temp[_tcslen(chp_host)] = 0;
	he = gethostbyname(cha_temp);
	if (!he) {
		err = WSAGetLastError();
	    WSACleanup();
		return err;
	}

	memset(&sa, 0, sizeof(sa));
	sa.sin_family = AF_INET;
	memcpy(&sa.sin_addr, he->h_addr_list[0], he->h_length);
	service = getservbyname("http","tcp");
	if (service){
		// 成功したらポート番号をコピー
		sa.sin_port = service->s_port;
	} else {
		// 失敗したら80番に決め打ち
		sa.sin_port = 80;
	}

	err = WSAConnect(sd, (struct sockaddr *)&sa, sizeof(sa), NULL, NULL, NULL, NULL);
	if (err == SOCKET_ERROR){
		err = WSAGetLastError();
		closesocket(sd);
	    WSACleanup();
		return err;
	}

	if (chp_cookie && chp_cookie[0]) {
		asprintf(&chp_header,
			_T("POST %s HTTP/1.0\r\n")
			_T("%s")
			_T("Host: %s\r\n")
			_T("Content-Type: text/plain; charset=Shift_JIS\r\n")
			_T("Content-length: %d\r\n\r\n")
			_T("%s\r\n\r\n"),
			chp_path, chp_cookie, chp_host, _tcslen(chp_params), chp_params);
	} else {
		asprintf(&chp_header,
			_T("POST %s HTTP/1.0\r\n")
			_T("Host: %s\r\n")
			_T("Content-Type: text/plain; charset=Shift_JIS\r\n")
			_T("Content-length: %d\r\n\r\n")
			_T("%s\r\n\r\n"),
			chp_path, chp_host, _tcslen(chp_params), chp_params);
	}
#ifdef _UNICODE
	ZeroMemory(cha_temp, sizeof(cha_temp));
	WideCharToMultiByte(CP_THREAD_ACP, WC_NO_BEST_FIT_CHARS, chp_header, _tcslen(chp_header), cha_temp, ARRAYSIZE(cha_temp)-1, NULL, NULL);
#else
	strcpy(cha_temp, chp_header);
#endif
    free(chp_header);

	len = send(sd, cha_temp, strlen(cha_temp), 0);
	if (len == SOCKET_ERROR) {
		err = WSAGetLastError();
	    WSACleanup();
		return err;
	}

	chp_buf = (LPSTR)malloc(BUF_SIZ+1);
	memset(chp_buf, '\0', BUF_SIZ+1);
	chp_str = chp_buf;
	while (true) {
		int siz = BUF_SIZ - (chp_str - chp_buf);
		if (siz <= 0)
			break;
		len = recv(sd, chp_str, siz, 0);
		if (!len) {
			break;
		} else if (len == SOCKET_ERROR) {
			err = WSAGetLastError();
			closesocket(sd);
			WSACleanup();
			free(chp_buf);
			return err;
		}
		chp_str += len;
	}
	*chp_str = '\0';

	closesocket(sd);
    WSACleanup();

	*chpp_result = chp_buf;

	return err;
}

#ifdef _UNICODE
int Http_Post_Get_Result(const TCHAR* chp_host, const TCHAR* chp_path, const TCHAR* chp_params, const TCHAR* chp_cookie, TCHAR** chpp_result)
{
	char* chp_buf;
	int err = Http_Post_Get_Result(chp_host, chp_path, chp_params, chp_cookie, &chp_buf);
	if (err)
		return err;

	*chpp_result = (LPTSTR)malloc((strlen(chp_buf) + 1)*sizeof(TCHAR));
	ZeroMemory(*chpp_result, (strlen(chp_buf) + 1)*sizeof(TCHAR));
	MultiByteToWideChar(CP_THREAD_ACP, MB_COMPOSITE, chp_buf, strlen(chp_buf), *chpp_result, strlen(chp_buf) + 1);
	free(chp_buf);
	return 0;
}
#endif

/*
static DWORD Read_From_Socket(SOCKET sock, PUCHAR pageBuf, DWORD contentLength)
{
	fd_set rfds;
	DWORD bytesRead;
	DWORD ret;
	int flg;
	int selectRet;

	ret = 1;
	bytesRead = 0;
	do {
		FD_ZERO(&rfds);
		FD_SET(sock, &rfds);

		selectRet = select(sock+1, &rfds, NULL, NULL, NULL);
		if(selectRet == 0) {
			TRACE(_T("**** Error select returns 0\n"));
			return (DWORD)-1;
		} else if(selectRet == -1) {
			TRACE(_T("**** Error select returns -1\n"));
			return (DWORD)-1;
		}

		ret = WSARecvEx(sock, (LPSTR)pageBuf + bytesRead, contentLength - bytesRead, &flg);
		if (ret == SOCKET_ERROR) {
			TRACE(_T("**** Error %d receiving message from proxy\n"), WSAGetLastError());
			return (DWORD)-1;
		}

		bytesRead += ret;
	} while (ret >= contentLength);
	return bytesRead;
}

#ifdef _DEBUG
static void PrintHexDump(DWORD length, PBYTE buffer)
{
	DWORD i,count,index;
	CHAR rgbDigits[]="0123456789abcdef";
	CHAR rgbLine[100];
	TCHAR trgbLine[100];
	CHAR cbLine;

    for (index = 0; length; length -= count, buffer += count, index += count) {
		count = (length > 16) ? 16:length;
		sprintf(rgbLine, "%4.4x  ",index);
		cbLine = 6;

		for (i=0;i<count;i++) {
			rgbLine[cbLine++] = rgbDigits[buffer[i] >> 4];
			rgbLine[cbLine++] = rgbDigits[buffer[i] & 0x0f];
			if (i == 7) {
				rgbLine[cbLine++] = ':';
			} else {
				rgbLine[cbLine++] = ' ';
			}
		}
		for (; i < 16; i++) {
			rgbLine[cbLine++] = ' ';
			rgbLine[cbLine++] = ' ';
			rgbLine[cbLine++] = ' ';
		}

		rgbLine[cbLine++] = ' ';

		for (i = 0; i < count; i++) {
			if (buffer[i] < 32 || buffer[i] > 126 || buffer[i] == '%') {
				rgbLine[cbLine++] = '.';
			} else {
				rgbLine[cbLine++] = buffer[i];
			}
		}

		rgbLine[cbLine++] = 0;
#ifdef _UNICODE
		ZeroMemory(trgbLine, sizeof(trgbLine));
		MultiByteToWideChar(CP_THREAD_ACP, MB_COMPOSITE, rgbLine, strlen(rgbLine), trgbLine, ARRAYSIZE(trgbLine));
#else
		strcpy(trgbLine, rgbLine);
#endif
		TRACE(_T("%s\n"), trgbLine);
	}
}

static void DisplayCertChain(
	PCCERT_CONTEXT  pServerCert,
	BOOL            fLocal)
{
	TCHAR szName[1000];
	PCCERT_CONTEXT pCurrentCert;
	PCCERT_CONTEXT pIssuerCert;
	DWORD dwVerificationFlags;

	TRACE(_T("\n"));

	// display leaf name
	if (!CertNameToStr(pServerCert->dwCertEncodingType,
					   &pServerCert->pCertInfo->Subject,
					   CERT_X500_NAME_STR | CERT_NAME_STR_NO_PLUS_FLAG,
					   szName, sizeof(szName)))
	{
		TRACE(_T("**** Error 0x%x building subject name\n"), GetLastError());
	}
	if (fLocal) {
		TRACE(_T("Client subject: %s\n"), szName);
	} else {
		TRACE(_T("Server subject: %s\n"), szName);
	}
	if (!CertNameToStr(pServerCert->dwCertEncodingType,
					   &pServerCert->pCertInfo->Issuer,
					   CERT_X500_NAME_STR | CERT_NAME_STR_NO_PLUS_FLAG,
					   szName, sizeof(szName)))
	{
		TRACE(_T("**** Error 0x%x building issuer name\n"), GetLastError());
	}
	if (fLocal) {
		TRACE(_T("Client issuer: %s\n"), szName);
	} else {
		TRACE(_T("Server issuer: %s\n\n"), szName);
	}

	// display certificate chain
	pCurrentCert = pServerCert;
	while(pCurrentCert != NULL) {
		dwVerificationFlags = 0;
		pIssuerCert = CertGetIssuerCertificateFromStore(pServerCert->hCertStore,
														pCurrentCert,
														NULL,
														&dwVerificationFlags);
		if (pIssuerCert == NULL) {
			if (pCurrentCert != pServerCert) {
				CertFreeCertificateContext(pCurrentCert);
			}
			break;
		}

		if (!CertNameToStr(pIssuerCert->dwCertEncodingType,
						   &pIssuerCert->pCertInfo->Subject,
						   CERT_X500_NAME_STR | CERT_NAME_STR_NO_PLUS_FLAG,
						   szName, sizeof(szName)))
		{
			TRACE(_T("**** Error 0x%x building subject name\n"), GetLastError());
		}
		TRACE(_T("CA subject: %s\n"), szName);
		if (!CertNameToStr(pIssuerCert->dwCertEncodingType,
						   &pIssuerCert->pCertInfo->Issuer,
						   CERT_X500_NAME_STR | CERT_NAME_STR_NO_PLUS_FLAG,
						   szName, sizeof(szName)))
		{
			TRACE(_T("**** Error 0x%x building issuer name\n"), GetLastError());
		}
		TRACE(_T("CA issuer: %s\n\n"), szName);

		if (pCurrentCert != pServerCert) {
			CertFreeCertificateContext(pCurrentCert);
		}
		pCurrentCert = pIssuerCert;
		pIssuerCert = NULL;
	}
}

static void DisplayConnectionInfo(CtxtHandle *phContext)
{
	SECURITY_STATUS Status;
	SecPkgContext_ConnectionInfo ConnectionInfo;

	Status = g_pSSPI->QueryContextAttributes(phContext,
									SECPKG_ATTR_CONNECTION_INFO,
									(PVOID)&ConnectionInfo);
	if (Status != SEC_E_OK) {
		TRACE(_T("Error 0x%x querying connection info\n"), Status);
		return;
	}

	TRACE(_T("\n"));

	switch(ConnectionInfo.dwProtocol) {
		case SP_PROT_TLS1_CLIENT:
			TRACE(_T("Protocol: TLS1\n"));
			break;

		case SP_PROT_SSL3_CLIENT:
			TRACE(_T("Protocol: SSL3\n"));
			break;

		case SP_PROT_PCT1_CLIENT:
			TRACE(_T("Protocol: PCT\n"));
			break;

		case SP_PROT_SSL2_CLIENT:
			TRACE(_T("Protocol: SSL2\n"));
			break;

		default:
			TRACE(_T("Protocol: 0x%x\n"), ConnectionInfo.dwProtocol);
	}

	switch(ConnectionInfo.aiCipher) {
		case CALG_RC4: 
			TRACE(_T("Cipher: RC4\n"));
			break;

		case CALG_3DES: 
			TRACE(_T("Cipher: Triple DES\n"));
			break;

		case CALG_RC2: 
			TRACE(_T("Cipher: RC2\n"));
			break;

		case CALG_DES: 
		case CALG_CYLINK_MEK:
			TRACE(_T("Cipher: DES\n"));
			break;

		case CALG_SKIPJACK: 
			TRACE(_T("Cipher: Skipjack\n"));
			break;

		default: 
			TRACE(_T("Cipher: 0x%x\n"), ConnectionInfo.aiCipher);
	}

	TRACE(_T("Cipher strength: %d\n"), ConnectionInfo.dwCipherStrength);

	switch(ConnectionInfo.aiHash) {
		case CALG_MD5: 
			TRACE(_T("Hash: MD5\n"));
			break;

		case CALG_SHA: 
			TRACE(_T("Hash: SHA\n"));
			break;

		default: 
			TRACE(_T("Hash: 0x%x\n"), ConnectionInfo.aiHash);
	}

	TRACE(_T("Hash strength: %d\n"), ConnectionInfo.dwHashStrength);

	switch(ConnectionInfo.aiExch)
	{
		case CALG_RSA_KEYX: 
		case CALG_RSA_SIGN: 
			TRACE(_T("Key exchange: RSA\n"));
			break;

		case CALG_KEA_KEYX: 
			TRACE(_T("Key exchange: KEA\n"));
			break;

		case CALG_DH_EPHEM:
			TRACE(_T("Key exchange: DH Ephemeral\n"));
			break;

		default: 
			TRACE(_T("Key exchange: 0x%x\n"), ConnectionInfo.aiExch);
	}

	TRACE(_T("Key exchange strength: %d\n"), ConnectionInfo.dwExchStrength);
}

static void DisplayWinVerifyTrustError(DWORD Status)
{
	LPSTR pszName = NULL;

	switch(Status)
	{
		case CERT_E_EXPIRED:                pszName = "CERT_E_EXPIRED";                 break;
		case CERT_E_VALIDITYPERIODNESTING:  pszName = "CERT_E_VALIDITYPERIODNESTING";   break;
		case CERT_E_ROLE:                   pszName = "CERT_E_ROLE";                    break;
		case CERT_E_PATHLENCONST:           pszName = "CERT_E_PATHLENCONST";            break;
		case CERT_E_CRITICAL:               pszName = "CERT_E_CRITICAL";                break;
		case CERT_E_PURPOSE:                pszName = "CERT_E_PURPOSE";                 break;
		case CERT_E_ISSUERCHAINING:         pszName = "CERT_E_ISSUERCHAINING";          break;
		case CERT_E_MALFORMED:              pszName = "CERT_E_MALFORMED";               break;
		case CERT_E_UNTRUSTEDROOT:          pszName = "CERT_E_UNTRUSTEDROOT";           break;
		case CERT_E_CHAINING:               pszName = "CERT_E_CHAINING";                break;
		case TRUST_E_FAIL:                  pszName = "TRUST_E_FAIL";                   break;
		case CERT_E_REVOKED:                pszName = "CERT_E_REVOKED";                 break;
		case CERT_E_UNTRUSTEDTESTROOT:      pszName = "CERT_E_UNTRUSTEDTESTROOT";       break;
		case CERT_E_REVOCATION_FAILURE:     pszName = "CERT_E_REVOCATION_FAILURE";      break;
		case CERT_E_CN_NO_MATCH:            pszName = "CERT_E_CN_NO_MATCH";             break;
		case CERT_E_WRONG_USAGE:            pszName = "CERT_E_WRONG_USAGE";             break;
		default:                            pszName = "(unknown)";                      break;
	}

	TRACE(_T("Error 0x%x (%s) returned by CertVerifyCertificateChainPolicy!\n"), Status, pszName);
}
#endif

BOOL LoadSecurityLibrary(void)
{
	INIT_SECURITY_INTERFACE         pInitSecurityInterface;
//	QUERY_CREDENTIALS_ATTRIBUTES_FN pQueryCredentialsAttributes;
	OSVERSIONINFO VerInfo;
	TCHAR lpszDLL[MAX_PATH];

	//
	//  Find out which security DLL to use, depending on
	//  whether we are on Win2K, NT or Win9x
	//

	VerInfo.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
	if (!GetVersionEx (&VerInfo)) {
        return FALSE;
    }

	if (VerInfo.dwPlatformId == VER_PLATFORM_WIN32_NT &&
		VerInfo.dwMajorVersion == 4) {
		_tcscpy (lpszDLL, NT4_DLL_NAME );
	} else if (VerInfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS ||
				VerInfo.dwPlatformId == VER_PLATFORM_WIN32_NT ) {
		_tcscpy (lpszDLL, DLL_NAME );
	} else {
		return FALSE;
	}

	//
	//  Load Security DLL
	//

	g_hSecurity = LoadLibrary(lpszDLL);
	if (g_hSecurity == NULL) {
		TRACE(_T("Error 0x%x loading %s.\n"), GetLastError(), lpszDLL);
		return FALSE;
	}

	pInitSecurityInterface = 
		(INIT_SECURITY_INTERFACE)GetProcAddress(
									g_hSecurity,
									"InitSecurityInterfaceW");
	if (pInitSecurityInterface == NULL) {
		TRACE(_T("Error 0x%x reading InitSecurityInterface entry point.\n"), GetLastError());
		FreeLibrary(g_hSecurity);
		g_hSecurity = NULL;
		return FALSE;
	}

	g_pSSPI = pInitSecurityInterface();
	if (g_pSSPI == NULL) {
		TRACE(_T("Error 0x%x reading security interface.\n"), GetLastError());
		FreeLibrary(g_hSecurity);
		g_hSecurity = NULL;
		return FALSE;
	}

	return TRUE;
}

void UnloadSecurityLibrary()
{
	FreeLibrary(g_hSecurity);
	g_hSecurity = NULL;
}

static SECURITY_STATUS CreateCredentials(
	LPSTR pszUserName,			// in
	PCredHandle phCreds)		// out
{
	TimeStamp       tsExpiry;
	SECURITY_STATUS Status;
	DWORD           cSupportedAlgs = 0;
	ALG_ID          rgbSupportedAlgs[16];
	PCCERT_CONTEXT  pCertContext = NULL;

	// Open the "MY" certificate store, which is where Internet Explorer
	// stores its client certificates.
	if (hMyCertStore == NULL) {
		hMyCertStore = CertOpenSystemStore(0, _T("MY"));
		if (!hMyCertStore) {
			TRACE(_T("**** Error 0x%x returned by CertOpenSystemStore\n"), GetLastError());
			return SEC_E_NO_CREDENTIALS;
		}
	}

	//
	// If a user name is specified, then attempt to find a client
	// certificate. Otherwise, just create a NULL credential.
	//

	if (pszUserName) {
		// Find client certificate. Note that this sample just searchs for a 
		// certificate that contains the user name somewhere in the subject name.
		// A real application should be a bit less casual.
		pCertContext = CertFindCertificateInStore(hMyCertStore, 
												  X509_ASN_ENCODING, 
												  0,
												  CERT_FIND_SUBJECT_STR_A,
												  pszUserName,
												  NULL);
		if (pCertContext == NULL) {
			TRACE(_T("**** Error 0x%x returned by CertFindCertificateInStore\n"), GetLastError());
			return SEC_E_NO_CREDENTIALS;
		}
	}

	//
	// Build Schannel credential structure. Currently, this sample only
	// specifies the protocol to be used (and optionally the certificate, 
	// of course). Real applications may wish to specify other parameters 
	// as well.
	//

	ZeroMemory(&SchannelCred, sizeof(SchannelCred));

	SchannelCred.dwVersion  = SCHANNEL_CRED_VERSION;
	if (pCertContext) {
		SchannelCred.cCreds     = 1;
		SchannelCred.paCred     = &pCertContext;
	}

	SchannelCred.grbitEnabledProtocols = dwProtocol;

	if (aiKeyExch) {
		rgbSupportedAlgs[cSupportedAlgs++] = aiKeyExch;
	}

	if (cSupportedAlgs) {
		SchannelCred.cSupportedAlgs    = cSupportedAlgs;
		SchannelCred.palgSupportedAlgs = rgbSupportedAlgs;
	}

	SchannelCred.dwFlags |= SCH_CRED_NO_DEFAULT_CREDS;

	// The SCH_CRED_MANUAL_CRED_VALIDATION flag is specified because
	// this sample verifies the server certificate manually. 
	// Applications that expect to run on WinNT, Win9x, or WinME 
	// should specify this flag and also manually verify the server
	// certificate. Applications running on newer versions of Windows can
	// leave off this flag, in which case the InitializeSecurityContext
	// function will validate the server certificate automatically.
	SchannelCred.dwFlags |= SCH_CRED_MANUAL_CRED_VALIDATION;

	//
	// Create an SSPI credential.
	//

	Status = g_pSSPI->AcquireCredentialsHandle(
						NULL,                   // Name of principal
						UNISP_NAME,             // Name of package
						SECPKG_CRED_OUTBOUND,   // Flags indicating use
						NULL,                   // Pointer to logon ID
						&SchannelCred,          // Package specific data
						NULL,                   // Pointer to GetKey() func
						NULL,                   // Value to pass to GetKey()
						phCreds,                // (out) Cred Handle
						&tsExpiry);             // (out) Lifetime (optional)
	if (Status != SEC_E_OK) {
		TRACE(_T("**** Error 0x%x returned by AcquireCredentialsHandle\n"), Status);
		goto cleanup;
	}

cleanup:
	//
	// Free the certificate context. Schannel has already made its own copy.
	//

	if (pCertContext) {
		CertFreeCertificateContext(pCertContext);
	}

	return Status;
}

static INT ConnectToServer(
	LPCSTR   pszServerName,	// in
	INT      iPortNumber,	// in
	SOCKET * pSocket)		// out
{
	SOCKET Socket;
	struct sockaddr_in sin;
	struct hostent *hp;

	Get_Proxy_Info();

	Socket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, NULL, 0);
//	Socket = socket(PF_INET, SOCK_STREAM, 0);
	if (Socket == INVALID_SOCKET) {
		TRACE(_T("**** Error %d creating socket\n"), WSAGetLastError());
		return WSAGetLastError();
	}

	if (fUseProxy) {
		sin.sin_family = AF_INET;
	//	sin.sin_port = ntohs((u_short)iProxyPort);
		WSANtohs(Socket, (u_short)iProxyPort, &sin.sin_port);

		if ((hp = gethostbyname(pszProxyServer)) == NULL) {
			TRACE(_T("**** Error %d returned by gethostbyname\n"), WSAGetLastError());
			return WSAGetLastError();
        } else {
			memcpy(&sin.sin_addr, hp->h_addr, 4);
		}
    } else {
		sin.sin_family = AF_INET;
	//	sin.sin_port = htons((u_short)iPortNumber);
		WSANtohs(Socket, (u_short)iPortNumber, &sin.sin_port);

		if ((hp = gethostbyname(pszServerName)) == NULL) {
			TRACE(_T("**** Error %d returned by gethostbyname\n"), WSAGetLastError());
			return WSAGetLastError();
        } else {
			memcpy(&sin.sin_addr, hp->h_addr, 4);
		}
	}

	if (WSAConnect(Socket, (struct sockaddr *)&sin, sizeof(sin), NULL, NULL, NULL, NULL) == SOCKET_ERROR) {
//	if (connect(Socket, (struct sockaddr *)&sin, sizeof(sin)) == SOCKET_ERROR) {
		TRACE(_T("**** Error %d connecting to \"%s\" (%s)\n"), 
			WSAGetLastError(),
			pszServerName, 
			inet_ntoa(sin.sin_addr));
		closesocket(Socket);
		return WSAGetLastError();
	}

    if (fUseProxy) {
		int flg;
		BYTE  pbMessage[200]; 
		DWORD cbMessage;
		DWORD Flags = 0;
		WSABUF DataBuf;

		// Build message for proxy server
		strcpy((LPSTR)pbMessage, "CONNECT ");
		strcat((LPSTR)pbMessage, pszServerName);
		strcat((LPSTR)pbMessage, ":");
		_itoa(iPortNumber, (LPSTR)pbMessage + strlen((LPSTR)pbMessage), 10);
		strcat((LPSTR)pbMessage, " HTTP/1.0\r\nUser-Agent: webclient\r\n\r\n");
	//	cbMessage = (DWORD)strlen((LPSTR)pbMessage);
		DataBuf.len = (DWORD)strlen((LPSTR)pbMessage);
		DataBuf.buf = (char FAR*)&pbMessage;

		// Send message to proxy server
		if (WSASend(Socket, &DataBuf, 1, &cbMessage, Flags, NULL, NULL) == SOCKET_ERROR) {
	//	if (send(Socket, (LPSTR)pbMessage, cbMessage, 0) == SOCKET_ERROR) {
			TRACE(_T("**** Error %d sending message to proxy!\n"), WSAGetLastError());
			return WSAGetLastError();
		}

		// Receive message from proxy server
	//	cbMessage = recv(Socket, (LPSTR)pbMessage, 200, 0);
	//	if (cbMessage == SOCKET_ERROR) {
		cbMessage = WSARecvEx(Socket, (LPSTR)pbMessage, 200, &flg);
		if (cbMessage == SOCKET_ERROR) {
			TRACE(_T("**** Error %d receiving message from proxy\n"), WSAGetLastError());
			return WSAGetLastError();
		}
		// this sample is limited but in normal use it 
		// should continue to receive until CR LF CR LF is received
	}

	*pSocket = Socket;

	return SEC_E_OK;
}

static LONG DisconnectFromServer(
	SOCKET          Socket, 
	PCredHandle     phCreds,
	CtxtHandle *    phContext)
{
	DWORD           dwType;
	PBYTE           pbMessage;
	DWORD           cbMessage;
	DWORD           cbData;

	SecBufferDesc   OutBuffer;
	SecBuffer       OutBuffers[1];
	DWORD           dwSSPIFlags;
	DWORD           dwSSPIOutFlags;
	TimeStamp       tsExpiry;
	DWORD           Status;

	//
	// Notify schannel that we are about to close the connection.
	//
	dwType = SCHANNEL_SHUTDOWN;

	OutBuffers[0].pvBuffer   = &dwType;
	OutBuffers[0].BufferType = SECBUFFER_TOKEN;
	OutBuffers[0].cbBuffer   = sizeof(dwType);

	OutBuffer.cBuffers  = 1;
	OutBuffer.pBuffers  = OutBuffers;
	OutBuffer.ulVersion = SECBUFFER_VERSION;

	Status = g_pSSPI->ApplyControlToken(phContext, &OutBuffer);
	if (FAILED(Status)) {
		TRACE(_T("**** Error 0x%x returned by ApplyControlToken\n"), Status);
		goto cleanup;
	}

	//
	// Build an SSL close notify message.
	//
	dwSSPIFlags = ISC_REQ_SEQUENCE_DETECT   |
				  ISC_REQ_REPLAY_DETECT     |
				  ISC_REQ_CONFIDENTIALITY   |
				  ISC_RET_EXTENDED_ERROR    |
				  ISC_REQ_ALLOCATE_MEMORY   |
				  ISC_REQ_STREAM;

	OutBuffers[0].pvBuffer   = NULL;
	OutBuffers[0].BufferType = SECBUFFER_TOKEN;
	OutBuffers[0].cbBuffer   = 0;

	OutBuffer.cBuffers  = 1;
	OutBuffer.pBuffers  = OutBuffers;
	OutBuffer.ulVersion = SECBUFFER_VERSION;

	Status = g_pSSPI->InitializeSecurityContext(
					phCreds,
					phContext,
					NULL,
					dwSSPIFlags,
					0,
					SECURITY_NATIVE_DREP,
					NULL,
					0,
					phContext,
					&OutBuffer,
					&dwSSPIOutFlags,
					&tsExpiry);
	if (FAILED(Status)) {
		TRACE(_T("**** Error 0x%x returned by InitializeSecurityContext\n"), Status);
		goto cleanup;
	}

	pbMessage = (PBYTE)OutBuffers[0].pvBuffer;
	cbMessage = OutBuffers[0].cbBuffer;

    //
    // Send the close notify message to the server.
    //
    if (pbMessage != NULL && cbMessage != 0) {
		WSABUF DataBuf;
		DWORD Flags = 0;
		DataBuf.len = cbMessage;
		DataBuf.buf = (char FAR*)&pbMessage;

		if (WSASend(Socket, &DataBuf, 1, &cbData, Flags, NULL, NULL) == SOCKET_ERROR || cbData == 0) {
	//	cbData = send(Socket, (LPSTR)pbMessage, cbMessage, 0);
	//	if (cbData == SOCKET_ERROR || cbData == 0) {
			Status = WSAGetLastError();
			TRACE(_T("**** Error %d sending close notify\n"), Status);
			goto cleanup;
		}

		TRACE(_T("Sending Close Notify\n"));
		TRACE(_T("%d bytes of handshake data sent\n"), cbData);

#ifdef _DEBUG
		PrintHexDump(cbData, pbMessage);
		TRACE(_T("\n"));
#endif
		// Free output buffer.
		g_pSSPI->FreeContextBuffer(pbMessage);
	}
    
cleanup:
	// Free the security context.
	g_pSSPI->DeleteSecurityContext(phContext);

	// Close the socket.
	closesocket(Socket);

	return Status;
}

static void GetNewClientCredentials(
	CredHandle *phCreds,
	CtxtHandle *phContext)
{
	CredHandle hCreds;
	SecPkgContext_IssuerListInfoEx IssuerListInfo;
	PCCERT_CHAIN_CONTEXT pChainContext;
	CERT_CHAIN_FIND_BY_ISSUER_PARA FindByIssuerPara;
	PCCERT_CONTEXT  pCertContext;
	TimeStamp       tsExpiry;
	SECURITY_STATUS Status;

	//
	// Read list of trusted issuers from schannel.
	//
	Status = g_pSSPI->QueryContextAttributes(
						phContext,
						SECPKG_ATTR_ISSUER_LIST_EX,
						(PVOID)&IssuerListInfo);
	if (Status != SEC_E_OK) {
		TRACE(_T("Error 0x%x querying issuer list info\n"), Status);
		return;
    }

	//
	// Enumerate the client certificates.
	//
	ZeroMemory(&FindByIssuerPara, sizeof(FindByIssuerPara));

	FindByIssuerPara.cbSize = sizeof(FindByIssuerPara);
	FindByIssuerPara.pszUsageIdentifier = szOID_PKIX_KP_CLIENT_AUTH;
	FindByIssuerPara.dwKeySpec = 0;
	FindByIssuerPara.cIssuer   = IssuerListInfo.cIssuers;
	FindByIssuerPara.rgIssuer  = IssuerListInfo.aIssuers;

	pChainContext = NULL;

	while(TRUE) {
		// Find a certificate chain.
		pChainContext = CertFindChainInStore(
							hMyCertStore,
							X509_ASN_ENCODING,
							0,
							CERT_CHAIN_FIND_BY_ISSUER,
							&FindByIssuerPara,
							pChainContext);
		if (pChainContext == NULL) {
			TRACE(_T("Error 0x%x finding cert chain\n"), GetLastError());
			break;
		}
		TRACE(_T("\ncertificate chain found\n"));

		// Get pointer to leaf certificate context.
		pCertContext = pChainContext->rgpChain[0]->rgpElement[0]->pCertContext;

		// Create schannel credential.
		SchannelCred.dwVersion = SCHANNEL_CRED_VERSION;
		SchannelCred.cCreds = 1;
		SchannelCred.paCred = &pCertContext;

		Status = g_pSSPI->AcquireCredentialsHandle(
							NULL,                   // Name of principal
							UNISP_NAME_W,           // Name of package
							SECPKG_CRED_OUTBOUND,   // Flags indicating use
							NULL,                   // Pointer to logon ID
							&SchannelCred,          // Package specific data
							NULL,                   // Pointer to GetKey() func
							NULL,                   // Value to pass to GetKey()
							&hCreds,                // (out) Cred Handle
							&tsExpiry);             // (out) Lifetime (optional)
		if (Status != SEC_E_OK) {
			TRACE(_T("**** Error 0x%x returned by AcquireCredentialsHandle\n"), Status);
			continue;
		}
		TRACE(_T("\nnew schannel credential created\n"));

		// Destroy the old credentials.
		g_pSSPI->FreeCredentialsHandle(phCreds);

		*phCreds = hCreds;

		//
		// As you can see, this sample code maintains a single credential
		// handle, replacing it as necessary. This is a little unusual.
		//
		// Many applications maintain a global credential handle that's
		// anonymous (that is, it doesn't contain a client certificate),
		// which is used to connect to all servers. If a particular server
		// should require client authentication, then a new credential 
		// is created for use when connecting to that server. The global
		// anonymous credential is retained for future connections to
		// other servers.
		//
		// Maintaining a single anonymous credential that's used whenever
		// possible is most efficient, since creating new credentials all
		// the time is rather expensive.
		//

		break;
	}
}

static SECURITY_STATUS ClientHandshakeLoop(
	SOCKET          Socket,         // in
	PCredHandle     phCreds,        // in
	CtxtHandle *    phContext,      // in, out
	BOOL            fDoInitialRead, // in
	SecBuffer *     pExtraData)     // out
{
	SecBufferDesc   InBuffer;
	SecBuffer       InBuffers[2];
	SecBufferDesc   OutBuffer;
	SecBuffer       OutBuffers[1];
	DWORD           dwSSPIFlags;
	DWORD           dwSSPIOutFlags;
	TimeStamp       tsExpiry;
	SECURITY_STATUS scRet;
	DWORD           cbData;
	PUCHAR          IoBuffer;
	DWORD           cbIoBuffer;
	BOOL            fDoRead;

	dwSSPIFlags = ISC_REQ_SEQUENCE_DETECT   |
				  ISC_REQ_REPLAY_DETECT     |
				  ISC_REQ_CONFIDENTIALITY   |
				  ISC_RET_EXTENDED_ERROR    |
				  ISC_REQ_ALLOCATE_MEMORY   |
				  ISC_REQ_STREAM;

	//
	// Allocate data buffer.
	//
	IoBuffer = (PBYTE)LocalAlloc(LMEM_FIXED, IO_BUFFER_SIZE);
	if (IoBuffer == NULL) {
		TRACE(_T("**** Out of memory (1)\n"));
		return SEC_E_INTERNAL_ERROR;
	}
	cbIoBuffer = 0;

	fDoRead = fDoInitialRead;

	// 
	// Loop until the handshake is finished or an error occurs.
	//
	scRet = SEC_I_CONTINUE_NEEDED;

	while (scRet == SEC_I_CONTINUE_NEEDED        ||
		   scRet == SEC_E_INCOMPLETE_MESSAGE     ||
		   scRet == SEC_I_INCOMPLETE_CREDENTIALS) {
		//
		// Read data from server.
		//
		if (0 == cbIoBuffer || scRet == SEC_E_INCOMPLETE_MESSAGE) {
			if (fDoRead) {
			//	cbData = recv(Socket, 
			//				  (LPSTR)(IoBuffer + cbIoBuffer), 
			//				  IO_BUFFER_SIZE - cbIoBuffer, 
			//				  0);
			//	if (cbData == SOCKET_ERROR) {
				cbData = Read_From_Socket(
							Socket,
							IoBuffer + cbIoBuffer, 
							IO_BUFFER_SIZE - cbIoBuffer);
				if (cbData == (DWORD)-1) {
				//	TRACE(_T("**** Error %d reading data from server\n"), WSAGetLastError());
					scRet = SEC_E_INTERNAL_ERROR;
					break;
				} else if (cbData == 0) {
					TRACE(_T("**** Server unexpectedly disconnected\n"));
					scRet = SEC_E_INTERNAL_ERROR;
					break;
				}
				TRACE(_T("%d bytes of handshake data received\n"), cbData);
#ifdef _DEBUG
				PrintHexDump(cbData, IoBuffer + cbIoBuffer);
				TRACE(_T("\n"));
#endif
				cbIoBuffer += cbData;
			} else {
				fDoRead = TRUE;
			}
		}

		//
		// Set up the input buffers. Buffer 0 is used to pass in data
		// received from the server. Schannel will consume some or all
		// of this. Leftover data (if any) will be placed in buffer 1 and
		// given a buffer type of SECBUFFER_EXTRA.
		//
		InBuffers[0].pvBuffer   = IoBuffer;
		InBuffers[0].cbBuffer   = cbIoBuffer;
		InBuffers[0].BufferType = SECBUFFER_TOKEN;

		InBuffers[1].pvBuffer   = NULL;
		InBuffers[1].cbBuffer   = 0;
		InBuffers[1].BufferType = SECBUFFER_EMPTY;

		InBuffer.cBuffers       = 2;
		InBuffer.pBuffers       = InBuffers;
		InBuffer.ulVersion      = SECBUFFER_VERSION;

		//
		// Set up the output buffers. These are initialized to NULL
		// so as to make it less likely we'll attempt to free random
		// garbage later.
		//
		OutBuffers[0].pvBuffer  = NULL;
		OutBuffers[0].BufferType= SECBUFFER_TOKEN;
		OutBuffers[0].cbBuffer  = 0;

		OutBuffer.cBuffers      = 1;
		OutBuffer.pBuffers      = OutBuffers;
		OutBuffer.ulVersion     = SECBUFFER_VERSION;

		//
		// Call InitializeSecurityContext.
		//
		scRet = g_pSSPI->InitializeSecurityContext(
							phCreds,
							phContext,
							NULL,
							dwSSPIFlags,
							0,
							SECURITY_NATIVE_DREP,
							&InBuffer,
							0,
							NULL,
							&OutBuffer,
							&dwSSPIOutFlags,
							&tsExpiry);

		//
		// If InitializeSecurityContext was successful (or if the error was 
		// one of the special extended ones), send the contends of the output
		// buffer to the server.
		//

		if (scRet == SEC_E_OK || scRet == SEC_I_CONTINUE_NEEDED || FAILED(scRet) &&
			(dwSSPIOutFlags & ISC_RET_EXTENDED_ERROR))
		{
			if (OutBuffers[0].cbBuffer != 0 && OutBuffers[0].pvBuffer != NULL) {
				WSABUF DataBuf;
				DWORD Flags = 0;

				DataBuf.len = OutBuffers[0].cbBuffer;
				DataBuf.buf = (LPSTR)OutBuffers[0].pvBuffer;
				if (WSASend(Socket, &DataBuf, 1, &cbData, Flags, NULL, NULL) == SOCKET_ERROR || cbData == 0) {
			//	cbData = send(Socket,
			//				  (LPSTR)OutBuffers[0].pvBuffer,
			//				  OutBuffers[0].cbBuffer,
			//				  0);
			//	if (cbData == SOCKET_ERROR || cbData == 0) {
					TRACE(_T("**** Error %d sending data to server (2)\n"), WSAGetLastError());
					g_pSSPI->FreeContextBuffer(OutBuffers[0].pvBuffer);
					g_pSSPI->DeleteSecurityContext(phContext);
					return SEC_E_INTERNAL_ERROR;
				}
				TRACE(_T("%d bytes of handshake data sent\n"), cbData);
#ifdef _DEBUG
				PrintHexDump(cbData, (PBYTE)OutBuffers[0].pvBuffer);
				TRACE(_T("\n"));
#endif
				// Free output buffer.
				g_pSSPI->FreeContextBuffer(OutBuffers[0].pvBuffer);
				OutBuffers[0].pvBuffer = NULL;
			}
		}

		//
		// If InitializeSecurityContext returned SEC_E_INCOMPLETE_MESSAGE,
		// then we need to read more data from the server and try again.
		//
		if (scRet == SEC_E_INCOMPLETE_MESSAGE) {
			continue;
		}

		//
		// If InitializeSecurityContext returned SEC_E_OK, then the 
		// handshake completed successfully.
		//
        if (scRet == SEC_E_OK) {
			//
			// If the "extra" buffer contains data, this is encrypted application
			// protocol layer stuff. It needs to be saved. The application layer
			// will later decrypt it with DecryptMessage.
			//
			TRACE(_T("Handshake was successful\n"));

			if (InBuffers[1].BufferType == SECBUFFER_EXTRA) {
				pExtraData->pvBuffer = LocalAlloc(LMEM_FIXED, InBuffers[1].cbBuffer);
				if (pExtraData->pvBuffer == NULL) {
					TRACE(_T("**** Out of memory (2)\n"));
					return SEC_E_INTERNAL_ERROR;
				}

				MoveMemory(pExtraData->pvBuffer,
						IoBuffer + (cbIoBuffer - InBuffers[1].cbBuffer),
						InBuffers[1].cbBuffer);

				pExtraData->cbBuffer   = InBuffers[1].cbBuffer;
				pExtraData->BufferType = SECBUFFER_TOKEN;

				TRACE(_T("%d bytes of app data was bundled with handshake data\n"), pExtraData->cbBuffer);
			} else {
				pExtraData->pvBuffer   = NULL;
				pExtraData->cbBuffer   = 0;
				pExtraData->BufferType = SECBUFFER_EMPTY;
			}

			//
			// Bail out to quit
			//
            break;
		}

		//
		// Check for fatal error.
		//
		if (FAILED(scRet)) {
			TRACE(_T("**** Error 0x%x returned by InitializeSecurityContext (2)\n"), scRet);
			break;
		}

		//
		// If InitializeSecurityContext returned SEC_I_INCOMPLETE_CREDENTIALS,
		// then the server just requested client authentication. 
		//
		if (scRet == SEC_I_INCOMPLETE_CREDENTIALS) {
			//
			// Busted. The server has requested client authentication and
			// the credential we supplied didn't contain a client certificate.
			//

			// 
			// This function will read the list of trusted certificate
			// authorities ("issuers") that was received from the server
			// and attempt to find a suitable client certificate that
			// was issued by one of these. If this function is successful, 
			// then we will connect using the new certificate. Otherwise,
			// we will attempt to connect anonymously (using our current
			// credentials).
			//
            
			GetNewClientCredentials(phCreds, phContext);

			// Go around again.
			fDoRead = FALSE;
			scRet = SEC_I_CONTINUE_NEEDED;
			continue;
		}

		//
		// Copy any leftover data from the "extra" buffer, and go around
		// again.
		//

		if ( InBuffers[1].BufferType == SECBUFFER_EXTRA ) {
			MoveMemory(IoBuffer,
					   IoBuffer + (cbIoBuffer - InBuffers[1].cbBuffer),
					   InBuffers[1].cbBuffer);
			cbIoBuffer = InBuffers[1].cbBuffer;
		} else {
			cbIoBuffer = 0;
		}
	}

    // Delete the security context in the case of a fatal error.
    if (FAILED(scRet))
    {
        g_pSSPI->DeleteSecurityContext(phContext);
    }

	LocalFree(IoBuffer);

	return scRet;
}

static SECURITY_STATUS PerformClientHandshake(
	SOCKET          Socket,         // in
	PCredHandle     phCreds,        // in
	LPCTSTR         pszServerName,  // in
	CtxtHandle *    phContext,      // out
	SecBuffer *     pExtraData)     // out
{
	SecBufferDesc   OutBuffer;
	SecBuffer       OutBuffers[1];
	DWORD           dwSSPIFlags;
	DWORD           dwSSPIOutFlags;
	TimeStamp       tsExpiry;
	SECURITY_STATUS scRet;
	DWORD           cbData;

	dwSSPIFlags = ISC_REQ_SEQUENCE_DETECT   |
				  ISC_REQ_REPLAY_DETECT     |
				  ISC_REQ_CONFIDENTIALITY   |
				  ISC_RET_EXTENDED_ERROR    |
				  ISC_REQ_ALLOCATE_MEMORY   |
				  ISC_REQ_STREAM;

	//
	//  Initiate a ClientHello message and generate a token.
	//

	OutBuffers[0].pvBuffer   = NULL;
	OutBuffers[0].BufferType = SECBUFFER_TOKEN;
	OutBuffers[0].cbBuffer   = 0;

	OutBuffer.cBuffers = 1;
	OutBuffer.pBuffers = OutBuffers;
	OutBuffer.ulVersion = SECBUFFER_VERSION;

	scRet = g_pSSPI->InitializeSecurityContext(
						phCreds,
						NULL,
						(LPTSTR)pszServerName,
						dwSSPIFlags,
						0,
						SECURITY_NATIVE_DREP,
						NULL,
						0,
						phContext,
						&OutBuffer,
						&dwSSPIOutFlags,
						&tsExpiry);
	if (scRet != SEC_I_CONTINUE_NEEDED) {
		TRACE(_T("**** Error %d returned by InitializeSecurityContext (1)\n"), scRet);
		return scRet;
	}

	// Send response to server if there is one.
	if (OutBuffers[0].cbBuffer != 0 && OutBuffers[0].pvBuffer != NULL) {
		WSABUF DataBuf;
		DWORD Flags = 0;

		DataBuf.len = OutBuffers[0].cbBuffer;
		DataBuf.buf = (LPSTR)OutBuffers[0].pvBuffer;
		if (WSASend(Socket, &DataBuf, 1, &cbData, Flags, NULL, NULL) == SOCKET_ERROR || cbData == 0) {
	//	cbData = send(Socket,
	//				  (LPSTR)OutBuffers[0].pvBuffer,
	//				  OutBuffers[0].cbBuffer,
	//				  0);
	//	if (cbData == SOCKET_ERROR || cbData == 0) {
			TRACE(_T("**** Error %d sending data to server (1)\n"), WSAGetLastError());
			g_pSSPI->FreeContextBuffer(OutBuffers[0].pvBuffer);
			g_pSSPI->DeleteSecurityContext(phContext);
			return SEC_E_INTERNAL_ERROR;
		}
		TRACE(_T("%d bytes of handshake data sent\n"), cbData);
#ifdef _DEBUG
		PrintHexDump(cbData, (PBYTE)OutBuffers[0].pvBuffer);
		TRACE(_T("\n"));
#endif
		// Free output buffer.
		g_pSSPI->FreeContextBuffer(OutBuffers[0].pvBuffer);
		OutBuffers[0].pvBuffer = NULL;
	}

	return ClientHandshakeLoop(Socket, phCreds, phContext, TRUE, pExtraData);
}

static SECURITY_STATUS HttpsGetFile(
	SOCKET          Socket,         // in
	PCredHandle     phCreds,        // in
	CtxtHandle *    phContext,      // in
	LPCSTR          pszHost,        // in
	LPCSTR          pszPath,        // in
	LPCSTR          pszCookie,      // in
	LPCSTR          pszData,        // in
	LPSTR*          chpp_result)    // out
{
	SecPkgContext_StreamSizes Sizes;
	SECURITY_STATUS scRet;
	SecBufferDesc   Message;
	SecBuffer       Buffers[4];
	SecBuffer *     pDataBuffer;
	SecBuffer *     pExtraBuffer;
	SecBuffer       ExtraBuffer;

	LPSTR pszResult = NULL;
	LPSTR pszTemp;
	PBYTE pbIoBuffer;
	DWORD cbIoBuffer;
	DWORD cbIoBufferLength;
	PBYTE pbMessage;
	DWORD cbMessage;

	DWORD cbData;
	INT   i;

	WSABUF DataBuf;
	DWORD  Flags = 0;

	*chpp_result = NULL;

	//
	// Read stream encryption properties.
	//
	scRet = g_pSSPI->QueryContextAttributes(
						phContext,
						SECPKG_ATTR_STREAM_SIZES,
						&Sizes);
	if (scRet != SEC_E_OK) {
		TRACE(_T("**** Error 0x%x reading SECPKG_ATTR_STREAM_SIZES\n"), scRet);
		return scRet;
	}

	TRACE(_T("\nHeader: %d, Trailer: %d, MaxMessage: %d\n"),
		Sizes.cbHeader,
		Sizes.cbTrailer,
		Sizes.cbMaximumMessage);

	//
	// Allocate a working buffer. The plaintext sent to EncryptMessage
	// should never be more than 'Sizes.cbMaximumMessage', so a buffer 
	// size of this plus the header and trailer sizes should be safe enough.
	// 
	cbIoBufferLength = Sizes.cbHeader + 
					   Sizes.cbMaximumMessage +
					   Sizes.cbTrailer;
	pbIoBuffer = (PBYTE)LocalAlloc(LMEM_FIXED, cbIoBufferLength);
	if (pbIoBuffer == NULL) {
		TRACE(_T("**** Out of memory (2)\n"));
		return SEC_E_INTERNAL_ERROR;
	}

	//
	// Build an HTTP request to send to the server.
	//

	// Build the HTTP request offset into the data buffer by "header size"
	// bytes. This enables Schannel to perform the encryption in place,
	// which is a significant performance win.
	pbMessage = pbIoBuffer + Sizes.cbHeader;

	// Build HTTP request. Note that I'm assuming that this is less than
	// the maximum message size. If it weren't, it would have to be broken up.
	if (pszCookie && pszCookie[0]) {
		sprintf((LPSTR)pbMessage,
			"POST %s HTTP/1.0\r\n"
			"%s"
			"Host: %s\r\n"
			"Content-Type: text/plain; charset=EUC-JP\r\n"
			"Content-length: %d\r\n\r\n"
			"%s\r\n\r\n",
			pszPath, pszCookie, pszHost, strlen(pszData), pszData);
	} else {
		sprintf((LPSTR)pbMessage,
			"POST %s HTTP/1.0\r\n"
			"Host: %s\r\n"
			"Content-Type: text/plain; charset=EUC-JP\r\n"
			"Content-length: %d\r\n\r\n"
			"%s\r\n\r\n",
			pszPath, pszHost, strlen(pszData), pszData);
	}

    cbMessage = (DWORD)strlen((LPSTR)pbMessage);

	TRACE(_T("Sending plaintext: %d bytes\n"), cbMessage);
#ifdef _DEBUG
	PrintHexDump(cbMessage, pbMessage);
	TRACE(_T("\n"));
#endif

	//
	// Encrypt the HTTP request.
	//
	Buffers[0].pvBuffer     = pbIoBuffer;
	Buffers[0].cbBuffer     = Sizes.cbHeader;
	Buffers[0].BufferType   = SECBUFFER_STREAM_HEADER;

	Buffers[1].pvBuffer     = pbMessage;
	Buffers[1].cbBuffer     = cbMessage;
	Buffers[1].BufferType   = SECBUFFER_DATA;

	Buffers[2].pvBuffer     = pbMessage + cbMessage;
	Buffers[2].cbBuffer     = Sizes.cbTrailer;
	Buffers[2].BufferType   = SECBUFFER_STREAM_TRAILER;

	Buffers[3].BufferType   = SECBUFFER_EMPTY;

	Message.ulVersion       = SECBUFFER_VERSION;
	Message.cBuffers        = 4;
	Message.pBuffers        = Buffers;

	scRet = g_pSSPI->EncryptMessage(phContext, 0, &Message, 0);

	if (FAILED(scRet)) {
		TRACE(_T("**** Error 0x%x returned by EncryptMessage\n"), scRet);
		LocalFree((HLOCAL)pbIoBuffer);
		return scRet;
	}

	// 
	// Send the encrypted data to the server.
	//
	DataBuf.len = Buffers[0].cbBuffer + Buffers[1].cbBuffer + Buffers[2].cbBuffer;
	DataBuf.buf = (LPSTR)pbIoBuffer;
	if (WSASend(Socket, &DataBuf, 1, &cbData, Flags, NULL, NULL) == SOCKET_ERROR || cbData == 0) {
//	cbData = send(Socket,
//				  (LPSTR)pbIoBuffer,
//				  Buffers[0].cbBuffer + Buffers[1].cbBuffer + Buffers[2].cbBuffer,
//				  0);
//	if (cbData == SOCKET_ERROR || cbData == 0) {
		TRACE(_T("**** Error %d sending data to server (3)\n"), WSAGetLastError());
		g_pSSPI->DeleteSecurityContext(phContext);
		LocalFree((HLOCAL)pbIoBuffer);
		return SEC_E_INTERNAL_ERROR;
	}
	TRACE(_T("%d bytes of application data sent\n"), cbData);
#ifdef _DEBUG
	PrintHexDump(cbData, pbIoBuffer);
	TRACE(_T("\n"));
#endif

	//
	// Read data from server until done.
	//
	cbIoBuffer = 0;

    while(TRUE) {
		//
		// Read some data.
		//
		if (0 == cbIoBuffer || scRet == SEC_E_INCOMPLETE_MESSAGE) {

		//	cbData = recv(Socket, 
		//				  (LPSTR)(pbIoBuffer + cbIoBuffer), 
		//				  cbIoBufferLength - cbIoBuffer, 
		//				  0);
		//	if (cbData == SOCKET_ERROR) {
			cbData = Read_From_Socket(
						Socket, 
						pbIoBuffer + cbIoBuffer, 
						cbIoBufferLength - cbIoBuffer);
			if (cbData == (DWORD)-1) {
			//	TRACE(_T("**** Error %d reading data from server\n"), WSAGetLastError());
				scRet = SEC_E_INTERNAL_ERROR;
				break;
			} else if (cbData == 0) {
				// Server disconnected.
				if (cbIoBuffer) {
					TRACE(_T("**** Server unexpectedly disconnected\n"));
					scRet = SEC_E_INTERNAL_ERROR;
					LocalFree((HLOCAL)pbIoBuffer);
					return scRet;
				} else {
					break;
				}
			} else {
				TRACE(_T("%d bytes of (encrypted) application data received\n"), cbData);
#ifdef _DEBUG
				PrintHexDump(cbData, pbIoBuffer + cbIoBuffer);
				TRACE(_T("\n"));
#endif
				cbIoBuffer += cbData;
			}
		}

		// 
		// Attempt to decrypt the received data.
		//
		Buffers[0].pvBuffer     = pbIoBuffer;
		Buffers[0].cbBuffer     = cbIoBuffer;
		Buffers[0].BufferType   = SECBUFFER_DATA;

		Buffers[1].BufferType   = SECBUFFER_EMPTY;
		Buffers[2].BufferType   = SECBUFFER_EMPTY;
		Buffers[3].BufferType   = SECBUFFER_EMPTY;

		Message.ulVersion       = SECBUFFER_VERSION;
		Message.cBuffers        = 4;
		Message.pBuffers        = Buffers;

		scRet = g_pSSPI->DecryptMessage(phContext, &Message, 0, NULL);

		if (scRet == SEC_E_INCOMPLETE_MESSAGE) {
			// The input buffer contains only a fragment of an
			// encrypted record. Loop around and read some more
			// data.
			continue;
		}

		// Server signalled end of session
		if (scRet == SEC_I_CONTEXT_EXPIRED)
			break;

		if (scRet != SEC_E_OK && 
			scRet != SEC_I_RENEGOTIATE && 
			scRet != SEC_I_CONTEXT_EXPIRED)
		{
			TRACE(_T("**** Error 0x%x returned by DecryptMessage\n"), scRet);
			LocalFree((HLOCAL)pbIoBuffer);
			return scRet;
		}

		// Locate data and (optional) extra buffers.
		pDataBuffer  = NULL;
		pExtraBuffer = NULL;
		for (i = 1; i < 4; i++) {
			if (pDataBuffer == NULL && Buffers[i].BufferType == SECBUFFER_DATA) {
				pDataBuffer = &Buffers[i];
				TRACE(_T("Buffers[%d].BufferType = SECBUFFER_DATA\n"),i);
			}
			if (pExtraBuffer == NULL && Buffers[i].BufferType == SECBUFFER_EXTRA) {
				pExtraBuffer = &Buffers[i];
			}
		}

		// Display or otherwise process the decrypted data.
		if (pDataBuffer) {
			TRACE(_T("Decrypted data: %d bytes\n"), pDataBuffer->cbBuffer);
#ifdef _DEBUG
			PrintHexDump(pDataBuffer->cbBuffer, (PBYTE)pDataBuffer->pvBuffer);
			TRACE(_T("\n"));
#endif
			if (!pszResult) {
				pszResult = (LPSTR)malloc(strlen((LPSTR)pDataBuffer->pvBuffer) + 1);
				strncpy(pszResult, (LPSTR)pDataBuffer->pvBuffer, pDataBuffer->cbBuffer);
				pszResult[pDataBuffer->cbBuffer] = '\0';
			} else {
				size_t s = strlen(pszResult);
				pszTemp = pszResult;
				pszResult = (LPSTR)malloc(s + pDataBuffer->cbBuffer + 1);
				strcpy(pszResult, pszTemp);
				strncpy(pszResult + s, (LPSTR)pDataBuffer->pvBuffer, pDataBuffer->cbBuffer);
				pszResult[s + pDataBuffer->cbBuffer] = '\0';
				free(pszTemp);
			}
		}

		// Move any "extra" data to the input buffer.
		if (pExtraBuffer) {
			MoveMemory(pbIoBuffer, pExtraBuffer->pvBuffer, pExtraBuffer->cbBuffer);
			cbIoBuffer = pExtraBuffer->cbBuffer;
		} else {
			cbIoBuffer = 0;
		}

		if (scRet == SEC_I_RENEGOTIATE) {
			// The server wants to perform another handshake
			// sequence.
			TRACE(_T("Server requested renegotiate!\n"));
			scRet = ClientHandshakeLoop(
						Socket, 
						phCreds, 
						phContext, 
						FALSE, 
						&ExtraBuffer);
			if (scRet != SEC_E_OK) {
				LocalFree((HLOCAL)pbIoBuffer);
				return scRet;
			}

			// Move any "extra" data to the input buffer.
			if (ExtraBuffer.pvBuffer) {
				MoveMemory(pbIoBuffer, ExtraBuffer.pvBuffer, ExtraBuffer.cbBuffer);
				cbIoBuffer = ExtraBuffer.cbBuffer;
			}
		}
	}
	LocalFree((HLOCAL)pbIoBuffer);

	pszTemp = strstr(pszResult, "\r\n");
	if (pszTemp) {
		pszTemp += strlen("\r\n");
	} else {
		pszTemp = pszResult;
	}
	*chpp_result = (LPSTR)malloc(strlen(pszTemp) + 1);
	strcpy(*chpp_result, pszTemp);
	free(pszResult);

	return SEC_E_OK;
}

static DWORD VerifyServerCertificate(
	PCCERT_CONTEXT  pServerCert,
	PSTR            pszServerName,
	DWORD           dwCertFlags)
{
	HTTPSPolicyCallbackData  polHttps;
	CERT_CHAIN_POLICY_PARA   PolicyPara;
	CERT_CHAIN_POLICY_STATUS PolicyStatus;
	CERT_CHAIN_PARA          ChainPara;
	PCCERT_CHAIN_CONTEXT     pChainContext = NULL;

	LPSTR rgszUsages[] = {szOID_PKIX_KP_SERVER_AUTH,
						  szOID_SERVER_GATED_CRYPTO,
						  szOID_SGC_NETSCAPE};
	DWORD cUsages = sizeof(rgszUsages) / sizeof(LPSTR);

	PWSTR   pwszServerName = NULL;
	DWORD   cchServerName;
	DWORD   Status;

	if (pServerCert == NULL) {
		Status = SEC_E_WRONG_PRINCIPAL;
		goto cleanup;
	}

	//
	// Convert server name to unicode.
	//
	if (pszServerName == NULL || strlen(pszServerName) == 0) {
		Status = SEC_E_WRONG_PRINCIPAL;
		goto cleanup;
	}

	cchServerName = MultiByteToWideChar(CP_ACP, 0, pszServerName, -1, NULL, 0);
	pwszServerName = (PWSTR)LocalAlloc(LMEM_FIXED, cchServerName * sizeof(WCHAR));
	if (pwszServerName == NULL) {
		Status = SEC_E_INSUFFICIENT_MEMORY;
		goto cleanup;
	}
	cchServerName = MultiByteToWideChar(CP_ACP, 0, pszServerName, -1, pwszServerName, cchServerName);
	if (cchServerName == 0) {
		Status = SEC_E_WRONG_PRINCIPAL;
		goto cleanup;
	}

	//
	// Build certificate chain.
	//
	ZeroMemory(&ChainPara, sizeof(ChainPara));
	ChainPara.cbSize = sizeof(ChainPara);
	ChainPara.RequestedUsage.dwType = USAGE_MATCH_TYPE_OR;
	ChainPara.RequestedUsage.Usage.cUsageIdentifier     = cUsages;
	ChainPara.RequestedUsage.Usage.rgpszUsageIdentifier = rgszUsages;

	if (!CertGetCertificateChain(
							NULL,
							pServerCert,
							NULL,
							pServerCert->hCertStore,
							&ChainPara,
							0,
							NULL,
							&pChainContext))
	{
		Status = GetLastError();
		TRACE(_T("Error 0x%x returned by CertGetCertificateChain!\n"), Status);
		goto cleanup;
	}

	//
	// Validate certificate chain.
	// 
	ZeroMemory(&polHttps, sizeof(HTTPSPolicyCallbackData));
	polHttps.cbStruct           = sizeof(HTTPSPolicyCallbackData);
	polHttps.dwAuthType         = AUTHTYPE_SERVER;
	polHttps.fdwChecks          = dwCertFlags;
	polHttps.pwszServerName     = pwszServerName;

	memset(&PolicyPara, 0, sizeof(PolicyPara));
	PolicyPara.cbSize            = sizeof(PolicyPara);
	PolicyPara.pvExtraPolicyPara = &polHttps;

	memset(&PolicyStatus, 0, sizeof(PolicyStatus));
	PolicyStatus.cbSize = sizeof(PolicyStatus);

	if (!CertVerifyCertificateChainPolicy(
							CERT_CHAIN_POLICY_SSL,
							pChainContext,
							&PolicyPara,
							&PolicyStatus))
	{
		Status = GetLastError();
		TRACE(_T("Error 0x%x returned by CertVerifyCertificateChainPolicy!\n"), Status);
		goto cleanup;
	}

	if (PolicyStatus.dwError) {
		Status = PolicyStatus.dwError;
#ifdef _DEBUG
		DisplayWinVerifyTrustError(Status); 
#endif
		goto cleanup;
	}

	Status = SEC_E_OK;

cleanup:
	if (pChainContext) {
		CertFreeCertificateChain(pChainContext);
	}
	if (pwszServerName) {
		LocalFree(pwszServerName);
	}

	return Status;
}

int Https_Post_Get_Result_Old(LPCTSTR chp_host, LPCTSTR chp_path, LPCTSTR chp_params, LPCTSTR chp_cookie, LPSTR* chpp_result)
{
	int err = 1;
	char cha_host[256];
	char cha_path[256];
	char cha_param[1024];
	char cha_cookie[1024];
	WSADATA WsaData;
	SOCKET  Socket = INVALID_SOCKET;

	CredHandle hClientCreds;
	CtxtHandle hContext;
	BOOL fCredsInitialized = FALSE;
	BOOL fContextInitialized = FALSE;

	SecBuffer  ExtraData;
	SECURITY_STATUS Status;

	PCCERT_CONTEXT pRemoteCertContext = NULL;

#ifdef _UNICODE
	ZeroMemory(cha_host, sizeof(cha_host));
	WideCharToMultiByte(CP_THREAD_ACP, WC_NO_BEST_FIT_CHARS, chp_host, _tcslen(chp_host), cha_host, ARRAYSIZE(cha_host)-1, NULL, NULL);
	ZeroMemory(cha_path, sizeof(cha_path));
	WideCharToMultiByte(CP_THREAD_ACP, WC_NO_BEST_FIT_CHARS, chp_path, _tcslen(chp_path), cha_path, ARRAYSIZE(cha_path)-1, NULL, NULL);
	ZeroMemory(cha_param, sizeof(cha_param));
	WideCharToMultiByte(CP_THREAD_ACP, WC_NO_BEST_FIT_CHARS, chp_params, _tcslen(chp_params), cha_param, ARRAYSIZE(cha_param)-1, NULL, NULL);
	if (chp_cookie) {
		ZeroMemory(cha_cookie, sizeof(cha_cookie));
		WideCharToMultiByte(CP_THREAD_ACP, WC_NO_BEST_FIT_CHARS, chp_cookie, _tcslen(chp_cookie), cha_cookie, ARRAYSIZE(cha_cookie)-1, NULL, NULL);
	} else {
		cha_cookie[0] = _T('\0');
	}
#else
	strcpy(cha_host, chp_host);
	strcpy(cha_path, chp_path);
	strcpy(cha_param, chp_params);
	if (chp_cookie) {
		strcpy(cha_cookie, chp_cookie);
	} else {
		cha_cookie[0] = '\0';
	}
#endif

	if (!LoadSecurityLibrary()) {
		TRACE(_T("Error initializing the security library\n"));
		goto cleanup;
	}

	//
	// Initialize the WinSock subsystem.
	//
	if (WSAStartup(0x0101, &WsaData) == SOCKET_ERROR) {
		TRACE(_T("Error %d returned by WSAStartup\n"), GetLastError());
		goto cleanup;
	}

	//
	// Create credentials.
	//
	if (CreateCredentials(pszUserName, &hClientCreds)) {
		TRACE(_T("Error creating credentials\n"));
		goto cleanup;
	}
	fCredsInitialized = TRUE;

	//
	// Connect to server.
	//
	if (ConnectToServer(cha_host, iPortNumber, &Socket)) {
		TRACE(_T("Error connecting to server\n"));
		goto cleanup;
	}

	//
	// Perform handshake
	//
	if (PerformClientHandshake(Socket,
							  &hClientCreds,
							  chp_host,
							  &hContext,
							  &ExtraData))
	{
		TRACE(_T("Error performing handshake\n"));
		goto cleanup;
	}
	fContextInitialized = TRUE;

	//
	// Authenticate server's credentials.
	//
	// Get server's certificate.
	Status = g_pSSPI->QueryContextAttributes(&hContext,
											 SECPKG_ATTR_REMOTE_CERT_CONTEXT,
											 (PVOID)&pRemoteCertContext);
	if (Status != SEC_E_OK) {
		TRACE(_T("Error 0x%x querying remote certificate\n"), Status);
		goto cleanup;
	}

#ifdef _DEBUG
	// Display server certificate chain.
	DisplayCertChain(pRemoteCertContext, FALSE);
#endif

	// Attempt to validate server certificate.
	Status = VerifyServerCertificate(pRemoteCertContext, cha_host, 0);
	if (Status) {
		// The server certificate did not validate correctly. At this
		// point, we cannot tell if we are connecting to the correct 
		// server, or if we are connecting to a "man in the middle" 
		// attack server.

		// It is therefore best if we abort the connection.

		TRACE(_T("**** Error 0x%x authenticating server credentials!\n"), Status);
		goto cleanup;
	}

	// Free the server certificate context.
	CertFreeCertificateContext(pRemoteCertContext);
	pRemoteCertContext = NULL;

#ifdef _DEBUG
	//
	// Display connection info. 
	//
	DisplayConnectionInfo(&hContext);
#endif

	//
	// Read file from server.
	//
	if (HttpsGetFile(Socket, 
					&hClientCreds,
					&hContext, 
					cha_host,
					cha_path,
					cha_cookie,
					cha_param,
					chpp_result))
	{
		TRACE(_T("Error fetching file from server\n"));
		goto cleanup;
	}

	//
	// Send a close_notify alert to the server and
	// close down the connection.
	//
	if (DisconnectFromServer(Socket, &hClientCreds, &hContext)) {
		TRACE(_T("Error disconnecting from server\n"));
		goto cleanup;
	}
	fContextInitialized = FALSE;
	Socket = INVALID_SOCKET;
	err = 0;

cleanup:
	// Free the server certificate context.
	if (pRemoteCertContext) {
		CertFreeCertificateContext(pRemoteCertContext);
	}

	// Free SSPI context handle.
	if (fContextInitialized) {
		g_pSSPI->DeleteSecurityContext(&hContext);
	}

	// Free SSPI credentials handle.
	if (fCredsInitialized) {
		g_pSSPI->FreeCredentialsHandle(&hClientCreds);
	}

	// Close socket.
	if (Socket != INVALID_SOCKET) {
		closesocket(Socket);
	}

	// Shutdown WinSock subsystem.
	WSACleanup();

	// Close "MY" certificate store.
	if (hMyCertStore) {
		CertCloseStore(hMyCertStore, 0);
		hMyCertStore = NULL;
	}

	UnloadSecurityLibrary();
	TRACE(_T("Done\n"));

	return err;
}
*/

static BOOL Get_Proxy_Info()
{
	unsigned long        nSize = 4096;
	char                 szBuf[4096] = { 0 };
	INTERNET_PROXY_INFO* pInfo = (INTERNET_PROXY_INFO*)szBuf;

	fUseProxy = FALSE;
	strcpy_s(pszProxyServer, sizeof(pszProxyServer), "proxy");

	if(!InternetQueryOption(NULL, INTERNET_OPTION_PROXY, pInfo, &nSize)) {
		TRACE(_T("InternetQueryOption failed! (%d)\n"), GetLastError());
		return FALSE;
	}

	if (pInfo->dwAccessType == INTERNET_OPEN_TYPE_PROXY) {
		LPSTR pszStr;
		fUseProxy = TRUE;
		strcpy_s(pszProxyServer, sizeof(pszProxyServer), (LPSTR)pInfo->lpszProxy);
		pszStr = strchr(pszProxyServer, ':');
		if (pszStr) {
			*pszStr = '\0';
			++pszStr;
			iProxyPort = atoi(pszStr);
		}
		return TRUE;
	}
	return FALSE;
}

int Https_Post_Get_Result(LPCTSTR chp_host, LPCTSTR chp_path, LPCTSTR chp_params, LPCTSTR chp_cookie, LPSTR* chpp_result)
{
#define MYBUFSIZ 32768
	HINTERNET hOpen, hConnect, hReq;
	INTERNET_PORT dwPort = INTERNET_DEFAULT_HTTPS_PORT;
	DWORD dwFlags = INTERNET_FLAG_RELOAD |
					INTERNET_FLAG_NO_CACHE_WRITE |
					INTERNET_FLAG_KEEP_CONNECTION |
					INTERNET_FLAG_SECURE |
					INTERNET_FLAG_IGNORE_CERT_CN_INVALID |
					INTERNET_FLAG_IGNORE_CERT_DATE_INVALID;
	DWORD dwSize;
	DWORD dwUsed;
	DWORD dwCode;
	DWORD dwBufSize;
	TCHAR szAccept[] = TEXT("*/*");
	LPSTR lpBuffer;
	LPTSTR AcceptTypes[2] = {0};
	LPTSTR chp_header;
	LPSTR chp_result;

	AcceptTypes[0] = szAccept;

	if (!Get_Proxy_Info()) {
		// No proxy was specified
		if (!(hOpen = InternetOpen(TEXT("HoBizToolBar"), LOCAL_INTERNET_ACCESS , NULL, 0, 0))) {
			return GetLastError();
		}
	} else {
		// Use proxy server
		TCHAR szProxy[256];
#ifdef _UNICODE
		ZeroMemory(szProxy, sizeof(szProxy));
		MultiByteToWideChar(CP_THREAD_ACP, MB_COMPOSITE, pszProxyServer, strlen(pszProxyServer), szProxy, (sizeof(szProxy) - 1) * sizeof(TCHAR));
#else
		lstrcpy(szProxy, pszProxyServer);
#endif
		if (!(hOpen = InternetOpen(TEXT("HotBizToolBar"), CERN_PROXY_INTERNET_ACCESS, szProxy, NULL, 0))) {
			return GetLastError();
		}
	}
	if (!(hConnect = InternetConnect(hOpen, chp_host, dwPort, TEXT(""), TEXT(""), INTERNET_SERVICE_HTTP, 0, 0))) {
		return GetLastError();
	}
	if (!(hReq = HttpOpenRequest(hConnect, TEXT("POST"), chp_path, HTTP_VERSION, TEXT(""), (LPCTSTR*)AcceptTypes, dwFlags ,0))) {
		return GetLastError();
	}
	if (chp_cookie && chp_cookie[0] &&
		!HttpAddRequestHeaders(hReq, chp_cookie, _tcslen(chp_cookie), HTTP_ADDREQ_FLAG_REPLACE))
	{
		return GetLastError();
	}

	dwSize = (_tcslen(chp_params) + 1) * sizeof(CHAR);
	lpBuffer = (LPSTR)LocalAlloc(LPTR, dwSize);
#ifdef _UNICODE
	ZeroMemory(lpBuffer, dwSize);
	WideCharToMultiByte(CP_THREAD_ACP, WC_NO_BEST_FIT_CHARS, chp_params, _tcslen(chp_params), lpBuffer, dwSize - 1, NULL, NULL);
#else
	strcpy(lpBuffer, chp_params);
#endif
	if (!HttpSendRequest(hReq, NULL, 0, (LPVOID)lpBuffer, dwSize - 1)) {
		LocalFree(lpBuffer);
		return GetLastError();
	}
	LocalFree(lpBuffer);

	dwSize = sizeof(DWORD);
	if (!HttpQueryInfo(hReq, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &dwCode, &dwSize, NULL)) {
		return GetLastError();
	}
	if (dwCode != HTTP_STATUS_OK) {
		return dwCode;
	}

	// First time we will find out the size of the headers.
	dwSize = 1;
	chp_header = (LPTSTR)LocalAlloc(LPTR, dwSize + sizeof(TCHAR));
	dwSize += sizeof(TCHAR);
	HttpQueryInfo(hReq, HTTP_QUERY_RAW_HEADERS_CRLF, chp_header, &dwSize, NULL);
	LocalFree((HLOCAL)chp_header);

	// Now we call HttpQueryInfo again to get the headers.
	chp_header = (LPTSTR)LocalAlloc(LPTR, dwSize + sizeof(TCHAR));
	dwSize += sizeof(TCHAR);
	if (!HttpQueryInfo(hReq, HTTP_QUERY_RAW_HEADERS_CRLF, (LPVOID)chp_header, &dwSize, NULL)) {
		LocalFree(chp_header);
		return GetLastError();
	}
	*(chp_header + dwSize / sizeof(TCHAR)) = _T('\0');

	dwUsed = 0;
	dwBufSize = MYBUFSIZ;
	lpBuffer = (LPSTR)LocalAlloc(LPTR, dwBufSize);
	do {
		if (!InternetReadFile (hReq, (LPVOID)(lpBuffer + dwUsed), dwBufSize - dwUsed - 1, &dwSize) ) {
			LocalFree(chp_header);
			LocalFree(lpBuffer);
			return GetLastError();
		}
		lpBuffer[dwUsed + dwSize] = '\0';
		if (dwSize >= dwBufSize - dwUsed - 1) {
			LPSTR p;
			dwBufSize += MYBUFSIZ;
			p = (LPSTR)LocalAlloc(LPTR, dwBufSize);
			strcpy_s(p, dwBufSize, lpBuffer);
			LocalFree(lpBuffer);
			lpBuffer = p;
		}
		dwUsed += dwSize;
	} while (dwSize);

	dwSize = (_tcslen(chp_header) + strlen(lpBuffer) + 1) * sizeof(CHAR);
	chp_result = (LPSTR)malloc(dwSize);
	ZeroMemory(chp_result, dwSize);
#ifdef _UNICODE
	WideCharToMultiByte(CP_THREAD_ACP, WC_NO_BEST_FIT_CHARS, chp_header, _tcslen(chp_header), chp_result, dwSize, NULL, NULL);
#else
	strcpy(chp_result, chp_header);
#endif
	strcat_s(chp_result, dwSize, lpBuffer);
	*chpp_result = chp_result;

	LocalFree(lpBuffer);
	LocalFree(chp_header);

	InternetCloseHandle(hReq);
	InternetCloseHandle(hConnect);
	InternetCloseHandle(hOpen);

	return 0;
}

#ifdef _UNICODE
int Https_Post_Get_Result(const TCHAR* chp_host, const TCHAR* chp_path, const TCHAR* chp_params, const TCHAR* chp_cookie, TCHAR** chpp_result)
{
	char* chp_buf;
	int err = Https_Post_Get_Result(chp_host, chp_path, chp_params, chp_cookie, &chp_buf);
	if (err)
		return err;

	*chpp_result = (LPTSTR)malloc((strlen(chp_buf) + 1)*sizeof(TCHAR));
	ZeroMemory(*chpp_result, (strlen(chp_buf) + 1)*sizeof(TCHAR));
	MultiByteToWideChar(CP_THREAD_ACP, MB_COMPOSITE, chp_buf, strlen(chp_buf), *chpp_result, strlen(chp_buf) + 1);
	free(chp_buf);
	return 0;
}
#endif
