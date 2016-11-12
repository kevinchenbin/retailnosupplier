//---------------------------------------------------------------------------
//#include "includeall.h"
#include <vcl.h>
#pragma hdrstop

#include "TeacherFD.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzEdit"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
TfrmteacherFD *frmteacherFD;
//---------------------------------------------------------------------------
__fastcall TfrmteacherFD::TfrmteacherFD(TComponent* Owner)
	: TForm(Owner)
{
 m_catalogSearchMode = 1;
}
void TfrmteacherFD::init(LandInfo *li)
{
   	fcon  = li->con ;
	aq->Connection = fcon;
	dbgridadoquery->Connection = fcon;
	UserID = li->userID ;
	Stgid = li->storageID ;


}
//---------------------------------------------------------------------------
void __fastcall TfrmteacherFD::edtCatalogKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\'') {
		Key = NULL;
	}
	if(cbteacher->Text=="")
	{
       ShowMessage("请先选择教师!");
	}

	if (m_catalogSearchMode == 6) {
		if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
			Key = NULL;
		}
	}
	int results;
   	if (Key == VK_RETURN)
	{
		if (edtCatalog->Text == "") {
			ChangeCatalogSearchMode();
			return;
		}
		if (m_catalogSearchMode==6) {
			FLOAT price;
			try
			{
				price = StrToFloat(edtCatalog->Text);
			}
			catch(...)
			{

                                ShowMsg(Handle ,"请输入正确的价格！",3);
				return ;
			}
		}

		TfrmSelectCatalog* frm = new TfrmSelectCatalog(Application,fcon);
		LandInfo li;
		li.app = Application;
		li.con = fcon;
		li.userID = UserID;
		li.storageID = Stgid;
		frm->Init(&li);
		frm->DoModalType = 9;
	  //	frm->StockAdjust  = this;
		frm->SetSearchMode(m_catalogSearchMode, edtCatalog->Text);
		frm->SelectAll = false;
		frm->QryBkInfo();
		if (frm->findbooks == 3) {
			results= frm->ShowModal();
		}else if (frm->findbooks==1) {
			results = 1;
		}else if ((frm->findbooks==0)||(frm->findbooks==-1)) {
			results = -1 ;
		}

		int bkinfoid;
		if (mrOk == results)
		{
			if (frm->SelectAll) {
				 for (int i = 0; i < frm->lengthint  ; i++) {
					AddNote(frm->SupplierID[i],frm->BkcatalogiD[i],frm->stkbkid[i],frm->skAmount[i]);
				 }
			}else
			{
			   frm->GetSelectResult(bkinfoid,catalogID);
			   AddNote(supplierID,catalogID,frm->BKinfoid,frm->Amount);
			   numerfd->SetFocus();
			}
		}

		delete frm;
		edtCatalog->Text = "";
	}
}
void TfrmteacherFD::ChangeCatalogSearchMode()
{
    	if (m_catalogSearchMode==3) {
		m_catalogSearchMode=5;
	}else
	{
		m_catalogSearchMode++;
	}
	if (m_catalogSearchMode >= 7)
	{
		m_catalogSearchMode = 1;
	}

	switch (m_catalogSearchMode)
	{
	case 1:
		edtCatalog->MaxLength = 15;
		lblCatalog->Caption = "书号";
		break;
	case 2:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "自编码";
		break;
	case 3:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "书名";
		break;
	case 5:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "作者";
		break;
	case 6:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "定价";
		break;
	default:
		break;
	}


}
//---------------------------------------------------------------------------
void __fastcall TfrmteacherFD::N1Click(TObject *Sender)
{
    lblCatalog->Caption = "书 号";
	m_catalogSearchMode=1;
}
//---------------------------------------------------------------------------
void __fastcall TfrmteacherFD::N2Click(TObject *Sender)
{
	lblCatalog->Caption = "自编码";
	m_catalogSearchMode=2;
}
//---------------------------------------------------------------------------
void __fastcall TfrmteacherFD::N3Click(TObject *Sender)
{
	lblCatalog->Caption = "书名";
	m_catalogSearchMode=3;
}
//---------------------------------------------------------------------------
void __fastcall TfrmteacherFD::N6Click(TObject *Sender)
{
	lblCatalog->Caption = "定价";
	m_catalogSearchMode=6;
}
//---------------------------------------------------------------------------
void __fastcall TfrmteacherFD::N4Click(TObject *Sender)
{
	lblCatalog->Caption = "作者";
	m_catalogSearchMode=5;
}
//---------------------------------------------------------------------------
void TfrmteacherFD::AddNote(int supplierID,int CatalogId,int bkinfoid,int amount)
 {
	AnsiString sql;
	sql = "insert into BS_TeacherFD(catalogid,begindate,enddate,teacherid)values(";
	sql=sql+IntToStr(CatalogId)+",'"+DateToStr(dtpbegin->DateTime)+"','"+DateToStr(dtpend->DateTime)+"',"+IntToStr(teacherid)+")";
	ExecSQL(sql);
	refreshdbgrid(teacherid);
	dbgridadoquery->Last();
	currentbookid=dbgridadoquery->FieldByName("id")->AsInteger;

   DBGrid1->SelectedRows->CurrentRowSelected = true;
 }
