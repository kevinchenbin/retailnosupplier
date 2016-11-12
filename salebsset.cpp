//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "salebsset.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzCmboBx"
#pragma resource "*.dfm"
Tfrmsalebsset *frmsalebsset;
//---------------------------------------------------------------------------
__fastcall Tfrmsalebsset::Tfrmsalebsset(TComponent* Owner,TADOConnection* con)
	: TForm(Owner)
{
   aquery->Connection = con;
   qryretairange->Connection = con;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsalebsset::sbokClick(TObject *Sender)
{
   AnsiString sql,bk;
   int bit,defaultdiscount;
   //���ȼ����ж�
   if ((cb1->ItemIndex == cb2->ItemIndex ) || (cb1->ItemIndex == cb3->ItemIndex) ||
	   (cb1->ItemIndex == cb4->ItemIndex ) || (cb2->ItemIndex == cb3->ItemIndex) ||
	   (cb2->ItemIndex == cb4->ItemIndex ) || (cb3->ItemIndex == cb4->ItemIndex ) ||
	   (cb1->ItemIndex == cb5->ItemIndex ) || (cb2->ItemIndex == cb5->ItemIndex ) ||
	   (cb3->ItemIndex == cb5->ItemIndex ) || (cb4->ItemIndex == cb5->ItemIndex )  ||
           (cb1->ItemIndex == cb6->ItemIndex)  || (cb2->ItemIndex == cb6->ItemIndex )  ||
           (cb3->ItemIndex == cb6->ItemIndex ) || (cb4->ItemIndex == cb6->ItemIndex ) ||
           (cb5->ItemIndex == cb6->ItemIndex )
           ) {
		ShowMsg(Handle ,"ͬһ���۷�ʽ����ͬʱ��ѡ��",0);
		return;
   }
   int id;
	try {
		id = (int)(cb1->Items->Objects[cb1->ItemIndex]);
	} catch (...) {
		ShowMsg(this->Handle,"��ѡ����ȷ�ĵ�һ�����۷�ʽ��",3);
		return;
	}

	try {
		id = (int)(cb2->Items->Objects[cb2->ItemIndex]);
	} catch (...) {
		ShowMsg(this->Handle,"��ѡ����ȷ�ĵڶ������۷�ʽ��",3);
		return;
	}

	try {
		id = (int)(cb3->Items->Objects[cb3->ItemIndex]);
	} catch (...) {
		ShowMsg(this->Handle,"��ѡ����ȷ�ĵ��������۷�ʽ��",3);
		return;
	}

	try {
		id = (int)(cb4->Items->Objects[cb4->ItemIndex]);
	} catch (...) {
		ShowMsg(this->Handle,"��ѡ����ȷ�ĵ��ļ����۷�ʽ��",3);
		return;
	}

	try {
		id = (int)(cb5->Items->Objects[cb5->ItemIndex]);
	} catch (...) {
		ShowMsg(this->Handle,"��ѡ����ȷ�ĵ��弶���۷�ʽ��",3);
		return;
	}
        try {
		id = (int)(cb6->Items->Objects[cb6->ItemIndex]);
	} catch (...) {
		ShowMsg(this->Handle,"��ѡ����ȷ�ĵ��������۷�ʽ��",3);
		return;
	}
   //С����λ��
   if (etdot->Text == "") {
		bit = 0;
   }
   else
   {
		bit = StrToInt(etdot->Text.Trim() );
   }
   if (bit > 4) {

           ShowMsg(Handle ,"С��λ�����ֻ������4λ��",0);
	   return;
   }
   //Ĭ�������ۿ�
   try {
		defaultdiscount = StrToFloat(eddefaultdiscount->Text);
   } catch (...) {

                ShowMsg(Handle ,"��������ȷ���ۿۣ�",0);
		return;
   }
   if (defaultdiscount > 100) {

                ShowMsg(Handle ,"�ۿ۲��ܴ���100��",0);
		return;
   }
   if (defaultdiscount < 0) {

                ShowMsg(Handle ,"�ۿ۲���С��0��",0);
		return;
   }
   bk = "0";
   if (bit > 0) {
		bk = bk + ".";
		for (int i = 0; i < bit; i++) {
			bk = bk + "0";
		}
   }
   sql = "update sys_bsset set bk = '" + bk + "' where name = 'salexiaoshudian'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();

   sql = "update sys_bsset set bk = '1' where id = " + IntToStr((int)(cb1->Items->Objects[cb1->ItemIndex])) ;
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   sql = "update sys_bsset set bk = '2' where id = " + IntToStr((int)(cb2->Items->Objects[cb2->ItemIndex])) ;
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   sql = "update sys_bsset set bk = '3' where id = " + IntToStr((int)(cb3->Items->Objects[cb3->ItemIndex])) ;
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   sql = "update sys_bsset set bk = '4' where id = " + IntToStr((int)(cb4->Items->Objects[cb4->ItemIndex])) ;
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   sql = "update sys_bsset set bk = '5' where id = " + IntToStr((int)(cb5->Items->Objects[cb5->ItemIndex])) ;
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   sql = "update sys_bsset set bk = '6' where id = " + IntToStr((int)(cb6->Items->Objects[cb6->ItemIndex])) ;
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();


   //�Ƿ������������
   if (cbbear->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'bear'";
   }
   else
   {
       sql = "update sys_bsset set value = 0 where name = 'bear'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //������ʷ��ϸ
   if (cbwosalehistory->Checked ) {
		sql = "update sys_bsset set value = 1,bk = '" + edwosaleday->Text + "' where name = 'wosaleday'";
   }
   else
   {
		sql = "update sys_bsset set value = 0,bk = '" + edwosaleday->Text + "' where name = 'wosaleday'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //��ǰ�ͻ���/Ƿ�������ʾ
   if (cbcheckedview->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'checkedview'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'checkedview'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //�Ƿ������������˻�
   if (cbwosalereturn->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'wosalereturn'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'wosalereturn'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //���������ϴ��ۿ�
   if (chpxlastdiscount->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxlastdiscount'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxlastdiscount'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //���ڳɱ��ۿ�����
   if (cblowcostalter->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'lowcostalter'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'lowcostalter'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //���ڳɱ��ۿ��Ƿ񷢻�
   if (cblowcostenable->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'lowcostenable'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'lowcostenable'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //���������ۿ�����
   if (cblownormalalter->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'lownormalalter'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'lownormalalter'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //���������ۿ��Ƿ񷢻�
   if (cblownormalenable->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'lownormalenable'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'lownormalenable'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //�����޸��ۿ۵�����
   if (cbwsaledisscountchange->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'WsalelDiscountChange'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'WsalelDiscountChange'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //�����˻����
   if (cbpxtuihuocatch->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxtuihuocatch'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxtuihuocatch'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //�ֳ��տ��Ƿ����
   if (chxianchangrecive->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'xianchangrecive'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'xianchangrecive'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //������ϸ��ʾ���Կͻ���ʷ��¼
   if (cbpxallclientdetail->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxallclientdetail'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxallclientdetail'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //����ɾ�������Ƿ�����
   if (cbpxdeleteusepassword->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxdeleteusepassword'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxdeleteusepassword'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //�����鵥�����Ƿ�����
   if (cbpxfindusepassword->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxfindusepassword'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxfindusepassword'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //�����˻������Ƿ�����
   if (cbpxtuihuousepassword->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxtuihuousepassword'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxtuihuousepassword'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //�޿������
   if (cbpxnobkinfosale->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxnobkinfosale'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxnobkinfosale'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //�޿�������˻�
   if (cbpxnobkinfotuihuo->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxnobkinfotuihuo'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxnobkinfotuihuo'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //������ӡ��ע
   /*if (cbpxprintbk->Checked ) {
		sql = "update sys_bsset set value = 1,bk = '" + edpxprintbk->Text + "' where name = 'pxprintbk'";
   }
   else
   {
		sql = "update sys_bsset set value = 0,bk = '" + edpxprintbk->Text + "' where name = 'pxprintbk'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL(); */
   //����Ĭ���ۿ�
   if (cbpxdefaultdiscount->Checked ) {
		sql = "update sys_bsset set value = 1,boundmax = " + eddefaultdiscount->Text + " where name = 'pxdefaultdiscount'";
   }
   else
   {
		sql = "update sys_bsset set value = 0,boundmax = '" + eddefaultdiscount->Text + "' where name = 'pxdefaultdiscount'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //�޿�������˻�
   if (chnokucunpxth->Checked ) {
		sql = "update sys_bsset set value = 1 where name = 'nokucunpxth'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'nokucunpxth'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //�˻��ʼ���ʱ��
   if (edmonth->Text == "" ) {
		edmonth->Text == "0" ;
   }
   sql = "update sys_bsset set bk = " + edmonth->Text + "where name = 'pxbenqituihuolv'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //�����޸ĵ�ͷ�����Ƿ�����
   if (chpxusechange->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxusechange'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxusechange'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //�ظ�¼����ʾ
   if (chwsalesametishi->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'wsalesametishi'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'wsalesametishi'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();

   //�ͻ��ӵ��ۿ�
   if (chpxclientadddot->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxclientadddot'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxclientadddot'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();

   //���Ԥ�������ۿ�
   if (chpxrkyjdiscount->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxrkyjdiscount'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxrkyjdiscount'";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();

   //�����ۿ�
   if (chpxaddcost->Checked ) {
	   sql = "update sys_bsset set value = 1 where name = 'pxaddcost'";
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxaddcost'";
   }

   AnsiString sql2;
 //  �����˻������ظ�¼��

   if (cbpxtuihuo->Checked) {
       sql2 = "update sys_bsset set value = 1 where name = 'wsalesametuihuotishi';";
   }else
   {

      sql2 = "update sys_bsset set value = 0 where name = 'wsalesametuihuotishi';";

   }



   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->SQL->Add(sql2);
   aquery->ExecSQL();



   //������ӡ̧ͷ
   /*sql = "update sys_bsset set bk = '" + edwsprinttitle->Text.Trim() + "' where name = 'wsprinttitle'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //��ϵ��
   sql = "update sys_bsset set bk = '" + edwscontact->Text.Trim() + "' where name = 'wscontact'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //�绰
   sql = "update sys_bsset set bk = '" + edwstel->Text.Trim() + "' where name = 'wstel'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();
   //��ַ
   sql = "update sys_bsset set bk = '" + edwsaddress->Text.Trim() + "' where name = 'wsaddress'";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->ExecSQL();   */
   //���۷�ʽ
   if (RadioGroup1->ItemIndex == 0 ) {
		sql = "update sys_bsset set value = 1 where name = 'pxpriordiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
		sql = "update sys_bsset set value = 0 where name = 'pxmindiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   else
   {
		sql = "update sys_bsset set value = 0 where name = 'pxpriordiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
		sql = "update sys_bsset set value = 1 where name = 'pxmindiscount'";
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->ExecSQL();
   }
   ShowMsg(Handle ,"ҵ�����óɹ���",3);
   Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmsalebsset::FormShow(TObject *Sender)
{
	Readydata();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsalebsset::sbcancelClick(TObject *Sender)
{
   Close();
}
void Tfrmsalebsset::Readydata()
{
  String sql= "select * from sys_bsset",bk;
  int bit;
  aquery->Close();
  aquery->SQL->Clear();
  aquery->SQL->Add(sql);
  aquery->Open();
  while (!aquery->Eof)
  {
	if (aquery->FieldByName("name")->AsAnsiString == "bear")
	{
		cbbear->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "wosaleday" ) {
		cbwosalehistory->Checked = aquery->FieldByName("value")->AsBoolean ;
		edwosaleday->Text = aquery->FieldByName("bk")->AsString ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "checkedview" ) {
		cbcheckedview->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "wosalereturn" ) {
		cbwosalereturn->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "lowcostalter" ) {
		cblowcostalter->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "lowcostenable" ) {
		cblowcostenable->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "lownormalalter" ) {
		cblownormalalter->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "lownormalenable" ) {
    	cblownormalenable->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "pxlastdiscount" ) {
		chpxlastdiscount->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "WsalelDiscountChange" ) {
		cbwsaledisscountchange->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "pxtuihuocatch" ) {
		cbpxtuihuocatch->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "salexiaoshudian" ) {
		bk = aquery->FieldByName("bk")->AsString;
		if (bk.Pos(".") == 0 ) {
			bit = 0;
		}
		else
		{
			bit = bk.Length() - bk.Pos(".");
		}
        etdot->Text = IntToStr(bit);
	}
	if (aquery->FieldByName("name")->AsAnsiString == "xianchangrecive" ) {
		chxianchangrecive->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "pxallclientdetail" ) {
		cbpxallclientdetail->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "pxdeleteusepassword" ) {
		cbpxdeleteusepassword->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "pxfindusepassword" ) {
		cbpxfindusepassword->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "pxtuihuousepassword" ) {
		cbpxtuihuousepassword->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "pxnobkinfosale" ) {
		cbpxnobkinfosale->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "pxnobkinfotuihuo" ) {
		cbpxnobkinfotuihuo->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	if (aquery->FieldByName("name")->AsAnsiString == "pxusechange" ) {
		chpxusechange->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//������ӡ��ע
	/*if (aquery->FieldByName("name")->AsAnsiString == "pxprintbk" ) {
		cbpxprintbk->Checked = aquery->FieldByName("value")->AsBoolean ;
		edpxprintbk->Text = aquery->FieldByName("bk")->AsString ;
	}   */
	//����Ĭ���ۿ�
	if (aquery->FieldByName("name")->AsAnsiString == "pxdefaultdiscount" ) {
		cbpxdefaultdiscount->Checked = aquery->FieldByName("value")->AsBoolean ;
		eddefaultdiscount->Text = aquery->FieldByName("boundmax")->AsString ;
	}
	//�������۷�ʽ
	if (aquery->FieldByName("name")->AsAnsiString == "pxpriordiscount" ) {
		if (aquery->FieldByName("value")->AsBoolean) {
			RadioGroup1->ItemIndex = 0;
		}
		else
		{
        	RadioGroup1->ItemIndex = 1;
		}
	}
	//�޿�������˻�
	if (aquery->FieldByName("name")->AsAnsiString == "nokucunpxth" ) {
		chnokucunpxth->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//�ظ�¼����ʾ
	if (aquery->FieldByName("name")->AsAnsiString == "wsalesametishi" ) {
		chwsalesametishi->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
        if (aquery->FieldByName("name")->AsAnsiString == "wsalesametuihuotishi" ) {
		cbpxtuihuo->Checked = aquery->FieldByName("value")->AsBoolean ;
	}

	//�˻��ʼ���ʱ��
	if (aquery->FieldByName("name")->AsAnsiString == "pxbenqituihuolv")
	{
		edmonth->Text = aquery->FieldByName("bk")->AsAnsiString ;
	}

	//�ͻ� �ӵ��ۿ�
	if (aquery->FieldByName("name")->AsAnsiString == "pxclientadddot" ) {
		chpxclientadddot->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//���Ԥ�������ۿ�
	if (aquery->FieldByName("name")->AsAnsiString == "pxrkyjdiscount" ) {
		chpxrkyjdiscount->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	//�����ۿ�
	if (aquery->FieldByName("name")->AsAnsiString == "pxaddcost")
	{
		chpxaddcost->Checked = aquery->FieldByName("value")->AsBoolean ;
	}
	 aquery->Next();

  }
  //���ȼ���
  sql = "select id,case when name = 'pxlastdiscount' then '�����ϴ��ۿ�' "
		" when name = 'pxdefaultdiscount' then '����Ĭ���ۿ�' when name = 'pxrkyjdiscount' then '���Ԥ�������ۿ�' "
		" when name = 'pxaddcost' then '�����ۿ�' when name = 'pxclientadddot' then '�ͻ��ӵ��ۿ�'  when name ='pxclientdis' then '�ͻ���Ʒ�ۿ�' end as name,bk "
		" from sys_bsset where name in('pxlastdiscount','pxdefaultdiscount','pxrkyjdiscount','pxaddcost','pxclientadddot','pxclientdis') order by bk";
  aquery->Close();
  aquery->SQL->Clear();
  aquery->SQL->Add(sql);
  aquery->Open();
  aquery->First();
  while (!aquery->Eof )
  {
	cb1->AddItem(aquery->FieldByName("name")->AsAnsiString ,(TObject*)aquery->FieldByName("id")->AsInteger );
	cb2->AddItem(aquery->FieldByName("name")->AsAnsiString ,(TObject*)aquery->FieldByName("id")->AsInteger );
	cb3->AddItem(aquery->FieldByName("name")->AsAnsiString ,(TObject*)aquery->FieldByName("id")->AsInteger );
	cb4->AddItem(aquery->FieldByName("name")->AsAnsiString ,(TObject*)aquery->FieldByName("id")->AsInteger );
	cb5->AddItem(aquery->FieldByName("name")->AsAnsiString ,(TObject*)aquery->FieldByName("id")->AsInteger );
        cb6->AddItem(aquery->FieldByName("name")->AsAnsiString ,(TObject*)aquery->FieldByName("id")->AsInteger );
	aquery->Next();
  }

  aquery->First();
  cb1->ItemIndex = cb1->Items->IndexOfObject((TObject*)aquery->FieldByName("id")->AsInteger );
  aquery->Next();
  cb2->ItemIndex = cb2->Items->IndexOfObject((TObject*)aquery->FieldByName("id")->AsInteger );
  aquery->Next();
  cb3->ItemIndex = cb3->Items->IndexOfObject((TObject*)aquery->FieldByName("id")->AsInteger );
  aquery->Next();
  cb4->ItemIndex = cb4->Items->IndexOfObject((TObject*)aquery->FieldByName("id")->AsInteger );
  aquery->Next();
  cb5->ItemIndex = cb5->Items->IndexOfObject((TObject*)aquery->FieldByName("id")->AsInteger );
  aquery->Next();
  cb6->ItemIndex = cb6->Items->IndexOfObject((TObject*)aquery->FieldByName("id")->AsInteger );
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsalebsset::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmsalebsset::eddefaultdiscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
		Key = NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsalebsset::cbpxtuihuocatchClick(TObject *Sender)
{
	if (cbpxtuihuocatch->Checked ) {
		cbwosalereturn->Checked = false;
	}
	else
	{
    	cbwosalereturn->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmsalebsset::etdotExit(TObject *Sender)
{
    if (StrToInt(etdot->Text)>3 ) {
       ShowMsg(Handle ,"С�������2λ��",3);
       etdot->SetFocus();
       etdot->Text = "2";
    }
}
//---------------------------------------------------------------------------

