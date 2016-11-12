//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitclientwanglai.h"
#include "..\bsadmin\UnitSelectClient.h"
#include "Notedetail.h"
#include "global.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "RpBase"
#pragma link "RpCon"
#pragma link "RpConDS"
#pragma link "RpDefine"
#pragma link "RpRave"
#pragma link "RpSystem"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmclientwanglai *frmclientwanglai;
//---------------------------------------------------------------------------
__fastcall Tfrmclientwanglai::Tfrmclientwanglai(TComponent* Owner,int type)
	: TForm(Owner)
{
  	chclient->Caption = "�ͻ�����";
		GroupBox1->Caption = "�ͻ���Ϣ";
		ch1->Caption = "����";
		this->Caption = "�ͻ���������";
		Client = type;
}
void Tfrmclientwanglai::init(LandInfo* li)
{
	userInfo.app = li->app ;
	userInfo.con = li->con ;
	userInfo.userID = li->userID ;
	userInfo.storageID = li->storageID ;
	userInfo.UserName = li->UserName;



         qfclient =li->qfclient;
        qfsupplier =li->qfsupply;

	fcon = li->con;
	stgid = li->storageID;
	query->Connection = li->con ;
	AnsiString sql;
	TADOQuery *aq = new TADOQuery(NULL);
	aq->Connection = fcon  ;

	if (Client == 1) {
		sql = "select * from SYS_BSSET where name = 'xiaoshudian'";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		format = aq->FieldByName("bk")->AsString ;
	}
	else
	{
		sql = "select * from SYS_BSSET where name = 'salexiaoshudian'";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		format = aq->FieldByName("bk")->AsString ;
	}
	sql = "select * from SYS_BSSET where name = 'changeDanHaoDisplay'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	ChangeDisplay  = aq->FieldByName("value")->AsBoolean ;

	sql = "select Name,master from SYS_StorageInfo where ID = " + IntToStr(stgid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	StorageName = aq->FieldByName("name")->AsAnsiString ;
	master = aq->FieldByName("master")->AsBoolean ;

         if (qfclient) {
           	sql = "select ID,Name from cust_customerinfo where Type in (2,3) and stgid = "+IntToStr(stgid)+" and Name <> ''  and customerstate=1 ";
         }else 	sql = "select ID,Name from cust_customerinfo where Type in (2,3)  and Name <> ''  and customerstate=1 ";


	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	cbdanwei->Items->Clear();
	cbdanwei->Text = "";
	while(!aq->Eof)
	{
		cbdanwei->Items->AddObject(aq->FieldByName("name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	delete aq;
	ButtonType1 = false;
	ButtonType2 = false;
	ButtonType3 = false;
	dtpbegin->Date = Now();
	dtpend->Date = Now();
	aqprint->Connection = userInfo.con ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmclientwanglai::editjianshuoKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		GetClientInfor(editjianshuo->Text.Trim());
	}
}
//---------------------------------------------------------------------------
void Tfrmclientwanglai::GetClientInfor(AnsiString KeyWord)
{
	AnsiString sql;
	if (Client == 1) {


		sql = "select ID,Name from cust_customerinfo where Type in (1) and stgid = "+IntToStr(stgid)+" and customerstate=1 and   Name like '%" + KeyWord+"%' and Name <> '' ";
    	TADOQuery *aq = new TADOQuery(NULL);
		aq->Connection = userInfo.con ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbdanwei->Items->Clear();
		cbdanwei->Text = "";
		while(!aq->Eof)
		{
			cbdanwei->Items->AddObject(aq->FieldByName("name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		aq->First();
		cbdanwei->ItemIndex = cbdanwei->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );
		delete aq;
	}else
	{
        if (qfclient) {
         sql = "select ID,Name from cust_customerinfo where Type in (2,3) and stgid = "+IntToStr(stgid)+" and customerstate=1 and Name like '%" + KeyWord+"%' and Name <> '' ";
        }else sql = "select ID,Name from cust_customerinfo where Type in (2,3) and customerstate=1 and Name like '%" + KeyWord+"%' and Name <> '' ";

    	TADOQuery *aq = new TADOQuery(NULL);
		aq->Connection = userInfo.con ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbdanwei->Items->Clear();
		cbdanwei->Text = "";
		while(!aq->Eof)
		{
			cbdanwei->Items->AddObject(aq->FieldByName("name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		aq->First();
		cbdanwei->ItemIndex = cbdanwei->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );
		delete aq;
	}
}
void Tfrmclientwanglai::GetClientDetail(int vendor)
{
   	AnsiString sql,sql1 ;
	if (Client == 1) {//��Ӧ��
		sql = "select sum(Checked) as checked,sum(Nochecked) as nochecked from BS_StorageNoteHeader where supplierid = " + IntToStr(vendor);
	}else
	{
		sql = "select sum(Checked) as checked,sum(Nochecked) as nochecked from BS_WsaleNoteHeader where VendorID in(select ID from GetChild("+IntToStr(vendor)+"))" ;
	}
	sql1 = "select cust_customerinfo.*,CUST_CustomerStartMoney.Balance + CUST_CustomerStartMoney.totalyue as totalyue from cust_customerinfo left join CUST_CustomerStartMoney on CUST_CustomerStartMoney.CustomerID = cust_customerinfo.id where cust_customerinfo.ID = "+ IntToStr(vendor);
	TADOQuery *aq = new TADOQuery(NULL);
	aq->Connection = fcon ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	edityijie->Text =  "��" + FormatFloat(format,aq->FieldByName("checked")->AsFloat);
	editweijie->Text = "��" + FormatFloat(format,aq->FieldByName("nochecked")->AsFloat);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql1);
	aq->Open();
	edityue->Text =  "��" + FormatFloat(format,aq->FieldByName("totalyue")->AsFloat);

	editcontact->Text = aq->FieldByName("contact")->AsAnsiString ;
	editzhanhao->Text = aq->FieldByName("bankaccount")->AsAnsiString ;
	edittel->Text = aq->FieldByName("telephone")->AsAnsiString ;
	editfax->Text = aq->FieldByName("fax")->AsAnsiString ;
	editaddress->Text = aq->FieldByName("address")->AsAnsiString ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientwanglai::cbdanweiSelect(TObject *Sender)
{
	try
	{
		GetClientDetail((int)cbdanwei->Items->Objects[cbdanwei->ItemIndex]);
	}
	catch(...)
	{
		ShowMsg(this->Handle,"��������ȷ�ĵ�λ���ƣ�",3);
	}
}
//---------------------------------------------------------------------------

void  Tfrmclientwanglai::ancode()
{
	AnsiString Danhao,sqlwhere;
	ButtonType2 = true;
	ButtonType1 = false ;
	if (Client== 1)
	{
		if (ChangeDisplay) {
			sql = "select grouping(A.stgNtCodeStr) as d ,isnull(name,'�ܺϼ�') cusname, case when grouping(A.stgNtCodeStr) = 1 then '�ϼ�' else '��ϸ' end as stype, A.stgNtCodeStr  as CodeStr, "  ;
		} else
		{
			sql = "select grouping(A.stgntcode) as d,isnull(name,'�ܺϼ�') cusname, case when grouping(A.stgntcode) = 1 then '�ϼ�' else '��ϸ' end as stype, cast(A.stgntcode as nvarchar(15))  as CodeStr,  "  ;
		}
		sql = sql +" sum(TotalAmount) as TotalAmount,sum(totalfixedprice) as totalfixedprice,sum(TotalDiscountedPrice) as TotalDiscountedPrice, "
			 " sum(nochecked) as nochecked,sum(checked) as checked,sum(addcosts) as addcosts,A.Remarks,A.State,A.fapiao "
			 " from BS_StorageNoteHeader A join CUST_CustomerInfo B ON A.Supplierid = B.ID ";
		sqlwhere = " where A.stgid = " + IntToStr(stgid);
		if (chstart->Checked) {
			sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpbegin->Date) + "',A.Hdtime) >= 0 ";
		}
		if (chend->Checked ) {
			sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpend->Date) + "',A.Hdtime) <= 0 ";
		}
		if (chclient->Checked && cbdanwei->Text != "") {
			try {
				sqlwhere = sqlwhere + " and A.supplierid = " + IntToStr((int)cbdanwei->Items->Objects[cbdanwei->ItemIndex]);
			} catch (...) {
				ShowMsg(this->Handle,"��ѡ����ȷ�ĵ�λ���ƣ�",3);
				return;
			}
		}
		if (chstate->Checked ) {
			sqlwhere = sqlwhere + " and A.State = " + IntToStr(cbstate->ItemIndex);
		}
		if (chfapiao->Checked ) {
			sqlwhere = sqlwhere + " and A.fapiao = " + IntToStr(cbfapiao->ItemIndex);
		}
		sql = sql +  sqlwhere;
		if (ChangeDisplay) {
			sql = sql +	 " group by Name,A.stgNtCodeStr,A.Remarks,A.State,A.fapiao with ROLLUP";
		}else
		{
		   sql = sql +	 " group by Name,A.stgntcode,A.Remarks,A.State,A.fapiao with ROLLUP";
		}
	 }
	 else                    //wsaleNtCodeStr
	 {
		if (ChangeDisplay) {
			Danhao = "wsaleNtCodeStr";
		} else
		{
			Danhao = "wsaleNtCode";
		}
		sql = "select  grouping(A."+Danhao+") as d, isnull(dbo.uf_bs_getclientname(A.vendorID),'�ܺϼ�') cusname, case when grouping(A."+Danhao+") = 1 then '�ϼ�' else '��ϸ' end as stype, cast (A."+Danhao+" as nvarchar(15))  as CodeStr,";
		sql = sql +  " sum(totalAmount) as totalAmount,sum(fixedprice) as totalfixedprice,sum(DiscountedPrice) as TotalDiscountedPrice, "
			 //" sum(totalbackdot) as '����',sum(totalyingshou) as 'Ӧ��', "
			 " sum(nochecked) as nochecked,sum(checked) as checked,sum(addcosts) as addcosts,A.Remarks,A.State,A.fapiao "
			 " from BS_WsaleNoteHeader A join CUST_CustomerInfo B ON A.vendorid = B.ID ";
	      //	sqlwhere = " where A.stgid = " + IntToStr(stgid);
		if (chstart->Checked) {
			sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpbegin->Date) + "',A.Hdtime) >= 0 ";
		}
		if (chend->Checked ) {
			sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpend->Date) + "',A.Hdtime) <= 0 ";
		}
		if (chclient->Checked && cbdanwei->Text != "") {
			try {
				sqlwhere = sqlwhere + " and A.vendorID in(select * from dbo.GetSameSupplierIDClient("+IntToStr((int)cbdanwei->Items->Objects[cbdanwei->ItemIndex])+"))";
			} catch (...) {
				ShowMsg(this->Handle,"��ѡ����ȷ�ĵ�λ���ƣ�",3);
				return;
			}
		}
		if (chstate->Checked ) {
			sqlwhere = sqlwhere + " and A.State = " + IntToStr(cbstate->ItemIndex);
		}
		if (chfapiao->Checked ) {
			sqlwhere = sqlwhere + " and A.fapiao = " + IntToStr(cbfapiao->ItemIndex);
		}
		sql = sql + sqlwhere + " group by Name,A.vendorID,A."+Danhao+",A.Remarks,A.State,A.fapiao with ROLLUP ";
	 }
	//TColumn *column;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();

	((TFloatField *)query->FieldByName("totalfixedprice"))->DisplayFormat =  "��" + format ;
	((TFloatField *)query->FieldByName("TotalDiscountedPrice"))->DisplayFormat =  "��" + format ;
	((TFloatField *)query->FieldByName("checked"))->DisplayFormat =  "��" + format ;
	((TFloatField *)query->FieldByName("nochecked"))->DisplayFormat =  "��" + format ;
	((TFloatField *)query->FieldByName("addcosts"))->DisplayFormat =  "��" + format ;

	/*TColumn *Col;
	dg->Columns->Clear();
	query->DisableControls();
	for (int i =1; i < query->Fields->Count ; i++) { //ȥ��ID

		Col =  dg->Columns->Add();
		Col->FieldName  = query->Fields->Fields[i]->FieldName  ;
		Col->Title->Alignment = taCenter ;

		if (Col->FieldName == "ͳ������") {
		  Col->Width = 60;
		  Col->Alignment = taLeftJustify ;
		}else
		{
		  Col->Width = 84;
		}
		query->Next();
	}
	if (Client == 1 ) { //��Ӧ��
		((TFloatField *)query->FieldByName("����"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("ʵ��"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("�ѽ�"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("δ��"))->DisplayFormat =  "��" + format ;

	} else
	{
		((TFloatField *)query->FieldByName("����"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("ʵ��"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("����"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("Ӧ��"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("�ѽ�"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("δ��"))->DisplayFormat =  "��" + format ;
	} */
	query->EnableControls();
   //	ButtonType2 = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientwanglai::SpeedButton2Click(TObject *Sender)
{
 	ButtonType3 = true;
}
//---------------------------------------------------------------------------

void Tfrmclientwanglai::Print(int type,int print)
{
	if (query->IsEmpty()  ) {
		return;
	}
	AnsiString sqlprint;
	sqlprint = StringReplace(sql,"���","xuhao",TReplaceFlags()<<rfReplaceAll);
	sqlprint = StringReplace(sqlprint,"����","danhao",TReplaceFlags()<<rfReplaceAll);
	sqlprint = StringReplace(sqlprint,"����","rkqi",TReplaceFlags()<<rfReplaceAll);

	sqlprint = StringReplace(sqlprint,"����","totalamount",TReplaceFlags()<<rfReplaceAll);
	sqlprint = StringReplace(sqlprint,"����","mayang",TReplaceFlags()<<rfReplaceAll);
	sqlprint = StringReplace(sqlprint,"ʵ��","siyang",TReplaceFlags()<<rfReplaceAll);
	sqlprint = StringReplace(sqlprint,"δ��","weijie",TReplaceFlags()<<rfReplaceAll);
	sqlprint = StringReplace(sqlprint,"�ѽ�","yijie",TReplaceFlags()<<rfReplaceAll);
	sqlprint = StringReplace(sqlprint,"���ӷ���","addcost",TReplaceFlags()<<rfReplaceAll);
	//sqlprint = StringReplace(sqlprint,"����","backdot",TReplaceFlags()<<rfReplaceAll);
	sqlprint = StringReplace(sqlprint,"��ע","bk",TReplaceFlags()<<rfReplaceAll);
	sqlprint = StringReplace(sqlprint,"����״̬","cwstate",TReplaceFlags()<<rfReplaceAll);
	sqlprint = StringReplace(sqlprint,"��Ʊ","fapiao",TReplaceFlags()<<rfReplaceAll);
	//sqlprint = StringReplace(sqlprint,"Ӧ��","yingshou",TReplaceFlags()<<rfReplaceAll);

	if (Client == 1) {
		sqlprint = StringReplace(sqlprint,"��Ӧ������","name",TReplaceFlags()<<rfReplaceAll);
	}else
	{
		sqlprint = StringReplace(sqlprint,"�ͻ�����","name",TReplaceFlags()<<rfReplaceAll);
		//sqlprint = StringReplace(sqlprint,"ͳ������","yewutype",TReplaceFlags()<<rfReplaceAll);
		//sqlprint = StringReplace(sqlprint,"�ͻ�","Clientname",TReplaceFlags()<<rfReplaceAll);
		//sqlprint = StringReplace(sqlprint,"��Ӧ��","Clientname",TReplaceFlags()<<rfReplaceAll);

	}
	aqprint->Close();
	aqprint->SQL->Clear();
	aqprint->SQL->Add(sqlprint);
	aqprint->Open();

       //	RvSystem1->SystemSetups >>ssAllowSetup;
       //	RvSystem1->SystemSetups >>ssAllowDestPreview;
      //	RvSystem1->SystemSetups >>ssAllowDestPrinter;
	//RvSystem1->SystemSetups >>ssAllowPrinterSetup;
       //	RvSystem1->SystemSetups >>ssAllowDestFile;
	if (1==print) {
       RvSystem1->DefaultDest = rdPrinter ;
	}else
	{
		RvSystem1->DefaultDest  = rdPreview ;
	}
	RvSystem1->SystemSetups<<ssAllowDestPreview;
	if (type == 1) {      //�ͻ���
	  if (Client == 1) {        //��Ӧ��
		  duizhang->ProjectFile = ExtractFilePath(Application->ExeName) + "DuizhangSupplier.rav";
	  }else
	  {
		  duizhang->ProjectFile = ExtractFilePath(Application->ExeName) + "Duizhang.rav";
	  }
	  duizhang->SetParam("title",StorageName + "���ʵ�");
	  duizhang->SetParam("danwei",cbdanwei->Text);
	  duizhang->SetParam("contact",editcontact->Text);
	  duizhang->SetParam("tel",edittel->Text);
	  duizhang->SetParam("yijie",edityijie->Text);//yijie
	  duizhang->SetParam("weijie",editweijie->Text);
	  duizhang->SetParam("begin",DateToStr(dtpbegin->Date));
	  duizhang->SetParam("end",DateToStr(dtpend->Date));
	}
	if (type == 2) {
	   if (Client == 1) {

	   }else
	   {


	   }
	   duizhang->ProjectFile = ExtractFilePath(Application->ExeName) + "DuizhangAnDan.rav";
	   duizhang->SetParam("title",StorageName + "���ʵ�");
  	   duizhang->SetParam("begin",DateToStr(dtpbegin->Date));
	   duizhang->SetParam("end",DateToStr(dtpend->Date ));
	}

	duizhang->Open();
	duizhang->Execute();
	duizhang->Close();
}

//---------------------------------------------------------------------------




void __fastcall Tfrmclientwanglai::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientwanglai::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientwanglai::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {    //��С��
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 81 ) {    //�˳�
		BtnExit->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==90) {   //�ָ�����
		WindowState = wsNormal  ;
	}
	if (Key == VK_F7 ) {    //Ԥ��
		BtnPrintPreview->Click();
	}
	if (Key == VK_F8 ) {    //��ӡ
		BtnPrint->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 70 ) {    //��ѯ
		BtnView->Click();
	}
	if (Key == VK_F3 ) {    //����
		BtnProperties->Click();
	}
	if (Key == VK_F4 ) {    //��Ʊ
		BtnNextRecord->Click();
	}
	if (Key == VK_F6 ) {    //����
		BtnExport->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientwanglai::BtnPrintClick(TObject *Sender)
{
	if (ButtonType1) {
		Print(1,1);
	}
	if (ButtonType2) {
		Print(2,1);
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientwanglai::BtnPrintPreviewClick(TObject *Sender)
{
	if (ButtonType1) {
		Print(1,0);
	}
	if (ButtonType2) {
		Print(2,0);
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientwanglai::BtnViewClick(TObject *Sender)
{
	//ancode();
	ButtonType1 = true;
	ButtonType2 = false;
	AnsiString sqlwhere,sqlwhere1;
	AnsiString sql1;
	if (Client== 1) { //��Ӧ��
		if (ChangeDisplay) {
			sql= " select  distinct A.ID,cast (RANK() OVER(order by A.ID asc) as nvarchar(10)) as '���',B.Name as '��Ӧ������',A.StgNtCode as Code,A.StgNtCodeStr as '����',CONVERT(varchar(12),A.Hdtime,111) as  '����'," ;
		}else
		{
			sql= " select distinct A.ID,cast (RANK() OVER(order by A.ID asc) as nvarchar(10)) as '���',B.Name as '��Ӧ������', A.StgNtCode as Code,cast(A.StgNtCode as nvarchar(15))as '����',CONVERT(varchar(12),A.Hdtime,111)as '����'," ;
		}
		sql = sql + " A.TotalAmount as '����',A.TotalFixedPrice as '����',A.TotalDiscountedPrice as 'ʵ��',A.AddCosts as '���ӷ���',A.AddCosts + A.TotalDiscountedPrice as totalyingfu, A.checked  as '�ѽ�',A.nochecked as 'δ��',A.duifangmoney as '�Է�����',A.hongcong as '���', "
				" A.remarks as '��ע',case A.cwstate when 0 then 'δ����' else '��'  end  as '����״̬', "
				" case when C.state = 0 and C.thistime > 0 then 'δ���' when abs(A.Checked) >= 0.01 and abs(A.NoChecked) < 0.01 then '�ѽ��' when abs(A.Checked) >= 0.01 and abs(A.NoChecked) >= 0.01 then '�ѽᲿ��' when  abs(A.Checked) < 0.01 and abs(A.NoChecked) >= 0.01 then 'δ���' end as '���״̬', "
				" case A.fapiao when 0 then 'δ��' else '��' end as '��Ʊ',A.fapiaotext, "
				" case when dbo.uf_bs_getjiekuancode(A.id,1) is null and A.Checked > 0 then '�ֳ����' else dbo.uf_bs_getjiekuancode(A.id,1) end as '����' from BS_StorageNoteHeader  A left join CUST_CustomerInfo B on A.supplierid = B.id "
				" left join (select FN_CUSEndMoneyDtails.thistime,FN_CUSEndMoneyDocuments.state,stgntcode from FN_CUSEndMoneyDtails join FN_CUSEndMoneyDocuments "
				" on FN_CUSEndMoneyDtails.EndMoneyDocumentID = FN_CUSEndMoneyDocuments.MoneyCode  where FN_CUSEndMoneyDtails.type = 2 and FN_CUSEndMoneyDtails.thistime <> 0 and FN_CUSEndMoneyDocuments.state = 0) C ON C.stgntcode = A.StgNtCode ";

		if (master) {
			sqlwhere = " where 1=1 " ;
		}
		else
		{
               //	sqlwhere = " where A.stgid = " + IntToStr(stgid) ;
		}

		if (chstart->Checked) {
			sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpbegin->Date) + "',A.Hdtime) >= 0 ";
		}
		if (chend->Checked ) {
			sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpend->Date) + "',A.Hdtime) <= 0 ";
		}
		if (chclient->Checked && cbdanwei->Text != "") {
			try {
				sqlwhere = sqlwhere + " and A.supplierid = " + IntToStr((int)cbdanwei->Items->Objects[cbdanwei->ItemIndex]);
			} catch (...) {
				ShowMsg(this->Handle,"��ѡ����ȷ�ĵ�λ���ƣ�",3);
				return;
			}
		}
		if (chstate->Checked ) {
			sqlwhere = sqlwhere + " and A.cwstate = " + IntToStr(cbstate->ItemIndex);
		}
		if (chfapiao->Checked ) {
			sqlwhere = sqlwhere + " and A.fapiao = " + IntToStr(cbfapiao->ItemIndex);
		}
		if (chshiyang->Checked ) {
			if (edmin->Text != "") {
				try {
					float dd = StrToFloat(edmin->Text);
				} catch (...) {

                                          ShowMsg(Handle ,"��������ȷ��ʵ��",3);
					return;
				}

				sqlwhere = sqlwhere + " and A.TotalDiscountedPrice >= " + edmin->Text ;
			}
			if (edmax->Text != "") {
				try {
					float dd = StrToFloat(edmax->Text);
				} catch (...) {
                                        ShowMsg(Handle ,"��������ȷ��ʵ��",3);
					return;
				}
				sqlwhere = sqlwhere + " and A.TotalDiscountedPrice <= " + edmax->Text ;
			}
		}
		if (ch1->Checked && !ch3->Checked  ) {
			sqlwhere = sqlwhere + " and A.StgNtCodeInt > 0 ";
		}
		if (ch1->Checked && ch3->Checked ) {

		}
		if (!ch1->Checked && ch3->Checked ) {
			sqlwhere = sqlwhere + " and A.TStgNtCodeInt > 0 ";
		}
		if (chjiekuan->Checked ) {
			switch (cbjiekuanstate->ItemIndex ) {
				case 0:   //δ���
					sqlwhere = sqlwhere + " and abs(A.NoChecked) > 0.01 ";
					break;
				case 1:  //�ѽӲ���
					sqlwhere = sqlwhere + " and abs(A.Checked) > 0.01 and abs(A.NoChecked) > 0.01 ";
					break;
				case 2:  //δ���
					sqlwhere = sqlwhere + " and D.state = 0 and D.type = 1 and abs(C.thistime) > 0.01 ";
					break;
				case 3:
					sqlwhere = sqlwhere + " and abs(A.Checked) > 0.01 and abs(A.NoChecked) <= 0.01 ";
					break;
            default:
                ;
			}
		}
		if (chfapiaohao->Checked ) {
			sqlwhere = sqlwhere + " and A.fapiaotext like '%" + edfapiaohao->Text.Trim() + "%'";
		}
		sql = sql + sqlwhere;

		sql1 =  "  select sum(A.TotalAmount) as TotalAmount,sum(A.TotalFixedPrice) as TotalFixedPrice,sum(A.TotalDiscountedPrice) as DiscountedPrice,sum(A.checked) as checked,sum(A.AddCosts) as AddCosts,sum(A.AddCosts + A.TotalDiscountedPrice) as totalyingfu,sum(A.nochecked) as " ;
		sql1 = sql1 + " nochecked from BS_StorageNoteHeader A left join (select * from FN_CUSEndMoneyDtails where type = 1) C ON C.stgntcode = A.StgNtCode "
				" left join FN_CUSEndMoneyDocuments D ON D.MoneyCode = C.EndMoneyDocumentID ";
		sql1 = sql1 + sqlwhere;

	}else
	{
		if (ChangeDisplay) {
			sql= " select distinct A.ID,cast (RANK() OVER(order by A.ID asc) as nvarchar(10)) as '���',dbo.uf_bs_getclientname(A.vendorID) as '�ͻ�����',A.wsaleNtCode as Code,A.WsaleNtCodeStr as '����',CONVERT(varchar(12),A.Hdtime,111) as  '����'," ;
		}else
		{
			sql= " select distinct A.ID,cast (RANK() OVER(order by A.ID asc) as nvarchar(10)) as '���',dbo.uf_bs_getclientname(A.vendorID) as '�ͻ�����',A.wsaleNtCode as Code,cast(A.wsaleNtCode as nvarchar(15)) as '����',CONVERT(varchar(12),A.Hdtime,111) as '����'," ;
		}
		//sql = sql +  "  TotalAmount as '����',fixedPrice as '����',DiscountedPrice as 'ʵ��',checked  as '�ѽ�',nochecked as 'δ��', "
		//	" Totalbackdot as '����',Totalyingshou as 'Ӧ��',remarks as '��ע',case A.cwstate when 0 then 'δ����' when 1 then '�Ѷ���' else '�����' end as '״̬',case A.fapiao when 0 then 'δ��' else '�ѿ�' end as '��Ʊ' from BS_WsaleNoteHeader  A ";

		sql = sql + " A.TotalAmount as '����',A.FixedPrice as '����',A.DiscountedPrice as 'ʵ��',A.AddCosts as '���ӷ���',A.AddCosts + A.DiscountedPrice as totalyingfu,A.checked  as '�ѽ�',A.nochecked as 'δ��',A.duifangmoney as '�Է�����',A.hongcong as '���', "
				" A.remarks as '��ע',case A.cwstate when 0 then 'δ����' else '��'  end  as '����״̬', "
				" case when C.state = 0 and C.thistime > 0 then 'δ���' when abs(A.Checked) >= 0.01 and abs(A.NoChecked) < 0.01 then '�ѽ��' when abs(A.Checked) >= 0.01 and abs(A.NoChecked) >= 0.01 then '�ѽᲿ��' when  abs(A.Checked) < 0.01 and abs(A.NoChecked) >= 0.01 then 'δ���' end as '���״̬', "
				" case A.fapiao when 0 then 'δ��' else '��' end as '��Ʊ',A.fapiaotext, "
				" case when dbo.uf_bs_getjiekuancode(A.id,2) is null and A.Checked > 0 then '�ֳ����' else dbo.uf_bs_getjiekuancode(A.id,2) end as '����' from BS_WsaleNoteHeader A "
				" left join (select FN_CUSEndMoneyDtails.thistime,FN_CUSEndMoneyDocuments.state,stgntcode from FN_CUSEndMoneyDtails join FN_CUSEndMoneyDocuments "
				" on FN_CUSEndMoneyDtails.EndMoneyDocumentID = FN_CUSEndMoneyDocuments.MoneyCode  where FN_CUSEndMoneyDtails.type = 2 and FN_CUSEndMoneyDtails.thistime <> 0 and FN_CUSEndMoneyDocuments.state = 0) C ON C.stgntcode = A.WsaleNtCode ";

		if (master) {
			sqlwhere = " where A.WsaleNtCode <> 0 ";//and A.stgid=" + IntToStr(stgid) ;
		}
		else
		{
			sqlwhere = " where A.WsaleNtCode <> 0 and A.stgid = " + IntToStr(stgid) ;
		}

		if (chstart->Checked) {
			sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpbegin->Date) + "',A.Hdtime) >= 0 ";
		}
		if (chend->Checked ) {
			sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpend->Date) + "',A.Hdtime) <= 0 ";
		}
		if (chclient->Checked && cbdanwei->Text != "") {
			try {
				sqlwhere = sqlwhere + " and A.vendorID in(select * from dbo.GetSameSupplierIDClient("+IntToStr((int)cbdanwei->Items->Objects[cbdanwei->ItemIndex])+"))";
			} catch (...) {
				ShowMsg(this->Handle,"��ѡ����ȷ�ĵ�λ���ƣ�",3);
				return;
			}
		}
		if (chstate->Checked ) {
			sqlwhere = sqlwhere + " and A.cwstate = " + IntToStr(cbstate->ItemIndex);
		}
		if (chfapiao->Checked ) {
			sqlwhere = sqlwhere + " and A.fapiao = " + IntToStr(cbfapiao->ItemIndex);
		}
		if (chshiyang->Checked ) {
			if (edmin->Text != "") {
				try {
					float dd = StrToFloat(edmin->Text);
				} catch (...) {
					ShowMsg(Handle ,"��������ȷ��ʵ��",3);
					return;
				}
				sqlwhere = sqlwhere + " and A.FixedPrice >= " + edmin->Text ;
			}
			if (edmax->Text != "") {
				try {
					float dd = StrToFloat(edmax->Text);
				} catch (...) {
				ShowMsg(Handle ,"��������ȷ��ʵ��",3);
					return;
				}
				sqlwhere = sqlwhere + " and A.FixedPrice <= " + edmax->Text ;
			}
		}
		if (ch1->Checked && !ch3->Checked  ) {
			sqlwhere = sqlwhere + " and A.WsaleNtCodeInt > 0 ";
		}
		if (ch1->Checked && ch3->Checked ) {

		}
		if (!ch1->Checked && ch3->Checked ) {
			sqlwhere = sqlwhere + " and A.TWsaleNtCodeInt > 0 ";
		}
		if (ch2->Checked ) {
        	sqlwhere = sqlwhere + " and A.state = 2 ";
		}
		if (chjiekuan->Checked ) {
			switch (cbjiekuanstate->ItemIndex ) {
				case 0:   //δ���
					sqlwhere = sqlwhere + " and abs(A.NoChecked) > 0.01 ";
					break;
				case 1:  //�ѽӲ���
					sqlwhere = sqlwhere + " and abs(A.Checked) > 0.01 and abs(A.NoChecked) > 0.01 ";
					break;
				case 2:  //δ���
					sqlwhere = sqlwhere + " and D.state = 0 and D.type = 2 and abs(C.thistime) > 0 ";
					break;
				case 3:
					sqlwhere = sqlwhere + " and abs(A.Checked) > 0.01 and abs(A.NoChecked) <= 0.01 ";
					break;
			default:
                ;
			}
		}
		if (chfapiaohao->Checked ) {
			sqlwhere = sqlwhere + " and A.fapiaotext like '%" + edfapiaohao->Text.Trim() + "%'";

		}

	


		sql = sql + sqlwhere;


		sql1 = " select sum(A.TotalAmount) as TotalAmount,sum(A.fixedprice) as TotalFixedPrice,sum(A.DiscountedPrice) as DiscountedPrice,sum(A.AddCosts) as AddCosts,sum(A.AddCosts + A.DiscountedPrice) as totalyingfu,sum(A.checked) as checked,sum(A.nochecked) as " ;
		sql1 = sql1 + " nochecked from BS_WsaleNoteHeader A left join (select * from FN_CUSEndMoneyDtails where type = 2) C ON C.stgntcode = A.WsaleNtCode "
				" left join FN_CUSEndMoneyDocuments D ON D.MoneyCode = C.EndMoneyDocumentID " ;
		sql1 = sql1 +	sqlwhere;
	}
	TColumn *column;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();


	((TFloatField *)query->FieldByName("����"))->DisplayFormat = "###,###,##" + format ;
	((TFloatField *)query->FieldByName("ʵ��"))->DisplayFormat = "###,###,##" + format ;
	((TFloatField *)query->FieldByName("�ѽ�"))->DisplayFormat = "###,###,##" + format ;
	((TFloatField *)query->FieldByName("δ��"))->DisplayFormat = "###,###,##" + format ;
	((TFloatField *)query->FieldByName("���ӷ���"))->DisplayFormat = "###,###,##" + format ;
	((TFloatField *)query->FieldByName("totalyingfu"))->DisplayFormat = "###,###,##" + format ;
	((TFloatField *)query->FieldByName("����"))->DisplayFormat = "###,###,##0" ;

	query->EnableControls();
}

//---------------------------------------------------------------------------

void __fastcall Tfrmclientwanglai::N1Click(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
	for (int i = 1; i <= dg->DataSource->DataSet->RecordCount; i++) {
		dg->DataSource->DataSet->RecNo = i;
		dg->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientwanglai::N2Click(TObject *Sender)
{
	N2->Checked = true;
	N3->Checked = false;
	BtnNextRecord->Caption = "���ݷ�Ʊ[F4]";
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientwanglai::N3Click(TObject *Sender)
{
	N2->Checked = false;
	N3->Checked = true;
	BtnNextRecord->Caption = "ȡ�����ݷ�Ʊ[F4]";
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientwanglai::N4Click(TObject *Sender)
{
	N4->Checked = true;
	N5->Checked = false;
	BtnProperties->Caption = "����[F3]";
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientwanglai::N5Click(TObject *Sender)
{
	N4->Checked = false;
	N5->Checked = true;
	BtnProperties->Caption = "ȡ������[F3]";
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientwanglai::BtnPropertiesClick(TObject *Sender)
{
	if (query->IsEmpty() ) {
        return;
	}
	AnsiString ids,sql;
	if (dg->SelectedRows->Count == 0)
	{
		ids = ids + query->FieldByName("ID")->AsString;
	}

	else if (dg->SelectedRows->Count > 0)
	{
		query->Bookmark = dg->SelectedRows->Items[0];
		ids = query->FieldByName("ID")->AsString;
		for (int i=1; i < dg->SelectedRows->Count; i++)
		{
			query->Bookmark = dg->SelectedRows->Items[i];
			ids = ids + "," + query->FieldByName("ID")->AsString;
		}
	}
	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	if (BtnProperties->Caption == "����[F3]") {
		if (Client == 1) {
			sql = "update BS_StorageNoteHeader set cwstate = 1 where id in(" + ids + ")";
		}
		else
		{
			sql = "update BS_WsaleNoteHeader set cwstate = 1 where id in(" + ids + ")";
		}
	}
	if (BtnProperties->Caption == "ȡ������[F3]") {
		if (Client == 1) {
			sql = "update BS_StorageNoteHeader set cwstate = 0 where id in(" + ids + ")";
		}
		else
		{
			sql = "update BS_WsaleNoteHeader set cwstate = 0 where id in(" + ids + ")";
		}
	}

	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
	TLocateOptions   Opts;
	Opts.Clear();
	Opts   <<   loPartialKey;
	String   str   = query->FieldByName("ID")->AsString;

	query->Active = false;
	query->Active = true;
	if (Client == 1 ) { //��Ӧ��
		((TFloatField *)query->FieldByName("����"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("ʵ��"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("�ѽ�"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("δ��"))->DisplayFormat =  "��" + format ;

	} else
	{
		((TFloatField *)query->FieldByName("����"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("ʵ��"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("�ѽ�"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("δ��"))->DisplayFormat =  "��" + format ;
	}
	query->Locate("ID",str,Opts);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientwanglai::BtnNextRecordClick(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
	AnsiString ids,sql;
	if (dg->SelectedRows->Count == 0)
	{
		ids = ids + query->FieldByName("ID")->AsString;
	}
	else if (dg->SelectedRows->Count > 0)
	{
		query->Bookmark = dg->SelectedRows->Items[0];
		ids = query->FieldByName("ID")->AsString;
		for (int i=1; i < dg->SelectedRows->Count; i++)
		{
			query->Bookmark = dg->SelectedRows->Items[i];
			ids = ids + "," + query->FieldByName("ID")->AsString;
		}
	}
	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = fcon;
	if (BtnNextRecord->Caption == "���ݷ�Ʊ[F4]") {
		if (Client == 1) {
			sql = "update BS_StorageNoteHeader set fapiao = 1 where id in(" + ids + ")";
		}
		else
		{
			sql = "update BS_WsaleNoteHeader set fapiao = 1 where id in(" + ids + ")";
		}
	}
	else{
		if (Client == 1) {
			sql = "update BS_StorageNoteHeader set fapiao = 0 where id in(" + ids + ")";
		}
		else
		{
			sql = "update BS_WsaleNoteHeader set fapiao = 0 where id in(" + ids + ")";
		}
	}

	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
	TLocateOptions   Opts;
	Opts.Clear();
	Opts   <<   loPartialKey;
	String   str   = query->FieldByName("ID")->AsString;

	query->Active = false;
	query->Active = true;
	if (Client == 1 ) { //��Ӧ��
		((TFloatField *)query->FieldByName("����"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("ʵ��"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("�ѽ�"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("δ��"))->DisplayFormat =  "��" + format ;

	} else
	{
		((TFloatField *)query->FieldByName("����"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("ʵ��"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("�ѽ�"))->DisplayFormat =  "��" + format ;
		((TFloatField *)query->FieldByName("δ��"))->DisplayFormat =  "��" + format ;
	}
	query->Locate("ID",str,Opts);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientwanglai::BtnExportClick(TObject *Sender)
{
	DbgridToExcel(dg);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//Excel��������
bool Tfrmclientwanglai::DbgridToExcel(TDBGridEh* dg)
{
	if (dg->DataSource ->DataSet->IsEmpty() ) {
        return false;
	}
	AnsiString temptext,path;

	savedlg->FileName = this->Caption;
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = ExtractFilePath(savedlg->FileName .c_str()  );
		Name = ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".csv";
		path =  DBPath;
	}
	else
	{
		return false;
	}
	int  iFileHandle;
	int   iFileLength;
	if(FileExists(path))
	   if (DeleteFileA(path))
			iFileHandle = FileCreate(path.c_str());
	   else
			return false;
	else
		iFileHandle = FileCreate(path.c_str());

	int t1= 0;
	for(int q=0;q<dg->Columns ->Count ;++q)
	{
		if (dg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = temptext + dg->Columns ->Items [q]->FieldName + ",";
		}
	}
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	dg->DataSource ->DataSet->DisableControls();
	dg->DataSource ->DataSet ->First();
	while(!dg->DataSource ->DataSet->Eof)
	{
		temptext = "\n";
		for(int j=1;j<dg->Columns ->Count+1  ;j++)
		{
			if (dg->Columns->Items[j-1]->Visible == true) {
				if (dg->Columns ->Items [j-1]->FieldName == "����") {
					if (dg->DataSource ->DataSet ->FieldByName(dg->Columns ->Items [j-1]->FieldName )->AsAnsiString != "") {
						temptext = temptext + "'" + dg->DataSource ->DataSet ->FieldByName(dg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
					}
					else
					{
                    	temptext = temptext + dg->DataSource ->DataSet ->FieldByName(dg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
					}
				}
				else
				{
					temptext = temptext + dg->DataSource ->DataSet ->FieldByName(dg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
			}
		}
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dg->DataSource ->DataSet ->Next() ;
	}
	dg->DataSource ->DataSet->EnableControls();

	FileClose(iFileHandle);
        ShowMsg(Handle ,"������ϣ�",3);
	return false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientwanglai::dgMouseLeave(TObject *Sender)
{
	if (!query->IsEmpty()  && query->State == dsEdit ) {
		try {
			query->Post();
		} catch (...) {
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientwanglai::cbstateChange(TObject *Sender)
{
	if (cbstate->Text != "") {
		chstate->Checked = true;
	}
	else
	{
    	chstate->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientwanglai::cbjiekuanstateChange(TObject *Sender)
{
	if (cbjiekuanstate->Text != "") {
		chjiekuan->Checked = true;
	}
	else
	{
    	chjiekuan->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientwanglai::cbfapiaoChange(TObject *Sender)
{
	if (cbfapiao->Text != "") {
		chfapiao->Checked = true;
	}
	else
	{
		chfapiao->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientwanglai::dtpbeginChange(TObject *Sender)
{
	chstart->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientwanglai::dtpendChange(TObject *Sender)
{
	chend->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientwanglai::edfapiaohaoChange(TObject *Sender)
{
	if (edfapiaohao->Text != "") {
		chfapiaohao->Checked = true;
	}
	else
	{
    	chfapiaohao->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientwanglai::FormShow(TObject *Sender)
{
	editjianshuo->SetFocus();
}
//---------------------------------------------------------------------------


void __fastcall Tfrmclientwanglai::cbdanweiChange(TObject *Sender)
{
	if (cbdanwei->Text != "") {
		chclient->Checked = true;
	}
	else
	{
    	chclient->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientwanglai::edminKeyPress(TObject *Sender, wchar_t &Key)
{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '\b')) {
		Key = NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientwanglai::edminChange(TObject *Sender)
{
	if (edmin->Text != "") {
		chshiyang->Checked = true;
	}
	else if (edmax->Text != "") {
		chshiyang->Checked = true;
	}
	else
	{
		chshiyang->Checked = false;
	}
}
//---------------------------------------------------------------------------


void __fastcall Tfrmclientwanglai::dg1DblClick(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
	if (query->RecordCount > 0) {
		TfrmNotedetail *frm = new TfrmNotedetail(Application,query->FieldByName("Code")->AsString,Client,fcon,0);
		frm->ShowModal();
		delete frm;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientwanglai::dg1Enter(TObject *Sender)
{
	if (!query->IsEmpty()  && query->State == dsEdit ) {
		try {
			query->Post();
		} catch (...) {
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientwanglai::queryAfterPost(TDataSet *DataSet)
{
	try {
    	TLocateOptions   Opts;
		Opts.Clear();
		Opts   <<   loPartialKey;
		String   str   = query->FieldByName("ID")->AsAnsiString ;
		query->Active = false;
		query->Active = true;
		query->Locate("ID",str,Opts);
	} catch (...) {
	}
}

//---------------------------------------------------------------------------
void __fastcall Tfrmclientwanglai::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmclientwanglai::dg1TitleClick(TColumn *Column)
{
	if (query->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (query->Sort == "") {
		query->Sort =  Column->FieldName + " ASC";
	}
	else if (query->Sort == qusort) {
		query->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		query->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------


