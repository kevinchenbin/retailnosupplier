#ifndef catalogadminH
#define catalogadminH

#include <ADODB.hpp>

extern "C" __declspec(dllexport) void __stdcall ManagePress(TApplication* app, TADOConnection* con,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall ManageBookType(TApplication* app, TADOConnection* con,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall CatalogKan(TApplication* app, TADOConnection* con,int stgid,int userid,HWND MainHandle,int version);
extern "C" __declspec(dllexport) void __stdcall Catalogbuilt(TApplication* app, TADOConnection* con,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall Catalogneworrec(TApplication* app, TADOConnection* con,int stgid,int userid,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall QiKanguanli(TApplication* app, TADOConnection* con,int stgid,HWND MainHandle,int version);
extern "C" __declspec(dllexport) void __stdcall Multibook(TApplication* app, TADOConnection* con,int stgid,int userid,HWND MainHandle);
//extern "C" __declspec(dllexport) void __stdcall QiKanguanli(TApplication* app, TADOConnection* con,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall WenJuguanli(TApplication* app, TADOConnection* con,int stgid,int userid,HWND MainHandle);
#endif
