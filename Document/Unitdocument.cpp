//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitdocument.h"
#include "SysUtils.hpp"
#include "Unitnewfile.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzListVw"
#pragma link "RzPanel"
#pragma link "RzTreeVw"
#pragma resource "*.dfm"
Tfrmdocument *frmdocument;
//---------------------------------------------------------------------------
__fastcall Tfrmdocument::Tfrmdocument(TComponent* Owner)
	: TForm(Owner)
{
}
void Tfrmdocument::init(TADOConnection *con,int userid,int stgid)
{
         fcon = con;
         fuserid = userid;
         fstgid = stgid;
         adosp->Connection = fcon;
         foldertype = 1;
         ReadyData(foldertype);  //1为我的文件
}
void Tfrmdocument::readdata(int type)
{


}
//---------------------------------------------------------------------------
void Tfrmdocument::ReadyData(int foldertype)
{
  String sql;
  if (foldertype ==1) {
   sql = "select * from BS_folder where type =" + IntToStr(foldertype)+" and stgid ="+ IntToStr(fstgid)+ "and createuser="+IntToStr(fuserid);

  }else
  {
       sql = "select * from BS_folder where type =" + IntToStr(foldertype);

  }


  struct Nodefolder *ndata = NULL;
   struct Nodefolder *gndata = NULL;
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


   tvpurview->Items->Clear();
  try
  {
	tmpstr =new TStringList();
	tvpurview->Items->BeginUpdate();//禁止刷新，提高速度
	//遍历记录集
	for(query->First(); !query->Eof; query->Next())
	{
	  ndata = new Nodefolder();
	  ndata->Name = query->FieldByName("foldname")->AsAnsiString ;
	  ndata->PrentID = query->FieldByName("parent")->AsInteger ;
	  ndata->ID = query->FieldByName("ID")->AsInteger ;
	  //生成一个根节点加入TreeView
	  aNode=tvpurview->Items->AddObject(NULL,ndata->Name ,(Nodefolder*)ndata);

	  //记录id-TreeNode对应关系,便于下面查找
	  tmpstr->AddObject(AnsiString(ndata->ID),aNode);
	}

	query->Close();
       //	ndata=NULL;

   int idx;
    /*	for(aNode=tvpurview->Items->GetFirstNode(); aNode!=NULL ;)
	{
	  gndata = (Nodefolder*)(aNode->Data);
	  if(-1==(idx=tmpstr->IndexOf(AnsiString(gndata->PrentID))))
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
	}  */
	tvpurview->FullCollapse();
  }
  __finally
  {
	delete tmpstr; tmpstr=NULL;
	query->Close();
	tvpurview->Items->EndUpdate();
	delete query;
  }



}
//---------------------------------------------------------------------------


void __fastcall Tfrmdocument::tvpurviewMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
    	  GroupNode = tvpurview->GetNodeAt(X,Y);
         if (GroupNode != NULL) {

                    struct Nodefolder *ndata = NULL;
                    ndata = (Nodefolder*)(GroupNode->Data);
                    ffolderid = ndata->ID;
                    ShowFile(ffolderid);
                    newfolder->Items->Items[1]->Enabled = true;

          }else
          {

              newfolder->Items->Items[1]->Enabled = false;
          }

}
void Tfrmdocument::ShowFile(int folderid)
{
   AnsiString sql;
   sql = "select id,documnetname,fix from bs_documents where folderid ="+IntToStr(folderid);
   TADOQuery *aq;
   aq = new TADOQuery(Application);
   aq->Connection = fcon;
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->Open();
   TListItem *item;
   lvfile->Items->Clear();
   	for(aq->First(); !aq->Eof; aq->Next())      //店信息
	{

           item =  lvfile->Items->Add();
           item->Caption = aq->FieldByName("documnetname")->AsWideString;
           item->ImageIndex = aq->FieldByName("fix")->AsInteger ;
           item->Data =(int*)aq->FieldByName("id")->AsInteger;

        }
   delete aq;

}
//---------------------------------------------------------------------------

void __fastcall Tfrmdocument::N3Click(TObject *Sender)
{
  if (openfile->Execute()) {

       if(FileExists(openfile->FileName))
       {
           adosp->Parameters->ParamByName("@name")->Value = ExtractFileName(openfile->FileName);
           adosp->Parameters->ParamByName("@fix")->Value = getFix(ExtractFileExt(openfile->FileName));
           adosp->Parameters->ParamByName("@userid")->Value =  fuserid;
           adosp->Parameters->ParamByName("@file")->LoadFromFile(openfile->FileName,ftBlob);
           adosp->Parameters->ParamByName("@foldid")->Value =  ffolderid;
           adosp->ExecProc();
           ShowFile(ffolderid);

       }else
       {
         ShowMsg(Handle ,"文件找不到！",3);
       }

  }
}
int Tfrmdocument::getFix(AnsiString ext)
{
     int f;
     f = 0;
         if (ext.LowerCase() == ".txt") {
               f = 5;
         }else if((ext.LowerCase() == ".doc")||(ext.LowerCase() == ".docx"))
         {
           f=2;
         }
         else if((ext.LowerCase() == ".xlsx")||(ext.LowerCase() == ".xls"))
         {
           f=6;
         }
         else if((ext.LowerCase() == ".ppt")||(ext.LowerCase() == ".pptx"))
         {
           f=4;
         }
         else if(ext.LowerCase() == ".csv")
         {
           f=1;
         }

       return f;



}
//---------------------------------------------------------------------------

