//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitInputName.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrminput *frminput;
//---------------------------------------------------------------------------
__fastcall Tfrminput::Tfrminput(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrminput::BitBtn1Click(TObject *Sender)
{
  if (editname->Text=="") {
      ShowMessage("命名不能为空!");
      return;
  }else
  {

    aname=editname->Text;


  }
}
//---------------------------------------------------------------------------
