//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "suppmanage.h"
#include "detailemessage.h"
#include "CoustomerImport.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzCmboBx"
#pragma link "RzDBGrid"
#pragma resource "*.dfm"
TSuppMana *SuppMana;
//---------------------------------------------------------------------------
__fastcall TSuppMana::TSuppMana(TComponent* Owner,int Type,TADOConnection *cnn,int stgid,bool sup,bool client)
	: TForm(Owner)
{
DBGridrecord->OnDrawColumnCell=DBGridrecordDrawColumnCell;
	type = Type;
    cn = cnn;
        fstgid=stgid;
	aqinit->Connection = cnn;
	aqrecord->Connection = cnn;
	query->Connection = cnn;
        qfsupplier=sup;


        qfclient=client;

	if (type == 1) {
		this->Caption = "供应商管理";
	   //	DBGridrecord->Columns ->Items[5]->Title->Caption = "采购员";
		RzLabel1->Caption = "供应商名称" ;
	}
	if (type == 2) {
		this->Caption = "客户管理";
		RzLabel1->Caption = "客户名称"  ;
		Label3->Caption = "业务员";
	}
     /*	AnsiString sql;
	int maxid;
	sql = "select max(ID) as id from cust_customerinfo where stgid="+IntToStr(fstgid);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	maxid = query->FieldByName("id")->AsInteger ;

		sql = "select A.Type,A.ID,A.name,A.contact,A.telephone,A.fax,A.Salesman,A.code,A.date,Convert(varchar(20),A.date,111) as date1,A.address,A.local,A.Balance,A.BusinessLessBookstore,A.BookstoreLessBusiness  from cust_customerinfo A left join Sys_local B on "
			  "A.Local = b.Local left join SYS_User C on A.salesman = C.Name "
			  " where A.ID > " + IntToStr(maxid) ;

	aqrecord->Close();
	aqrecord->SQL->Clear();
	aqrecord->SQL->Add(sql); */
}
//---------------------------------------------------------------------------
void TSuppMana::Initsalesman()
{  	//初始化销售人员
	AnsiString sql ,value;
	if (type == 1) {
		sql = "select * from SYS_StaffInfo where career = 1";
	}
	else
	{
		sql = "select * from SYS_StaffInfo where career = 2";
	}

	aqinit->Close();
	aqinit->SQL->Clear();
	aqinit->SQL->Add(sql);
	aqinit->Open();
	while(!aqinit->Eof)
	{
		cbsale->AddItem(aqinit->FieldByName("Name")->AsAnsiString,(TObject*)aqinit->FieldByName("ID")->AsInteger );
		aqinit->Next();
	}
}
 int TSuppMana::getsalemanid(AnsiString name)
 {
	   int i;

	  // i= CBsale->Items->IndexOf(name) ;
	  // if (i!=-1) {
	  //      return (int)CBsale->Items->Objects[i];
	 //  }else return -1;


 }
