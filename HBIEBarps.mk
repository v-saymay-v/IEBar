
HBIEBarps.dll: dlldata.obj HBIEBar_p.obj HBIEBar_i.obj
	link /dll /out:HBIEBarps.dll /def:HBIEBarps.def /entry:DllMain dlldata.obj HBIEBar_p.obj HBIEBar_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del HBIEBarps.dll
	@del HBIEBarps.lib
	@del HBIEBarps.exp
	@del dlldata.obj
	@del HBIEBar_p.obj
	@del HBIEBar_i.obj
