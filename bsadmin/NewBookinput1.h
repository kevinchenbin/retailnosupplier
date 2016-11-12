//---------------------------------------------------------------------------

#ifndef NewBookinput1H
#define NewBookinput1H
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
#include "StorageMngForm.h"
#include <ComCtrls.hpp>
#include "RzEdit.hpp"
#include "RzSpnEdt.hpp"
#include <Mask.hpp>
#include "RzLine.hpp"
#include "ProcureMng.h"
#include "UnitBIOrder.h"
#include "MemberOrder.h"
//---------------------------------------------------------------------------
class Tfrmnewbook1 : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnExit;
	TADOQuery *aquery;
	TDataSource *ds;
	TPanel *Panel1;
	TRzDBGrid *RzDBGrid1;
	TRzCheckBox *rzcbinput;
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
	TEdit *editcode;
	TEdit *editisbn;
	TEdit *editbookname;
	TEdit *editbookself;
	TEdit *editprice;
	TEdit *editauthor;
	TComboBox *rcbpress;
	TDateTimePicker *datapressday;
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
	TEdit *edISBNtype;
	TEdit *edbook;
	TEdit *edaffix;
	TEdit *edyizhe;
	TComboBox *cbformat;
	TComboBox *cbbind;
	TRzSpinEdit *edprintcount;
	TLabel *Label1;
	TComboBox *cbsaletype;
	TRzLine *RzLine1;
	TPageControl *pcwenju;
	TTabSheet *TabSheet1;
	TLabel *Label30;
	TLabel *Label32;
	TLabel *Label33;
	TEdit *editwenjutiaomao;
	TEdit *editwenjuname;
	TEdit *editwenjuself;
	TEdit *editwenjuprice;
	TPageControl *pcqikan;
	TTabSheet *TabSheet2;
	TDBGrid *dg;
	TADOQuery *aqinsert;
	TDataSource *dsinsert;
	TEdit *edquery;
	TEdit *edpresscount;
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
	TLabel *Label23;
	TRzSpinEdit *spepack;
	TLabel *Label35;
	TEdit *edhuojiangstate;
	TLabel *Label27;
	TLabel *Label36;
	TEdit *meditwords;
	TEdit *medityinzhang;
	TLabel *Label39;
	TEdit *edchangshang;
	TLabel *Label40;
	TLabel *Label41;
	TSpeedButton *btaddtype;
	TSpeedButton *spselectType;
	TEdit *edguige;
	TEdit *edtyquery;
	TEdit *edtypename;
	TEdit *edtyname;
	TEdit *edpyquery;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton3;
	TSpeedButton *SpeedButton4;
	TSpeedButton *SpeedButton5;
	TComboBox *cbtype;
	TComboBox *qcbtype;
	TEdit *edpequery;
	TLabel *Label42;
	TEdit *editbk;
	TComboBox *cbshengdaia;
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall editcodeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall editbooknameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editauthorKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall rcbpressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall RzDBGrid1CellClick(TColumn *Column);
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
	void __fastcall cbsaletypeChange(TObject *Sender);
	void __fastcall editwenjupriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editqikanmaoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editqikanissnKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editqikannameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editqikanpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editqikanfaxingKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editwenjutiaomaoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editwenjunameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dgCellClick(TColumn *Column);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edqueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editisbnKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editbookselfKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall chduokanClick(TObject *Sender);
	void __fastcall edpressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall sedyearKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbpressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editqikanqihaoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbkanqiKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edkanhaoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtykanhaoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edyearpriceKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editqikanpriceExit(TObject *Sender);
	void __fastcall cbkanqiExit(TObject *Sender);
	void __fastcall chduokanKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbduokanKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall sedkannumExit(TObject *Sender);
	void __fastcall sedkannumKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edpresscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall spepackKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edhuojiangstateKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall meditwordsKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall medityinzhangKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall btaddtypeClick(TObject *Sender);
	void __fastcall spselectTypeClick(TObject *Sender);
	void __fastcall edtyqueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edguigeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edchangshangKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edpyqueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edpequeryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall qcbtypeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbtypeKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall editbkKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbshengdaiaKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall ComboBox1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormShow(TObject *Sender);

private:	// User declarations
	TADOConnection *fcon;
	int NewBooKCatalogID;
         int ID;
	//char GetPYIndexChar(char *str);
	int BrocodeToPress(String brocode);
	int type;
		void ShowInput(int type);
	AnsiString GetSelf(AnsiString context);
	AnsiString BarCodeToISSN(AnsiString BarCode);
	AnsiString ISSNToBarCode(AnsiString ISSN);
        AnsiString GetSelfQiKan(AnsiString context);
public:		// User declarations
	__fastcall Tfrmnewbook1(TComponent* Owner,TADOConnection *con);
	void ReadyData();
	bool userbar;
	int GetID();

	void Press(int mode);
	TfrmStorageMng * StorageMng;
	TfrmProcureMng * ProcureMng;
	TfrmBIorder * BIorder;
        Tfrmmemberorder *memberorder;
	int modle;  //1入库，2智能入库，3采购，4订单
	void Press1(int mode);
	AnsiString constbarcode;
	int TypeID;
        void presstype(int mode,int selecttype);  //1.图书2,期刊3,文具
        int GetIDFromText(int type);


};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmnewbook1 *frmnewbook1;
//---------------------------------------------------------------------------
#endif
