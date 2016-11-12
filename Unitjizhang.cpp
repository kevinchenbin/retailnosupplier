//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Unitkemuset.h"
#include "Unitjizhang.h"
#include "Addsyslog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzGrids"
#pragma link "RzTabs"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzDTP"
#pragma link "frxClass"
#pragma link "frxCross"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "frxDBSet"
#pragma link "RzDBGrid"
#pragma resource "*.dfm"
Tfrmjizhang *frmjizhang;
//---------------------------------------------------------------------------
__fastcall Tfrmjizhang::Tfrmjizhang(TComponent* Owner)
	: TForm(Owner)
{
}
void Tfrmjizhang::init(TADOConnection *Acon,int AStorageID,int AUserID)
{
      fcon = Acon;
      fstorageid =   AStorageID;
      fuserid = AUserID;
      aq1->Connection = Acon;
      aq2->Connection = Acon;
      aqa->Connection = Acon;
      aqb->Connection = Acon;
     // adotablea->Connection = Acon;
      dtpdate->DateTime = Now();

      DataRead();
      DataRead1();
      DateTotalReade();
}
  void Tfrmjizhang::DataRead()
  {

        AnsiString sql; //收入
         sql = "select id,kemuname from dbo.FN_kemu where type = 1";
            aq1->Close();
            aq1->SQL->Clear();
            aq1->SQL->Add(sql);
            aq1->Open();
            for (int i=0; i < aq1->RecordCount; i++) {
            dg->Columns->Items[0]->PickList->Add(aq1->FieldByName("kemuname")->AsAnsiString);
            aq1->Next();

            }
            //支出
            sql = "select id,kemuname from dbo.FN_kemu where type = 2";
            aq1->Close();
            aq1->SQL->Clear();
            aq1->SQL->Add(sql);
            aq1->Open();
            for (int i=0; i < aq1->RecordCount; i++) {
            dgb->Columns->Items[0]->PickList->Add(aq1->FieldByName("kemuname")->AsAnsiString);
            aq1->Next();

            }




       if (RzPageControl1->ActivePageIndex==0) {


            sql="select * from dbo.FN_jizhang where moneytype=1 and datediff(d,jizhangdate,'"+DateTimeToStr(dtpdate->DateTime)+"')=0";
            aqa->Close();
            aqa->SQL->Clear();
            aqa->SQL->Add(sql);
            aqa->Open();
       }







         return;




  }
  void Tfrmjizhang::DataRead1()
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrmjizhang::BtnNewClick(TObject *Sender)
{
    Tfrmkemuset * frm = new Tfrmkemuset(Application);
    frm->init(fcon);
    frm->ShowModal();
    delete frm;
}
//---------------------------------------------------------------------------
 void Tfrmjizhang::SaveData()
 {

     AnsiString sql,idstr1,idstr2,idstr;
   try
   {
  if ((aqa->State==dsInsert )||(aqa->State==dsEdit)) {

       aqa->Post();
     aqa->DisableControls();
        aqa->First();
      for (int i=0; i < aqa->RecordCount; i++) {
           idstr1 = idstr1+ aqa->FieldByName("id")->AsAnsiString+",";
            aqa->Next();
      }
      aqa->EnableControls();
     sql = "update FN_jizhang set jizhangdate=getdate(),stgid="+IntToStr(fstorageid)+",userid="+IntToStr(fuserid)+",moneytype=1 where ";
     sql =sql+ " id in("+idstr1+"-1)";

  if (idstr==",") {
    return;
  }
    TADOQuery *aq8 = new TADOQuery(Application);
     aq8->Connection = fcon;
    aq8->Close();
    aq8->SQL->Clear();
    aq8->SQL->Add(sql);
    aq8->ExecSQL();
    delete aq8;
   // MessageBox(0,"保存成功!","先行者软件提示",MB_ICONINFORMATION);

  }
    if ((aqb->State==dsInsert )||(aqb->State==dsEdit)) {
    aqb->Post();
    aqb->DisableControls();
       aqb->First();

      for (int i=0; i < aqb->RecordCount; i++) {
            idstr2 = idstr2+ aqb->FieldByName("id")->AsAnsiString+",";
            aqb->Next();
      }
      aqb->EnableControls();
      if (idstr2==",") {
    return;
  }
     sql = "update FN_jizhang set jizhangdate=getdate(),stgid="+IntToStr(fstorageid)+",userid="+IntToStr(fuserid)+",moneytype=2 where ";
     sql =sql+ " id in("+idstr2+"-1)";

    TADOQuery *aq8 = new TADOQuery(Application);
     aq8->Connection = fcon;
    aq8->Close();
    aq8->SQL->Clear();
    aq8->SQL->Add(sql);
    aq8->ExecSQL();
    delete aq8;
// MessageBox(0,"保存成功!","先行者软件提示",MB_ICONINFORMATION);
  }


    }catch(...)
    {
    }




 }
