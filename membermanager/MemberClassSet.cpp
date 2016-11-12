//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MemberClassSet.h"
#include "global.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmmemclassmg *frmmemclassmg;
//---------------------------------------------------------------------------
__fastcall Tfrmmemclassmg::Tfrmmemclassmg(TComponent* Owner,TADOConnection *cnn)
	: TForm(Owner)
{
	Root = tvMemberType->Items->Item[0];
	quMemberType->Connection = cnn;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmmemclassmg::FormShow(TObject *Sender)
{
	AnsiString sql;
	sql = "select IDType,Type as T,discount from cust_membertype order by discount desc ";
	quMemberType->Close();
	quMemberType->SQL->Clear();
	quMemberType->SQL->Add(sql);
	quMemberType->Open();
	while(!quMemberType->Eof )
	{
	  AnsiString idtypename =  quMemberType->FieldByName("T")->AsAnsiString.Trim()  +  "(" + quMemberType->FieldByName("discount")->AsAnsiString + "%)";
	  tvMemberType->Items->AddChild(Root,idtypename);
	  quMemberType->Next();
	}
	tvMemberType->AutoExpand = true;
	edTypeName->Enabled = false;
	edTypeDiscount->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemclassmg::BtnAddClick(TObject *Sender)
{
	savemodle = 1; //1Ϊ���
	edTypeName->Text = "";
	edTypeName->Enabled = true;
	edTypeDiscount->Text = "100";
	edTypeDiscount->Enabled = true;
	edTypeName->SetFocus();
	BtnChangeOptions->Enabled = false;
	BtnSave->Enabled = true;
	AnsiString sql;
	sql = "select MAX(IDType) as IDType from CUST_MemberType";
	quMemberType->Close();
	quMemberType->SQL->Clear();
	quMemberType->SQL->Add(sql);
	quMemberType->Open();
	int memberid = quMemberType->FieldByName("IDType")->AsInteger + 1;
	edMemberID->Text = IntToStr(memberid);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemclassmg::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemclassmg::BtnDeleteClick(TObject *Sender)
{
	if (tvMemberType->Selected->Level != 1){
                ShowMsg(Handle ,"��ѡ��һ����Ա���ͣ�",3);
	}
	else
	{
        AnsiString idtypename =  tvMemberType->Selected->Text;
		idtypename = idtypename.SubString(0,idtypename.Pos("(")-1 );
		if (idtypename == "Ĭ�ϻ�Ա") {

                        ShowMsg(Handle ,"Ĭ�ϻ�Ա����ɾ����",3);
			return;
		}
		AnsiString sql,sdf ;
		sql = "select * from CUST_MemberInfo where CUST_MemberInfo.MemberType = (select IDType from CUST_MemberType where Type = '" + idtypename + "')";
		quMemberType->Close();
		quMemberType->SQL->Clear();
		quMemberType->SQL->Add(sql);
		quMemberType->Open();
		if (!quMemberType->IsEmpty()) {

                        ShowMsg(Handle ,"�û�Ա���͵Ļ�Ա��Ϣ���ڣ�����ɾ���û�Ա���ͣ�",3);
		}
		else
		{
			sql = "delete from CUST_MemberType where Type = '" + idtypename + "'";
			sdf = "ȷ��ɾ����Ա���ͣ�"+Trim(tvMemberType->Selected->Text)+"��";

			if (ShowMsg(Handle ,sdf.c_str(),1)==1) {
				try {
					quMemberType->Close();
					quMemberType->SQL->Clear();
					quMemberType->SQL->Add(sql);
					quMemberType->ExecSQL();
					tvMemberType->Selected->Delete();
					edTypeName->Text = "";
					edTypeDiscount->Text = "";
				} catch (Exception &E) {

                                         ShowMsg(Handle ,"�����ݸ�ϵͳ���������й���������ɾ����",3);
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemclassmg::tvMemberTypeClick(TObject *Sender)
{
	AnsiString sql;
	BtnAdd->Enabled = true;
	BtnChangeOptions->Enabled = true;
	BtnSave->Enabled = false;
	edTypeName->Enabled = false;
	edTypeDiscount->Enabled = false;
	AnsiString idtypename =  tvMemberType->Selected->Text;
	idtypename = idtypename.SubString(0,idtypename.Pos("(")-1 );
	sql = "select * from CUST_MemberType where Type = '" + idtypename + "'";
	quMemberType->Close();
	quMemberType->SQL->Clear();
	quMemberType->SQL->Add(sql);
	quMemberType->Open();
	if (tvMemberType->Selected->Level == 1) {
		edTypeDiscount->Text =  quMemberType->FieldByName("Discount")->AsString;
		edMemberID->Text = quMemberType->FieldByName("IDType")->AsString ;
		edTypeName->Text = idtypename;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemclassmg::BtnChangeOptionsClick(TObject *Sender)
{
	BtnAdd->Enabled = false;
	BtnSave->Enabled = true;
	if (savemodle == 1 && edTypeName->Enabled) {

                ShowMsg(Handle ,"����Ϊ���״̬�������޸ģ�",3);
	}
	else
	{
		edTypeName->Enabled = true;
		edTypeDiscount->Enabled = true;
	}
	savemodle = 2; //2Ϊ�޸�
	edTypeName->SetFocus();
	if (tvMemberType->Selected->Level != 1){

                ShowMsg(Handle ,"��ѡ��һ����Ա���ͣ�",3);
	}
	else
	{
		AnsiString idtypename =  tvMemberType->Selected->Text;
		idtypename = idtypename.SubString(0,idtypename.Pos("(")-1 );
		if (idtypename == "Ĭ�ϻ�Ա") {
			edTypeName->Enabled = false;
            edTypeDiscount->SetFocus();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemclassmg::edTypeDiscountClick(TObject *Sender)
{
	AnsiString IDiscount = edTypeDiscount->Text;
	int len = IDiscount.Pos("%")-1;
	if (IDiscount.Pos("%")!= 0 ) {
    	IDiscount = IDiscount.SubString(0,len);
	}
	edTypeDiscount->Text = IDiscount;
}
//---------------------------------------------------------------------------

//��ӱ��溯��
void __fastcall Tfrmmemclassmg::Addsave()
{
	AnsiString sql,sdf,IDiscount = edTypeDiscount->Text;
	int len = IDiscount.Pos("%")-1 ;
	if (IDiscount.Pos("%")!=0 ) {
		IDiscount =  IDiscount.SubString(0,len);
	}
	sql = "select * from CUST_MemberType where Type = '" + edTypeName->Text + "'" ;
	quMemberType->Close();
	quMemberType->SQL->Clear();
	quMemberType->SQL->Add(sql);
	quMemberType->Open();
	if (edTypeName->Text == "") {
                ShowMsg(Handle ,"�������Ʋ���Ϊ�գ�",3);
	}
	else
	{
		if (edTypeDiscount->Text == "") {

                        ShowMsg(Handle ,"�ۿ۲���Ϊ�գ�",3);
		}
		else
		{
			if (!quMemberType->IsEmpty() ) {

                                ShowMsg(Handle ,"�û�Ա��������ӣ�",3);
			}
			else
			{
				sdf =  "ȷ����ӻ�Ա���ͣ�"+edTypeName->Text+"��";
                                ;
				if (ShowMsg(Handle ,sdf.c_str(),1)==1) {
					if (quMemberType->State != dsInsert) {
						quMemberType->Append();
					}
					if (quMemberType->State == dsInsert) {
						quMemberType->FieldByName("Type")->AsString = edTypeName->Text;
						quMemberType->FieldByName("Discount")->AsFloat = StrToFloat(IDiscount);
						quMemberType->Post();
						AnsiString addname = edTypeName->Text.Trim() + "(" + edTypeDiscount->Text.Trim() + "%)";
						tvMemberType->Items->AddChild(Root,addname);
						edTypeName->Enabled = false;
						edTypeDiscount->Enabled = false;
						BtnAdd->Enabled = true;
						BtnChangeOptions->Enabled = true;
						BtnSave->Enabled = false;
					}
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

//�޸ı��溯��
void __fastcall Tfrmmemclassmg::Changesave()
{
	savemodle = 2; //2Ϊ�޸�
	edTypeName->Enabled = true;
	edTypeDiscount->Enabled = true;
	AnsiString IDiscount = edTypeDiscount->Text;
	int len = IDiscount.Pos("%")-1 ;
	if (IDiscount.Pos("%")!=0 ) {
		IDiscount =  IDiscount.SubString(0,len);
	}
	if (tvMemberType->Selected->Level != 1){
                ShowMsg(Handle ,"��ѡ��һ����Ա���ͣ�",3);
	}
	else
	{
		AnsiString sql,sdf ;
		AnsiString idtypename =  tvMemberType->Selected->Text.Trim() ;
		idtypename = idtypename.SubString(0,idtypename.Pos("(")-1 );
		/*sql = "select * from CUST_MemberInfo where CUST_MemberInfo.MemberType = (select IDType from CUST_MemberType where Type = '" + idtypename + "')";
		quMemberType->Close();
		quMemberType->SQL->Clear();
		quMemberType->SQL->Add(sql);
		quMemberType->Open();
		if (!quMemberType->IsEmpty()) {
			MessageBox(0,"�û�Ա���͵Ļ�Ա��Ϣ���ڣ������޸ĸû�Ա���ͣ�","�޸Ĵ���" ,MB_OK);
		}
		else
		{ */
			sql = "update CUST_MemberType set Type = '" + Trim(edTypeName->Text)+"',Discount = " +IDiscount+"where Type = '" + idtypename + "'";
			sdf = "ȷ���޸Ļ�Ա���ͣ�"+idtypename+"��";
			if (ShowMsg(Handle ,sdf.c_str(),1)==1) {
				try {
					quMemberType->Close();
					quMemberType->SQL->Clear();
					quMemberType->SQL->Add(sql);
					quMemberType->ExecSQL();
					AnsiString addname = edTypeName->Text.Trim() + "(" + edTypeDiscount->Text.Trim() + "%)";
					tvMemberType->Selected->Text = addname;
					edTypeName->Enabled = false;
					edTypeDiscount->Enabled = false;
					BtnAdd->Enabled = true;
					BtnChangeOptions->Enabled = true;
					BtnSave->Enabled = false;
				} catch (Exception &E) {
                                        ShowMsg(Handle ,"�����ݸ�ϵͳ���������й����������޸ģ�",3);

				}
			}
		//}
	}
}
//---------------------------------------------------------------------------


void __fastcall Tfrmmemclassmg::BtnSaveClick(TObject *Sender)
{
    if (edTypeName->Text == "") {

                ShowMsg(Handle ,"��Ա�������Ʋ���Ϊ�գ�",3);
		return;
	}
	if (edTypeDiscount->Text == "") {

                ShowMsg(Handle ,"��Ա�����ۿ۲���Ϊ�գ�",3);
		return;
	}
	int discount;
	discount = StrToInt(edTypeDiscount->Text.Trim() );
	if (discount > 100) {

        ShowMsg(Handle ,"��Ա�����ۿ۲��ܴ���100��",3);
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

void __fastcall Tfrmmemclassmg::edTypeNameKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		//BtnSave->Click();
		edTypeDiscount->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemclassmg::edTypeDiscountKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if (Key == VK_RETURN) {
    	BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemclassmg::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmmemclassmg::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F1) {
		 BtnAdd->Click();
	   }
		if (Key == VK_F3) {
		 BtnChangeOptions->Click();
	   }

		if (Key == VK_F4) {
		 BtnSave->Click();
	   }
		if (Key == VK_F7) {
		 BtnDelete->Click();
	   }
		if (Shift.Contains(ssCtrl)&& Key ==81  ) {
			BtnExit->Click();
		}

}
//---------------------------------------------------------------------------

