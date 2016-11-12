//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitbalance.h"
#include "Unitautojie.h"
#include "Unitweijieselect.h"
#include "..\bsadmin\UnitSelectClient.h"
#include "Notedetail.h"
#include "PwdForm.h"
#include   <math.h>
#include "global.h"
#include "Unittishi.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "RzCmboBx"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RpBase"
#pragma link "RpCon"
#pragma link "RpConDS"
#pragma link "RpDefine"
#pragma link "RpSystem"
#pragma link "RpRave"
#pragma resource "*.dfm"
Tfrmbalance *frmbalance;
//---------------------------------------------------------------------------
__fastcall Tfrmbalance::Tfrmbalance(TComponent* Owner,TADOConnection *cn,int userid,int type,int stgid,bool master)
	: TForm(Owner)
{
	fcon = cn;
	Type = type;
	fstgid = stgid;
	fmaster = master;
	fuserid = userid;
	aquery->Connection = fcon;
	aqhd->Connection = fcon;
	aqdg1->Connection = fcon;
	aquerytotal->Connection = fcon;
	AddNew = false;
	if (Type == 1) {
		this->Caption = "��Ӧ����������";
		lablename->Caption = "��Ӧ��";
		dg->Columns->Items[1]->Title->Caption = "��ⵥ��";
		dg->Columns->Items[2]->Title->Caption = "��ⵥ��";
		dg->Columns->Items[3]->Title->Caption = "�������";
		dg->Columns->Items[9]->Title->Caption = "��ⵥ��ע";
		Label21->Caption = "���";
		cbjieshuantype->AddItem("�����˿�",(TObject*)1);
		cbjieshuantype->AddItem("����",(TObject*)2);
		cbjieshuantype->AddItem("Ԥ����",(TObject*)3);
		cbjieshuantype->AddItem("�����Գ�",(TObject*)4);
		cbjieshuantype->AddItem("����˿�",(TObject*)5);
		Label10->Caption = "������";
		Label2->Caption = "��Ӧ��";
		spselect->Caption = "ѡ�������ⵥ";
	}else
	{
		this->Caption = "�ͻ���������";
		lablename->Caption = "�ͻ�";
		dg->Columns->Items[1]->Title->Caption = "��������";
		dg->Columns->Items[2]->Title->Caption = "��������";
		dg->Columns->Items[3]->Title->Caption = "��������";
		dg->Columns->Items[9]->Title->Caption = "��������ע";
		Label21->Caption = "�տ";
		cbjieshuantype->AddItem("�տ��˿�",(TObject*)1);
		cbjieshuantype->AddItem("����տ�",(TObject*)2);
		cbjieshuantype->AddItem("Ԥ�տ�",(TObject*)3);
		cbjieshuantype->AddItem("�����Գ�",(TObject*)4);
	  	cbjieshuantype->AddItem("����˿�",(TObject*)5);
		Label12->Caption = "Ԥ�տ�";
		Label10->Caption = "�տ���";
		Label2->Caption = "��Ӧ��";
		spselect->Caption = "ѡ����㷢����";
		Label7->Caption = "�տ�����";
		Label24->Caption = "ת��Ԥ�տ�";
	}
	aqdg->Connection = fcon;
	ReadyData();
	selectID = new TStringList();
	save = false;

	AnsiString sql;
	sql = "select value from sys_bsset where name = 'changeDanHaoDisplay'";
	TADOQuery *aq1 = new TADOQuery(NULL);
	aq1->Connection = cn;
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->Open();
	ChangeDisplay = aq1->FieldByName("value")->AsBoolean;

	sql = "select Name from sys_user where id = " + IntToStr(userid);
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->Open();
	edemploy->Text = aq1->FieldByName("Name")->AsAnsiString ;

	sql = "select ID,Name,supshenheipwd,supfanshenpwd,clishenheipwd,clifanshenpwd from SYS_StorageInfo where id = " + IntToStr(fstgid);
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->Open();
	Edit1->Text = aq1->FieldByName("ID")->AsString ;
	Edit2->Text = aq1->FieldByName("Name")->AsString ;
	supshenheipwd  =  aq1->FieldByName("supshenheipwd")->AsString ;
	supfanshenpwd  =  aq1->FieldByName("supfanshenpwd")->AsString ;
	clishenheipwd  =  aq1->FieldByName("clishenheipwd")->AsString ;
	clifanshenpwd  =  aq1->FieldByName("clifanshenpwd")->AsString ;

	if (type == 1) {
		aq1->Close();
		aq1->SQL->Clear();
		aq1->SQL->Add("select * from sys_bsset where name ='xiaoshudian'");
		aq1->Open();
		Disc =  "###,###,##" + aq1->FieldByName("bk")->AsAnsiString ;
	}
	else
	{
    	aq1->Close();
		aq1->SQL->Clear();
		aq1->SQL->Add("select * from sys_bsset where name ='salexiaoshudian'");
		aq1->Open();
		Disc =  "###,###,##" + aq1->FieldByName("bk")->AsAnsiString ;
	}
	if (Disc == "###,###,##0") {
		xiaoshubit = 0;
		cc = "%0.0f";
	}
	else if (Disc == "###,###,##0.0") {
		xiaoshubit = 1;
		cc = "%0.1f";
	}
	else if (Disc == "###,###,##0.00") {
		xiaoshubit = 2;
		cc = "%0.2f";
	}

	delete aq1;
	if (ChangeDisplay) {
		dg->Columns->Items[1]->Visible = false;
		dg->Columns->Items[2]->Visible = true;
	}
	else
	{
		dg->Columns->Items[1]->Visible = true;
		dg->Columns->Items[2]->Visible = false;
	}
}
//---------------------------------------------------------------------------
void Tfrmbalance::ReadyData()
{
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	String sqlstr;
	if (Type == 1) {
		sqlstr = "select ID,Name from CUST_CustomerInfo where type = 1 and name <> '' and customerstate=1 and stgid="+IntToStr(fstgid)+" order by name ";
	}
	else
	{
		sqlstr = "select ID,Name from CUST_CustomerInfo where type in(2,3) and customerstate=1 order by name  ";
	}
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sqlstr);
	aq->Open();

	while(!aq->Eof)
	{
		cbselect->AddItem(aq->FieldByName("Name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	delete aq;
	dtp->Date = Date();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmbalance::BtnNewClick(TObject *Sender)
{
	if (ShowMsg(this->Handle,"ȷ��Ҫ����µ���",3) == 1) {
		Enable(true);
		save = false;
		BtnOK->Enabled = true;
		BtnCancel->Enabled = false;
		BtnDelete->Enabled = true;
		cbselect->ItemIndex = -1;
		cbjieshuantype->ItemIndex = -1;
		cbmethod->ItemIndex = -1;
		editnum->Text = "";
		editstate->Text = "";
		edithukuan->Text = "0.00";
		membk->Text = "";
		editmoney->Text = "0.00";
		editmayang->Text = "0.00";
		editshiyang->Text = "0.00";
		editaddcost->Text = "0.00";
		edityijie->Text = "0.00";
		editweijie->Text = "0.00";
		editthistime->Text = "0.00";
		edzryuhu->Text = "0.00";
		edduicong->Text = "0.00";


                edityu->Text = "0.00";

                editweijiedan->Text = "0.00";
                edityinghu->Text = "0.00";
                edityuhu->Text = "0.00";

		editmoney->Enabled = true;
		spselect->Enabled = true;
		sbautojieshuan->Enabled = true;
		autobt->Enabled = true;
		btduicong->Enabled = true;
		edtQryVendor->Enabled = true;
		aqdg->Close();
		dtp->Date = Date();
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		String sql;
		if (Type == 1) {
                        if (qfsupplier) {
                         	sql = "select * from CUST_CustomerInfo where Type = 1 and customerstate=1 and stgid="+IntToStr(fstgid)+" order by Name";
                        }else sql = "select * from CUST_CustomerInfo where Type = 1 and customerstate=1  order by Name";

		}
		else
		{
                   if (qfclient) {
                       sql = " select * from CUST_CustomerInfo where Type in (2,3) and customerstate=1 and stgid="+IntToStr(fstgid)+" order by Name ";
                   }else sql = " select * from CUST_CustomerInfo where Type in (2,3) and customerstate=1  order by Name ";

		}
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbselect->Clear();
		while(!aq->Eof)
		{
			cbselect->Items->AddObject(aq->FieldByName("name")->AsAnsiString ,(TObject*)aq->FieldByName("id")->AsInteger );
			aq->Next();
		}
		delete aq;
                aqdg1->Active = false;



		edtQryVendor->Text = "";
		edtQryVendor->SetFocus();
		dbnv->Enabled = false;
	}
}
//---------------------------------------------------------------------------
void Tfrmbalance::Excute(String sql)
{
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
 }
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::BtnSaveClick(TObject *Sender)
{
	if (!save) {
		if (Type == 1 && cbselect->Text == "") {
			ShowMsg(Handle ,"��ѡ����㹩Ӧ�̣�",3);
			return;
		}
		if (Type == 2 && cbselect->Text == "") {
			ShowMsg(Handle ,"��ѡ�����ͻ���",3);
			return;
		}
		if (cbjieshuantype->Text  == "") {
			ShowMsg(Handle ,"�������Ͳ���Ϊ�գ�",3);
			return;
		}
		if (cbmethod->Text == "") {
			ShowMsg(Handle ,"���㷽ʽ����Ϊ�գ�",3);
			return;
		}

		AnsiString sqlstr;
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		Code = NoteCode::BuildCode(aq, GetDBTime(aq), 0, "FN_CUSEndMoneyDocuments", "MoneyCode");
		delete aq;
		editnum->Text = Code;  //���ɵ���

		editnum->Text = editnum->Text.SubString(2,editnum->Text.Length() );                                            //0Ϊû����� 1 �����
		editstate->Text = "δ���";																	//�����µ�

		sqlstr = "insert into FN_CUSEndMoneyDocuments (MoneyCode,date,state,type,userid,stgid,clearingtype,clearingstyle,remarks,paymentdate,jiespz,cusid) "
		"values ("+Code+",getdate(),0," + IntToStr(Type) + "," + IntToStr(fuserid)  +"," + IntToStr(fstgid) + ",'"+ cbjieshuantype->Text.Trim() + "','" + cbmethod->Text.Trim() + "','" +  membk->Text + "','" + DateToStr(dtp->Date) + "','" + edjspz->Text.Trim() + "'," + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex])) + ")";
		Excute(sqlstr);
		Enable(false);
		save = true;

		//�����ݼ�
		DisplayDetail(editnum->Text);
		ShowMsg(Handle ,"���㵥�����ɳɹ���",3);

		selectID->Clear();
		editmoney->Enabled = true;
		editmoney->SetFocus();
	}else
	{
		String sql;
		sql ="update FN_CUSEndMoneyDocuments set jiespz = '" + edjspz->Text + "',Remarks = '" + membk->Text + "',clearingstyle = '" + cbmethod->Text + "',paymentdate = '" + DateToStr(dtp->Date) + "'" ;
		sql = sql + " where moneycode = " + editnum->Text ;
		Excute(sql);
		//editmoney->SetFocus();
	}
}
//---------------------------------------------------------------------------
void Tfrmbalance::Enable(BOOL var)
{
	cbselect->Enabled  = var;
	edtQryVendor->Enabled = var;
	cbjieshuantype->Enabled = var;
	//cbmethod->Enabled = var;
	//edityu->Enabled = var;
	//edityinghu->Enabled = var;
	//editnum->Enabled = var;
	//editstate->Enabled = var;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmbalance::editmoneyKeyPress(TObject *Sender, wchar_t &Key)
{
	FLOAT hukuan;
	AnsiString sql;
	String sqlupdate;

	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '-')&&(Key != '\b')) {
		Key = NULL;
	}
	if (Key == VK_RETURN) {
		if (aqdg->IsEmpty() && (cbjieshuantype->ItemIndex != 2 && cbjieshuantype->ItemIndex != 4)) {
		ShowMsg(Handle ,"��ѡ����㵥�ݣ�",3);
		editmoney->Text = "0.00";
		return;
	}
	FLOAT num;
	if (editnum->Text =="") {
		return;
	}
	if (editstate->Text =="�����") {
		ShowMsg(Handle ,"���ŵ�������ˣ������ٽ��㣡",0);
		return;
	}
	try {
		num = StrToFloat(editmoney->Text);
		editmoney->Text = FormatFloat("0.00",num);
	} catch (...) {
		ShowMsg(Handle ,"��������ȷ�Ľ������ٽ��㣡",0);
		return;
	}
	if (num == 0) {
		return;
	}else
	{
		hukuan = aqdg1->FieldByName("nochecked")->AsFloat ;

		if (cbjieshuantype->ItemIndex == 0)   //�����˿�
		{
        	if (num > 0 && hukuan < 0) {
				num = 0-num;
				editmoney->Text = "-" + editmoney->Text ;
			}
			if ((num > 0 && hukuan < 0) || (num < 0 && hukuan > 0)) {
				editmoney->Text = "0.00";
				return;
			}
		}
		if (Disc == "0.0") {
			if ((num - hukuan )>0.1 && (cbjieshuantype->ItemIndex != 2 && cbjieshuantype->ItemIndex != 4)) {
				ShowMsg(Handle ,"���������,�����¸�������ٽ��㣡",3);
				editmoney->Text = "0.00";
				editmoney->SetFocus();
				return;
			}
		}
		else if (Disc == "0") {
			if ((num - hukuan )>1 && (cbjieshuantype->ItemIndex != 2 && cbjieshuantype->ItemIndex != 4)) {
				ShowMsg(Handle ,"��������࣬�����¸��",3);
				editmoney->Text = "0.00";
				editmoney->SetFocus();
				return;
			}
		}
		else if ((num - hukuan )>0 && (cbjieshuantype->ItemIndex != 2 && cbjieshuantype->ItemIndex != 4)) {
				ShowMsg(Handle ,"���������,�����¸��",3);
				editmoney->Text = "0.00";
				editmoney->SetFocus();
				return;
		}
		num = num + aqdg1->FieldByName("hongcong")->AsFloat;

		   switch (cbjieshuantype->ItemIndex) {
				case 0:                //�����˿�
					aqdg1->Edit();

					if (Disc == "0.0") {
						if (abs(num - hukuan)<0.1) {
							aqdg1->FieldByName("thistime")->AsFloat = hukuan ;
						}
						else
						{
							aqdg1->FieldByName("thistime")->AsFloat = num ;

						}
					}
					else if (Disc == "0") {
						if (abs(num - hukuan)<1) {
							aqdg1->FieldByName("thistime")->AsFloat = hukuan ;

						}
						else
						{
							aqdg1->FieldByName("thistime")->AsFloat = num ;

						}
					}
					else {
						aqdg1->FieldByName("thistime")->AsFloat = num ;

					}
					aqdg1->UpdateBatch(arCurrent);
                    aqdg->Refresh();
                    sql = "update FN_CUSEndMoneyDocuments set yuhu = 0 where MoneyCode = " + editnum->Text ;
					Excute(sql);

					break;
				case 1:
					if (num > 0) {
                    	edityu->Text = StringReplace(edityu->Text , ",","",TReplaceFlags()<<rfReplaceAll);

						if (StrToFloat(editmoney->Text) > StrToFloat(edityu->Text)) {
						ShowMsg(Handle ,"����!��",3);
						editmoney->Text = "0.00";
						editmoney->SetFocus();
						return;
						} else
						{
							aqdg1->Edit();
							aqdg1->FieldByName("thistime")->AsAnsiString = editmoney->Text ;
							aqdg1->UpdateBatch(arCurrent);
							aqdg->Refresh();
							//edityu->Text = FormatFloat("0.00",StrToFloat(edityu->Text) - StrToFloat(editmoney->Text));
						}
					}
					else
					{
						editmoney->Text = "0.00";
					}
					break;
				 case 2:                 ////Ԥ����

					   sql = "update FN_CUSEndMoneyDocuments set yuhu = " + StringReplace(editmoney->Text , ",","",TReplaceFlags()<<rfReplaceAll) + " where MoneyCode = " + editnum->Text ;
					   Excute(sql);
					   //edityuhu->Text =  editmoney->Text;
					   break;
				 case 4:                 ////����˿�
					if (num > 0) {
                    	edityu->Text = StringReplace(edityu->Text , ",","",TReplaceFlags()<<rfReplaceAll);

						if (StrToFloat(editmoney->Text) > StrToFloat(edityu->Text)) {

                                                         ShowMsg(Handle ,"����!��",3);
							editmoney->Text = "0.00";
							editmoney->SetFocus();
							return;
						} else
						{
							sql = "update FN_CUSEndMoneyDocuments set yuhu = " + StringReplace(editmoney->Text , ",","",TReplaceFlags()<<rfReplaceAll) + " where MoneyCode = " + editnum->Text ;
							Excute(sql);
						}
					}
					else
					{
                    	editmoney->Text = "0.00";
					}

					   	break;
		}

		}
		Displaytotal(editnum->Text);
	}
}
//---------------------------------------------------------------------------
void Tfrmbalance::shenhe()  //��ǰѡ�еĵ���ID������������
{
	AnsiString sql;
	AnsiString zryuhu;
	switch (cbjieshuantype->ItemIndex) {
		case 0:       //�����˿�
		case 3:       //�Գ�
			aqdg1->First();
			while(!aqdg1->Eof)
			{
				sql = "exec JieShuan '"+aqdg1->FieldByName("stgntcode")->AsAnsiString+"','"+aqdg1->FieldByName("thistime")->AsAnsiString+"',"+IntToStr(Type);
				Excute(sql);
				aqdg1->Next();
			}
			   //aqdg->Active = false;
			   //aqdg->Active = true;

			   //����û�н�Ŀ�
				//editweijiedan->Text = StringReplace(editweijiedan->Text,",","",TReplaceFlags()<<rfReplaceAll);
				//edityinghu->Text = StringReplace(edityinghu->Text,",","",TReplaceFlags()<<rfReplaceAll);
				//edithukuan->Text = StringReplace(edithukuan->Text,",","",TReplaceFlags()<<rfReplaceAll);

				//editweijiedan->Text = FormatFloat("0.00",StrToFloat(editweijiedan->Text) - StrToFloat(edithukuan->Text));
				//edityinghu->Text =  FormatFloat("0.00",StrToFloat(edityinghu->Text) - StrToFloat(edithukuan->Text));

				zryuhu = StringReplace(edzryuhu->Text,",","",TReplaceFlags()<<rfReplaceAll);
				if (StrToFloat(zryuhu) > 0.00 ) {
					sql = "update CUST_CustomerStartMoney set totalyue = totalyue + "+ zryuhu +" where customerid = " + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex]));
					Excute(sql);
					//edityuhu->Text = StringReplace(edityuhu->Text,",","",TReplaceFlags()<<rfReplaceAll);
					//edityuhu->Text = FormatFloat("0.00",StrToFloat(edityuhu->Text)+ StrToFloat(zryuhu));
					//edityu->Text = StringReplace(edityu->Text,",","",TReplaceFlags()<<rfReplaceAll);
					//edityu->Text = FormatFloat("0.00",StrToFloat(edityu->Text)+ StrToFloat(zryuhu));
				}
			break;
			case 1:              //�����
				aqdg1->First();
				while(!aqdg1->Eof)
				{
					sql = "exec JieShuan '"+aqdg1->FieldByName("stgntcode")->AsAnsiString+"','"+aqdg1->FieldByName("thistime")->AsAnsiString+"',"+IntToStr(Type);
					Excute(sql);
					//aqdg->Edit();
					//aqdg->FieldByName("checked")->AsAnsiString =  FormatFloat("0.00",aqdg->FieldByName("thistime")->AsFloat);
					//aqdg->FieldByName("nochecked")->AsAnsiString =  FormatFloat("0.00",aqdg->FieldByName("nochecked")->AsFloat - aqdg->FieldByName("thistime")->AsFloat);
					//aqdg->UpdateBatch(arCurrent);
					aqdg1->Next();
				}

				//edithukuan->Text = StringReplace(edithukuan->Text,",","",TReplaceFlags()<<rfReplaceAll);
				sql = "update CUST_CustomerStartMoney set totalyue = totalyue - FN_CUSEndMoneyDocuments.overage from "
					" CUST_CustomerStartMoney join FN_CUSEndMoneyDocuments on CUST_CustomerStartMoney.customerid = FN_CUSEndMoneyDocuments.cusid "
					" where FN_CUSEndMoneyDocuments.MoneyCode = " + editnum->Text ;
				sql = "update CUST_CustomerStartMoney set totalyue = totalyue - "+ StringReplace(edithukuan->Text,",","",TReplaceFlags()<<rfReplaceAll) +" where customerid = " + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex]));
		         	Excute(sql);

				edityu->Text = StringReplace(edityu->Text,",","",TReplaceFlags()<<rfReplaceAll);
				edityu->Text = FormatFloat("0.00",StrToFloat(edityu->Text)- StrToFloat(StringReplace(edithukuan->Text,",","",TReplaceFlags()<<rfReplaceAll)));

			   //����û�н�Ŀ�
				//editweijiedan->Text = StringReplace(editweijiedan->Text,",","",TReplaceFlags()<<rfReplaceAll);
				//edityinghu->Text = StringReplace(edityinghu->Text,",","",TReplaceFlags()<<rfReplaceAll);

				//editweijiedan->Text = FormatFloat("0.00",StrToFloat(editweijiedan->Text) - StrToFloat(edithukuan->Text));
				//edityinghu->Text =  FormatFloat("0.00",StrToFloat(edityinghu->Text) - StrToFloat(edithukuan->Text));

				break;
		   case 2:                       //Ԥ����

			   //edithukuan->Text = StringReplace(edithukuan->Text,",","",TReplaceFlags()<<rfReplaceAll);
			   //edityuhu->Text = StringReplace(edityuhu->Text,",","",TReplaceFlags()<<rfReplaceAll);
			   //editmoney->Text = StringReplace(editmoney->Text,",","",TReplaceFlags()<<rfReplaceAll);
			   //edityuhu->Text = FormatFloat("0.00",StrToFloat(edityuhu->Text)+ StrToFloat(edithukuan->Text));
			   //edityu->Text = StringReplace(edityu->Text,",","",TReplaceFlags()<<rfReplaceAll);
			   //edityu->Text = FormatFloat("0.00",StrToFloat(edityu->Text)+ StrToFloat(edithukuan->Text));
			   sql = "update CUST_CustomerStartMoney set totalyue = totalyue + "+ StringReplace(edithukuan->Text,",","",TReplaceFlags()<<rfReplaceAll) +" where customerid = " + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex]));
			   Excute(sql);

			  break;
		   case 4:                       //����˿�
			   //edithukuan->Text = StringReplace(edithukuan->Text,",","",TReplaceFlags()<<rfReplaceAll);
			   //edityuhu->Text = StringReplace(edityuhu->Text,",","",TReplaceFlags()<<rfReplaceAll);
			   //editmoney->Text = StringReplace(editmoney->Text,",","",TReplaceFlags()<<rfReplaceAll);
			   //edityuhu->Text = FormatFloat("0.00",StrToFloat(edityuhu->Text)- StrToFloat(edithukuan->Text));
			   //edityu->Text = StringReplace(edityu->Text,",","",TReplaceFlags()<<rfReplaceAll);
			   //edityu->Text = FormatFloat("0.00",StrToFloat(edityu->Text) - StrToFloat(edithukuan->Text));
			   sql = "update CUST_CustomerStartMoney set totalyue = totalyue - "+ StringReplace(edithukuan->Text,",","",TReplaceFlags()<<rfReplaceAll) +" where customerid = " + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex]));
			   Excute(sql);

			  break;
	default:
	   ;
	}
	aqdg->Active = false;
	aqdg->Active = true;
	aqdg1->Active = false;
	aqdg1->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::BtnOKClick(TObject *Sender)
{
	String sql;
	if(editnum->Text == "")
	{
		return;
	}
	if (editstate->Text == "�����") {
		return;
	}
	TfrmPwd* frm = new TfrmPwd(this);
	if (mrOk == frm->ShowModal())
	{
		if (Type == 1) {                               //��Ӧ��
			if (frm->GetPassword() != supshenheipwd)
			{
				ShowMsg(Handle ,"�������!��",0);
				return;
			}
		}
		else
		{
			if (frm->GetPassword() != clishenheipwd)
			{
				ShowMsg(Handle ,"�������!��",0);
				return;
			}
		}
	}
	else
	{
    	return;
	}
	if (Type == 1) {
		sql = "select BS_StorageNoteHeader.nochecked,FN_CUSEndMoneyDtails.thistime,FN_CUSEndMoneyDtails.EndMoneyDocumentID from FN_CUSEndMoneyDtails left join BS_StorageNoteHeader "
			" on BS_StorageNoteHeader.StgNtCode = FN_CUSEndMoneyDtails.stgntcode "
			" where FN_CUSEndMoneyDtails.EndMoneyDocumentID = " + editnum->Text.Trim() + " and FN_CUSEndMoneyDtails.thistime > BS_StorageNoteHeader.nochecked";
	}
	else
	{
		sql = "select BS_WsaleNoteHeader.nochecked,FN_CUSEndMoneyDtails.thistime,FN_CUSEndMoneyDtails.EndMoneyDocumentID from FN_CUSEndMoneyDtails left join BS_WsaleNoteHeader "
			" on BS_WsaleNoteHeader.WsaleNtCode = FN_CUSEndMoneyDtails.stgntcode "
			" where FN_CUSEndMoneyDtails.EndMoneyDocumentID = " + editnum->Text.Trim() + " and FN_CUSEndMoneyDtails.thistime > BS_WsaleNoteHeader.nochecked";
	}

	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
     //	if (aquery->RecordCount > 0) {
       //		ShowMsg(Handle ,"���ν�����д���δ��������������ˣ�",0);
      //  DisplayDetail(editnum->Text);
     //		return;
     //	}

	if(ShowMsg(Handle ,"ȷ��Ҫ��˸��ŵ�����?",1)==1 )
	{
		shenhe();
		sql = "update FN_CUSEndMoneyDocuments set state=1 " ;
		sql = sql + " where moneycode = '" + editnum->Text+"'";
		Excute(sql);
		editstate->Text = "�����";
		Enable(0);
		dtp->Enabled = false;
		editmoney->Enabled = false;
		sbautojieshuan->Enabled = false;
		autobt->Enabled = false;
		spselect->Enabled  = false;
		BtnOK->Enabled = false;
		BtnCancel->Enabled = true;
		BtnDelete->Enabled = false;



		QryNthead(editnum->Text);
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::BtnDeleteClick(TObject *Sender)
{
	int i;
	i = dg->SelectedRows->Count;

	if (dg->DataSource->DataSet->IsEmpty() ) {
		return;
	}
	if (editstate->Text == "�����") {
		return;
	}
	AnsiString sql;
	if (cbjieshuantype->ItemIndex == 3) {
		if( ShowMsg(Handle ,"��������Ϊ�����Գ�ʱ���޷����һ��ɾ�������ȷ������ɾ�����м�¼",1)==1 )
		{
			sql = "delete from FN_CUSEndMoneyDtails where EndMoneyDocumentID = " + editnum->Text ;
			Excute(sql);

			editmoney->Text = FormatFloat(Disc,aqdg1->FieldByName("thistime")->AsFloat);
			if (cbjieshuantype->ItemIndex == 0) {      //����Ԥ���
				sql = "update FN_CUSEndMoneyDocuments set yuhu = 0,overage = 0 where MoneyCode = " + editnum->Text ;
				Excute(sql);
			}
			DisplayDetail(editnum->Text);
			Displaytotal(editnum->Text);
		}
	}
	else
	{
		if( ShowMsg(Handle ,"ȷ��ɾ������¼��",1)==1 )
		{
			if (dg->SelectedRows->Count == 0)
			{
				i = selectID->IndexOf(dg->DataSource->DataSet->FieldByName("stgntcode")->AsAnsiString);
				if (i != -1) {
					selectID->Delete(i);
				}
				sql = "delete from FN_CUSEndMoneyDtails where EndMoneyDocumentID = " + editnum->Text + " and stgntcode = " + aqdg1->FieldByName("stgntcode")->AsAnsiString;
				Excute(sql);
			}
			else if (dg->SelectedRows->Count > 0)
			{
				aqdg1->Bookmark = dg->SelectedRows->Items[0];
				i = selectID->IndexOf(dg->DataSource->DataSet->FieldByName("stgntcode")->AsAnsiString);
				if (i != -1) {
					selectID->Delete(i);
				}
				sql = "delete from FN_CUSEndMoneyDtails where EndMoneyDocumentID = " + editnum->Text + " and stgntcode = " + aqdg1->FieldByName("stgntcode")->AsAnsiString;
				Excute(sql);

				for (int j=1; j < dg->SelectedRows->Count; j++)
				{
					aqdg1->Bookmark = dg->SelectedRows->Items[j];
					i = selectID->IndexOf(dg->DataSource->DataSet->FieldByName("stgntcode")->AsAnsiString);
					if (i != -1) {
						selectID->Delete(i);
					}
					sql = "delete from FN_CUSEndMoneyDtails where EndMoneyDocumentID = " + editnum->Text + " and stgntcode = " + aqdg1->FieldByName("stgntcode")->AsAnsiString;
					Excute(sql);
				}
			}
			else
				return;

			editmoney->Text = FormatFloat(Disc,aqdg1->FieldByName("thistime")->AsFloat);
			  //����Ԥ���
			sql = "update FN_CUSEndMoneyDocuments set yuhu = 0,overage = 0 where MoneyCode = " + editnum->Text ;
			Excute(sql);

			DisplayDetail(editnum->Text);
			Displaytotal(editnum->Text);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::BtnClick(TObject *Sender)
{
	String Codestr,sqlstr;
	TfrmQryNoteCode1 *frm = new TfrmQryNoteCode1(this,Type,fcon,fstgid);
	frm->Caption = "δ���";
	frm->weishenhei = true;
	frm->SetstgID(fstgid);
	if (mrOk == frm->ShowModal() ) {
		Codestr =  frm->GetNoteCode();
		sqlstr = frm->GetSqlWhere();
		QryNthead(Codestr);
		dbnv->Enabled = true;
		aqhd->Close();
		aqhd->SQL->Clear();
		aqhd->SQL->Add(sqlstr);
		aqhd->Open();
	}
	delete frm;
}

//---------------------------------------------------------------------------
void Tfrmbalance::DisplayDetail(String Danhao)
{
	String sql;

	if (Type == 1) {
		if (editstate->Text == "�����") {
        	sql = "select rank() over(order by FN_CUSEndMoneyDtails.id) as xuhao,FN_CUSEndMoneyDtails.id,FN_CUSEndMoneyDtails.EndMoneyDocumentID,FN_CUSEndMoneyDtails.stgntcode,FN_CUSEndMoneyDtails.stgntcode,FN_CUSEndMoneyDtails.hdtime,FN_CUSEndMoneyDtails.thistime,FN_CUSEndMoneyDtails.type,FN_CUSEndMoneyDtails.bk,FN_CUSEndMoneyDtails.CodeStr,BS_StorageNoteHeader.fapiaotext ,BS_StorageNoteHeader.Remarks,"
				"BS_StorageNoteHeader.totalfixedprice,BS_StorageNoteHeader.totaldiscountedprice,BS_StorageNoteHeader.addcosts,BS_StorageNoteHeader.checked,BS_StorageNoteHeader.nochecked,BS_StorageNoteHeader.totalamount,FN_CUSEndMoneyDtails.hongcong "
				" from FN_CUSEndMoneyDtails left join BS_StorageNoteHeader on FN_CUSEndMoneyDtails.stgntcode = BS_StorageNoteHeader.StgNtCode where EndMoneyDocumentID = " + Danhao + " order by FN_CUSEndMoneyDtails.id asc";
		}
		else
		{
        	sql = "select rank() over(order by FN_CUSEndMoneyDtails.id) as xuhao,FN_CUSEndMoneyDtails.id,FN_CUSEndMoneyDtails.EndMoneyDocumentID,FN_CUSEndMoneyDtails.stgntcode,FN_CUSEndMoneyDtails.stgntcode,FN_CUSEndMoneyDtails.hdtime,FN_CUSEndMoneyDtails.thistime,FN_CUSEndMoneyDtails.type,FN_CUSEndMoneyDtails.bk,FN_CUSEndMoneyDtails.CodeStr,BS_StorageNoteHeader.fapiaotext ,BS_StorageNoteHeader.Remarks,"
				"BS_StorageNoteHeader.totalfixedprice,BS_StorageNoteHeader.totaldiscountedprice,BS_StorageNoteHeader.addcosts,BS_StorageNoteHeader.checked,BS_StorageNoteHeader.nochecked - FN_CUSEndMoneyDtails.hongcong as nochecked,BS_StorageNoteHeader.totalamount,FN_CUSEndMoneyDtails.hongcong "
				" from FN_CUSEndMoneyDtails left join BS_StorageNoteHeader on FN_CUSEndMoneyDtails.stgntcode = BS_StorageNoteHeader.StgNtCode where EndMoneyDocumentID = " + Danhao + " order by FN_CUSEndMoneyDtails.id asc";
		}
	}
	else
	{
		if (editstate->Text == "�����") {
        	sql = "select rank() over(order by FN_CUSEndMoneyDtails.id) as xuhao,FN_CUSEndMoneyDtails.id,FN_CUSEndMoneyDtails.EndMoneyDocumentID,FN_CUSEndMoneyDtails.stgntcode,FN_CUSEndMoneyDtails.stgntcode,FN_CUSEndMoneyDtails.hdtime,FN_CUSEndMoneyDtails.thistime,FN_CUSEndMoneyDtails.type,FN_CUSEndMoneyDtails.bk,FN_CUSEndMoneyDtails.CodeStr,BS_WsaleNoteHeader.fapiaotext ,BS_WsaleNoteHeader.Remarks,"
				"BS_WsaleNoteHeader.fixedprice as totalfixedprice,BS_WsaleNoteHeader.discountedprice as totaldiscountedprice,BS_WsaleNoteHeader.addcosts,BS_WsaleNoteHeader.checked,BS_WsaleNoteHeader.nochecked - FN_CUSEndMoneyDtails.hongcong as nochecked,BS_WsaleNoteHeader.totalamount,FN_CUSEndMoneyDtails.hongcong "
				" from FN_CUSEndMoneyDtails left join BS_WsaleNoteHeader on FN_CUSEndMoneyDtails.stgntcode = BS_WsaleNoteHeader.WsaleNtCode where EndMoneyDocumentID =  " + Danhao + " order by FN_CUSEndMoneyDtails.id asc";
		}
		else
		{
        	sql = "select rank() over(order by FN_CUSEndMoneyDtails.id) as xuhao,FN_CUSEndMoneyDtails.id,FN_CUSEndMoneyDtails.EndMoneyDocumentID,FN_CUSEndMoneyDtails.stgntcode,FN_CUSEndMoneyDtails.stgntcode,FN_CUSEndMoneyDtails.hdtime,FN_CUSEndMoneyDtails.thistime,FN_CUSEndMoneyDtails.type,FN_CUSEndMoneyDtails.bk,FN_CUSEndMoneyDtails.CodeStr,BS_WsaleNoteHeader.fapiaotext ,BS_WsaleNoteHeader.Remarks,"
				"BS_WsaleNoteHeader.fixedprice as totalfixedprice,BS_WsaleNoteHeader.discountedprice as totaldiscountedprice,BS_WsaleNoteHeader.addcosts,BS_WsaleNoteHeader.checked,BS_WsaleNoteHeader.nochecked - FN_CUSEndMoneyDtails.hongcong as nochecked ,BS_WsaleNoteHeader.totalamount,FN_CUSEndMoneyDtails.hongcong "
				" from FN_CUSEndMoneyDtails left join BS_WsaleNoteHeader on FN_CUSEndMoneyDtails.stgntcode = BS_WsaleNoteHeader.WsaleNtCode where EndMoneyDocumentID =  " + Danhao + " order by FN_CUSEndMoneyDtails.id asc";
		}
	}
	aqdg1->Close();
	aqdg1->SQL->Clear();
	aqdg1->SQL->Add(sql);
	aqdg1->Open();

	sql = "select * from FN_CUSEndMoneyDtails where EndMoneyDocumentID =  " + Danhao + " order by id asc";
	aqdg->Close();
	aqdg->SQL->Clear();
	aqdg->SQL->Add(sql);
	aqdg->Open();
	selectID->Clear();
	while (!aqdg->Eof )
	{
		selectID->Add(aqdg->FieldByName("stgntcode")->AsAnsiString);
		aqdg->Next();
	}

	Enable(0);
	if (aqdg1->IsEmpty() ) {
		cbjieshuantype->Enabled = true;
	}
	else
	{
    	cbjieshuantype->Enabled = false;
	}

	((TFloatField *)aqdg1->FieldByName("totalfixedprice"))->DisplayFormat = "###,###,##0.00";
	((TFloatField *)aqdg1->FieldByName("totaldiscountedprice"))->DisplayFormat = Disc;
	((TFloatField *)aqdg1->FieldByName("addcosts"))->DisplayFormat = Disc;
	((TFloatField *)aqdg1->FieldByName("checked"))->DisplayFormat = Disc;
	((TFloatField *)aqdg1->FieldByName("nochecked"))->DisplayFormat = Disc;
	((TFloatField *)aqdg1->FieldByName("totalamount"))->DisplayFormat = "###,###,##0";
	((TFloatField *)aqdg1->FieldByName("thistime"))->DisplayFormat = Disc;
	((TFloatField *)aqdg1->FieldByName("hongcong"))->DisplayFormat = Disc;
	editmoney->Text = FormatFloat(Disc,aqdg1->FieldByName("thistime")->AsFloat);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::searchClick(TObject *Sender)
{
	String Codestr,sqlstr;
	TfrmQryNoteCode1 *frm = new TfrmQryNoteCode1(this,Type,fcon,fstgid);
	frm->SetstgID(fstgid);
	if (mrOk == frm->ShowModal() ) {
		Codestr =  frm->GetNoteCode();
		sqlstr = frm->GetSqlWhere();
		QryNthead(Codestr);
		dbnv->Enabled = true;
		aqhd->Close();
		aqhd->SQL->Clear();
		aqhd->SQL->Add(sqlstr);
		aqhd->Open();
	}
	delete frm;

}
//---------------------------------------------------------------------------
void Tfrmbalance::QryNthead(String code)
{
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	String sql;

	cbselect->Clear();
	ReadyData();
	edtQryVendor->Text = "";

	sql = "select custmername,sys_user.name as opname,cusid,yuhu,paymentdate as date,jiespz,Remarks,payment,clearingtype,clearingstyle,Convert(varchar(20),paymentdate,111) as date,case state when 0 then 'δ���' when 1 then '�����' end as state,remarks from FN_CUSEndMoneyDocuments left join sys_user on FN_CUSEndMoneyDocuments.userid = sys_user.id ";
	sql = sql + " where moneycode = " + code+ " and type = " + IntToStr(Type) ;
	aq->SQL->Add(sql);
	aq->Open();

	if (aq->IsEmpty() ) {
   		ShowMsg(Handle ,"���޴˵���",0);
		delete aq;
		return;
	}
    	cbselect->ItemIndex = cbselect->Items->IndexOfObject((TObject*)aq->FieldByName("cusid")->AsInteger);
       //	cbselect->ItemIndex =  cbselect->Items->IndexOf(aq->FieldByName("custmername")->AsAnsiString);


	//cbselect->OnChange(this) ;
	cbselect->OnSelect(this);
	cbjieshuantype->ItemIndex = cbjieshuantype->Items->IndexOf(aq->FieldByName("clearingtype")->AsAnsiString.Trim());
	//cbjieshuantype->Text =  aq->FieldByName("clearingtype")->AsAnsiString ;
	cbmethod->Text = aq->FieldByName("clearingstyle")->AsAnsiString ;
	editnum->Text = code ;
	dtp->Date = aq->FieldByName("date")->AsDateTime ;
	membk->Text =  aq->FieldByName("remarks")->AsAnsiString ;
	if (aq->FieldByName("clearingtype")->AsAnsiString == "Ԥ����" ||aq->FieldByName("clearingtype")->AsAnsiString == "Ԥ�տ�" ) {
		editmoney->Text =  aq->FieldByName("yuhu")->AsAnsiString ;
	}

	edemploy->Text = aq->FieldByName("opname")->AsAnsiString ;
	editstate->Text = aq->FieldByName("state")->AsAnsiString ;
	membk->Text = aq->FieldByName("Remarks")->AsAnsiString ;
	edjspz->Text = aq->FieldByName("jiespz")->AsAnsiString ;

	if (editstate->Text == "�����") {
	   editmoney->Enabled = false;
	   spselect->Enabled  = false;
	   sbautojieshuan->Enabled  = false;
	   autobt->Enabled = false;
	   BtnOK->Enabled = false;
	   BtnDelete->Enabled = false;
	   BtnCancel->Enabled = true;
	}else if (editstate->Text == "δ���") {
		editmoney->Enabled = true;
		spselect->Enabled  = true;
		sbautojieshuan->Enabled  = true;
		autobt->Enabled = true;
		BtnOK->Enabled = true;
		BtnDelete->Enabled = true;
		BtnCancel->Enabled = false;
	}
	btduicong->Enabled = false;
	if (cbjieshuantype->Text=="Ԥ����" || cbjieshuantype->Text=="Ԥ�տ�" || cbjieshuantype->Text=="����˿�" || cbjieshuantype->Text=="�����Գ�") {
		spselect->Enabled  = false;
		sbautojieshuan->Enabled  = false;
		autobt->Enabled = false;
	}
	if (cbjieshuantype->ItemIndex == 3 && editstate->Text == "δ���") {
		btduicong->Enabled = true;
        editmoney->Enabled = false;
	}
	DisplayDetail(code);
	Displaytotal(code);
	save = true;
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::BtnCancelClick(TObject *Sender)
{
	String sql;
	if(editnum->Text == "")
	{
		return;
	}
	if (editstate->Text == "δ���") {
		return;
	}

	TfrmPwd* frm = new TfrmPwd(this);
	if (mrOk == frm->ShowModal())
	{
		if (Type == 1) {                               //��Ӧ��
			if (frm->GetPassword() != supfanshenpwd)
			{
				ShowMsg(Handle ,"�������",0);
				return;
			}
		}
		else
		{
			if (frm->GetPassword() != clifanshenpwd)
			{
				ShowMsg(Handle ,"�������",0);
				return;
			}
		}
	}
	else
	{
		return;
	}
	if(ShowMsg(Handle ,"ȷ��Ҫ����˸��ŵ�����?",1)==1 )
	{
		String sql;
		AnsiString zryuhu;
		editweijiedan->Text = StringReplace(editweijiedan->Text,",","",TReplaceFlags()<<rfReplaceAll);
		edityinghu->Text =StringReplace(edityinghu->Text,",","",TReplaceFlags()<<rfReplaceAll);
		edithukuan->Text =StringReplace(edithukuan->Text,",","",TReplaceFlags()<<rfReplaceAll);
		edityu->Text =StringReplace(edityu->Text,",","",TReplaceFlags()<<rfReplaceAll);
		edityuhu->Text = StringReplace(edityuhu->Text,",","",TReplaceFlags()<<rfReplaceAll);
		switch (cbjieshuantype->ItemIndex) {
		case 0:      //�����˿�
		case 3:     //�Գ�
			aqdg1->First();
			while(!aqdg1->Eof)
			{
				sql = "exec fajieshan '"+aqdg1->FieldByName("stgntcode")->AsAnsiString+"','"+aqdg1->FieldByName("thistime")->AsAnsiString+"',"+IntToStr(Type);
				Excute(sql);
				  //aqdg->Edit();
				  //aqdg->FieldByName("checked")->AsAnsiString = FloatToStr(aqdg->FieldByName("checked")->AsFloat -  aqdg->FieldByName("thistime")->AsFloat) ;
				  //aqdg->FieldByName("nochecked")->AsAnsiString =  FloatToStr(aqdg->FieldByName("nochecked")->AsFloat + aqdg->FieldByName("thistime")->AsFloat);
				  //aqdg->UpdateBatch(arCurrent);
				aqdg1->Next();
			}
			   //����û�н�Ŀ�
			//editweijiedan->Text = FloatToStr(StrToFloat(editweijiedan->Text) + StrToFloat(edithukuan->Text));
			//edityinghu->Text =  FloatToStr(StrToFloat(edityinghu->Text) + StrToFloat(edithukuan->Text));

			zryuhu = StringReplace(edzryuhu->Text,",","",TReplaceFlags()<<rfReplaceAll);
			if (StrToFloat(zryuhu) > 0.00 ) {
				sql = "update CUST_CustomerStartMoney set totalyue = totalyue - "+ zryuhu +" where customerid = " + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex]));
				Excute(sql);
				//edityuhu->Text = FormatFloat("0.00",StrToFloat(edityuhu->Text)- StrToFloat(zryuhu));
				//edityu->Text = StringReplace(edityu->Text,",","",TReplaceFlags()<<rfReplaceAll);
				//edityu->Text = FormatFloat("0.00",StrToFloat(edityu->Text)- StrToFloat(zryuhu));
			}
			break;
		case 1:              //�����
			aqdg1->First();
			while(!aqdg1->Eof)
			{
				sql = "exec fajieshan '"+aqdg1->FieldByName("stgntcode")->AsAnsiString+"','"+aqdg1->FieldByName("thistime")->AsAnsiString+"',"+IntToStr(Type);
				Excute(sql);
				aqdg1->Next();
			}


                        	sql = "update CUST_CustomerStartMoney set totalyue = totalyue + "+ StringReplace(edithukuan->Text,",","",TReplaceFlags()<<rfReplaceAll) +" where customerid = " + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex]));
			Excute(sql);

		      //	sql = "update CUST_CustomerStartMoney set totalyue = totalyue + FN_CUSEndMoneyDocuments.overage from "
		       //			" CUST_CustomerStartMoney join FN_CUSEndMoneyDocuments on CUST_CustomerStartMoney.customerid = FN_CUSEndMoneyDocuments.cusid "
		//		" where FN_CUSEndMoneyDocuments.MoneyCode = " + editnum->Text ;
		       //	Excute(sql);

			edityu->Text = FloatToStr(StrToFloat(edityu->Text)+ StrToFloat(edithukuan->Text));    //edithukuan

			//editweijiedan->Text = FloatToStr(StrToFloat(editweijiedan->Text) + StrToFloat(edithukuan->Text));
			//edityinghu->Text =  FloatToStr(StrToFloat(edityinghu->Text) + StrToFloat(edithukuan->Text));
			break;
		case 2:                       //Ԥ����
			//edityuhu->Text = FormatFloat("0.00",StrToFloat(edityuhu->Text) - StrToFloat(edithukuan->Text));
			//edityu->Text = FloatToStr(StrToFloat(edityu->Text)- StrToFloat(edithukuan->Text));
			sql = "update CUST_CustomerStartMoney set totalyue = totalyue - "+ StringReplace(edithukuan->Text,",","",TReplaceFlags()<<rfReplaceAll) +" where customerid = " + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex]));
			Excute(sql);
			break;
		case 4:                       //����˿�
			//edityuhu->Text = FormatFloat("0.00",StrToFloat(edityuhu->Text) + StrToFloat(edithukuan->Text));
			//edityu->Text = FloatToStr(StrToFloat(edityu->Text) + StrToFloat(edithukuan->Text));
			sql = "update CUST_CustomerStartMoney set totalyue = totalyue + "+ StringReplace(edithukuan->Text,",","",TReplaceFlags()<<rfReplaceAll) +" where customerid = " + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex]));
			Excute(sql);
			break;
		default:
			;
		}

		sql = "update FN_CUSEndMoneyDocuments set state = 0 where moneycode = "+editnum->Text ;
		Excute(sql);
		editstate->Text = "δ���";
		aqdg->Refresh();
		cbselect->Enabled = false;
		cbjieshuantype->Enabled = false;
		//cbmethod->Enabled = false;
		editnum->Enabled = false;
		editstate->Enabled = false;
		editmoney->Enabled = true;
		spselect->Enabled = true;
		sbautojieshuan->Enabled = true;
		autobt->Enabled = true;
		edtQryVendor->Enabled = false;
		BtnCancel->Enabled = false;
		BtnOK->Enabled = true;
		BtnDelete->Enabled = true;

		ShowMsg(Handle ,"�ɹ�����ˣ�",3);
		QryNthead(editnum->Text);
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::dgCellClick(TColumn *Column)
{
	if (editnum->Text == "") {
		return;
	}
	if (dg->DataSource->DataSet->IsEmpty() ) {
		return;
	}
	editmoney->Text = FormatFloat(Disc,aqdg1->FieldByName("thistime")->AsFloat);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::edtQryVendorKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r')
	{
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		String sql;
		if (Type == 1) {
                if (qfsupplier) {
                  sql = " select id,name from CUST_CustomerInfo where Type = 1  and customerstate=1 and stgid="+IntToStr(fstgid)+" and Name like '%"+ edtQryVendor->Text.Trim() + "%' and name <> '' ";
                }  else sql = " select id,name from CUST_CustomerInfo where Type = 1  and customerstate=1  and Name like '%"+ edtQryVendor->Text.Trim() + "%' and name <> '' ";

			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			cbselect->Clear();
			while(!aq->Eof)
			{
				cbselect->Items->AddObject(aq->FieldByName("name")->AsAnsiString ,(TObject*)aq->FieldByName("id")->AsInteger );
				aq->Next();
			}
			aq->First();
			cbselect->ItemIndex = cbselect->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );
			cbselect->OnSelect(this);
			cbselect->SetFocus();
		}
		else
		{
                if ( qfclient) {
                  	sql = " select name,id from CUST_CustomerInfo where Type in(2,3) and customerstate=1 and stgid="+IntToStr(fstgid)+" and Name like '%"+ edtQryVendor->Text.Trim() + "%' and name <> '' ";
                }else 	sql = " select name,id from CUST_CustomerInfo where Type in(2,3) and customerstate=1  and Name like '%"+ edtQryVendor->Text.Trim() + "%' and name <> '' ";

			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			cbselect->Clear();
			while(!aq->Eof)
			{
				cbselect->Items->AddObject(aq->FieldByName("name")->AsAnsiString ,(TObject*)aq->FieldByName("id")->AsInteger );
				aq->Next();
			}
			aq->First();
			cbselect->ItemIndex = cbselect->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );
			cbselect->OnSelect(this);
			cbselect->SetFocus();
		}
		delete aq;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F1) {    //�鵥
		if (!search->Enabled ) {
			return;
		}
		search->Click();
	}
	if (Key == VK_F2) {    //��
		if (!BtnNew->Enabled ) {
			return;
		}
		BtnNew->Click();
	}
	if (Key == VK_F3) {    //����
		if (!BtnSave->Enabled ) {
			return;
		}
		BtnSave->Click();
	}
	if (Key == VK_F5) {    //ɾ��
		if (!BtnDelete->Enabled ) {
			return;
		}
		BtnDelete->Click();
	}
	if (Key == VK_F7) {    //���
		if (!BtnOK->Enabled ) {
			return;
		}
		BtnOK->Click();
	}
	if (Key == VK_F8) {    //�����
		if (!BtnCancel->Enabled ) {
			return;
		}
		BtnCancel->Click();
	}
	if (Key == VK_F9) {    //δ���
		if (!Btn->Enabled ) {
			return;
		}
		Btn->Click();
	}
	if (Key == VK_F10) {    //��ӡ
		if (!BtnPrint->Enabled ) {
			return;
		}
		BtnPrint->Click();
	}
	if (Key == VK_F11) {    //Ԥ��
		if (!BtnView->Enabled ) {
			return;
		}
		BtnView->Click();
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

void __fastcall Tfrmbalance::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::spselectClick(TObject *Sender)
{
	if (editnum->Text == "") {
		return;
	}
	Tfrmselectjiedan *frm = new Tfrmselectjiedan(Application,fcon,aqdg);
	frm->ID = IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex]));
	frm->balance = this;
	frm->selectedID = selectID ;
	frm->DanCode = editnum->Text ;
	frm->Type = Type ;
	frm->stgid = fstgid;
	frm->master = fmaster;
	frm->ShowModal();
	delete frm;
	aqdg->UpdateBatch(arAll);
	DisplayDetail(editnum->Text);
	editmoney->SetFocus();
	Displaytotal(editnum->Text);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::sbautojieshuanClick(TObject *Sender)
{
	AnsiString sql,sqlupdate;
	double Totalyinhu=0.00,shijie=0.00,danjie=0.00,yy = 0.00,hushu=0.00;
	if (aqdg->IsEmpty() ) {
		return;
	}
     //   aqdg1->Sort="totalamount ASC";
     //   aqdg->Sort="totalamount ASC";
	aqdg1->First();
        // dg->DataSource->DataSet->DisableControls();
	while(!aqdg1->Eof)
	{
		Totalyinhu = Totalyinhu + StrToFloat(FormatFloat("0.00",aqdg1->FieldByName("nochecked")->AsFloat)) ;
                if (aqdg1->FieldByName("nochecked")->AsFloat <0 ) {
                     hushu=hushu- StrToFloat(FormatFloat("0.00",aqdg1->FieldByName("nochecked")->AsFloat));
                }
		aqdg1->Next();
	}
      // dg->DataSource->DataSet->EnableControls();
	Tfrmautojieshuan * frm = new Tfrmautojieshuan(Application);
	frm->Caption = "ͳһ����";
	if (Type == 1) {
		frm->Label1->Caption  = "Ӧ��";
	}
	else
	{
		frm->Label1->Caption = "Ӧ��";
	}
	frm->edityinhu->Text = FormatFloat(Disc,Totalyinhu);
	if (cbjieshuantype->ItemIndex == 1) {
		yy = StrToFloat(StringReplace(edityu->Text,",","",TReplaceFlags()<<rfReplaceAll));
		frm->yue = yy;
	}
	if ( mrOk == frm->ShowModal())
	{
		shijie = StrToFloat(frm->editshijie->Text);
		if (cbjieshuantype->ItemIndex == 1) {
			if (shijie > yy ) {
				sql = "update FN_CUSEndMoneyDocuments set overage = " + FloatToStr(yy) + " where MoneyCode = " + editnum->Text ;
				Excute(sql);
			}
			else
			{
				sql = "update FN_CUSEndMoneyDocuments set overage = " + FloatToStr(shijie) + " where MoneyCode = " + editnum->Text ;
				Excute(sql);
			}
		}

		if (shijie >= Totalyinhu && shijie > 0) {
			if (Type == 1) {
				sql = "update FN_CUSEndMoneyDtails set thistime = BS_StorageNoteHeader.NoChecked from "
					" FN_CUSEndMoneyDtails join BS_StorageNoteHeader on FN_CUSEndMoneyDtails.stgntcode = BS_StorageNoteHeader.stgntcode "
					" where FN_CUSEndMoneyDtails.EndMoneyDocumentID = " + editnum->Text;
			}
			else
			{
				sql = "update FN_CUSEndMoneyDtails set thistime = BS_WsaleNoteHeader.NoChecked from "
					" FN_CUSEndMoneyDtails join BS_WsaleNoteHeader on FN_CUSEndMoneyDtails.stgntcode = BS_WsaleNoteHeader.WsaleNtCode "
					" where FN_CUSEndMoneyDtails.EndMoneyDocumentID = " + editnum->Text;
			}
			Excute(sql);
			if (frm->yuhukuan) {      //����Ԥ����
				sql = "update FN_CUSEndMoneyDocuments set yuhu = " + FloatToStr(shijie-Totalyinhu) + " where MoneyCode = " + editnum->Text ;
				Excute(sql);
			}
			else
			{
				sql = "update FN_CUSEndMoneyDocuments set yuhu = 0 where MoneyCode = " + editnum->Text ;
				Excute(sql);
			}
		}
		else
		{
			sql = "update FN_CUSEndMoneyDtails set thistime = 0 where EndMoneyDocumentID = " + editnum->Text ;
			Excute(sql);
			//����ѡ��ĵ������ν���
                      //  dg->DataSource->DataSet->DisableControls();

			aqdg->First();
			aqdg1->First();
                        if (Totalyinhu>0) {
                           shijie=shijie+hushu; 
                        }
			while(!aqdg->Eof)
			{
				if (Totalyinhu > 0) {

                                        if (aqdg1->FieldByName("nochecked")->AsFloat>0) {    //����Ǹ������򲻹�ֱ�Ӹ���thistime


					if (shijie - aqdg1->FieldByName("nochecked")->AsFloat >= 0)
					{
						aqdg->Edit();
						aqdg->FieldByName("thistime")->AsFloat = aqdg1->FieldByName("nochecked")->AsFloat + aqdg1->FieldByName("hongcong")->AsFloat;
						shijie =  shijie - StrToFloat(FormatFloat("0.00",aqdg1->FieldByName("nochecked")->AsFloat));
                                               // ShowMessage(FloatToStr(shijie));
						aqdg->UpdateBatch(arCurrent);
					}else if (shijie - aqdg1->FieldByName("nochecked")->AsFloat < 0) {
						if (shijie == 0) {
                            break;
						}

                                                if (aqdg1->FieldByName("nochecked")->AsFloat<0 ) {   //���С�ڣ�
                                                  	aqdg->Edit();
					         	aqdg->FieldByName("thistime")->AsFloat =aqdg1->FieldByName("nochecked")->AsFloat;
					        	aqdg->UpdateBatch(arCurrent);
                                                }else
                                                {
						aqdg->Edit();
						aqdg->FieldByName("thistime")->AsFloat = shijie + aqdg1->FieldByName("hongcong")->AsFloat;
						aqdg->UpdateBatch(arCurrent);
						shijie =  0;
						break;
                                                }
					}
                                        }//����
                                        else {
                                           	aqdg->Edit();
						aqdg->FieldByName("thistime")->AsFloat = aqdg1->FieldByName("nochecked")->AsFloat ;

						aqdg->UpdateBatch(arCurrent);
                                        }

				}
				else
				{
					shijie = 0-shijie;
					if (shijie + aqdg1->FieldByName("nochecked")->AsFloat >= 0)
					{
						aqdg->Edit();
						aqdg->FieldByName("thistime")->AsFloat = aqdg1->FieldByName("nochecked")->AsFloat + aqdg1->FieldByName("hongcong")->AsFloat;
						shijie =  shijie + aqdg1->FieldByName("nochecked")->AsFloat;
						aqdg->UpdateBatch(arCurrent);
					}else if (shijie + aqdg1->FieldByName("nochecked")->AsFloat < 0) {
						if (shijie == 0) {
							break;
						}
						aqdg->Edit();
						aqdg->FieldByName("thistime")->AsFloat = aqdg1->FieldByName("hongcong")->AsFloat - shijie;
						aqdg->UpdateBatch(arCurrent);
						shijie = 0;
						break;
					}
				}
				aqdg->Next();
				aqdg1->Next();
			}
		}
		DisplayDetail(editnum->Text);
		Displaytotal(editnum->Text);
               //  dg->DataSource->DataSet->EnableControls();
	}
}
//---------------------------------------------------------------------------
void Tfrmbalance::Displaytotal(String documentid)
{
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql;
	if (cbjieshuantype->Text == "Ԥ����" || cbjieshuantype->Text == "Ԥ�տ�" || cbjieshuantype->Text == "����˿�" ) {
		sql = "select sum(round(yuhu," + IntToStr(xiaoshubit) + ")) as yuhu from FN_CUSEndMoneyDocuments where MoneyCode = " + documentid;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();

		editthistime->Text = FormatFloat(Disc,aq->FieldByName("yuhu")->AsFloat );
		edithukuan->Text = FormatFloat(Disc,aq->FieldByName("yuhu")->AsFloat );
		editmoney->Text =  FormatFloat("0.00",aq->FieldByName("yuhu")->AsFloat );
		edzryuhu->Text = "0.00";
		edduicong->Text = "0.00";
		editmayang->Text = "0.00" ;
		editshiyang->Text = FormatFloat(Disc,0.00 );
		editaddcost->Text = FormatFloat(Disc,0.00 );
	}
	else
	{
		if (Type == 1)  {
			sql = "select sum(B.TotalFixedPrice) as totalfixedprice,sum(round(B.TotalDiscountedPrice," + IntToStr(xiaoshubit) + ")) as totaldiscountedprice,sum(B.TotalAmount) as totalamount, "
			" sum(round(B.AddCosts," + IntToStr(xiaoshubit) + ")) as addcosts,sum(round(B.Checked," + IntToStr(xiaoshubit) + ")) as checked,sum(round(B.NoChecked," + IntToStr(xiaoshubit) + ")) as nochecked,sum(round(thistime-FN_CUSEndMoneyDtails.hongcong," + IntToStr(xiaoshubit) + ")) as thistime "
			" from FN_CUSEndMoneyDtails left join BS_StorageNoteHeader B ON FN_CUSEndMoneyDtails.stgntcode = B.StgNtCode where EndMoneyDocumentID = " + documentid;
		}
		else
		{
			sql = "select sum(B.FixedPrice) as totalfixedprice,sum(round(B.DiscountedPrice," + IntToStr(xiaoshubit) + ")) as totaldiscountedprice,sum(B.TotalAmount) as totalamount, "
			" sum(round(B.AddCosts," + IntToStr(xiaoshubit) + ")) as addcosts,sum(round(B.Checked," + IntToStr(xiaoshubit) + ")) as checked,sum(round(B.Nochecked," + IntToStr(xiaoshubit) + ")) as nochecked,sum(round(thistime-FN_CUSEndMoneyDtails.hongcong," + IntToStr(xiaoshubit) + ")) as thistime "
			" from FN_CUSEndMoneyDtails left join BS_WsaleNoteHeader B ON FN_CUSEndMoneyDtails.stgntcode = B.WsaleNtCode where EndMoneyDocumentID = " + documentid;
		}
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();

		editmayang->Text = aq->FieldByName("totalfixedprice")->AsAnsiString ;
		editshiyang->Text = FormatFloat(Disc,aq->FieldByName("totaldiscountedprice")->AsFloat );
		editaddcost->Text = FormatFloat(Disc,aq->FieldByName("addcosts")->AsFloat );
		edityijie->Text = FormatFloat(Disc,aq->FieldByName("checked")->AsFloat );
		editweijie->Text = FormatFloat(Disc,aq->FieldByName("nochecked")->AsFloat );
		editthistime->Text = FormatFloat(Disc,aq->FieldByName("thistime")->AsFloat );
		edithukuan->Text = FormatFloat(Disc,aq->FieldByName("thistime")->AsFloat );
		edduicong->Text = "0.00";
		edzryuhu->Text = "0.00";
		if (cbjieshuantype->ItemIndex == 0 || cbjieshuantype->ItemIndex == 1) { //�����˿��жึ��ʱ
			sql = "select sum(round(yuhu," + IntToStr(xiaoshubit) + ")) as yuhu from FN_CUSEndMoneyDocuments where MoneyCode = " + documentid;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			edzryuhu->Text = FormatFloat(Disc,aq->FieldByName("yuhu")->AsFloat );
		}
		if (cbjieshuantype->ItemIndex == 3) {   //�Գ���
			sql = "select sum(thistime) as thistime from FN_CUSEndMoneyDtails where EndMoneyDocumentID = " + documentid + " and thistime > 0.00";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			edduicong->Text = FormatFloat(Disc,aq->FieldByName("thistime")->AsFloat );
		}
	}
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::edjspzKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::edtclientKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		cbjieshuantype->SetFocus();
		edtQryVendor->Text = "";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::dbnvClick(TObject *Sender, TNavigateBtn Button)
{
	QryNthead(aqhd->FieldByName("MoneyCode")->AsAnsiString );
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::dgDblClick(TObject *Sender)
{
	if (aqdg->IsEmpty() ) {
		return;
	}
	TfrmNotedetail *frm = new TfrmNotedetail(Application,aqdg1->FieldByName("stgntcode")->AsAnsiString ,Type,fcon,0);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::autobtClick(TObject *Sender)
{
	if (editnum->Text == "") {
		return;
	}
	AnsiString weijie,sql;
	weijie = StringReplace(editweijiedan->Text,",","",TReplaceFlags()<<rfReplaceAll);
	if (StrToFloat(weijie) == 0.00 ) {
		MessageBox(0,"����Ҫ����ĵ���!","��ʾ",MB_ICONASTERISK);
		return;
	}
	Tfrmautojieshuan * frm = new Tfrmautojieshuan(Application);
	if (Type == 1) {
		frm->Label1->Caption  = "Ӧ��";
	}
	else
	{
		frm->Label1->Caption = "Ӧ��";
	}
	frm->edityinhu->Text =FormatFloat(Disc,StrToFloat(weijie));
	if (cbjieshuantype->ItemIndex == 1) {
		frm->yue = StrToFloat(StringReplace(edityu->Text,",","",TReplaceFlags()<<rfReplaceAll));
	}
	Double shijie = 0.00,tmp = 0.0;
	ts = 0;
	if (mrOk == frm->ShowModal()) {
		shijie = StrToFloat(frm->editshijie->Text);

		float chakuan = 0.00;
		if (!frm->yuhukuan && StrToFloat(weijie) < 0) {
			chakuan = StrToFloat(weijie) - shijie;
		}
		sql = "delete from FN_CUSEndMoneyDtails where EndMoneyDocumentID = " + editnum->Text ;
		Excute(sql);
		selectID->Clear();
		if (Type == 1) {
			sql = "select A.ID,A.stgntcode,A.StgNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,totalfixedprice,totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,CUST_CustomerInfo.Name as custname,A.fapiaotext,A.Remarks,case when A.hcstate = 0 then A.hongcong else 0 end as hongcong "
				" from BS_StorageNoteHeader A left join CUST_CustomerInfo on A.supplierid = CUST_CustomerInfo.id  left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID  where supplierid =" + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex])) + " and nochecked < 0 and state <> 2 and A.StgNtCode <> 0 and A.StgNtCode is not null ";
		}
		else if (Type == 2) {     //as stgntcode
			sql = "select A.ID,A.wsalentcode as stgntcode ,A.WsaleNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,fixedprice as totalfixedprice,discountedprice as totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,dbo.uf_bs_getclientname(CUST_CustomerInfo.id) as custname,A.fapiaotext,A.Remarks,case when A.hcstate = 0 then A.hongcong else 0 end as hongcong "
				" from BS_WsaleNoteHeader A left join CUST_CustomerInfo on A.VendorID = CUST_CustomerInfo.id left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID where VendorID = "+IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex])) +" and  nochecked < 0 and state <> 2 and A.WsaleNtCode <> 0 and A.WsaleNtCode is not null ";
		}
		if (!fmaster) {
			sql = sql + " and SYS_StorageInfo.ID = " + IntToStr(fstgid);
		}
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();
		//AnsiString bb;
		while(!aquery->Eof)
		{
			if (AddEnable(Type,aquery->FieldByName("stgntcode")->AsAnsiString)) {
				if (ts == 0 && aquery->FieldByName("hongcong")->AsFloat != 0.00) {
					Tfrmtishi *frm = new Tfrmtishi(Application);
					frm->edcode->Text = aquery->FieldByName("CodeStr")->AsAnsiString ;
					frm->edmy->Text = aquery->FieldByName("totalfixedprice")->AsAnsiString ;
					frm->edsy->Text = aquery->FieldByName("totaldiscountedprice")->AsAnsiString ;
					frm->edyj->Text = aquery->FieldByName("checked")->AsAnsiString ;
					frm->edwj->Text = aquery->FieldByName("nochecked")->AsAnsiString ;
					frm->edhc->Text = aquery->FieldByName("hongcong")->AsAnsiString ;
					frm->membk->Lines->Append(aquery->FieldByName("Remarks")->AsAnsiString);
					if (frm->ShowModal() == mrOk  ) {
						hc = frm->hc ;
						ts = frm->ts ;
					}
				}
				if (hc && aquery->FieldByName("hongcong")->AsFloat != 0.00) {
					tmp = aquery->FieldByName("nochecked")->AsFloat - aquery->FieldByName("hongcong")->AsFloat;
				}
				else
				{
					tmp = aquery->FieldByName("nochecked")->AsFloat;
				}

				if (chakuan < 0 && tmp < chakuan ) {
					aqdg->Append();
					aqdg->FieldByName("stgntcode")->AsAnsiString = aquery->FieldByName("stgntcode")->AsAnsiString ;
					aqdg->FieldByName("CodeStr")->AsAnsiString = aquery->FieldByName("CodeStr")->AsAnsiString ;
					aqdg->FieldByName("hdtime")->AsDateTime = aquery->FieldByName("hdtime")->AsDateTime  ;
					aqdg->FieldByName("totalfixedprice")->AsFloat = aquery->FieldByName("totalfixedprice")->AsFloat ;
					aqdg->FieldByName("totaldiscountedprice")->AsFloat = aquery->FieldByName("totaldiscountedprice")->AsFloat ;
					aqdg->FieldByName("addcosts")->AsFloat = aquery->FieldByName("addcosts")->AsFloat ;
					aqdg->FieldByName("checked")->AsFloat = aquery->FieldByName("checked")->AsFloat ;
					aqdg->FieldByName("nochecked")->AsFloat = aquery->FieldByName("nochecked")->AsFloat ;
					aqdg->FieldByName("checked")->AsFloat = aquery->FieldByName("checked")->AsFloat ;
					aqdg->FieldByName("totalamount")->AsInteger = aquery->FieldByName("totalamount")->AsInteger ;
					if (hc && aquery->FieldByName("hongcong")->AsFloat != 0.00) {
						aqdg->FieldByName("hongcong")->AsFloat = aquery->FieldByName("hongcong")->AsFloat ;
					}
					aqdg->FieldByName("thistime")->AsFloat = aquery->FieldByName("nochecked")->AsFloat-chakuan;
					aqdg->FieldByName("type")->AsInteger  = Type ;
					aqdg->FieldByName("EndMoneyDocumentID")->AsAnsiString = editnum->Text  ;
					selectID->Add(aqdg->FieldByName("stgntcode")->AsAnsiString);
					chakuan = 0;
					shijie = shijie - tmp + chakuan;
				}
				else if (chakuan < 0 && tmp >= chakuan) {
					chakuan = chakuan - tmp;
				}
				else
				{
					aqdg->Append();
					aqdg->FieldByName("stgntcode")->AsAnsiString = aquery->FieldByName("stgntcode")->AsAnsiString ;
					aqdg->FieldByName("CodeStr")->AsAnsiString = aquery->FieldByName("CodeStr")->AsAnsiString ;
					aqdg->FieldByName("hdtime")->AsDateTime = aquery->FieldByName("hdtime")->AsDateTime  ;
					aqdg->FieldByName("totalfixedprice")->AsFloat = aquery->FieldByName("totalfixedprice")->AsFloat ;
					aqdg->FieldByName("totaldiscountedprice")->AsFloat = aquery->FieldByName("totaldiscountedprice")->AsFloat ;
					aqdg->FieldByName("addcosts")->AsFloat = aquery->FieldByName("addcosts")->AsFloat ;
					aqdg->FieldByName("checked")->AsFloat = aquery->FieldByName("checked")->AsFloat ;
					aqdg->FieldByName("nochecked")->AsFloat = aquery->FieldByName("nochecked")->AsFloat ;
					aqdg->FieldByName("checked")->AsFloat = aquery->FieldByName("checked")->AsFloat ;
					aqdg->FieldByName("totalamount")->AsInteger = aquery->FieldByName("totalamount")->AsInteger ;
					if (hc && aquery->FieldByName("hongcong")->AsFloat != 0.00) {
						aqdg->FieldByName("hongcong")->AsFloat = aquery->FieldByName("hongcong")->AsFloat ;
					}
					aqdg->FieldByName("thistime")->AsFloat = aquery->FieldByName("nochecked")->AsFloat;
					aqdg->FieldByName("type")->AsInteger  = Type ;
					aqdg->FieldByName("EndMoneyDocumentID")->AsAnsiString = editnum->Text  ;
					selectID->Add(aqdg->FieldByName("stgntcode")->AsAnsiString);
					tmp = aqdg->FieldByName("nochecked")->AsFloat;
					shijie = shijie - tmp;
				}
			}
			aquery->Next();
		}
		if (Type == 1) {
			sql = "select A.ID,A.stgntcode,A.StgNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,totalfixedprice,totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,CUST_CustomerInfo.Name as custname,A.fapiaotext,A.Remarks,case when A.hcstate = 0 then A.hongcong else 0 end as hongcong "
				" from BS_StorageNoteHeader A left join CUST_CustomerInfo on A.supplierid = CUST_CustomerInfo.id  left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID  where supplierid =" + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex])) + " and nochecked > 0 and state <> 2 and A.StgNtCode <> 0 and A.StgNtCode is not null ";
		}
		else if (Type == 2) {     //as stgntcode
			sql = "select A.ID,A.wsalentcode as stgntcode ,A.WsaleNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,fixedprice as totalfixedprice,discountedprice as totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,dbo.uf_bs_getclientname(CUST_CustomerInfo.id) as custname,A.fapiaotext,A.Remarks,case when A.hcstate = 0 then A.hongcong else 0 end as hongcong "
				" from BS_WsaleNoteHeader A left join CUST_CustomerInfo on A.VendorID = CUST_CustomerInfo.id left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID where VendorID = "+ IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex])) +" and  nochecked > 0 and state <> 2 and A.WsaleNtCode <> 0 and A.WsaleNtCode is not null ";
		}
		if (!fmaster) {
			sql = sql + " and SYS_StorageInfo.ID = " + IntToStr(fstgid);
		}
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();
		while(!aquery->Eof)
		{
			if (AddEnable(Type,aquery->FieldByName("stgntcode")->AsAnsiString)) {
				if (ts == 0 && aquery->FieldByName("hongcong")->AsFloat != 0.00) {
					Tfrmtishi *frm = new Tfrmtishi(Application);
					frm->edcode->Text = aquery->FieldByName("CodeStr")->AsAnsiString ;
					frm->edmy->Text = aquery->FieldByName("totalfixedprice")->AsAnsiString ;
					frm->edsy->Text = aquery->FieldByName("totaldiscountedprice")->AsAnsiString ;
					frm->edyj->Text = aquery->FieldByName("checked")->AsAnsiString ;
					frm->edwj->Text = aquery->FieldByName("nochecked")->AsAnsiString ;
					frm->edhc->Text = aquery->FieldByName("hongcong")->AsAnsiString ;
					frm->membk->Lines->Append(aquery->FieldByName("Remarks")->AsAnsiString);
					if (frm->ShowModal() == mrOk  ) {
						hc = frm->hc ;
						ts = frm->ts ;
					}
				}
				if (hc && aquery->FieldByName("hongcong")->AsFloat != 0.00) {
					tmp = aquery->FieldByName("nochecked")->AsFloat - aquery->FieldByName("hongcong")->AsFloat;
				}
				else
				{
					tmp = aquery->FieldByName("nochecked")->AsFloat;
				}
				if (shijie - tmp > 0 ) {
					aqdg->Append();
					aqdg->FieldByName("stgntcode")->AsAnsiString = aquery->FieldByName("stgntcode")->AsAnsiString ;
					aqdg->FieldByName("CodeStr")->AsAnsiString = aquery->FieldByName("CodeStr")->AsAnsiString ;
					aqdg->FieldByName("hdtime")->AsDateTime = aquery->FieldByName("hdtime")->AsDateTime  ;
					aqdg->FieldByName("totalfixedprice")->AsFloat = aquery->FieldByName("totalfixedprice")->AsFloat ;
					aqdg->FieldByName("totaldiscountedprice")->AsFloat = aquery->FieldByName("totaldiscountedprice")->AsFloat ;
					aqdg->FieldByName("addcosts")->AsFloat = aquery->FieldByName("addcosts")->AsFloat ;
					aqdg->FieldByName("checked")->AsFloat = aquery->FieldByName("checked")->AsFloat ;
					aqdg->FieldByName("nochecked")->AsFloat = aquery->FieldByName("nochecked")->AsFloat ;
					aqdg->FieldByName("checked")->AsFloat = aquery->FieldByName("checked")->AsFloat ;
					aqdg->FieldByName("totalamount")->AsInteger = aquery->FieldByName("totalamount")->AsInteger ;
					if (hc && aquery->FieldByName("hongcong")->AsFloat != 0.00) {
						aqdg->FieldByName("hongcong")->AsFloat = aquery->FieldByName("hongcong")->AsFloat ;
					}
					aqdg->FieldByName("thistime")->AsFloat = aquery->FieldByName("nochecked")->AsFloat;
					aqdg->FieldByName("type")->AsInteger  = Type ;
					aqdg->FieldByName("EndMoneyDocumentID")->AsAnsiString = editnum->Text  ;
					selectID->Add(aqdg->FieldByName("stgntcode")->AsAnsiString);
				}
				else
				{
					aqdg->Append();
					aqdg->FieldByName("stgntcode")->AsAnsiString = aquery->FieldByName("stgntcode")->AsAnsiString ;
					aqdg->FieldByName("CodeStr")->AsAnsiString = aquery->FieldByName("CodeStr")->AsAnsiString ;
					aqdg->FieldByName("hdtime")->AsDateTime = aquery->FieldByName("hdtime")->AsDateTime  ;
					aqdg->FieldByName("totalfixedprice")->AsFloat = aquery->FieldByName("totalfixedprice")->AsFloat ;
					aqdg->FieldByName("totaldiscountedprice")->AsFloat = aquery->FieldByName("totaldiscountedprice")->AsFloat ;
					aqdg->FieldByName("addcosts")->AsFloat = aquery->FieldByName("addcosts")->AsFloat ;
					aqdg->FieldByName("checked")->AsFloat = aquery->FieldByName("checked")->AsFloat ;
					aqdg->FieldByName("nochecked")->AsFloat = aquery->FieldByName("nochecked")->AsFloat ;
					aqdg->FieldByName("checked")->AsFloat = aquery->FieldByName("checked")->AsFloat ;
					aqdg->FieldByName("totalamount")->AsInteger = aquery->FieldByName("totalamount")->AsInteger ;
					if (hc && aquery->FieldByName("hongcong")->AsFloat != 0.00) {
						aqdg->FieldByName("hongcong")->AsFloat = aquery->FieldByName("hongcong")->AsFloat ;
						aqdg->FieldByName("thistime")->AsFloat = shijie + aquery->FieldByName("hongcong")->AsFloat ;
					}
					else
					{
						aqdg->FieldByName("thistime")->AsFloat = shijie;
					}

					aqdg->FieldByName("type")->AsInteger  = Type ;
					aqdg->FieldByName("EndMoneyDocumentID")->AsAnsiString = editnum->Text  ;
					selectID->Add(aqdg->FieldByName("stgntcode")->AsAnsiString);
					break;
				}

				shijie = shijie - tmp;
			}
			aquery->Next();
		}

		if (frm->yuhukuan && shijie > 0 && cbjieshuantype->ItemIndex == 0) {      //����Ԥ���
			sql = "update FN_CUSEndMoneyDocuments set yuhu = " + FloatToStr(shijie) + " where MoneyCode = " + editnum->Text ;
			Excute(sql);
		}
		else
		{
			sql = "update FN_CUSEndMoneyDocuments set yuhu = 0 where MoneyCode = " + editnum->Text ;
			Excute(sql);
		}
		aqdg->UpdateBatch(arAll);
		DisplayDetail(editnum->Text);
		Displaytotal(editnum->Text);
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::BtnViewClick(TObject *Sender)
{
	Print(1);
}
//---------------------------------------------------------------------------

