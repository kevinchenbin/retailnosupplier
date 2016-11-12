//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitInputmessage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrminputmessage *frminputmessage;
//---------------------------------------------------------------------------
__fastcall Tfrminputmessage::Tfrminputmessage(TComponent* Owner)
	: TForm(Owner)
{
}
void Tfrminputmessage::settitle(AnsiString capt1,AnsiString capt2)
{

      this->Caption = capt1;
      Label1->Caption = capt2;
}
AnsiString Tfrminputmessage::GetInfor()
{
       return meminfor->Text;

}
void Tfrminputmessage::SetDisplayInfo(AnsiString msg)
{
           meminfor->Text = msg;

}
//---------------------------------------------------------------------------void Tfrminputmessage::settitle(AnsiString capt2,AnsiString capt1)

//---------------------------------------------------------------------------
void __fastcall Tfrminputmessage::meminforKeyPress(TObject *Sender, wchar_t &Key)

{
      if (Key == '\r')
	{
            Button1->Click();
            Key=NULL;
        }

}
//---------------------------------------------------------------------------
