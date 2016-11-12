//---------------------------------------------------------------------------

#ifndef bsprintH
#define bsprintH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RpCon.hpp"
#include "RpConBDE.hpp"
#include "RpConDS.hpp"
#include "RpDefine.hpp"
#include "RpRave.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include "RpBase.hpp"
#include "RpSystem.hpp"
#include "frxClass.hpp"
#include "frxDBSet.hpp"
#include "frxCross.hpp"
#include "frxRich.hpp"
#include "frxExportXLS.hpp"
#include "frxExportPDF.hpp"
#include "global.h"
//---------------------------------------------------------------------------

class Tfrmwsaleprinta : public TForm
{
__published:	// IDE-managed Components
	TRvProject *wholesale;
	TADOQuery *aqHeader;
	TRvDataSetConnection *RvDataSetConnection1;
	TADOQuery *aqdetail;
	TRvDataSetConnection *RvDataSetConnection2;
	TADOQuery *aqtotalnum;
	TRvDataSetConnection *RvDataSetConnection3;
	TRvSystem *RvSystem1;
	TRvDataSetConnection *rvstorage1;
	TRvDataSetConnection *rvstorage2;
	TADOQuery *aqrvstoragedetail;
	TADOQuery *aqhead;
	TADOQuery *aqorderhead;
	TADOQuery *aqorderdetail;
	TRvDataSetConnection *rvorderdetail;
	TRvDataSetConnection *rvorderhead;
	TADOQuery *aqProcureHeader;
	TADOQuery *aqProcureDetail;
	TRvDataSetConnection *rvProcureDetail;
	TRvDataSetConnection *rvProcureHead;
	TRvDataSetConnection *rvstoragechashu;
	TADOQuery *aqstoragechashu;
	TADOConnection *fcon;
	TfrxDBDataset *frxdbprohead;
	TfrxDBDataset *frxdbprodetail;
	TfrxDBDataset *frxDBwsalehead;
	TfrxCrossObject *frxCrossObject1;
	TfrxRichObject *frxRichObject1;
	TfrxReport *frxOrder;
	TfrxDBDataset *frxDBorddetail;
	TfrxDBDataset *frxDBordhead;
	TfrxReport *frxstorage;
	TfrxDBDataset *frxDBstohead;
	TfrxDBDataset *frxDBstodetail;
	TfrxReport *frxWsaleA4;
	TfrxReport *frxProcure;
	TfrxReport *frxWsale;
	TfrxReport *frxWsalemuilprint;
	TfrxDBDataset *frxmutildetail;
	TADOQuery *aqmuilprinthead;
	TDataSource *dsmuilprint;
	TADOQuery *aqmuildetail;
	TfrxDBDataset *frxdbwsalemuilprint;
	TfrxReport *frxsehngdaicaigou;
	TfrxReport *frxreportxiaopiao;
	TfrxDBDataset *frxDBDataset1;
	TfrxDBDataset *frxDBA4;
	TADOQuery *queryA5;
	TfrxReport *frxReportA5;
	TADOQuery *queryA4;
	void __fastcall frxProcureGetValue(const UnicodeString VarName, Variant &Value);
	void __fastcall frxWsale2GetValue(const UnicodeString VarName, Variant &Value);
	void __fastcall frxOrderGetValue(const UnicodeString VarName, Variant &Value);
	void __fastcall frxstorageGetValue(const UnicodeString VarName, Variant &Value);
	void __fastcall frxstorageBeforePrint(TfrxReportComponent *Sender);
	void __fastcall frxWsalemuilprintGetValue(const UnicodeString VarName, Variant &Value);
	void __fastcall frxWsale2BeforePrint(TfrxReportComponent *Sender);




private:	// User declarations
public:		// User declarations
	__fastcall Tfrmwsaleprinta(TComponent* Owner,TADOConnection *cn);
	TStringList * PrintTile;
         bool lianxueprint;
	void InputPara(AnsiString ID);
	void previewprint(int type , int simple);
	void PrintStorage(int ID);
	void PrintStoragechashu(int ID);
	void PrintStorageExe(int type);
	void PrintStorageExe();
	int PrintType,printmodle,tuihuo;
	bool DanhaoChange;
        bool pixiaoortuihuo;
	float yingshou,fandian,Discount;
	String Maker,num;
	AnsiString format,format1;
	AnsiString pxbk,rkbk,ClientName,supplycode,printtitle,contact,tel,address,shaddress,shtel,shcontact;
	int stgid,Kind;
	AnsiString Touppnum(AnsiString ychar);
	AnsiString Doubletostring(double num);
	AnsiString FindTitleName(AnsiString ColumnName);
	float FindTitlewith(AnsiString ColumnName);
        void ExcelExport(int type);
        AnsiString wsalexiaoshudian;
        void wsalemuilPrint(AnsiString ID,int type,bool xiaopiao);
        void SetAutoSetPageLength(TfrxReport frReport);
        int GetMaxHeight(int aPageIndex,TfrxReport frReport);
        double PelsTomm(double Pels);
        void PrintSerial(TfrxReport *Frx,int SequencePage);
        void A4print(AnsiString ID);

};

//---------------------------------------------------------------------------
extern PACKAGE Tfrmwsaleprinta *frmwsaleprinta;
#endif
