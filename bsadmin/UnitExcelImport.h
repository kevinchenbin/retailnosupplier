//---------------------------------------------------------------------------

#ifndef UnitExcelImportH
#define UnitExcelImportH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <ImgList.hpp>
#include <ExtCtrls.hpp>
#include <DBGrids.hpp>

#include "StorageMngForm.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TOpenDialog *opndlgExcelPath;
	TImageList *ImageList1;
	TADOConnection *con1;
	TADOQuery *qry1;
	TEdit *edtExcelPath;
	TLabel *Label1;
	TRzToolbar *RzToolbar1;
	TRzToolButton *BtnImport;
	TRzToolButton *BtnExit;
	TSpeedButton *SpeedButton1;
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall BtnImportClick(TObject *Sender);
private:	// User declarations
char GetPYIndexChar(char *str);
   TADOConnection *fcon;
   TStringList *press;
   int getpressid(AnsiString name);
	AnsiString GetSelf(AnsiString context);
public:		// User declarations
	__fastcall TForm1(TComponent* Owner,TADOConnection *con);
	TfrmStorageMng *st;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
