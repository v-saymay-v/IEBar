#ifndef __HTTPPOST_H__
#define __HTTPPOST_H__

int Http_Head_Get_Result(const TCHAR* chp_host, char** chpp_result);
#ifdef _UNICODE
int Http_Head_Get_Result(const TCHAR* chp_host, TCHAR** chpp_result);
#endif

int Http_Post_Get_Result(LPCTSTR chp_host, LPCTSTR chp_path, LPCTSTR chp_params, LPCTSTR chp_cookie, LPSTR* chpp_result);
#ifdef _UNICODE
int Http_Post_Get_Result(LPCTSTR chp_host, LPCTSTR chp_path, LPCTSTR chp_params, LPCTSTR chp_cookie, LPTSTR* chpp_result);
#endif

int Https_Post_Get_Result(LPCTSTR chp_host, LPCTSTR chp_path, LPCTSTR chp_params, LPCTSTR chp_cookie, LPSTR* chpp_result);
#ifdef _UNICODE
int Https_Post_Get_Result(LPCTSTR chp_host, LPCTSTR chp_path, LPCTSTR chp_params, LPCTSTR chp_cookie, LPTSTR* chpp_result);
#endif

#endif
