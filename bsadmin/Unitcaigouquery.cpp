//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitcaigouquery.h"
#include "UnitInputmessage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//Tfrmcaigouquery *frmcaigouquery;                                            jbk
//---------------------------------------------------------------------------
__fastcall Tfrmcaigouquery::Tfrmcaigouquery(TComponent* Owner,TADOConnection *con,int stgid,int modle,int tuihuo,bool qfsupplier)
	: TForm(Owner)
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
        fqfsupplier= qfsupplier;
        if (qfsupplier) {
         sql = "select ID,Name from CUST_CustomerInfo where type = 1 and customerstate =1 and stgid="+IntToStr(stgid);

        }else sql = "select ID,Name from CUST_CustomerInfo where type = 1 and customerstate =1 ";



	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbsupplier->AddItem(aq->FieldByName("Name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	aq->First();
	cbsupplier->ItemIndex = cbsupplier->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );

    sql = "select * from SYS_BSSET where name = 'changeDanHaoDisplay'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();

	ChangeDisplay  = aq->FieldByName("value")->AsBoolean ;

        if (fmodle==3) { //省代查询
                   PopupMenu1->AutoPopup = false;
                   disvialetype();
        }else if (fmodle==2) {
                  rkshowbeizhu();//入库查询
              }
              if (fmodle==1) {
                  PopupMenu1->AutoPopup = false;
              }
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouquery::edclientKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		AnsiString sql;

        if (fqfsupplier) {
         sql = "select ID,Name from CUST_CustomerInfo where type = 1 and stgid = "+IntToStr(fstgid)+" and customerstate =1 and Name like '%" + edclient->Text + "%'";
        }else sql = "select ID,Name from CUST_CustomerInfo where type = 1  and customerstate =1 and Name like '%" + edclient->Text + "%'";

		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
        cbsupplier->Clear();
		while (!aq->Eof )
		{
			cbsupplier->AddItem(aq->FieldByName("Name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		aq->First();
		cbsupplier->ItemIndex = cbsupplier->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );
		delete aq;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcaigouquery::Button2Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcaigouquery::Button1Click(TObject *Sender)
{
	AnsiString sql;

	if (fmodle == 1) {
		sql = "select BS_ProcureNoteHeader.Procurestr as NtCode,BS_ProcureNoteHeader.ProcureNtCode,convert(nvarchar(10),HdTime,120) as HdTime,CUST_CustomerInfo.Name as clientname,BS_ProcureNoteHeader.TotalAmount,BS_ProcureNoteHeader.FixedPrice,BS_ProcureNoteHeader.DiscountedPrice,remarks from BS_ProcureNoteHeader left join CUST_CustomerInfo on BS_ProcureNoteHeader.SupplierID = CUST_CustomerInfo.id ";
		sqlwhere = " where BS_ProcureNoteHeader.Procurestr <> '' and BS_ProcureNoteHeader.StgID = " + IntToStr(fstgid);
	}
	else if (fmodle==2) {


		if (ChangeDisplay) {
			sql = "select BS_StorageNoteHeader.StgNtCodeStr as NtCode,BS_StorageNoteHeader.StgNtCode,convert(nvarchar(10),HdTime,120) as HdTime,CUST_CustomerInfo.Name as clientname,BS_StorageNoteHeader.TotalAmount,BS_StorageNoteHeader.TotalFixedPrice as FixedPrice,BS_StorageNoteHeader.TotalDiscountedPrice as DiscountedPrice,remarks from BS_StorageNoteHeader left join CUST_CustomerInfo on BS_StorageNoteHeader.SupplierID = CUST_CustomerInfo.id ";
		}
		else
		{
			sql = "select BS_StorageNoteHeader.StgNtCode as NtCode,convert(nvarchar(10),HdTime,120) as HdTime,CUST_CustomerInfo.Name as clientname,BS_StorageNoteHeader.TotalAmount,BS_StorageNoteHeader.TotalFixedPrice as FixedPrice,BS_StorageNoteHeader.TotalDiscountedPrice as DiscountedPrice,remarks from BS_StorageNoteHeader left join CUST_CustomerInfo on BS_StorageNoteHeader.SupplierID = CUST_CustomerInfo.id ";
		}
		sqlwhere = " where BS_StorageNoteHeader.StgID = " + IntToStr(fstgid);
		if (ftuihuo == 0) {
			sqlwhere = sqlwhere + " and StgNtCodeInt > 0 ";
		}
		else
		{
			sqlwhere = sqlwhere + " and TStgNtCodeInt > 0 ";
		}
                        if (cbyangshu->Checked) {
                          if (cbrukuleixing->ItemIndex==1) {
                           sqlwhere = sqlwhere + " and state = 2 " ;
                        }else sqlwhere = sqlwhere + " and state = 0 " ;
                        }
                if ((cbrkbz->Visible)&&(cbrkbz->Checked)) {
                     sqlwhere = sqlwhere + " and BS_StorageNoteHeader.remarks like '%"+editrkbk->Text.Trim()+"%'";

                }
	} else if (fmodle ==3) {//省代查询


               sql="select Daixiaocode as NtCode,convert(nvarchar(10),HdTime,120) as HdTime,CUST_CustomerInfo.Name as clientname, ";
               sql = sql + " TotalAmount, FixedPrice, DiscountedPrice, BS_DaixiaoHeader.bk as remarks from dbo.BS_DaixiaoHeader  left join CUST_CustomerInfo  on BS_DaixiaoHeader.supplierid=CUST_CustomerInfo.id  ";
               sqlwhere=  " where BS_DaixiaoHeader.stgid = "+IntToStr(fstgid);
               if (cbyangshu->Checked) {
                   sqlwhere = sqlwhere + " and BS_DaixiaoHeader.bk like '%"+editbk->Text.Trim()+"%'";
               }
        }



	if (chstart->Checked ) {
		sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpstart->Date) + "',HdTime) >= 0";
	}
	if (chend->Checked ) {
		sqlwhere = sqlwhere + " and datediff(day,'" + DateToStr(dtpend->Date) + "',HdTime) <= 0";
	}
	if (chclient->Checked && cbsupplier->Text != "") {
		int  supplierid;
		try {
			supplierid = int(cbsupplier->Items->Objects[cbsupplier->ItemIndex]);
		} catch (...) {
			MessageBoxA(0,"请选择正确的供应商！","提示",MB_ICONERROR);
			return;
		}

		sqlwhere = sqlwhere + " and SupplierID = "  + IntToStr(supplierid);
	}
    if (chcode->Checked && edcode->Text != "") {
    	if (fmodle == 1) {
			sqlwhere = sqlwhere + " and Procureid = " + edcode->Text ;
		}
		else if (fmodle==2) {


			if (ChangeDisplay) {
				sqlwhere = sqlwhere + " and (StgNtCodeInt = " + edcode->Text + " or TStgNtCodeInt = " + edcode->Text + ") ";
			}
			else
			{
				sqlwhere = sqlwhere + " and StgNtCode = " + edcode->Text ;
			}

                        
		}
                else if (fmodle==3) {
                        sqlwhere = sqlwhere + " and daixiaoint="+ edcode->Text;
                     }
	}
	sql = sql + sqlwhere;
	if (fmodle == 1) {
		sql = sql + " order by Procurestr";
	}
	else if (fmodle==2){
		sql = sql + " order by StgNtCodeStr";
	}else if (fmodle==3) {
              sql = sql + " order by Daixiaocode";
              }
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
}
//---------------------------------------------------------------------------
AnsiString Tfrmcaigouquery::GetNoteCode()
{
	AnsiString recode;
	if (!query->IsEmpty() ) {
		if (fmodle == 2 && ChangeDisplay) {
			recode = query->FieldByName("StgNtCode")->AsString ;
		}
		else if (fmodle == 1) {
			recode = query->FieldByName("ProcureNtCode")->AsString ;
		}
		else
		{
			recode = query->FieldByName("NtCode")->AsString ;
		}
	}
	return recode;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcaigouquery::DBGrid1DblClick(TObject *Sender)
{
	ModalResult = mrOk ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcaigouquery::DBGrid1KeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        ModalResult = mrOk ;
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
AnsiString Tfrmcaigouquery::GetWhere()
{
	return sqlwhere;
}
void __fastcall Tfrmcaigouquery::dtpstartChange(TObject *Sender)
{
	chstart->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouquery::dtpendChange(TObject *Sender)
{
	chend->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouquery::cbsupplierChange(TObject *Sender)
{
	if (cbsupplier->Text != "") {
		chclient->Checked = true;
	}
	else
	{
    	chclient->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouquery::edcodeChange(TObject *Sender)
{
	if (edcode->Text != "") {
		chcode->Checked = true;
	}
	else
	{
		chcode->Checked = false;
	}
}
void Tfrmcaigouquery::showstate()
{

       cbyangshu->Visible = true;
       cbrukuleixing->Visible = true;




}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouquery::cbrukuleixingChange(TObject *Sender)
{
   cbyangshu->Checked= true;
}
void Tfrmcaigouquery::disvialetype()
{
        cbyangshu->Caption = "备注";
        cbyangshu->Visible = true;
        cbrukuleixing->Visible=false;
        editbk->Visible=true;


}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouquery::editbkChange(TObject *Sender)
{
	if (cbyangshu->Visible) {
		cbyangshu->Checked = true;
	}
	else
	{
		cbyangshu->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouquery::editrkbkChange(TObject *Sender)
{
    if(cbrkbz->Visible)
    {
      cbrkbz->Checked=true;


    }
}
void Tfrmcaigouquery::rkshowbeizhu()
{
      cbrkbz->Visible = true;
      editrkbk->Visible=true;





}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouquery::N1Click(TObject *Sender)
{
//更新备注

  if (query->IsEmpty()) {
        return;
    }
    int id;
    Tfrminputmessage *frmupdatebk = new Tfrminputmessage(Application);
    frmupdatebk->settitle("更新备注","备注");
    frmupdatebk->SetDisplayInfo(query->FieldByName("remarks")->AsAnsiString);
    if(frmupdatebk->ShowModal()==mrOk)
    {
      if (fmodle==2) { //批销
       try
       {
            query->Edit();
            query->FieldByName("remarks")->AsAnsiString = frmupdatebk->GetInfor();
            query->Post();
       }catch(...)
       {
       }
       /*
       TADOQuery *aq = new TADOQuery(Application);
       aq->Connection = fcon;
       aq->Close();
       aq->SQL->Clear();
       aq->SQL->Add(sql);
       aq->ExecSQL();
       delete aq; */


     }

    }
    delete  frmupdatebk;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcaigouquery::FormShow(TObject *Sender)
{
 if (0==version) {
      editrkbk->Text = "";
      cbrkbz->Checked=false;
 }
}
//---------------------------------------------------------------------------