void __fastcall Tfrmdocument::Btn1Click(TObject *Sender)
{
ReadyData(1);
foldertype = 1;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdocument::Btn2Click(TObject *Sender)
{
ReadyData(2);
foldertype = 2;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdocument::N1Click(TObject *Sender)
{
    AnsiString sql;
    sql = "insert into bs_folder (foldname,createdate,createuser,parent,type,stgid) ";
    Tfrmnewfile * frm = new Tfrmnewfile(Application);
    if (frm->ShowModal() ==1)
    {
      frm->editfoldername->Text.Trim();
      tvpurview->Items->AddObject(NULL,frm->editfoldername->Text.Trim(),NULL);
      sql = sql + " values('"+frm->editfoldername->Text.Trim()+"',getdate(),"+IntToStr(fuserid)+",-1,"+IntToStr(foldertype)+","+IntToStr(fstgid)+")";
      TADOQuery *aq;
      aq = new TADOQuery(Application);
      aq->Connection = fcon;
      aq->SQL->Clear();
      aq->SQL->Add(sql);
      aq->ExecSQL();
      delete aq;
      ReadyData(foldertype);
    }
    delete frm;

}
//---------------------------------------------------------------------------


void __fastcall Tfrmdocument::N2Click(TObject *Sender)
{
      AnsiString sql;
      sql = "select count(*) as doc from BS_Documents where folderid ="+IntToStr(ffolderid);
       TADOQuery *aq;
      aq = new TADOQuery(Application);
      aq->Connection = fcon;
      aq->SQL->Clear();
      aq->SQL->Add(sql);
      aq->Open();

      if (aq->FieldByName("doc")->AsInteger !=0) {

         ShowMsg(Handle ,"此文件夹中有文件，不能删除！",0);

      }else
      {
        sql = "delete BS_Documents where folderid ="+IntToStr(ffolderid);
        aq->SQL->Clear();
        aq->SQL->Add(sql);
        aq->ExecSQL();
         ShowMsg(Handle ,"删除文件夹成功！",3);

      }
          delete aq;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmdocument::lvfileMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	  lsitem = lvfile->GetItemAt(X,Y);
          if (lsitem !=NULL) {
             newfile->Items->Items[1]->Enabled = true;
             newfile->Items->Items[3]->Enabled = true;
             displayText = lsitem->Caption ;
             fdocumentid=(int)lsitem->Data;
            // fdocumentid = lsitem->data;
          }else
          {
             newfile->Items->Items[1]->Enabled = false;

             newfile->Items->Items[3]->Enabled = false;

          }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdocument::N5Click(TObject *Sender)
{
        savefile->DefaultExt =   ExtractFileExt(displayText);
      	savefile->FileName =  displayText;
     // ShowMessage(IntToStr(fdocumentid));


	if (savefile->Execute()) {
		AnsiString SavePath1 = savefile->FileName ;

		//下载附件
		AnsiString sql = "select documnet from bs_documents where id = " + IntToStr(fdocumentid);
		TADOQuery *aaq = new TADOQuery(NULL);
		aaq->Connection = fcon ;
		aaq->Close();
		aaq->SQL->Clear();
		aaq->SQL->Add(sql);
		aaq->Open();
	   try
	   {
	   TBlobField *Field = (TBlobField*)aaq->FieldByName("documnet");
	   Field->SaveToFile(SavePath1);
	   delete aaq;

	   }catch(...)
	   {
                 ShowMsg(Handle ,"文件下载有发生错误！",3);
		  return;
	   }
              try
	   {
		   if (1==ShowMsg(Handle ,"文件下载成功,是否打开？",1))
		   {
			 ShellExecute(NULL,"open",SavePath1.c_str() ,"","",SW_SHOW);
		   }
	   }catch(...)

	   {
                  ShowMsg(Handle ,"文件打开失败",3);
		  return;
	   }

           }
         }
//---------------------------------------------------------------------------

void __fastcall Tfrmdocument::BtnExitClick(TObject *Sender)
{
      Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdocument::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdocument::N4Click(TObject *Sender)
{
  // ShowMessage(IntToStr(MessageBoxA(0,"确认删除此文件？","提示",MB_YESNO|MB_ICONQUESTION)));

      if (6==MessageBoxA(0,"确认删除此文件？","提示",MB_YESNO|MB_ICONQUESTION))
     {
         try
         {
        	AnsiString sql = "delete  bs_documents where id = " + IntToStr(fdocumentid);
		TADOQuery *aaq = new TADOQuery(NULL);
		aaq->Connection = fcon ;
		aaq->Close();
		aaq->SQL->Clear();
		aaq->SQL->Add(sql);
		aaq->ExecSQL();
                MessageBoxA(0,"删除文件成功!","提示",MB_ICONASTERISK);
                ShowFile(ffolderid);

         }catch(...)
         {
            MessageBoxA(0,"删除文件失败!","提示",MB_ICONWARNING);
         }
     }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdocument::FormClose(TObject *Sender, TCloseAction &Action)
{
   Action = caFree ;
}
//---------------------------------------------------------------------------

