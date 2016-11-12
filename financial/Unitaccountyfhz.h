//---------------------------------------------------------------------------

#ifndef UnitaccountyfhzH
#define UnitaccountyfhzH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "RpBase.hpp"
#include "RpCon.hpp"
#include "RpConDS.hpp"
#include "RpDefine.hpp"
#include "RpRave.hpp"
#include "RpSystem.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <Dialogs.hpp>
#include <ImgList.hpp>
#include "global.h"
//---------------------------------------------------------------------------
class Taccountyfhz : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnView;
	TRzToolButton *BtnExport;
	TRzToolButton *BtnPrint;
	TRzToolButton *BtnPrintPreview;
	TRzToolButton *BtnAlignBottom;
	TPanel *Panel1;
	TLabel *Label2;
	TGroupBox *GroupBox1;
	TLabel *Label4;
	TDateTimePicker *DTPstart;
	TDateTimePicker *DTPend;
	TCheckBox *CBstart;
	TCheckBox *CBend;
	TEdit *edquery;
	TCheckBox *chhuizong;
	TCheckBox *chprofite;
	TCheckBox *chname;
	TComboBox *cbInOut;
	TComboBox *cbCusName;
	TDBGridEh *DBGridtotal;
	TSaveDialog *savedlg;
	TRvProject *RvProject1;
	TImageList *ImageList1;
	TRvDataSetConnection *rvdatacon;
	TRvSystem *RvSystem1;
	TDataSource *ds;
	TADOQuery *aquery;
	TADOQuery *aqcustom;
	TLabel *labtitle;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall BtnPrintPreviewClick(TObject *Sender);
	void __fastcall BtnPrintClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall DTPstartClick(TObject *Sender);
	void __fastcall DTPendClick(TObject *Sender);
	void __fastcall DBGridtotalTitleClick(TColumnEh *Column);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall edqueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
        TADOConnection *fcon;
	int type;
	String Disc;
        int fstgid;
public:		// User declarations
	__fastcall Taccountyfhz(TComponent* Owner,int Type,TADOConnection *cn,int stgid);
        AnsiString querysql,username,stogName;
        bool __fastcall DbgridToExcel(TDBGridEh* dbg);
};
//---------------------------------------------------------------------------
extern PACKAGE Taccountyfhz *accountyfhz;
//---------------------------------------------------------------------------
#endif
