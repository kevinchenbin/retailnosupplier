//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitweijieselect.h"
#include "global.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzDBGrid"
#pragma link "RzPanel"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma resource "*.dfm"
Tfrmselectjiedan *frmselectjiedan;
//---------------------------------------------------------------------------
__fastcall Tfrmselectjiedan::Tfrmselectjiedan(TComponent* Owner,TADOConnection *cn,TADOQuery *aq)
	: TForm(Owner)
{
   aqdg->Connection = cn;
   con = cn;

   selectaq = aq;
   selectaq->First();


   mselect = false;

   AnsiString sql;
   sql = "select value from sys_bsset where name = 'changeDanHaoDisplay'";
   TADOQuery *aq1 = new TADOQuery(NULL);
   aq1->Connection = cn;
   aq1->SQL->Clear();
   aq1->SQL->Add(sql);
   aq1->Open();
   ChangeDisplay = aq1->FieldByName("value")->AsBoolean;

   if (Type == 1) {
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

	delete aq1;
	if (ChangeDisplay) {
		 dg->Columns->Items[2]->Visible = false;
		 dg->Columns->Items[3]->Visible = true;
	}
	else
	{
		dg->Columns->Items[2]->Visible = true;
		dg->Columns->Items[3]->Visible = false;
	}
	dtp1->Date = Date();
	dtp2->Date = Date();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmselectjiedan::FormClose(TObject *Sender, TCloseAction &Action)

{
  Action = caFree ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmselectjiedan::BtnExitClick(TObject *Sender)
{
   Close();
}
void Tfrmselectjiedan::GetdgData(String ID)
{
	String sql;
	if (Type == 1) {
		sql = "select A.ID,A.stgntcode,A.StgNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then '未结' when 1 then '未结完' end as state,totalfixedprice,totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,CUST_CustomerInfo.Name as custname,A.fapiaotext,A.Remarks,A.cwstate,A.hcstate,A.hongcong,A.hc "
			" from BS_StorageNoteHeader A left join CUST_CustomerInfo on A.supplierid = CUST_CustomerInfo.id  left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID  where supplierid =" + ID + " and abs(nochecked) >= 0.01 and state <> 2 and A.StgNtCode <> 0 and A.StgNtCode is not null  ";
	}else if (Type == 2) {     //as stgntcode
		sql = "select A.ID,A.wsalentcode as stgntcode ,A.WsaleNtCodeStr as CodeStr,Convert(varchar(20),hdtime,23) as hdtime,addcosts,checked,nochecked,case state when 0 then '未结' when 1 then '未结完' end as state,fixedprice as totalfixedprice,discountedprice as totaldiscountedprice,totalamount,SYS_StorageInfo.Name as stgname,dbo.uf_bs_getclientname(CUST_CustomerInfo.id) as custname,A.fapiaotext,A.Remarks,A.cwstate,A.hcstate,A.hongcong,A.hc "
			" from BS_WsaleNoteHeader A left join CUST_CustomerInfo on A.VendorID = CUST_CustomerInfo.id left join SYS_StorageInfo on A.StgID = SYS_StorageInfo.ID where VendorID in (select ID from GetChild("+ ID +")) and abs(nochecked) >= 0.01 and state <> 2 and A.WsaleNtCode <> 0 and A.WsaleNtCode is not null  ";
	}
	if (!master) {
	  	sql = sql + " and SYS_StorageInfo.ID = " + IntToStr(stgid);
	}
	if (chduizhang->Checked ) {
		sql = sql + " and A.cwstate > 0 ";
	}
	if (edfapiaotext->Text != "") {
		sql = sql + " and A.fapiaotext like '%" + edfapiaotext->Text + "%'";
	}
	if (chtime->Checked ) {
		sql = sql + " and datediff(day,HdTime,'" + DateToStr(dtp1->DateTime) + "') <= 0";
		sql = sql + " and datediff(day,HdTime,'" + DateToStr(dtp2->DateTime) + "') >= 0";
	}
	sql = sql+ " order by HdTime " ;
	aqdg->Close();
	aqdg->SQL->Clear();
	aqdg->SQL->Add(sql);
	aqdg->Open();
	/*while (!aqdg->Eof )
	{
		dg->Columns->Items [12]->PickList ->Add("0");
		dg->Columns->Items [12]->PickList ->Add("1");
		aqdg->Next();
	}   */

  ((TFloatField *)aqdg->FieldByName("totalfixedprice"))->DisplayFormat = Disc;
  ((TFloatField *)aqdg->FieldByName("totaldiscountedprice"))->DisplayFormat = Disc;
  ((TFloatField *)aqdg->FieldByName("addcosts"))->DisplayFormat = Disc;
  ((TFloatField *)aqdg->FieldByName("checked"))->DisplayFormat = Disc;
  ((TFloatField *)aqdg->FieldByName("nochecked"))->DisplayFormat = Disc;
  ((TFloatField *)aqdg->FieldByName("totalamount"))->DisplayFormat = "###,###,##0";

 /* if (ChangeDisplay) {
	 dg->Columns->Items[2]->Visible = true;
	 dg->Columns->Items[1]->Visible = false;
  }else
  {
	 dg->Columns->Items[2]->Visible = true;
	 dg->Columns->Items[1]->Visible = false;
  }    */


  /*

	((TFloatField *)dg->DataSource->DataSet->FieldByName("addcosts"))->DisplayFormat = Disc;
	((TFloatField *)dg->DataSource->DataSet->FieldByName("checked"))->DisplayFormat = Disc;
	((TFloatField *)dg->DataSource->DataSet->FieldByName("nochecked"))->DisplayFormat = Disc;

	if (Type == 1) {
		((TFloatField *)dg->DataSource->DataSet->FieldByName("totalfixedprice"))->DisplayFormat = Disc;
		((TFloatField *)dg->DataSource->DataSet->FieldByName("totaldiscountedprice"))->DisplayFormat = Disc;
			((TFloatField *)dg->DataSource->DataSet->FieldByName("thistime"))->DisplayFormat = Disc;
		sql = " select sum(nochecked) as totalyinghu ";
		sql = sql + " from BS_StorageNoteHeader A join BS_StorageNoteHeader_Attachment B on A.stgntcode = B.stgntcode where supplierid =" + ID + " and state <> 2 ";
	}else if (Type == 2) { //客户
			((TFloatField *)dg->DataSource->DataSet->FieldByName("totalfixedprice"))->DisplayFormat = Disc;
			((TFloatField *)dg->DataSource->DataSet->FieldByName("totalfixedprice"))->DisplayFormat = Disc;
				((TFloatField *)dg->DataSource->DataSet->FieldByName("thistime"))->DisplayFormat = Disc;
		sql = " select sum(nochecked) as totalyinghu ";
		sql = sql + " from BS_WsaleNoteHeader  where VendorID =" + ID + " and state <> 2 ";
	}


       */

   //	edithukuan->Text = FormatFloat("0.00",aquerytotal->FieldByName("totalyinghu")->AsFloat);

}
//---------------------------------------------------------------------------

void __fastcall Tfrmselectjiedan::FormShow(TObject *Sender)
{
	GetdgData(ID);
	if (Type == 1) {
	   this->Caption = "请选择入库单据";
	   dg->Columns->Items[1]->Title->Caption = "供应商名称";
	   dg->Columns->Items[2]->Title->Caption = "入库单号";
	   dg->Columns->Items[3]->Title->Caption = "入库单号";
	   dg->Columns->Items[5]->Title->Caption = "入库日期";

   }else
   {
	  this->Caption = "请选择发货单据";
	  dg->Columns->Items[1]->Title->Caption = "客户名称";
	  dg->Columns->Items[2]->Title->Caption = "发货单号";
	  dg->Columns->Items[3]->Title->Caption = "发货单号";
	  dg->Columns->Items[5]->Title->Caption = "发货日期";
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrmselectjiedan::BtnOKClick(TObject *Sender)
{
	dgDblClick(this);
	/*if (aqdg->IsEmpty() ) {
    	return;
	}
	for (int i= 0; i < selectedID->Count ; i++) {
	   if (selectedID->IndexOf(aqdg->FieldByName("stgntcode")->AsAnsiString) != -1 ) {
		 return;
	   }
   }
	selectaq->Append();
	selectaq->FieldByName("stgntcode")->AsAnsiString = aqdg->FieldByName("stgntcode")->AsAnsiString ;
	selectaq->FieldByName("CodeStr")->AsAnsiString = aqdg->FieldByName("CodeStr")->AsAnsiString ;
	selectaq->FieldByName("hdtime")->AsDateTime = aqdg->FieldByName("hdtime")->AsDateTime  ;
	selectaq->FieldByName("totalfixedprice")->AsAnsiString = aqdg->FieldByName("totalfixedprice")->AsAnsiString ;
	selectaq->FieldByName("totaldiscountedprice")->AsAnsiString = aqdg->FieldByName("totaldiscountedprice")->AsAnsiString ;
	selectaq->FieldByName("addcosts")->AsAnsiString = aqdg->FieldByName("addcosts")->AsAnsiString ;
	selectaq->FieldByName("checked")->AsAnsiString = aqdg->FieldByName("checked")->AsAnsiString ;
	selectaq->FieldByName("nochecked")->AsAnsiString = aqdg->FieldByName("nochecked")->AsAnsiString ;
	selectaq->FieldByName("checked")->AsAnsiString = aqdg->FieldByName("checked")->AsAnsiString ;
	selectaq->FieldByName("totalamount")->AsAnsiString = aqdg->FieldByName("totalamount")->AsAnsiString ;

	selectaq->FieldByName("thistime")->AsAnsiString = "0.00" ;
	selectaq->FieldByName("type")->AsAnsiString = IntToStr(Type) ;
	selectaq->FieldByName("EndMoneyDocumentID")->AsAnsiString = DanCode  ;
	selectedID->Add(aqdg->FieldByName("stgntcode")->AsAnsiString);

	Close();    */
}
//---------------------------------------------------------------------------

void __fastcall Tfrmselectjiedan::BtnPostClick(TObject *Sender)
{
	if (aqdg->IsEmpty() ) {
		return;
	}
	if (aqdg->State == dsEdit ) {
        aqdg->Post();
	}
	aqdg->First();
	while(!aqdg->Eof)
	{
		if (AddEnable(Type,aqdg->FieldByName("stgntcode")->AsAnsiString)) {
			for (int i= 0; i < selectedID->Count ; i++) {
				if (selectedID->IndexOf(aqdg->FieldByName("stgntcode")->AsAnsiString) != -1 ) {
					return;
				}
			}
			selectaq->Append();
			selectaq->FieldByName("stgntcode")->AsAnsiString = aqdg->FieldByName("stgntcode")->AsAnsiString ;
			selectaq->FieldByName("hdtime")->AsDateTime = aqdg->FieldByName("hdtime")->AsDateTime  ;
			selectaq->FieldByName("totalfixedprice")->AsAnsiString = aqdg->FieldByName("totalfixedprice")->AsAnsiString ;
			selectaq->FieldByName("totaldiscountedprice")->AsAnsiString = aqdg->FieldByName("totaldiscountedprice")->AsAnsiString ;
			selectaq->FieldByName("addcosts")->AsAnsiString = aqdg->FieldByName("addcosts")->AsAnsiString ;
			selectaq->FieldByName("checked")->AsAnsiString = aqdg->FieldByName("checked")->AsAnsiString ;
			selectaq->FieldByName("nochecked")->AsAnsiString = aqdg->FieldByName("nochecked")->AsAnsiString ;
			selectaq->FieldByName("checked")->AsAnsiString = aqdg->FieldByName("checked")->AsAnsiString ;
			selectaq->FieldByName("totalamount")->AsAnsiString = aqdg->FieldByName("totalamount")->AsAnsiString ;
			selectaq->FieldByName("CodeStr")->AsAnsiString = aqdg->FieldByName("CodeStr")->AsAnsiString ;
			selectaq->FieldByName("thistime")->AsAnsiString = "0.00" ;
			if (aqdg->FieldByName("hc")->AsInteger == 1 && aqdg->FieldByName("hongcong")->AsFloat != 0.00) {
				selectaq->FieldByName("hongcong")->AsFloat = aqdg->FieldByName("hongcong")->AsFloat ;
			}
			selectedID->Add(aqdg->FieldByName("stgntcode")->AsAnsiString);
			selectaq->FieldByName("type")->AsAnsiString = IntToStr(Type) ;
			selectaq->FieldByName("EndMoneyDocumentID")->AsAnsiString = DanCode  ;
		}
		else
		{
			if (ShowMsg(this->Handle,"该单有未审核结款单，是否继续？",1) == 1) {
				for (int i= 0; i < selectedID->Count ; i++) {
					if (selectedID->IndexOf(aqdg->FieldByName("stgntcode")->AsAnsiString) != -1 ) {
						return;
					}
				}
				selectaq->Append();
				selectaq->FieldByName("stgntcode")->AsAnsiString = aqdg->FieldByName("stgntcode")->AsAnsiString ;
				selectaq->FieldByName("hdtime")->AsDateTime = aqdg->FieldByName("hdtime")->AsDateTime  ;
				selectaq->FieldByName("totalfixedprice")->AsAnsiString = aqdg->FieldByName("totalfixedprice")->AsAnsiString ;
				selectaq->FieldByName("totaldiscountedprice")->AsAnsiString = aqdg->FieldByName("totaldiscountedprice")->AsAnsiString ;
				selectaq->FieldByName("addcosts")->AsAnsiString = aqdg->FieldByName("addcosts")->AsAnsiString ;
				selectaq->FieldByName("checked")->AsAnsiString = aqdg->FieldByName("checked")->AsAnsiString ;
				selectaq->FieldByName("nochecked")->AsAnsiString = aqdg->FieldByName("nochecked")->AsAnsiString ;
				selectaq->FieldByName("checked")->AsAnsiString = aqdg->FieldByName("checked")->AsAnsiString ;
				selectaq->FieldByName("totalamount")->AsAnsiString = aqdg->FieldByName("totalamount")->AsAnsiString ;
				selectaq->FieldByName("CodeStr")->AsAnsiString = aqdg->FieldByName("CodeStr")->AsAnsiString ;
				selectaq->FieldByName("thistime")->AsAnsiString = "0.00" ;
				if (aqdg->FieldByName("hc")->AsBoolean && aqdg->FieldByName("hongcong")->AsFloat != 0.00) {
					selectaq->FieldByName("hongcong")->AsFloat = aqdg->FieldByName("hongcong")->AsFloat ;
				}
				selectedID->Add(aqdg->FieldByName("stgntcode")->AsAnsiString);
				selectaq->FieldByName("type")->AsAnsiString = IntToStr(Type) ;
				selectaq->FieldByName("EndMoneyDocumentID")->AsAnsiString = DanCode  ;
			}
		}
		aqdg->Next();
	}
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmselectjiedan::BtnSendtoBackClick(TObject *Sender)
{
	mselect = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmselectjiedan::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmselectjiedan::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key == VK_F1 ) {    //选择
		BtnOK->Click();
	}
	if (Key == VK_F2 ) {    //全选
		BtnPost->Click();
	}
	if (Key == VK_F3 ) {    //多选
		BtnSendtoBack->Click();
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

bool Tfrmselectjiedan::AddEnable(int type,AnsiString code)
{
	AnsiString sql;
	TADOQuery *aq1 = new TADOQuery(NULL);
	aq1->Connection = con;

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

void __fastcall Tfrmselectjiedan::SpeedButton1Click(TObject *Sender)
{
	GetdgData(ID);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmselectjiedan::dgDblClick(TObject *Sender)
{
	if (aqdg->IsEmpty() ) {
		return;
	}
	if (aqdg->State == dsEdit ) {
    	aqdg->Post();
	}
	if (!AddEnable(Type,aqdg->FieldByName("stgntcode")->AsAnsiString)) {
		if (ShowMsg(this->Handle,"该单有未审核结款单，是否继续？",1) != 1) {
			return;
		}
	}
	for (int i= 0; i < selectedID->Count ; i++) {
	   if (selectedID->IndexOf(aqdg->FieldByName("stgntcode")->AsAnsiString) != -1 ) {
			return;
	   }
	}
	selectaq->Append();
	selectaq->FieldByName("stgntcode")->AsAnsiString = aqdg->FieldByName("stgntcode")->AsAnsiString ;
	selectaq->FieldByName("CodeStr")->AsAnsiString = aqdg->FieldByName("CodeStr")->AsAnsiString ;
	selectaq->FieldByName("hdtime")->AsDateTime = aqdg->FieldByName("hdtime")->AsDateTime ;
	selectaq->FieldByName("totalfixedprice")->AsAnsiString = aqdg->FieldByName("totalfixedprice")->AsAnsiString ;
	selectaq->FieldByName("totaldiscountedprice")->AsAnsiString = aqdg->FieldByName("totaldiscountedprice")->AsAnsiString ;
	selectaq->FieldByName("addcosts")->AsAnsiString = aqdg->FieldByName("addcosts")->AsAnsiString ;
	selectaq->FieldByName("checked")->AsAnsiString = aqdg->FieldByName("checked")->AsAnsiString ;
	selectaq->FieldByName("nochecked")->AsAnsiString = aqdg->FieldByName("nochecked")->AsAnsiString ;
	selectaq->FieldByName("checked")->AsAnsiString = aqdg->FieldByName("checked")->AsAnsiString ;
	selectaq->FieldByName("totalamount")->AsAnsiString = aqdg->FieldByName("totalamount")->AsAnsiString ;
	if (aqdg->FieldByName("hc")->AsBoolean && aqdg->FieldByName("hongcong")->AsFloat != 0.00) {
		selectaq->FieldByName("hongcong")->AsFloat = aqdg->FieldByName("hongcong")->AsFloat ;
	}
	selectaq->FieldByName("thistime")->AsAnsiString = "0.00" ;
	selectaq->FieldByName("type")->AsAnsiString = IntToStr(Type) ;
	selectaq->FieldByName("EndMoneyDocumentID")->AsAnsiString = DanCode  ;
	selectedID->Add(aqdg->FieldByName("stgntcode")->AsAnsiString);
	selectaq->UpdateBatch(arAll);
	balance->DisplayDetail(balance->editnum->Text) ;
	balance->Displaytotal(balance->editnum->Text);
	if (!mselect) {
		Close();
	}
}
//---------------------------------------------------------------------------

