//---------------------------------------------------------------------------

#ifndef accountdetailH
#define accountdetailH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzButton.hpp"
#include "RzCmboBx.hpp"
#include <ComCtrls.hpp>
#include "RzEdit.hpp"
#include <Mask.hpp>
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzRadChk.hpp"
#include <Buttons.hpp>
#include "RpBase.hpp"
#include "RpCon.hpp"
#include "RpConDS.hpp"
#include "RpDefine.hpp"
#include "RpRave.hpp"
#include "RpSystem.hpp"
#include <Dialogs.hpp>
#include "global.h"
#include <Menus.hpp>
#include "frxClass.hpp"
#include "frxDBSet.hpp"
#include "frxExportPDF.hpp"
#include "frxExportCSV.hpp"
#include "frxExportHTML.hpp"
#include "frxExportImage.hpp"
#include "frxExportRTF.hpp"
#include "frxExportXLS.hpp"
//---------------------------------------------------------------------------

class TAccDetail : public TForm
{
__published:	// IDE-managed Components
	TImageList *ImageList1;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnView;
	TRzToolButton *BtnExit;
	TDataSource *ds1;
	TDataSource *da2;
	TADOQuery *Querybase;
	TADOQuery *Querydetail;
	TADOQuery *aquery;
	TADOQuery *Querybance;
	TRzToolButton *BtnExport;
	TADOQuery *aq;
	TRvSystem *RvSystem1;
	TRvProject *RvProject1;
	TRvDataSetConnection *dc;
	TADOQuery *aqprint;
	TRzToolButton *BtnPrint;
	TRzToolButton *BtnPrintPreview;
	TRzToolButton *BtnAlignBottom;
	TSaveDialog *savedlg;
	TRzDBGrid *DBGridbase;
	TRzDBGrid *DBGriddetail;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TDateTimePicker *DTPstart;
	TDateTimePicker *DTPend;
	TRzCheckBox *CBstart;
	TRzCheckBox *CBend;
	TEdit *edquery;
	TCheckBox *chguolv;
	TComboBox *CBstate;
	TComboBox *CBcustom;
	TGroupBox *GroupBox2;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TRzEdit *etshiyang;
	TRzEdit *etchecked;
	TRzEdit *etleftmoney;
	TRzEdit *etaddcost;
	TRzEdit *etcount;
	TPopupMenu *PopupMenu1;
	TMenuItem *N1;
	TMenuItem *N2;
	TPopupMenu *PopupMenu2;
	TMenuItem *N3;
	TMenuItem *N4;
	TCheckBox *cbf;
	TCheckBox *cbt;
	TfrxReport *frxReport1;
	TfrxDBDataset *frxDBDataset1;
	TPopupMenu *PopupMenu3;
	TMenuItem *N5;
	TMenuItem *N6;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall DBGridbaseCellClick(TColumn *Column);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall edqueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall DTPstartChange(TObject *Sender);
	void __fastcall DTPendChange(TObject *Sender);
	void __fastcall DBGridbaseTitleClick(TColumn *Column);
	void __fastcall DBGriddetailTitleClick(TColumn *Column);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall frxReport1GetValue(const UnicodeString VarName, Variant &Value);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);

private:	// User declarations
	int type,type1;
	String Disc;
	TADOConnection *fcon;
	bool ChangeDisplay;
	AnsiString sqlwhere;
	AnsiString sql1,sql;
public:		// User declarations
	__fastcall TAccDetail(TComponent* Owner,int Type,TADOConnection *cn,int stgid);
	bool __fastcall DbgridToExcel(TRzDBGrid* dbg);
        	bool __fastcall DbgridToExceler(TRzDBGrid* dbg);
	void PrintFunction(int  type);
        void ExcelOut(TADOQuery *adoquery,TDBGrid *dbg,AnsiString strfile);
	AnsiString stogName,Maker;
	//int ClientID;
	String storageformat,saleformat;
          int fstgid;
        AnsiString user;
        AnsiString GetSearchID();
        AnsiString getheaderid;
        AnsiString TotalChecked,TotalNoChecked,TotalAmount,TotalFix,TotalDis,TotalFixDaxie,Totaladdcosts,TotalHuikuan;

        AnsiString fh,fht;
        AnsiString rk,rkt;
        void GetPrintWith();
        void PrintReport(int mode);
               AnsiString Touppnum(AnsiString ychar);
	AnsiString Doubletostring(double num);
	AnsiString FindTitleName(AnsiString ColumnName);
	float FindTitlewith(AnsiString ColumnName);
        TStringList * PrintTile;
        	AnsiString format,format1;
	AnsiString pxbk,rkbk,ClientName,supplycode,printtitle,contact,tel,telephone,address,shaddress,shtel,shcontact;
        AnsiString stgname,stgtel,stgaddress,stgcontact;
        int  ta;
        float tf,td;
        bool qfsupplier;
        bool qfclient;
};
//---------------------------------------------------------------------------
extern PACKAGE TAccDetail *AccDetail;
//---------------------------------------------------------------------------
#endif
