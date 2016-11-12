#ifndef bsadminH
#define bsadminH

#include <ADODB.hpp>
#include "pdtypes.h"
#include "RpDefine.hpp"
extern "C" __declspec(dllexport) void __stdcall ManageMarketing(LandInfo* li,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall ManageRetail(AnsiString powerlist,LandInfo* li,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall ManageOrder(LandInfo* li,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall ManageProcurement(LandInfo* li,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall ManageStorage(LandInfo* li,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall CheckQuery(LandInfo* li,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall SupplierManage(LandInfo* li,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall OrderManage(LandInfo* li,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall ProcureManage(LandInfo *li,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall ManageReturnStorage(LandInfo* li,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall ManageReturnMarketing(LandInfo* li,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall ManageReturnRetail(LandInfo* li,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall StockAdjust(LandInfo *li,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall BIOrderManage(LandInfo *li,int type,HWND MainHandle);
//extern "C" __declspec(dllexport) void __stdcall SupplierModify(LandInfo *li,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall Stockxuyi(LandInfo *li,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall fastcheck(LandInfo *li,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall ZNProcureManage(LandInfo *li,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall BIOrderManageDanHao(LandInfo *li,AnsiString Danhao,HWND MainHandle);
//extern "C" __declspec(dllexport) void __stdcall ZNStorage(LandInfo *li,HWND MainHandle);
//extern "C" __declspec(dllexport) void __stdcall ZNWsale(LandInfo *li,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall Ysbooksale(LandInfo *li,HWND MainHandle);
//extern "C" __declspec(dllexport) void __stdcall OrdereShenhei(LandInfo *li,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall CaigoufromOrder(LandInfo *li,HWND MainHandle);
//extern "C" __declspec(dllexport) void __stdcall daohuofenfa(LandInfo *li,HWND MainHandle);
//extern "C" __declspec(dllexport) void __stdcall orderask(LandInfo *li,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall siglefenfa(LandInfo *li,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall DiaoBo(LandInfo *li,int modle,AnsiString Danhao,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall ZNReturnStock(LandInfo *li,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall Catalogneworrecbsadmin(TApplication* app, TADOConnection* con,HWND MainHandle,LandInfo *li);
extern "C" __declspec(dllexport) void __stdcall DaiXiao(LandInfo* li,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall DiaoxiaoCaigouFahuo(LandInfo* li,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall pixiaohuizhong(LandInfo* li,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall Tearcher(LandInfo* li,HWND MainHandle);
extern "C" __declspec(dllexport) void __stdcall TearcherSearch(LandInfo* li,HWND MainHandle);

#endif
