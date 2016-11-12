//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "detailemessage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzPanel"
#pragma link "RzCmboBx"
#pragma resource "*.dfm"
TDetaileForm *DetaileForm;
//---------------------------------------------------------------------------
__fastcall TDetaileForm::TDetaileForm(TComponent* Owner,int type,int savamod,String id,TADOConnection *cnn,int stgid)
	: TForm(Owner)
{
	modsave = savamod;
	Type = type;
	ID = id;
        fstgid = stgid;
	aqinit->Connection = cnn;
	aqdetail->Connection = cnn;
	if (Type == 1) {
		if (modsave == 1) {
			this->Caption = "新供应商资料录入" ;
		}
		else
		{
			this->Caption = "供应商资料修改" ;
		}
		Label12->Visible = false;
		Label13->Visible = false;
		edlogname->Visible = false;
		edpassword->Visible = false;
	}
	if (Type == 2) {
		if (modsave == 1) {
			this->Caption = "新客户资料录入" ;
		}
		else
		{
			this->Caption = "客户资料修改" ;
		}
	}
}
//---------------------------------------------------------------------------
void TDetaileForm::Initsalesman()
{  	//初始化销售人员
   AnsiString sql ,value;
   sql = "select * from SYS_StaffInfo where Career = 1";
   if (Type==2) {
		sql = "select * from SYS_StaffInfo where Career = 2";
        RzLabel9->Caption = "业务员";
   }
   aqinit->Close();
   aqinit->SQL->Clear();
   aqinit->SQL->Add(sql);
   aqinit->Open();
   while(!aqinit->Eof )
   {
	 CBsale->AddItem(aqinit->FieldByName("Name")->AsString ,(TObject*)aqinit->FieldByName("ID")->AsInteger );
	 aqinit->Next();
   }

   sql = "select * from dbo.Sys_shandongcity";
   aqinit->Close();
   aqinit->SQL->Clear();
   aqinit->SQL->Add(sql);
   aqinit->Open();
   while(!aqinit->Eof )
   {
	 cbdaozhan->AddItem(aqinit->FieldByName("cityname")->AsString ,(TObject*)aqinit->FieldByName("ID")->AsInteger );
	 aqinit->Next();
   }

}