//---------------------------------------------------------------------------
void TSuppMana::InitLocalinfo()
{
	//初始化地区
	AnsiString sql ,value;
	sql = "select ID,local from SYS_local";
	aqinit->Close();
	aqinit->SQL->Clear();
	aqinit->SQL->Add(sql);
	aqinit->Open();
	while(!aqinit->Eof)
	{
		cblocal->AddItem(aqinit->FieldByName("local")->AsString,(TObject*)aqinit->FieldByName("ID")->AsInteger);
		aqinit->Next();
	}
}
//---------------------------------------------------------------------------
void __fastcall TSuppMana::BtnViewClick(TObject *Sender)
{
	AnsiString sql,sqlwhere;
	sql = "select rank() over(order by A.id) as xuhao,A.Type,A.ID,A.name,A.stgid,A.contact,A.customerstate as cstate, case A.customerstate when 1 then '启用' when 0 then '停用' end as customerstate,A.Mobile,A.CreditMoney,A.Bond,A.telephone,A.fax,A.Salesman,A.code,A.date,Convert(varchar(20),A.date,111) as date1,A.address,A.local ,A.Balance,A.BusinessLessBookstore,A.BookstoreLessBusiness,A.bk,CUST_Customertype.name as typename from cust_customerinfo A  " ;
	sql = sql + "  left join CUST_Customertype on A.customertype = CUST_Customertype.id ";// left join SYS_StaffInfo C on A.salesman = C.name ";


	sqlwhere = " where A.type  = " + IntToStr(type);
	if (edquery->Text != "") {
		sqlwhere = sqlwhere + " and A.name like '%" + edquery->Text.Trim() + "%'";
	}
	if (etcontax->Text != "") {
		sqlwhere = sqlwhere +  " and A.Contact like '%" + etcontax->Text + "%'";
	}
	if (cblocal->Text != "") {
		sqlwhere = sqlwhere + " and A.Local = '" + IntToStr((int)(cblocal->Items->Objects[cblocal->ItemIndex])) +"'";
	}
	if (cbsale->Text !="") {
		sqlwhere = sqlwhere + " and c.name = '" + cbsale->Text.Trim() +"'";
	}
        if (qfsupplier) {
          sqlwhere =sqlwhere+ " and A.stgid="+IntToStr(fstgid);
        }

        if (qfclient) {
           sqlwhere =sqlwhere+ " and A.stgid="+IntToStr(fstgid);
        }


        if (cbstates->Text !="全部") {
            if (cbstates->ItemIndex==1) {
              sqlwhere =sqlwhere+ " and A.customerstate=1";
            }else
            if (cbstates->ItemIndex==2 ) {
               sqlwhere =sqlwhere+ " and A.customerstate=0";
            }

        }

	aqrecord->Close();
	aqrecord->SQL->Clear();
	aqrecord->SQL->Add(sql+sqlwhere);
	aqrecord->DisableControls();
	aqrecord->EnableControls();
	aqrecord->Open();
}
//---------------------------------------------------------------------------
void __fastcall TSuppMana::BtnNewClick(TObject *Sender)
{
	TDetaileForm * frm = new TDetaileForm(Application,type,1,"",cn,fstgid);
	frm->ShowModal() ;
	delete frm;
	//aqrecord->Close();
	//aqrecord->Open();
	aqrecord->Active = false;
	aqrecord->DisableControls();
	aqrecord->EnableControls();
	aqrecord->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TSuppMana::BtnFinishClick(TObject *Sender)
{
	if (aqrecord->IsEmpty() ) {
    	return;
	}
	if (aqrecord->FieldByName("name")->AsString == "普通供应商" ) {
		ShowMsg(Handle ,"普通供应商不能修改！",3);
		return;
	}
	if (aqrecord->FieldByName("name")->AsString == "普通客户" ) {
		ShowMsg(Handle ,"普通客户不能修改！",3);
		return;
	}
	AnsiString sql;
	if (type == 1) {
		sql = "select * From BS_StorageNoteHeader where (cwstate > 0 or Checked <> 0) and SupplierID = " + aqrecord->FieldByName("ID")->AsAnsiString ;
	}
	else
	{
		sql = "select * From BS_WsaleNoteHeader where (cwstate > 0 or Checked <> 0) and VendorID = " + aqrecord->FieldByName("ID")->AsAnsiString ;
	}
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->RecordCount > 0) {
		ShowMsg(Handle ,"该数据有相关财务记录，请谨慎修改！",3);
		//return;
	}
	TDetaileForm * frmffff = new TDetaileForm(Application,type,2,aqrecord->FieldByName("ID")->AsString,cn,fstgid);
	frmffff->ShowModal() ;
	delete frmffff;
	aqrecord->Active = false;
	aqrecord->DisableControls();
	aqrecord->EnableControls();
	aqrecord->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TSuppMana::BtnDeleteClick(TObject *Sender)
{
	AnsiString sqlSM,sqlCUS,sdf;
	if (aqrecord->IsEmpty() ) {
    	return;
	}
	if (aqrecord->FieldByName("name")->AsString == "普通供应商" ) {
		ShowMsg(Handle ,"普通供应商不能删除！",3);
		return;
	}
	if (aqrecord->FieldByName("name")->AsString == "普通客户" ) {
		ShowMsg(Handle ,"普通客户不能删除！",3);
		return;
	}
	sqlSM = "delete from CUST_CustomerStartMoney where CustomerID = " + aqrecord->FieldByName("ID")->AsString ;
	sqlCUS = "delete from CUST_CustomerInfo where ID = " + aqrecord->FieldByName("ID")->AsString ;
	if (type == 1) {
		sdf = "确认删除供应商"+aqrecord->FieldByName("name")->AsString +"吗？" ;
	}
	if (type == 2) {
		sdf = "确认删除客户"+aqrecord->FieldByName("name")->AsString +"吗？" ;
	}
	if (ShowMsg(Handle ,sdf.c_str(),1)==1) {
		try {
			aqinit->Close();
			aqinit->SQL->Clear();
			aqinit->SQL->Add(sqlSM);
			aqinit->ExecSQL();
			aqinit->Close();
			aqinit->SQL->Clear();
			aqinit->SQL->Add(sqlCUS);
			aqinit->ExecSQL();
		} catch (Exception &E) {
			ShowMsg(Handle ,"该数据跟系统其他数据有关联，不能删除！",3);
		}
	}
	aqrecord->Active = false;
	aqrecord->DisableControls();
	aqrecord->EnableControls();
	aqrecord->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TSuppMana::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TSuppMana::FormShow(TObject *Sender)
{
	Initsalesman();
	InitLocalinfo();
	if (type == 1) {
		DBGridrecord->Columns->Items[1]->Title->Caption = "供应商名称";
	}
	if (type == 2) {
		DBGridrecord->Columns->Items[1]->Title->Caption = "客户名称";
		DBGridrecord->Columns->Items[9]->Title->Caption = "业务员";
	}
        BtnView->Click();
}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::BtnExportClick(TObject *Sender)
{
	if (!aqrecord->IsEmpty() ) {
    	DbgridToExcel(DBGridrecord);
	}
}
//---------------------------------------------------------------------------

//Excel导出函数
bool __fastcall TSuppMana::DbgridToExcel(TRzDBGrid* dbg)
{
	AnsiString temptext ;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;
	if(k == 0)
	{
		ShowMsg(Handle ,"没有数据！",3);
		return false;
	}
	Variant     v;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
//  在Excel中成字符串显示
	if (type == 1) {
		v.OlePropertyGet("Cells",1,5).OlePropertySet("Value","供应商查询记录" );
	}
	else
	{
		v.OlePropertyGet("Cells",1,5).OlePropertySet("Value","客户查询记录" );
	}

/*v.OlePropertyGet("Cells",2,1).OlePropertySet("Value","单位名称" );
	temptext = "'"+ etname->Text;
	v.OlePropertyGet("Cells",2,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",2,4).OlePropertySet("Value","联系人" );
	temptext = "'"+ etcontax->Text;
	v.OlePropertyGet("Cells",2,5).OlePropertySet("Value",temptext .c_str());
	v.OlePropertyGet("Cells",3,1).OlePropertySet("Value","所属区域" );
	temptext = "'"+ CBlocal->Text;
	v.OlePropertyGet("Cells",3,2).OlePropertySet("Value",temptext .c_str() );
	v.OlePropertyGet("Cells",3,4).OlePropertySet("Value","采购员" );
	temptext = "'"+ CBsale->Text;
	v.OlePropertyGet("Cells",3,5).OlePropertySet("Value",temptext .c_str());  */

	n=1;

	int t1= 0;
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
		}
	}
	int t2 = dbg->DataSource ->DataSet ->RecordCount ;

	dbg->DataSource ->DataSet ->First();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				t1++;
				temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
				v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
			}
		}
		dbg->DataSource ->DataSet ->Next() ;
	}

	return false;
}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::etcontaxKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		BtnView->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::BtnImportClick(TObject *Sender)
{
	aqrecord->Active = true;
	TFormCousImport *frm = new TFormCousImport(Application,aqrecord,type,fstgid);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F2) {     //新单
		BtnNew->Click();
	}
	if (Key == VK_F3) {     //修改
		BtnFinish->Click();
	}
	if (Key == VK_F5) {     //删除
		BtnDelete->Click();
	}
	if (Key == VK_F6) {     //导出
		BtnExport->Click();
	}
	if (Key == VK_F7) {     //导入
		BtnImport->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 70 ) {    //查询
		BtnView->Click();
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

void __fastcall TSuppMana::edqueryKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
    if (Key == VK_RETURN) {
		BtnView->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::cbsaleKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		BtnView->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::cblocalKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		BtnView->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::DBGridrecordTitleClick(TColumn *Column)
{
	if (aqrecord->IsEmpty() ) {
    	return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (aqrecord->Sort == "") {
		aqrecord->Sort =  Column->FieldName + " ASC";
	}
	else if (aqrecord->Sort == qusort) {
		aqrecord->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		aqrecord->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::DBGridrecordDrawColumnCell(TObject *Sender, const TRect &Rect,
		  int DataCol, TColumn *Column, Grids::TGridDrawState State)
{
       //
       if (DBGridrecord->DataSource->DataSet->RecordCount>0) {
         if (!DBGridrecord->DataSource->DataSet->FieldByName("cstate")->AsBoolean)
        {
          ((TDBGrid*)Sender)->Canvas->Font->Color=clRed;
       }
	  ((TDBGrid*)Sender)->DefaultDrawColumnCell(Rect,DataCol,Column,State);
       }
}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::PopupMenu1Popup(TObject *Sender)
{
	//                                    dsOpening
                                          // TDataSetState
        if (aqrecord->State == dsOpening) {
            if (DBGridrecord->DataSource->DataSet->FieldByName("cstate")->AsBoolean) {
              N1->Enabled = false;
              N2->Enabled = true;
           }else
           {
              N1->Enabled = true;
              N2->Enabled = false;

           }
        }

}
//---------------------------------------------------------------------------
void TSuppMana::updatestate(int type)
{

        if ((aqrecord->FieldByName("name")->AsAnsiString=="普通供应商")||(aqrecord->FieldByName("name")->AsAnsiString=="普通客户")) {

           ShowMsg(Handle ,"默认客户或供应商，不能停用！",3);
          return ;
        }
        AnsiString sql ;
        sql = "update CUST_CustomerInfo set customerstate = "+IntToStr(type)+" where id = "+aqrecord->FieldByName("ID")->AsAnsiString ;

        TADOQuery *aq = new TADOQuery(NULL);
        aq->Connection = cn;
        aq->Close();
        aq->SQL->Clear();
        aq->SQL->Add(sql);
        aq->ExecSQL();


        BtnView->Click();



}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::N1Click(TObject *Sender)
{
  if (DBGridrecord->DataSource->DataSet->RecordCount<=0) {
            return ;
   }
    if( type == 1)
    {
      if (Supplierpower) {
        updatestate(1);
      } else
      {
         ShowMsg(Handle,"没有供应商启停用权限",3);
      }

    }else if (type==2){
          if (Clientpower) {
            updatestate(1);
          }else
          {
            ShowMsg(Handle,"没有供应商启停用权限",3);
          }

    }
}
//---------------------------------------------------------------------------

void __fastcall TSuppMana::N2Click(TObject *Sender)
{
if (DBGridrecord->DataSource->DataSet->RecordCount<=0) {
            return ;
   }
 if( type == 1)
    {
      if (Supplierpower) {
        updatestate(0);
      } else
      {
         ShowMsg(Handle,"没有客户启停用权限",3);
      }

    }else if (type==2){
          if (Clientpower) {
            updatestate(0);
          }else
          {
            ShowMsg(Handle,"没有供应商启停用权限",3);
          }

    }
}
//---------------------------------------------------------------------------

