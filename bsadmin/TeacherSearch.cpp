//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TeacherSearch.h"
#include "DBGridEhImpExp.hpp"
#include "TeacherFDDetail.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma resource "*.dfm"
Tfrmteachersearch *frmteachersearch;
//---------------------------------------------------------------------------
__fastcall Tfrmteachersearch::Tfrmteachersearch(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void Tfrmteachersearch::LoadData(AnsiString aname)
{
    AnsiString sql;
   sql="select id,name from Teacher where name like '%"+aname+"%'";
   aqq->Close();
   aqq->SQL->Clear();
   aqq->SQL->Add(sql);
   aqq->Open();

   cbteacher->Items->Clear();

   while (!aqq->Eof)
   {
	cbteacher->Items->AddObject(aqq->FieldByName("name")->AsAnsiString,(TObject*)(aqq->FieldByName("id")->AsInteger));
	aqq->Next();
   }
   if (aname=="") {
	 cbteacher->Items->AddObject("全部",(TObject*)(-1));
   }

   if (aqq->RecordCount>0) {
	cbteacher->ItemIndex=0;
   }else cbteacher->ItemIndex=-1;




}
void Tfrmteachersearch::init(LandInfo *li)
{
   	fcon  = li->con ;
	aq->Connection = fcon;
	aqq->Connection = fcon;
	ADODataSet1->Connection=fcon;
	adosp->Connection=fcon;
	UserID = li->userID ;
	Stgid = li->storageID ;
   LoadData("");

}
//---------------------------------------------------------------------------
void __fastcall Tfrmteachersearch::editnameKeyPress(TObject *Sender, wchar_t &Key)

{
	//检索教师名称
 	if (Key == '\'') {
		Key = NULL;
	}
	if (Key==VK_RETURN) {
	 LoadData(editname->Text.Trim());
	}
	
}
//---------------------------------------------------------------------------
void Tfrmteachersearch::Search()
{
	AnsiString sql;
	sql = "exec TeacherFDSearch ";
   adosp->Active=false;
  if (cteacher->Checked) {

		adosp->Parameters->ParamByName("@teacherid")->Value =getteacherid(cbteacher->Text);
  }else 	adosp->Parameters->ParamByName("@teacherid")->Value =-1;

   if (CheckBox2->Checked) {
	adosp->Parameters->ParamByName("@begintime")->Value =DateToStr(dtpbegin->Date);
	adosp->Parameters->ParamByName("@endtime")->Value =DateToStr(dtpend->Date);
  }else
  {
	adosp->Parameters->ParamByName("@begintime")->Value="1998-01-02";
	adosp->Parameters->ParamByName("@endtime")->Value = "2090-01-02";
   }
 adosp->Active=true;

			DataSource1->DataSet = NULL;

			ADODataSet1->Recordset = adosp->Recordset;
			ADODataSet1->First();
			DataSource1->DataSet = ADODataSet1;

}
int Tfrmteachersearch::getteacherid(AnsiString name)
{
   int i;
  i= cbteacher->Items->IndexOf(name);
  if (i!=-1) {
	  return int(cbteacher->Items->Objects[i]);
  }else return -1;


}
//---------------------------------------------------------------------------


void __fastcall Tfrmteachersearch::BtnClick(TObject *Sender)
{
Search();

}
//---------------------------------------------------------------------------

void __fastcall Tfrmteachersearch::BtnExitClick(TObject *Sender)
{
 TDBGridEhExportAsXLS *ExportAsXLS;
 TMetaClass *test;

 if (sd->Execute()) {
 if (!sd->FileName.IsEmpty())
 {
	ExportAsXLS=new  TDBGridEhExportAsXLS();
	test=ExportAsXLS->ClassType();
	SaveDBGridEhToExportFile(test,dbgrid,sd->FileName,true);
	delete ExportAsXLS;
  }
  }


}
//---------------------------------------------------------------------------

void __fastcall Tfrmteachersearch::RzToolButton2Click(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmteachersearch::dbgridDblClick(TObject *Sender)
{
///
	 Tfrmfddetail *frm = new Tfrmfddetail(Application) ;
	 frm->fcon =fcon;
	 frm->tearchid= ADODataSet1->FieldByName("teacherid")->AsInteger;
	 if (CheckBox2->Checked) {
	  frm->begintime= DateToStr(dtpbegin->Date);
	  frm->endtime=DateToStr(dtpend->Date); ;
	 }
	 frm->tearchname = ADODataSet1->FieldByName("name")->AsAnsiString;
	 frm->ShowModal();
	 delete frm;
}
//---------------------------------------------------------------------------

