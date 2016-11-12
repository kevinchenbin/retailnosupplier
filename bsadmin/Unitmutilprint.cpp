//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitmutilprint.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzDBGrid"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmmembersearch *frmmembersearch;
//---------------------------------------------------------------------------
__fastcall Tfrmmembersearch::Tfrmmembersearch(TComponent* Owner,TADOConnection *con,int stgid)
	: TForm(Owner)
{
        fcn = con;
        fstgid = stgid;
        dtpstart->Date = Date();
	dtpend->Date = Date();
        aqquery->Connection = con;
        TADOQuery *aq = new TADOQuery(this);
	aq->Connection = con;
	AnsiString sql;
	sql = "select id,name from dbo.CUST_MemberInfo where available=1";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();

        while(!aq->Eof)
        {
          cbsupplier->AddItem(aq->FieldByName("name")->AsAnsiString,(TObject*)aq->FieldByName("id")->AsInteger);
          aq->Next();
        }
       delete aq;





}
AnsiString Tfrmmembersearch::Getsql()
{
       return sql;

}

AnsiString Tfrmmembersearch::GetNoteCode()
{

          if (!aqquery->IsEmpty()) {

              return aqquery->FieldByName("notecode")->AsAnsiString ;
          }


}
//---------------------------------------------------------------------------
void __fastcall Tfrmmembersearch::edclientKeyPress(TObject *Sender, wchar_t &Key)

{
 if (Key=='\r') {

      TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcn;
	AnsiString sql;
	sql = "select id,name from dbo.CUST_MemberInfo where available=1 and name like '%"+edclient->Text +"%'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();

        while(!aq->Eof)
        {
          cbsupplier->AddItem(aq->FieldByName("name")->AsAnsiString,(TObject*)aq->FieldByName("id")->AsInteger);
          aq->Next();
        }
        delete aq;


 }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmembersearch::Button1Click(TObject *Sender)
{
              sql="select a.id,a.memberntcode as notecode,convert(nvarchar(10),hdtime,120) as hdtime,c.name as membername,c.CardSN,a.TotalAmount,a.TotalFixedPrice,a.TotalDiscountedprice, ";
              sql = sql +" a.remarks,su.name as username from dbo.BS_MemberOrderHeader a join CUST_MemberInfo c on a.memberid = c.id ";
              sql = sql +" left join sys_user su on a.operatorid = su.id where 1=1 ";
         	if (chstart->Checked ) {
				sqlwhere = sqlwhere + "  and datediff(day,'" + DateToStr(dtpstart->Date) + "',HdTime) >= 0";
			}
			if (chend->Checked ) {
				sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpend->Date) + "',HdTime) <= 0";
			}
			if (chclient->Checked && edclient->Text != "") {
				sqlwhere = sqlwhere + " and c.id ="+IntToStr((int)(cbsupplier->Items->Objects[cbsupplier->ItemIndex]));
			}
			if (chcode->Checked && edcode->Text != "" && encodeend->Text!="") {
				sqlwhere = sqlwhere +" and MemberNtint >= " + edcode->Text+" and MemberNtint <= "+encodeend->Text;
			}
                        sql = sql +sqlwhere+" and a.stgid = "+IntToStr(fstgid);
                        aqquery->Close();
                        aqquery->SQL->Clear();
                        aqquery->SQL->Add(sql);
                        aqquery->Open();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmembersearch::dbgridDblClick(TObject *Sender)
{
	if (aqquery->IsEmpty()) {
		return;
	}
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmembersearch::dtpstartChange(TObject *Sender)
{
   chstart->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmembersearch::dtpendChange(TObject *Sender)
{
    chend->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmembersearch::edclientChange(TObject *Sender)
{
chclient->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmembersearch::edcodeChange(TObject *Sender)
{
 chcode->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmembersearch::Button2Click(TObject *Sender)
{
     	Close();
}
//---------------------------------------------------------------------------