//---------------------------------------------------------------------------
void TDetaileForm::InitLocalinfo()
{
	//初始化地区
	AnsiString sql ,value;
	sql = "select ID,local from SYS_local";
	aqinit->Close();
	aqinit->SQL->Clear();
	aqinit->SQL->Add(sql);
	aqinit->Open();
	while(!aqinit->Eof)
	{
		CBlocal->AddItem(aqinit->FieldByName("local")->AsAnsiString ,(TObject*)aqinit->FieldByName("ID")->AsInteger );
		aqinit->Next();
	}
}
//---------------------------------------------------------------------------
void TDetaileForm::InitType()
{
	//初始化地区
   AnsiString sql ,value;
   sql = "select ID,Name from CUST_Customertype where type = " + IntToStr(Type) ;
   aqinit->Close();
   aqinit->SQL->Clear();
   aqinit->SQL->Add(sql);
   aqinit->Open();
   while(!aqinit->Eof)
   {
	 cbtype->AddItem(aqinit->FieldByName("Name")->AsString,(TObject*)aqinit->FieldByName("ID")->AsInteger);
	 aqinit->Next();
   }
}
void __fastcall TDetaileForm::FormShow(TObject *Sender)
{
	dbedtName->SetFocus();
	if (modsave == 2) {
    	edtphone->SetFocus();
	}
	AnsiString sql;

	Initsalesman();
	InitLocalinfo();
	InitType();

	if (modsave == 2) {
		sql = "select * from CUST_CustomerInfo where ID = " + ID;
        aqinit->Close();
		aqinit->SQL->Clear();
		aqinit->SQL->Add(sql);
		aqinit->Open();
		dbedtName->Text = aqinit->FieldByName("Name")->AsString;
		dbeditContact->Text = aqinit->FieldByName("Contact")->AsString;
		edtphone->Text = aqinit->FieldByName("Telephone")->AsString;
		edtfax->Text = aqinit->FieldByName("Fax")->AsString;
		dbedit->Text = aqinit->FieldByName("Address")->AsString;
		edtcode->Text = aqinit->FieldByName("Code")->AsString;
		CBlocal->Text = aqinit->FieldByName("Local")->AsString;
		CBsale->Text = aqinit->FieldByName("Salesman")->AsString;
		edemail->Text = aqinit->FieldByName("Email")->AsString ;
		edsecondcontact->Text = aqinit->FieldByName("secondlyContact")->AsString ;
		edmobile->Text = aqinit->FieldByName("Mobile")->AsString ;
		edxinyong->Text = aqinit->FieldByName("CreditMoney")->AsString ;
		edbaozj->Text = aqinit->FieldByName("Bond")->AsString ;
		edbank->Text = aqinit->FieldByName("bank")->AsString ;
		edbankaccount->Text = aqinit->FieldByName("bankAccount")->AsString ;
		edqq->Text = aqinit->FieldByName("QQCode")->AsString ;
		edlogname->Text = aqinit->FieldByName("logname")->AsString ;
		edpassword->Text = aqinit->FieldByName("logpassword")->AsString ;
		cbtype->ItemIndex = cbtype->Items->IndexOfObject((TObject*)aqinit->FieldByName("customertype")->AsInteger );
                cbdaozhan->Text = aqinit->FieldByName("daozhan")->AsString ;
                edbk->Text = aqinit->FieldByName("bk")->AsString ;
	  //	dbedtName->Enabled = false;

	}
}
int TDetaileForm::getsalemanid(AnsiString name)
{
  int i;

	   i= CBsale->Items->IndexOf(name) ;
	   if (i!=-1) {
            return (int)CBsale->Items->Objects[i];
	   }else return -1;

}
//---------------------------------------------------------------------------
void __fastcall TDetaileForm::BtnSaveClick(TObject *Sender)
{
	AnsiString sql,sdf;

    if (dbedtName->Text == "") {
		ShowMsg(Handle ,"请输入单位名称！",3);
		return;
	}
	if (edxinyong->Text == "") {
		edxinyong->Text = "0";
	}
	if (edbaozj->Text == "") {
		edbaozj->Text = "0";
	}
        AnsiString salesmanID,LocalID;

		salesmanID = CBsale->Text.Trim();

        if (CBlocal->ItemIndex!=-1) {
          LocalID = IntToStr((int)(CBlocal->Items->Objects[CBlocal->ItemIndex]));
        }else LocalID=-1;
	if (modsave == 1) {
        if (Type == 1) {
			sql = "select * from CUST_CustomerInfo where type = 1 and customerstate=1 and stgid="+IntToStr(fstgid)+" and Name = '" + dbedtName->Text.Trim() + "'";
			aqdetail->Close();
			aqdetail->SQL->Clear();
			aqdetail->SQL->Add(sql);
			aqdetail->Open();
			if (aqdetail->RecordCount > 0) {
				ShowMsg(Handle ,"该供应商已经录入，请确认！",3);
				return;
			}
		}
		else {
			sql = "select * from CUST_CustomerInfo where type = 2 and customerstate=1 and stgid="+IntToStr(fstgid)+" and Name = '" + dbedtName->Text.Trim() + "'";
			aqdetail->Close();
			aqdetail->SQL->Clear();
			aqdetail->SQL->Add(sql);
			aqdetail->Open();
			if (aqdetail->RecordCount > 0) {
				ShowMsg(Handle ,"该客户已经录入，请确认！",3);
				return;
			}
		}


		int memtype;
		if (cbtype->Text != "") {
			try {
				memtype =  int(cbtype->Items->Objects[cbtype->ItemIndex]);
			} catch (...) {
				ShowMsg(Handle ,"请选择正确的类别！",3);
				return;
			}
		}



			if (cbtype->Text != "") {
				sql = "Insert into cust_customerinfo(Type,name,contact,telephone,fax,salesman,code,date,address,local,PrentID,Email,bank,bankAccount,secondlyContact,QQCode,logname,logpassword,customertype,Mobile,CreditMoney,Bond,bk,stgid,daozhan,customerstate) ";
				sql = sql + " values("+StrToInt(Type) + ",'" + dbedtName->Text + "','" + dbeditContact->Text.Trim()+"','" + edtphone->Text + "','";
				sql = sql + edtfax->Text.Trim() + "','" + salesmanID + "','" + edtcode->Text.Trim();
				sql = sql + "',GetDate(),'" +  dbedit->Text.Trim()+ "'," + LocalID + "," + IntToStr(ParentID)  + ",'" + edemail->Text + "','";
				sql = sql + edbank->Text + "','" + edbankaccount->Text + "','";
				sql = sql + edsecondcontact->Text + "','" + edqq->Text + "','" + edlogname->Text + "','" + edpassword->Text + "',";
				sql = sql + IntToStr(int(cbtype->Items->Objects[cbtype->ItemIndex])) + ",'" + edmobile->Text + "'," + edxinyong->Text + "," + edbaozj->Text + ",'" + edbk->Text + "',"+IntToStr(fstgid)+",'"+cbdaozhan->Text+"',1)";
			}
			else
			{
				sql = "Insert into cust_customerinfo(Type,name,contact,telephone,fax,salesman,code,date,address,local,PrentID,Email,bank,bankAccount,secondlyContact,QQCode,logname,logpassword,Mobile,CreditMoney,Bond,bk,stgid,daozhan,customerstate) ";
				sql = sql + " values("+StrToInt(Type) + ",'" + dbedtName->Text + "','" + dbeditContact->Text.Trim()+"','" + edtphone->Text + "','";
				sql = sql + edtfax->Text.Trim() + "','" + salesmanID + "','" + edtcode->Text.Trim();
				sql = sql + "',GetDate(),'" +  dbedit->Text.Trim()+ "'," + LocalID + "," + IntToStr(ParentID)  + ",'" + edemail->Text + "','";
				sql = sql + edbank->Text + "','" + edbankaccount->Text + "','" ;
				sql = sql + edsecondcontact->Text + "','" + edqq->Text + "','" + edlogname->Text + "','" + edpassword->Text + "','" + edmobile->Text + "'," + edxinyong->Text + "," + edbaozj->Text + ",'" + edbk->Text + "',"+IntToStr(fstgid)+",'"+cbdaozhan->Text+"',1)";
			}

			if (Type == 1) {
				sdf = "确认添加供应商" + dbedtName->Text +"吗？" ;
			}
			if ((Type == 2) || (Type == 3)) {
				sdf = "确认添加客户" + dbedtName->Text +"吗？" ;
			}

			if (ShowMsg(Handle ,sdf.c_str(),1)==1) {
				//qudetail->Active = true;
				/*if (qudetail->State != dsInsert) {
					qudetail->Append();
				}
				qudetail->FieldByName("Type")->AsInteger = Type;
				qudetail->FieldByName("name")->AsString =  dbedtName->Text.Trim();
				qudetail->FieldByName("contact")->AsString =  dbeditContact->Text.Trim();
				qudetail->FieldByName("telephone")->AsString =  edtphone->Text.Trim();
				qudetail->FieldByName("fax")->AsString = edtfax->Text.Trim();
				qudetail->FieldByName("salesman")->AsString   = salesmanID;
				qudetail->FieldByName("code")->AsString = edtcode->Text.Trim();
				qudetail->FieldByName("date")->AsDateTime = Date();
				qudetail->FieldByName("address")->AsString =  dbedit->Text.Trim();
				qudetail->FieldByName("local")->AsString   =  LocalID;
				qudetail->Edit() ;*/
				aqdetail->Close();
				aqdetail->SQL->Clear();
                                aqdetail->SQL->Add("declare @ret int;");
				aqdetail->SQL->Add(sql+";");
                                aqdetail->SQL->Add("set @ret = SCOPE_IDENTITY();");
                                aqdetail->SQL->Add("select @ret as clientid;");

				aqdetail->Open();
                                clientid = aqdetail->FieldByName("clientid")->AsInteger;

				sql =  "select max(ID) as id from cust_customerinfo where stgid ="+IntToStr(fstgid);
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
				this->Close();
			}
	}
	if (modsave == 2) {
		AnsiString sql,sdf;
		sql = "update cust_customerinfo set name = '" +dbedtName->Text +"',Contact = '" + dbeditContact->Text.Trim()+ "',Telephone = '";
		sql = sql + edtphone->Text + "',Fax = '" + edtfax->Text.Trim() + "',Address = '" + dbedit->Text.Trim();
		sql = sql + "',Code = '" + edtcode->Text.Trim() +"',local = " + LocalID + ",salesman = '" + CBsale->Text.Trim() + "',Email = '";
		sql = sql + edemail->Text + "',bank = '" + edbank->Text + "',bankAccount = '" + edbankaccount->Text;
		sql = sql + "',secondlyContact = '";

		sql = sql + edsecondcontact->Text + "',QQCode = '" + edqq->Text + "',bk='"+edbk->Text+"',logname = '" + edlogname->Text + "',logpassword = '" + edpassword->Text + "'";
		sql = sql + ",Mobile = '" + edmobile->Text + "',CreditMoney = " + edxinyong->Text + ",Bond = " + edbaozj->Text +",daozhan='"+cbdaozhan->Text+"'";
		if (cbtype->Text != "") {
			sql = sql + ",customertype = " + IntToStr(int(cbtype->Items->Objects[cbtype->ItemIndex]));
		}
		sql = sql + " where ID = " + ID;

		if (Type == 1) {
			sdf = "确认修改供应商" + dbedtName->Text +"吗？" ;
		}
		if (Type == 2) {
			sdf = "确认修改客户" + dbedtName->Text +"吗？" ;
		}

		if (ShowMsg(Handle ,sdf.c_str(),1)==1) {
			try {
				aqinit->Close();
				aqinit->SQL->Clear();
				aqinit->SQL->Add(sql);
				aqinit->ExecSQL();
				this->Close();
			} catch (Exception &E) {

                                ShowMsg(Handle ,"该数据跟系统其他数据有关联，不能修改！",3);
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TDetaileForm::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::dbedtNameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		dbeditContact->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::edtphoneKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		edxinyong->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::dbeditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == '\r') {
    	edbk->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::CBlocal1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		dbeditContact->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::dbeditContactKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		edmobile->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::edtfaxKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		edsecondcontact->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::edtcodeKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		edqq->SetFocus();
	}
}
//---------------------------------------------------------------------------


void __fastcall TDetaileForm::edsecondcontactKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        CBlocal->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::edemailKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        edbank->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::edmsnaddressKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        edqq->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::edqqKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        edemail->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::edbankKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        cbtype->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::edbankaccountKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		if (Type == 1) {
			dbedit->SetFocus();
		}
		else
		{
			edlogname->SetFocus();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::edlognameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        edpassword->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::edpasswordKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key == VK_RETURN) {
		dbedit->SetFocus();
	}
}
//---------------------------------------------------------------------------



void __fastcall TDetaileForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F4) {     //保存
		BtnSave->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //退出
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::CBlocalKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
		CBsale->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::CBsaleKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		edtcode->SetFocus();
	}
}
//---------------------------------------------------------------------------


void __fastcall TDetaileForm::edmobileKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		edtphone->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::edxinyongKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		edbaozj->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::edbaozjKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		edtfax->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::cbtypeKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		edbankaccount->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::edbkKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TDetaileForm::editdaozhanKeyPress(TObject *Sender, wchar_t &Key)
{
    if (Key == VK_RETURN) {

       AnsiString sql = "select * from dbo.Sys_shandongcity where cityname like '%"+editdaozhan->Text+"%'";
   aqinit->Close();
   aqinit->SQL->Clear();
   aqinit->SQL->Add(sql);
   aqinit->Open();
   cbdaozhan->Clear();
   while(!aqinit->Eof )
   {
	 cbdaozhan->AddItem(aqinit->FieldByName("cityname")->AsString ,(TObject*)aqinit->FieldByName("ID")->AsInteger );
	 aqinit->Next();
   }
    if (cbdaozhan->Items->Count>0) {
         cbdaozhan->ItemIndex=0;
    }


	}
}
//---------------------------------------------------------------------------


void __fastcall TDetaileForm::FormClose(TObject *Sender, TCloseAction &Action)
{
     Action=caFree;
}
//---------------------------------------------------------------------------

