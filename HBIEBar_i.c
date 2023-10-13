

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IHotBizBar,0x409F0914,0xE242,0x4A54,0xAD,0xED,0x36,0x0E,0x6D,0xF4,0x7F,0xF2);


MIDL_DEFINE_GUID(IID, LIBID_HBIEBARLib,0x07DFE7F2,0xFBFD,0x4F20,0xA5,0x0D,0x26,0xB9,0x2E,0x65,0xE6,0xAB);


MIDL_DEFINE_GUID(CLSID, CLSID_HotBizBar,0xCB07F490,0x0619,0x4D1D,0xB4,0x4A,0x8F,0x45,0x8E,0x47,0xD0,0xDF);


MIDL_DEFINE_GUID(CLSID, CLSID_IconPage,0xF288E7B8,0xC81F,0x4CDA,0xA2,0xF8,0x24,0x5E,0xF8,0x3F,0x38,0xA9);


MIDL_DEFINE_GUID(CLSID, CLSID_HostPage,0xD13B392B,0x5DDC,0x438B,0x9E,0x7B,0xCD,0xE7,0x14,0x17,0x9E,0x9A);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



