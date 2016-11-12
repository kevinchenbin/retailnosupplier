//---------------------------------------------------------------------------

#ifndef MemberCardH
#define MemberCardH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <DB.hpp>
#include <DBTables.hpp>
#include <ADODB.hpp>
#include "RzCmboBx.hpp"
#include "global.h"
//---------------------------------------------------------------------------
class TfrmMemberCard : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageListMemcard;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnExit;
	TADOQuery *quMemberType;
	TADOCommand *ADOCommand1;
	TADOQuery *quMemberCard;
	TADOQuery *quMemberInfo;
	TGroupBox *GroupBox1;
	TLabel *membername;
	TLabel *membercardid;
	TLabel *membersex;
	TLabel *memberbirthday;
	TLabel *membertype;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *membertelephone;
	TLabel *membermobile;
	TLabel *memberaddress;
	TLabel *Label4;
	TEdit *edtname;
	TEdit *edtcardID;
	TEdit *edtdiscount;
	TDateTimePicker *tdtbirthday;
	TEdit *edCardCast;
	TEdit *edpassword;
	TRadioGroup *rg;
	TEdit *edityouxiao;
	TComboBox *cbtype;
	TComboBox *cbsex;
	TDateTimePicker *dtpyouxiao;
	TEdit *edttelephone;
	TEdit *edtmobile;
	TEdit *edtaddress;
	TEdit *edbircard;
	TEdit *edtpostalcode;
	TLabel *Label7;
	TLabel *Label8;
	TEdit *editjifen;


	void __fastcall edtnameChange(TObject *Sender);
	void __fastcall edtcardIDChange(TObject *Sender);
	void __fastcall edtsexChange(TObject *Sender);
	void __fastcall edttelephoneChange(TObject *Sender);
	void __fastcall edtmobileChange(TObject *Sender);
	void __fastcall edtaddressChange(TObject *Sender);
	void __fastcall edtpostalcodeChange(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall edtdiscountChange(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall edtnameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edtcardIDKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edttelephoneKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edtpostalcodeKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edCardCastKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edpasswordKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edbircardKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edityouxiaoExit(TObject *Sender);
	void __fastcall rgClick(TObject *Sender);
	void __fastcall edCardCastKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbtypeKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall cbtypeSelect(TObject *Sender);
	void __fastcall ComboBox1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edtaddressKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edtdiscountKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall tdtbirthdayKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall dtpyouxiaoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtmobileKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtpostalcodeKeyPress(TObject *Sender, wchar_t &Key);















private:	// User declarations
	AnsiString name,sex,type,birthday,telephone,mobile,address,postalcode,discount;
	int m_modle,memtype,memsex;
	String *ASMemInfo;


public:		// User declarations
	__fastcall TfrmMemberCard(TComponent* Owner,int modle,String *ASMemberInfo,TADOConnection *cn);
        AnsiString cardID;
        bool savebt;
        int stgid;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMemberCard *frmMemberCard;
//---------------------------------------------------------------------------
#endif
