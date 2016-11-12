//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CoustomerImport.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzRadChk"
#pragma link "RzPanel"
#pragma link "RzPrgres"
#pragma link "RzShellDialogs"
#pragma resource "*.dfm"
TFormCousImport *FormCousImport;
//---------------------------------------------------------------------------
__fastcall TFormCousImport::TFormCousImport(TComponent* Owner,TADOQuery * query,int type)
	: TForm(Owner)
{
	Type = type;
	Import = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormCousImport::btselectpathClick(TObject *Sender)
{
	if (opndlgExcelPath->Execute())
	{
		String DBPath,Name;
		DBPath = ExtractFilePath(opndlgExcelPath->FileName .c_str()  );
		Name = ExtractFileName(opndlgExcelPath->FileName .c_str() );
		DBPath = DBPath + Name;
		edtExcelPath->Text = DBPath;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormCousImport::BtnImportClick(TObject *Sender)
{
	if(edtExcelPath->Text == "")
	return;
	else
	{
		MessageBoxA(0,"确定要导入？","Excel导入",MB_ICONQUESTION);
		lblExcel->Visible = true;
		lblExcel->Caption = "导入正在进行,请稍后...";
	}
	Import= false;
	Variant vExcelApp,vSheet,Wb;
	vExcelApp = Variant::CreateObject("Excel.Application");
	AnsiString s = ExtractFilePath(opndlgExcelPath->FileName .c_str());
	s = s + ExtractFileName(opndlgExcelPath->FileName .c_str() );
	vExcelApp.OlePropertyGet("WorkBooks").OleProcedure("Open",s.c_str()   );// opndlgExcelPath->f  FileName .c_str() );
	Wb = vExcelApp.OlePropertyGet("ActiveWorkBook");
	vSheet = Wb.OlePropertyGet("ActiveSheet");
	vSheet.OlePropertySet("name","11");
	Wb.OleProcedure("Save");
	Wb.OleProcedure("Close");
	vExcelApp.OleFunction("Quit");
	String sql = "select * from [11$]" ;
//	sql = sql + vSheet;
//	sql = sql + "$]";
	String str = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=";
	str = str + edtExcelPath->Text ;
	str = str + ";Mode=Read;Extended Properties=Excel 8.0;Persist Security Info=False";
	 //C:\\Documents and Settings\\Administrator\\桌面\\11.xls;Mode=Read;Extended Properties=Excel 8.0;Persist Security Info=False";

	//con1->Provider = "Microsoft.Jet.OLEDB.4.0";
	con1->ConnectionString = "";
	try
	{
		con1->ConnectionString =  str ;
	}
	catch(...)
	{
			MessageBoxA(0,"该数据已经导入！","Excel导入",MB_ICONEXCLAMATION);
			Import = true;
			return;
	}
	con1->LoginPrompt = false;
	con1->ConnectOptions = coConnectUnspecified ;
	con1->KeepConnection = true;
	con1->Mode = cmRead;
	try
	{
		 con1->Connected = true;
	}
	catch(...)
	{
		MessageBoxA(0,"数据源配置错误！","Excel导入",MB_ICONHAND);
		Import= true;
		return;
	}
	qry1->Connection = con1;
	qry1->Active = false;
	qry1->SQL->Clear();
	qry1->SQL ->Add(sql);
	qry1->Active = true;
	ds1->DataSet = qry1;

	//int j = qry1->DataSource ->DataSet ->RecordCount ;
	int j = qry1->RecordCount ;
	float percent = 0;
	for(int i=1;i<=j;i++)
	{

		qry1->Active = true;
		dsdg->Active = true;
		if (dsdg->State != dsInsert) {
        	dsdg->Append();
		}
		if (cbtype->Checked ) {
			dsdg->FieldByName("Type")->AsString = qry1->FieldByName("Type")->AsString;
		}
		if (cbname->Checked ) {
			dsdg->FieldByName("Name")->AsString = qry1->FieldByName("Name")->AsString;
		}
		if (cbaddress->Checked ) {
			dsdg->FieldByName("Address")->AsString = qry1->FieldByName("Address")->AsString;
		}
		if (cbcode->Checked ) {
			dsdg->FieldByName("Code")->AsString = qry1->FieldByName("Code")->AsString;
		}
		if (cbtelphone->Checked ) {
			dsdg->FieldByName("Telephone")->AsString = qry1->FieldByName("Telephone")->AsString;
		}
		if (cbfax->Checked ) {
			dsdg->FieldByName("Fax")->AsString = qry1->FieldByName("Fax")->AsString;
		}
		if (cbcontex->Checked ) {
			dsdg->FieldByName("Contact")->AsString = qry1->FieldByName("Contact")->AsString;
		}
		if (cbdate->Checked ) {
			dsdg->FieldByName("Date")->Value  = qry1->FieldByName("Date")->Value ;
		}
		if (chsaleman->Checked ) {
			dsdg->FieldByName("Salesman")->AsString  = qry1->FieldByName("Salesman")->AsString  ;
		}
		if (cbbalance->Checked ) {
			dsdg->FieldByName("Balance")->Value  = qry1->FieldByName("Balance")->Value ;
		}
		if (cbarea->Checked ) {
			dsdg->FieldByName("Local")->Value  = qry1->FieldByName("Local")->Value ;
		}
		if (cbBsLessBus->Checked ) {
			dsdg->FieldByName("BookstoreLessBusiness")->Value  = qry1->FieldByName("BookstoreLessBusiness")->Value ;
		}
		if (cbBusLessBs->Checked ) {
			dsdg->FieldByName("BusinessLessBookstore")->Value  = qry1->FieldByName("BusinessLessBookstore")->Value ;
		}
		dsdg->Append();
		sql =  "select max(ID) as id from cust_customerinfo";
		aqdetail->Close();
		aqdetail->SQL->Clear();
		aqdetail->SQL->Add(sql);
		aqdetail->Open();
		int customerid = aqdetail->FieldByName("id")->AsInteger ;
		sql = "insert into CUST_CustomerStartMoney(CustomerID) values (" + IntToStr(customerid)  + ")" ;
		aqdetail->Close();
		aqdetail->SQL->Clear();
		aqdetail->SQL->Add(sql);
		aqdetail->ExecSQL();
		lbsum->Caption = IntToStr(j);
		lbnow->Caption = IntToStr(i);
		percent = i*100/j;
		prgrsbrExcelImport->Percent = percent;
		qry1->RecNo ++;

	}
	dsdg->Append();
	lblExcel->Caption = "EXCEL导入完毕！";
	MessageBoxA(0,"数据导入成功！","Excel导入",MB_ICONEXCLAMATION);
	Import= true;
	this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormCousImport::BtnExitClick(TObject *Sender)
{
	if (Import) {
		Close();
	}else
	{
		MessageBoxA(0,"正在导入中，不能退出！","Excel导入",MB_ICONASTERISK);
	}
}
//---------------------------------------------------------------------------
