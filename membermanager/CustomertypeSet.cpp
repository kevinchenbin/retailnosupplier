//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CustomertypeSet.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmcustomertype *frmcustomertype;
//---------------------------------------------------------------------------
__fastcall Tfrmcustomertype::Tfrmcustomertype(TComponent* Owner,TADOConnection *cnn,int Type,int stgid)
	: TForm(Owner)
{
	Root = tvMemberType->Items->Item[0];
	quMemberType->Connection = cnn;
	type = Type;
        fstgid = stgid;
	if (type == 1) {
		tvMemberType->Items->Item[0]->Text = "供应商分类";
		this->Caption = "供应商分类";
	}
	else
	{
		tvMemberType->Items->Item[0]->Text = "客户分类";
		this->Caption = "客户分类";
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcustomertype::FormShow(TObject *Sender)
{
	AnsiString sql;
	sg = new TStringList;
	sql = "select ID,Name from CUST_Customertype where type = " + IntToStr(type);
	quMemberType->Close();
	quMemberType->SQL->Clear();
	quMemberType->SQL->Add(sql);
	quMemberType->Open();
	while(!quMemberType->Eof )
	{
	  AnsiString idtypename =  quMemberType->FieldByName("Name")->AsAnsiString.Trim();
	  tvMemberType->Items->AddChild(Root,idtypename);
	  quMemberType->Next();
	}
	tvMemberType->AutoExpand = true;
	edTypeName->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcustomertype::BtnAddClick(TObject *Sender)
{
	savemodle = 1; //1为添加
	edTypeName->Text = "";
	edTypeName->Enabled = true;
	edTypeName->SetFocus();
	BtnChangeOptions->Enabled = false;
	BtnSave->Enabled = true;
	AnsiString sql;
	sql = "select MAX(ID) as ID from CUST_Customertype";
	quMemberType->Close();
	quMemberType->SQL->Clear();
	quMemberType->SQL->Add(sql);
	quMemberType->Open();
	int memberid = quMemberType->FieldByName("ID")->AsInteger + 1;
	edMemberID->Text = IntToStr(memberid);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcustomertype::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcustomertype::BtnDeleteClick(TObject *Sender)
{
	if (tvMemberType->Selected->Level != 1){
		if (type == 1) {

                        ShowMsg(Handle ,"请选择供应商类型！",3);
		}
		else
		{

                          ShowMsg(Handle ,"请选择客户类型！",3);
		}
	}
	else
	{
		AnsiString idtypename =  tvMemberType->Selected->Text;
		AnsiString sql,sdf ;
		sql = "select ID from CUST_CustomerInfo where customertype = (select ID from CUST_Customertype where Name = '" + idtypename + "' and type = " + IntToStr(type) + ") and  customerstate=1 and stgid="+IntToStr(fstgid);
		quMemberType->Close();
		quMemberType->SQL->Clear();
		quMemberType->SQL->Add(sql);
		quMemberType->Open();
		if (!quMemberType->IsEmpty()) {
			if (type == 1) {

                                ShowMsg(Handle ,"该供应商类型的供应商信息存在，不能删除该供应商类型！",0);
			}
			else
			{

                                ShowMsg(Handle ,"该客户类型的客户信息存在，不能删除该客户类型！",0);
			}

		}
		else
		{
			sql = "delete from CUST_Customertype where Name = '" + idtypename + "' and type = " + IntToStr(type)+" and stgid="+IntToStr(fstgid) ;
			if (type == 1) {
				sdf = "确认删除供应商类型："+Trim(tvMemberType->Selected->Text)+"吗？";
			}
			else
			{
				sdf = "确认删除客户类型："+Trim(tvMemberType->Selected->Text)+"吗？";
			}

			if (ShowMsg(Handle ,sdf.c_str() ,1)==1) {
				try {
					quMemberType->Close();
					quMemberType->SQL->Clear();
					quMemberType->SQL->Add(sql);
					quMemberType->ExecSQL();
					tvMemberType->Selected->Delete();
					edTypeName->Text = "";
				} catch (Exception &E) {
                                        ShowMsg(Handle ,"该数据跟系统其他数据有关联，不能删除！",3);
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcustomertype::tvMemberTypeClick(TObject *Sender)
{
	AnsiString sql;
	BtnAdd->Enabled = true;
	BtnChangeOptions->Enabled = true;
	BtnSave->Enabled = false;
	edTypeName->Enabled = false;
	AnsiString idtypename =  tvMemberType->Selected->Text;
	sql = "select * from CUST_Customertype where Name = '" + idtypename + "' and type = " + IntToStr(type) ;
	quMemberType->Close();
	quMemberType->SQL->Clear();
	quMemberType->SQL->Add(sql);
	quMemberType->Open();
	if (tvMemberType->Selected->Level == 1) {
		edMemberID->Text = quMemberType->FieldByName("ID")->AsString ;
		edTypeName->Text = idtypename;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcustomertype::BtnChangeOptionsClick(TObject *Sender)
{
	BtnAdd->Enabled = false;
	BtnSave->Enabled = true;
	if (savemodle == 1 && edTypeName->Enabled) {

                ShowMsg(Handle ,"现在为添加状态，不能修改！",3);

	}
	else
	{
		edTypeName->Enabled = true;
	}
	savemodle = 2; //2为修改
	edTypeName->SetFocus();
	if (tvMemberType->Selected->Level != 1){
		if (type == 1) {
                        ShowMsg(Handle ,"请选择一条供应商类型！",3);
		}
		else
		{

                         ShowMsg(Handle ,"请选择一条客户类型！",3);
		}
	}
	else
	{
		AnsiString idtypename =  tvMemberType->Selected->Text;
	}
}
//---------------------------------------------------------------------------


//添加保存函数
void __fastcall Tfrmcustomertype::Addsave()
{
	AnsiString sql,sdf;
	sql = "select * from CUST_Customertype where Name = '" + edTypeName->Text + "' and type = " + IntToStr(type);
	quMemberType->Close();
	quMemberType->SQL->Clear();
	quMemberType->SQL->Add(sql);
	quMemberType->Open();
	if (edTypeName->Text == "") {
		if (type == 1) {

                        ShowMsg(Handle ,"供应商类型名称不能为空！",3);
		}
		else
		{

                        ShowMsg(Handle ,"客户类型名称不能为空！",3);
		}

	}
	else
	{
			if (!quMemberType->IsEmpty() ) {
				if (type == 1) {

                                        ShowMsg(Handle ,"该供应商类型已添加！",3);
				}
				else
				{

                                        ShowMsg(Handle ,"该客户类型已添加！",3);
				}
			}
			else
			{

				if (type == 1) {
					sdf =  "确认添加供应商类型："+edTypeName->Text+"吗？";
				}
				else
				{
					sdf =  "确认添加客户类型："+edTypeName->Text+"吗？";
				}
				if (ShowMsg(Handle ,sdf.c_str(),1)==1) {
                                 ;
					if (quMemberType->State != dsInsert) {
						quMemberType->Append();
					}
					if (quMemberType->State == dsInsert) {
						quMemberType->FieldByName("Name")->AsString = edTypeName->Text;
						quMemberType->FieldByName("type")->AsInteger = type;
						quMemberType->Post();
                                                sql = "select max(ID) as ID from CUST_Customertype";
						quMemberType->Close();
						quMemberType->SQL->Clear();
						quMemberType->SQL->Add(sql);
						quMemberType->Open();
						AnsiString addname = edTypeName->Text.Trim() ;
						tvMemberType->Items->AddChild(Root,addname);
						//tvMemberType->Items->AddChildObject(Root,addname,(TObject *)quMemberType->FieldByName("ID")->AsInteger);
						sg->AddObject(addname,(TObject *)quMemberType->FieldByName("ID")->AsInteger);
						edTypeName->Enabled = false;
						BtnAdd->Enabled = true;
						BtnChangeOptions->Enabled = true;
						BtnSave->Enabled = false;
					}
				}
			}
	}
}
//---------------------------------------------------------------------------

//修改保存函数
void __fastcall Tfrmcustomertype::Changesave()
{
	savemodle = 2; //2为修改
	edTypeName->Enabled = true;
	if (tvMemberType->Selected->Level != 1){
		if (type == 1) {

                        ShowMsg(Handle ,"请选择一条供应商类型！",3);
		}
		else
		{

                        ShowMsg(Handle ,"请选择一条客户类型！",3);
		}
	}
	else
	{
		AnsiString sql,sdf;
		AnsiString idtypename =  tvMemberType->Selected->Text.Trim() ;
		sql = "select ID from CUST_CustomerInfo where customertype = (select ID from CUST_Customertype where Name = '" + idtypename + "' and type = " + IntToStr(type) + ") and  customerstate=1 and stgid="+IntToStr(fstgid);
		quMemberType->Close();
		quMemberType->SQL->Clear();
		quMemberType->SQL->Add(sql);
		quMemberType->Open();
		if (!quMemberType->IsEmpty()) {
			if (type == 1) {
                                  ShowMsg(Handle ,"该供应商的供应商信息存在，不能修改该供应商类型！",3);
			}
			else
			{

                                  ShowMsg(Handle ,"该客户类型的客户信息存在，不能修改该客户类型！",3);
			}
		}
		else
		{
			sql = "update CUST_Customertype set Name = '" + Trim(edTypeName->Text)+ "' where Name = '" + idtypename + "' and type = " + IntToStr(type) ;
			if (type == 1) {
				sdf = "确认修改供应商类型："+idtypename+"吗？";
			}
			else
			{
				sdf = "确认修改客户类型："+idtypename+"吗？";
			}
			if (ShowMsg(Handle ,sdf.c_str(),1)==1) {


				try {
					quMemberType->Close();
					quMemberType->SQL->Clear();
					quMemberType->SQL->Add(sql);
					quMemberType->ExecSQL();
					AnsiString addname = edTypeName->Text.Trim() ;
					tvMemberType->Selected->Text = addname;
					edTypeName->Enabled = false;
					BtnAdd->Enabled = true;
					BtnChangeOptions->Enabled = true;
					BtnSave->Enabled = false;
				} catch (Exception &E) {
                                        ShowMsg(Handle ,"该数据跟系统其他数据有关联，不能修改！",3);

				}
			}
		}
	}
}
//---------------------------------------------------------------------------


void __fastcall Tfrmcustomertype::BtnSaveClick(TObject *Sender)
{
	if (edTypeName->Text == "") {
		if (type == 1) {
                        ShowMsg(Handle ,"供应商类型名称不能为空！",3);

		}
		else
		{
                        ShowMsg(Handle ,"客户类型名称不能为空！",3);
		}
		return;
	}
	if (savemodle == 1) {
		Addsave();
	}
	else if (savemodle == 2) {
		Changesave();
	}
	else
	{}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcustomertype::edTypeNameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		BtnSave->Click();
	}
}
//---------------------------------------------------------------------------


void __fastcall Tfrmcustomertype::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcustomertype::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F2) {
		BtnAdd->Click();
	}
	if (Key == VK_F3) {
		BtnChangeOptions->Click();
	}
	if (Key == VK_F4) {
		BtnSave->Click();
	}
	if (Key == VK_F5) {
		BtnDelete->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==81) {
		BtnExit->Click();
	}
}
//---------------------------------------------------------------------------