bool TfrmteacherFD::DbgridToExcel(TDBGrid* dbg)
 {
	ShowMessage("");
 }
void TfrmteacherFD::Deletenote()
{
  AnsiString delsql;
  if (!dbgridadoquery->IsEmpty()) {


if (MessageBoxA(0,"确定要删除吗？","提示",MB_ICONQUESTION|MB_OKCANCEL)==1 ) {

		delsql="delete BS_TeacherFD where id =";
		delsql= delsql+dbgridadoquery->FieldByName("id")->AsAnsiString;
	   ExecSQL(delsql);
	  refreshdbgrid(teacherid);
	}
  }
}
void TfrmteacherFD::ExecSQL(AnsiString sql)
{
	TADOQuery *aqexe;
	aqexe =   new TADOQuery(Application);
	aqexe->Connection = fcon;
	aqexe->Close();
	aqexe->SQL->Clear();
	aqexe->SQL->Add(sql);
	aqexe->ExecSQL();
	delete aqexe;




}
void TfrmteacherFD::LoadData(AnsiString aname)
{
   AnsiString sql;
   sql="select id,name from Teacher where name like '%"+aname+"%'";
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->Open();

   cbteacher->Items->Clear();

   while (!aq->Eof)
   {
	cbteacher->Items->AddObject(aq->FieldByName("name")->AsAnsiString,(TObject*)(aq->FieldByName("id")->AsInteger));
	aq->Next();
   }
   if (aq->RecordCount>0) {
	cbteacher->ItemIndex=0;
   }else cbteacher->ItemIndex=-1;




}
void __fastcall TfrmteacherFD::editnameKeyPress(TObject *Sender, wchar_t &Key)
{
	//检索教师名称
 	if (Key == '\'') {
		Key = NULL;
	}
	if (editname->Text!="") {
	  LoadData(editname->Text.Trim());
	}
}

//---------------------------------------------------------------------------

void __fastcall TfrmteacherFD::FormShow(TObject *Sender)
{
LoadData("");
dtpbegin->DateTime=Now();
dtpend->DateTime=Now();
}

