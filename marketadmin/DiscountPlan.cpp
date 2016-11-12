//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "global.h"
#include "DiscountPlan.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzCmboBx"
#pragma link "RzRadChk"
#pragma link "RzEdit"
#pragma link "RzDTP"
#pragma link "RzDBGrid"
#pragma resource "*.dfm"
TFormDiscount *FormDiscount;
//---------------------------------------------------------------------------
__fastcall TFormDiscount::TFormDiscount(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TFormDiscount::Init(TApplication* app, TADOConnection* con,int stgid)
{
    fstgid = stgid;
	query->Connection = con;
	querydetail->Connection = con;
	cn = con;
	//画面初期显示
	AnsiString sql;
	dtpstart->Date = Date();
	dtpend->Date = Date();
	type = 1;
	//店名追加
	//cbstgid->Enabled = false;
	sql = "select ID,Name from SYS_StorageInfo";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	while (!query->Eof)
	{
		cbstgid->AddItem(query->FieldByName("Name")->AsString,(TObject *)query->FieldByName("ID")->AsInteger );
		query->Next();
	}
	cbstgid->ItemIndex = cbstgid->Items->IndexOfObject((TObject*)stgid) ;

	sql = "select Master from SYS_StorageInfo where id = " + IntToStr(stgid);
    query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->FieldByName("Master")->AsBoolean ) {
		cbstgid->Enabled = true;
	}
	else
	{
		cbstgid->Enabled = false;
	}
	//会员类别追加
	sql = "select IDType,Type from CUST_MemberType";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	while (!query->Eof)
	{
		cbmembertype->AddItem(query->FieldByName("Type")->AsString ,(TObject*)query->FieldByName("IDType")->AsInteger );
		query->Next();
	}
    cbmembertype->ItemIndex = 0;
	//打折方案追加
	//rzdiscounttype->Add("购物金额");
	type = 1;
	sql = "select A.*,C.Name as storagename, B.Name,CUST_MemberType.Type as memtype,convert(varchar(20),A.Endtime,23) as endtime1 from BS_DiscountInfo A left join BS_BookType B on A.BookTypeID = B.ID left join CUST_MemberType on A.MemberType = CUST_MemberType.IDType left join SYS_StorageInfo C ON A.StgID = C.id where A.StgID = " + IntToStr(stgid) ;
	querydetail->Close();
	querydetail->SQL->Clear();
	querydetail->SQL->Add(sql);
	querydetail->Open();
	GetData();
	disable();
}
//---------------------------------------------------------------------------
void __fastcall TFormDiscount::dbgdiscountCellClick(TColumn *Column)
{
	disable();
}
//---------------------------------------------------------------------------

