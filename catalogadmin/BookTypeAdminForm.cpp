//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BooKTypeAdminForm.h"
#include "global.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzLstBox"
#pragma link "RzTreeVw"
#pragma link "RzListVw"
#pragma link "RzDBList"
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma link "RzDBGrid"
#pragma link "RpCon"
#pragma link "RpConDS"
#pragma link "RpDefine"
#pragma link "RpRave"
#pragma resource "*.dfm"
TfrmBookTypeAdmin *frmBookTypeAdmin;
//---------------------------------------------------------------------------
__fastcall TfrmBookTypeAdmin::TfrmBookTypeAdmin(TComponent* Owner)
  :TForm(Owner)
   //	: TfrmMDIChild(Owner)
{
	 //	m_module = MTBkcatalog;
	Modal = 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBookTypeAdmin::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree;
}
//---------------------------------------------------------------------------
void TfrmBookTypeAdmin::ModifyInfo(AnsiString oldstr,AnsiString newstr,int type,int Operation)
{
   //��� Operation= 2 �� oldstr ΪҪɾ�����ַ���
   int index;
   if (type == 1) {     //�������
      if (Operation == 1) {   //�޸�
            index = TypeName->IndexOf(oldstr);
            if (index != -1) {
              TypeName->Delete(index);
              TypeName->Add(newstr);
            }
      }else if (Operation == 2)      //ɾ��
      {
            index = TypeName->IndexOf(oldstr);
            if (index != -1) {
              TypeName->Delete(index);
            }
      }
   }else
   {
      if (Operation == 1) {   //�޸�

            index = TypeCode->IndexOf(oldstr);
            if (index != -1) {
              TypeCode->Delete(index);
              TypeCode->Add(newstr);
            }
      }else if(Operation == 2)      //ɾ��
      {
            index = TypeCode->IndexOf(oldstr);
            if (index != -1) {
              TypeCode->Delete(index);
            }
      }
   }
}
bool TfrmBookTypeAdmin::isSameIDorName(AnsiString str,int type)
{
   int index;
   if (type == 1) {    //�������

        index = TypeName->IndexOf(str);
   }
   else
   {
       index = TypeCode->IndexOf(str);

   }

   if (index != -1) {   //������ͬ��
     return true;
   }
   return false;
}
void TfrmBookTypeAdmin::Init(TApplication* app, TADOConnection* con)
{
  //	TfrmMDIChild::Init(app, con);

	aqbookclass->Connection = con;
	aquery->Connection = con;
	dsp->Connection = con;

		TStringList *tmpstr = NULL;

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

	AnsiString ClassName;
	AnsiString sql ;
	sql = "select id,ParentID,code,name,bk from bs_booktype";
	aqbookclass->Close();
	aqbookclass->SQL->Clear();
	aqbookclass->SQL->Add(sql);
	aqbookclass->Open() ;
        node = tvbookclass->Items->Item[0];


     

        tmpstr = new TStringList(NULL);
		tvbookclass->Items->BeginUpdate();
        AnsiString displayname;
      	for(aqbookclass->First(); !aqbookclass->Eof; aqbookclass->Next())
       	{
                ndata = new Nodedata();
                ndata->Name = "[" + aqbookclass->FieldByName("Code")->AsAnsiString + "]" + aqbookclass->FieldByName("name")->AsAnsiString ;
                ndata->PrentID = aqbookclass->FieldByName("ParentID")->AsInteger ;
                ndata->ID = aqbookclass->FieldByName("ID")->AsInteger ;
				ndata->bk = aqbookclass->FieldByName("bk")->AsAnsiString;
				ndata->code = aqbookclass->FieldByName("Code")->AsAnsiString;
				//����һ�����ڵ����TreeView
				displayname =  ndata->Name;
                aNode =  tvbookclass->Items->AddChildObject(node,displayname,ndata);
                //aNode = tvbookclass->Items->AddObject(NULL,displayname,ndata);
                //��¼id-TreeNode��Ӧ��ϵ,�����������
                tmpstr->AddObject(AnsiString(ndata->ID),aNode);
				TypeName->Add("[" + aqbookclass->FieldByName("Code")->AsAnsiString + "]" + aqbookclass->FieldByName("name")->AsAnsiString);
                TypeCode->Add(aqbookclass->FieldByName("Code")->AsAnsiString);
   	}



        aqbookclass->Close();
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
		  tvbookclass->Items->EndUpdate();

}




