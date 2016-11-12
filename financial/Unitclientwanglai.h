//---------------------------------------------------------------------------

#ifndef UnitclientwanglaiH
#define UnitclientwanglaiH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include "RpBase.hpp"
#include "RpCon.hpp"
#include "RpConDS.hpp"
#include "RpDefine.hpp"
#include "RpRave.hpp"
#include "RpSystem.hpp"
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ADODB.hpp>
#include <ComCtrls.hpp>
#include <DB.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include "pdtypes.h"
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class Tfrmclientwanglai : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnView;
	TRzToolButton *BtnPrintPreview;
	TRzToolButton *BtnPrint;
	TRzToolButton *BtnProperties;
	TRzToolButton *BtnNextRecord;
	TRzToolButton *BtnExport;
	TPanel *Panel1;
	TGroupBox *GroupBox1;
	TLabel *Label7;
	TLabel *Label6;
	TLabel *Label5;
	TLabel *Label4;
	TLabel *Label3;
	TLabel *Label1;
	TLabel *Label9;
	TLabel *Label10;
	TEdit *editfax;
	TEdit *edittel;
	TEdit *editaddress;
	TEdit *editcontact;
	TEdit *editzhanhao;
	TEdit *edityijie;
	TEdit *editweijie;
	TEdit *edityue;
	TGroupBox *GroupBox5;
	TLabel *Label15;
	TLabel *Label16;
	TCheckBox *chclient;
	TEdit *editjianshuo;
	TComboBox *cbdanwei;
	TDateTimePicker *dtpend;
	TDateTimePicker *dtpbegin;
	TCheckBox *chstart;
	TCheckBox *chend;
	TCheckBox *chstate;
	TCheckBox *chfapiao;
	TComboBox *cbstate;
	TComboBox *cbfapiao;
	TCheckBox *ch1;
	TCheckBox *ch3;
	TCheckBox *ch2;
	TCheckBox *chjiekuan;
	TComboBox *cbjiekuanstate;
	TCheckBox *chfapiaohao;
	TEdit *edfapiaohao;
	TCheckBox *chshiyang;
	TEdit *edmin;
	TEdit *edmax;
	TRvProject *duizhang;
	TADOQuery *query;
	TADOQuery *aqprint;
	TRvDataSetConnection *Rvcondizhang;
	TDataSource *DataSource2;
	TRvSystem *RvSystem1;
	TSaveDialog *savedlg;
	TADOConnection *fcon;
	TPopupMenu *pmdz;
	TMenuItem *N4;
	TMenuItem *N5;
	TPopupMenu *pmfapiao;
	TMenuItem *N2;
	TMenuItem *N3;
	TPopupMenu *pm;
	TMenuItem *N1;
	TDBGrid *dg1;
	TDBGridEh *dg;
        	void __fastcall editjianshuoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbdanweiSelect(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnPrintClick(TObject *Sender);
	void __fastcall BtnPrintPreviewClick(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);
	void __fastcall BtnPropertiesClick(TObject *Sender);
	void __fastcall BtnNextRecordClick(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall dgMouseLeave(TObject *Sender);
	void __fastcall cbstateChange(TObject *Sender);
	void __fastcall cbjiekuanstateChange(TObject *Sender);
	void __fastcall cbfapiaoChange(TObject *Sender);
	void __fastcall dtpbeginChange(TObject *Sender);
	void __fastcall dtpendChange(TObject *Sender);
	void __fastcall edfapiaohaoChange(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall cbdanweiChange(TObject *Sender);
	void __fastcall edminKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edminChange(TObject *Sender);
	void __fastcall dg1DblClick(TObject *Sender);
	void __fastcall dg1Enter(TObject *Sender);
	void __fastcall queryAfterPost(TDataSet *DataSet);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall dg1TitleClick(TColumn *Column);
private:	// User declarations
   LandInfo  userInfo;
   int Client,stgid;
   String format;
   bool ChangeDisplay;
   bool ButtonType1,ButtonType2,ButtonType3;
   AnsiString sql;
   AnsiString StorageName;
public:		// User declarations
	__fastcall Tfrmclientwanglai(TComponent* Owner,int type);
        	void init(LandInfo* li);
	void GetClientInfor(AnsiString KeyWord);
	void GetClientDetail(int vendor);
	void Print(int type,int print);
	void ancode();
	bool DbgridToExcel(TDBGridEh* dbg);
	bool master;
         bool qfclient;
        bool qfsupplier;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmclientwanglai *frmclientwanglai;
//---------------------------------------------------------------------------
#endif