void __fastcall TFormDiscount::NdeleteClick(TObject *Sender)
{
	if (querydetail->IsEmpty())  {
		return;
	}

	AnsiString sql;
	if (dbgdiscount->SelectedRows->Count == 0) {
		sql = "delete from BS_DiscountInfo where id = " + querydetail->FieldByName("ID")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
	}
	else if (dbgdiscount->SelectedRows->Count > 0) {
		querydetail->Bookmark = dbgdiscount->SelectedRows->Items[0];
		sql = "delete from BS_DiscountInfo where id = " + querydetail->FieldByName("ID")->AsString ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
		for (int i=1; i < dbgdiscount->SelectedRows->Count; i++)
		{
			querydetail->Bookmark = dbgdiscount->SelectedRows->Items[i];
			sql = "delete from BS_DiscountInfo where id = " + querydetail->FieldByName("ID")->AsString ;
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->ExecSQL();
		}
	}
	querydetail->Active = false;
	querydetail->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormDiscount::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormDiscount::disable()
{
	if (!querydetail->IsEmpty()) {
		cbmembertype->ItemIndex = cbmembertype->Items->IndexOfObject((TObject*)querydetail->FieldByName("MemberType")->AsInteger );
		eddiscount->Text = querydetail->FieldByName("Discount")->AsString ;
		dtpstart->Date = querydetail->FieldByName("Starttime")->AsDateTime ;
		dtpend->Date = querydetail->FieldByName("Endtime")->AsDateTime ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormDiscount::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall TFormDiscount::eddiscountKeyPress(TObject *Sender, wchar_t &Key)
{
	if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
    	Key = NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormDiscount::BtnAlignBottomClick(TObject *Sender)
{
	WindowState  = wsMinimized;
}
//---------------------------------------------------------------------------

void __fastcall TFormDiscount::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
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

void __fastcall TFormDiscount::cbstgidSelect(TObject *Sender)
{
	AnsiString sql;
	try {
		fstgid =  (int)cbstgid->Items->Objects[cbstgid->ItemIndex];
	} catch (...) {
		ShowMsg(Handle ,"请选择正确的店名！",3);
		return;
	}
	sql = "select A.*,C.Name as storagename, B.Name,CUST_MemberType.Type as memtype,convert(varchar(20),A.Endtime,23) as endtime1 from BS_DiscountInfo A left join BS_BookType B on A.BookTypeID = B.ID left join CUST_MemberType on A.MemberType = CUST_MemberType.IDType left join SYS_StorageInfo C ON A.StgID = C.id where A.StgID = " + IntToStr(fstgid) ;
	querydetail->Close();
	querydetail->SQL->Clear();
	querydetail->SQL->Add(sql);
	querydetail->Open();
	disable();
}
//---------------------------------------------------------------------------

void __fastcall TFormDiscount::RzButton2Click(TObject *Sender)
{
	AnsiString sql;
	if (eddiscount->Text == "") {
		ShowMsg(Handle ,"折扣不能为空！",3);
		return;
	}
	int discount =  StrToInt(eddiscount->Text);
	if (discount < 0) {
		ShowMsg(Handle ,"折扣不能小于0！",3);
		return;
	}
	if (discount > 100) {
		ShowMsg(Handle ,"折扣不能大于100！",3);
		return;
	}
	int start,end;
	if (dtpstart->Date > dtpend->Date ) {
		ShowMsg(Handle ,"结束日期必须大于开始日期！",3);
		return;
	}
	int memtype;
	try {
		memtype =  (int)cbmembertype->Items->Objects[cbmembertype->ItemIndex];
	} catch (...) {
		ShowMsg(Handle ,"请选择正确的会员类别！",3);
		return;
	}
	try {
		fstgid =  (int)cbstgid->Items->Objects[cbstgid->ItemIndex];
	} catch (...) {
		ShowMsg(Handle ,"请选择正确的店名！",3);
		return;
	}

	struct Nodedata *ndata = NULL;
	TTreeNode  *aNode=NULL;
	TStringList * ActionList;
	ActionList = new TStringList();
	AnsiString typeids = "";

	try
	{
		Screen->Cursor = crHourGlass ;
		for(aNode=tvbookclass->Items->GetFirstNode() ; aNode!=NULL ;)
		{
			if (aNode->Text != "书目类别") {
            	ndata = (Nodedata*)(aNode->Data);
				if (GetNodeChecked(aNode)) {
					if (typeids == "") {
						typeids = IntToStr(ndata->ID);
					}
					else
					{
                    	typeids = typeids + "," + IntToStr(ndata->ID);
					}
				}
			}
			aNode=aNode->GetNext();
		}
		if (typeids == "") {
			return;
		}

		sql = "delete from BS_DiscountInfo where BookTypeID in (" + typeids + ") and StgID = " + IntToStr(fstgid) + " and MemberType = " + IntToStr(memtype) ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
		sql = "insert into BS_DiscountInfo(BookTypeID,stgid,MemberType,discount,Starttime,Endtime) select id," + IntToStr(fstgid) + "," + IntToStr(memtype) + "," + eddiscount->Text + ",'" + DateToStr(dtpstart->Date) + "','" + DateToStr(dtpend->Date) + "' from BS_BookType where id in(" + typeids + ")";
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->ExecSQL();
		querydetail->Active = false;
		querydetail->Active = true;

		Screen->Cursor = crDefault ;
		ShowMsg(this->Handle,"设置成功！",3);
	}
	catch (...) {
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormDiscount::FormCreate(TObject *Sender)
{
	SetWindowLong(tvbookclass->Handle,GWL_STYLE,
	GetWindowLong(tvbookclass->Handle,GWL_STYLE) | TVS_CHECKBOXES);
}

//---------------------------------------------------------------------------

void __fastcall TFormDiscount::tvbookclassMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (ClickNode!=NULL)
	{
		if (GetNodeChecked(ClickNode)!=NodeChecked)
		{ // 把它的子孙都置成一样
			NodeChecked=!NodeChecked; // 更新它
			SetChildChecked(ClickNode,NodeChecked);
		}
	}
}

//---------------------------------------------------------------------------

bool  TFormDiscount::GetNodeChecked(TTreeNode *ANode)
{
	  TVITEM tvItem;
	  tvItem.mask = TVIF_HANDLE | TVIF_STATE;
	  tvItem.hItem = ANode->ItemId;
	  tvItem.stateMask = TVIS_STATEIMAGEMASK;
	  TreeView_GetItem(ANode->TreeView->Handle, &tvItem);
	  return ((BOOL)(tvItem.state >> 12) -1);
}

//---------------------------------------------------------------------------

void  TFormDiscount::SetChildChecked(TTreeNode *ANode,bool yn)
{
	int count=ANode->Count;
	SetNodeChecked(ANode,yn);
	if (count!=0) {
		for (int i=0;i<count;i++){    // 递归
			SetChildChecked(ANode->Item[i],yn);
        }
	}
}

//---------------------------------------------------------------------------

void  TFormDiscount::SetNodeChecked(TTreeNode *ANode,bool IsSetToChecked)
{
	TVITEM tvItem;
	tvItem.mask = TVIF_HANDLE | TVIF_STATE;
	tvItem.hItem = ANode->ItemId;
	tvItem.stateMask = TVIS_STATEIMAGEMASK;
	tvItem.state = INDEXTOSTATEIMAGEMASK(IsSetToChecked?2:1);
	TreeView_SetItem(ANode->TreeView->Handle, &tvItem);
}

//---------------------------------------------------------------------------

void __fastcall TFormDiscount::tvbookclassMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y)
{
	ClickNode = tvbookclass->GetNodeAt(X,Y);
	if (ClickNode!=NULL) {// 保存原节点的Checked值
		NodeChecked = GetNodeChecked(ClickNode);
	}
}

//---------------------------------------------------------------------------

void __fastcall TFormDiscount::N1Click(TObject *Sender)
{
	if (querydetail->IsEmpty() ) {
		return;
	}
	for (int i = 1; i <= querydetail->RecordCount ; i++) {
		dbgdiscount->DataSource->DataSet->RecNo = i;
		dbgdiscount->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------

void TFormDiscount::GetData()
{
	tvbookclass->Items->Clear();
	AnsiString sql = " exec USP_BS_Type_View '" + edtypename->Text.Trim() + "'";
	struct Nodedata *ndata = NULL;

	TStringList *tmpstr=NULL;

	TTreeNode  *aNode=NULL;
	TTreeNode  *bNode=NULL;
	TTreeNode  *pNode=NULL;

	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();

	tmpstr =new TStringList();
	tvbookclass->Items->BeginUpdate();//禁止刷新，提高速度
	//遍历记录集
	for(query->First(); !query->Eof; query->Next())
	{
	  ndata = new Nodedata();
	  ndata->Name = "[" + query->FieldByName("code")->AsAnsiString + "]" + query->FieldByName("name")->AsAnsiString ;
	  ndata->PrentID = query->FieldByName("parentID")->AsInteger ;
	  ndata->ID = query->FieldByName("ID")->AsInteger ;
	  //生成一个根节点加入TreeView
	  aNode=tvbookclass->Items->AddObject(NULL,ndata->Name ,ndata);
	  //记录id-TreeNode对应关系,便于下面查找
	  tmpstr->AddObject(AnsiString(ndata->ID),aNode);
	}

	query->Close();
	ndata=NULL;

	int idx;
	for(aNode=tvbookclass->Items->GetFirstNode(); aNode!=NULL ;)
	{
		ndata = (Nodedata*)(aNode->Data);
		if(-1==(idx=tmpstr->IndexOf(AnsiString(ndata->PrentID))))
		{
			aNode=aNode->getNextSibling();
			continue;
		}
		else
		{
			pNode = (TTreeNode*)(tmpstr->Objects[idx]);
			bNode=aNode;
			aNode=aNode->getNextSibling();
			bNode->MoveTo(pNode,naAddChild);
		}
	}
	tvbookclass->FullCollapse();
	tvbookclass->Items->EndUpdate();














	/*TStringList *tmpstr = NULL;

	struct Nodedata *ndata = NULL;
	TypeName = new TStringList(NULL);
	TypeCode = new TStringList(NULL);
	ClassType = new TStringList(NULL);
	TypeCode->Sorted = true;
	TypeName->Sorted = true;

	TTreeNode  *aNode=NULL;
	TTreeNode  *bNode=NULL;
	TTreeNode  *pNode=NULL;
	TTreeNode * node;

	AnsiString ClassName,sql;
	sql = "select id,ParentID,code,name,bk from bs_booktype where name like '%" + edtypename->Text.Trim() + "%' or code like '%" + edtypename->Text.Trim() + "%'" ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open() ;
	node = tvbookclass->Items->Item[0];

	tmpstr = new TStringList(NULL);
	tvbookclass->Items->BeginUpdate();
	AnsiString displayname;
	for(query->First(); !query->Eof; query->Next())
	{
		ndata = new Nodedata();
		ndata->Name = "[" + query->FieldByName("Code")->AsAnsiString + "]" + query->FieldByName("name")->AsAnsiString ;
		ndata->PrentID = query->FieldByName("ParentID")->AsInteger ;
		ndata->ID = query->FieldByName("ID")->AsInteger ;
		ndata->bk = query->FieldByName("bk")->AsAnsiString;
		ndata->code = query->FieldByName("Code")->AsAnsiString;
		//生成一个根节点加入TreeView
		displayname = ndata->Name;
		aNode =  tvbookclass->Items->AddChildObject(node,displayname,ndata);
		//记录id-TreeNode对应关系,便于下面查找
		tmpstr->AddObject(AnsiString(ndata->ID),aNode);
		TypeName->Add("[" + query->FieldByName("Code")->AsAnsiString + "]" + query->FieldByName("name")->AsAnsiString);
		TypeCode->Add(query->FieldByName("Code")->AsAnsiString);
	}
	query->Close();
	ndata=NULL;
	node=NULL;
	node=tvbookclass->Items->GetFirstNode();
	int idx;
	for(aNode=node->getFirstChild(); aNode!=NULL ;)
	{
		ndata = (Nodedata*)(aNode->Data);
		if(-1==(idx=tmpstr->IndexOf(AnsiString(ndata->PrentID))))
		{
			aNode=aNode->getNextSibling();
			continue;
		}
		else
		{
			pNode = (TTreeNode*)(tmpstr->Objects[idx]);
			bNode=aNode;
			aNode=aNode->getNextSibling();
			bNode->MoveTo(pNode,naAddChild);
		}
	}
	tvbookclass->Items->EndUpdate();     */
}
//---------------------------------------------------------------------------

void __fastcall TFormDiscount::RzButton1Click(TObject *Sender)
{
	GetData();
}
//---------------------------------------------------------------------------

void __fastcall TFormDiscount::edtypenameKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		RzButton1->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormDiscount::RzButton1KeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		RzButton1->Click();
	}
}
//---------------------------------------------------------------------------

