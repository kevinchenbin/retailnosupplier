//---------------------------------------------------------------------------

#ifndef MemberFormH
#define MemberFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzDBEdit.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include <Mask.hpp>
#include "RzDBGrid.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "RzLine.hpp"
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Buttons.hpp>
#include <DBTables.hpp>
#include <DBClient.hpp>
#include "MemberCard.h"
#include "MemberCardaddvalue.h"
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include "MemberImport.h"
//---------------------------------------------------------------------------
class TfrmMember : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *rztlbr1;
	TRzToolButton *btAdd;
	TRzToolButton *btDelete;
	TRzToolButton *btEsc;
	TRzToolButton *btUpdate;
	TImageList *ImageListmember;
	TADODataSet *dsMemberInfo;
	TADOQuery *quMemberInfo;
	TDataSource *DataSource1;
	TADOQuery *quType;
	TPopupMenu *rtkeydowm;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *addvalue;
	TADOQuery *quMemberCard;
	TADOQuery *quMemberRecord;
	TOpenTextFileDialog *OpenTextFileDialog1;
	TRzToolButton *BtnExport;
	TRzToolButton *BtnImport;
	TRzToolButton *BtnChangeOptions;
	TRzToolButton *BtnError;
	TRzToolButton *BtnAlignBottom;
	TRzToolButton *BtnWordWrap;
	TRzToolButton *BtnClear;
	TRzToolButton *BtnSendtoBack;
	TMenuItem *N4;
	TMenuItem *N5;
	TDBGrid *dgmemlist;
	TGroupBox *GroupBox1;
	TSpeedButton *sbquery;
	TLabel *Label5;
	TLabel *Label6;
	TEdit *edtcardnum;
	TEdit *edtname;
	TComboBox *cbMemberType;
	TCheckBox *chsex;
	TComboBox *cbsex;
	TCheckBox *chstate;
	TComboBox *cbstate;
	TCheckBox *chjifen;
	TEdit *edminjifen;
	TEdit *edmaxjifen;
	TCheckBox *chjine;
	TEdit *edminjine;
	TEdit *edmaxjine;
	TCheckBox *chname;
	TCheckBox *chcard;
	TCheckBox *chtype;
	TCheckBox *chstart;
	TDateTimePicker *dtpstart;
	TCheckBox *chend;
	TDateTimePicker *dtpend;
	TSaveDialog *savedlg;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall sbqueryClick(TObject *Sender);
	void __fastcall btEscClick(TObject *Sender);
	void __fastcall btAddClick(TObject *Sender);
	void __fastcall btUpdateClick(TObject *Sender);
	void __fastcall btDeleteClick(TObject *Sender);
	void __fastcall cbMemberTypeSelect(TObject *Sender);
	void __fastcall addvalueClick(TObject *Sender);
	void __fastcall dgmemlistTitleClick(TColumn *Column);
	void __fastcall edtcardnumKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edtnameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall BtnImportClick(TObject *Sender);
	void __fastcall BtnChangeOptionsClick(TObject *Sender);
	void __fastcall BtnErrorClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignBottomClick(TObject *Sender);

	void __fastcall edtcardnumChange(TObject *Sender);
	void __fastcall edtnameChange(TObject *Sender);
	void __fastcall cbsexChange(TObject *Sender);
	void __fastcall cbMemberTypeChange(TObject *Sender);
	void __fastcall edminjifenChange(TObject *Sender);
	void __fastcall edminjineChange(TObject *Sender);
	void __fastcall cbstateChange(TObject *Sender);
	void __fastcall dtpstartChange(TObject *Sender);
	void __fastcall dtpendChange(TObject *Sender);
	void __fastcall cbsexKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edminjifenKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edmaxjifenKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edminjineKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edmaxjineKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbstateKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dtpstartKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dtpendKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnWordWrapClick(TObject *Sender);
	void __fastcall BtnClearClick(TObject *Sender);
	void __fastcall BtnSendtoBackClick(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);


private:	// User declarations
	TStringList * MemberinfoList;
	TADOConnection *fcon;
	void __fastcall OnMinMaxSize(TMessage &Msg);
	BEGIN_MESSAGE_MAP
	MESSAGE_HANDLER(WM_SYSCOMMAND, TMessage, OnMinMaxSize)
	END_MESSAGE_MAP(TForm)
public:		// User declarations
	__fastcall TfrmMember(TComponent* Owner,TADOConnection *cn);
	bool __fastcall DbgridToExcel(TDBGrid* dbg);
	int userid,stgid;
		void __fastcall dgmemlistDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
		  TColumn *Column, Grids::TGridDrawState State);
};

//---------------------------------------------------------------------------
extern PACKAGE TfrmMember *frmMember;
//---------------------------------------------------------------------------
#endif
