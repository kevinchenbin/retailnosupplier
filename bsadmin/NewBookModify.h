//---------------------------------------------------------------------------

#ifndef NewBookModifyH
#define NewBookModifyH
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
#include <Buttons.hpp>
#include "RzDBCmbo.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBCtrls.hpp>
#include "StorageMngForm.h"
#include "RzEdit.hpp"
#include "RzSpnEdt.hpp"
#include <ComCtrls.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TfrmNewBookModify : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnExit;
	TADOQuery *aquery;
	TADOConnection *fcon;
	TADOCommand *comAddcatalog;
	TPageControl *PageControlBook;
	TTabSheet *tsbase;
	TLabel *Label8;
	TLabel *Label9;
	TSpeedButton *SpeedButton2;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label1;
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
	TTabSheet *tsdetail;
	TLabel *Label17;
	TLabel *Label18;
	TLabel *Label19;
	TLabel *Label20;
	TLabel *Label24;
	TLabel *Label25;
	TLabel *Label26;
	TLabel *Label28;
	TLabel *Label29;
	TLabel *Label35;
	TEdit *edISBNtype;
	TEdit *edbook;
	TEdit *edaffix;
	TEdit *edyizhe;
	TComboBox *cbformat;
	TComboBox *cbbind;
	TRzSpinEdit *edprintcount;
	TEdit *edhuojiangstate;
	TPageControl *pgqikan;
	TTabSheet *tabbase;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label21;
	TLabel *Label22;
	TLabel *Label31;
	TLabel *Label34;
	TLabel *Label37;
	TLabel *Label38;
	TEdit *editqikanmao;
	TEdit *editqikanname;
	TEdit *editqikanissn;
	TEdit *editqikanself;
	TEdit *editqikanprice;
	TEdit *editqikanqihao;
	TComboBox *cbpress;
	TEdit *edpress;
	TRzSpinEdit *sedyear;
	TComboBox *cbkanqi;
	TComboBox *cbduokan;
	TRzSpinEdit *sedkannum;
	TCheckBox *chduokan;
	TEdit *edkanhao;
	TEdit *edtykanhao;
	TEdit *edyearprice;
	TSpeedButton *SpeedButton1;
	TEdit *edtyname;
	TEdit *edpyquery;
	TLabel *Label27;
	TLabel *Label36;
	TEdit *meditwords;
	TEdit *medityinzhang;
	TSpeedButton *spselectType;
	TEdit *edtypequery;
	TEdit *edtypename;
	TComboBox *cbshengdai;
	TEdit *editbk;
	TLabel *Label42;
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall editcodeKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall editbooknameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall editpriceKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall rcbtypeKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall rcbpressKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edqueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall editcodeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editisbnKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall chduokanClick(TObject *Sender);
	void __fastcall editqikanmaoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editqikanqihaoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editqikanissnKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editqikannameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall sedyearKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editqikanpriceExit(TObject *Sender);
	void __fastcall editqikanpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edpressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbpressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbkanqiExit(TObject *Sender);
	void __fastcall cbkanqiKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall chduokanKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbduokanKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall sedkannumExit(TObject *Sender);
	void __fastcall sedkannumKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edkanhaoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtykanhaoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edyearpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editbooknameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editbookselfKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editauthorKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall rcbpressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall datapressdayKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edpresscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edISBNtypeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edyizheKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edprintcountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edaffixKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbformatKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbbindKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edbookKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edbkKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edhuojiangstateKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall spepackKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edpyqueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall meditwordsKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall medityinzhangKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtypequeryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbshengdaiKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editbkKeyPress(TObject *Sender, wchar_t &Key);

private:	// User declarations
	TfrmStorageMng *from;
public:		// User declarations
	__fastcall TfrmNewBookModify(TComponent* Owner,TADOConnection *con,int bkcatalogid,int stgid,int userid);
	void ReadyData();

	void Press(int mode);
	int catalogid;
	int newbook,newcatalogid,ybkcatalogid;
	void Press1(int mode);
	AnsiString BarCodeToISSN(AnsiString BarCode);
	AnsiString ISSNToBarCode(AnsiString ISSN);
	AnsiString GetSelf(AnsiString context);
	int fstgid,fuserid;
	AnsiString ybookname,logmessage;
        AnsiString GetSelfQiKan(AnsiString context);
	int TypeID;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmNewBookModify *frmNewBookModify;
//---------------------------------------------------------------------------
#endif
