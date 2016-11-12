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
        sqlbase = "select distinct SYS_InforMessage.*,case sys_inforMessage.type when 1 then '�ڲ�����' when 2 then '��������' when 3 then '��������' end as 'thype' ,SYS_InforMessage.datetime as sendtime,SYS_StorageInfo.name as stgname,sys_user.name as username from SYS_InforMessage "
		" left join sys_user on SYS_InforMessage.stgid = SYS_User.stgid "
		       "	 left join SYS_UserGroup on SYS_UserGroup.userid = SYS_User.id "
		       "	 left join SYS_GroupAction on SYS_GroupAction.groupid = SYS_UserGroup.groupid "
		      "	 left join SYS_Action on SYS_GroupAction.actionid = sys_action.code "
            " left join SYS_StorageInfo on SYS_StorageInfo.id = SYS_InforMessage.stgid "
			" where  ((sys_action.actionname = '��������'  and SYS_InforMessage.type  in(2,3)) "
                 " or ((sys_action.actionname = '��������' or sys_action.actionname = '�ɹ�����' or sys_action.actionname ='��������') and SYS_InforMessage.type = 1)) " ;



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
        if (dataaq->FieldByName("master")->AsBoolean) {   //�ܵ�
                                                //����

            masterstgid=  dataaq->FieldByName("id")->AsInteger;
        }
        if (dataaq->FieldByName("id")->AsInteger==fstgid) {
           indexstg = i;
        }

       i++;
       dataaq->Next();
   }
       cbstorage->ItemIndex = indexstg;
    if (masterstgid==fstgid) {    //����


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


        if(!cbhistory->Checked) //������ʷ��¼
     {
          sql = sqlbase+" and sys_user.id = " + IntToStr(fuserid) + " and SYS_InforMessage.state <> 0 ";

     }else
     {
          //sql = sqlbase+" and sys_user.id = " + IntToStr(fuserid);
     }

     if (cbstg->Checked) {  //ѡ�е��
        if (cbstorage->Enabled) {  //������
         selectstgid= (int)cbstorage->Items->Objects[cbstorage->ItemIndex];

        }else selectstgid=fstgid;

      sql = sql + "  and SYS_InforMessage.stgid = " + IntToStr(selectstgid);

     } else   //��ѡ����
     {

        //sql = sql + "  and SYS_InforMessage.stgid = " + IntToStr(selectstgid);

     }






     if (cbbegin->Checked) {   //��ʼʱ��


           sql = sql+"  and datediff(day,SYS_InforMessage.datetime,'"+btd->Date.FormatString("yyyy-mm-dd")+"')<=0 ";
     }
     if (cbend->Checked) {    //����ʱ��
          sql = sql+"  and datediff(day,SYS_InforMessage.datetime,'"+endtd->Date.FormatString("yyyy-mm-dd")+"')>=0 ";
     }
     if(cbmsg->Checked)   //��Ϣ����
     {
        sql = sql+"  and SYS_InforMessage.Type="+IntToStr(cbmsgtype->ItemIndex+1);
     }
     if(cbmsgcontent->Checked)   //��Ϣ����
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

