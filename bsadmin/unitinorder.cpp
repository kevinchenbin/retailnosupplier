//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unitinorder.h"
#include "UnitSelectClient.h"
#include "NoteCode.h"
#include "ProcureMng.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzEdit"
#pragma link "RzSpnEdt"
#pragma resource "*.dfm"
Tfrminorder *frminorder;
//---------------------------------------------------------------------------
__fastcall Tfrminorder::Tfrminorder(TComponent* Owner,TADOConnection *cn,int stgid,int userid,int headid)
	: TForm(Owner)
{
	con = cn;
	fstgid = stgid;
	fuserid = userid;
	ClientID = -1;
	query->Connection = cn;
	dtpstart->Date = Date();
	dtpend->Date = Date();
	fheadid = headid;
	dtedtDate->Date = Date();
	chordercode->Checked = false;
        cmdAddNote->Connection = cn;
        aq->Connection = cn;
}
//---------------------------------------------------------------------------
void __fastcall Tfrminorder::edclientKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		TfrmselectClient * frm = new TfrmselectClient(Application,con,edclient->Text,fstgid);
		if (mrOk == frm->ShowModal())
		{
			ClientID = frm->GetSelectID();
			ClientView();
			edtclient->SetFocus();
		}
		delete frm;
	}
}
//---------------------------------------------------------------------------
void Tfrminorder::ClientView()
{
	if (ClientID == -1) {
		return;
	}
	String sql;
	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = con;
	sql = "exec USP_BS_Client_View 0," + IntToStr(ClientID)  ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	edtclient->Text = aq->FieldByName("Name")->AsAnsiString ;
	delete aq;
}
void Tfrminorder::loadsupplier()
{

   	String sql;
	TADOQuery * aq = new TADOQuery(NULL);
	aq->Connection = con;
	sql = " select * from CUST_CustomerInfo where Type =1 and customerstate=1  order by name";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();

	//while (aq->)

	delete aq;






}
//---------------------------------------------------------------------------
void __fastcall Tfrminorder::spselectClientClick(TObject *Sender)
{

	TfrmselectClient * frm = new TfrmselectClient(Application,con,"",fstgid);
	if (mrOk == frm->ShowModal())
	{
		ClientID = frm->GetSelectID();
		edtclient->SetFocus();
		ClientView();
	}
	delete frm;
}
//---------------------------------------------------------------------------
void __fastcall Tfrminorder::RzButton1Click(TObject *Sender)
{
	AnsiString sql;
      /*	sql = "select distinct BS_OrderNote.id as noteid,bs_bookcatalog.id,BS_OrderNoteHeader.OrderNtCode,dbo.UF_BS_GetClientName(BS_OrderNoteHeader.VendorID) as ClientName,BS_OrderNoteHeader.id,convert(nvarchar(10),BS_OrderNoteHeader.HdTime,120) as HdTime,order_lock.usableamount,order_lock.stkamount,BS_OrderNote.UnsendAmount, "
			" BS_OrderNoteHeader.Remarks,bs_bookcatalog.isbn,bs_bookcatalog.name,bs_bookcatalog.price,bs_bookcatalog.author,bs_bookcatalog.presscount,bs_bookcatalog.pressdate,BS_PressInfo.AbbreviatedName,BS_OrderNote.amount,BS_OrderNote.discount"
			" from BS_OrderNoteHeader left join BS_OrderNote on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id "
			" left join bs_bookcatalog on  bs_bookcatalog.id = BS_OrderNote.BkcatalogID "
			" left join order_lock on bs_bookcatalog.id = order_lock.bkcatalogid "
			" left join BS_PressInfo on bs_bookcatalog.pressid = BS_PressInfo.id";
                        以前老的选择

                        以面是世家的订单选择语句
                 */
        	sql = "select distinct BS_OrderNoteHeader.OrderNtCode,BS_OrderNoteHeader.Orderstr,BS_OrderNoteHeader.orderint as danhaoint,BS_OrderNoteHeader.ID as OID,BS_OrderNoteHeader.VendorID as ClientID,"
			" dbo.UF_BS_GetClientName(BS_OrderNoteHeader.VendorID) as ClientName,BS_OrderNoteHeader.id, "
			" convert(nvarchar(10),BS_OrderNoteHeader.HdTime,120) as HdTime,BS_OrderNoteHeader.Remarks,STG.name as stgname ,"
			" BS_OrderNote.UnsendAmount-BS_OrderNote.localnum as needprocurenum,BS_OrderNote.ID as NoteID,BS_OrderNote.fixedprice,BS_OrderNote.discountedprice,BS_OrderNote.discount,OL.stkamount, OL.stkamount - OL.localnum as usableamount,OL.UnrecAmount, "
			" BS_OrderNote.amount,BS_OrderNote.UnsendAmount,BS_OrderNote.localnum,OL.UnsendAmount AS toatalunamount,BS_OrderNote.ID DetailID ,C.ID as Bkcatalogid,C.ISBN,C.name ,C.price,C.author,"
			" BP.FullName,BP.AbbreviatedName,BT.Name "
			" from BS_OrderNoteHeader left join BS_OrderNote on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id "
			" Left join bs_bookcatalog C ON BS_OrderNote.bkcatalogid = C.ID "
			" left join BS_PressInfo BP ON  C.Pressid = BP.ID "
			" left join BS_BookType BT ON C.Smallbooktypeid = BT.ID "
			" left join SYS_StorageInfo STG ON BS_OrderNoteHeader.stgid = STG.ID "
			" left join UV_order_pro OL ON BS_OrderNote.Bkcatalogid = OL.bkcatalogid and OL.stgid = STG.ID "
			" where BS_OrderNoteHeader.stgid="+IntToStr(fstgid);

	sqlwhere = "  and (BS_OrderNote.needprocurenum <> BS_OrderNote.amount)  and BS_OrderNote.state = 0 and BS_OrderNoteHeader.state in (0,1)  and BS_OrderNoteHeader.shenheistate = 1 " ;
	if (chordercode->Checked && editdanhao->Text != "") {
		sqlwhere = sqlwhere + " and BS_OrderNoteHeader.orderint = " + editdanhao->Text ;
	}
	if (chstart->Checked ) {
		sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',BS_OrderNoteHeader.HdTime) >= 0 ";
	}
	if (chend->Checked ) {
		sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpend->Date) + "',BS_OrderNoteHeader.HdTime) <= 0 ";
	}
	if (chclient->Checked && edtclient->Text != "") {
		sqlwhere = sqlwhere + " and BS_OrderNoteHeader.VendorID in (select id from dbo.GetChild(" + IntToStr(ClientID) + ")) ";
	}

        if (cbordercheck->Checked) {

            if (cbordertype->ItemIndex==0) {     //全部

            }else if (cbordertype->ItemIndex==1) {
                        sqlwhere = sqlwhere + " and BS_OrderNoteHeader.type =1 ";
            }else if (cbordertype->ItemIndex==2) {
                 sqlwhere = sqlwhere + " and BS_OrderNoteHeader.type =0";
            }
        }
	sql = sql + sqlwhere;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
}
//---------------------------------------------------------------------------