void Tfrmbalance::Print(int modle)
{
	if (aqdg->IsEmpty() ) {
		return;
	}
       //	RvSystem1->SystemSetups >>ssAllowSetup;
	//RvSystem1->SystemSetups >>ssAllowDestPreview;
	//RvSystem1->SystemSetups >>ssAllowDestPrinter;
      //	RvSystem1->SystemSetups >>ssAllowPrinterSetup;
      //	RvSystem1->SystemSetups >>ssAllowDestFile;
	if (modle == 1) {
		RvSystem1->DefaultDest  = rdPreview ;
	}
	else
	{
		RvSystem1->DefaultDest  = rdPrinter ;
	}
	RvSystem1->SystemSetups<<ssAllowDestPrinter;

	if (Type == 1) {
		if (ChangeDisplay) {
			RvProject1->ProjectFile = ExtractFilePath(Application->ExeName) + "supplierfance1.rav";
		}
		else
		{
			RvProject1->ProjectFile = ExtractFilePath(Application->ExeName) + "supplierfance.rav";
		}
		RvProject1->Open();
		RvProject1->SetParam("title",Edit2->Text + "���");
		RvProject1->SetParam("Name",cbselect->Text);
	}
	else
	{
		if (ChangeDisplay) {
			RvProject1->ProjectFile  =ExtractFilePath(Application->ExeName) + "clientfance1.rav";
		}
		else
		{
			RvProject1->ProjectFile  =ExtractFilePath(Application->ExeName) + "clientfance.rav";
		}
		RvProject1->Open();
		RvProject1->SetParam("title",Edit2->Text + "�տ");
		RvProject1->SetParam("Name",cbselect->Text);
	}
	RvProject1->SetParam("yue",edityu->Text);
	RvProject1->SetParam("yuhu",edityuhu->Text);
	RvProject1->SetParam("weijie",editweijiedan->Text);
	RvProject1->SetParam("yingfu",edityinghu->Text);
	RvProject1->SetParam("Danhao",editnum->Text);
	RvProject1->SetParam("riqi",DateToStr(dtp->Date));
	RvProject1->SetParam("state",editstate->Text);
	RvProject1->SetParam("style",cbjieshuantype->Text);
	RvProject1->SetParam("method",cbmethod->Text);
	RvProject1->SetParam("pingz",edjspz->Text);
	RvProject1->SetParam("bk",membk->Text);
	RvProject1->SetParam("maker",edemploy->Text);
	TRavePage *RavePage;
	TRaveRegion *RaveRegion;
	TRaveCalcText *calctext3,*calctext4,*calctext5,*calctext6,*calctext7;
	TRaveBand *raveband;
	RavePage = (TRavePage *)RvProject1->ProjMan->FindRaveComponent("Report1.Page1",NULL);
	calctext3 =  (TRaveCalcText *)RvProject1->ProjMan->FindRaveComponent("CalcText3",RavePage);
	calctext4 =  (TRaveCalcText *)RvProject1->ProjMan->FindRaveComponent("CalcText4",RavePage);
	calctext5 =  (TRaveCalcText *)RvProject1->ProjMan->FindRaveComponent("CalcText5",RavePage);
	calctext6 =  (TRaveCalcText *)RvProject1->ProjMan->FindRaveComponent("CalcText6",RavePage);
	calctext7 =  (TRaveCalcText *)RvProject1->ProjMan->FindRaveComponent("CalcText7",RavePage);

	calctext3->DisplayFormat = Disc;
	calctext4->DisplayFormat = Disc;
	calctext5->DisplayFormat = Disc;
	calctext6->DisplayFormat = Disc;
	calctext7->DisplayFormat = Disc;

	RvProject1->Execute();
	RvProject1->Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::BtnPrintClick(TObject *Sender)
{
	Print(2);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::btduicongClick(TObject *Sender)
{
	if (editnum->Text == "") {
		return;
	}
	ts = 0;
	AnsiString weijie,sql;
	weijie = StringReplace(editweijiedan->Text,",","",TReplaceFlags()<<rfReplaceAll);
	sql = "delete from FN_CUSEndMoneyDtails where EndMoneyDocumentID = " + editnum->Text ;
	Excute(sql);
	selectID->Clear();
	DOUBLE shijie = 0.00,tmp = 0.0;
	//AnsiString bb;
	if (StrToFloat(weijie) > 0.00 ) {
		if (Type == 1) {
			sql = "select A.ID,A.stgntcode,A.StgNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,totalfixedprice,totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,CUST_CustomerInfo.Name as custname,A.fapiaotext,A.Remarks,case when A.hcstate = 0 then A.hongcong else 0 end as hongcong "
				" from BS_StorageNoteHeader A left join CUST_CustomerInfo on A.supplierid = CUST_CustomerInfo.id  left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID  where supplierid = " + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex])) + " and nochecked < 0 and state <> 2 and A.StgNtCode <> 0 and A.StgNtCode is not null ";
		}
		else if (Type == 2) {     //as stgntcode
			sql = "select A.ID,A.wsalentcode as stgntcode ,A.WsaleNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,fixedprice as totalfixedprice,discountedprice as totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,dbo.uf_bs_getclientname(CUST_CustomerInfo.id) as custname,A.fapiaotext,A.Remarks,case when A.hcstate = 0 then A.hongcong else 0 end as hongcong "
				" from BS_WsaleNoteHeader A left join CUST_CustomerInfo on A.VendorID = CUST_CustomerInfo.id left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID where VendorID = " + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex])) +" and  nochecked < 0 and state <> 2 and A.WsaleNtCode <> 0 and A.WsaleNtCode is not null ";
		}
	}
	else
	{
		if (Type == 1) {
			sql = "select A.ID,A.stgntcode,A.StgNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,totalfixedprice,totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,CUST_CustomerInfo.Name as custname,A.fapiaotext,A.Remarks,case when A.hcstate = 0 then A.hongcong else 0 end as hongcong "
				" from BS_StorageNoteHeader A left join CUST_CustomerInfo on A.supplierid = CUST_CustomerInfo.id  left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID  where supplierid =" + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex])) + " and nochecked > 0 and state <> 2 and A.StgNtCode <> 0 and A.StgNtCode is not null ";
		}
		else if (Type == 2) {     //as stgntcode
			sql = "select A.ID,A.wsalentcode as stgntcode ,A.WsaleNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,fixedprice as totalfixedprice,discountedprice as totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,dbo.uf_bs_getclientname(CUST_CustomerInfo.id) as custname,A.fapiaotext,A.Remarks,case when A.hcstate = 0 then A.hongcong else 0 end as hongcong "
				" from BS_WsaleNoteHeader A left join CUST_CustomerInfo on A.VendorID = CUST_CustomerInfo.id left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID where VendorID = " + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex])) +" and  nochecked > 0 and state <> 2 and A.WsaleNtCode <> 0 and A.WsaleNtCode is not null ";
		}
	}
	if (!fmaster) {
		sql = sql + " and SYS_StorageInfo.ID = " + IntToStr(fstgid);
	}
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	while(!aquery->Eof)
	{
		if (AddEnable(Type,aquery->FieldByName("stgntcode")->AsAnsiString)) {
			if (ts == 0 && aquery->FieldByName("hongcong")->AsFloat != 0.00) {
				Tfrmtishi *frm = new Tfrmtishi(Application);
				frm->edcode->Text = aquery->FieldByName("CodeStr")->AsAnsiString ;
				frm->edmy->Text = aquery->FieldByName("totalfixedprice")->AsAnsiString ;
				frm->edsy->Text = aquery->FieldByName("totaldiscountedprice")->AsAnsiString ;
				frm->edyj->Text = aquery->FieldByName("checked")->AsAnsiString ;
				frm->edwj->Text = aquery->FieldByName("nochecked")->AsAnsiString ;
				frm->edhc->Text = aquery->FieldByName("hongcong")->AsAnsiString ;
				frm->membk->Lines->Append(aquery->FieldByName("Remarks")->AsAnsiString);
				if (frm->ShowModal() == mrOk) {
					hc = frm->hc ;
					ts = frm->ts ;
				}
			}
			aqdg->Append();
			aqdg->FieldByName("stgntcode")->AsAnsiString = aquery->FieldByName("stgntcode")->AsAnsiString ;
			aqdg->FieldByName("CodeStr")->AsAnsiString = aquery->FieldByName("CodeStr")->AsAnsiString ;
			aqdg->FieldByName("hdtime")->AsDateTime = aquery->FieldByName("hdtime")->AsDateTime  ;
			aqdg->FieldByName("totalfixedprice")->AsFloat = aquery->FieldByName("totalfixedprice")->AsFloat ;
			aqdg->FieldByName("totaldiscountedprice")->AsFloat = aquery->FieldByName("totaldiscountedprice")->AsFloat ;
			aqdg->FieldByName("addcosts")->AsFloat = aquery->FieldByName("addcosts")->AsFloat ;
			aqdg->FieldByName("checked")->AsFloat = aquery->FieldByName("checked")->AsFloat ;
			aqdg->FieldByName("nochecked")->AsFloat = aquery->FieldByName("nochecked")->AsFloat ;
			aqdg->FieldByName("checked")->AsFloat = aquery->FieldByName("checked")->AsFloat ;
			aqdg->FieldByName("totalamount")->AsInteger = aquery->FieldByName("totalamount")->AsInteger ;
			if (hc && aquery->FieldByName("hongcong")->AsFloat != 0.00) {
				aqdg->FieldByName("hongcong")->AsFloat = aquery->FieldByName("hongcong")->AsFloat ;
			}
			aqdg->FieldByName("thistime")->AsFloat = aquery->FieldByName("nochecked")->AsFloat;
			aqdg->FieldByName("type")->AsInteger  = Type ;
			aqdg->FieldByName("EndMoneyDocumentID")->AsAnsiString = editnum->Text  ;
			selectID->Add(aqdg->FieldByName("stgntcode")->AsAnsiString);

			if (hc && aquery->FieldByName("hongcong")->AsFloat != 0.00) {
				tmp = aquery->FieldByName("nochecked")->AsFloat - aquery->FieldByName("hongcong")->AsFloat;
			}
			else
			{
				tmp = aquery->FieldByName("nochecked")->AsFloat;
			}
			shijie = shijie + tmp;
		}
		aquery->Next();

	}
	if (shijie > 0.00) {
		if (Type == 1) {
			sql = "select A.ID,A.stgntcode,A.StgNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,totalfixedprice,totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,CUST_CustomerInfo.Name as custname,A.fapiaotext,A.Remarks,case when A.hcstate = 0 then A.hongcong else 0 end as hongcong "
				" from BS_StorageNoteHeader A left join CUST_CustomerInfo on A.supplierid = CUST_CustomerInfo.id  left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID  where supplierid =" + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex])) + " and nochecked < 0 and state <> 2 and A.StgNtCode <> 0 and A.StgNtCode is not null ";
		}
		else if (Type == 2) {     //as stgntcode
			sql = "select A.ID,A.wsalentcode as stgntcode ,A.WsaleNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,fixedprice as totalfixedprice,discountedprice as totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,dbo.uf_bs_getclientname(CUST_CustomerInfo.id) as custname,A.fapiaotext,A.Remarks,case when A.hcstate = 0 then A.hongcong else 0 end as hongcong "
				" from BS_WsaleNoteHeader A left join CUST_CustomerInfo on A.VendorID = CUST_CustomerInfo.id left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID where VendorID = "+ IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex])) +" and  nochecked < 0 and state <> 2 and A.WsaleNtCode <> 0 and A.WsaleNtCode is not null ";
		}
		if (!fmaster) {
			sql = sql + " and SYS_StorageInfo.ID = " + IntToStr(fstgid);
		}
	}
	else if (shijie < 0.00) {
		if (Type == 1) {
			sql = "select A.ID,A.stgntcode,A.StgNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,totalfixedprice,totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,CUST_CustomerInfo.Name as custname,A.fapiaotext,A.Remarks,case when A.hcstate = 0 then A.hongcong else 0 end as hongcong "
				" from BS_StorageNoteHeader A left join CUST_CustomerInfo on A.supplierid = CUST_CustomerInfo.id  left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID  where supplierid =" + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex])) + " and nochecked > 0 and state <> 2 and A.StgNtCode <> 0 and A.StgNtCode is not null ";
		}
		else if (Type == 2) {     //as stgntcode
			sql = "select A.ID,A.wsalentcode as stgntcode ,A.WsaleNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,fixedprice as totalfixedprice,discountedprice as totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,dbo.uf_bs_getclientname(CUST_CustomerInfo.id) as custname,A.fapiaotext,A.Remarks,case when A.hcstate = 0 then A.hongcong else 0 end as hongcong "
				" from BS_WsaleNoteHeader A left join CUST_CustomerInfo on A.VendorID = CUST_CustomerInfo.id left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID where VendorID = "+ IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex])) +" and  nochecked > 0 and state <> 2 and A.WsaleNtCode <> 0 and A.WsaleNtCode is not null ";
		}
		if (!fmaster) {
			sql = sql + " and SYS_StorageInfo.ID = " + IntToStr(fstgid);
		}
	}
	shijie = 0.00-shijie;

	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	while(!aquery->Eof)
	{
		if (AddEnable(Type,aquery->FieldByName("stgntcode")->AsAnsiString)) {
			if (ts == 0 && aquery->FieldByName("hongcong")->AsFloat != 0.00) {
				Tfrmtishi *frm = new Tfrmtishi(Application);
				frm->edcode->Text = aquery->FieldByName("CodeStr")->AsAnsiString ;
				frm->edmy->Text = aquery->FieldByName("totalfixedprice")->AsAnsiString ;
				frm->edsy->Text = aquery->FieldByName("totaldiscountedprice")->AsAnsiString ;
				frm->edyj->Text = aquery->FieldByName("checked")->AsAnsiString ;
				frm->edwj->Text = aquery->FieldByName("nochecked")->AsAnsiString ;
				frm->edhc->Text = aquery->FieldByName("hongcong")->AsAnsiString ;
				frm->membk->Lines->Append(aquery->FieldByName("Remarks")->AsAnsiString);
				if (frm->ShowModal() == mrOk) {
					hc = frm->hc ;
					ts = frm->ts ;
				}
			}
			if (hc && aquery->FieldByName("hongcong")->AsFloat != 0.00) {
				tmp = aquery->FieldByName("nochecked")->AsFloat - aquery->FieldByName("hongcong")->AsFloat ;
			}
			else
			{
				tmp = aquery->FieldByName("nochecked")->AsFloat;
			}
			if ((shijie - tmp > 0 && shijie > 0) || (shijie - tmp < 0 && shijie < 0) ) {
				aqdg->Append();
				aqdg->FieldByName("stgntcode")->AsAnsiString = aquery->FieldByName("stgntcode")->AsAnsiString ;
				aqdg->FieldByName("CodeStr")->AsAnsiString = aquery->FieldByName("CodeStr")->AsAnsiString ;
				aqdg->FieldByName("hdtime")->AsDateTime = aquery->FieldByName("hdtime")->AsDateTime  ;
				aqdg->FieldByName("totalfixedprice")->AsFloat = aquery->FieldByName("totalfixedprice")->AsFloat ;
				aqdg->FieldByName("totaldiscountedprice")->AsFloat = aquery->FieldByName("totaldiscountedprice")->AsFloat ;
				aqdg->FieldByName("addcosts")->AsFloat = aquery->FieldByName("addcosts")->AsFloat ;
				aqdg->FieldByName("checked")->AsFloat = aquery->FieldByName("checked")->AsFloat ;
				aqdg->FieldByName("nochecked")->AsFloat = aquery->FieldByName("nochecked")->AsFloat ;
				aqdg->FieldByName("checked")->AsFloat = aquery->FieldByName("checked")->AsFloat ;
				aqdg->FieldByName("totalamount")->AsInteger = aquery->FieldByName("totalamount")->AsInteger ;
				if (hc && aquery->FieldByName("hongcong")->AsFloat != 0.00){
					aqdg->FieldByName("hongcong")->AsFloat = aquery->FieldByName("hongcong")->AsFloat ;
				}
				aqdg->FieldByName("thistime")->AsFloat = aquery->FieldByName("nochecked")->AsFloat;
				aqdg->FieldByName("type")->AsInteger  = Type ;
				aqdg->FieldByName("EndMoneyDocumentID")->AsAnsiString = editnum->Text  ;
				selectID->Add(aqdg->FieldByName("stgntcode")->AsAnsiString);
			}
			else
			{
				aqdg->Append();
				aqdg->FieldByName("stgntcode")->AsAnsiString = aquery->FieldByName("stgntcode")->AsAnsiString ;
				aqdg->FieldByName("CodeStr")->AsAnsiString = aquery->FieldByName("CodeStr")->AsAnsiString ;
				aqdg->FieldByName("hdtime")->AsDateTime = aquery->FieldByName("hdtime")->AsDateTime  ;
				aqdg->FieldByName("totalfixedprice")->AsFloat = aquery->FieldByName("totalfixedprice")->AsFloat ;
				aqdg->FieldByName("totaldiscountedprice")->AsFloat = aquery->FieldByName("totaldiscountedprice")->AsFloat ;
				aqdg->FieldByName("addcosts")->AsFloat = aquery->FieldByName("addcosts")->AsFloat ;
				aqdg->FieldByName("checked")->AsFloat = aquery->FieldByName("checked")->AsFloat ;
				aqdg->FieldByName("nochecked")->AsFloat = aquery->FieldByName("nochecked")->AsFloat ;
				aqdg->FieldByName("checked")->AsFloat = aquery->FieldByName("checked")->AsFloat ;
				aqdg->FieldByName("totalamount")->AsInteger = aquery->FieldByName("totalamount")->AsInteger ;
				if (hc && aquery->FieldByName("hongcong")->AsFloat != 0.00){
					aqdg->FieldByName("hongcong")->AsFloat = aquery->FieldByName("hongcong")->AsFloat ;
					aqdg->FieldByName("thistime")->AsFloat = shijie + aquery->FieldByName("hongcong")->AsFloat;
				}
				else
				{
					aqdg->FieldByName("thistime")->AsFloat = shijie;
				}
				aqdg->FieldByName("type")->AsInteger  = Type ;
				aqdg->FieldByName("EndMoneyDocumentID")->AsAnsiString = editnum->Text  ;
				selectID->Add(aqdg->FieldByName("stgntcode")->AsAnsiString);
				break;
			}
			shijie = shijie - tmp;
		}

		aquery->Next();
	}
	aqdg->UpdateBatch(arAll);
	DisplayDetail(editnum->Text);
	Displaytotal(editnum->Text);
}
//---------------------------------------------------------------------------


