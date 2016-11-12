//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unittuihuoset.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzDBGrid"
#pragma link "RzTabs"
#pragma resource "*.dfm"
Tfrmtuihuoset *frmtuihuoset;
//---------------------------------------------------------------------------
__fastcall Tfrmtuihuoset::Tfrmtuihuoset(TComponent* Owner,TADOConnection* con,int stgid)
	: TForm(Owner)
{
    adotablesupplier->Connection = con;
    adotableclass->Connection = con;
    fcon = con;
    fstgid = stgid;
}
void Tfrmtuihuoset::ReadyData()
{

     	try
	{
		String sql ;
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		sql = "select id,name from dbo.CUST_CustomerInfo where type= 1 and customerstate=1 and stgid="+IntToStr(fstgid);
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
                cbsupplier->Clear();
		while(!aq->Eof)
		{
			cbsupplier->AddItem(aq->FieldByName("name")->AsAnsiString, (TObject*)aq->FieldByName("id")->AsInteger );
			aq->Next();
		}

               	sql = "select id,code,name from BS_BookType ";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
                cbsupplier2->Clear();
		while(!aq->Eof)
		{
			cbsupplier2->AddItem(aq->FieldByName("code")->AsAnsiString+aq->FieldByName("name")->AsAnsiString, (TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		delete aq;
	}catch(...)
	{}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmtuihuoset::editsupplierKeyPress(TObject *Sender, wchar_t &Key)

{
//查询供应商
                        if (Key == '\r') {
                                TADOQuery *aq = new TADOQuery(this);
                                aq->Connection = fcon;
                                AnsiString sql;
                                if (editsupplier->Text != "")
                                {
                                    sql = "select id,name from dbo.CUST_CustomerInfo where type= 1 and customerstate=1 and stgid="+IntToStr(fstgid)+" and name like '%" + editsupplier->Text.Trim() + "%'" ;
                                }
                                else
                                {
                                    sql = "select id,name from dbo.CUST_CustomerInfo where type= 1 and customerstate=1 and stgid="+IntToStr(fstgid);
                                }

                                aq->Close();
                                aq->SQL->Clear();
                                aq->SQL->Add(sql);
                                aq->Open();
                                cbsupplier->Clear();
                                while(!aq->Eof)
                                {
                                    cbsupplier->AddItem(aq->FieldByName("name")->AsAnsiString, (TObject*)aq->FieldByName("ID")->AsInteger );
                                    aq->Next();
                                }
                                if (aq->RecordCount>0) {
                                  cbsupplier->ItemIndex = 0;
                                }
                        }


}
//---------------------------------------------------------------------------

void __fastcall Tfrmtuihuoset::editclassKeyPress(TObject *Sender, wchar_t &Key)
{
           if (Key == '\r') {
                TADOQuery *aq = new TADOQuery(this);
                aq->Connection = fcon;
                AnsiString sql;
                if (editclass->Text != "")
                {
                    sql = "select id,code,name from BS_BookType where code like '%" + editclass->Text.Trim() + "%'" ;
                }
                else
                {
                    sql = "select id,code,name from BS_BookType ";
                }

                aq->Close();
                aq->SQL->Clear();
                aq->SQL->Add(sql);
                aq->Open();
                cbsupplier2->Clear();

                while(!aq->Eof)
                {
                    cbsupplier2->AddItem("["+aq->FieldByName("code")->AsAnsiString+"]"+aq->FieldByName("name")->AsAnsiString, (TObject*)aq->FieldByName("ID")->AsInteger );
                    aq->Next();
                }
                if (aq->RecordCount>0) {
                   cbsupplier2->ItemIndex = 0;
                }
     }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmtuihuoset::SpeedButton1Click(TObject *Sender)
{
  try
  {
 	if (adotablesupplier->State != dsInsert) {
			adotablesupplier->Append();
        }
        adotablesupplier->FieldByName("classtypename")->AsAnsiString ="";
        adotablesupplier->FieldByName("suppliername")->AsAnsiString = cbsupplier->Text;
        adotablesupplier->FieldByName("supplierid")->AsInteger  = (int)(cbsupplier->Items->Objects[cbsupplier->ItemIndex]);;
        adotablesupplier->FieldByName("classtypeid")->AsInteger   = 1;
        adotablesupplier->FieldByName("zhouqi")->AsInteger   = StrToInt(editzhouqi->Text);
        adotablesupplier->FieldByName("type")->AsInteger   = 1; //1.代表供应商
        adotablesupplier->Post();


  }catch(...)
        {}

}
//---------------------------------------------------------------------------

void __fastcall Tfrmtuihuoset::FormShow(TObject *Sender)
{
    ReadyData();
    adotablesupplier->Active = true;
    adotableclass->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmtuihuoset::SpeedButton2Click(TObject *Sender)
{
try
  {
        if (adotableclass->State != dsInsert) {
                adotableclass->Append();
        }
        adotableclass->FieldByName("classtypename")->AsAnsiString =cbsupplier2->Text ;
        adotableclass->FieldByName("suppliername")->AsAnsiString = "";
        adotableclass->FieldByName("supplierid")->AsInteger  =-1;
        adotableclass->FieldByName("classtypeid")->AsInteger = (int)(cbsupplier2->Items->Objects[cbsupplier2->ItemIndex]);;
        adotableclass->FieldByName("zhouqi")->AsInteger   = StrToInt(editzhouqi2->Text);
        adotableclass->FieldByName("type")->AsInteger   = 2; //1.代表类别
        adotableclass->Post();
  }catch(...)
  {}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmtuihuoset::RzDBGrid1CellClick(TColumn *Column)
{
  //
  editzhouqi->Text =  adotablesupplier->FieldByName("zhouqi")->AsAnsiString ;
  cbsupplier->Text = adotablesupplier->FieldByName("suppliername")->AsAnsiString ;

}
//---------------------------------------------------------------------------

void __fastcall Tfrmtuihuoset::RzDBGrid2CellClick(TColumn *Column)
{
     editzhouqi2->Text =  adotableclass->FieldByName("zhouqi")->AsAnsiString ;
     cbsupplier2->Text = adotableclass->FieldByName("classtypename")->AsAnsiString ;

}
//---------------------------------------------------------------------------

void __fastcall Tfrmtuihuoset::N1Click(TObject *Sender)
{
//
try
  {
    if (adotablesupplier->State != dsEdit)
    {
          adotablesupplier->Edit();
          adotablesupplier->Delete();

    }
}catch(...)
{}

}
//---------------------------------------------------------------------------

void __fastcall Tfrmtuihuoset::D1Click(TObject *Sender)
{
try
  {
    if (adotableclass->State != dsEdit)
    {
            adotableclass->Edit();
            adotableclass->Delete();

    }
}catch(...)
{}
}
//---------------------------------------------------------------------------

