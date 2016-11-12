//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitFeizhensi.h"
#include "UnitSelectsupplier.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzDBGrid"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmfeizhengshicai *frmfeizhengshicai;
//---------------------------------------------------------------------------
__fastcall Tfrmfeizhengshicai::Tfrmfeizhengshicai(TComponent* Owner,TADOConnection *cn,int groupid,int stgid)
	: TForm(Owner)
{
	con = cn;
	fstgid = stgid;
	group = groupid;
	aq1->Connection = cn;
	aq2->Connection = cn;
	aq3->Connection = cn;
	AnsiString sql;
	sql = "select distinct BS_Tmporder.supplierid,CUST_CustomerInfo.Name,sum(BS_Tmporder.amount) as amount "
			" from BS_Tmporder left join CUST_CustomerInfo on BS_Tmporder.supplierid = CUST_CustomerInfo.id "
			" where BS_Tmporder.modle = 1 and BS_Tmporder.groupid = " + IntToStr(groupid) + "and BS_Tmporder.supplierid  > -1 "
			" group by BS_Tmporder.supplierid,CUST_CustomerInfo.Name";
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add(sql);
	aq1->Open();

	sql = "select distinct BS_Tmporder.Pressname,sum(BS_Tmporder.amount) as amount from BS_Tmporder "
			" where BS_Tmporder.modle = 1 and BS_Tmporder.groupid = " + IntToStr(groupid) + " and BS_Tmporder.supplierid  = -1"
			" group by BS_Tmporder.Pressname";
	aq3->Close();
	aq3->SQL->Clear();
	aq3->SQL->Add(sql);
	aq3->Open();
	if (aq3->RecordCount > 0 ) {
		RzDBGrid3->Visible = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfeizhengshicai::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfeizhengshicai::RzDBGrid1CellClick(TColumn *Column)
{
	if (aq1->IsEmpty() ) {
		return;
	}
	AnsiString sql;
	sql = "select distinct A.id,A.ISBN,A.bookname,A.amount,A.bkamount,Order_lock.usableamount,A.Price,A.discount,Order_lock.stkamount,Order_lock.localnum,Order_lock.UnsendAmount,Order_lock.procurenum,A.Pressname,A.supplierid  "
			" from  BS_Tmporder A left join Order_lock on A.bkcatalogid = Order_lock.bkcatalogid "
			"where A.modle = 1 and A.groupid = " + IntToStr(group) + " and A.supplierid = " + aq1->FieldByName("supplierid")->AsString + " and Order_lock.stgid = " + IntToStr(fstgid) ;
	aq2->Close();
	aq2->SQL->Clear();
	aq2->SQL->Add(sql);
	aq2->Open();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfeizhengshicai::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfeizhengshicai::btokClick(TObject *Sender)
{
   if (aq1->IsEmpty() && aq3->IsEmpty()  ) {
      ModalResult = mrCancel ;
   }else
   {
	 ModalResult = mrOk ;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfeizhengshicai::RzDBGrid3CellClick(TColumn *Column)
{
	if (aq3->IsEmpty() ) {
		return;
	}
	AnsiString sql;
	sql = "select A.id,A.ISBN,A.bookname,A.amount,A.bkamount,Order_lock.usableamount,A.Price,A.discount,Order_lock.stkamount,Order_lock.localnum,Order_lock.UnsendAmount,Order_lock.procurenum,A.Pressname,A.supplierid  "
			" from  BS_Tmporder A left join Order_lock on A.bkcatalogid = Order_lock.bkcatalogid "
			"where A.modle = 1 and A.groupid = " + IntToStr(group) + " and A.Pressname = '" + aq3->FieldByName("Pressname")->AsString + "'" + " and Order_lock.stgid = " + IntToStr(fstgid) ;
	aq2->Close();
	aq2->SQL->Clear();
	aq2->SQL->Add(sql);
	aq2->Open();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfeizhengshicai::N1Click(TObject *Sender)
{
	if (aq2->IsEmpty() ) {
        return;
	}
	Tfrmselectsupplier * frm = new Tfrmselectsupplier(Application,con,"");
	if (mrOk == frm->ShowModal())
	{
		SupplierID = frm->GetSelectID();
	}
	for (int i =0; i < RzDBGrid2->SelectedRows->Count ; i++) {
		aq2->GotoBookmark(RzDBGrid2->SelectedRows->Items[i]);
		aq2->Edit();
		aq2->FieldByName("supplierid")->AsInteger =  SupplierID;
		aq2->UpdateBatch(arCurrent);
	}
	aq2->Active = false;
	aq2->Active = true;
	aq1->Active = false;
	aq1->Active = true;
}
//---------------------------------------------------------------------------

