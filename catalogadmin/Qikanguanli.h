//---------------------------------------------------------------------------

#ifndef QikanguanliH
#define QikanguanliH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "RzCmboBx.hpp"
#include "RzDBGrid.hpp"
#include "RzRadChk.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "pdutil.h"
#include <Buttons.hpp>
#include "RzEdit.hpp"
#include "RzLine.hpp"
#include <Mask.hpp>
#include "RzRadGrp.hpp"
#include "RzLabel.hpp"
#include <ComCtrls.hpp>
#include "RzSpnEdt.hpp"
#include "StrUtils.hpp"
#include <Dialogs.hpp>
#include <Menus.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
//---------------------------------------------------------------------------
class TfrmQikanguanli : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnExit;
	TPanel *Panel1;
	TRzCheckBox *rzcbinput;
	TADOQuery *aquery;
	TDataSource *ds;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnExport;
	TRzToolButton *BtnDelete;
	TRzToolButton *BtnClear;
	TRzToolButton *BtnCancel;
	TADOQuery *query;
	TRzToolButton *BtnView;
	TADOQuery *aqinsert;
	TDataSource *dsinsert;
	TRzToolButton *BtnJumptoLine;
	TRzToolButton *BtnAlignBottom;
	TSaveDialog *savedlg;
	TPopupMenu *pm;
	TMenuItem *N1;
	TRzToolButton *BtnInsertRecord;
	TADOStoredProc *addqikan;
	TRzToolButton *BtnUndo;
	TRzDBGrid *dg;
	TGroupBox *GroupBox2;
	TLabel *Label25;
	TLabel *Label26;
	TLabel *Label27;
	TLabel *Label28;
	TLabel *Label1;
	TLabel *Label7;
	TLabel *Label6;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TEdit *editqikanmao;
	TEdit *editqikanname;
	TEdit *editqikanissn;
	TEdit *editqikanself;
	TEdit *editqikanprice;
	TEdit *editqikanqihao;
	TComboBox *rcbpress;
	TEdit *edquery;
	TRzSpinEdit *sedyear;
	TComboBox *cbkanqi;
	TComboBox *cbduokan;
	TRzSpinEdit *sedkannum;
	TCheckBox *chduokan;
	TComboBox *cbyoufa;
	TEdit *youfacode;
	TEdit *edkanhao;
	TEdit *edtykanhao;
	TEdit *bk;
	TEdit *edyearprice;
	TGroupBox *GroupBox1;
	TEdit *edpressarea;
	TRzButton *RzButton1;
	TRzButton *RzButton2;
	TRzButton *RzButton3;
	TRzToolButton *BtnSaveCancel;
	TLabel *Label13;
	TEdit *edpinzhong;
	TSpeedButton *spselectType;
	TEdit *edtypename;
	TSpeedButton *btaddtype;
	TComboBox *qcbtype;
	TEdit *edtypequery;
	TComboBox *cbdaixiao;
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall BtnClearClick(TObject *Sender);
	void __fastcall BtnCancelClick(TObject *Sender);
	void __fastcall BtnDeleteClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall editqikanmaoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editqikanqihaoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editqikannameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editqikanissnKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editqikanpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall chtaoshuKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall chduokanClick(TObject *Sender);
	void __fastcall edqueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall rcbpressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editqikanselfKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall rcbtypeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbkanqiKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall chduokanKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edyearpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edkanhaoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtykanhaoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbyoufaKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall youfacodeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edpressareaKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall bkKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall sedyearKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall sedkannumKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbduokanKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnInsertRecordClick(TObject *Sender);
	void __fastcall cbkanqiExit(TObject *Sender);
	void __fastcall sedkannumExit(TObject *Sender);
	void __fastcall editqikanqihaoExit(TObject *Sender);
	void __fastcall BtnUndoClick(TObject *Sender);
	void __fastcall dgCellClick(TColumn *Column);
	void __fastcall dgTitleClick(TColumn *Column);
	void __fastcall BtnSaveCancelClick(TObject *Sender);
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall RzButton2Click(TObject *Sender);
	void __fastcall RzButton3Click(TObject *Sender);
	void __fastcall btaddtypeClick(TObject *Sender);
	void __fastcall spselectTypeClick(TObject *Sender);
	void __fastcall edtypequeryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall qcbtypeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbdaixiaoKeyPress(TObject *Sender, wchar_t &Key);

private:	// User declarations
	TADOConnection *fcon;
	String ID;
       //	AnsiString GetPYIndexChar(char *str);
	int modle;
	int type;
	AnsiString GetSelf(AnsiString context);
        AnsiString GetSelfQiKan(AnsiString context);
	AnsiString BarCodeToISSN(AnsiString BarCode);
	AnsiString ISSNToBarCode(AnsiString ISSN);

	void ReadyData();
        bool DbgridToExcel(TDBGrid* dbg);

public:		// User declarations
	__fastcall TfrmQikanguanli(TComponent* Owner,TADOConnection *con,int stgid);
	String GetID();
	void Query(String condition);
	int __fastcall BrocodeToPress(String brocode);
	bool __fastcall DbgridToExcel(TRzDBGrid* dbg);
	void Press(int mode);
	int TypeID,fstgid;
        int version;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmQikanguanli *frmQikanguanli;
//---------------------------------------------------------------------------
#endif