void __fastcall Tfrminorder::dtpstartChange(TObject *Sender)
{
	chstart->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrminorder::dtpendChange(TObject *Sender)
{
	chend->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrminorder::edtclientChange(TObject *Sender)
{
	if (edtclient->Text != "") {
		chclient->Checked = true;
	}
	else
	{
    	chclient->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrminorder::dtedtDateChange(TObject *Sender)
{
	NoteCode nc(dtedtDate->Date, fstgid, spedtID->IntValue);
	edordercode->Text = nc.AsString();
}
//---------------------------------------------------------------------------

void __fastcall Tfrminorder::spedtIDChange(TObject *Sender)
{
	if (spedtID->IntValue < 0 || spedtID->IntValue > 99999)
	{
		ShowMessage("单号错误!");
		return;
	}
	NoteCode nc(dtedtDate->Date, fstgid, spedtID->IntValue);
	edordercode->Text = nc.AsString();
}
//---------------------------------------------------------------------------

void __fastcall Tfrminorder::edordercodeChange(TObject *Sender)
{
	if (edordercode->Text != "") {
		chordercode->Checked = true;
	}
	else
	{
    	chordercode->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrminorder::RzButton3Click(TObject *Sender)
{
	//转入采购
       /*	if (query->IsEmpty() ) {
		return;
	}
        int dd;
	if (DBGrid1->SelectedRows->Count > 0) {
		for (int i =0; i < DBGrid1->SelectedRows->Count ; i++) {
			query->GotoBookmark(DBGrid1->SelectedRows->Items[i]);
			int ret = pro->AddNote(1,query->FieldByName("id")->AsInteger);
			if (ret == 1) {
				pro->dsetNote->Edit();
                                pro->dsetNote->FieldByName("procureNtHeaderID")->AsInteger =pro->dsetNtHeader->FieldByName("ID")->AsInteger;
				pro->dsetNote->FieldByName("Amount")->AsInteger = query->FieldByName("amount")->AsInteger;
				pro->dsetNote->FieldByName("Discount")->AsFloat = query->FieldByName("discount")->AsFloat ;
				pro->dsetNote->FieldByName("orderid")->AsString = query->FieldByName("noteid")->AsString ;
				pro->dsetNote->FieldByName("ordercode")->AsString = query->FieldByName("OrderNtCode")->AsString  ;
				pro->dsetNote->FieldByName("clientname")->AsString = query->FieldByName("ClientName")->AsString ;
				pro->dsetNote->UpdateBatch(arAll);
			}
			else if (ret == 2) {
            	pro->dsetNote->Edit();
				pro->dsetNote->FieldByName("Amount")->AsInteger = pro->dsetNote->FieldByName("Amount")->AsInteger + query->FieldByName("amount")->AsInteger;
				pro->dsetNote->FieldByName("orderid")->AsString = pro->dsetNote->FieldByName("orderid")->AsString + "," + query->FieldByName("noteid")->AsInteger ;
				if (pro->dsetNote->FieldByName("ordercode")->AsString == "") {
					pro->dsetNote->FieldByName("ordercode")->AsString = query->FieldByName("OrderNtCode")->AsString  ;
				}
				else
				{
					pro->dsetNote->FieldByName("ordercode")->AsString = pro->dsetNote->FieldByName("ordercode")->AsString + "," + query->FieldByName("OrderNtCode")->AsString  ;
				}

				if (pro->dsetNote->FieldByName("clientname")->AsString == "") {
					pro->dsetNote->FieldByName("clientname")->AsString = query->FieldByName("ClientName")->AsString ;
				}
				else
				{
					pro->dsetNote->FieldByName("clientname")->AsString = pro->dsetNote->FieldByName("clientname")->AsString + "," + query->FieldByName("ClientName")->AsString ;
				}

				pro->dsetNote->UpdateBatch(arAll);
			}
            updaterecord();
	   }
	   pro->QryNtHeader();
	}
	else
	{
		int ret = pro->AddNote(0,query->FieldByName("id")->AsInteger);
		if (ret == 1) {
			pro->dsetNote->Edit();
			pro->dsetNote->FieldByName("Amount")->AsInteger = query->FieldByName("amount")->AsInteger;
			pro->dsetNote->FieldByName("Discount")->AsFloat = query->FieldByName("discount")->AsFloat ;
			pro->dsetNote->FieldByName("orderid")->AsString = query->FieldByName("noteid")->AsString ;
			pro->dsetNote->FieldByName("ordercode")->AsString = query->FieldByName("OrderNtCode")->AsString  ;
			pro->dsetNote->FieldByName("clientname")->AsString = query->FieldByName("ClientName")->AsString ;
			pro->dsetNote->UpdateBatch(arCurrent);

		}
		else if (ret == 2) {
			pro->dsetNote->Edit();
			pro->dsetNote->FieldByName("Amount")->AsInteger = pro->dsetNote->FieldByName("Amount")->AsInteger + query->FieldByName("amount")->AsInteger;
				pro->dsetNote->FieldByName("orderid")->AsString = pro->dsetNote->FieldByName("orderid")->AsString + "," + query->FieldByName("noteid")->AsInteger ;
				if (pro->dsetNote->FieldByName("ordercode")->AsString == "") {
					pro->dsetNote->FieldByName("ordercode")->AsString = query->FieldByName("OrderNtCode")->AsString  ;
				}
				else
				{
					pro->dsetNote->FieldByName("ordercode")->AsString = pro->dsetNote->FieldByName("ordercode")->AsString + "," + query->FieldByName("OrderNtCode")->AsString  ;
				}

				if (pro->dsetNote->FieldByName("clientname")->AsString == "") {
					pro->dsetNote->FieldByName("clientname")->AsString = query->FieldByName("ClientName")->AsString ;
				}
				else
				{
					pro->dsetNote->FieldByName("clientname")->AsString = pro->dsetNote->FieldByName("clientname")->AsString + "," + query->FieldByName("ClientName")->AsString ;
				}
			pro->dsetNote->UpdateBatch(arCurrent);
		}
		updaterecord();
	}
	pro->dsetNtHeader->Edit();
	pro->dsetNtHeader->FieldByName("inorder")->AsInteger = 1;
	pro->dsetNtHeader->UpdateBatch(arCurrent); */
}
//---------------------------------------------------------------------------
void Tfrminorder::updaterecord()
{
	AnsiString sql;
	sql  = "update bs_ordernote set needprocurenum = 10 where id = " + query->FieldByName("noteid")->AsAnsiString ;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = con;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall Tfrminorder::N1Click(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
	for (int i = 1; i <= query->RecordCount; i++) {
		DBGrid1->DataSource->DataSet->RecNo = i;
		DBGrid1->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrminorder::DBGrid1TitleClick(TColumn *Column)
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

void __fastcall Tfrminorder::sbcaigouClick(TObject *Sender)
{
   //
       if (query->IsEmpty()) {
          return;
       }
   	AnsiString sql ;
	TBookmark bm;
	Screen->Cursor = crHourGlass ;
	sql = "delete BS_Tmporder where modle = 1 and userid = " + IntToStr(fuserid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
       bool tt= false;
       sql= "select * from BS_Tmporder where 1=2";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	TLocateOptions   Opts;
	Opts.Clear();
	Opts   <<   loPartialKey;
	String   str ;
	try
	{
           if (DBGrid1->SelectedRows->Count==0) {
                MessageBox(NULL,"请先选择订单书目！","提示",MB_OK|MB_ICONINFORMATION);
		Screen->Cursor = crDefault ;
		return;
             }
		DBGrid1->DataSource->DataSet->DisableControls();
		for (int i = 0 ; i < DBGrid1->SelectedRows->Count ; i++) {

	       	 DBGrid1->DataSource->DataSet->Bookmark = DBGrid1->SelectedRows->Items[i];
	       	 bm = DBGrid1->DataSource->DataSet->GetBookmark();
	       	 DBGrid1->DataSource->DataSet->GotoBookmark(bm);
                   tt =true;
		 //amount 实际采购数量，bkamount 未发数量
		   /*	sql = "select sum(BS_Tmporder.bkamount) as bkamount,sum(BS_Tmporder.amount) as amount,sum(BS_OrderNote.localnum) as localnum from BS_Tmporder join BS_OrderNote on BS_Tmporder.ordernoteid = BS_OrderNote.id where groupid = 0 and BS_Tmporder.bkcatalogid = " + DBGrid2->DataSource->DataSet->FieldByName("Bkcatalogid")->AsAnsiString ;
			query2->Close();
			query2->SQL->Clear();
			query2->SQL->Add(sql);
			query2->Open(); */
			int cc = 0;

			if (aq->State != dsInsert) {
				aq->Append();
			}
			aq->FieldByName("groupid")->AsInteger =0;

			aq->FieldByName("modle")->AsInteger =1;
			aq->FieldByName("orderheaderid")->AsInteger = DBGrid1->DataSource->DataSet->FieldByName("OID")->AsInteger;
			aq->FieldByName("ordernoteid")->AsInteger = DBGrid1->DataSource->DataSet->FieldByName("DetailID")->AsInteger;


                        aq->FieldByName("OrderNtCode")->AsAnsiString =  DBGrid1->DataSource->DataSet->FieldByName("OrderNtCode")->AsAnsiString;
			aq->FieldByName("amount")->AsInteger =  DBGrid1->DataSource->DataSet->FieldByName("needprocurenum")->AsInteger;
			aq->FieldByName("ISBN")->AsAnsiString = DBGrid1->DataSource->DataSet->FieldByName("ISBN")->AsAnsiString;
			aq->FieldByName("BookName")->AsAnsiString = DBGrid1->DataSource->DataSet->FieldByName("name")->AsAnsiString;
			aq->FieldByName("price")->AsFloat  = DBGrid1->DataSource->DataSet->FieldByName("price")->AsFloat;
			aq->FieldByName("author")->AsAnsiString = DBGrid1->DataSource->DataSet->FieldByName("author")->AsAnsiString;
			aq->FieldByName("Orderstr")->AsAnsiString = DBGrid1->DataSource->DataSet->FieldByName("Orderstr")->AsAnsiString;
			aq->FieldByName("bkcatalogid")->AsInteger = DBGrid1->DataSource->DataSet->FieldByName("Bkcatalogid")->AsInteger;

			aq->FieldByName("bkamount")->AsInteger = DBGrid1->DataSource->DataSet->FieldByName("UnsendAmount")->AsInteger;   // 订单订数
			aq->FieldByName("pressname")->AsAnsiString = DBGrid1->DataSource->DataSet->FieldByName("FullName")->AsAnsiString;
			aq->FieldByName("clientName")->AsAnsiString = DBGrid1->DataSource->DataSet->FieldByName("ClientName")->AsAnsiString;
			aq->FieldByName("clientid")->AsInteger = DBGrid1->DataSource->DataSet->FieldByName("ClientID")->AsInteger;
			aq->FieldByName("discount")->AsFloat  = DBGrid1->DataSource->DataSet->FieldByName("discount")->AsFloat; ;
			aq->FieldByName("fixedprice")->AsFloat = DBGrid1->DataSource->DataSet->FieldByName("fixedprice")->AsFloat;
			aq->FieldByName("discountprice")->AsFloat = DBGrid1->DataSource->DataSet->FieldByName("discountedprice")->AsFloat;
			aq->FieldByName("chenked")->AsBoolean  = true;
			aq->FieldByName("supplierid")->AsInteger = -1;
			aq->FieldByName("fahuoclient")->AsInteger = 0;
			aq->FieldByName("userid")->AsInteger = fuserid;
			aq->Post();
                        DBGrid1->DataSource->DataSet->Next();
		 //}
	}
	DBGrid1->DataSource->DataSet->EnableControls() ;
	}catch(...)
	{
		MessageBox(NULL,"生成采购单失败！","提示",MB_OK|MB_ICONINFORMATION);
		Screen->Cursor = crDefault ;
		return;
	}



        if (!tt) {
           Screen->Cursor = crDefault ;
           return; 
        }
        sql = "exec USP_BS_SetSupplier " + IntToStr(0)+","+IntToStr(fuserid)+","+IntToStr(fstgid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
        ///////////////////////////////////////////////////开始生成导出单///////////////////////

         createproc();
         Screen->Cursor = crDefault;
         AnsiString caigoudanstr;
          caigoudanstr = "已成功生成"+returncode+"采购单！";
         MessageBox(NULL, caigoudanstr.c_str(),"先行者软件提醒",MB_OK|MB_ICONINFORMATION);
        Close();
}
void Tfrminorder::createproc()
{
      	if (AddCaigou()!=1) {
		return;
	}
	AnsiString sql;
	sql = "select id from BS_ProcureNoteHeader where procureid in(" + returncodeint + ")" ;
               // pro->DelInvalidNtHeader();
		pro->QryNtHeader(sgfirsthid);
		pro->DBNavigator1->Enabled = true;
		pro->aqheader->Close();
		pro->aqheader->SQL->Clear();
		pro->aqheader->SQL->Add(sql);
		pro->aqheader->Open();
      //	}
       //	delete frm;
}
int Tfrminorder::AddCaigou()
{
        cmdAddNote->Parameters->ParamByName("@OperatorID")->Value = fuserid;
	cmdAddNote->Parameters->ParamByName("@StgID")->Value = fstgid;
	cmdAddNote->Parameters->ParamByName("@CODEMODE")->Value = 0;
	cmdAddNote->Parameters->ParamByName("@groupid")->Value = 0;
	cmdAddNote->Execute();
	try
	{
		returncode =  cmdAddNote->Parameters->ParamByName("@ReturnCode")->Value ;
		sgfirsthid =  cmdAddNote->Parameters->ParamByName("@Returnint")->Value ;
		sgheaderid =  cmdAddNote->Parameters->ParamByName("@return_value")->Value;
                returncodeint = cmdAddNote->Parameters->ParamByName("@ReturnCodeint")->Value;
		return 1;
	}
	catch(...)
	{
		return 0;
	}
}
//---------------------------------------------------------------------------

