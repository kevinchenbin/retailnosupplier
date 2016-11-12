//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitmuilprint.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Unitorderquery"
#pragma resource "*.dfm"
Tfrmorderquery1 *frmorderquery1;
//---------------------------------------------------------------------------
__fastcall Tfrmorderquery1::Tfrmorderquery1(TComponent* Owner,TADOConnection *con,int stgid,int modle,int tuihuo,AnsiString ausername,bool qfclient)
	: Tfrmorderquery(Owner,con,stgid,modle,tuihuo,ausername,qfclient)
{

	fstgid = stgid;
	fcon = con;
	fmodle = modle;
	ftuihuo = tuihuo;
	query->Connection = con;
	dtpstart->Date = Date();
	dtpend->Date = Date();
    TADOQuery *aq = new TADOQuery(this);
	aq->Connection = con;
	AnsiString sql;
	sql = "select * from SYS_BSSET where name = 'changeDanHaoDisplay'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	ChangeDisplay  = aq->FieldByName("value")->AsBoolean ;
        fqfclient=qfclient;
        if(qfclient)
        {
	sql = "select ID,Name from CUST_CustomerInfo where type in (2,3) and customerstate =1 and stgid="+IntToStr(fstgid);
        }else  sql = "select ID,Name from CUST_CustomerInfo where type in (2,3) and customerstate =1";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbclient->AddItem(aq->FieldByName("Name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}

        sql = "select ID,name from sys_user where  stgid="+IntToStr(fstgid);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cboperator->AddItem(aq->FieldByName("Name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}

        //fuserid
            fusername=ausername;
        cboperator->Text = ausername;

        cboperator->ItemIndex = cboperator->Items->IndexOf(ausername);
	delete aq;


       if (fmodle!=2) {
           PopupMenu1->AutoPopup= false;
         }
         printnow=false;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall Tfrmorderquery1::edclientKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		if (edclient->Text == "") {
            return;
		}
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
        AnsiString sql;
         if (fqfclient) {
           sql = "select ID,Name from CUST_CustomerInfo where type in (2,3) and customerstate =1 and stgid="+IntToStr(fstgid)+" and name like '%" + edclient->Text.Trim() + "%'" ;
         } else sql = "select ID,Name from CUST_CustomerInfo where type in (2,3) and customerstate =1  and name like '%" + edclient->Text.Trim() + "%'" ;

		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbclient->Clear();
		while (!aq->Eof )
		{
			cbclient->AddItem(aq->FieldByName("Name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		aq->First();
		cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );
		ClientID =  aq->FieldByName("ID")->AsInteger;
        cbclient->SetFocus();
		delete aq;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmorderquery1::Button2Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmorderquery1::Button1Click(TObject *Sender)
{
	AnsiString sql;
	if (fmodle == 1) {
		sql = "select RANK() OVER(order by BS_OrderNoteHeader.OrderNtCode ) as xuhao,BS_OrderNoteHeader.id,BS_OrderNoteHeader.remarks,sys_user.name as operator,BS_OrderNoteHeader.OrderNtCode,BS_OrderNoteHeader.OrderStr as NtCode,convert(nvarchar(10),HdTime,120) as HdTime,dbo.UF_BS_GetClientName(BS_OrderNoteHeader.VendorID) as clientname,BS_OrderNoteHeader.TotalAmount,BS_OrderNoteHeader.FixedPrice,BS_OrderNoteHeader.DiscountedPrice from BS_OrderNoteHeader left join sys_user on BS_OrderNoteHeader.operatorid=sys_user.id";
		if (chinorder->Checked ) {
			sqlwhere = " where BS_OrderNoteHeader.OrderNtCode <> 0 and BS_OrderNoteHeader.type = 1 ";
		}
		else
		{
			sqlwhere = " where BS_OrderNoteHeader.OrderNtCode <> 0 and BS_OrderNoteHeader.StgID = " + IntToStr(fstgid);
		}
	}else if (fmodle == 100) {
			sql = "select RANK() OVER(order by BS_OrderNoteHeader.OrderNtCode ) as xuhao,BS_OrderNoteHeader.id,BS_OrderNoteHeader.remarks,sys_user.name as operator,BS_OrderNoteHeader.OrderNtCode,BS_OrderNoteHeader.OrderStr as NtCode,convert(nvarchar(10),HdTime,120) as HdTime,dbo.UF_BS_GetClientName(BS_OrderNoteHeader.VendorID) as clientname,BS_OrderNoteHeader.TotalAmount,BS_OrderNoteHeader.FixedPrice,BS_OrderNoteHeader.DiscountedPrice from BS_OrderNoteHeader left join sys_user on BS_OrderNoteHeader.operatorid=sys_user.id where type = 1 ";
            sqlwhere = "";
			if (chstart->Checked ) {
				sqlwhere = sqlwhere + "  and datediff(day,'" + DateToStr(dtpstart->Date) + "',HdTime) >= 0";
			}
			if (chend->Checked ) {
				sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpend->Date) + "',HdTime) <= 0";
			}
			if (chclient->Checked && cbclient->Text != "") {
				sqlwhere = sqlwhere + " and VendorID in (select id from dbo.GetChild("  + IntToStr(ClientID) + ")) ";
			}
			if (chcode->Checked && edcode->Text != "" && editcode2->Text!="") {
				sqlwhere = sqlwhere +" and Orderint >= " + edcode->Text+" and Orderint <= "+editcode2->Text;
			}



			sql  = sql + sqlwhere + " order by OrderStr";
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			return;
	}
	else
	{
		if (ChangeDisplay) {
			sql = "select RANK() OVER(order by BS_WsaleNoteHeader.WsaleNtCode ) as xuhao,BS_WsaleNoteHeader.id,BS_WsaleNoteHeader.remarks,sys_user.name as operator,BS_WsaleNoteHeader.WsaleNtCodeStr as NtCode,BS_WsaleNoteHeader.WsaleNtCode,convert(nvarchar(10),HdTime,120) as HdTime,dbo.UF_BS_GetClientName(BS_WsaleNoteHeader.VendorID) as clientname,BS_WsaleNoteHeader.TotalAmount,BS_WsaleNoteHeader.FixedPrice,BS_WsaleNoteHeader.DiscountedPrice from BS_WsaleNoteHeader left join sys_user on BS_WsaleNoteHeader.operatorid=sys_user.id" ;
		}
		else
		{
			sql = "select RANK() OVER(order by BS_WsaleNoteHeader.WsaleNtCode ) as xuhao,BS_WsaleNoteHeader.id,BS_WsaleNoteHeader.remarks,sys_user.name as operator,BS_WsaleNoteHeader.WsaleNtCode as NtCode,convert(nvarchar(10),HdTime,120) as HdTime,dbo.UF_BS_GetClientName(BS_WsaleNoteHeader.VendorID) as clientname,BS_WsaleNoteHeader.TotalAmount,BS_WsaleNoteHeader.FixedPrice,BS_WsaleNoteHeader.DiscountedPrice from BS_WsaleNoteHeader left join sys_user on BS_WsaleNoteHeader.operatorid=sys_user.id" ;
		}
		sqlwhere = " where BS_WsaleNoteHeader.StgID = " + IntToStr(fstgid);
		if (ftuihuo == 0) {
			sqlwhere = sqlwhere + " and BS_WsaleNoteHeader.WsaleNtCodeInt > 0 ";
		}
		else if (ftuihuo == 1) {
			sqlwhere = sqlwhere + " and BS_WsaleNoteHeader.TWsaleNtCodeInt > 0 ";
		}
                if (checkfahuofashi->Checked ) {  //发货方式
			sqlwhere = " where BS_WsaleNoteHeader.remarks like '%"+cbfahuofashi->Text+"%'";
		}
               if (cbchao->Checked) {
                  if (cboperator->Text!="") {
                    try
                    {
                     int huiid = (int)cboperator->Items->Objects[cboperator->ItemIndex];
                     sqlwhere = sqlwhere +" and OperatorID ="+IntToStr(huiid);
                     }
                     catch(...)
                     {}
                  }

                }

	}
	if (chstart->Checked ) {
		sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',HdTime) >= 0";
	}
	if (chend->Checked ) {
		sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpend->Date) + "',HdTime) <= 0";
	}
	if (chclient->Checked && cbclient->Text != "") {
		sqlwhere = sqlwhere + " and VendorID in (select id from dbo.GetChild("  + IntToStr(ClientID) + ")) ";
	}


         if(fmodle==1)
         {
            if(cbshenghe->Checked&&cbweisheng->Checked)
                        {


                        }else
                        {
                        if(cbshenghe->Checked)
                        {
                              sqlwhere = sqlwhere +" and shenheistate =0 ";
                        }
                          if (cbweisheng->Checked) {
                            sqlwhere = sqlwhere +" and shenheistate =1" ;
                        }  }

                                         //操作员查询
             if (cbchao->Checked) {
                  if (cboperator->Text!="") {
                    try
                    {
                    int huiid = (int)cboperator->Items->Objects[cboperator->ItemIndex];
                     sqlwhere = sqlwhere +" and OperatorID ="+IntToStr(huiid);
                     }
                     catch(...)
                     {}
                  }

                }

         }






	if (chcode->Checked && edcode->Text != "" && editcode2->Text!="") {
    	if (fmodle == 1) {
			sqlwhere = sqlwhere +" and Orderint >= " + edcode->Text+" and Orderint <= "+editcode2->Text;
		}
		else
		{
			if (ChangeDisplay) {
                             	if (ftuihuo == 0) {
                                     sqlwhere = sqlwhere + " and WsaleNtCodeInt >= " + edcode->Text + " and WsaleNtCodeInt <= " + editcode2->Text;
                                }else
                                {
                                    sqlwhere = sqlwhere + " and TWsaleNtCodeInt >= " + edcode->Text + " and TWsaleNtCodeInt <= " + editcode2->Text;

                                }

			}
			else
			{
				sqlwhere = sqlwhere + " and WsaleNtCode = " + edcode->Text ;
			}
		}
	}
	sql = sql + sqlwhere;
	if (fmodle == 1) {
		sql = sql + " order by OrderStr";
	}
	else {
		sql = sql + " order by WsaleNtCodeStr";
	}
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();


        int total,zhitotal,shetotal;
        shetotal = 0;
        zhitotal=0;
         total=0;
         query->DisableControls();
         AnsiString ss;
        for (int i=0; i < query->RecordCount; i++) {
             ss = query->FieldByName("remarks")->AsAnsiString ;

            if (ss.Pos("社直发")!=0) {
               shetotal=shetotal+ query->FieldByName("TotalAmount")->AsInteger ;
            }
            if (ss.Pos("淄转发")!=0) {
                zhitotal=zhitotal+ query->FieldByName("TotalAmount")->AsInteger ;
            }

            total=total+query->FieldByName("TotalAmount")->AsInteger ;
            query->Next();
        }
        query->EnableControls();
        edittotal->Text = IntToStr(total);
        editshe->Text = IntToStr(shetotal);
        editzhi->Text = IntToStr(zhitotal);
}
//---------------------------------------------------------------------------
AnsiString Tfrmorderquery1::GetNoteCode()
{
	AnsiString recode;
	if (!query->IsEmpty() ) {
		if (fmodle == 2 && ChangeDisplay ) {
			recode = query->FieldByName("WsaleNtCode")->AsString ;
		}
		else if (fmodle == 1 || fmodle == 100) {
			recode = query->FieldByName("OrderNtCode")->AsString ;
		}
		else
		{
			recode = query->FieldByName("NtCode")->AsString ;
		}
	}
	return recode;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmorderquery1::DBGrid1DblClick(TObject *Sender)
{
	if (query->IsEmpty()) {
		return;
	}
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmorderquery1::DBGrid1KeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
    	if (query->IsEmpty()) {
			return;
		}
        ModalResult = mrOk ;
	}
}
//---------------------------------------------------------------------------

AnsiString Tfrmorderquery1::GetWhere()
{
	return sqlwhere;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmorderquery1::dtpstartChange(TObject *Sender)
{
	chstart->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderquery1::dtpendChange(TObject *Sender)
{
	chend->Checked = true;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmorderquery1::edcodeChange(TObject *Sender)
{
	if (edcode->Text != "") {
		chcode->Checked = true;
	}
	else
	{
    	chcode->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderquery1::cbclientClick(TObject *Sender)
{
	try {
		ClientID = (int)(cbclient->Items->Objects[cbclient->ItemIndex]);
	} catch (...) {

                ShowMsg(Handle ,"请选择正确的客户！",3);
		return;
	}
}
//---------------------------------------------------------------------------


void __fastcall Tfrmorderquery1::cbclientChange(TObject *Sender)
{
	if (cbclient->Text != "") {
		chclient->Checked = true;
	}
	else
	{
		chclient->Checked = false;
	}
}
void Tfrmorderquery1::enableshenghe()
{


    cbweisheng->Visible=true;
    cbshenghe->Visible = true;
}

void Tfrmorderquery1::enablefahuofangshi()
{
       checkfahuofashi->Visible = true;
       cbfahuofashi->Visible = true;


}
//---------------------------------------------------------------------------


void __fastcall Tfrmorderquery1::cbfahuofashiChange(TObject *Sender)
{

   checkfahuofashi->Checked = true;

}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderquery1::A1Click(TObject *Sender)
{
   //

     if (query->IsEmpty() ) {
		return;
	}
	for (int i = 1; i <= query->RecordCount; i++) {
		DBGrid1->DataSource->DataSet->RecNo = i;
		DBGrid1->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmorderquery1::P1Click(TObject *Sender)
{
  //
  	if (query->IsEmpty()) {
			return;
		}
    clientname="";
    headerid="";
             	DBGrid1->DataSource->DataSet->DisableControls();
  	for (int i = 0 ; i < DBGrid1->SelectedRows->Count ; i++) {

	       	 DBGrid1->DataSource->DataSet->Bookmark = DBGrid1->SelectedRows->Items[i];
	       	 bm = DBGrid1->DataSource->DataSet->GetBookmark();
	       	 DBGrid1->DataSource->DataSet->GotoBookmark(bm);
                 clientname=clientname+ query->FieldByName("clientname")->AsAnsiString+",";
                 headerid= headerid+query->FieldByName("id")->AsAnsiString+",";

        }
        	DBGrid1->DataSource->DataSet->EnableControls();
     if (headerid=="") {
        ShowMsg(Handle ,"请选择单据！",3);
     }else
     {
         printnow=true;
         ModalResult = mrOk ;
     }

}
//---------------------------------------------------------------------------
void __fastcall Tfrmorderquery1::Button3Click(TObject *Sender)
{
 P1->Click();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmorderquery1::FormShow(TObject *Sender)
{
//
if (0==version) {
        cbfahuofashi->Text = "一般发货";
        cbfahuofashi->Items->Add("一般发货");
        cbfahuofashi->Items->Add("样书发货");
        cborderbk->Caption = "发货类型:";
        Label3->Visible = false;
        Label5->Visible = false;
        editshe->Visible=false;
        editzhi->Visible = false;
}
}
//---------------------------------------------------------------------------

