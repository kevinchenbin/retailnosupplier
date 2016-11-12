//---------------------------------------------------------------------------

#ifndef CoustomerImportH
#define CoustomerImportH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RzButton.hpp"
#include "RzRadChk.hpp"
#include "RzPanel.hpp"
#include <ExtCtrls.hpp>
#include "RzShellDialogs.hpp"
#include <ImgList.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <ComCtrls.hpp>
#include "RzPrgres.hpp"
//---------------------------------------------------------------------------
class TFormCousImport : public TForm
{
__published:	// IDE-managed Components
	TLabel *lblExcel;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnImport;
	TRzToolButton *BtnExit;
	TPanel *Panel1;
	TLabel *Label1;
	TRzGroupBox *RzGroupBox1;
	TRzCheckBox *cbname;
	TRzCheckBox *cbaddress;
	TRzCheckBox *cbcode;
	TRzCheckBox *cbtelphone;
	TRzCheckBox *cbfax;
	TRzCheckBox *cbcontex;
	TRzCheckBox *cbdate;
	TRzCheckBox *chsaleman;
	TRzCheckBox *cbbalance;
	TRzCheckBox *cbarea;
	TRzCheckBox *cballcheck;
	TEdit *edtExcelPath;
	TRzButton *btselectpath;
	TRzOpenDialog *opndlgExcelPath;
	TImageList *ImageList1;
	TADOQuery *qry1;
	TDataSource *ds1;
	TADOQuery *aqdetail;
	TRzToolButton *BtnAlignBottom;
	TADOTable *adotable;
	TADOConnection *con1;
	TRzProgressBar *RzProgressBar1;
	void __fastcall btselectpathClick(TObject *Sender);
	void __fastcall BtnImportClick(TObject *Sender);
	void __fastcall BtnExitClick(TObject *Sender);
	void __fastcall cballcheckClick(TObject *Sender);
	void __fastcall BtnAlignBottomClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
	bool Import;
	int Type;
        int fstgid;
	TADOQuery * dsdg;
public:		// User declarations
	__fastcall TFormCousImport(TComponent* Owner,TADOQuery * query,int type,int stgid);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormCousImport *FormCousImport;
//---------------------------------------------------------------------------
#endif
