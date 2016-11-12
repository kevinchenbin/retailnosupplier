//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "UnitPublicMsg.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzDBGrid"
#pragma resource "*.dfm"
TfrmpublicMsg *frmpublicMsg;
//---------------------------------------------------------------------------
__fastcall TfrmpublicMsg::TfrmpublicMsg(TComponent* Owner)
	: TForm(Owner)
{
rdb->OnDrawColumnCell=rdbDrawColumnCell;
}
void TfrmpublicMsg::init(TADOConnection *cn,int stgid,int userid)
{
   fcn = cn;
   fstgid = stgid;
   fuserid = userid;
   aq->Connection = fcn;
        sqlbase = "select distinct SYS_InforMessage.*,case sys_inforMessage.type when 1 then '内部订单' when 2 then '申请配送' when 3 then '主动配送' end as 'thype' ,SYS_InforMessage.datetime as sendtime,SYS_StorageInfo.name as stgname,sys_user.name as username from SYS_InforMessage "
		" left join sys_user on SYS_InforMessage.stgid = SYS_User.stgid "
		       "	 left join SYS_UserGroup on SYS_UserGroup.userid = SYS_User.id "
		       "	 left join SYS_GroupAction on SYS_GroupAction.groupid = SYS_UserGroup.groupid "
		      "	 left join SYS_Action on SYS_GroupAction.actionid = sys_action.code "
            " left join SYS_StorageInfo on SYS_StorageInfo.id = SYS_InforMessage.stgid "
			" where  ((sys_action.actionname = '主动配送'  and SYS_InforMessage.type  in(2,3)) "
                 " or ((sys_action.actionname = '订单处理' or sys_action.actionname = '采购处理' or sys_action.actionname ='申请配送') and SYS_InforMessage.type = 1)) " ;



}
void __fastcall TfrmpublicMsg::WndProc(TMessage &Msg)
{
if (Msg.Msg == WM_SYSCOMMAND)
{
if(Msg.WParam == (HTCAPTION | SC_MOVE))
{
Msg.WParam = 0;
}
}
TForm::WndProc(Msg);
}
void TfrmpublicMsg::LoadData()
{
   AnsiString sql;

     sql = sqlbase+" and sys_user.id = " + IntToStr(fuserid) + " and SYS_InforMessage.state <> 0 and SYS_InforMessage.stgid = " + IntToStr(fstgid);
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->Open();



   sql = "select id,name,master from dbo.SYS_StorageInfo";
   TADOQuery *dataaq = new TADOQuery(Application);

   dataaq->Connection =fcn;
   dataaq->Close();
   dataaq->SQL->Clear();
   dataaq->SQL->Add(sql);
   dataaq->Open();
   int indexstg ;
   int masterstgid;
   int i=0;
   while(!dataaq->Eof)
   {

        cbstorage->AddItem(dataaq->FieldByName("name")->AsAnsiString,(TObject*)dataaq->FieldByName("id")->AsInteger);
        if (dataaq->FieldByName("master")->AsBoolean) {   //总店
                                                //主店

            masterstgid=  dataaq->FieldByName("id")->AsInteger;
        }
        if (dataaq->FieldByName("id")->AsInteger==fstgid) {
           indexstg = i;
        }

       i++;
       dataaq->Next();
   }
       cbstorage->ItemIndex = indexstg;
    if (masterstgid==fstgid) {    //主店


        cbstg->Checked = true;


    }else
    {
      cbstorage->Enabled = false;
      cbstg->Checked = true;
      cbstg->Enabled = false;
    }

    delete   dataaq;



}
//---------------------------------------------------------------------------

void __fastcall TfrmpublicMsg::rdbDrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumn *Column, Grids::TGridDrawState State)
{
/*
   if ((Column->FieldName  == "Message")&& (!Column->Field->Value.IsNull())) {
		TRect rc = TRect(10,10,10,10);
	  rdb->Canvas->FillRect(Rect);
	  int x = Rect.Left+(Rect.Right-Rect.Left-32)/2;
		Graphics::TBitmap   *p   =   new   Graphics::TBitmap();
	  ImageList1->GetBitmap(0,p);
	   rc.Right = Rect.Right -234;
	   rc.Left = Rect.left ;
	   rc.Top = Rect.Top ;
	   rc.Bottom = Rect.Bottom ;
	  rdb->Canvas->StretchDraw(rc,p);
	  rdb->Canvas->TextOutA(rc.Left + 20,rc.top ,Column->Field->Value);

  }else
  {
	rdb->DefaultDrawColumnCell(Rect,DataCol,Column,State);
  }      */
}
//---------------------------------------------------------------------------


void __fastcall TfrmpublicMsg::rdbDblClick(TObject *Sender)
{
   if (aq->RecordCount == 0 ) {
       return;
   }
   DanHao = aq->FieldByName("value")->AsAnsiString;
   ID = aq->FieldByName("id")->AsAnsiString ;
   type1 = aq->FieldByName("type")->AsAnsiString ;  // Result = 1;
   MsgType = aq->FieldByName("MsgType")->AsAnsiString ;
   ModalResult = mrOk;
}
//---------------------------------------------------------------------------

void __fastcall TfrmpublicMsg::sbsearchClick(TObject *Sender)
{

    AnsiString sql;
     int selectstgid;


        if(!cbhistory->Checked) //包括历史记录
     {
          sql = sqlbase+" and sys_user.id = " + IntToStr(fuserid) + " and SYS_InforMessage.state <> 0 ";

     }else
     {
          //sql = sqlbase+" and sys_user.id = " + IntToStr(fuserid);
     }

     if (cbstg->Checked) {  //选中店号
        if (cbstorage->Enabled) {  //是主店
         selectstgid= (int)cbstorage->Items->Objects[cbstorage->ItemIndex];

        }else selectstgid=fstgid;

      sql = sql + "  and SYS_InforMessage.stgid = " + IntToStr(selectstgid);

     } else   //不选择店号
     {

        //sql = sql + "  and SYS_InforMessage.stgid = " + IntToStr(selectstgid);

     }






     if (cbbegin->Checked) {   //开始时间


           sql = sql+"  and datediff(day,SYS_InforMessage.datetime,'"+btd->Date.FormatString("yyyy-mm-dd")+"')<=0 ";
     }
     if (cbend->Checked) {    //结束时间
          sql = sql+"  and datediff(day,SYS_InforMessage.datetime,'"+endtd->Date.FormatString("yyyy-mm-dd")+"')>=0 ";
     }
     if(cbmsg->Checked)   //消息类型
     {
        sql = sql+"  and SYS_InforMessage.Type="+IntToStr(cbmsgtype->ItemIndex+1);
     }
     if(cbmsgcontent->Checked)   //消息内容
     {
         sql = sql+"  and SYS_InforMessage.message like '%"+edcontent->Text.Trim()+"%'";

     }

    aq->Close();
    aq->SQL->Clear();
    aq->SQL->Add(sql);
    aq->Open();


}
//---------------------------------------------------------------------------

void __fastcall TfrmpublicMsg::edcontentChange(TObject *Sender)
{
    cbmsgcontent->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmpublicMsg::cbmsgtypeChange(TObject *Sender)
{
     cbmsg->Checked = true;
}
//---------------------------------------------------------------------------

