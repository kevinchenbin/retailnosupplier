//---------------------------------------------------------------------------

#ifndef StaffdetailH
#define StaffdetailH
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
class TfrmStaffdetail : public TForm
{
__published:	// IDE-managed Components
	TRzToolbar *RzToolbar1;
	TImageList *ImageList1;
	TRzToolButton *BtnSave;
	TRzToolButton *BtnExit;
	TADOQuery *aqinit;
	TADOQuery *aqdetail;
	TADOQuery *qudetail;
	TRzGroupBox *RzGroupBox1;
	TRzLabel *RzLabel2;
	TRzLabel *RzLabel3;
	TRzLabel *RzLabel4;
	TRzLabel *RzLabel8;
	TLabel *Label1;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label10;
	TRzEdit *edName;
	TEdit *edtphone;
	TEdit *edMobile;
	TEdit *edemail;
	TEdit *edqq;
	TEdit *edaddress;
	TComboBox *cbCareer;
	TComboBox *cbSex;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnSaveClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall edaddressKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall cbSexKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edNameKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cbCareerKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtphoneKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edMobileKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edqqKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edemailKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);














private:	// User declarations
	int modsave,fstgid;
	String ID;
public:		// User declarations
	__fastcall TfrmStaffdetail(TComponent* Owner,int savamod,String id,TADOConnection *cnn,int Stgid);
	int ParentID ;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmStaffdetail *frmStaffdetail;
//---------------------------------------------------------------------------
#endif
