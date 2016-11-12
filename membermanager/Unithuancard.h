//---------------------------------------------------------------------------

#ifndef UnithuancardH
#define UnithuancardH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "RzPanel.hpp"
#include <ImgList.hpp>
#include "RzButton.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include "RzCmboBx.hpp"
#include <ComCtrls.hpp>
#include "global.h"
//---------------------------------------------------------------------------
class Tfrmhuancard : public TForm
{
__published:	// IDE-managed Components
	TImageList *ImageList1;
	TADOConnection *fcon;
	TEdit *edpassword;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label12;
	TEdit *edcard;
	TEdit *edname;
	TEdit *edtype;
	TEdit *edsex;
	TEdit *edyue;
	TEdit *edconsumption;
	TEdit *edjifen;
	TEdit *eddiscount;
	TLabel *Label8;
	TGroupBox *newcard;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TLabel *membername;
	TLabel *membercardid;
	TLabel *membersex;
	TLabel *memberbirthday;
	TLabel *membertype;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label14;
	TEdit *edtname;
	TEdit *edtcardID;
	TEdit *edtdiscount;
	TDateTimePicker *tdtbirthday;
	TEdit *edCardCast;
	TEdit *edtpwd;
	TRadioGroup *rg;
	TDateTimePicker *dtpyouxiao;
	TComboBox *cbtype;
	TComboBox *cbsex;
	TTabSheet *TabSheet2;
	TLabel *membertelephone;
	TLabel *membermobile;
	TLabel *memberaddress;
	TLabel *memberpostalcode;
	TLabel *Label13;
	TEdit *edttelephone;
	TEdit *edtmobile;
	TEdit *edtaddress;
	TEdit *edtpostalcode;
	TEdit *edbircard;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnExit;
	TRzToolButton *BtnSendtoBack;
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall BtnSendtoBackClick(TObject *Sender);
	void __fastcall edtcardIDKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtpwdKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edpasswordKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edCardCastKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbtypeSelect(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tfrmhuancard(TComponent* Owner,TADOConnection *con,int cardid);
	int ycardid,newcardid,password;
	AnsiString Pwd;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrmhuancard *frmhuancard;
//---------------------------------------------------------------------------
#endif
