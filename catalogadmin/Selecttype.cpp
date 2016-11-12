//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Selecttype.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrmselecttype *frmselecttype;
//---------------------------------------------------------------------------
__fastcall Tfrmselecttype::Tfrmselecttype(TComponent* Owner,TADOConnection *con,AnsiString sqlwhere)
	: TForm(Owner)
{
	fcon = con;
	where = sqlwhere;
}
//---------------------------------------------------------------------------
void Tfrmselecttype::ShowClient()
{
	AnsiString sql = " exec USP_BS_Type_View '" + where + "'";
	struct Node *ndata = NULL;

	TStringList *tmpstr=NULL;

	TTreeNode  *aNode=NULL;
	TTreeNode  *bNode=NULL;
	TTreeNode  *pNode=NULL;

	TADOQuery *query = new TADOQuery(Application);
	query->Connection = fcon;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();

	tmpstr =new TStringList();
	tvclient->Items->BeginUpdate();//禁止刷新，提高速度
	//遍历记录集
	for(query->First(); !query->Eof; query->Next())
	{
	  ndata = new Node();
	  ndata->Name = "[" + query->FieldByName("code")->AsAnsiString + "]" + query->FieldByName("name")->AsAnsiString ;
	  ndata->PrentID = query->FieldByName("parentID")->AsInteger ;
	  ndata->ID = query->FieldByName("ID")->AsInteger ;
	  //生成一个根节点加入TreeView
	  aNode=tvclient->Items->AddObject(NULL,ndata->Name ,ndata);
	  //记录id-TreeNode对应关系,便于下面查找
	  tmpstr->AddObject(AnsiString(ndata->ID),aNode);
	}

	query->Close();
	ndata=NULL;

	int idx;
	for(aNode=tvclient->Items->GetFirstNode(); aNode!=NULL ;)
	{
		ndata = (Node*)(aNode->Data);
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
	tvclient->FullCollapse();
	tvclient->Items->EndUpdate();
}
//---------------------------------------------------------------------------
AnsiString Tfrmselecttype::GetSelect()
{
	return SelectClientName;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmselecttype::FormCreate(TObject *Sender)
{
	ShowClient();
}
//---------------------------------------------------------------------------
int Tfrmselecttype::GetSelectID()
{
	return Typeid;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmselecttype::tvclientMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	ClickNode = tvclient->GetNodeAt(X,Y);
}
//---------------------------------------------------------------------------
void __fastcall Tfrmselecttype::tvclientDblClick(TObject *Sender)
{
	if (ClickNode!=NULL) {
		struct Node *ndata = NULL;
		ndata = (Node*)(ClickNode->Data);
		SelectClientName = ndata->Name ;
		Typeid = ndata->ID ;
		ModalResult = mrOk ;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmselecttype::tvclientKeyPress(TObject *Sender, wchar_t &Key)

{



	if (Key == '\r') {
	if (tvclient->Selected!=NULL) {
		 ClickNode=	tvclient->Selected;
		if (ClickNode!=NULL) {
			struct Node *ndata = NULL;
			ndata = (Node*)(ClickNode->Data);
			SelectClientName = ndata->Name;
			Typeid = ndata->ID ;
			ModalResult = mrOk ;
		}
		 }
	}
}
//---------------------------------------------------------------------------


