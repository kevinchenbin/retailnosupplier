//---------------------------------------------------------------------------

#ifndef CatalogkanliH
#define CatalogkanliH
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
class TfrmCatalogkanli : public TForm
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
	TRzToolButton *BtnImport;
	TRzToolButton *BtnExport;
	TRzToolButton *BtnDelete;
	TRzToolButton *BtnClear;
	TRzToolButton *BtnCancel;
	TADOQuery *query;
	TDBGrid *DBGrid1;
	TRzToolButton *BtnView;
	TADOQuery *aqinsert;
	TDataSource *dsinsert;
	TRzToolButton *BtnJumptoLine;
	TRzToolButton *BtnAlignBottom;
	TSaveDialog *savedlg;
	TPopupMenu *pm;
	TMenuItem *N1;
	TRzToolButton *BtnAlignClient;
	TRzToolButton *BtnUndo;
	TfrxReport *frxReport1;
	TRzToolButton *RzToolButton1;
	TGroupBox *GroupBox1;
	TLabel *Label22;
	TLabel *Label34;
	TLabel *Label35;
	TLabel *Label1;
	TLabel *Label2;
	TSpeedButton *SpeedButton1;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label11;
	TLabel *Label13;
	TSpeedButton *btaddtype;
	TSpeedButton *btaddpress;
	TLabel *Label17;
	TLabel *Label14;
	TLabel *Label12;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label19;
	TLabel *Label20;
	TLabel *Label10;
	TLabel *Label23;
	TLabel *Label24;
	TLabel *Label21;
	TMemo *mcontent;
	TEdit *meditwords;
	TEdit *medityinzhang;
	TEdit *editcode;
	TEdit *editisbn;
	TEdit *editbookname;
	TEdit *editbookself;
	TEdit *editprice;
	TEdit *editauthor;
	TComboBox *rcbpress;
	TDateTimePicker *datapressday;
	TEdit *edquery;
	TEdit *edpresscount;
	TRzSpinEdit *spepack;
	TEdit *edISBNtype;
	TEdit *edbook;
	TEdit *edaffix;
	TEdit *edyizhe;
	TComboBox *cbformat;
	TComboBox *cbbind;
	TRzSpinEdit *edprintcount;
	TEdit *edhuojiangstate;
	TRzToolButton *RzToolButton4;
	TRzToolButton *btncnacelsave;
	TRzButton *RzButton1;
	TRzButton *RzButton2;
	TRzButton *RzButton3;
	TLabel *Label8;
	TEdit *edpinzhong;
	TSpeedButton *spselectType;
	TEdit *edtypequery;
	TEdit *edtypename;
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall editcodeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall editbooknameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editauthorKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall rcbtypeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall rcbpressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall edtQueryKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnNewClick(TObject *Sender);
	void __fastcall BtnClearClick(TObject *Sender);
	void __fastcall BtnCancelClick(TObject *Sender);
	void __fastcall BtnDeleteClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnExportClick(TObject *Sender);
	void __fastcall BtnImportClick(TObject *Sender);
	void __fastcall DBGrid1CellClick(TColumn *Column);
	void __fastcall datapressdayKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall sedpresscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edISBNtypeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edyizheKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edprintcountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edaffixKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbformatKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbbindKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edbookKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edbkKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnViewClick(TObject *Sender);
	void __fastcall btaddtypeClick(TObject *Sender);
	void __fastcall btaddpressClick(TObject *Sender);
	void __fastcall cbsaletypeChange(TObject *Sender);
	void __fastcall editwenjutiaomaoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnJumptoLineClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edqueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editisbnKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall editbookselfKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall DBGrid1TitleClick(TColumn *Column);
	void __fastcall BtnAlignClientClick(TObject *Sender);
	void __fastcall edpresscountKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnUndoClick(TObject *Sender);
	void __fastcall RzToolButton1Click(TObject *Sender);
	void __fastcall edhuojiangstateKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall meditwordsKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall medityinzhangKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall mcontentKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall btncnacelsaveClick(TObject *Sender);
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall RzButton2Click(TObject *Sender);
	void __fastcall RzButton3Click(TObject *Sender);
	void __fastcall spselectTypeClick(TObject *Sender);
	void __fastcall edtypequeryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall spepackKeyPress(TObject *Sender, wchar_t &Key);


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
	__fastcall TfrmCatalogkanli(TComponent* Owner,TADOConnection *con,int stgid,int userid);
	void ReadyData();
	String GetID();
	void Query(String condition);
	int __fastcall BrocodeToPress(String brocode);
	bool __fastcall DbgridToExcel(TDBGrid* dbg);
	void Press(int mode);
	int fstgid,fuserid;
        void cumvalue(AnsiString sqlsum);
	AnsiString logmessage,constbarcode;
	bool userbar;
	int TypeID;
        int version;
        AnsiString paw;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCatalogkanli *frmCatalogkanli;
//---------------------------------------------------------------------------
#endif
