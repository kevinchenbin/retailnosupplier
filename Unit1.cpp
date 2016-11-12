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
	Name = path + "image\\底图\\底图-1.png";
	TPngImage * imag;
	imag = new TPngImage();
	imag->LoadFromFile(Name);
	imageui->Picture->Graphic = imag;

	imag = new TPngImage();
	Name = path + "image\\底图\\logo_03.png";
	imag->LoadFromFile(Name);
	Image2->Picture->Graphic = imag;

	imag = new TPngImage();
	Name = path + "image\\底图\\底图-2.png";
	imag->LoadFromFile(Name);
	imagebj->Picture->Graphic = imag;

	imag = new TPngImage();
	Name = path + "image\\流程图\\采购管理\\1.png";
	imag->LoadFromFile(Name);
	Image6->Picture->Graphic = imag;

	imag = new TPngImage();
	Name = path + "image\\流程图\\采购管理\\3.png";
	imag->LoadFromFile(Name);
	Image5->Picture->Graphic = imag;

	imag = new TPngImage();
	Name = path + "image\\下方图标\\短信平台.png";
	imag->LoadFromFile(Name);
	Image8->Picture->Graphic = imag;

	imag = new TPngImage();
	Name = path + "image\\下方图标\\内部交流.png";
	imag->LoadFromFile(Name);
	Image9->Picture->Graphic = imag;

	imag = new TPngImage();
	Name = path + "image\\下方图标\\任务管理.png";
	imag->LoadFromFile(Name);
	Image10->Picture->Graphic = imag;

	imag = new TPngImage();
	Name = path + "image\\下方图标\\文档管理.png";
	imag->LoadFromFile(Name);
	Image11->Picture->Graphic = imag;

	imag = new TPngImage();
	Name = path + "image\\流程图\\采购管理\\2.png";
	imag->LoadFromFile(Name);
	Image7->Picture->Graphic = imag;

	imag = new TPngImage();
	Name = path + "image\\流程图\\采购管理\\2.png";
	imag->LoadFromFile(Name);
	Image4->Picture->Graphic = imag;

	imag = new TPngImage();
	Name = path + "image\\流程图\\采购管理\\1.png";
	imag->LoadFromFile(Name);
	Image1->Picture->Graphic = imag;

	imag = new TPngImage();
	Name = path + "image\\流程图\\采购管理\\1.png";
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
	 //不显示滚动条
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
	MessageBoxA(0,"无权限操作此模块,请与管理员联系!","警告",MB_ICONASTERISK);
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
	//将子窗体全部关闭
	HWND hWnd = ::GetWindow(::GetWindow(ClientHandle, GW_CHILD), GW_HWNDFIRST);
	while (hWnd != NULL)
	{

		if(MessageBox(0,"有未关闭窗口，是否退出？,确认将关闭整个系统！" ,"确认" ,MB_ICONQUESTION|MB_OKCANCEL)==1)
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
	//检测是否含有未关闭的子窗体
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
	//如果有则不能关闭主窗体
	if (allclose)
	{
		Action = caNone;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ProcureExecute(TObject *Sender)
{
	//采购管理
    if (!FindDog()) {
        return;
	}
	if (CheckPower("采购处理") ) {
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
	//入库管理
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
	if (CheckPower("入库处理")) {
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
	//入库退货管理
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

	if (CheckPower("入库退货")) {
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
	//智能退货
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
	if (CheckPower("智能退货")) {
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
	//申请配送
	if (!FindDog()) {
		return;
	}
	if (CheckPower("申请配送")) {
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
	//申请配送
	if (!FindDog()) {
		return;
	}
	if (CheckPower("主动配送")) {
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
	//POS零售管理
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	li.FormatStr = "#,##0.00";
	if (CheckPower("POS零售")) {
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
	//零售退货
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	li.FormatStr = "#,##0.00";
	if (CheckPower("POS退货")) {
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
	//jiaojieban 零售员交接班
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
            MessageBoxA(0,"密码输入错误！","错误",MB_ICONERROR);
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
		sql = "insert into sys_log (EventType,SourceFrom,EventDate,EventUser,EventMessage,stgName) values('信息','交接',getdate()," + IntToStr(frmLand->GetUserID()) + ",'收银员交接'," + IntToStr(frmLand->GetStorageID()) + ")" ;

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
	if (CheckPower("订单处理") ) {
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
	if (CheckPower("发货处理")) {
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
	if (CheckPower("发货退货")) {
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
	if (CheckPower("库存查询")) {
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
	//订单查询
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("订单查询")) {
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
	//采购查询
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("采购查询")) {
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
	//入库查询
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	li.FormatStr = "#,##0.00";
	if (CheckPower("入库查询")) {
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
	if (CheckPower("发货查询")) {
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
	if (CheckPower("POS零售查询")) {
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
	if (CheckPower("盘点查询")) {
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
	//配送查询
	if (!FindDog()) {
        return;
	}
	LandInfo li;
	li.app = Application;
	li.con = frmLand->conLand;
	li.userID = frmLand->GetUserID();
	li.storageID = frmLand->GetStorageID();
	if (CheckPower("配送查询")) {
		QryPeisongNote(&li);
	}
	else
	{
		ShowNoPower();
	}
}
//---------------------------------------------------------------------------

