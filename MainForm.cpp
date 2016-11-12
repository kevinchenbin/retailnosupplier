//---------------------------------------------------------------------------
#ifdef USE_VCLDB
#define INC_VCLDB_HEADERS
#endif

#ifdef USE_VCLEXT
#define INC_VCLEXT_HEADERS
#endif

#ifdef USE_OLE
#define INC_OLE_HEADERS
#endif

#ifdef USE_ATL
#define INC_ATL_HEADERS
#endif

#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
#include "LandForm.h"
#include "global.h"
#include "pdtypes.h"
#include "bsadmin\bsadmin.h"
#include "shlwapi.h"
#include "tchar.h"
#include "PwdForm.h"
#include "Print.h"
#include "bsquery\bsquery.h"
#include "Unitestartsupclient.h"
#include "Unitwanglai.h"
#include "accoutnsdue.h"
#include "accountdetail.h"
#include "accountquery.h"
#include "Unitbalance.h"
#include "suppmanage.h"
#include "Staffmanage.h"
#include "MemberForm.h"
#include "MemberResult.h"
#include "RecordQuery.h"
#include "StockalarmSet.h"
#include "localadjust.h"
#include "StockCheck.h"
#include "Stockalarm.h"
#include "sysadmin\sysadmin.h"
#include "systemset.h"
#include "unitprinttitle.h"
#include "UnitLog.h"
#include "retailbsset.h"
#include "orderbsset.h"
#include "storagebsset.h"
#include "salebsset.h"
#include "procureset.h"
#include "stockalarmbsset.h"
#include "diaoboset.h"
#include "catalogadmin\catalogadmin.h"
#include "AreaSet.h"
#include "MemberClassSet.h"
#include "storagelocal.h"
#include "CustomertypeSet.h"
#include "UnitStorToStor.h"
#include "UnitpurviewManage.h"
#include "UnitGroup.h"
#include "SpecialPasswordForm.h"
#include "Unituser.h"
#include "Moneydiscount.h"
#include "MemberJifenMng.h"
#include "ClientBackdot.h"
#include "marketadmin\marketadmin.h"
#include "dataanalysis\dataanalysis.h"
#include "Unitsiglebook.h"
#include "Unitshengji.h"
#include "Unitabout.h"
#include "UnitPublicMsg.h"
#include "Unitaccountyfhz.h"
#include "Unitclientwanglai.h"
#include "UnitTaskManage.h"
#include "Document\Unitdocument.h"
#include "clientadddot.h"
#include "Unitjizhang.h"
#include "ClientDisforbook.h"
 #include "Unitjizhangsearch.h"
#include "Teacher\Uniteachermanager.h"
#include <vcl/Clipbrd.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "IWBaseControl"
#pragma link "IWBaseHTMLControl"
#pragma link "IWControl"
#pragma link "IWExtCtrls"
#pragma link "IWVCLBaseControl"
#pragma link "RzStatus"
#pragma resource "*.dfm"
#pragma resource "pdrs.RES"
#pragma resource "pdres.RES"
#include "TeacherFD.h"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
	: TForm(Owner)
{
	OriginalClientWndProc = 0;
	jiaojie = 0;
	NewClientWndProc = (FARPROC)MakeObjectInstance(ClientWndProc);
	OriginalClientWndProc=reinterpret_cast<void*>(SetWindowLong(ClientHandle ,GWL_WNDPROC,reinterpret_cast<LONG>(NewClientWndProc)));
    frmLand = new TfrmLand(Application);
	if (frmLand->ShowModal() != mrOk)
	{
		Application->Terminate();
		Application->ProcessMessages();
	}
        Acon = new TADOConnection(Application);
	AUserID = frmLand->GetUserID();
	AStorageName = frmLand->cbstorage->Text;
	AStorageID = frmLand->GetStorageID();
	AUserName = frmLand->GetUserNameA();
	AMaster =  frmLand->GetMaster();
        this->Caption =this->Caption +frmLand->softversion;
             Acon->LoginPrompt = false;
           Acon->KeepConnection = true;
        try
        {
           Acon->ConnectionString =  frmLand->conLand->ConnectionString;
           Acon->Connected = true;

        }
        catch(Exception &E)
        {
              ShowMsg(Handle,E.Message,3);
        }
        delete frmLand;

       	pancg->Parent = NULL;
      	pancg->ParentWindow = this->ClientHandle ;

	panps->Parent = NULL;
	panps->ParentWindow = this->ClientHandle ;

	panfh->Parent = NULL;
	panfh->ParentWindow = this->ClientHandle ;

	panls->Parent = NULL;
	panls->ParentWindow = this->ClientHandle ;

	pankc->Parent = NULL;
	pankc->ParentWindow = this->ClientHandle ;

	pankh->Parent = NULL;
	pankh->ParentWindow = this->ClientHandle ;

	pancx->Parent = NULL;
	pancx->ParentWindow = this->ClientHandle ;

	pancw->Parent = NULL;
	pancw->ParentWindow = this->ClientHandle ;

	Panel2->Parent = NULL;
	Panel2->ParentWindow = this->ClientHandle ;

	Panel1->Parent = NULL;
	Panel1->ParentWindow = this->ClientHandle ;

	tag = -1;
        TPngImage * imag;
	imag = new TPngImage();
	imag->LoadFromResourceName((unsigned int)HInstance,"ditu1");
	imageui->Picture->Graphic = imag;
      //  imageui->Picture->SaveToFile("D:\\pic\\ditu1.jpg");

	imag = new TPngImage();
	imag->LoadFromResourceName((unsigned int)HInstance,"logo");
	Image2->Picture->Graphic = imag;

        //Image2->Picture->SaveToFile("D:\\pic\\logo.jpg");

	imag = new TPngImage();
	imag->LoadFromResourceName((unsigned int)HInstance,"ditu2");
	imagebj->Picture->Graphic = imag;

       // imagebj->Picture->SaveToFile("D:\\pic\\ditu2.jpg");

	imag = new TPngImage();
        imag->LoadFromResourceName((unsigned int)HInstance,"caigoulin1");
	Image6->Picture->Graphic = imag;

       //     Image6->Picture->SaveToFile("D:\\pic\\caigoulin1.jpg");

	imag = new TPngImage();
        imag->LoadFromResourceName((unsigned int)HInstance,"caigoulin3");
	Image5->Picture->Graphic = imag;
       // Image5->Picture->SaveToFile("D:\\pic\\caigoulin3.jpg");

	imag = new TPngImage();
	imag->LoadFromResourceName((unsigned int)HInstance,"sms");
	Image8->Picture->Graphic = imag;
        //Image8->Picture->SaveToFile("D:\\pic\\sms.jpg");

	imag = new TPngImage();
	imag->LoadFromResourceName((unsigned int)HInstance,"jiaoliu");
	Image9->Picture->Graphic = imag;
        //Image9->Picture->SaveToFile("D:\\pic\\jiaoliu.jpg");

	imag = new TPngImage();
	imag->LoadFromResourceName((unsigned int)HInstance,"task");
	Image10->Picture->Graphic = imag;
       // Image10->Picture->SaveToFile("D:\\pic\\task.jpg");

	imag = new TPngImage();
	imag->LoadFromResourceName((unsigned int)HInstance,"document");
	Image11->Picture->Graphic = imag;
       // Image11->Picture->SaveToFile("D:\\pic\\document.jpg");

	imag = new TPngImage();
	imag->LoadFromResourceName((unsigned int)HInstance,"caigoulin2");
	Image7->Picture->Graphic = imag;


	imag = new TPngImage();
	imag->LoadFromResourceName((unsigned int)HInstance,"caigoulin2");
	Image4->Picture->Graphic = imag;

      //  Image4->Picture->SaveToFile("D:\\pic\\caigoulin2.jpg");
       //////////////////////////////////////////////////////////////////////
	imag = new TPngImage();
	imag->LoadFromResourceName((unsigned int)HInstance,"caigoulin3");
	Image1->Picture->Graphic = imag;

      //  Image1->Picture->SaveToFile("D:\\pic\\caigoulin3.jpg");
      //	imag = new TPngImage();
      //	imag->LoadFromResourceName((unsigned int)HInstance,"caigoulin1");
     //	Image3->Picture->Graphic = imag;

        imag = new TPngImage();
	imag->LoadFromResourceName((unsigned int)HInstance,"line4");
	Image12->Picture->Graphic = imag;

        imag = new TPngImage();
	imag->LoadFromResourceName((unsigned int)HInstance,"line4");
	Image13->Picture->Graphic = imag;

           imag = new TPngImage();
	imag->LoadFromResourceName((unsigned int)HInstance,"caigoulin1");
	Image14->Picture->Graphic = imag;



        imag = new TPngImage();
	imag->LoadFromResourceName((unsigned int)HInstance,"caigoulin1");
	Image15->Picture->Graphic = imag;

       // Image15->Picture->SaveToFile("D:\\pic\\caigoulin1.jpg");

	lbtitle->Caption  = GetTitle();
       // sptitle->Caption = lbtitle->Caption;
        Label1->Transparent = true;
        Label2->Transparent = true;
        Label3->Transparent = true;
        Label4->Transparent = true;
      //  Timer1->Enabled = true;
        stgname->Transparent = true;
        lbversion->Transparent = true;

       // this->WindowProc = myproc;
 }
void __fastcall TfrmMain::ToolBarShowOrNot(TMessage &msg)
{
            if (msg.WParam==1) {
               MainToolBar->Visible = true;
            }else MainToolBar->Visible = false;



}
void TfrmMain::DisVisable()
{
    SendMessage(Handle,WM_MYMESSAGE,0,0);

}
void __fastcall TfrmMain::MainClose(TMessage &msg)
{
    if (Handle==NULL) {
             return;
    }
    if(EnumChildWindows(Handle,(WNDENUMPROC)EnumChildWin,2))
     {
           this->Dispatch(&msg);

     }else             //有子窗体
     {
        if (msg.Msg != WM_CLOSE){
            this->Dispatch(&msg);
         }
      }


}