void __fastcall TfrmBookTypeAdmin::btn6Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------



//------------------------------------------------------------------------
void __fastcall TfrmBookTypeAdmin::btnExit1Click(TObject *Sender)
{
	btnExit1->Enabled = false;
	BtnSave->Enabled = true;
	rtbmodify->Enabled = false;
	btnExit2->Enabled = false;
	Modal = 1;

	String sql;
	/*sql = "select Max(ID) as id from BS_BookType";
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	ettypenum->Text = IntToStr(aquery->FieldByName("id")->AsInteger + 1);*/
	ettypenum->Text = "";
	edtname->Text = "";
	edtback->Text = "";
	edtname->Enabled = true;
	edtback->Enabled = true;
    ettypenum->Enabled = true;
	ettypenum->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookTypeAdmin::btnExit2Click(TObject *Sender)
{
	String sql;
	AnsiString sdf;



	   if (tvbookclass->Selected != NULL && tvbookclass->Selected->Parent != NULL) {

			 sdf = "ȷ��Ҫɾ�����"+ ((Nodedata*)tvbookclass->Selected->Data)->Name +"��";
			 if (ShowMsg(this->Handle,sdf.c_str(),1) == 1) {
				 sql = "select count(*) as C from BS_BookCatalog inner join BS_BookType on BS_BookType.ID = BS_BookCatalog.type where BS_BookType.Name = '" +  ((Nodedata*)tvbookclass->Selected->Data)->Name + "'";
				 aquery->Close();
				 aquery->SQL->Clear();
				 aquery->SQL->Add(sql);
				 aquery->Open();
				 if (aquery->FieldByName("C")->AsInteger > 0 ) {
					 ShowMsg(this->Handle,"��������������ͼ�飬����ɾ����",3);
					 return;
				 }
                                   // ShowMessage(((Nodedata*)tvbookclass->Selected->Data)->code);
                                 if (1) {
                                   sql = "delete BS_BookType where code = '" + ((Nodedata*)tvbookclass->Selected->Data)->code+"'";
                                 }else {
				      sql = "delete BS_BookType where id = " + IntToStr(((Nodedata*)tvbookclass->Selected->Data)->ID);
                                 }

				 aquery->Close();
				 aquery->SQL->Clear();
				 aquery->SQL->Add(sql);
				 try {
					aquery->ExecSQL();
                                        ModifyInfo(((Nodedata*)tvbookclass->Selected->Data)->Name,"",1,1);
                                        ModifyInfo(((Nodedata*)tvbookclass->Selected->Data)->ID,"",2,2);
					tvbookclass->Selected->Delete();
					edtname->Text = "";
					edtback->Text = "";


				 } catch (...) {
					ShowMsg(this->Handle,"�����ݸ�ϵͳ���������й���������ɾ����",3);
				 }
			 }
	   } else
	   {
		   ShowMsg(this->Handle,"��ѡ�����ͣ�",3);
	   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookTypeAdmin::btnExit3Click(TObject *Sender)
{
	//DbgridToExcel(RzDBGrid1);

}
//---------------------------------------------------------------------------

void __fastcall TfrmBookTypeAdmin::btn1Click(TObject *Sender)
{

	//rvprjct1->Engine ->ExecuteAction();
	//rvprjct1->New();
}
//---------------------------------------------------------------------------


void __fastcall TfrmBookTypeAdmin::dbedtCodeKeyPress(TObject *Sender, wchar_t &Key)
{
 /*	if(Key == VK_RETURN)
	{
		if(dbedtCode->Text == "")
		{
			ShowMessage("����Ϊ��");
			return;
		}
		dbedtTypeName->SetFocus();
	}  */
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookTypeAdmin::dbedtTypeNameKeyPress(TObject *Sender, wchar_t &Key)

{
  /*	if(Key == VK_RETURN)
	{
		if(dbedtTypeName->Text == "")
		{
			ShowMessage("����Ϊ��");
			return;
		}
		else
		{
			if(dsetBookType->State != dsInsert)
			{
			ShowMessage("�������״̬");
			return;
			}
			dsetBookType->Post();
			dbedtCode->Text = "";
			dbedtTypeName->Text = "";
		}
//		dsetBookType->Post();
//		dbedtCode->Text = "";
//		dbedtTypeName->Text = "";

	}   */
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookTypeAdmin::RzToolButton1Click(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void TfrmBookTypeAdmin::OnHotKeyPress(DWORD vkCode)
{
  /*	if(vkCode == VK_F6)
	{
		 btnExit1Click(NULL);
	}
	if(vkCode == VK_DELETE)
	{
    	 btnExit2Click(NULL);
	}
	if(vkCode == VK_ESCAPE)
	{
    	 RzToolButton1Click(NULL);
	}  */
}
int TfrmBookTypeAdmin::GetSelecedNodeID()
{
  if (tvbookclass->Selected != NULL) {
      if (tvbookclass->Selected->Text=="ͼ�����") {
         return -10;
      }else
      {
         return ((Nodedata*)tvbookclass->Selected->Data)->ID;
      }
  }
  return -2;

}
void __fastcall TfrmBookTypeAdmin::BtnSaveClick(TObject *Sender)
{
   AnsiString sql ;
   TTreeNode *node,*node2;
   String ClassName;
   AnsiString number;
   int SelectNodeID;
   String parentID;
   String classnamestr;
   int postit;
    struct Nodedata * rnode = NULL;
        classnamestr =edtname->Text.Trim();
        postit =  classnamestr.Pos("]");

   ClassName = classnamestr.Delete(1,postit);

   if (edtname->Text == "") {
		ShowMsg(this->Handle,"������������ƣ�",3);
		return;
   }
	   node2 = tvbookclass->Selected ;
	   if (node2->Text == "ƷĿ���") {
			if(isSameIDorName(edtname->Text.Trim(),1))
			{
				ShowMsg(this->Handle,"����������Ѵ��ڣ�����������������ƣ�",3);
				return;
			}
	   }
	   else
	   {
        	if(((Nodedata *)node2->Data)->Name != edtname->Text.Trim())
			{
				if(isSameIDorName(edtname->Text.Trim(),1))
				{
					ShowMsg(this->Handle,"����������Ѵ��ڣ�����������������ƣ�",3);
					return;
				}
			}
	   }

	   //ȡ�������code
	      //	if (isSameIDorName(ettypenum->Text.Trim(),2))
	     //	{
	      //		ShowMsg(this->Handle,"�ñ���Ѵ��ڣ���������������ţ�",3);
	      //		return;
	     //	}

   switch (Modal) {  //���
	   case 1:
                if (ettypenum->Text.Trim() =="") {
                   ShowMsg(this->Handle,"���������ţ�",3);
                   ettypenum->SetFocus();
					return;
                }

						//ȡ��ѡ��ڵ�ģɣ�
		if (node2->Text == "ƷĿ���")  {
			parentID = IntToStr(-1);
		}
		else
		{
        	SelectNodeID = GetSelecedNodeID();
			if (SelectNodeID == -2) {
				ShowMsg(this->Handle,"����ѡ��Ҫ��ӵ����",3);
				return;
			}else if (SelectNodeID == -10 ) {
				parentID = IntToStr(-1);
			}else
			{
				parentID = IntToStr(SelectNodeID);
			}
		}


            sql = "insert into bs_booktype(parentid,code,name,bk) values("+ parentID +",'"+ettypenum->Text.Trim()+"','";
			sql = sql + ClassName+"','"+edtback->Text.Trim()  +  "')";
			aqbookclass->Close();
			aqbookclass->SQL->Clear();
			aqbookclass->SQL->Add(sql);
			aqbookclass->ExecSQL();

			node = tvbookclass->Selected ;


                        rnode = new Nodedata();
						rnode->code= ettypenum->Text.Trim();
                        rnode->Name =  ClassName;
                        rnode->bk = edtback->Text.Trim();
                        rnode->PrentID =  ((Nodedata *)node)->ID ;
                        	ClassName = "[" + ettypenum->Text.Trim() + "]" + ClassName;
                        tvbookclass->Items->AddChildObject(node,ClassName,rnode);

			ClassType->Add(ClassName);
			edtname->Text = "";
			edtback->Text = "";

			TypeName->Add(ClassName);
			TypeCode->Add(ettypenum->Text.Trim());
			break;

	

	   case 2:

			sql = "update bs_booktype Set Name = '" + ClassName + "',code = '"+ ettypenum->Text.Trim() +"' where id = " + IntToStr(((Nodedata*)tvbookclass->Selected->Data)->ID);
			aqbookclass->Close();
			aqbookclass->SQL->Clear();
			aqbookclass->SQL->Add(sql);
			aqbookclass->ExecSQL();
			tvbookclass->Selected->Text =ClassName;
                     //   ((Nodedata*)tvbookclass->Selected->Data)->Name
                        if (tvbookclass->Selected != NULL) {
                           ModifyInfo(((Nodedata*)tvbookclass->Selected->Data)->Name,ClassName,1,1);

                            ModifyInfo(((Nodedata*)tvbookclass->Selected->Data)->code,ettypenum->Text.Trim(),2,1);
                           tvbookclass->Selected->Text = "["+ettypenum->Text+"]"+ClassName;
                        }

			break;
	   default:
			;
      }

		BtnSave->Enabled = false;
		btnExit1->Enabled = true;
		rtbmodify->Enabled = true;
		edtname->Enabled = false;
		edtback->Enabled = false;

}
//---------------------------------------------------------------------------


void __fastcall TfrmBookTypeAdmin::rtbmodifyClick(TObject *Sender)
{

	if (tvbookclass->Selected != NULL && tvbookclass->Selected->Parent != NULL) {
    	btnExit1->Enabled = false;
		BtnSave->Enabled = true;
		rtbmodify->Enabled = false;
		btnExit2->Enabled = false;
		Modal = 2;
		edtname->Enabled = true;
		edtback->Enabled = true;
		ettypenum->Enabled = false;

   } else
   {
	   ShowMsg(this->Handle,"��ѡ�����ͣ�",3);
   }
}
//---------------------------------------------------------------------------


void __fastcall TfrmBookTypeAdmin::tvbookclassClick(TObject *Sender)
{
	BtnSave->Enabled = false;
	edtname->Enabled = false;
	edtback->Enabled = false;
	ettypenum->Enabled = false;
	btnExit2->Enabled = true;
	if (tvbookclass->Selected != NULL&&tvbookclass->Selected->Parent != NULL) {

		 ettypenum->Text =  ((Nodedata*)tvbookclass->Selected->Data)->code;
		 edtname->Text  =  ((Nodedata*)tvbookclass->Selected->Data)->Name;
		 edtback->Text =  ((Nodedata*)tvbookclass->Selected->Data)->bk ;
		 btnExit1->Enabled = true;
		 rtbmodify->Enabled = true;

	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmBookTypeAdmin::edtnameKeyPress(TObject *Sender, wchar_t &Key)

{
	 if (Key=='\r') {
         BtnSave->Click();
	 }
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookTypeAdmin::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBookTypeAdmin::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F2) {  //���
		 btnExit1->Click();
	}	if (Key == VK_F4) {     //����
		BtnSave->Click();
	}
		if (Key == VK_F5) {      //ɾ��
		btnExit2->Click();
	}
		if (Key == VK_F3) {   //�޸�
		rtbmodify->Click();
	}
		if (Key == VK_F6) {      //����
		btnExit3->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //��С��
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //�˳�
		RzToolButton1->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //�ָ�����
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