void __fastcall Tfrmjizhang::BtnAlignBottomClick(TObject *Sender)
{
       try
       {
       SaveData();
        MessageBox(0,"保存成功!","先行者软件提示",MB_ICONINFORMATION);

       }catch(...)
       {


       }

}
//---------------------------------------------------------------------------
void Tfrmjizhang::search()
{

    AnsiString sql;
    float totalmoney;
    totalmoney=0;
    if (RzPageControl1->ActivePageIndex==0) {
        sql = "select * from dbo.FN_jizhang where moneytype=1 and datediff(d,jizhangdate,'"+DateTimeToStr(dtpdate->DateTime)+"')=0";
        aqa->Close();
        aqa->SQL->Clear();
        aqa->SQL->Add(sql);
        aqa->Open();
        aqa->DisableControls();

        for (int i=0; i < aqa->RecordCount; i++) {
          totalmoney=totalmoney+aqa->FieldByName("jimoney")->AsFloat;
        aqa->Next();
        }
        aqa->EnableControls();
        editheji->Text = FloatToStr(totalmoney);
    } else
    {
        sql = "select * from dbo.FN_jizhang where moneytype=2 and datediff(d,jizhangdate,'"+DateTimeToStr(dtpdate->DateTime)+"')=0";
        aqb->Close();
        aqb->SQL->Clear();
        aqb->SQL->Add(sql);
        aqb->Open();

           aqb->DisableControls();

        for (int i=0; i < aqb->RecordCount; i++) {
          totalmoney=totalmoney+aqb->FieldByName("jimoney")->AsFloat;
        aqb->Next();
        }
        aqb->EnableControls();

        Edit1->Text = FloatToStr(totalmoney);
    }




}


void __fastcall Tfrmjizhang::sbsearchClick(TObject *Sender)
{
//查询
  // ;
if (FormatDateTime("yyyy-mm-dd",dtpdate->DateTime) !=FormatDateTime("yyyy-mm-dd",Now())) {
 // DataRead();
}
search();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmjizhang::SpeedButton1Click(TObject *Sender)
{
    //

}
void Tfrmjizhang::DateTotalReade()
{


      AnsiString sql,sql1;
     sql="select id,name from dbo.SYS_StorageInfo ";
      TADOQuery *aq0 = new TADOQuery(Application);
   aq0->Connection = fcon ;
   aq0->Close();
   aq0->SQL->Clear();
   aq0->SQL->Add(sql);
   aq0->Open();
   for (int i=0; i < aq0->RecordCount; i++) {
      dg->Columns->Items[2]->PickList->Add(aq0->FieldByName("name")->AsAnsiString);
      dgb->Columns->Items[2]->PickList->Add(aq0->FieldByName("name")->AsAnsiString);
      aq0->Next();
   }
   delete aq0;


}
//---------------------------------------------------------------------------


void __fastcall Tfrmjizhang::RzToolButton1Click(TObject *Sender)
{
//打印
      if (RzPageControl1->ActivePageIndex==0) {
          titleshouru="收入";
          frxdb->DataSet = aqa;



      }else
      {
          titleshouru="支出";
         frxdb->DataSet = aqb;

      }
      print(1);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmjizhang::frxjizhangGetValue(const UnicodeString VarName, Variant &Value)

{
	if (CompareText(VarName,"\"title\"")==0 )
        {

          Value=stgname+"非营利性收支报表";;
        }
        if (CompareText(VarName,"\"searchtime\"")==0 )
        {
          Value=DateToStr(dtpdate->Date);//+" 到　"+DateToStr(dtpend->Date);
        }
        if (CompareText(VarName,"\"operator\"")==0 )
        {

          Value=Ausername;
        }
        if (CompareText(VarName,"\"titleshouru\"")==0) {
           Value = titleshouru;
        }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmjizhang::BtnExitClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmjizhang::FormClose(TObject *Sender, TCloseAction &Action)
{
Action = caFree;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmjizhang::RzPageControl1Change(TObject *Sender)
{
SaveData();
search();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmjizhang::RzToolButton2Click(TObject *Sender)
{
//
    if (RzPageControl1->ActivePageIndex==0) {
          titleshouru="收入";
          frxdb->DataSet = aqa;



      }else
      {
          titleshouru="支出";
         frxdb->DataSet = aqb;

      }
      print(0);
}
void Tfrmjizhang::print(int type)
{

try
{
    if (type==1) {
          AnsiString ps;
            ps = ExtractFilePath(Application->ExeName) +"jizhang.fr3";
            frxjizhang->LoadFromFile(ps);
            frxjizhang->PrepareReport(true);
            frxjizhang->PrintOptions->ShowDialog = false;
            frxjizhang->Print();
            //frxjizhang->ShowPreparedReport();
    } else {

       AnsiString ps;
            ps = ExtractFilePath(Application->ExeName) +"jizhang.fr3";
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





void __fastcall Tfrmjizhang::D1Click(TObject *Sender)
{
aqa->Delete();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall Tfrmjizhang::dgKeyPress(TObject *Sender, wchar_t &Key)
{
if (Key=='\r') {
     dg->Perform(WM_KEYDOWN,0x09,0);
  }
}
//---------------------------------------------------------------------------


void __fastcall Tfrmjizhang::dgbKeyPress(TObject *Sender, wchar_t &Key)
{
if (Key=='\r') {
     dgb->Perform(WM_KEYDOWN,0x09,0);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmjizhang::dgColExit(TObject *Sender)
{
          if (dg->SelectedIndex==1) {
                float totalmoney;
                aqa->DisableControls();

                for (int i=0; i < aqa->RecordCount; i++) {
                totalmoney=totalmoney+aqa->FieldByName("jimoney")->AsFloat;
                aqa->Next();
                }
                aqa->EnableControls();
                editheji->Text = FloatToStr(totalmoney);

          }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmjizhang::dgbColExit(TObject *Sender)
{
      if (dgb->SelectedIndex==1) {
                float totalmoney;
                aqb->DisableControls();

                for (int i=0; i < aqb->RecordCount; i++) {
                totalmoney=totalmoney+aqb->FieldByName("jimoney")->AsFloat;
                aqb->Next();
                }
                aqb->EnableControls();
                Edit1->Text = FloatToStr(totalmoney);

          }
}
//---------------------------------------------------------------------------

