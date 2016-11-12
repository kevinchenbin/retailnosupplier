

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PressAdminForm.h"
#include "MDIChild.h"
#include "pdutil.h"

//---------------------------------------------------------------------------
//jia---------------------------------------------------------------------------
  #include   "ComObj.hpp"
  #define       PG       OlePropertyGet
  #define       PS       OlePropertySet
  #define       FN       OleFunction
  #define       PR       OleProcedure
 //jia----------------------------
#pragma package(smart_init)
#pragma link "MDIChild"
#pragma link "RzButton"
#pragma link "RzCmboBx"
#pragma link "RzDBCmbo"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma link "RzDBGrid"

#pragma link "RzDBEdit"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma link "RzShellDialogs"
#pragma link "RzLine"
#pragma resource "*.dfm"
TfrmPressAdmin *frmPressAdmin;
//---------------------------------------------------------------------------
__fastcall TfrmPressAdmin::TfrmPressAdmin(TComponent* Owner)
	: TfrmMDIChild(Owner)
{
 
}
//---------------------------------------------------------------------------
void __fastcall TfrmPressAdmin::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPressAdmin::btnQueryClick(TObject *Sender)
{
	//ShowMessage("hello");
	Query(edtQuery->Text );
}
//---------------------------------------------------------------------------
void TfrmPressAdmin::Init(TApplication* app, TADOConnection* con)
{
	TfrmMDIChild::Init(app, con);
	m_con = con;
	dsetPress->Connection = m_con;
	dsetPress->CommandText = "select * from BS_PressInfo";
	dsetPress->Active = true;
	//dsetPress->First();
}

void TfrmPressAdmin::Query(String condition)
{
	if (dsetPress->Active)
	{
		dsetPress->Active = false;
	}

	String sql;
	if(cbQueryType->ItemIndex == 0)
	{

		//sql = "select * from BS_PressInfo where PresentNum = 1";
		if(condition=="")
		{
		sql = "select * from BS_PressInfo" ;  //
		}
		else sql = "select * from BS_PressInfo where PresentNum like '%" + condition + "%'";// + condition;
	}
	else if(cbQueryType->ItemIndex == 2)
	{
		sql = "select * from BS_PressInfo where FullName like '%" + condition + "%'";
	}
	else if(cbQueryType->ItemIndex == 1)
	{
		sql = "select * from BS_PressInfo where AbbreviatedName like '%" + condition + "%'";
	}
	dsetPress->CommandText = sql;
	dsetPress->Active = true;
}

void __fastcall TfrmPressAdmin::RzToolButton4Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------


void __fastcall TfrmPressAdmin::RzToolButton2Click(TObject *Sender)
{
	/*if(dsetPress->State == dsInsert&&dbedtPreNum->Text != "")
	{
	dbedtAbbrNam->ReadOnly = false;
	dsetPress->Post();
	dsetPress->Refresh();
	}*/



}
//---------------------------------------------------------------------------