void __fastcall TfrmMain::imageuiMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	/*if(Button == mbLeft)
	{
		ReleaseCapture();
		SendMessage( Handle, WM_NCLBUTTONDOWN, HTCAPTION, 0);
	}  */
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::ClientWndProc(TMessage&   Message)
{
	 //不显示滚动条
	ShowScrollBar(frmMain->ClientHandle,SB_BOTH,false);
	//   Then   call   the   original   WndProc()   for   the   other   messages
	if(OriginalClientWndProc   !=   0)
	{
		Message.Result
		=   CallWindowProc(reinterpret_cast<FARPROC>(OriginalClientWndProc),
			ClientHandle,
			Message.Msg,
			Message.WParam,
			Message.LParam);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::SpeedButton1Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------


void TfrmMain::TPclick(int tt)
{
	if (tag == tt) {
		return;
	}
	if (tag == -1) {
		imagebj->Visible = true;
		imageui->Visible = false;
	}
	if (tag == 1) {
		pancg->Visible = false;
		tbcg->ImageIndex = tbcg->ImageIndex -1;
	}
	if (tag == 2) {
		panps->Visible = false;
		tbps->ImageIndex = tbps->ImageIndex -1;
	}
	if (tag == 3) {
		panfh->Visible = false;
		tbfh->ImageIndex = tbfh->ImageIndex -1;
	}
	if (tag == 4) {
		panls->Visible = false;
		tbls->ImageIndex = tbls->ImageIndex -1;
	}
	if (tag == 5) {
		pankc->Visible = false;
		tbkc->ImageIndex = tbkc->ImageIndex -1;
	}
	if (tag == 6) {
		pankh->Visible = false;
		tbkh->ImageIndex = tbkh->ImageIndex -1;
	}
	if (tag == 7) {
		pancx->Visible = false;
		tbcx->ImageIndex = tbcx->ImageIndex -1;
	}
	if (tag == 8) {
		pancw->Visible = false;
		tbcw->ImageIndex = 15;
	}

	if (tt == 1) {
		pancg->Visible = true;
		tbcg->ImageIndex = tbcg->ImageIndex + 1;
	}
	if (tt == 2) {
		panps->Visible = true;
		tbps->ImageIndex = tbps->ImageIndex + 1;
	}
	if (tt == 3) {
		panfh->Visible = true;
		tbfh->ImageIndex = tbfh->ImageIndex + 1;
	}
	if (tt == 4) {
		panls->Visible = true;
		tbls->ImageIndex = tbls->ImageIndex + 1;
	}
	if (tt == 5) {
		pankc->Visible = true;
		tbkc->ImageIndex = tbkc->ImageIndex + 1;
	}
	if (tt == 6) {
		pankh->Visible = true;
		tbkh->ImageIndex = tbkh->ImageIndex + 1;
	}
	if (tt == 7) {
		pancx->Visible = true;
		tbcx->ImageIndex = tbcx->ImageIndex + 1;
	}
	if (tt == 8) {
		pancw->Visible = true;
		tbcw->ImageIndex = 0;
	}
	tag = tt;
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::imagecg1Click(TObject *Sender)
{
	TPclick(1);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::imagecw1Click(TObject *Sender)
{
	TPclick(8);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::imagecx1Click(TObject *Sender)
{
	TPclick(7);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::imageps1Click(TObject *Sender)
{
	TPclick(2);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::imagefh1Click(TObject *Sender)
{
	TPclick(3);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::imagels1Click(TObject *Sender)
{
	TPclick(4);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::imagekc1Click(TObject *Sender)
{
	TPclick(5);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::imagekh1Click(TObject *Sender)
{
	TPclick(6);
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::tbcgClick(TObject *Sender)
{
	TPclick(1);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::tbpsClick(TObject *Sender)
{
	TPclick(2);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::tbfhClick(TObject *Sender)
{
	TPclick(3);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::tblsClick(TObject *Sender)
{
	TPclick(4);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::tbkcClick(TObject *Sender)
{
	TPclick(5);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::tbkhClick(TObject *Sender)
{
	TPclick(6);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::tbcxClick(TObject *Sender)
{
	TPclick(7);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::tbcwClick(TObject *Sender)
{
	TPclick(8);
}
//---------------------------------------------------------------------------

BOOL TfrmMain::CheckPower(String ModalName)
{
	int i = PowerList->IndexOf(ModalName);
	if (i<0) {
		return false;
	}else
	{
		return true;
	}
}

//---------------------------------------------------------------------------
void TfrmMain::ShowNoPower()
{
	MessageBoxA(0,"无权限操作此模块,请与管理员联系!","警告",MB_ICONASTERISK);
}

//---------------------------------------------------------------------------
void TfrmMain::GetPowerList(int UserID)
{
	String sql;
	sql = "select D.ActionName from sys_usergroup A join SYS_group B On A.GroupID = B.ID "
		 " join SYS_GroupAction C on B.ID = C.GroupID "
		 " join sys_action D on C.ActionID = D.Code "
		 " where A.UserID  =" + IntToStr(UserID);
	PowerList = new TStringList();

	TADOQuery *aq = new TADOQuery(Application);
	aq->Connection = Acon ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while(!aq->Eof)
	{
		PowerList->AddObject(aq->FieldByName("ActionName")->AsAnsiString.Trim() ,(TObject*)1);
		aq->Next();
	}
	delete aq;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormShow(TObject *Sender)
{
	GetPowerList(AUserID);
	AnsiString sname = "您现在登录的是:" + AStorageName ;
	stgname->Caption = sname;

        //加载MSg

        MessageInfo = new TStringList();
        MessageInfo->AddObject("msg1",msg1);
        MessageInfo->AddObject("msg2",msg2);
        MessageInfo->AddObject("msg3",msg3);
        MessageInfo->AddObject("msg4",msg4);
        MessageInfo->AddObject("msg5",msg5);
        MessageInfo->AddObject("msg6",msg6);
        MessagePic = new TStringList();
        MessagePic->AddObject("g1",g1) ;
        MessagePic->AddObject("g2",g2) ;
        MessagePic->AddObject("g3",g3) ;
        MessagePic->AddObject("g4",g4) ;
        MessagePic->AddObject("g5",g5) ;
        MessagePic->AddObject("g6",g6) ;
        LoadMyMessage();
        Timer1->Enabled = true;
        InitDiffVersion();
        InitQF();//是否区分供应商
}
void TfrmMain::LoadMyMessage()
{
  AnsiString sql;
  AnsiString MsgName,MsgPic;
  int j,k,l,p;
  int recordcount;


   //all msg visible = false;
  for (int i = 0; i < MessageInfo->Count ; i++) {
		TLabel * MsgLabel = (TLabel *)MessageInfo->Objects[i];
		MsgLabel->Visible  = false;
		TRzGlyphStatus * MsgImage = (TRzGlyphStatus *)MessagePic->Objects[i];
		MsgImage->Visible = false;
  }
   sql = "select distinct top 7 SYS_InforMessage.* from SYS_InforMessage left join sys_user on SYS_InforMessage.stgid = SYS_User.stgid "
			" left join SYS_UserGroup on SYS_UserGroup.userid = SYS_User.id "
			" left join SYS_GroupAction on SYS_GroupAction.groupid = SYS_UserGroup.groupid "
			" left join SYS_Action on SYS_GroupAction.actionid = sys_action.code "
			" where  ((sys_action.actionname = '主动配送'  and SYS_InforMessage.type  in(2,3)) "
			" or ((sys_action.actionname = '订单处理' or sys_action.actionname = '采购处理' or sys_action.actionname ='申请配送') and SYS_InforMessage.type = 1)) "
			" and sys_user.id = " + IntToStr(AUserID) + " and SYS_InforMessage.state <> 0 and SYS_InforMessage.stgid = " + IntToStr(AStorageID);

   TADOQuery *aq = new TADOQuery(NULL);
   aq->Connection =  Acon;
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->Open();
   if (aq->RecordCount > 6) {
       recordcount = 6;
       lbmore->Visible = true;
       lbmore->Transparent = true;
   }else
   {
       recordcount = aq->RecordCount;
   }
   for (int i =0 ; i < recordcount ; i++)
   {
		MsgName = "msg" + IntToStr(i+1);
		MsgPic = "g" + IntToStr(i+1);
		j = MessageInfo->IndexOf(MsgName);    //取出要显示的panel
		TLabel * MsgLabel = (TLabel *)MessageInfo->Objects[j];
		MsgLabel->Visible  = true;
		MsgLabel->Caption = aq->FieldByName("Message")->AsAnsiString ;
		MsgLabel->Hint = aq->FieldByName("value")->AsAnsiString;
		MsgLabel->Tag = aq->FieldByName("type")->AsInteger ;
		MsgLabel->HelpContext =aq->FieldByName("id")->AsInteger ;
                MsgLabel->HelpKeyword = aq->FieldByName("MsgType")->AsAnsiString;
                MsgLabel->Transparent = true;
		k = MessagePic->IndexOf(MsgPic);
		TRzGlyphStatus * MsgImage = (TRzGlyphStatus *)MessagePic->Objects[j];
                MsgImage->Transparent = true;
		MsgImage->Visible = true;

	 	aq->Next();
   }

   delete aq;
}
//---------------------------------------------------------------------------

BOOL CALLBACK EnumChildWin(HWND hwndChild,LPARAM lParam)
{
  char nClass[20];
  char lsname[5];
  char *enumClass = "Tfrm";
  GetClassName(hwndChild, nClass, 20);
  lsname[0]= nClass[0];
  lsname[1]= nClass[1];
  lsname[2]= nClass[2];
  lsname[3]= nClass[3];
  lsname[4] ='\0';

      if(!strcmp(lsname, enumClass)) // 类名称是否匹配
      {
        return false;
      }

  return true;


}
void __fastcall TfrmMain::FormClose(TObject *Sender, TCloseAction &Action)
{

          if( EnumChildWindows(Handle,(WNDENUMPROC)EnumChildWin,2))
          {
               Action = caFree;
          }else
          {

            Action = caNone;
          /*  if(ShowMsg(Handle ,"有未关闭窗口，是否退出？,确认将关闭整个系统！",1)==1)
		{
                        Action = caFree;
		}
		else
		{
			Action = caNone;
			return;
		} */

          }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ProcureExecute(TObject *Sender)
{
	//采购管理
    if (!FindDog(version)) {
        return;
	}



            if (CheckPower("非省代采购") ) {
            LandInfo li;
            li.app = Application;
            li.con = Acon;
            li.userID = AUserID;
            li.storageID = AStorageID;
            li.UserName = AUserName;
            li.FormatStr = "#,##0.00";
             li.qfsupply= Qfsupplier;
        li.qfclient = Qfclient;
            ProcureManage(&li,frmMain->ClientHandle);
            DisVisable();  //不显示主菜单
            }else
            {
               ShowNoPower();
            }


}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::storageExecute(TObject *Sender)
{
	//入库管理
    if (!FindDog(version)) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = Acon;
	li.userID = AUserID;
	li.storageID = AStorageID;
	li.UserName = AUserName;
        li.version=version;
        li.qfsupply= Qfsupplier;
        li.qfclient = Qfclient;
	li.FormatStr = "#,##0.00";
	if (CheckPower("入库处理")) {
		ManageStorage(&li,frmMain->ClientHandle);
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::storagebackExecute(TObject *Sender)
{
	//入库退货管理
    if (!FindDog(version)) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = Acon;
	li.userID = AUserID;
	li.storageID = AStorageID;
	li.UserName = AUserName;
	li.FormatStr = "#,##0.00";
        li.version=version;
         li.qfsupply= Qfsupplier;
        li.qfclient = Qfclient;

	if (CheckPower("入库退货")) {
		ManageReturnStorage(&li,frmMain->ClientHandle);
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ZNreturnExecute(TObject *Sender)
{
	//智能退货
	if (!FindDog(version)) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = Acon;
	li.userID = AUserID;
	li.storageID = AStorageID;
	li.UserName = AUserName;
	li.FormatStr = "#,##0.00";
	if (CheckPower("智能退货")) {
		ZNReturnStock(&li,frmMain->ClientHandle);
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::sqPeisongExecute(TObject *Sender)
{
	//申请配送
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("申请配送")) {
		LandInfo li;
		li.app = Application;
		li.con = Acon;
		li.userID = AUserID;
		li.storageID = AStorageID;
		li.UserName = AUserName;
                if (CheckPower("作废处理")) {
                  li.qfclient= true;
                }else  li.qfclient= false;
		DiaoBo(&li,0,"",frmMain->ClientHandle);
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::zdpeisongExecute(TObject *Sender)
{
	//申请配送
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("主动配送")) {
		LandInfo li;
		li.app = Application;
		li.con = Acon;
		li.userID = AUserID;
		li.storageID = AStorageID;
		li.UserName = AUserName;
                if (CheckPower("作废处理")) {
                  li.qfclient= true;
                }else  li.qfclient= false;
		DiaoBo(&li,1,"",frmMain->ClientHandle);
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::RetailExecute(TObject *Sender)
{
	//POS零售管理
	if (!FindDog(version)) {
        return;
	}
	AnsiString powerlist;
	LandInfo li;
	li.app = Application;
	li.con = Acon;
	li.userID = AUserID;
	li.storageID = AStorageID;
		li.version=version;
	li.FormatStr = "#,##0.00";
		 li.qfsupply= Qfsupplier;
		li.qfclient = Qfclient;

	if (CheckPower("POS零售")) {
			//更改零售折扣
//前台挂单
////前台退换
//前台输入售价

	   if (CheckPower("更改零售折扣")) {
		powerlist="1";
	   }else powerlist="0";

	   if (CheckPower("前台挂单")) {
		powerlist=powerlist+"1";
	   }else powerlist=powerlist+"0";

	   if (CheckPower("前台退换")) {
		powerlist=powerlist+"1";
	   }else powerlist=powerlist+"0";

	   if (CheckPower("前台输入售价")) {
		powerlist=powerlist+"1";
	   }else powerlist=powerlist+"0";

	 

		ManageRetail(powerlist,&li,frmMain->ClientHandle);


                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::retailbackExecute(TObject *Sender)
{
	//零售退货
	if (!FindDog(version)) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = Acon;
	li.userID = AUserID;
	li.storageID = AStorageID;
	li.FormatStr = "#,##0.00";
        li.version=version;
         li.qfsupply= Qfsupplier;
        li.qfclient = Qfclient;
	if (CheckPower("POS退货")) {
		ManageReturnRetail(&li,frmMain->ClientHandle);
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::POSjiaobanExecute(TObject *Sender)
{
	//jiaojieban 零售员交接班
	if (!FindDog(version)) {
        return;
	}
	TADOQuery *aq = new TADOQuery(NULL);
	aq->Connection = Acon ;
	AnsiString sql;
	sql = "select jiaojiepwd from SYS_StorageInfo where id = " + IntToStr(AStorageID);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
        try
        {
	TfrmPwd *frmpwd = new  TfrmPwd(Application);
	if (frmpwd->ShowModal() == mrOk) {
		if (frmpwd->GetPassword()!= aq->FieldByName("jiaojiepwd")->AsAnsiString) {
            MessageBoxA(0,"密码输入错误！","错误",MB_ICONERROR);
			delete aq;
			return;
		}

		sql = "select jiaojieprint from SYS_StorageInfo where id = " + IntToStr(AStorageID);
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->FieldByName("jiaojieprint")->AsInteger ) {
			TfrmPrint *frm  = new TfrmPrint(Application);
			frm->RetailjiaojiePrint(AUserID, Acon,AStorageID);
			delete frm;
			//TfrmPrint::RetailjiaojiePrint(frmLand->GetUserID(), frmLand->conLand);
		}
		sql = "insert into sys_log (EventType,SourceFrom,EventDate,EventUser,EventMessage,stgName) values('信息','交接',getdate()," + IntToStr(AUserID) + ",'收银员交接'," + IntToStr(AStorageID) + ")" ;

		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		delete aq;
		jiaojie = 1;
		rlogin->Execute();
	}
        }catch(...)
        {}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::OrderExecute(TObject *Sender)
{
	if (!FindDog(version)) {
		return;
	}
	LandInfo li;
	li.app = Application;
	li.con = Acon;
	li.userID = AUserID;
	li.storageID = AStorageID;
        li.UserName =AUserName ;
	li.FormatStr = "#,##0.00";
        li.version=version;
         li.qfsupply= Qfsupplier;
        li.qfclient = Qfclient;
	if (CheckPower("订单处理") ) {
		BIOrderManage(&li,0,frmMain->ClientHandle);
                DisVisable();  //不显示主菜单
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SaleExecute(TObject *Sender)
{
	if (!FindDog(version)) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = Acon;
	li.userID = AUserID;
	li.storageID = AStorageID;
        li.UserName =AUserName ;
        li.version = version;
	li.FormatStr = "#,##0.00";
         li.qfsupply= Qfsupplier;
        li.qfclient = Qfclient;
	if (CheckPower("发货处理")) {
		ManageMarketing(&li,frmMain->ClientHandle);
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::salebackExecute(TObject *Sender)
{
	if (!FindDog(version)) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = Acon;
	li.userID = AUserID;
	li.storageID = AStorageID;
        li.UserName =AUserName ;
        li.version=version;
	li.FormatStr = "#,##0.00";
         li.qfsupply= Qfsupplier;
        li.qfclient = Qfclient;
	if (CheckPower("发货退货")) {
		ManageReturnMarketing(&li,frmMain->ClientHandle);
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::StorageSearchExecute(TObject *Sender)
{
	if (!FindDog(version)) {
        return;
	}
	if (CheckPower("库存查询")) {
		LandInfo li;
		li.app = Application;
		li.con = Acon;
		li.userID = AUserID;
		li.storageID = AStorageID;
                li.qfsupply= Qfsupplier;
                li.qfclient = Qfclient;
		BusinessQuery(Application, &li, 3,frmMain->ClientHandle);
       DisVisable();  //不显示主菜单
	}
	else
	{
		  ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::OrderSearchExecute(TObject *Sender)
{
	//订单查询
	if (!FindDog(version)) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = Acon;
	li.userID = AUserID;
	li.storageID = AStorageID;
        li.qfsupply= Qfsupplier;
                li.qfclient = Qfclient;
	if (CheckPower("订单查询")) {
		QryOderNote(&li,frmMain->ClientHandle);
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::stocksearchExecute(TObject *Sender)
{
	//采购查询
	if (!FindDog(version)) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = Acon;
	li.userID = AUserID;
	li.storageID = AStorageID;
        li.qfsupply= Qfsupplier;
                li.qfclient = Qfclient;
	if (CheckPower("采购查询")) {
		QryProcureNote(&li,frmMain->ClientHandle);
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::rikusearchExecute(TObject *Sender)
{
	//入库查询
	if (!FindDog(version)) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = Acon;
	li.userID = AUserID;
	li.storageID = AStorageID;
	li.FormatStr = "#,##0.00";
        li.qfsupply= Qfsupplier;
                li.qfclient = Qfclient;
	if (CheckPower("入库查询")) {
		QueryStorageNote(&li,frmMain->ClientHandle);
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::salesearchExecute(TObject *Sender)
{
	if (!FindDog(version)) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = Acon;
	li.userID = AUserID;
	li.storageID = AStorageID;
        li.qfsupply= Qfsupplier;
                li.qfclient = Qfclient;
	if (CheckPower("发货查询")) {
		QueryWsaleNote(&li,frmMain->ClientHandle);
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::posretailsearchExecute(TObject *Sender)
{
	if (!FindDog(version)) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = Acon;
	li.userID = AUserID;
	li.storageID = AStorageID;
        li.qfsupply= Qfsupplier;
                li.qfclient = Qfclient;
	if (CheckPower("POS零售查询")) {
		QueryRetailNote(&li,frmMain->ClientHandle);
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::storagechecksearchExecute(TObject *Sender)
{
	if (!FindDog(version)) {
        return;
	}
	if (CheckPower("盘点查询")) {
		LandInfo li;
		li.app = Application;
		li.con = Acon;
		li.userID = AUserID;
		li.storageID = AStorageID;
                li.qfsupply= Qfsupplier;
                li.qfclient = Qfclient;
		QryCheckNote(&li,frmMain->ClientHandle);
                DisVisable();  //不显示主菜单
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::peishongsearchExecute(TObject *Sender)
{
	//配送查询
	if (!FindDog(version)) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = Acon;
	li.userID = AUserID;
	li.storageID = AStorageID;
        li.qfsupply= Qfsupplier;
                li.qfclient = Qfclient;
	if (CheckPower("配送查询")) {
		QryPeisongNote(&li,frmMain->ClientHandle);
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::financestartExecute(TObject *Sender)
{
	//  单位往来期初
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("供应商往来期初")) {
		Tfrmsupplierandclient * frm = new Tfrmsupplierandclient(Application,Acon,1,AStorageID);
		frm->ShowModal();
		delete frm;
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ClientfinanceStartExecute(TObject *Sender)
{
	if (!FindDog(version)) {
        return;
	}
	if (CheckPower("客户往来期初")) {
		Tfrmsupplierandclient * frm = new Tfrmsupplierandclient(Application,Acon,2,AStorageID);
		frm->Show();
                DisVisable();  //不显示主菜单
		return;
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::supplierduizhangExecute(TObject *Sender)
{
	//供应商往来对账   0
	if (!FindDog(version)) {
        return;
	}
	if (CheckPower("供应商往来对帐")) {
		Tfrmwanglaizhang * frm = new Tfrmwanglaizhang(Application,1);      //供应商往来
		LandInfo li;
		li.app = Application;
		li.con = Acon;
		li.userID = AUserID;
		li.storageID = AStorageID;
                li.qfsupply= Qfsupplier;
                li.qfclient = Qfclient;
		frm->init(&li);
		frm->Show();
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ClientWanglaiduizhangExecute(TObject *Sender)
{
	if (!FindDog(version)) {
        return;
	}
	if (CheckPower("客户住来对帐")) {
		Tfrmclientwanglai * frm = new Tfrmclientwanglai(Application,2);      //客户往来
		LandInfo li;
		li.app = Application;
		li.con = Acon;
		li.userID = AUserID;
		li.storageID = AStorageID;
                li.qfsupply= Qfsupplier;
                li.qfclient = Qfclient;
		frm->init(&li);
		frm->Show();
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::yihutotalExecute(TObject *Sender)
{
	//应付汇总
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("应付汇总")) {
		Taccountyfhz *frm = new Taccountyfhz(Application,1,Acon,AStorageID);
		frm->username = AUserName;
		frm->stogName = AStorageName ;
                frm->labtitle->Caption = AStorageName;
		frm->Show();
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::yingfudetailExecute(TObject *Sender)
{
	//供应商应收明细
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("应付明细")) {
		TAccDetail *frm = new TAccDetail(Application,1,Acon,AStorageID);
		frm->stogName = AStorageName ;
		frm->Maker = AUserName ;
		frm->Show();
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::yingshouhuizhongExecute(TObject *Sender)
{
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("应收汇总")) {
		TAccountDoe *frm = new TAccountDoe(Application,2,Acon,AStorageID);
		frm->username = AUserName;
		frm->stogName = AStorageName ;
                frm->labtitle->Caption =AStorageName ;
		frm->Show();
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::yingshoudetailExecute(TObject *Sender)
{
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("应收明细")) {
		TAccDetail *frm = new TAccDetail(Application,2,Acon,AStorageID);
		frm->stogName = AStorageName ;
		frm->Maker = AUserName ;
		frm->Show();
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SupplierjieShuanSearchExecute(TObject *Sender)
{
	//	5．	供应商结算查询
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("供应商结算查询")) {
		TAccQuery * frm = new TAccQuery(Application,1,Acon,AStorageID,AMaster);
		frm->Show();
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ClientjieshuansearchExecute(TObject *Sender)
{
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("客户结算查询")) {
		TAccQuery * frm = new TAccQuery(Application,2,Acon,AStorageID,AMaster);
		frm->Show();
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SupplierjieshuanExecute(TObject *Sender)
{
	//付款结算
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("供应商结算")) {
		Tfrmbalance *frm = new Tfrmbalance(Application,Acon,AUserID,1,AStorageID,AMaster);

              //  frm->
		frm->Show();
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ClientJieShuanExecute(TObject *Sender)
{
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("客户结算")) {
		Tfrmbalance *frm = new Tfrmbalance(Application,Acon,AUserID,2,AStorageID,AMaster);
                 frm->qfclient=Qfclient;
                 frm->qfsupplier=Qfsupplier;
		frm->Show();
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SupplierInfoExecute(TObject *Sender)
{
	//供应商设置
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("供应商资料")) {
		LandInfo li;
		li.app = Application;
		li.con = Acon;
		li.userID = AUserID;
		li.storageID = AStorageID;
                li.qfsupply= Qfsupplier;
                li.qfclient = Qfclient;
		//1为供应商
		TSuppMana * frm = new TSuppMana(Application,1,Acon,AStorageID,Qfsupplier,Qfclient);
                if (CheckPower("供应商启停用"))
                {
                      frm->Supplierpower =true;
                  }else {
                      frm->Supplierpower=false;
                }
               // frm->qfsupplier= Qfsupplier;
		frm->Show();
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ClientInfoExecute(TObject *Sender)
{
	//客户资料
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("客户资料")) {
		LandInfo li;
		li.app = Application;
		li.con = Acon;
		li.userID = AUserID;
		li.storageID = AStorageID;
                li.qfsupply= Qfsupplier;
                li.qfclient = Qfclient;
		//1为供应商
		TSuppMana * frm = new TSuppMana(Application,2,Acon,AStorageID,Qfsupplier,Qfclient);
                 if (CheckPower("供应商启停用"))
                {
                      frm->Clientpower =true;
                  }else {
                      frm->Clientpower=false;
                }
                frm->qfclient=Qfclient;
                frm->qfsupplier= Qfsupplier;
		frm->Show();
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::StuffinfoExecute(TObject *Sender)
{
	if (!FindDog(version)) {
        return;
	}
	if (CheckPower("业务员资料")) {
		TfrmStaff *frm = new TfrmStaff(Application,Acon,AStorageID);
		frm->ShowModal();
		delete frm;
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::MemberInfoExecute(TObject *Sender)
{
	//会员管理
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("会员资料")) {
		TfrmMember *frm = new TfrmMember(Application,Acon);
		frm->userid = AUserID;
		frm->stgid = AStorageID;
		frm->Show();
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::MemberchongzhiExecute(TObject *Sender)
{
	//会员充值
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("会员充值")) {
		TfrmMemberResult *frm = new TfrmMemberResult(Application,Acon);
		frm->userid = AUserID;
		frm->stgid = AStorageID;
		frm->Show();
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::MemberchongziSearchExecute(TObject *Sender)
{
	//充值记录查询
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("会员充值查询")) {
		TFormRecordQuery *frm = new TFormRecordQuery(Application,Acon,AUserID,AStorageID);
		frm->Show();
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::StoragealarmExecute(TObject *Sender)
{
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("库存限量")) {
		TfrmalarmSet *frm = new TfrmalarmSet(Application,Acon,AStorageID,AUserID);
		frm->Show();
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::storageLocaladjustExecute(TObject *Sender)
{
	LandInfo li;
	li.app = Application;
	li.con = Acon;
	li.userID = AUserID;
	li.storageID = AStorageID;
        li.qfsupply= Qfsupplier;
        li.qfclient = Qfclient;
	if (CheckPower("库位调整")) {
		Tfrmadjust *frm = new Tfrmadjust(Application,Acon,&li);
		frm->Show();
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::onestorageNumberadjustExecute(TObject *Sender)
{
	if (!FindDog(version)) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = Acon;
	li.userID = AUserID;
	li.storageID = AStorageID;
	li.UserName = AUserName;
        li.qfsupply= Qfsupplier;
        li.qfclient = Qfclient;
	if (CheckPower("库存调整")) {
		StockAdjust(&li,frmMain->ClientHandle);
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::shikupandianExecute(TObject *Sender)
{
	//库存盘点
	if (!FindDog(version)) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = Acon;
	li.userID = AUserID;
	li.storageID = AStorageID;
	li.UserName = AUserName;
        li.qfsupply= Qfsupplier;
                li.qfclient = Qfclient;
	if (CheckPower("库存盘点")) {
		Tfrmcheckstock * frm = new Tfrmcheckstock(Application,Acon ,&li);
		frm->Show();
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::kucunyujingExecute(TObject *Sender)
{
	Tfrmalarm *frm = new Tfrmalarm(Application,Acon,AStorageID);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::rloginExecute(TObject *Sender)
{       char nClass[20];


        if(!EnumChildWindows(Handle,(WNDENUMPROC)EnumChildWin,2))
	{
		ShowMsg(Handle ,"有未关闭的子窗口，请关闭后重试！",3);
		return;
	}
        frmLand = new TfrmLand(Application);
	frmLand->edtPassword->Text = "";
	if (jiaojie == 1) {
		frmLand->Caption = "零售员交接班";
	}
	else
	{
    	frmLand->Caption = "登录";
	}
	jiaojie = 0;

	if( frmLand->ShowModal() == mrOk)
	{

		AUserID = frmLand->GetUserID();
		AStorageName = frmLand->cbstorage->Text;
		AStorageID = frmLand->GetStorageID();
		AUserName = frmLand->GetUserNameA();
		AMaster =  frmLand->GetMaster();

		PowerList->Clear();
		GetPowerList(AUserID);

		AnsiString sname = "您现在登录的是:" + AStorageName;
		stgname->Caption = sname;
                lbtitle->Caption  = GetTitle();
		LoadMyMessage();
                TPclick(-1);
		//Time();

	}
        delete   frmLand;
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::quitExecute(TObject *Sender)
{
	if (MessageBoxA(0,"是否退出系统？","提示",MB_ICONQUESTION|MB_OKCANCEL )==1 ) {
		Application->Terminate();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::RzToolButton56Click(TObject *Sender)
{
	TPoint  pt;
        TPoint p;

	pt.x = 208 + ((TRzToolButton*)Sender)->Left;
	pt.y = 104;
        p = ClientToScreen(pt);

   switch (((TRzToolButton*)Sender)->Tag) {
       case 0:
              	PMfile->Popup(p.x,p.y);
       break;
       case 1:
               PMsystem->Popup(p.x,p.y);
       break;
       case 2:
               PMbasicData->Popup(p.x,p.y);
       break;
       case 3:
               PMcatalog->Popup(p.x,p.y);
       break;
       case 4:
               PMwlclient->Popup(p.x,p.y);
       break;
       case 5:
               PMprocure->Popup(p.x,p.y);
       break;
       case 6:
              PMpeisong->Popup(p.x,p.y);
       break;
       case 7:
             PMsale->Popup(p.x,p.y);
       break;
         case 8:
             PMstack->Popup(p.x,p.y);
       break;
         case 9:
             PManalysis->Popup(p.x,p.y);
       break;
         case 10:
             PMhelp->Popup(p.x,p.y);
       break;


   }




}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::StogeSetExecute(TObject *Sender)
{
	//店仓信息设置
	if (!FindDog(version)) {
        return;
	}
	if (CheckPower("店仓管理")) {
		SetUpStorageInfo(Application,Acon,AUserID,AStorageID,AMaster,version);
      DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::DanHaoDisplayExecute(TObject *Sender)
{
	//单号显示规则
	if (!FindDog(version)) {
        return;
	}
	if (CheckPower("单号显示规则")) {
		AnsiString pwd;
		TADOQuery * aq;
		aq = new TADOQuery(this);
		aq->Connection = Acon  ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add("select bk from sys_bsset where name ='changeDanHaoDisplay'");
		aq->Open();
		pwd =  aq->FieldByName("bk")->AsAnsiString ;
		delete aq;
		TfrmPwd *frm1 = new TfrmPwd(Application);
		if (mrOk == frm1->ShowModal() ) {
			if (pwd == frm1->GetPassword()) {
				Tfrmsystemset *frm = new Tfrmsystemset(Application,Acon);
				frm->userid = AUserID;
				frm->storageid = AStorageID;
				frm->ShowModal();
				delete frm;
			}
			else
			{
				MessageBoxA(0,"密码输入错误!","提示",MB_ICONASTERISK);
			}
		}
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::RzToolButton57Click(TObject *Sender)
{
	TPoint  pt;
	GetCursorPos(&pt);
	pt.x = pt.x - 10;
	pt.y = pt.y + 10;
	PMsystem->Popup(pt.x,pt.y);
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::retailPrintExecute(TObject *Sender)
{
	//零售打印
	if (!FindDog(version)) {
        return;
	}
	if (CheckPower("零售打印")) {
		LandInfo li;
		li.app = Application;
		li.con = Acon;
		li.userID = AUserID;
		li.storageID = AStorageID;
		ManagePrint(Application, Acon, 3,AStorageID);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::PrinttitleExecute(TObject *Sender)
{
	//单据抬头
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("打印信息设置")) {
		Tfrmprinttitle *frm = new Tfrmprinttitle(Application,Acon,AStorageID);
		frm->ShowModal();
		delete frm;
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::logSearchExecute(TObject *Sender)
{
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("日志查询")) {
		TfrmLog *frm = new TfrmLog(Application,Acon,AUserID,AStorageID);
		frm->Show();
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::OrderControlExecute(TObject *Sender)
{
	//定单业务控制
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("订单业务控制")) {
		Tfrmorderbsset *frm = new Tfrmorderbsset(Application,Acon);
		frm->ShowModal();
		delete frm;
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::StockControlExecute(TObject *Sender)
{
	//采购业务控制
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("采购业务控制")) {
		Tfrmprocureset *frm = new Tfrmprocureset(Application,Acon);
		frm->ShowModal();
		delete frm;
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::storagecontrolExecute(TObject *Sender)
{
	//入库业务控制
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("入库业务控制")) {
		Tfrmstoragebsset *frm = new Tfrmstoragebsset(Application,Acon,AStorageID);
		frm->ShowModal();
		delete frm;
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SaleControlExecute(TObject *Sender)
{
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("批销业务控制")) {
		Tfrmsalebsset *frm = new Tfrmsalebsset(Application,Acon);
		frm->ShowModal();
		delete frm;
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::RetailControlExecute(TObject *Sender)
{
	//零售业务控制
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("零售业务控制")) {
		Tfrmretailbsset *frm = new Tfrmretailbsset(Application,Acon);
		frm->ShowModal();
		delete frm;
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::PeiShongControlExecute(TObject *Sender)
{
	//配送业务控制
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("配送业务控制")) {
		Tfrmdiaoboset *frm = new Tfrmdiaoboset(Application,Acon);
		frm->ShowModal();
		delete frm;
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::StockAlarmControlExecute(TObject *Sender)
{
	//配送业务控制
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("库存预警设置")) {
		Tfrmstockalarmbsset *frm = new Tfrmstockalarmbsset(Application,Acon);
		frm->ShowModal();
		delete frm;
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::pressmanageExecute(TObject *Sender)
{
	//出版社管理
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("出版社管理")) {
		ManagePress(Application, Acon,frmMain->ClientHandle);
                DisVisable();  //不显示主菜单
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::breedTypeExecute(TObject *Sender)
{
	//图书类别管理
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("品目类别管理")) {
		ManageBookType(Application, Acon,frmMain->ClientHandle);
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::LocalManageExecute(TObject *Sender)
{
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("区域管理")) {
		TMemberAreaSet * frm = new TMemberAreaSet(Application,Acon,AStorageID);
		frm->ShowModal();
		delete frm;
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::memberclassExecute(TObject *Sender)
{
	//会员类型
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("会员类型")) {
		Tfrmmemclassmg *frm = new Tfrmmemclassmg(Application,Acon);
		frm->ShowModal();
		delete frm;
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::StorageInfoExecute(TObject *Sender)
{
	//库位管理
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("库位资料") ) {
		LandInfo li;
		li.app = Application;
		li.con = Acon;
		li.userID = AUserID;
		li.storageID = AStorageID;
                li.qfsupply= Qfsupplier;
                li.qfclient = Qfclient;
		Tfrmstorelocal *frm = new Tfrmstorelocal(Application,Acon,&li);
		frm->ShowModal();
		delete frm;
                DisVisable();  //不显示主菜单
	}
	else
	{
	   ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SupplierClassExecute(TObject *Sender)
{
	//供应商类别
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("供应商分类")) {
		Tfrmcustomertype *frm = new Tfrmcustomertype(Application,Acon,1,AStorageID);
		frm->ShowModal();
		delete frm;
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ClientClassExecute(TObject *Sender)
{
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("客户分类")) {
		Tfrmcustomertype *frm = new Tfrmcustomertype(Application,Acon,2,AStorageID);
		frm->ShowModal();
		delete frm;
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::RzToolButton58Click(TObject *Sender)
{
	TPoint  pt;
	GetCursorPos(&pt);
	pt.x = pt.x - 10;
	pt.y = pt.y + 10;
	PMbasicData->Popup(pt.x,pt.y);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::BreedManageExecute(TObject *Sender)
{
	//图书品目管理
	if (!FindDog(version)) {
        return;
	}
	if (CheckPower("图书目录管理") ) {
		CatalogKan(Application, Acon,AStorageID,AUserID,frmMain->ClientHandle,version);
       DisVisable();  //不显示主菜单
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::catalogMakeExecute(TObject *Sender)
{
	//目录制作
	if (!FindDog(version)) {
        return;
	}
	if (CheckPower("目录制作") ) {
		Catalogbuilt(Application, Acon,frmMain->ClientHandle);
                DisVisable();  //不显示主菜单
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::catalogneworrecExecute(TObject *Sender)
{
	//新荐书目
	if (!FindDog(version)) {
        return;
	}
	if (CheckPower("新荐书目") ) {
		Catalogneworrec(Application, Acon,AStorageID,AUserID,frmMain->ClientHandle);
                DisVisable();  //不显示主菜单
	}else
	{                                    //TApplication* app, TADOConnection* con,int stgid,int userid,HWND MainHandle
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::qikanguanliExecute(TObject *Sender)
{
	//期刊管理
	if (!FindDog(version)) {
        return;
	}
	if (CheckPower("期刊目录管理") ) {
		QiKanguanli(Application, Acon,AStorageID,frmMain->ClientHandle,version);
                DisVisable();  //不显示主菜单
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::MutibookExecute(TObject *Sender)
{
	//重书合并
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("重书合并")) {
		Multibook(Application,Acon,AStorageID,AUserID,frmMain->ClientHandle);
       DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::RzToolButton59Click(TObject *Sender)
{
	TPoint  pt;
	GetCursorPos(&pt);
	pt.x = pt.x - 10;
	pt.y = pt.y + 10;
	PMcatalog->Popup(pt.x,pt.y);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::RzToolButton60Click(TObject *Sender)
{
	TPoint  pt;
	GetCursorPos(&pt);
	pt.x = pt.x - 10;
	pt.y = pt.y + 10;
	PMwlclient->Popup(pt.x,pt.y);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::RzToolButton61Click(TObject *Sender)
{
	TPoint  pt;
	GetCursorPos(&pt);
	pt.x = pt.x - 10;
	pt.y = pt.y + 10;
	PMprocure->Popup(pt.x,pt.y);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::RzToolButton62Click(TObject *Sender)
{
	TPoint  pt;
	GetCursorPos(&pt);
	pt.x = pt.x - 10;
	pt.y = pt.y + 10;
	PMpeisong->Popup(pt.x,pt.y);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::RzToolButton63Click(TObject *Sender)
{
	TPoint  pt;
	GetCursorPos(&pt);
	pt.x = pt.x - 10;
	pt.y = pt.y + 10;
	PMsale->Popup(pt.x,pt.y);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::RzToolButton64Click(TObject *Sender)
{
	TPoint  pt;
	GetCursorPos(&pt);
	pt.x = pt.x - 10;
	pt.y = pt.y + 10;
	PMstack->Popup(pt.x,pt.y);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::OperatorManageExecute(TObject *Sender)
{
	//操作员管理
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("操作员管理")) {
		Tfrmuser * frm = new Tfrmuser(Application,Acon,AUserName,AStorageID,AUserID);
		frm->ShowModal();
		delete frm;
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::rolemanageExecute(TObject *Sender)
{
	//角色管理
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("角色管理")) {
		Tfrmgroup * frm = new Tfrmgroup(Application,Acon,AStorageID,AUserID);
		frm->ShowModal();
		delete frm;
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::PowerSetExecute(TObject *Sender)
{
	//权限管理
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("权限设置")) {
		Tfrmpurview * frm  = new Tfrmpurview(Application,Acon , AStorageID,AUserID);
		frm->ShowModal();
		delete frm;
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::StorToStorExecute(TObject *Sender)
{
	if (!FindDog(version)) {
		return;
	}
	if (!AMaster) {
		MessageBoxA(0,"只有总店相关人员才能进行该项设置！","提示",MB_ICONWARNING);
		return;
	}
	if (CheckPower("各店互访权限管理")) {
		TfrmStorToStor *frm = new TfrmStorToStor(Application,Acon);
		frm->ShowModal();
		delete frm;
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::specialPassWordExecute(TObject *Sender)
{
	//特殊口令
	if (!FindDog(version)) {
		return;
	}
	LandInfo li;
	li.app = Application;
	li.con = Acon;
	li.userID = AUserID;
	li.storageID = AStorageID;
	if (CheckPower("特殊口令设置")){
		TfrmSpecialPassword *frm = new TfrmSpecialPassword(Application);
		frm->Init(&li);
		frm->ShowModal();
		delete frm;
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::retailclassPromotionExecute(TObject *Sender)
{
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("零售类别促销")) {
		DiscountSales(Application, Acon,AStorageID);
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::RetailbuyExecute(TObject *Sender)
{
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("零售购物金额促销")) {
		LandInfo li;
		li.app = Application;
		li.con = Acon;
		li.userID = AUserID;
		li.storageID = AStorageID;
		TfrmMonerydiscount *frm = new TfrmMonerydiscount(Application,Acon,AStorageID) ;
		frm->Show();
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::MemberoneProductExecute(TObject *Sender)
{
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("会员类型单品促销")) {
		MemberDiscount(Application, Acon,AStorageID);
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::MemberjifenExecute(TObject *Sender)
{
	//会员积分管理
	if (!FindDog(version)) {
		return;
	}
	if (!AMaster) {
		MessageBoxA(0,"只有总店才有权限操作此模块!","提示",MB_ICONASTERISK);
		return;
	}
	if (CheckPower("会员积分管理")) {
		LandInfo li;
		li.app = Application;
		li.con = Acon;
		li.userID = AUserID;
		li.storageID = AStorageID;
		TfrmMemberjifen *frm = new TfrmMemberjifen(Application,Acon) ;
		frm->stgid = AStorageID ;
		frm->ShowModal();
		delete frm;
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::MemberadddotExecute(TObject *Sender)
{
	/*if (!FindDog(version)) {
		return;
	}
	if (CheckPower("会员类型与预计折扣")) {
		Memtypeadd(Application,Acon,AStorageID);
	}
	else
	{
		ShowNoPower();
	}  */
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SaleOneProductExecute(TObject *Sender)
{
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("批销单品折扣")) {
		WsaleDiscount(Application, Acon,AStorageID);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SaleAddPointExecute(TObject *Sender)
{
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("批销附加折扣")) {
		WsaleDiscountSales(Application, Acon,AStorageID);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SaleNowbackDotExecute(TObject *Sender)
{
	//批销现场返点
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("批销现场返点")) {
		LandInfo li;
		li.app = Application;
		li.con = Acon;
		li.userID = AUserID;
		li.storageID = AStorageID;
		TfrmClientBackdot *frm = new TfrmClientBackdot(Application,Acon,AStorageID) ;
		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::jingxiaochunfenxieExecute(TObject *Sender)
{
	//进销存分析
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("进销存分析")) {
		PurchaseSalesInventoryAnalysis(Application, Acon,AStorageID);
   DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::saletimehuizhongExecute(TObject *Sender)
{
	//销售时段汇总统计
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("销售时段汇总统计")) {

                if(CheckPower("销售时段成本查看"))
                {
                      xiaoshou(Application,Acon,AStorageID,true);
                      DisVisable();  //不显示主菜单
                }else   xiaoshou(Application,Acon,AStorageID,false);

	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::yefupaihangbangExecute(TObject *Sender)
{
	//业务排行旁
	if (!FindDog(version)) {
		return;
	}
   if (CheckPower("业务排行榜")) {
		Yewupaihang(Application,Acon,AStorageID);
                DisVisable();  //不显示主菜单
   }
   else
   {
		ShowNoPower();
   }
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::retailhuizhongfengxieExecute(TObject *Sender)
{
	//零售汇总分析
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("零售汇总分析")) {
		RetailSummary(Application, Acon,AStorageID);
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------



void __fastcall TfrmMain::clientjieduanjiesuanExecute(TObject *Sender)
{
	// 客户阶段结算分析
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("客户走账期结算分析")) {
		ClientStageClearing(Application, Acon,AStorageID);
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::supplierjieduanjiesuanExecute(TObject *Sender)
{
	// 供应商阶段结算分析
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("供应商走账期结算分析")) {
		SupplierStageClearing(Application, Acon,AStorageID);
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::RzToolButton65Click(TObject *Sender)
{
	TPoint  pt;
	GetCursorPos(&pt);
	pt.x = pt.x - 10;
	pt.y = pt.y + 10;
	PManalysis->Popup(pt.x,pt.y);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::siglebookExecute(TObject *Sender)
{
	if (!FindDog(version)) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = Acon;
	li.userID = AUserID;
	li.storageID = AStorageID;
	li.UserName = AUserName;
        li.version=version;
	li.FormatStr = "#,##0.00";
	if (CheckPower("单品分析")) {
		Siglebook(&li,frmMain->ClientHandle);
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::paihangfenxiExecute(TObject *Sender)
{
	//销售书排行与毛利分析
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("销售书排行与毛利分析")) {
		SalesAnalysis(Application, Acon,AStorageID);
                DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::manualExecute(TObject *Sender)
{
	//用户手册
	AnsiString path;
	path =  ExtractFilePath(Application->ExeName);
	path = path + "help.doc";
	ShellExecute(NULL,"open",path.c_str() ,"","",SW_SHOW);
        DisVisable();  //不显示主菜单
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::systemupdateExecute(TObject *Sender)
{
	//系统更新
	Tfrmshengji * frm = new Tfrmshengji(Application);
	frm->ShowModal();
        DisVisable();  //不显示主菜单

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::aboutExecute(TObject *Sender)
{
	//关于本软件
	TfrmAboutsoftware *frm = new TfrmAboutsoftware(Application);
	frm->ShowModal();
        DisVisable();  //不显示主菜单
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::RzToolButton66Click(TObject *Sender)
{
	TPoint  pt;
	GetCursorPos(&pt);
	pt.x = pt.x - 10;
	pt.y = pt.y + 10;
	PMhelp->Popup(pt.x,pt.y);
}
AnsiString TfrmMain::GetTitle()
{
     AnsiString title;
   	TDateTime dateTime;
	char   dayss[7][10]   =   { "星期日 ", "星期一 ",   "星期二 ",   "星期三 ",   "星期四 ",   "星期五 ",   "星期六 "};
	dateTime=DateTimeToStr(Now());

   title = "欢迎您："+AUserName+"，今天是"+FormatDateTime("YYYY年mm月dd日",Date())+"，"+dayss[dateTime.DayOfWeek()-1];
   return title;

}
//---------------------------------------------------------------------------




void __fastcall TfrmMain::msg1Click(TObject *Sender)
{
    	LandInfo li;
	int type =0;
	int ID;
        int MsgType; //点进去后,是否需要操作
	type = 2;
        TCHAR buf[MAX_PATH+1];
	AnsiString DanHao;
        TADOQuery *aq;
        HWND hWnd;
        AnsiString sql;
	type =	((TLabel*)(Sender))->Tag ;
		MsgType = StrToInt(((TLabel*)(Sender))->HelpKeyword);
	ID = ((TLabel*)(Sender))->HelpContext ;
	DanHao = ((TLabel*)(Sender))->Hint;
	adosp->Connection = Acon;
		MsgType=0;
	try
	{
	   switch (type) {
		   case 1:
				li.app = Application;
				li.con = Acon ;
				li.userID = AUserID  ;
				li.FormatStr = "#,##0.00";
				li.storageID = AStorageID  ;
				adosp->Parameters->ParamByName("@ID")->Value =ID;
				adosp->ExecProc();
				BIOrderManageDanHao(&li,DanHao,frmMain->ClientHandle);

				break;
		   case 2:         //申请配送
                                sql = "select sys_user.* from sys_user join SYS_UserGroup on SYS_UserGroup.userid = SYS_User.id "
                                " join SYS_GroupAction on SYS_GroupAction.groupid = SYS_UserGroup.groupid "
                                " join SYS_Action on SYS_GroupAction.actionid = sys_action.code "
                                " where  ((sys_action.actionname = '申请配送') or (sys_action.actionname = '主动配送')) and SYS_User.id = " + IntToStr(AUserID) ;
                                aq = new TADOQuery(Application);
                                aq->Connection = Acon;
                                aq->Close();
                                aq->SQL ->Clear();
                                aq->SQL->Add(sql);
                                aq->Open();
                                if (aq->IsEmpty() ) {
                                     ShowMsg(Handle ,"请确认是否具有此功能的操作权限！",3);
                                     break;
                                }
                                hWnd = ::GetWindow(::GetWindow(ClientHandle, GW_CHILD), GW_HWNDFIRST);

				while (hWnd != NULL)
				{
					::ZeroMemory(buf, sizeof(buf));
					if (::GetClassName(hWnd, buf, MAX_PATH) > 0)
					{
						if (StrCmp(_T("Tfrmdiaobo"), buf) == 0)
						{

                                                        ShowMsg(Handle ,"为了保证连锁店库存的真实有效性\n一个用户同时只允许打开一个主动配送或请求配送模块！",3);
							return;
						}
					}
					hWnd = ::GetWindow(hWnd, GW_HWNDNEXT);
				}


				li.app = Application;
				li.con = Acon;
				li.userID =   AUserID;
				li.storageID =  AStorageID;
				li.UserName = AUserName;
				DiaoBo(&li,10,DanHao,frmMain->ClientHandle); //消息点进去的,申请配送为10
                                if (MsgType==0) {
                                        adosp->Parameters->ParamByName("@ID")->Value = ID;
			         	adosp->ExecProc();
                                }

                                break;
		   case 3:         //主动配送

                                  sql = "select sys_user.* from sys_user join SYS_UserGroup on SYS_UserGroup.userid = SYS_User.id "
                                " join SYS_GroupAction on SYS_GroupAction.groupid = SYS_UserGroup.groupid "
                                " join SYS_Action on SYS_GroupAction.actionid = sys_action.code "
                                " where  ((sys_action.actionname = '申请配送') or (sys_action.actionname = '主动配送')) and SYS_User.id = " + IntToStr(AUserID) ;
                                aq = new TADOQuery(Application);
                                aq->Connection = Acon;
                                aq->Close();
                                aq->SQL ->Clear();
                                aq->SQL->Add(sql);
                                aq->Open();
                                if (aq->IsEmpty() ) {
                                     ShowMsg(Handle ,"请确认是否具有此功能的操作权限！",3);
                                     break;
                                }

				hWnd = ::GetWindow(::GetWindow(ClientHandle, GW_CHILD), GW_HWNDFIRST);

				while (hWnd != NULL)
				{
					::ZeroMemory(buf, sizeof(buf));
					if (::GetClassName(hWnd, buf, MAX_PATH) > 0)
					{
						if (StrCmp(_T("Tfrmdiaobo"), buf) == 0)
						{

                                                        ShowMsg(Handle ,"为了保证连锁店库存的真实有效性\n一个用户同时只允许打开一个主动配送或请求配送模块！",3);
							return;
						}
					}
					hWnd = ::GetWindow(hWnd, GW_HWNDNEXT);
				}


				li.app = Application;
				li.con = Acon;
				li.userID =   AUserID;
				li.storageID =  AStorageID;
				li.UserName = AUserName;
				DiaoBo(&li,11,DanHao,frmMain->ClientHandle);  //消息点进去的,主动配送 为11
                                   if (MsgType==0) {
                                        adosp->Parameters->ParamByName("@ID")->Value = ID;
			         	adosp->ExecProc();
                                }
			   break;
		 }
   }catch(...)
   {

   }
	LoadMyMessage();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::lbmoreClick(TObject *Sender)
{
   TfrmpublicMsg * frmPmsg = new TfrmpublicMsg(Application);
   frmPmsg->init(Acon,AStorageID,AUserID);
   frmPmsg->LoadData();
   //frmPmsg->Show();
   //;
   if (frmPmsg->ShowModal()== mrOk) {

      LanuchOrder(frmPmsg->type1,frmPmsg->ID,frmPmsg->DanHao,frmPmsg->MsgType);
   }
    delete frmPmsg;
}
void TfrmMain::LanuchOrder(AnsiString type1,AnsiString ID,AnsiString DanHao,AnsiString IDstr)
 {



             //kdfd
             HWND hWnd;
        AnsiString sql;
        int type = 0;
        int MsgType;
		type = StrToInt(type1);
    	LandInfo li;
         TADOQuery *aq;

         TCHAR buf[MAX_PATH+1];
	adosp->Connection = Acon;
	try
	{
	   switch (type) {
		   case 1:
				li.app = Application;
				li.con = Acon  ;
				li.userID = AUserID  ;
				li.FormatStr = "#,##0.00";
				li.storageID =  AStorageID  ;
                                li.qfsupply= Qfsupplier;
                li.qfclient = Qfclient;
				adosp->Parameters->ParamByName("@ID")->Value =ID;
				adosp->ExecProc();
				BIOrderManageDanHao(&li,DanHao,frmMain->ClientHandle);

				break;
		   case 2:
                               sql = "select sys_user.* from sys_user join SYS_UserGroup on SYS_UserGroup.userid = SYS_User.id "
                                " join SYS_GroupAction on SYS_GroupAction.groupid = SYS_UserGroup.groupid "
                                " join SYS_Action on SYS_GroupAction.actionid = sys_action.code "
                                " where  ((sys_action.actionname = '申请配送') or (sys_action.actionname = '主动配送')) and SYS_User.id = " + IntToStr(AUserID) ;
                               aq = new TADOQuery(Application);
                                aq->Connection = Acon;
                                aq->Close();
                                aq->SQL ->Clear();
                                aq->SQL->Add(sql);
                                aq->Open();
                                if (aq->IsEmpty() ) {
                                     ShowMsg(Handle ,"请确认是否具有此功能的操作权限！",3);
                                     break;
                                }
                                hWnd = ::GetWindow(::GetWindow(ClientHandle, GW_CHILD), GW_HWNDFIRST);

				while (hWnd != NULL)
				{
					::ZeroMemory(buf, sizeof(buf));
					if (::GetClassName(hWnd, buf, MAX_PATH) > 0)
					{
						if (StrCmp(_T("Tfrmdiaobo"), buf) == 0)
						{

                                                        ShowMsg(Handle ,"为了保证连锁店库存的真实有效性\n一个用户同时只允许打开一个主动配送或请求配送模块！",3);
							return;
						}
					}
					hWnd = ::GetWindow(hWnd, GW_HWNDNEXT);
				}


				li.app = Application;
				li.con = Acon;
				li.userID =   AUserID;
				li.storageID =  AStorageID;
				li.UserName = AUserName;
                                li.qfsupply= Qfsupplier;
                                li.qfclient = Qfclient;
				DiaoBo(&li,10,DanHao,frmMain->ClientHandle);
                                   if (StrToInt(IDstr)==0) {
                                        adosp->Parameters->ParamByName("@ID")->Value = ID;
			         	adosp->ExecProc();
                                }
                                break;
		   case 3:
            	        sql = "select sys_user.* from sys_user join SYS_UserGroup on SYS_UserGroup.userid = SYS_User.id "
                                " join SYS_GroupAction on SYS_GroupAction.groupid = SYS_UserGroup.groupid "
                                " join SYS_Action on SYS_GroupAction.actionid = sys_action.code "
                                " where  ((sys_action.actionname = '申请配送') or (sys_action.actionname = '主动配送')) and SYS_User.id = " + IntToStr(AUserID) ;
                                aq = new TADOQuery(Application);
                                aq->Connection = Acon;
                                aq->Close();
                                aq->SQL ->Clear();
                                aq->SQL->Add(sql);
                                aq->Open();
                                if (aq->IsEmpty() ) {
                                     ShowMsg(Handle ,"请确认是否具有此功能的操作权限！",3);
                                     break;
                                }

				hWnd = ::GetWindow(::GetWindow(ClientHandle, GW_CHILD), GW_HWNDFIRST);

				while (hWnd != NULL)
				{
					::ZeroMemory(buf, sizeof(buf));
					if (::GetClassName(hWnd, buf, MAX_PATH) > 0)
					{
						if (StrCmp(_T("Tfrmdiaobo"), buf) == 0)
						{

                                                        ShowMsg(Handle ,"为了保证连锁店库存的真实有效性\n一个用户同时只允许打开一个主动配送或请求配送模块！",3);
							return;
						}
					}
					hWnd = ::GetWindow(hWnd, GW_HWNDNEXT);
				}


				li.app = Application;
				li.con = Acon;
				li.userID =   AUserID;
				li.storageID =  AStorageID;
				li.UserName = AUserName;
                                li.qfsupply= Qfsupplier;
                li.qfclient = Qfclient;
				DiaoBo(&li,11,DanHao,frmMain->ClientHandle);
                                   if (StrToInt(MsgType)==0) {
                                        adosp->Parameters->ParamByName("@ID")->Value = ID;
			         	adosp->ExecProc();
                                }
		 }
   }catch(...)
   {

   }
       	LoadMyMessage();

 }
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Image10Click(TObject *Sender)
{
/*   	//任务管理
	if (!FindDog(version)) {
        return;
	}
	if (CheckPower("任务管理")) {
		Tfrmtaskmanagea * frm = new Tfrmtaskmanagea(Application);
		frm->init(Acon,AUserID,AStorageID);

		frm->Show();
	}
	else
	{
		ShowNoPower();
	}  */

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Image11Click(TObject *Sender)
{
    	//文档管理
	 if(!FindDog(version)) {
        return;
	}
	if (CheckPower("文档管理")) {
		Tfrmdocument * frm = new Tfrmdocument(Application);
		frm->init(Acon,AUserID,AStorageID);

		frm->Show();
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::wenjuguanliExecute(TObject *Sender)
{
	//文具目录管理
	if (!FindDog(version)) {
        return;
	}
	if (CheckPower("文具目录管理") ) {
		WenJuguanli(Application, Acon,AStorageID,AUserID,frmMain->ClientHandle);
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::clientadddotExecute(TObject *Sender)
{
	//客户折扣加点设置
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("客户折扣加点设置")) {
		Tfrmclientadddot *frm = new Tfrmclientadddot(Application,Acon,AStorageID);
		frm->ShowModal();
		delete frm;
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::Image9Click(TObject *Sender)
{
//
	//新荐书目
	if (!FindDog(version)) {
        return;
	}

        if (version==0) {
           	if (CheckPower("快捷发货") ) {
        	LandInfo li;
		li.app = Application;
		li.con = Acon;
		li.userID = AUserID;
		li.storageID = AStorageID;
                li.qfsupply= Qfsupplier;
                li.qfclient = Qfclient;
		Catalogneworrecbsadmin(Application, Acon,frmMain->ClientHandle,&li);
	}else
	{
		ShowNoPower();
	}
        }else
        {
	if (CheckPower("非省代发货") ) {
        	LandInfo li;
		li.app = Application;
		li.con = Acon;
		li.userID = AUserID;
		li.storageID = AStorageID;
                li.qfsupply= Qfsupplier;
                li.qfclient = Qfclient;
		Catalogneworrecbsadmin(Application, Acon,frmMain->ClientHandle,&li);
	}else
	{
		ShowNoPower();
	}
        }
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::N49Click(TObject *Sender)
{
//
  if (CheckPower("客户单品折扣") ) {
   Tfrmclientdisforbook *frm = new Tfrmclientdisforbook(Application);
   frm->init(Acon,AStorageID);
   frm->Show();
  }else
   {
       ShowNoPower();
   }

}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::Timer1Timer(TObject *Sender)
{
LoadMyMessage();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N52Click(TObject *Sender)
{
//
    if (!FindDog(version)) {
        return;
	}
            if (CheckPower("会员订阅查询") ) {
	LandInfo li;
	li.app = Application;
	li.con = Acon;
	li.userID = AUserID;
	li.storageID = AStorageID;
        li.qfsupply= Qfsupplier;
        li.qfclient = Qfclient;
       QueryMemberOrder(&li,frmMain->ClientHandle);
        }else
	{
	   ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N54Click(TObject *Sender)
{
//
       	//采购管理
    if (!FindDog(version)) {
        return;
	}
        if (version==0) {
               N66->Click();
        }else
        {
            if (CheckPower("省代采购") ) {
            LandInfo li;
            li.app = Application;
            li.con = Acon;
            li.userID = AUserID;
            li.storageID = AStorageID;
            li.UserName=AUserName;
            DaiXiao(&li,frmMain->ClientHandle);
            DisVisable();  //不显示主
        }else
	{
	   ShowNoPower();
	}
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N56Click(TObject *Sender)
{
//
if (!FindDog(version)) {
        return;
	}
        if(version==0)
        {

             MenuItem12->Click();


        }else
        {
   if (CheckPower("省代发货") ) {
	LandInfo li;
	li.app = Application;
	li.con = Acon;
	li.userID = AUserID;
	li.storageID = AStorageID;
        li.UserName =AUserName ;
       DiaoxiaoCaigouFahuo(&li,frmMain->ClientHandle);
       DisVisable();  //不显示主菜单
        }else
	{
	   ShowNoPower();
	}
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N57Click(TObject *Sender)
{
//
      if (!FindDog(version)) {
        return;
	}
   if (CheckPower("省代采购查询") ) {
	LandInfo li;
	li.app = Application;
	li.con = Acon;
	li.userID = AUserID;
	li.storageID = AStorageID;
       QryProcureShenDai(&li,frmMain->ClientHandle);
       DisVisable();  //不显示主菜单
       }else
	{
	   ShowNoPower();
	}
}
//---------------------------------------------------------------------------



void __fastcall TfrmMain::N59Click(TObject *Sender)
{
       	if (!FindDog(version)) {
        return;
	}
      	if (CheckPower("批销汇总查询")) {
            	LandInfo li;
	li.app = Application;
	li.con = Acon;
	li.userID = AUserID;
	li.storageID = AStorageID;
        li.UserName=AUserName;

       pixiaohuizhong(&li,frmMain->ClientHandle);
       DisVisable();  //不显示主菜单
	}
	else
	{
		ShowNoPower();
	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N60Click(TObject *Sender)
{
    //
    	//单日结账
	if (!FindDog(version)) {
        return;
	}


        	LandInfo li;
		li.app = Application;
		li.con = Acon;
		li.userID = AUserID;
		li.storageID = AStorageID;
                li.UserName= AUserName;
	if (CheckPower("零售结账查询")) {
		CheckQuery(&li,frmMain->ClientHandle);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::maitoolbuttonClick(TObject *Sender)
{
    //

	TPoint  pt;
        TPoint p;

	pt.x = 5 + ((TRzToolButton*)Sender)->Left;
	pt.y = 29;
        p = ClientToScreen(pt);

   switch (((TRzToolButton*)Sender)->Tag) {
       case 0:
              	PMfile->Popup(p.x,p.y);
       break;
       case 1:
               PMsystem->Popup(p.x,p.y);
       break;
       case 2:
               PMbasicData->Popup(p.x,p.y);
       break;
       case 3:
               PMcatalog->Popup(p.x,p.y);
       break;
       case 4:
               PMwlclient->Popup(p.x,p.y);
       break;
       case 5:
               PMprocure->Popup(p.x,p.y);
       break;
       case 6:
              PMpeisong->Popup(p.x,p.y);
       break;
       case 7:
             PMsale->Popup(p.x,p.y);
       break;
         case 8:
             PMstack->Popup(p.x,p.y);
       break;
         case 9:
             PManalysis->Popup(p.x,p.y);
       break;
         case 10:
             PMhelp->Popup(p.x,p.y);
       break;


   }

}
//---------------------------------------------------------------------------



void __fastcall TfrmMain::N62Click(TObject *Sender)
{
//财务日记帐
   if (CheckPower("非营业性收支") ) {
        Tfrmjizhang * frm = new Tfrmjizhang(Application);
        frm->Astgid = IntToStr(AStorageID) ;
        frm->init(Acon,AStorageID,AUserID);
        frm->search();
        frm->stgname = AStorageName;
        frm->Ausername = AUserName;
        frm->Show();
       // delete frm;
   }else
   {
       ShowNoPower();
   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N66Click(TObject *Sender)
{
//
   if (CheckPower("非营利性收支查询") ) {
        Tfrmsearch * frm = new Tfrmsearch(Application);

        frm->init(Acon,AStorageID,AUserID);


        frm->ShowModal();
        delete frm;
   }else
   {
       ShowNoPower();
   }
}
void TfrmMain::InitQF()
{

	TADOQuery *aq = new TADOQuery(NULL);
	aq->Connection = Acon ;
	AnsiString sql;
	sql = "select value,name from SYS_BSSET where name in('Qufensupplier','Qufenclient')";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();

         Qfsupplier=false;
        Qfclient=false;

        while(!aq->Eof)
        {
           if (aq->FieldByName("name")->AsAnsiString=="Qufensupplier") {
              if (aq->FieldByName("value")->AsBoolean) {
               Qfsupplier=true;
             }
           }
           if (aq->FieldByName("name")->AsAnsiString=="Qufenclient") {
              if (aq->FieldByName("value")->AsBoolean) {
              Qfclient=true;
           }
           }

         aq->Next();
        }
         delete aq;


       



}
void TfrmMain::InitDiffVersion()
{
        version=GetVersionNum();
        if(version==0)//零售版
        {
           Label1->Caption="非营业性收支";
           Label2->Caption="快捷发货";
           Label3->Caption="非营业性查询";
           Label4->Caption="单品分析";

           N54->Visible=false;
           N56->Visible=false;
           N57->Visible=false;
           N52->Visible=false;
        }





}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::Image8Click(TObject *Sender)
{
	//采购管理
    if (!FindDog(version)) {
        return;
	}

       if (version==0) {
               N62->Click();
        }else
        {

            if (CheckPower("非省代采购") ) {
            LandInfo li;
            li.app = Application;
            li.con = Acon;
            li.userID = AUserID;
            li.storageID = AStorageID;
            li.UserName = AUserName;
            li.FormatStr = "#,##0.00";
			ProcureManage(&li,frmMain->ClientHandle);
            DisVisable();  //不显示主菜单
            }else
            {
               ShowNoPower();
            }
            }
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::N67Click(TObject *Sender)
{
//数据清理

   if (CheckPower("数据整理") ) {
        Tfrmjizhang * frm = new Tfrmjizhang(Application);
        frm->Astgid = IntToStr(AStorageID) ;
        frm->init(Acon,AStorageID,AUserID);
        frm->search();
        frm->stgname = AStorageName;
        frm->Ausername = AUserName;
        frm->Show();
       // delete frm;
   }else
   {
       ShowNoPower();
   }
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::N71Click(TObject *Sender)
{
//教师管理
  Tfrmteachermanager * frm = new Tfrmteachermanager(Application);
  frm->Acon=Acon;
  frm->ShowModal();
  delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N70Click(TObject *Sender)
{
   //教师返点设置

			LandInfo li;
			li.app = Application;
			li.con = Acon;
			li.userID = AUserID;
			li.storageID = AStorageID;
			li.UserName = AUserName;
			li.FormatStr = "#,##0.00";
			Tearcher(&li,frmMain->ClientHandle);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N72Click(TObject *Sender)
{
  		LandInfo li;
			li.app = Application;
			li.con = Acon;
			li.userID = AUserID;
			li.storageID = AStorageID;
			li.UserName = AUserName;
			li.FormatStr = "#,##0.00";
			TearcherSearch(&li,frmMain->ClientHandle);
}
//---------------------------------------------------------------------------


