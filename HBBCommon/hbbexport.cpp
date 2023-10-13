#include "StdAfx.h"
#include "resource.h"
#include "hbbexport.h"
#include "os.h"

UINT g_nFuncIcon[] = {
	IDI_HOTBIZBAR,
	IDI_SCHEDULE,
	IDI_MESSAGE,
	IDI_MAIL,
	IDI_FORUM,
	IDI_BULLETIN,
	IDI_PROJECT,
	IDI_TODO,
	IDI_RESERVE,
	IDI_CABINET,
	IDI_ADDRESS,
	IDI_WORKFLOW,
	IDI_HOTBIZBAR,
	IDI_TIMECARD,
	IDI_CIRCULATE,
	IDI_WHERE,
	IDI_REPORT,
	IDI_HOTBIZBAR
};

UINT g_nFuncItem[] = {
	0,
	IDM_SCHEDULE,
	IDM_MESSAGE,
	IDM_MAIL,
	IDM_FORUM,
	IDM_BULLETIN,
	IDM_PROJECT,
	IDM_TODO,
	IDM_RESERVE,
	IDM_CABINET,
	IDM_ADDRESS,
	IDM_WORKFLOW,
	0,
	IDM_TIMECARD,
	IDM_CIRCULATE,
	IDM_WHERE,
	IDM_REPORT,
	0
};

extern "C" VOID PASCAL EXPORT DbgMessageBox(LPCTSTR format, ...)
{
	va_list ap;
	LPTSTR pszMess;

	va_start (ap, format);
	vasprintf(&pszMess, format, ap);
	va_end (ap);

	MessageBox(NULL, pszMess, _T("Debug Message"), MB_ICONINFORMATION|MB_OK);
	free(pszMess);
}
