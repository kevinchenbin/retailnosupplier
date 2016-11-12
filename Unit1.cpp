//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "LandForm.h"
#include "global.h"
#include "pdtypes.h"
#include "bsadmin\bsadmin.h"
#include "shlwapi.h"
#include "tchar.h"
#include "PwdForm.h"
#include "Print.h"
#include "bsquery\bsquery.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
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
	Acon = frmLand->conLand ;
	AUserID = frmLand->GetUserID();
	AStorageName = frmLand->cbstorage->Text;
	AStorageID = frmLand->GetStorageID();
	AUserName = frmLand->GetUserNameA();
	AMaster =  frmLand->GetMaster();

	/*HRGN   hRgn   =   NULL;
	for(int   n=0;   n <pan-> ControlCount;   n++)   {
		TControl*   Control   =   pan-> Controls[n];
		TRect   Rect   =   Control-> BoundsRect;
		HRGN   hRgn1   =   CreateRectRgnIndirect(&Rect);
		if   (hRgn   ==   NULL)
				hRgn   =   hRgn1;
		else {
				CombineRgn(hRgn,hRgn,hRgn1,RGN_OR);
				DeleteObject(hRgn1);
		}
	}
	SetWindowRgn(pan-> Handle,   hRgn,   TRUE);
	DeleteObject(hRgn);*/

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
	AnsiString path =  ExtractFilePath(Application->ExeName);
	AnsiString Name;
	Name = path + "image\\��ͼ\\��ͼ-1.png";
	TPngImage * imag;
	imag = new TPngImage();
	imag->LoadFromFile(Name);
	imageui->Picture->Graphic = imag;

	imag = new TPngImage();
	Name = path + "image\\��ͼ\\logo_03.png";
	imag->LoadFromFile(Name);
	Image2->Picture->Graphic = imag;

	imag = new TPngImage();
	Name = path + "image\\��ͼ\\��ͼ-2.png";
	imag->LoadFromFile(Name);
	imagebj->Picture->Graphic = imag;

	imag = new TPngImage();
	Name = path + "image\\����ͼ\\�ɹ�����\\1.png";
	imag->LoadFromFile(Name);
	Image6->Picture->Graphic = imag;

	imag = new TPngImage();
	Name = path + "image\\����ͼ\\�ɹ�����\\3.png";
	imag->LoadFromFile(Name);
	Image5->Picture->Graphic = imag;

	imag = new TPngImage();
	Name = path + "image\\�·�ͼ��\\����ƽ̨.png";
	imag->LoadFromFile(Name);
	Image8->Picture->Graphic = imag;

	imag = new TPngImage();
	Name = path + "image\\�·�ͼ��\\�ڲ�����.png";
	imag->LoadFromFile(Name);
	Image9->Picture->Graphic = imag;

	imag = new TPngImage();
	Name = path + "image\\�·�ͼ��\\�������.png";
	imag->LoadFromFile(Name);
	Image10->Picture->Graphic = imag;

	imag = new TPngImage();
	Name = path + "image\\�·�ͼ��\\�ĵ�����.png";
	imag->LoadFromFile(Name);
	Image11->Picture->Graphic = imag;

	imag = new TPngImage();
	Name = path + "image\\����ͼ\\�ɹ�����\\2.png";
	imag->LoadFromFile(Name);
	Image7->Picture->Graphic = imag;

	imag = new TPngImage();
	Name = path + "image\\����ͼ\\�ɹ�����\\2.png";
	imag->LoadFromFile(Name);
	Image4->Picture->Graphic = imag;

	imag = new TPngImage();
	Name = path + "image\\����ͼ\\�ɹ�����\\1.png";
	imag->LoadFromFile(Name);
	Image1->Picture->Graphic = imag;

	imag = new TPngImage();
	Name = path + "image\\����ͼ\\�ɹ�����\\1.png";
	imag->LoadFromFile(Name);
	Image3->Picture->Graphic = imag;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::imageuiMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	/*if(Button == mbLeft)
	{
		ReleaseCapture();
		SendMessage( Handle, WM_NCLBUTTONDOWN, HTCAPTION, 0);
	}  */
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ClientWndProc(TMessage&   Message)
{
	 //����ʾ������
	ShowScrollBar(Form1->ClientHandle,SB_BOTH,false);
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
void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------


void TForm1::TPclick(int tt)
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


void __fastcall TForm1::imagecg1Click(TObject *Sender)
{
	TPclick(1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::imagecw1Click(TObject *Sender)
{
	TPclick(8);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::imagecx1Click(TObject *Sender)
{
	TPclick(7);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::imageps1Click(TObject *Sender)
{
	TPclick(2);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::imagefh1Click(TObject *Sender)
{
	TPclick(3);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::imagels1Click(TObject *Sender)
{
	TPclick(4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::imagekc1Click(TObject *Sender)
{
	TPclick(5);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::imagekh1Click(TObject *Sender)
{
	TPclick(6);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::tbcgClick(TObject *Sender)
{
	TPclick(1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::tbpsClick(TObject *Sender)
{
	TPclick(2);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::tbfhClick(TObject *Sender)
{
	TPclick(3);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::tblsClick(TObject *Sender)
{
	TPclick(4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::tbkcClick(TObject *Sender)
{
	TPclick(5);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::tbkhClick(TObject *Sender)
{
	TPclick(6);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::tbcxClick(TObject *Sender)
{
	TPclick(7);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::tbcwClick(TObject *Sender)
{
	TPclick(8);
}
//---------------------------------------------------------------------------

BOOL TForm1::CheckPower(String ModalName)
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
void TForm1::ShowNoPower()
{
	MessageBoxA(0,"��Ȩ�޲�����ģ��,�������Ա��ϵ!","����",MB_ICONASTERISK);
}

//---------------------------------------------------------------------------
void TForm1::GetPowerList(int UserID)
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
void __fastcall TForm1::FormShow(TObject *Sender)
{
	GetPowerList(AUserID);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	//���Ӵ���ȫ���ر�
	HWND hWnd = ::GetWindow(::GetWindow(ClientHandle, GW_CHILD), GW_HWNDFIRST);
	while (hWnd != NULL)
	{

		if(MessageBox(0,"��δ�رմ��ڣ��Ƿ��˳���,ȷ�Ͻ��ر�����ϵͳ��" ,"ȷ��" ,MB_ICONQUESTION|MB_OKCANCEL)==1)
		{
			::SendMessage(hWnd, WM_CLOSE, 0, 0);
			Application->ProcessMessages();
			hWnd = ::GetWindow(hWnd, GW_HWNDNEXT);
		}
		else
		{
			Action = caNone;
			return;
		}
	}
	//����Ƿ���δ�رյ��Ӵ���
	bool allclose = false;
	hWnd = ::GetWindow(::GetWindow(ClientHandle, GW_CHILD), GW_HWNDFIRST);
	TCHAR buf[MAX_PATH+1];
	while (hWnd != NULL)
	{
		::ZeroMemory(buf, sizeof(buf));
		if (::GetClassName(hWnd, buf, MAX_PATH) > 0)
		{
			if (StrCmp(_T("TfrmRetailMng"), buf) == 0)
			{
				allclose = true;
				break;
			}
		}
        hWnd = ::GetWindow(hWnd, GW_HWNDNEXT);
	}
	//��������ܹر�������
	if (allclose)
	{
		Action = caNone;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ProcureExecute(TObject *Sender)
{
	//�ɹ�����
    if (!FindDog()) {
        return;
	}
	if (CheckPower("�ɹ�����") ) {
		LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID  = frmLand->GetStorageID();
		li.FormatStr = "#,##0.00";
	ProcureManage(&li,Form1->Handle);
	}else
	{
	   ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::storageExecute(TObject *Sender)
{
	//������
    if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.UserName = frmLand->cbName->Text ;
	li.FormatStr = "#,##0.00";
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("��⴦��")) {
		ManageStorage(&li,Form1->Handle);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::storagebackExecute(TObject *Sender)
{
	//����˻�����
    if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.UserName = frmLand->cbName->Text ;
	li.FormatStr = "#,##0.00";
	li.storageID = frmLand->GetStorageID();

	if (CheckPower("����˻�")) {
		ManageReturnStorage(&li,Form1->Handle);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ZNreturnExecute(TObject *Sender)
{
	//�����˻�
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.UserName = frmLand->cbName->Text ;
	li.FormatStr = "#,##0.00";
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("�����˻�")) {
		ZNReturnStock(&li,Form1->Handle);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::sqPeisongExecute(TObject *Sender)
{
	//��������
	if (!FindDog()) {
		return;
	}
	if (CheckPower("��������")) {
		LandInfo li;
		li.app = Application;
		li.con = frmLand->conLand;
		li.userID = frmLand->GetUserID();
		li.storageID = frmLand->GetStorageID();
		li.UserName = frmLand->GetUserNameA();
		DiaoBo(&li,0,"",Form1->Handle);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::zdpeisongExecute(TObject *Sender)
{
	//��������
	if (!FindDog()) {
		return;
	}
	if (CheckPower("��������")) {
		LandInfo li;
		li.app = Application;
		li.con = frmLand->conLand;
		li.userID = frmLand->GetUserID();
		li.storageID = frmLand->GetStorageID();
		li.UserName = frmLand->GetUserNameA();
		DiaoBo(&li,1,"",Form1->Handle);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RetailExecute(TObject *Sender)
{
	//POS���۹���
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	li.FormatStr = "#,##0.00";
	if (CheckPower("POS����")) {
		ManageRetail(&li,Form1->Handle);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::retailbackExecute(TObject *Sender)
{
	//�����˻�
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	li.FormatStr = "#,##0.00";
	if (CheckPower("POS�˻�")) {
		ManageReturnRetail(&li,Form1->Handle);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::POSjiaobanExecute(TObject *Sender)
{
	//jiaojieban ����Ա���Ӱ�
	if (!FindDog()) {
        return;
	}
	TADOQuery *aq = new TADOQuery(NULL);
	aq->Connection = frmLand->conLand ;
	AnsiString sql;
	sql = "select jiaojiepwd from SYS_StorageInfo where id = " + IntToStr(frmLand->GetStorageID());
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	TfrmPwd *frmpwd = new  TfrmPwd(Application);
	if (frmpwd->ShowModal() == mrOk) {
		if (frmpwd->GetPassword()!= aq->FieldByName("jiaojiepwd")->AsAnsiString) {
            MessageBoxA(0,"�����������","����",MB_ICONERROR);
			delete aq;
			return;
		}

		sql = "select jiaojieprint from SYS_StorageInfo where id = " + IntToStr(frmLand->GetStorageID());
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->FieldByName("jiaojieprint")->AsInteger ) {
			TfrmPrint *frm  = new TfrmPrint(Application);
			frm->RetailjiaojiePrint(frmLand->GetUserID(), frmLand->conLand,frmLand->GetStorageID());
			delete frm;
			//TfrmPrint::RetailjiaojiePrint(frmLand->GetUserID(), frmLand->conLand);
		}
		sql = "insert into sys_log (EventType,SourceFrom,EventDate,EventUser,EventMessage,stgName) values('��Ϣ','����',getdate()," + IntToStr(frmLand->GetUserID()) + ",'����Ա����'," + IntToStr(frmLand->GetStorageID()) + ")" ;

		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		delete aq;
		jiaojie = 1;
		rlogin->Execute();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::OrderExecute(TObject *Sender)
{
	if (!FindDog()) {
		return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.FormatStr = "#,##0.00";
	li.storageID = frmLand->GetStorageID() ;
	if (CheckPower("��������") ) {
		BIOrderManage(&li,0,Form1->Handle);
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SaleExecute(TObject *Sender)
{
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.UserName = frmLand->cbName->Text ;
	li.storageID = frmLand->GetStorageID();
	li.FormatStr = "#,##0.00";
	if (CheckPower("��������")) {
		ManageMarketing(&li,Form1->Handle);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::salebackExecute(TObject *Sender)
{
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	li.FormatStr = "#,##0.00";
	if (CheckPower("�����˻�")) {
		ManageReturnMarketing(&li,Form1->Handle);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StorageSearchExecute(TObject *Sender)
{
	if (!FindDog()) {
        return;
	}
	if (CheckPower("����ѯ")) {
    	LandInfo li;
		li.app = Application;
		li.con = frmLand->conLand;
		li.userID = frmLand->GetUserID();
		li.storageID = frmLand->GetStorageID();
		BusinessQuery(Application, &li, 3);
	}
	else
	{
		  ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::OrderSearchExecute(TObject *Sender)
{
	//������ѯ
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("������ѯ")) {
		QryOderNote(&li);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::stocksearchExecute(TObject *Sender)
{
	//�ɹ���ѯ
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("�ɹ���ѯ")) {
		QryProcureNote(&li);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::rikusearchExecute(TObject *Sender)
{
	//����ѯ
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	li.FormatStr = "#,##0.00";
	if (CheckPower("����ѯ")) {
		QueryStorageNote(&li);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::salesearchExecute(TObject *Sender)
{
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("������ѯ")) {
		QueryWsaleNote(&li);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::posretailsearchExecute(TObject *Sender)
{
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("POS���۲�ѯ")) {
		QueryRetailNote(&li);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::storagechecksearchExecute(TObject *Sender)
{
	if (!FindDog()) {
        return;
	}
	if (CheckPower("�̵��ѯ")) {
		LandInfo li;
		li.app = Application;
		li.con = frmLand->conLand;
		li.userID = frmLand->GetUserID();
		li.storageID = frmLand->GetStorageID();
		QryCheckNote(&li);
	}else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::peishongsearchExecute(TObject *Sender)
{
	//���Ͳ�ѯ
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("���Ͳ�ѯ")) {
		QryPeisongNote(&li);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