void TfrmteacherFD::refreshdbgrid(int tearcher)
{
  AnsiString sql;
  dbgridadoquery->Active = false;
  dbgridadoquery->Parameters->ParamByName("teacherid")->Value = tearcher;
  dbgridadoquery->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmteacherFD::cbteacherChange(TObject *Sender)
{
  if (cbteacher->Text!="") {
		 teacherid=getteacherid(cbteacher->Text);
	  if(-1!=teacherid )
	  {
		 refreshdbgrid(teacherid);
	  }
  }
}
int TfrmteacherFD::getteacherid(AnsiString name)
{
  int i;
  i= cbteacher->Items->IndexOf(name);
  if (i!=-1) {
	  return int(cbteacher->Items->Objects[i]);
  }else return -1;
}
//---------------------------------------------------------------------------

void __fastcall TfrmteacherFD::numerfdKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\'') {
		Key = NULL;


	}
	if (Key == VK_RETURN)
	{

	if (dbgridadoquery->FieldByName("price")->AsAnsiString=="") {
       return;
	}
	 numerfdje->Value =dbgridadoquery->FieldByName("price")->AsFloat*numerfd->Value*0.01;


	UpdateValue(numerfd->Value,1,dbgridadoquery->FieldByName("ID")->AsInteger);
	numerfdje->SetFocus();
	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmteacherFD::numerfdjeKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\'') {
		Key = NULL;
	}
     if (Key == VK_RETURN)
	{

	if (dbgridadoquery->FieldByName("price")->AsAnsiString=="") {
	   return;
	}
	if (numerfdje->Value!=0) {
			 numerfd->Value = (numerfdje->Value / dbgridadoquery->FieldByName("price")->AsFloat)*100;
	}
		UpdateValue(numerfd->Value,1,dbgridadoquery->FieldByName("ID")->AsInteger);
		UpdateValue(numerfdje->Value,2,dbgridadoquery->FieldByName("ID")->AsInteger);
		edtCatalog->SetFocus();
    }
}
void TfrmteacherFD::UpdateValue(double value, int atype,int id)
{
   AnsiString sql;
   if (atype==1) {
			dbgridadoquery->Edit();
			dbgridadoquery->FieldByName("discount")->AsFloat = value;
			dbgridadoquery->Post();
	//sql="update BS_TeacherFD set discount="+FloatToStr(value)+" where id="+IntToStr(id);
   }else if (atype==2) {
			dbgridadoquery->Edit();
			dbgridadoquery->FieldByName("disvalue")->AsFloat = value;
			dbgridadoquery->Post();
   //	sql="update BS_TeacherFD set disvalue="+FloatToStr(value)+" where id="+IntToStr(id);
   }
 // ExecSQL(sql);



 // refreshdbgrid(teacherid);

}
//---------------------------------------------------------------------------

void __fastcall TfrmteacherFD::D1Click(TObject *Sender)
{
Deletenote();
}
//---------------------------------------------------------------------------

void __fastcall TfrmteacherFD::DBGrid1CellClick(TColumn *Column)
{
   //
   if (!dbgridadoquery->IsEmpty()) {
	 numerfd->Value=dbgridadoquery->FieldByName("discount")->AsFloat;
   numerfdje->Value=dbgridadoquery->FieldByName("disvalue")->AsFloat;
   dtpbegin->DateTime=dbgridadoquery->FieldByName("begindate")->AsDateTime;
   dtpend->DateTime=dbgridadoquery->FieldByName("enddate")->AsDateTime;
}
   }

//---------------------------------------------------------------------------

void __fastcall TfrmteacherFD::BtnClick(TObject *Sender)
{
   //
	if (!dbgridadoquery->IsEmpty()) {
		dbgridadoquery->Edit();
		dbgridadoquery->FieldByName("discount")->AsFloat =numerfd->Value ;
		dbgridadoquery->FieldByName("begindate")->AsDateTime =dtpbegin->DateTime;
		dbgridadoquery->FieldByName("enddate")->AsDateTime =dtpend->DateTime;
		dbgridadoquery->FieldByName("disvalue")->AsFloat =  numerfdje->Value;
		dbgridadoquery->Post();
		MessageBoxA(0,"保存成功!","提示",MB_ICONINFORMATION);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmteacherFD::RzToolButton2Click(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------

