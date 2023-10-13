

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Mon Apr 20 14:57:11 2009
 */
/* Compiler settings for .\HBIEBar.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __HBIEBar_h__
#define __HBIEBar_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IHotBizBar_FWD_DEFINED__
#define __IHotBizBar_FWD_DEFINED__
typedef interface IHotBizBar IHotBizBar;
#endif 	/* __IHotBizBar_FWD_DEFINED__ */


#ifndef __HotBizBar_FWD_DEFINED__
#define __HotBizBar_FWD_DEFINED__

#ifdef __cplusplus
typedef class HotBizBar HotBizBar;
#else
typedef struct HotBizBar HotBizBar;
#endif /* __cplusplus */

#endif 	/* __HotBizBar_FWD_DEFINED__ */


#ifndef __IconPage_FWD_DEFINED__
#define __IconPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class IconPage IconPage;
#else
typedef struct IconPage IconPage;
#endif /* __cplusplus */

#endif 	/* __IconPage_FWD_DEFINED__ */


#ifndef __HostPage_FWD_DEFINED__
#define __HostPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class HostPage HostPage;
#else
typedef struct HostPage HostPage;
#endif /* __cplusplus */

#endif 	/* __HostPage_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IHotBizBar_INTERFACE_DEFINED__
#define __IHotBizBar_INTERFACE_DEFINED__

/* interface IHotBizBar */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IHotBizBar;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("409F0914-E242-4A54-ADED-360E6DF47FF2")
    IHotBizBar : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IHotBizBarVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IHotBizBar * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IHotBizBar * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IHotBizBar * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IHotBizBar * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IHotBizBar * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IHotBizBar * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IHotBizBar * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IHotBizBarVtbl;

    interface IHotBizBar
    {
        CONST_VTBL struct IHotBizBarVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHotBizBar_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHotBizBar_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IHotBizBar_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IHotBizBar_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IHotBizBar_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IHotBizBar_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IHotBizBar_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IHotBizBar_INTERFACE_DEFINED__ */



#ifndef __HBIEBARLib_LIBRARY_DEFINED__
#define __HBIEBARLib_LIBRARY_DEFINED__

/* library HBIEBARLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_HBIEBARLib;

EXTERN_C const CLSID CLSID_HotBizBar;

#ifdef __cplusplus

class DECLSPEC_UUID("CB07F490-0619-4D1D-B44A-8F458E47D0DF")
HotBizBar;
#endif

EXTERN_C const CLSID CLSID_IconPage;

#ifdef __cplusplus

class DECLSPEC_UUID("F288E7B8-C81F-4CDA-A2F8-245EF83F38A9")
IconPage;
#endif

EXTERN_C const CLSID CLSID_HostPage;

#ifdef __cplusplus

class DECLSPEC_UUID("D13B392B-5DDC-438B-9E7B-CDE714179E9A")
HostPage;
#endif
#endif /* __HBIEBARLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


