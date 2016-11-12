//---------------------------------------------------------------------------

#ifndef wenjukanliH
#define wenjukanliH
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
#include "RzDTP.hpp"
#include "frxClass.hpp"
//---------------------------------------------------------------------------
class Tfrmwenjukanli : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnExit;
	TPanel *Panel1;
	TADOQuery *aquery;
	TDataSource *ds;
	TRzToolButton *BtnNew;
	TRzToolButton *BtnExport;
	TRzToolButton *BtnDelete;
	TRzToolButton *BtnClear;
	TRzToolButton *BtnCancel;
	TADOQuery *query;
	TDBGrid *DBGrid1;
	TRzToolButton *BtnView;
	TADOQuery *aqinsert;
	TDataSource *dsinsert;
	TRzToolButton *BtnAlignBottom;
	TSaveDialog *savedlg;
	TPopupMenu *pm;
	TMenuItem *N1;
	TRzToolButton *BtnUndo;
	TRzToolButton *RzToolButton1;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label13;
	TSpeedButton *btaddtype;
	TEdit *editcode;
	TEdit *editbookname;
	TEdit *editbookself;
	TEdit *editprice;
	TEdit *editauthor;
	TEdit *edpresscount;
	TRzToolButton *RzToolButton4;
	TRzToolButton *btncnacelsave;
	TRzButton *RzButton1;
	TRzButton *RzButton2;
	TRzButton *RzButton3;
	TLabel *Label8;
	TEdit *edpinzhong;
	TGroupBox *GroupBox2;
	TRzCheckBox *rzcbinput;
	TCheckBox *chbarcode;
	TCheckBox *chname;
	TCheckBox *chprice;
	TEdit *edqrybar;
	TEdit *edqryname;
	TEdit *edqryprice;
	TSpeedButton *spselectType;
	TEdit *edquery;
	TEdit *edtypename;
	TfrxReport *frxReport1;
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall editcodeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editbooknameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall BtnClearClick(TObject *Sender);
	void __fastcall BtnCancelClick(TObject *Sender);
	void __fastcall BtnDeleteClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall DBGrid1CellClick(TColumn *Column);
	void __fastcall datapressdayKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall sedpresscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall btaddtypeClick(TObject *Sender);
	void __fastcall editwenjutiaomaoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall editbookselfKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall DBGrid1TitleClick(TColumn *Column);
	void __fastcall BtnUndoClick(TObject *Sender);
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall btncnacelsaveClick(TObject *Sender);
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall RzButton2Click(TObject *Sender);
	void __fastcall RzButton3Click(TObject *Sender);
	void __fastcall edqrybarChange(TObject *Sender);
	void __fastcall edqrynameChange(TObject *Sender);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall edpresscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall spselectTypeClick(TObject *Sender);
	void __fastcall edqueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editauthorKeyPress(TObject *Sender, wchar_t &Key);







private:	// User declarations
	TADOConnection *fcon;
	String ID;
       //	char GetPYIndexChar(char *str);
	int modle;
	int type;
	AnsiString GetSelf(AnsiString context);
	AnsiString BarCodeToISSN(AnsiString BarCode);
	AnsiString ISSNToBarCode(AnsiString ISSN);

public:		// User declarations
	__fastcall Tfrmwenjukanli(TComponent* Owner,TADOConnection *con,int stgid,int userid);
	String GetID();
	int __fastcall BrocodeToPress(String brocode);
	bool __fastcall DbgridToExcel(TDBGrid* dbg);
	int fstgid,fuserid;
        void cumvalue(AnsiString sqlsum);
	AnsiString logmessage,constbarcode;
	bool userbar;
	int TypeID;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmwenjukanli *frmwenjukanli;
//---------------------------------------------------------------------------
#endif
