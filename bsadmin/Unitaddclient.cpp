//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitaddclient.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrmaddclient *frmaddclient;
//---------------------------------------------------------------------------
__fastcall Tfrmaddclient::Tfrmaddclient(TComponent* Owner,TADOConnection *con,int stgid)
	: TForm(Owner)
{

    	AnsiString sql;
	sql = "select ID,Name from CUST_CustomerInfo where type = 2 and customerstate =1 and stgid="+IntToStr(stgid);
        aq->Connection = con;
        fcon= con;
        fstgid = stgid;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{        if (aq->FieldByName("Name")->AsAnsiString!="普通客户" )
                {
		cbclient->AddItem(aq->FieldByName("Name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );

                }
        	aq->Next();
	}
	aq->First();
	cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );

}
//---------------------------------------------------------------------------
void __fastcall Tfrmaddclient::edclientKeyPress(TObject *Sender, wchar_t &Key)
{
    //
    	if (Key == '\r') {

		AnsiString sql;
		sql = "select ID,Name from CUST_CustomerInfo where type = 2 and stgid = "+IntToStr(fstgid)+" and customerstate =1 and Name like '%" + edclient->Text + "%'";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
        cbclient->Clear();
		while (!aq->Eof )
		{       if (aq->FieldByName("Name")->AsAnsiString!="普通客户" ) {
                                cbclient->AddItem(aq->FieldByName("Name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );

                        }  aq->Next();

		}
		aq->First();
		cbclient->ItemIndex =0;// cbclient->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );

                cbclient->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmaddclient::cbclientKeyPress(TObject *Sender, wchar_t &Key)
{
    	if (Key == '\r') {
            Button1->Click();
        }
}
int Tfrmaddclient::getselectclient()
{
        int clientid;

        try
        {
          clientid= (int)cbclient->Items->Objects[cbclient->ItemIndex];

        }catch(...)
        {
          clientid=-1;
        }
        return clientid;

}
//---------------------------------------------------------------------------
