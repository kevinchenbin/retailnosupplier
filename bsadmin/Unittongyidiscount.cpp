//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unittongyidiscount.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzEdit"
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmtongyidiscount *frmtongyidiscount;
//---------------------------------------------------------------------------
__fastcall Tfrmtongyidiscount::Tfrmtongyidiscount(TComponent* Owner)
	: TForm(Owner)
{
}
float Tfrmtongyidiscount::getdiscount()
{


if (CheckBox1->Checked) {
   return nedit->Value;
} else return -1;




}
AnsiString Tfrmtongyidiscount::getfahuofangshi()
{

if (CheckBox2->Checked) {
   return cbfahuofangshi->Text;
}else return "";



}
//---------------------------------------------------------------------------


