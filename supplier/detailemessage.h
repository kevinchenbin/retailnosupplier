//---------------------------------------------------------------------------

#ifndef detailemessageH
#define detailemessageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzDBEdit.hpp"
#include "RzEdit.hpp"
#include "RzLabel.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <Mask.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzCmboBx.hpp"
#include <ComCtrls.hpp>
#include "global.h"
//---------------------------------------------------------------------------
class TDetaileForm : public TForm
{
__published:	// IDE-managed Components
	TRzGroupBox *RzGroupBox1;
	TRzLabel *RzLabel2;
	TRzLabel *RzLabel3;
	TRzLabel *RzLabel4;
	TRzLabel *RzLabel5;
	TRzLabel *RzLabel9;
	TRzLabel *RzLabel11;
	TRzLabel *RzLabel8;
	TLabel *Label1;
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnExit;
	TADOQuery *aqinit;
	TADOQuery *aqdetail;
	TRzEdit *dbedtName;
	TRzEdit *dbedit;
	TRzEdit *dbeditContact;
	TEdit *edtphone;
	TEdit *edtcode;
	TEdit *edtfax;
	TLabel *Label2;
	TEdit *edsecondcontact;
	TLabel *Label3;
	TEdit *edemail;
	TLabel *Label4;
	TEdit *edqq;
	TLabel *Label7;
	TEdit *edbank;
	TLabel *Label8;
	TEdit *edbankaccount;
	TLabel *Label12;
	TEdit *edlogname;
	TLabel *Label13;
	TEdit *edpassword;
	TLabel *Label10;
	TComboBox *cbtype;
	TLabel *Label11;
	TRzToolButton *BtnAlignBottom;
	TComboBox *CBlocal;
	TComboBox *CBsale;
	TRzLabel *RzLabel1;
	TEdit *edmobile;
	TRzLabel *RzLabel6;
	TLabel *Label5;
	TEdit *edxinyong;
	TEdit *edbaozj;
	TRzLabel *RzLabel7;
	TRzEdit *edbk;
	TComboBox *cbdaozhan;
	TLabel *Label6;
	TEdit *editdaozhan;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall dbedtNameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edtphoneKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall dbeditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall CBlocal1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall dbeditContactKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edtfaxKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edtcodeKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edsecondcontactKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edemailKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edmsnaddressKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edqqKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edbankKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edbankaccountKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edlognameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edpasswordKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall CBlocalKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall CBsaleKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edmobileKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edxinyongKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edbaozjKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall cbtypeKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edbkKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall editdaozhanKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);












private:	// User declarations
	int modsave,Type;
	String ID;
        int fstgid;
public:		// User declarations
	__fastcall TDetaileForm(TComponent* Owner,int type,int savamod,String id,TADOConnection *cnn,int stgid);
	void Initsalesman();
	void InitLocalinfo();
	void InitType();
	int getsalemanid(AnsiString name);
	int ParentID ;
        int clientid;
};
//---------------------------------------------------------------------------
extern PACKAGE TDetaileForm *DetaileForm;
//---------------------------------------------------------------------------
#endif
