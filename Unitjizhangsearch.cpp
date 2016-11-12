//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitjizhangsearch.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "RzDTP"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "frxClass"
#pragma link "frxDBSet"
#pragma resource "*.dfm"
Tfrmsearch *frmsearch;
//---------------------------------------------------------------------------
__fastcall Tfrmsearch::Tfrmsearch(TComponent* Owner)
	: TForm(Owner)
{
}
void Tfrmsearch::init(TADOConnection *Acon,int AStorageID,int AUserID)
{
   fcon = Acon;
   fuserid= AUserID;
   fstorageid=AStorageID;
   aq->Connection = fcon;
    dtpbegin->DateTime = Now();
     dtpend->DateTime = Now();
   DataRead();

}
void Tfrmsearch::DataRead()
{
   AnsiString sql ;
   sql = "select id,kemuname from FN_Kemu";
   TADOQuery *aq=new TADOQuery(Application);
   aq->Connection = fcon;
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->Open();
   for (int i=0; i < aq->RecordCount; i++) {

       cbkemus->Items->AddObject(aq->FieldByName("kemuname")->AsAnsiString,(TObject*)aq->FieldByName("id")->AsInteger);
      aq->Next();
   }

   sql ="select id,name from dbo.SYS_StorageInfo";
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->Open();
    for (int i=0; i < aq->RecordCount; i++) {

       cbstg->Items->AddObject(aq->FieldByName("name")->AsAnsiString,(TObject*)aq->FieldByName("id")->AsInteger);
      aq->Next();
   }


}
//---------------------------------------------------------------------------

void __fastcall Tfrmsearch::SpeedButton1Click(TObject *Sender)
{
//
 AnsiString sql;
 sql = "select convert(varchar(10),a.jizhangdate,120) as jizhangdate,a.department,a.bk,jimoney,kemu,a.id,a.stgid as stgid from dbo.FN_jizhang a " ;
 sql =sql+"  where datediff(d,'"+FormatDateTime("yyyy-mm-dd",dtpbegin->DateTime)+"',jizhangdate)>=0 and  datediff(d,'"+FormatDateTime("yyyy-mm-dd",dtpend->DateTime)+"',jizhangdate)<=0 ";

 if (cbbumen->Checked) {
   sql = sql +" and department ='"+cbstg->Text+"'";
 }
 if (cbkemu->Checked){
     sql = sql +" and kemu ='"+cbkemus->Text+"'"; //IntToStr(int(cbkemus->Items->IndexOfObject((TObject*)cbkemus->ItemIndex)));
 }


 aq->Close();
 aq->SQL->Clear();
 aq->SQL->Add(sql);
 aq->Open();

}
//--------------------------------------------------------------------------
void __fastcall Tfrmsearch::BtnExitClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsearch::frxjizhangGetValue(const UnicodeString VarName, Variant &Value)

{
  	if (CompareText(VarName,"\"title\"")==0 )
        {

          Value=stgname+"非营利性支出";;
        }
        if (CompareText(VarName,"\"searchtime\"")==0 )
        {
          Value=DateToStr(dtpbegin->Date)+" 到　"+DateToStr(dtpend->Date);
        }
        if (CompareText(VarName,"\"operator\"")==0 )
        {

          Value=fusername;
        }
        if (CompareText(VarName,"\"titleshouru\"")==0) {
           Value = "收支";
        }
}
//---------------------------------------------------------------------------
void Tfrmsearch::print(int type)
{

try
{
    if (type==1) {
          AnsiString ps;
            ps = ExtractFilePath(Application->ExeName) +"jizhangsearch.fr3";
            frxjizhang->LoadFromFile(ps);
            frxjizhang->PrepareReport(true);
            frxjizhang->PrintOptions->ShowDialog = false;
            frxjizhang->Print();
            //frxjizhang->ShowPreparedReport();
    } else {

       AnsiString ps;
            ps = ExtractFilePath(Application->ExeName) +"jizhangsearch.fr3";
            frxjizhang->LoadFromFile(ps);
            frxjizhang->PrepareReport(true);
            frxjizhang->PrintOptions->ShowDialog = false;
           // frxWsale->Print();
            frxjizhang->ShowPreparedReport();


    }
    }catch(...)
    {

       MessageBox(0,"打印失败!","先行者软件提示",MB_ICONASTERISK);

    }


}
//---------------------------------------------------------------------------
void __fastcall Tfrmsearch::RzToolButton1Click(TObject *Sender)
{
aq->DisableControls();
print(1);
aq->EnableControls();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsearch::RzToolButton2Click(TObject *Sender)
{
aq->DisableControls();
print(0);
aq->EnableControls();
}
//---------------------------------------------------------------------------
