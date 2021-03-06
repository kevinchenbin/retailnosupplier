//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitSelectClient.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmselectClient *frmselectClient;
//---------------------------------------------------------------------------
__fastcall TfrmselectClient::TfrmselectClient(TComponent* Owner,TADOConnection *con,AnsiString sqlwhere,int stgid)
	: TForm(Owner)
{
   fcon = con;
   where = sqlwhere;
   fstgid = stgid;
}
void TfrmselectClient::ShowClient()
{
  AnsiString sql = " exec USP_BS_Client_View 1,0,"+IntToStr(fstgid)+",'" + where + "'";
  struct Nodedata *ndata = NULL;

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
	  ndata = new Nodedata();
	  ndata->Name = query->FieldByName("name")->AsAnsiString ;
	  ndata->PrentID = query->FieldByName("prentID")->AsInteger ;
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
	tvclient->FullCollapse();
	tvclient->Items->EndUpdate();
}
//---------------------------------------------------------------------------
AnsiString TfrmselectClient::GetSelect()
{
      return SelectClientName;
}
void __fastcall TfrmselectClient::FormCreate(TObject *Sender)
{

	ShowClient();
}
int TfrmselectClient::GetSelectID()
{
	return ClientID;
}
//---------------------------------------------------------------------------
void __fastcall TfrmselectClient::tvclientMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
   ClickNode = tvclient->GetNodeAt(X,Y);
}
//---------------------------------------------------------------------------
void __fastcall TfrmselectClient::tvclientDblClick(TObject *Sender)
{
   if (ClickNode!=NULL) {
	  struct Nodedata *ndata = NULL;
	  ndata = (Nodedata*)(ClickNode->Data);
	   SelectClientName = ndata->Name  ;
	   ClientID = ndata->ID ;
	   ModalResult = mrOk ;
   }
}
//---------------------------------------------------------------------------
void __fastcall TfrmselectClient::tvclientKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
    	if (ClickNode!=NULL) {
			struct Nodedata *ndata = NULL;
			ndata = (Nodedata*)(ClickNode->Data);
			SelectClientName = ndata->Name  ;
			ClientID = ndata->ID ;
			ModalResult = mrOk ;
		}
	}
}
//---------------------------------------------------------------------------