void __fastcall TfrmPressAdmin::btnAddClick(TObject *Sender)
{
	//
	RzDBEdit2->SetFocus();
	int i;
	i=123;
	String s;
	s=IntToStr(i);
	ShowMessage(s);
	dsetPress->Append();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::btnDeleteClick(TObject *Sender)
{
	if(!dsetPress->IsEmpty())
	{
		dsetPress->Delete();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::frmExportClick(TObject *Sender)
{
	//ShowMessage("ok");

	if (svdlgExport->Execute())
	{

	}


}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::btnExitClick(TObject *Sender)
{
	//
	Close();
}
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::edtQueryKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
		if (Key==VK_RETURN) {
				Query(edtQuery->Text);
		 }
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::RzDBEdit2KeyPress(TObject *Sender, wchar_t &Key)
{
	  if (Key==VK_RETURN) //
	{

			RzDBEdit3->SetFocus();

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::RzDBEdit3KeyPress(TObject *Sender, wchar_t &Key)
{
     if (Key==VK_RETURN) //
	{

			RzDBEdit4->SetFocus();

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::RzDBEdit4KeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key==VK_RETURN) //
	{

			RzDBEdit5->SetFocus();

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::RzDBEdit5KeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key==VK_RETURN) //
	{

			RzDBEdit6->SetFocus();

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::RzDBEdit6KeyPress(TObject *Sender, wchar_t &Key)
{
if (Key==VK_RETURN) //
	{

			RzDBEdit7->SetFocus();

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::RzDBEdit7KeyPress(TObject *Sender, wchar_t &Key)
{
if (Key==VK_RETURN) //
	{

			RzDBEdit8->SetFocus();

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::RzDBEdit8KeyPress(TObject *Sender, wchar_t &Key)
{
if (Key==VK_RETURN) //
	{

			RzDBEdit9->SetFocus();

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::RzDBEdit9KeyPress(TObject *Sender, wchar_t &Key)
{
if (Key==VK_RETURN) //
	{

			RzDBEdit10->SetFocus();

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::RzDBEdit10KeyPress(TObject *Sender, wchar_t &Key)

{
if (Key==VK_RETURN) //
	{

			RzDBEdit11->SetFocus();

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::RzDBEdit11KeyPress(TObject *Sender, wchar_t &Key)

{
if (Key==VK_RETURN) //
	{

			RzDBEdit12->SetFocus();

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::RzDBEdit12KeyPress(TObject *Sender, wchar_t &Key)

{
if (Key==VK_RETURN) //
	{

			RzDBEdit2->SetFocus();

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::btnExit1Click(TObject *Sender)
{
	Query(edtQuery->Text );
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::btnExit2Click(TObject *Sender)
{
    GroupBox1->Enabled = true;
	edtQuery->Text = "" ;
	//
	RzDBEdit2->SetFocus();
	int i;
	i=123;
	String s;
	s=IntToStr(i);
	//ShowMessage(s);
	dsetPress->Append();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::btnExit3Click(TObject *Sender)
{
	if(!dsetPress->IsEmpty())
	{       if (dsetPress->FieldByName("id")->AsString =="") {
                    return;
                }
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = m_con ;
		AnsiString sql;
		sql = "select * from bs_bookcatalog where pressid = " + dsetPress->FieldByName("id")->AsString ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->IsEmpty() ) {
			dsetPress->Delete();
		}
		else
		{
                        ShowMsg(Handle ,"该记录有引用，不能删除！",3);

		}
		delete aq;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::btnExit4Click(TObject *Sender)
{

	if (dsetPress->Active && dsetPress->RecordCount > 0) {
               Screen->Cursor = crHourGlass;
		DbgridToExcel(dbgrdPress);
                Screen->Cursor =crDefault;
	}

}
//Excel导出函数
bool __fastcall TfrmPressAdmin::DbgridToExcel(TRzDBGrid* dbg)
{
	AnsiString temptext,path;

             	savedlg->FileName = "出版社信息";//StringReplace(cbclient->Text.Trim() +dbeditdanhao->Text ,"\\","-",TReplaceFlags()<<rfReplaceAll) + "入库单";
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = Sysutils::ExtractFilePath(savedlg->FileName .c_str()  );
		Name = Sysutils::ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".xls";
		path =  DBPath;
	}
	else
	{
    	return false;
	}
        if(FileExists(path))
        try {
            DeleteFileA(path);
        } catch (...) {
        return false;
        }

	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;
	if(k == 0)
	{
                ShowMsg(Handle ,"没有数据！",3);
		return false;
	}
	Variant     v;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",false);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
//  在Excel中成字符串显示
	v.OlePropertyGet("Cells",1,4).OlePropertySet("Value","出版社管理" );

	n = 1;

	int t1= 0;
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
		}
	}


       dbg->DataSource->DataSet->DisableControls();
	int t2 = dbg->DataSource ->DataSet ->RecordCount ;

	dbg->DataSource ->DataSet ->First();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				t1++;
				temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
				v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
			}
		}
		dbg->DataSource ->DataSet ->Next() ;
	}


        dbg->DataSource->DataSet->EnableControls();

        	try {
                v.OlePropertyGet("ActiveWorkbook").OleFunction("SaveAs", path.c_str());
                //	xWorkbook.OleFunction("SaveAs",path.c_str());
                v.OleFunction("Quit");
              //  vSheet = Unassigned;
                v = Unassigned;
	} catch (...) {
           return false;
	}
        MessageBox(0, "Excel 导出结束!","Excel导出", MB_OK | MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::btnExit5Click(TObject *Sender)
{
	try
	{
		if (RzDBEdit3->Text == "" && RzDBEdit4->Text == "") {
			ShowMsg(this->Handle,"请至少输入简称或全称！",3);
			return;
		}
		dsetPress->Post();
		GroupBox1->Enabled = false;
	}
	catch(...)
	{

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::btn1Click(TObject *Sender)
{
//	int j = dbgrdPressAdd->DataSource ->DataSet ->RecordCount ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::RzToolButton1Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void TfrmPressAdmin::OnHotKeyPress(DWORD vkCode)
{
	if(vkCode == VK_F6)
	{
    	 btnExit2Click(NULL);
	}
	if(vkCode == VK_ESCAPE)
	{
    	 RzToolButton1Click(NULL);
	}
}

void __fastcall TfrmPressAdmin::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPressAdmin::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F2) {  //添加
		 btnExit2->Click();
	}	if (Key == VK_F4) {     //保存
		btnExit5->Click();
	}
		if (Key == VK_F5) {      //删除
		btnExit3->Click();
	}
		if (Key == VK_F6) {      //导出
		btnExit4->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 70 ) {    //查询
		btnExit1->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		RzToolButton1->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmPressAdmin::BtnChangeOptionsClick(TObject *Sender)
{
	if (dsetPress->IsEmpty() ) {
		return;
	}
	GroupBox1->Enabled = true;
}
//---------------------------------------------------------------------------



void __fastcall TfrmPressAdmin::dbgrdPressCellClick(TColumn *Column)
{
	if (dsetPress->IsEmpty() ) {
        return;
	}
	GroupBox1->Enabled = false;
}
//---------------------------------------------------------------------------


