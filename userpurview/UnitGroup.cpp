//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitGroup.h"
#include "UnitNewGroup.h"
#include "Addsyslog.h"
#include "global.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "RzDBGrid"
#pragma resource "*.dfm"
Tfrmgroup *frmgroup;
//---------------------------------------------------------------------------
__fastcall Tfrmgroup::Tfrmgroup(TComponent* Owner,TADOConnection *cn,int stgid,int sid)
	: TForm(Owner)
{
dg->OnDrawColumnCell=dgDrawColumnCell;
  fcon = cn;
  aqgroup->Connection = cn;
  fstgid = stgid;
  userid = sid;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmgroup::BtnNewClick(TObject *Sender)
{
   Tfrmnewgroup * frm = new Tfrmnewgroup(Application,fcon,fstgid);
   frm->userid = userid;
  if (mbOK ==  frm->ShowModal())
  {
	frm->listviewuser->Items->Clear();
  }
   delete frm;
   aqgroup->Active = false;
   aqgroup->Active = true;
}
void Tfrmgroup::ReadyData()
{
   String sql;
   sql = "select id,groupname,stgid,bk,CONVERT(varchar(12) , createdatetime, 111 ) as createdatetime from sys_group where stgid = " + IntToStr(fstgid);
   aqgroup->Close();
   aqgroup->SQL->Clear();
   aqgroup->SQL->Add(sql);
   aqgroup->Open();



}
//---------------------------------------------------------------------------

void __fastcall Tfrmgroup::FormShow(TObject *Sender)
{
ReadyData();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmgroup::N3Click(TObject *Sender)
{
 Tfrmnewgroup * frm = new Tfrmnewgroup(Application,fcon,fstgid);
  frm->Type = 2;
  frm->GroupID = aqgroup->FieldByName("ID")->AsInteger ;
  frm->editgroupname->Text = aqgroup->FieldByName("Groupname")->AsAnsiString ;
  frm->editdescript->Text = aqgroup->FieldByName("bk")->AsAnsiString ;
  frm->ReadyGroupData(aqgroup->FieldByName("ID")->AsInteger);
  if (mbOK ==  frm->ShowModal())
  {
	frm->listviewuser->Items->Clear();
  }
   delete frm;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmgroup::dgDrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumn *Column, Grids::TGridDrawState State)
{
  if (Column->FieldName  == "groupname") {
		TRect rc = TRect(10,10,10,10);
	   //TRect MyRect = Rect(10,10,100,100);
				  //		  Rectangle(rc,0,0,0,0) ;
	  dg->Canvas->FillRect(Rect);
	  int x = Rect.Left+(Rect.Right-Rect.Left-32)/2;
		Graphics::TBitmap   *p   =   new   Graphics::TBitmap();
	  ImageList1->GetBitmap(6,p);
	 // dg->Canvas->Draw(Rect.Left,Rect.top + 1,p);
	   rc.Right = Rect.Right -84;
	   rc.Left = Rect.left ;
	   rc.Top = Rect.Top ;
	   rc.Bottom = Rect.Bottom ;
	  dg->Canvas->StretchDraw(rc,p);
	  dg->Canvas->TextOutA(rc.Left + 20,rc.top ,Column->Field->Value);

  }else
  {
	dg->DefaultDrawColumnCell(Rect,DataCol,Column,State);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmgroup::FormClose(TObject *Sender, TCloseAction &Action)
{
  Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmgroup::BtnDeleteClick(TObject *Sender)
{
   if (aqgroup->FieldByName("groupname")->AsAnsiString  == "系统管理员" ) {
	   ShowMsg(this->Handle,"系统管理组不能删除！",0);
	   return;
   }
   if (ShowMsg(this->Handle,"确认要删除该组吗？",1) == 1) {
	  String sql;
	  sql = "select count(*) as t from sys_usergroup where GroupID =" + IntToStr(aqgroup->FieldByName("ID")->AsInteger) + " and userid >= 0" ;
	  TADOQuery *aq = new TADOQuery(Application);
	  aq->Connection = fcon ;
	  aq->Close();
	  aq->SQL->Clear();
	  aq->SQL->Add(sql);
	  aq->Open();
	  if (aq->FieldByName("t")->AsInteger > 0 ) {
		  ShowMsg(this->Handle,"该组还有成员，不能删除！",0);
		  delete aq;
		  return;
	  }
	  sql = "delete sys_group where ID = " + IntToStr(aqgroup->FieldByName("ID")->AsInteger);
	  aq->Close();
	  aq->SQL->Clear();
	  aq->SQL->Add(sql);
	  aq->ExecSQL();
	  logmessage = "删除角色" + aqgroup->FieldByName("groupname")->AsAnsiString;
	  AddEvent(1,"角色管理窗口",userid,fstgid,logmessage,fcon);
	  delete aq;
	  aqgroup->Active = false;
	  aqgroup->Active = true;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmgroup::dgDblClick(TObject *Sender)
{
  	N3->Click();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmgroup::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmgroup::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmgroup::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F2) {     //添单
		BtnNew->Click();
	}
	if (Key == VK_F5) {     //删除
		BtnDelete->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmgroup::N1Click(TObject *Sender)
{
//
BtnNew->Click();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmgroup::N2Click(TObject *Sender)
{
BtnDelete->Click();
}
//---------------------------------------------------------------------------

