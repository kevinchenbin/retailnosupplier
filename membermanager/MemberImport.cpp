//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MemberImport.h"
#include "global.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzRadChk"
#pragma link "RzPanel"
#pragma link "RzPrgres"
#pragma link "RzShellDialogs"
#pragma resource "*.dfm"
TFormMemImport *FormMemImport;
//---------------------------------------------------------------------------
__fastcall TFormMemImport::TFormMemImport(TComponent* Owner,TADOQuery * query)
	: TForm(Owner)
{
	Import = true;
	dsdg = query ;
	aq->Connection = query->Connection ;
}
//---------------------------------------------------------------------------
void __fastcall TFormMemImport::btselectpathClick(TObject *Sender)
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
void __fastcall TFormMemImport::BtnImportClick(TObject *Sender)
{
	if(edtExcelPath->Text == "")
		return;
	else
	{
		if (ShowMsg(this->Handle,"确定要导入？",1) != 1) {
			return;
		}
		lblExcel->Visible = true;
		lblExcel->Caption = "导入正在进行,请稍后...";
	}
	Import= false;
	AnsiString sql;

	AnsiString str = "Provider=Microsoft.Jet.OLEDB.4.0;Extended Properties=Excel 8.0;Persist Security Info=false;Data Source=";
	//EXCEL导入
	str = str + edtExcelPath->Text ;
	adotable->ConnectionString = "";
	try
	{
		con1->ConnectionString =  str ;
	}
	catch(...)
	{
		ShowMsg(this->Handle,"该数据已经导入！",3);
		Import = true;
		return;
	}

	try
	{
		 con1->Connected  = true;
	}
	catch(...)
	{
		ShowMsg(this->Handle,"数据源配置错误！",3);
		Import= true;
		return;
	}
	Import= false;

	adotable->Connection = con1;
	TStrings *list;
	list = new TStringList();
	con1->GetTableNames(list,true);  //取得表名
	AnsiString aa =  list->Strings[0];
	adotable->TableName = list->Strings[0];

	try
	{
		adotable->Active = true;
	}
	catch(...)
	{
		ShowMsg(this->Handle,"数据源配置错误！",3);
		Import= true;
		return;
	}

	pb->Max = adotable->RecordCount;
	Sleep(10);
	int inportamount = 0;
	int p= 1;

	while (!adotable->Eof)
	{
		p++;
		pb->Position = p;
		dsdg->Active = true;
		if (dsdg->State != dsInsert) {
			dsdg->Append();
		}
		if (cbtype->Checked ) {
			AnsiString tyname,sql;
			try {
				tyname = adotable->FieldByName("类别")->AsString;
			} catch (...) {
				ShowMsg(this->Handle,"请确认导入文件有类别列！",3);
				Import= true;
				return;
			}
			sql = "select * from CUST_MemberType where type = '" + tyname + "'";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			if (aq->RecordCount > 0) {
				dsdg->FieldByName("MemberType")->AsInteger = aq->FieldByName("IDType")->AsInteger;
			}
			else
			{
				sql = "insert into CUST_MemberType(type,Discount) values('" + tyname + "',100)";
                aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->ExecSQL();
				sql = "select max(IDType) as ID from CUST_MemberType ";
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->Open();
				dsdg->FieldByName("MemberType")->AsInteger = aq->FieldByName("ID")->AsInteger;
			}
		}
		if (cbname->Checked ) {
        	try {
				dsdg->FieldByName("Name")->AsString = adotable->FieldByName("名称")->AsString;
			} catch (...) {
				ShowMsg(this->Handle,"请确认导入文件有名称列！",3);
				Import= true;
				return;
			}
		}
		if (cbcardid->Checked ) {
			try {
				dsdg->FieldByName("CardID")->AsString = adotable->FieldByName("卡号")->AsString;
				dsdg->FieldByName("CardSN")->AsString = adotable->FieldByName("卡号")->AsString;
			} catch (...) {
				ShowMsg(this->Handle,"请确认导入文件有卡号列！",3);
				Import= true;
				return;
			}
		}
		if (cbsex->Checked ) {
			try {
				if (adotable->FieldByName("性别")->AsString == "男") {
					dsdg->FieldByName("Sex")->AsInteger = 0;
				}
				else
				{
					dsdg->FieldByName("Sex")->AsInteger = 1;
				}
			} catch (...) {
				ShowMsg(this->Handle,"请确认导入文件有性别列！",3);
				Import= true;
				return;
			}
		}
		if (cbmobile->Checked ) {
			try {
				dsdg->FieldByName("Mobile")->AsString = adotable->FieldByName("手机")->AsString;
			} catch (...) {
				ShowMsg(this->Handle,"请确认导入文件有手机列！",3);
				Import= true;
				return;
			}
		}
		if (cbtelphone->Checked ) {
			try {
				dsdg->FieldByName("Tel")->AsString = adotable->FieldByName("电话")->AsString;
			} catch (...) {
				ShowMsg(this->Handle,"请确认导入文件有电话列！",3);
				Import= true;
				return;
			}
		}
		if (cbaddress->Checked ) {
			try {
				dsdg->FieldByName("Address")->AsString = adotable->FieldByName("地址")->AsString;
			} catch (...) {
				ShowMsg(this->Handle,"请确认导入文件有地址列！",3);
				Import= true;
				return;
			}
		}
		if (cbcode->Checked ) {
            try {
				dsdg->FieldByName("PostalCode")->AsString = adotable->FieldByName("邮编")->AsString;
			} catch (...) {
				ShowMsg(this->Handle,"请确认导入文件有邮编列！",3);
				Import= true;
				return;
			}
		}
		if (cbbirthday->Checked ) {
			try {
				dsdg->FieldByName("Birthday")->AsDateTime  = adotable->FieldByName("生日")->AsDateTime ;
			} catch (...) {
				ShowMsg(this->Handle,"请确认导入文件是否有生日列，日期格式是否正确！",3);
				Import= true;
				return;
			}
		}
		if (cbbalance->Checked ) {
			try {
				dsdg->FieldByName("Balance")->Value = adotable->FieldByName("余额")->Value ;
			} catch (...) {
				ShowMsg(this->Handle,"请确认导入文件是否有余额列，余额是否正确！",3);
				Import= true;
				return;
			}
		}
		if (chtotalcons->Checked ) {
			try {
				dsdg->FieldByName("TotalConsumption")->Value = adotable->FieldByName("总消费")->Value ;
			} catch (...) {
				ShowMsg(this->Handle,"请确认导入文件是否有总消费列，总消费是否正确！",3);
				Import= true;
				return;
			}
		}
		if (chjifen->Checked ) {
			try {
				dsdg->FieldByName("Memberdot")->Value = adotable->FieldByName("积分")->Value ;
			} catch (...) {
				ShowMsg(this->Handle,"请确认导入文件是否有积分列，积分是否正确！",3);
				Import= true;
				return;
			}
		}
		if (chyxdate->Checked ) {
			try {
				dsdg->FieldByName("youxiaodate")->Value = adotable->FieldByName("有效日期")->Value ;
			} catch (...) {
				ShowMsg(this->Handle,"请确认导入文件是否有有效日期列，有效日期格式是否正确！",3);
				Import= true;
				return;
			}
		}
		dsdg->Append() ;
		adotable->Next();
	}
	dsdg->UpdateBatch(arAll);
	lblExcel->Caption = "EXCEL导入完毕！";
	ShowMsg(this->Handle,"数据导入成功！",3);
	Import= true;
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------
void __fastcall TFormMemImport::BtnExitClick(TObject *Sender)
{
	if (Import) {
		Close();
	}else
	{
		ShowMsg(this->Handle,"正在导入中，不能退出！",3);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormMemImport::cballcheckClick(TObject *Sender)
{
	if (cballcheck->Checked ) {
		cbtype->Checked = true;
		cbname->Checked = true;
		cbcardid->Checked = true;
		cbsex->Checked = true;
		cbmobile->Checked = true;
		cbtelphone->Checked = true;
		cbaddress->Checked = true;
		cbcode->Checked = true;
		cbbirthday->Checked = true;
		cbbalance->Checked = true;
		chtotalcons->Checked = true;
		chyxdate->Checked = true;
		chjifen->Checked = true;
	}
	else
	{
		cbtype->Checked = false;
		cbname->Checked = false;
		cbcardid->Checked = false;
		cbsex->Checked = false;
		cbmobile->Checked = false;
		cbtelphone->Checked = false;
		cbaddress->Checked = false;
		cbcode->Checked = false;
		cbbirthday->Checked = false;
		cbbalance->Checked = false;
		chtotalcons->Checked = false;
		chyxdate->Checked = false;
		chjifen->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMemImport::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
			if (Key == VK_F2) {
		 BtnImport->Click();
	   }

		if (Shift.Contains(ssCtrl)&& Key ==90) {
			WindowState = wsNormal  ;
		}
		if (Shift.Contains(ssCtrl)&& Key ==81  ) {
			BtnExit->Click();
		}

}
//---------------------------------------------------------------------------

