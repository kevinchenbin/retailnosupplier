//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitDataClear.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::cbpxChange(TObject *Sender)
{
  if (cbpx->ItemIndex==0) {

  }else if (cbpx->ItemIndex==1) {

        }
}
//---------------------------------------------------------------------------
