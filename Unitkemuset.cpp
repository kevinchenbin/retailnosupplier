//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitkemuset.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmkemuset *frmkemuset;
//---------------------------------------------------------------------------
__fastcall Tfrmkemuset::Tfrmkemuset(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrmkemuset::BtnNewClick(TObject *Sender)
{
  //添加
  cbtype->Enabled = true;
  editkemuname->Enabled = true;
  BtnExit->Enabled = true;
  editkemuname->Text = "";
  saveflag=1;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmkemuset::BtnAlignBottomClick(TObject *Sender)
{
 cbtype->Enabled = true;
  editkemuname->Enabled = true;
  BtnExit->Enabled = true;
  saveflag=2 ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmkemuset::BtnExitClick(TObject *Sender)
{
  //保存
  AnsiString sql;
    AnsiString type;
      if (cbtype->ItemIndex == 0) {
          type="1";
         }else type = "2";

      if (saveflag==1) {//添加


        sql = "Insert into FN_kemu (kemuname,type)values('"+editkemuname->Text.Trim()+"',"+type+")";
      }else if (saveflag==2) { //修改
        sql = " update FN_kemu set kemuname='"+editkemuname->Text.Trim()+"',type="+ type + " where id="+aq->FieldByName("id")->AsAnsiString ;
      }



        aq1->Close();
        aq1->SQL->Clear();
        aq1->SQL->Add(sql);
        aq1->ExecSQL();
        MessageBox(0,"保存成功！","先行者软件提醒",MB_ICONWARNING);
        aq->Active = false;
        aq->Active = true;
      saveflag = 0;
      BtnExit->Enabled = false;
      editkemuname->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall Tfrmkemuset::DBGrid1CellClick(TColumn *Column)
{
   editkemuname->Text =   aq->FieldByName("kemuname")->AsAnsiString;
   if (aq->FieldByName("type")->AsInteger == 1) {
      cbtype->ItemIndex = 0;
   }else    cbtype->ItemIndex =1;
}
//---------------------------------------------------------------------------
void Tfrmkemuset::init(TADOConnection *Acon)
 {

        saveflag =0;
         aq->Connection = Acon;
         aq->Active = true;
         aq1->Connection = Acon;
         fcon = Acon;

 }
//---------------------------------------------------------------------------
void __fastcall Tfrmkemuset::RzToolButton1Click(TObject *Sender)
{
//删除

   if((MessageBox(0,"确定要删除吗？","先行者软件提醒",MB_ICONQUESTION|MB_YESNO))==6)
   {
       AnsiString sql;
       TADOQuery *aqdelete = new TADOQuery(Application);
       aqdelete->Connection = fcon;

       sql = "select count(id) as t from FN_jizhang where kemu='"+aq->FieldByName("kemuname")->AsAnsiString+"'";
       aqdelete->Close();
       aqdelete->SQL->Clear();
       aqdelete->SQL->Add(sql);
       aqdelete->Open();
       if (aqdelete->FieldByName("t")->AsInteger==0) {
       sql = "delete FN_kemu where id = "+aq->FieldByName("id")->AsAnsiString;
       aqdelete->Close();
       aqdelete->SQL->Clear();
       aqdelete->SQL->Add(sql);
       aqdelete->ExecSQL();
       aq->Active = false;
       aq->Active = true;
       }else
       {
         MessageBox(0,"该科目有数据关联不能删除!","先行者软件提醒",MB_ICONWARNING);


       }


       delete aqdelete;
   }

}
//---------------------------------------------------------------------------

