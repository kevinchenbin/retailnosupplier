//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CoustomerImport.h"
#include "global.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzRadChk"
#pragma link "RzPanel"
#pragma link "RzShellDialogs"
#pragma link "RzPrgres"
#pragma resource "*.dfm"
TFormCousImport *FormCousImport;
//---------------------------------------------------------------------------
__fastcall TFormCousImport::TFormCousImport(TComponent* Owner,TADOQuery * query,int type,int stgid )
	: TForm(Owner)
{
	Type = type;
	Import = true;
        fstgid = stgid;
	if (Type == 1) {
		this->Caption = "��Ӧ�����ݵ���";
		chsaleman->Caption = "�ɹ�Ա";
		cbname->Caption = "��Ӧ������";
	}
	if (Type == 2) {
		this->Caption = "�ͻ����ݵ���";
		cbname->Caption = "�ͻ�����";
	}
	dsdg = query;
	aqdetail->Connection = query->Connection ;
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
		if (ShowMsg(this->Handle,"ȷ��Ҫ���룿",1) != 1) {
			return;
		}
		lblExcel->Visible = true;
		lblExcel->Caption = "�������ڽ���,���Ժ�...";
	}
	Import= false;
	AnsiString sql;

	AnsiString str = "Provider=Microsoft.Jet.OLEDB.4.0;Extended Properties=Excel 8.0;Persist Security Info=false;Data Source=";
	//EXCEL����
	str = str + edtExcelPath->Text ;
       //	adotable->ConnectionString = "";
	try
	{
		con1->ConnectionString =  str ;
	}
	catch(...)
	{
		ShowMsg(this->Handle,"�������Ѿ����룡",3);
		Import = true;
		return;
	}

	try
	{
		 con1->Connected  = true;
	}
	catch(...)
	{
		ShowMsg(this->Handle,"����Դ���ô���",3);
		Import= true;
		return;
	}
	Import= false;

	adotable->Connection = con1;
	TStrings *list;
	list = new TStringList();
	con1->GetTableNames(list,true);  //ȡ�ñ���
	AnsiString aa =  list->Strings[0];
	adotable->TableName = list->Strings[0];

	try
	{
		adotable->Active = true;
	}
	catch(...)
	{
		ShowMsg(this->Handle,"����Դ���ô���",3);
		Import= true;
		return;
	}

      //	pb->Max = adotable->RecordCount;
	Sleep(10);
	int inportamount = 0;
	int n = 0;
	int p= 1;

	while (!adotable->Eof)
	{
		p++;
	      //	pb->Position = p;
		dsdg->Active = true;
		if (dsdg->State != dsInsert) {
			dsdg->Append();
		}
                dsdg->FieldByName("stgid")->AsInteger  =fstgid;
		dsdg->FieldByName("Type")->AsInteger  = Type;
		if (cbname->Checked ) {
			try {
				dsdg->FieldByName("Name")->AsString = adotable->FieldByName("����")->AsString;
			} catch (...) {
				ShowMsg(this->Handle,"��ȷ�ϵ����ļ��������У�",3);
				Import= true;
				return;
			}
		}
		if (cbaddress->Checked ) {
			try {
				dsdg->FieldByName("Address")->AsString = adotable->FieldByName("��ַ")->AsString;
			} catch (...) {
				ShowMsg(this->Handle,"��ȷ�ϵ����ļ��е�ַ�У�",3);
				Import= true;
				return;
			}
		}
		if (cbcode->Checked ) {
			try {
				dsdg->FieldByName("Code")->AsString = adotable->FieldByName("�ʱ�")->AsString;
			} catch (...) {
				ShowMsg(this->Handle,"��ȷ�ϵ����ļ����ʱ��У�",3);
				Import= true;
				return;
			}
		}
		if (cbtelphone->Checked ) {
			try {
				dsdg->FieldByName("Telephone")->AsString  = adotable->FieldByName("�绰")->AsString;
			} catch (...) {
				ShowMsg(this->Handle,"��ȷ�ϵ����ļ��е绰�У�",3);
				Import= true;
				return;
			}
		}
		if (cbfax->Checked ) {
			try {
				dsdg->FieldByName("Fax")->AsString = adotable->FieldByName("����")->AsString;
			} catch (...) {
				ShowMsg(this->Handle,"��ȷ�ϵ����ļ��д����У�",3);
				Import= true;
				return;
			}
		}
		if (cbcontex->Checked ) {
			try {
				dsdg->FieldByName("Contact")->AsString = adotable->FieldByName("��ϵ��")->AsString;
			} catch (...) {
				ShowMsg(this->Handle,"��ȷ�ϵ����ļ�����ϵ���У�",3);
				Import= true;
				return;
			}
		}
		if (cbdate->Checked ) {
			try {
				dsdg->FieldByName("Date")->Value  = adotable->FieldByName("����")->Value ;
			} catch (...) {
				ShowMsg(this->Handle,"��ȷ�ϵ����ļ��������У����ڸ�ʽ��ȷ��",3);
				Import= true;
				return;
			}
		}
		if (chsaleman->Checked ) {
			try {
				dsdg->FieldByName("Salesman")->AsString  = adotable->FieldByName("ҵ��Ա")->AsString  ;
			} catch (...) {
				ShowMsg(this->Handle,"��ȷ�ϵ����ļ���ҵ��Ա�У�",3);
				Import= true;
				return;
			}
		}
		if (cbarea->Checked ) {
			try {
				dsdg->FieldByName("Local")->AsString = adotable->FieldByName("����")->AsString ;
			} catch (...) {
				ShowMsg(this->Handle,"��ȷ�ϵ����ļ��������У�",3);
				Import= true;
				return;
			}
		}
      //  dsdg->FieldByName("cstate")->AsBoolean=true;
		dsdg->Append() ;
		adotable->Next();
		n = n + 1;
	}
	dsdg->UpdateBatch(arAll);
	sql = "insert into CUST_CustomerStartMoney(CustomerID) select "
			" id from CUST_CustomerInfo where id not in(select CustomerID from CUST_CustomerStartMoney) and stgid ="+IntToStr(fstgid);
	aqdetail->Close();
	aqdetail->SQL->Clear();
	aqdetail->SQL->Add(sql);
	aqdetail->ExecSQL();
	lblExcel->Caption = "EXCEL������ϣ�";
	ShowMsg(this->Handle,"���ݵ���ɹ���",3);
	Import= true;
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------
void __fastcall TFormCousImport::BtnExitClick(TObject *Sender)
{
	if (Import) {
		Close();
	}else
	{
		ShowMsg(this->Handle,"���ڵ����У������˳���",3);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormCousImport::cballcheckClick(TObject *Sender)
{
	if (cballcheck->Checked ) {
		cbname->Checked = true;
		cbaddress->Checked = true;
		cbcontex->Checked = true;
		cbtelphone->Checked = true;
		cbfax->Checked = true;
		cbcode->Checked = true;
		chsaleman->Checked = true;
		cbdate->Checked = true;
		cbbalance->Checked = true;
		cbarea->Checked = true;
	}
	else
	{
		cbname->Checked = false;
		cbaddress->Checked = false;
		cbcontex->Checked = false;
		cbtelphone->Checked = false;
		cbfax->Checked = false;
		cbcode->Checked = false;
		chsaleman->Checked = false;
		cbdate->Checked = false;
		cbbalance->Checked = false;
		cbarea->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormCousImport::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TFormCousImport::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F7) {     //����
		BtnImport->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //��С��
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //�˳�
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //�ָ�����
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