void __fastcall Tfrmbalance::N2Click(TObject *Sender)
{
	if (aqdg->IsEmpty() ) {
		return;
	}
	for (int i = 1; i <= aqdg->RecordCount ; i++) {
		dg->DataSource->DataSet->RecNo = i;
		dg->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------


void __fastcall Tfrmbalance::edtQryVendorExit(TObject *Sender)
{
	edtQryVendor->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::cbselectKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		cbselect->OnSelect(this);
		cbjieshuantype->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::cbselectSelect(TObject *Sender)
{
	String sql;
	int custID;
	float tmpweijie,tmpyinhu;
	try {
		custID = (int)(cbselect->Items->Objects[cbselect->ItemIndex]);

	} catch (...) {

        ShowMsg(Handle ,"��ѡ����ȷ�Ŀͻ���",0);
	}

	if (Type == 1) {
		 sql = "select sum(NoChecked) as totalnochecked from BS_StorageNoteHeader where supplierid= " + IntToStr(custID);
	}else
	{
		sql = " select sum(NoChecked) as totalnochecked  from BS_WsaleNoteHeader where VendorID in  (select ID from GetChild("+IntToStr(custID)+"))";
	}

	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	editweijiedan->Text = FormatFloat(Disc,aquery->FieldByName("totalnochecked")->AsFloat);
    if (aquery->FieldByName("totalnochecked")->AsFloat == 0.00) {
		cbjieshuantype->ItemIndex = 2;
		spselect->Enabled = false;
		sbautojieshuan->Enabled = false;
		autobt->Enabled = false;
		btduicong->Enabled = false;
	}
	else
	{
		cbjieshuantype->ItemIndex = -1;
		spselect->Enabled = true;
		sbautojieshuan->Enabled = true;
		autobt->Enabled = true;
		btduicong->Enabled = true;
	}
	sql = "select totalyue + balance as totalyue from CUST_CustomerStartMoney   where customerid =" + IntToStr(custID) ;
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	edityu->Text =  FormatFloat(Disc,aquery->FieldByName("totalyue")->AsFloat);
	edityuhu->Text =FormatFloat(Disc,aquery->FieldByName("totalyue")->AsFloat);

	editweijiedan->Text = StringReplace(editweijiedan->Text,",","",TReplaceFlags()<<rfReplaceAll);
	edityu->Text =StringReplace(edityu->Text,",","",TReplaceFlags()<<rfReplaceAll);

	tmpweijie =  StrToFloat(editweijiedan->Text);
    tmpyinhu =  StrToFloat(edityu->Text);
	if (StrToFloat(edityu->Text) > StrToFloat(editweijiedan->Text)) {

	 edityinghu->Text = FormatFloat(Disc,StrToFloat(editweijiedan->Text));
	} else if (StrToFloat(edityu->Text)< StrToFloat(editweijiedan->Text)) {
	   edityinghu->Text = FormatFloat(Disc,(tmpweijie-tmpyinhu ));
	}else if (StrToFloat(edityu->Text)== StrToFloat(editweijiedan->Text)) {
	  edityinghu->Text = "0.00";
	}
}
//---------------------------------------------------------------------------


void __fastcall Tfrmbalance::cbjieshuantypeChange(TObject *Sender)
{
	if ( cbselect->Text == "") {
		return;
	}
	if (cbjieshuantype->Text == "Ԥ����" || cbjieshuantype->Text == "Ԥ�տ�" || cbjieshuantype->Text == "����˿�") {
		spselect->Enabled = false;
		sbautojieshuan->Enabled = false;
		autobt->Enabled = false;
		btduicong->Enabled = false;
		editmoney->Enabled = true;
	}
	else if (cbjieshuantype->ItemIndex == 3) {
		btduicong->Enabled = true;
		spselect->Enabled = false;
		sbautojieshuan->Enabled = false;
		autobt->Enabled = false;
		editmoney->Enabled = false;
	}
	else
	{
		btduicong->Enabled = false;
		spselect->Enabled = true;
		sbautojieshuan->Enabled = true;
		autobt->Enabled = true;
		editmoney->Enabled = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::cbjieshuantypeExit(TObject *Sender)
{
	if ( cbselect->Text == "") {
		return;
	}
	AnsiString weijie,yue,sql;
	yue = StringReplace(edityu->Text,",","",TReplaceFlags()<<rfReplaceAll);
	if (StrToFloat(yue) == 0.00 && (cbjieshuantype->ItemIndex == 1 || cbjieshuantype->ItemIndex == 4)) {

                ShowMsg(Handle ,"û���������������н�",0);
                return;
		cbjieshuantype->ItemIndex = -1;
		btduicong->Enabled = true;
		spselect->Enabled = true;
		sbautojieshuan->Enabled = true;
		autobt->Enabled = true;
		editmoney->Enabled = true;
		cbjieshuantype->SetFocus();
		return;
	}
	weijie = StringReplace(editweijiedan->Text,",","",TReplaceFlags()<<rfReplaceAll);
	if (StrToFloat(weijie) == 0.00 && StrToFloat(yue) == 0 && cbjieshuantype->ItemIndex != 2) {
		if (Type == 1) {

                        ShowMsg(Handle ,"����Ҫ����ĵ��ݣ�ֻ��ѡ��Ԥ���",0);
		}
		else
		{

                        ShowMsg(Handle ,"����Ҫ����ĵ��ݣ�ֻ��ѡ��Ԥ�տ�!",0);
		}
		cbjieshuantype->ItemIndex = 2;
		btduicong->Enabled = false;
		spselect->Enabled = false;
		sbautojieshuan->Enabled = false;
		autobt->Enabled = false;
		editmoney->Enabled = true;
		cbjieshuantype->SetFocus();
		return;
	}
	else if ((cbjieshuantype->ItemIndex != 2 && cbjieshuantype->ItemIndex != 4) && StrToFloat(weijie) == 0.00 ) {
		if (Type == 1) {

                        ShowMsg(Handle ,"����Ҫ����ĵ��ݣ�ֻ��ѡ��Ԥ���������˿�!",0);
		}
		else
		{
                        ShowMsg(Handle ,"����Ҫ����ĵ��ݣ�ֻ��ѡ��Ԥ�տ������˿�!",0);
		}

		cbjieshuantype->ItemIndex = 2;
		btduicong->Enabled = false;
		spselect->Enabled = false;
		sbautojieshuan->Enabled = false;
		autobt->Enabled = false;
		editmoney->Enabled = true;
		cbjieshuantype->SetFocus();
		return;
	}
	else if (cbjieshuantype->ItemIndex == 3) {
		if (Type == 1) {
			sql = "select A.ID,A.stgntcode,A.StgNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,totalfixedprice,totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,CUST_CustomerInfo.Name as custname,A.fapiaotext,A.Remarks "
				" from BS_StorageNoteHeader A left join CUST_CustomerInfo on A.supplierid = CUST_CustomerInfo.id  left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID  where supplierid = " + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex])) + " and nochecked < 0 and state <> 2 and A.StgNtCode <> 0 and A.StgNtCode is not null ";
		}
		else if (Type == 2) {     //as stgntcode
			sql = "select A.ID,A.wsalentcode as stgntcode ,A.WsaleNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,fixedprice as totalfixedprice,discountedprice as totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,dbo.uf_bs_getclientname(CUST_CustomerInfo.id) as custname,A.fapiaotext,A.Remarks "
				" from BS_WsaleNoteHeader A left join CUST_CustomerInfo on A.VendorID = CUST_CustomerInfo.id left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID where VendorID = " + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex])) +" and  nochecked < 0 and state <> 2 and A.WsaleNtCode <> 0 and A.WsaleNtCode is not null ";
		}
		if (!fmaster) {
			sql = sql + " and SYS_StorageInfo.ID = " + IntToStr(fstgid);
		}
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();
		if (aquery->IsEmpty() ) {

                        ShowMsg(Handle ,"�޶Գ嵥�ݣ�����ʹ�������Գ�!",3);
			cbjieshuantype->ItemIndex = -1;
			btduicong->Enabled = true;
			spselect->Enabled = true;
			sbautojieshuan->Enabled = true;
			autobt->Enabled = true;
			editmoney->Enabled = true;
			cbjieshuantype->SetFocus();
			return;
		}
		if (Type == 1) {
			sql = "select A.ID,A.stgntcode,A.StgNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,totalfixedprice,totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,CUST_CustomerInfo.Name as custname,A.fapiaotext,A.Remarks "
				" from BS_StorageNoteHeader A left join CUST_CustomerInfo on A.supplierid = CUST_CustomerInfo.id  left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID  where supplierid =" + IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex])) + " and nochecked > 0 and state <> 2 and A.StgNtCode <> 0 and A.StgNtCode is not null ";
		}
		else if (Type == 2) {     //as stgntcode
			sql = "select A.ID,A.wsalentcode as stgntcode ,A.WsaleNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then 'δ��' when 1 then 'δ����' end as state,fixedprice as totalfixedprice,discountedprice as totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,dbo.uf_bs_getclientname(CUST_CustomerInfo.id) as custname,A.fapiaotext,A.Remarks "
				" from BS_WsaleNoteHeader A left join CUST_CustomerInfo on A.VendorID = CUST_CustomerInfo.id left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID where VendorID = "+ IntToStr((int)(cbselect->Items->Objects[cbselect->ItemIndex])) +" and  nochecked > 0 and state <> 2 and A.WsaleNtCode <> 0 and A.WsaleNtCode is not null ";
		}
		if (!fmaster) {
			sql = sql + " and SYS_StorageInfo.ID = " + IntToStr(fstgid);
		}
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();
		if (aquery->IsEmpty() ) {

                         ShowMsg(Handle ,"�޶Գ嵥�ݣ�����ʹ�������Գ�!",3);
			cbjieshuantype->ItemIndex = -1;
			btduicong->Enabled = true;
			spselect->Enabled = true;
			sbautojieshuan->Enabled = true;
			autobt->Enabled = true;
			editmoney->Enabled = true;
			cbjieshuantype->SetFocus();
			return;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::cbjieshuantypeKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        cbmethod->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmbalance::cbmethodKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		edjspz->SetFocus();
	}
}
//---------------------------------------------------------------------------
bool Tfrmbalance::AddEnable(int type,AnsiString code)
{
	AnsiString sql;
	TADOQuery *aq1 = new TADOQuery(NULL);
	aq1->Connection = fcon;

	if (type == 1) {
		sql = "select * from FN_CUSEndMoneyDocuments left join FN_CUSEndMoneyDtails on FN_CUSEndMoneyDocuments.MoneyCode = FN_CUSEndMoneyDtails.EndMoneyDocumentID "
			" where FN_CUSEndMoneyDocuments.type = 1 and FN_CUSEndMoneyDtails.type = 1 and FN_CUSEndMoneyDocuments.state = 0 and FN_CUSEndMoneyDtails.stgntcode = " + code;
	}
	else
	{
		sql = "select * from FN_CUSEndMoneyDocuments left join FN_CUSEndMoneyDtails on FN_CUSEndMoneyDocuments.MoneyCode = FN_CUSEndMoneyDtails.EndMoneyDocumentID "
			" where FN_CUSEndMoneyDocuments.type = 2 and FN_CUSEndMoneyDtails.type = 2 and FN_CUSEndMoneyDocuments.state = 0 and FN_CUSEndMoneyDtails.stgntcode = " + code;
	}
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->Open();

	if (aq1->RecordCount > 0) {
		delete aq1;
		return false;
	}
	else
	{
		delete aq1;
		return true;
	}
}
//---------------------------------------------------------------------------



