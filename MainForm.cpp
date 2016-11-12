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

     }else             //���Ӵ���
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
	 //����ʾ������
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
	MessageBoxA(0,"��Ȩ�޲�����ģ��,�������Ա��ϵ!","����",MB_ICONASTERISK);
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
	AnsiString sname = "�����ڵ�¼����:" + AStorageName ;
	stgname->Caption = sname;

        //����MSg

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
        InitQF();//�Ƿ����ֹ�Ӧ��
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
			" where  ((sys_action.actionname = '��������'  and SYS_InforMessage.type  in(2,3)) "
			" or ((sys_action.actionname = '��������' or sys_action.actionname = '�ɹ�����' or sys_action.actionname ='��������') and SYS_InforMessage.type = 1)) "
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
		j = MessageInfo->IndexOf(MsgName);    //ȡ��Ҫ��ʾ��panel
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

      if(!strcmp(lsname, enumClass)) // �������Ƿ�ƥ��
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
          /*  if(ShowMsg(Handle ,"��δ�رմ��ڣ��Ƿ��˳���,ȷ�Ͻ��ر�����ϵͳ��",1)==1)
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
	//�ɹ�����
    if (!FindDog(version)) {
        return;
	}



            if (CheckPower("��ʡ���ɹ�") ) {
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
            DisVisable();  //����ʾ���˵�
            }else
            {
               ShowNoPower();
            }


}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::storageExecute(TObject *Sender)
{
	//������
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
	if (CheckPower("��⴦��")) {
		ManageStorage(&li,frmMain->ClientHandle);
                DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::storagebackExecute(TObject *Sender)
{
	//����˻�����
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

	if (CheckPower("����˻�")) {
		ManageReturnStorage(&li,frmMain->ClientHandle);
                DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ZNreturnExecute(TObject *Sender)
{
	//�����˻�
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
	if (CheckPower("�����˻�")) {
		ZNReturnStock(&li,frmMain->ClientHandle);
                DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::sqPeisongExecute(TObject *Sender)
{
	//��������
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("��������")) {
		LandInfo li;
		li.app = Application;
		li.con = Acon;
		li.userID = AUserID;
		li.storageID = AStorageID;
		li.UserName = AUserName;
                if (CheckPower("���ϴ���")) {
                  li.qfclient= true;
                }else  li.qfclient= false;
		DiaoBo(&li,0,"",frmMain->ClientHandle);
                DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::zdpeisongExecute(TObject *Sender)
{
	//��������
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("��������")) {
		LandInfo li;
		li.app = Application;
		li.con = Acon;
		li.userID = AUserID;
		li.storageID = AStorageID;
		li.UserName = AUserName;
                if (CheckPower("���ϴ���")) {
                  li.qfclient= true;
                }else  li.qfclient= false;
		DiaoBo(&li,1,"",frmMain->ClientHandle);
                DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::RetailExecute(TObject *Sender)
{
	//POS���۹���
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

	if (CheckPower("POS����")) {
			//���������ۿ�
//ǰ̨�ҵ�
////ǰ̨�˻�
//ǰ̨�����ۼ�

	   if (CheckPower("���������ۿ�")) {
		powerlist="1";
	   }else powerlist="0";

	   if (CheckPower("ǰ̨�ҵ�")) {
		powerlist=powerlist+"1";
	   }else powerlist=powerlist+"0";

	   if (CheckPower("ǰ̨�˻�")) {
		powerlist=powerlist+"1";
	   }else powerlist=powerlist+"0";

	   if (CheckPower("ǰ̨�����ۼ�")) {
		powerlist=powerlist+"1";
	   }else powerlist=powerlist+"0";

	 

		ManageRetail(powerlist,&li,frmMain->ClientHandle);


                DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::retailbackExecute(TObject *Sender)
{
	//�����˻�
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
	if (CheckPower("POS�˻�")) {
		ManageReturnRetail(&li,frmMain->ClientHandle);
                DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::POSjiaobanExecute(TObject *Sender)
{
	//jiaojieban ����Ա���Ӱ�
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
            MessageBoxA(0,"�����������","����",MB_ICONERROR);
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
		sql = "insert into sys_log (EventType,SourceFrom,EventDate,EventUser,EventMessage,stgName) values('��Ϣ','����',getdate()," + IntToStr(AUserID) + ",'����Ա����'," + IntToStr(AStorageID) + ")" ;

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
	if (CheckPower("��������") ) {
		BIOrderManage(&li,0,frmMain->ClientHandle);
                DisVisable();  //����ʾ���˵�
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
	if (CheckPower("��������")) {
		ManageMarketing(&li,frmMain->ClientHandle);
                DisVisable();  //����ʾ���˵�
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
	if (CheckPower("�����˻�")) {
		ManageReturnMarketing(&li,frmMain->ClientHandle);
                DisVisable();  //����ʾ���˵�
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
	if (CheckPower("����ѯ")) {
		LandInfo li;
		li.app = Application;
		li.con = Acon;
		li.userID = AUserID;
		li.storageID = AStorageID;
                li.qfsupply= Qfsupplier;
                li.qfclient = Qfclient;
		BusinessQuery(Application, &li, 3,frmMain->ClientHandle);
       DisVisable();  //����ʾ���˵�
	}
	else
	{
		  ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::OrderSearchExecute(TObject *Sender)
{
	//������ѯ
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
	if (CheckPower("������ѯ")) {
		QryOderNote(&li,frmMain->ClientHandle);
                DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::stocksearchExecute(TObject *Sender)
{
	//�ɹ���ѯ
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
	if (CheckPower("�ɹ���ѯ")) {
		QryProcureNote(&li,frmMain->ClientHandle);
                DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::rikusearchExecute(TObject *Sender)
{
	//����ѯ
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
	if (CheckPower("����ѯ")) {
		QueryStorageNote(&li,frmMain->ClientHandle);
                DisVisable();  //����ʾ���˵�
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
	if (CheckPower("������ѯ")) {
		QueryWsaleNote(&li,frmMain->ClientHandle);
                DisVisable();  //����ʾ���˵�
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
	if (CheckPower("POS���۲�ѯ")) {
		QueryRetailNote(&li,frmMain->ClientHandle);
                DisVisable();  //����ʾ���˵�
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
	if (CheckPower("�̵��ѯ")) {
		LandInfo li;
		li.app = Application;
		li.con = Acon;
		li.userID = AUserID;
		li.storageID = AStorageID;
                li.qfsupply= Qfsupplier;
                li.qfclient = Qfclient;
		QryCheckNote(&li,frmMain->ClientHandle);
                DisVisable();  //����ʾ���˵�
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::peishongsearchExecute(TObject *Sender)
{
	//���Ͳ�ѯ
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
	if (CheckPower("���Ͳ�ѯ")) {
		QryPeisongNote(&li,frmMain->ClientHandle);
                DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::financestartExecute(TObject *Sender)
{
	//  ��λ�����ڳ�
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("��Ӧ�������ڳ�")) {
		Tfrmsupplierandclient * frm = new Tfrmsupplierandclient(Application,Acon,1,AStorageID);
		frm->ShowModal();
		delete frm;
                DisVisable();  //����ʾ���˵�
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
	if (CheckPower("�ͻ������ڳ�")) {
		Tfrmsupplierandclient * frm = new Tfrmsupplierandclient(Application,Acon,2,AStorageID);
		frm->Show();
                DisVisable();  //����ʾ���˵�
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
	//��Ӧ����������   0
	if (!FindDog(version)) {
        return;
	}
	if (CheckPower("��Ӧ����������")) {
		Tfrmwanglaizhang * frm = new Tfrmwanglaizhang(Application,1);      //��Ӧ������
		LandInfo li;
		li.app = Application;
		li.con = Acon;
		li.userID = AUserID;
		li.storageID = AStorageID;
                li.qfsupply= Qfsupplier;
                li.qfclient = Qfclient;
		frm->init(&li);
		frm->Show();
                DisVisable();  //����ʾ���˵�
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
	if (CheckPower("�ͻ�ס������")) {
		Tfrmclientwanglai * frm = new Tfrmclientwanglai(Application,2);      //�ͻ�����
		LandInfo li;
		li.app = Application;
		li.con = Acon;
		li.userID = AUserID;
		li.storageID = AStorageID;
                li.qfsupply= Qfsupplier;
                li.qfclient = Qfclient;
		frm->init(&li);
		frm->Show();
                DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::yihutotalExecute(TObject *Sender)
{
	//Ӧ������
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("Ӧ������")) {
		Taccountyfhz *frm = new Taccountyfhz(Application,1,Acon,AStorageID);
		frm->username = AUserName;
		frm->stogName = AStorageName ;
                frm->labtitle->Caption = AStorageName;
		frm->Show();
                DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::yingfudetailExecute(TObject *Sender)
{
	//��Ӧ��Ӧ����ϸ
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("Ӧ����ϸ")) {
		TAccDetail *frm = new TAccDetail(Application,1,Acon,AStorageID);
		frm->stogName = AStorageName ;
		frm->Maker = AUserName ;
		frm->Show();
                DisVisable();  //����ʾ���˵�
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
	if (CheckPower("Ӧ�ջ���")) {
		TAccountDoe *frm = new TAccountDoe(Application,2,Acon,AStorageID);
		frm->username = AUserName;
		frm->stogName = AStorageName ;
                frm->labtitle->Caption =AStorageName ;
		frm->Show();
                DisVisable();  //����ʾ���˵�
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
	if (CheckPower("Ӧ����ϸ")) {
		TAccDetail *frm = new TAccDetail(Application,2,Acon,AStorageID);
		frm->stogName = AStorageName ;
		frm->Maker = AUserName ;
		frm->Show();
                DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SupplierjieShuanSearchExecute(TObject *Sender)
{
	//	5��	��Ӧ�̽����ѯ
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("��Ӧ�̽����ѯ")) {
		TAccQuery * frm = new TAccQuery(Application,1,Acon,AStorageID,AMaster);
		frm->Show();
                DisVisable();  //����ʾ���˵�
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
	if (CheckPower("�ͻ������ѯ")) {
		TAccQuery * frm = new TAccQuery(Application,2,Acon,AStorageID,AMaster);
		frm->Show();
                DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SupplierjieshuanExecute(TObject *Sender)
{
	//�������
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("��Ӧ�̽���")) {
		Tfrmbalance *frm = new Tfrmbalance(Application,Acon,AUserID,1,AStorageID,AMaster);

              //  frm->
		frm->Show();
                DisVisable();  //����ʾ���˵�
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
	if (CheckPower("�ͻ�����")) {
		Tfrmbalance *frm = new Tfrmbalance(Application,Acon,AUserID,2,AStorageID,AMaster);
                 frm->qfclient=Qfclient;
                 frm->qfsupplier=Qfsupplier;
		frm->Show();
                DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SupplierInfoExecute(TObject *Sender)
{
	//��Ӧ������
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("��Ӧ������")) {
		LandInfo li;
		li.app = Application;
		li.con = Acon;
		li.userID = AUserID;
		li.storageID = AStorageID;
                li.qfsupply= Qfsupplier;
                li.qfclient = Qfclient;
		//1Ϊ��Ӧ��
		TSuppMana * frm = new TSuppMana(Application,1,Acon,AStorageID,Qfsupplier,Qfclient);
                if (CheckPower("��Ӧ����ͣ��"))
                {
                      frm->Supplierpower =true;
                  }else {
                      frm->Supplierpower=false;
                }
               // frm->qfsupplier= Qfsupplier;
		frm->Show();
                DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ClientInfoExecute(TObject *Sender)
{
	//�ͻ�����
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("�ͻ�����")) {
		LandInfo li;
		li.app = Application;
		li.con = Acon;
		li.userID = AUserID;
		li.storageID = AStorageID;
                li.qfsupply= Qfsupplier;
                li.qfclient = Qfclient;
		//1Ϊ��Ӧ��
		TSuppMana * frm = new TSuppMana(Application,2,Acon,AStorageID,Qfsupplier,Qfclient);
                 if (CheckPower("��Ӧ����ͣ��"))
                {
                      frm->Clientpower =true;
                  }else {
                      frm->Clientpower=false;
                }
                frm->qfclient=Qfclient;
                frm->qfsupplier= Qfsupplier;
		frm->Show();
                DisVisable();  //����ʾ���˵�
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
	if (CheckPower("ҵ��Ա����")) {
		TfrmStaff *frm = new TfrmStaff(Application,Acon,AStorageID);
		frm->ShowModal();
		delete frm;
                DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::MemberInfoExecute(TObject *Sender)
{
	//��Ա����
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("��Ա����")) {
		TfrmMember *frm = new TfrmMember(Application,Acon);
		frm->userid = AUserID;
		frm->stgid = AStorageID;
		frm->Show();
                DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::MemberchongzhiExecute(TObject *Sender)
{
	//��Ա��ֵ
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("��Ա��ֵ")) {
		TfrmMemberResult *frm = new TfrmMemberResult(Application,Acon);
		frm->userid = AUserID;
		frm->stgid = AStorageID;
		frm->Show();
                DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::MemberchongziSearchExecute(TObject *Sender)
{
	//��ֵ��¼��ѯ
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("��Ա��ֵ��ѯ")) {
		TFormRecordQuery *frm = new TFormRecordQuery(Application,Acon,AUserID,AStorageID);
		frm->Show();
                DisVisable();  //����ʾ���˵�
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
	if (CheckPower("�������")) {
		TfrmalarmSet *frm = new TfrmalarmSet(Application,Acon,AStorageID,AUserID);
		frm->Show();
                DisVisable();  //����ʾ���˵�
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
	if (CheckPower("��λ����")) {
		Tfrmadjust *frm = new Tfrmadjust(Application,Acon,&li);
		frm->Show();
                DisVisable();  //����ʾ���˵�
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
	if (CheckPower("������")) {
		StockAdjust(&li,frmMain->ClientHandle);
                DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::shikupandianExecute(TObject *Sender)
{
	//����̵�
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
	if (CheckPower("����̵�")) {
		Tfrmcheckstock * frm = new Tfrmcheckstock(Application,Acon ,&li);
		frm->Show();
                DisVisable();  //����ʾ���˵�
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
		ShowMsg(Handle ,"��δ�رյ��Ӵ��ڣ���رպ����ԣ�",3);
		return;
	}
        frmLand = new TfrmLand(Application);
	frmLand->edtPassword->Text = "";
	if (jiaojie == 1) {
		frmLand->Caption = "����Ա���Ӱ�";
	}
	else
	{
    	frmLand->Caption = "��¼";
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

		AnsiString sname = "�����ڵ�¼����:" + AStorageName;
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
	if (MessageBoxA(0,"�Ƿ��˳�ϵͳ��","��ʾ",MB_ICONQUESTION|MB_OKCANCEL )==1 ) {
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
	//�����Ϣ����
	if (!FindDog(version)) {
        return;
	}
	if (CheckPower("��ֹ���")) {
		SetUpStorageInfo(Application,Acon,AUserID,AStorageID,AMaster,version);
      DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::DanHaoDisplayExecute(TObject *Sender)
{
	//������ʾ����
	if (!FindDog(version)) {
        return;
	}
	if (CheckPower("������ʾ����")) {
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
				MessageBoxA(0,"�����������!","��ʾ",MB_ICONASTERISK);
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
	//���۴�ӡ
	if (!FindDog(version)) {
        return;
	}
	if (CheckPower("���۴�ӡ")) {
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
	//����̧ͷ
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("��ӡ��Ϣ����")) {
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
	if (CheckPower("��־��ѯ")) {
		TfrmLog *frm = new TfrmLog(Application,Acon,AUserID,AStorageID);
		frm->Show();
                DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::OrderControlExecute(TObject *Sender)
{
	//����ҵ�����
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("����ҵ�����")) {
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
	//�ɹ�ҵ�����
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("�ɹ�ҵ�����")) {
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
	//���ҵ�����
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("���ҵ�����")) {
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
	if (CheckPower("����ҵ�����")) {
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
	//����ҵ�����
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("����ҵ�����")) {
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
	//����ҵ�����
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("����ҵ�����")) {
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
	//����ҵ�����
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("���Ԥ������")) {
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
	//���������
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("���������")) {
		ManagePress(Application, Acon,frmMain->ClientHandle);
                DisVisable();  //����ʾ���˵�
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::breedTypeExecute(TObject *Sender)
{
	//ͼ��������
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("ƷĿ������")) {
		ManageBookType(Application, Acon,frmMain->ClientHandle);
                DisVisable();  //����ʾ���˵�
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
	if (CheckPower("�������")) {
		TMemberAreaSet * frm = new TMemberAreaSet(Application,Acon,AStorageID);
		frm->ShowModal();
		delete frm;
                DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::memberclassExecute(TObject *Sender)
{
	//��Ա����
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("��Ա����")) {
		Tfrmmemclassmg *frm = new Tfrmmemclassmg(Application,Acon);
		frm->ShowModal();
		delete frm;
                DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::StorageInfoExecute(TObject *Sender)
{
	//��λ����
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("��λ����") ) {
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
                DisVisable();  //����ʾ���˵�
	}
	else
	{
	   ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SupplierClassExecute(TObject *Sender)
{
	//��Ӧ�����
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("��Ӧ�̷���")) {
		Tfrmcustomertype *frm = new Tfrmcustomertype(Application,Acon,1,AStorageID);
		frm->ShowModal();
		delete frm;
                DisVisable();  //����ʾ���˵�
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
	if (CheckPower("�ͻ�����")) {
		Tfrmcustomertype *frm = new Tfrmcustomertype(Application,Acon,2,AStorageID);
		frm->ShowModal();
		delete frm;
                DisVisable();  //����ʾ���˵�
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
	//ͼ��ƷĿ����
	if (!FindDog(version)) {
        return;
	}
	if (CheckPower("ͼ��Ŀ¼����") ) {
		CatalogKan(Application, Acon,AStorageID,AUserID,frmMain->ClientHandle,version);
       DisVisable();  //����ʾ���˵�
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::catalogMakeExecute(TObject *Sender)
{
	//Ŀ¼����
	if (!FindDog(version)) {
        return;
	}
	if (CheckPower("Ŀ¼����") ) {
		Catalogbuilt(Application, Acon,frmMain->ClientHandle);
                DisVisable();  //����ʾ���˵�
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::catalogneworrecExecute(TObject *Sender)
{
	//�¼���Ŀ
	if (!FindDog(version)) {
        return;
	}
	if (CheckPower("�¼���Ŀ") ) {
		Catalogneworrec(Application, Acon,AStorageID,AUserID,frmMain->ClientHandle);
                DisVisable();  //����ʾ���˵�
	}else
	{                                    //TApplication* app, TADOConnection* con,int stgid,int userid,HWND MainHandle
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::qikanguanliExecute(TObject *Sender)
{
	//�ڿ�����
	if (!FindDog(version)) {
        return;
	}
	if (CheckPower("�ڿ�Ŀ¼����") ) {
		QiKanguanli(Application, Acon,AStorageID,frmMain->ClientHandle,version);
                DisVisable();  //����ʾ���˵�
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::MutibookExecute(TObject *Sender)
{
	//����ϲ�
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("����ϲ�")) {
		Multibook(Application,Acon,AStorageID,AUserID,frmMain->ClientHandle);
       DisVisable();  //����ʾ���˵�
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
	//����Ա����
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("����Ա����")) {
		Tfrmuser * frm = new Tfrmuser(Application,Acon,AUserName,AStorageID,AUserID);
		frm->ShowModal();
		delete frm;
                DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::rolemanageExecute(TObject *Sender)
{
	//��ɫ����
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("��ɫ����")) {
		Tfrmgroup * frm = new Tfrmgroup(Application,Acon,AStorageID,AUserID);
		frm->ShowModal();
		delete frm;
                DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::PowerSetExecute(TObject *Sender)
{
	//Ȩ�޹���
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("Ȩ������")) {
		Tfrmpurview * frm  = new Tfrmpurview(Application,Acon , AStorageID,AUserID);
		frm->ShowModal();
		delete frm;
                DisVisable();  //����ʾ���˵�
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
		MessageBoxA(0,"ֻ���ܵ������Ա���ܽ��и������ã�","��ʾ",MB_ICONWARNING);
		return;
	}
	if (CheckPower("���껥��Ȩ�޹���")) {
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
	//�������
	if (!FindDog(version)) {
		return;
	}
	LandInfo li;
	li.app = Application;
	li.con = Acon;
	li.userID = AUserID;
	li.storageID = AStorageID;
	if (CheckPower("�����������")){
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
	if (CheckPower("����������")) {
		DiscountSales(Application, Acon,AStorageID);
                DisVisable();  //����ʾ���˵�
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
	if (CheckPower("���۹��������")) {
		LandInfo li;
		li.app = Application;
		li.con = Acon;
		li.userID = AUserID;
		li.storageID = AStorageID;
		TfrmMonerydiscount *frm = new TfrmMonerydiscount(Application,Acon,AStorageID) ;
		frm->Show();
                DisVisable();  //����ʾ���˵�
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
	if (CheckPower("��Ա���͵�Ʒ����")) {
		MemberDiscount(Application, Acon,AStorageID);
                DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::MemberjifenExecute(TObject *Sender)
{
	//��Ա���ֹ���
	if (!FindDog(version)) {
		return;
	}
	if (!AMaster) {
		MessageBoxA(0,"ֻ���ܵ����Ȩ�޲�����ģ��!","��ʾ",MB_ICONASTERISK);
		return;
	}
	if (CheckPower("��Ա���ֹ���")) {
		LandInfo li;
		li.app = Application;
		li.con = Acon;
		li.userID = AUserID;
		li.storageID = AStorageID;
		TfrmMemberjifen *frm = new TfrmMemberjifen(Application,Acon) ;
		frm->stgid = AStorageID ;
		frm->ShowModal();
		delete frm;
                DisVisable();  //����ʾ���˵�
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
	if (CheckPower("��Ա������Ԥ���ۿ�")) {
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
	if (CheckPower("������Ʒ�ۿ�")) {
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
	if (CheckPower("���������ۿ�")) {
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
	//�����ֳ�����
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("�����ֳ�����")) {
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
	//���������
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("���������")) {
		PurchaseSalesInventoryAnalysis(Application, Acon,AStorageID);
   DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::saletimehuizhongExecute(TObject *Sender)
{
	//����ʱ�λ���ͳ��
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("����ʱ�λ���ͳ��")) {

                if(CheckPower("����ʱ�γɱ��鿴"))
                {
                      xiaoshou(Application,Acon,AStorageID,true);
                      DisVisable();  //����ʾ���˵�
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
	//ҵ��������
	if (!FindDog(version)) {
		return;
	}
   if (CheckPower("ҵ�����а�")) {
		Yewupaihang(Application,Acon,AStorageID);
                DisVisable();  //����ʾ���˵�
   }
   else
   {
		ShowNoPower();
   }
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::retailhuizhongfengxieExecute(TObject *Sender)
{
	//���ۻ��ܷ���
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("���ۻ��ܷ���")) {
		RetailSummary(Application, Acon,AStorageID);
                DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------



void __fastcall TfrmMain::clientjieduanjiesuanExecute(TObject *Sender)
{
	// �ͻ��׶ν������
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("�ͻ������ڽ������")) {
		ClientStageClearing(Application, Acon,AStorageID);
                DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::supplierjieduanjiesuanExecute(TObject *Sender)
{
	// ��Ӧ�̽׶ν������
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("��Ӧ�������ڽ������")) {
		SupplierStageClearing(Application, Acon,AStorageID);
                DisVisable();  //����ʾ���˵�
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
	if (CheckPower("��Ʒ����")) {
		Siglebook(&li,frmMain->ClientHandle);
                DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::paihangfenxiExecute(TObject *Sender)
{
	//������������ë������
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("������������ë������")) {
		SalesAnalysis(Application, Acon,AStorageID);
                DisVisable();  //����ʾ���˵�
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::manualExecute(TObject *Sender)
{
	//�û��ֲ�
	AnsiString path;
	path =  ExtractFilePath(Application->ExeName);
	path = path + "help.doc";
	ShellExecute(NULL,"open",path.c_str() ,"","",SW_SHOW);
        DisVisable();  //����ʾ���˵�
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::systemupdateExecute(TObject *Sender)
{
	//ϵͳ����
	Tfrmshengji * frm = new Tfrmshengji(Application);
	frm->ShowModal();
        DisVisable();  //����ʾ���˵�

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::aboutExecute(TObject *Sender)
{
	//���ڱ����
	TfrmAboutsoftware *frm = new TfrmAboutsoftware(Application);
	frm->ShowModal();
        DisVisable();  //����ʾ���˵�
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
	char   dayss[7][10]   =   { "������ ", "����һ ",   "���ڶ� ",   "������ ",   "������ ",   "������ ",   "������ "};
	dateTime=DateTimeToStr(Now());

   title = "��ӭ����"+AUserName+"��������"+FormatDateTime("YYYY��mm��dd��",Date())+"��"+dayss[dateTime.DayOfWeek()-1];
   return title;

}
//---------------------------------------------------------------------------




void __fastcall TfrmMain::msg1Click(TObject *Sender)
{
    	LandInfo li;
	int type =0;
	int ID;
        int MsgType; //���ȥ��,�Ƿ���Ҫ����
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
		   case 2:         //��������
                                sql = "select sys_user.* from sys_user join SYS_UserGroup on SYS_UserGroup.userid = SYS_User.id "
                                " join SYS_GroupAction on SYS_GroupAction.groupid = SYS_UserGroup.groupid "
                                " join SYS_Action on SYS_GroupAction.actionid = sys_action.code "
                                " where  ((sys_action.actionname = '��������') or (sys_action.actionname = '��������')) and SYS_User.id = " + IntToStr(AUserID) ;
                                aq = new TADOQuery(Application);
                                aq->Connection = Acon;
                                aq->Close();
                                aq->SQL ->Clear();
                                aq->SQL->Add(sql);
                                aq->Open();
                                if (aq->IsEmpty() ) {
                                     ShowMsg(Handle ,"��ȷ���Ƿ���д˹��ܵĲ���Ȩ�ޣ�",3);
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

                                                        ShowMsg(Handle ,"Ϊ�˱�֤�����������ʵ��Ч��\nһ���û�ͬʱֻ�����һ���������ͻ���������ģ�飡",3);
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
				DiaoBo(&li,10,DanHao,frmMain->ClientHandle); //��Ϣ���ȥ��,��������Ϊ10
                                if (MsgType==0) {
                                        adosp->Parameters->ParamByName("@ID")->Value = ID;
			         	adosp->ExecProc();
                                }

                                break;
		   case 3:         //��������

                                  sql = "select sys_user.* from sys_user join SYS_UserGroup on SYS_UserGroup.userid = SYS_User.id "
                                " join SYS_GroupAction on SYS_GroupAction.groupid = SYS_UserGroup.groupid "
                                " join SYS_Action on SYS_GroupAction.actionid = sys_action.code "
                                " where  ((sys_action.actionname = '��������') or (sys_action.actionname = '��������')) and SYS_User.id = " + IntToStr(AUserID) ;
                                aq = new TADOQuery(Application);
                                aq->Connection = Acon;
                                aq->Close();
                                aq->SQL ->Clear();
                                aq->SQL->Add(sql);
                                aq->Open();
                                if (aq->IsEmpty() ) {
                                     ShowMsg(Handle ,"��ȷ���Ƿ���д˹��ܵĲ���Ȩ�ޣ�",3);
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

                                                        ShowMsg(Handle ,"Ϊ�˱�֤�����������ʵ��Ч��\nһ���û�ͬʱֻ�����һ���������ͻ���������ģ�飡",3);
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
				DiaoBo(&li,11,DanHao,frmMain->ClientHandle);  //��Ϣ���ȥ��,�������� Ϊ11
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
                                " where  ((sys_action.actionname = '��������') or (sys_action.actionname = '��������')) and SYS_User.id = " + IntToStr(AUserID) ;
                               aq = new TADOQuery(Application);
                                aq->Connection = Acon;
                                aq->Close();
                                aq->SQL ->Clear();
                                aq->SQL->Add(sql);
                                aq->Open();
                                if (aq->IsEmpty() ) {
                                     ShowMsg(Handle ,"��ȷ���Ƿ���д˹��ܵĲ���Ȩ�ޣ�",3);
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

                                                        ShowMsg(Handle ,"Ϊ�˱�֤�����������ʵ��Ч��\nһ���û�ͬʱֻ�����һ���������ͻ���������ģ�飡",3);
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
                                " where  ((sys_action.actionname = '��������') or (sys_action.actionname = '��������')) and SYS_User.id = " + IntToStr(AUserID) ;
                                aq = new TADOQuery(Application);
                                aq->Connection = Acon;
                                aq->Close();
                                aq->SQL ->Clear();
                                aq->SQL->Add(sql);
                                aq->Open();
                                if (aq->IsEmpty() ) {
                                     ShowMsg(Handle ,"��ȷ���Ƿ���д˹��ܵĲ���Ȩ�ޣ�",3);
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

                                                        ShowMsg(Handle ,"Ϊ�˱�֤�����������ʵ��Ч��\nһ���û�ͬʱֻ�����һ���������ͻ���������ģ�飡",3);
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
/*   	//�������
	if (!FindDog(version)) {
        return;
	}
	if (CheckPower("�������")) {
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
    	//�ĵ�����
	 if(!FindDog(version)) {
        return;
	}
	if (CheckPower("�ĵ�����")) {
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
	//�ľ�Ŀ¼����
	if (!FindDog(version)) {
        return;
	}
	if (CheckPower("�ľ�Ŀ¼����") ) {
		WenJuguanli(Application, Acon,AStorageID,AUserID,frmMain->ClientHandle);
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::clientadddotExecute(TObject *Sender)
{
	//�ͻ��ۿۼӵ�����
	if (!FindDog(version)) {
		return;
	}
	if (CheckPower("�ͻ��ۿۼӵ�����")) {
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
	//�¼���Ŀ
	if (!FindDog(version)) {
        return;
	}

        if (version==0) {
           	if (CheckPower("��ݷ���") ) {
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
	if (CheckPower("��ʡ������") ) {
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
  if (CheckPower("�ͻ���Ʒ�ۿ�") ) {
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
            if (CheckPower("��Ա���Ĳ�ѯ") ) {
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
       	//�ɹ�����
    if (!FindDog(version)) {
        return;
	}
        if (version==0) {
               N66->Click();
        }else
        {
            if (CheckPower("ʡ���ɹ�") ) {
            LandInfo li;
            li.app = Application;
            li.con = Acon;
            li.userID = AUserID;
            li.storageID = AStorageID;
            li.UserName=AUserName;
            DaiXiao(&li,frmMain->ClientHandle);
            DisVisable();  //����ʾ��
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
   if (CheckPower("ʡ������") ) {
	LandInfo li;
	li.app = Application;
	li.con = Acon;
	li.userID = AUserID;
	li.storageID = AStorageID;
        li.UserName =AUserName ;
       DiaoxiaoCaigouFahuo(&li,frmMain->ClientHandle);
       DisVisable();  //����ʾ���˵�
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
   if (CheckPower("ʡ���ɹ���ѯ") ) {
	LandInfo li;
	li.app = Application;
	li.con = Acon;
	li.userID = AUserID;
	li.storageID = AStorageID;
       QryProcureShenDai(&li,frmMain->ClientHandle);
       DisVisable();  //����ʾ���˵�
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
      	if (CheckPower("�������ܲ�ѯ")) {
            	LandInfo li;
	li.app = Application;
	li.con = Acon;
	li.userID = AUserID;
	li.storageID = AStorageID;
        li.UserName=AUserName;

       pixiaohuizhong(&li,frmMain->ClientHandle);
       DisVisable();  //����ʾ���˵�
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
    	//���ս���
	if (!FindDog(version)) {
        return;
	}


        	LandInfo li;
		li.app = Application;
		li.con = Acon;
		li.userID = AUserID;
		li.storageID = AStorageID;
                li.UserName= AUserName;
	if (CheckPower("���۽��˲�ѯ")) {
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
//�����ռ���
   if (CheckPower("��Ӫҵ����֧") ) {
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
   if (CheckPower("��Ӫ������֧��ѯ") ) {
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
        if(version==0)//���۰�
        {
           Label1->Caption="��Ӫҵ����֧";
           Label2->Caption="��ݷ���";
           Label3->Caption="��Ӫҵ�Բ�ѯ";
           Label4->Caption="��Ʒ����";

           N54->Visible=false;
           N56->Visible=false;
           N57->Visible=false;
           N52->Visible=false;
        }





}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::Image8Click(TObject *Sender)
{
	//�ɹ�����
    if (!FindDog(version)) {
        return;
	}

       if (version==0) {
               N62->Click();
        }else
        {

            if (CheckPower("��ʡ���ɹ�") ) {
            LandInfo li;
            li.app = Application;
            li.con = Acon;
            li.userID = AUserID;
            li.storageID = AStorageID;
            li.UserName = AUserName;
            li.FormatStr = "#,##0.00";
			ProcureManage(&li,frmMain->ClientHandle);
            DisVisable();  //����ʾ���˵�
            }else
            {
               ShowNoPower();
            }
            }
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::N67Click(TObject *Sender)
{
//��������

   if (CheckPower("��������") ) {
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
//��ʦ����
  Tfrmteachermanager * frm = new Tfrmteachermanager(Application);
  frm->Acon=Acon;
  frm->ShowModal();
  delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::N70Click(TObject *Sender)
{
   //��ʦ��������

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


