//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "unitinorderfenfa.h"
#include "UnitDiaobo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma resource "*.dfm"
Tfrmunitinorder *frmunitinorder;
//---------------------------------------------------------------------------
__fastcall Tfrmunitinorder::Tfrmunitinorder(TComponent* Owner,TADOConnection *con,int headerid,int stgid)
	: TForm(Owner)
{
DBGrid1->OnDrawColumnCell=DBGrid1DrawColumnCell;
	fcon = con;
	fstgid = stgid;
	hdid = headerid;
	cmdAddNote->Connection = con;
	AnsiString sql;
	sql = "select distinct DENSE_RANK() over (order by BS_BookCatalog.id) as xuhao,BS_OrderNote.id,BS_BookCatalog.isbn,BS_BookCatalog.name,BS_BookCatalog.price,BS_BookCatalog.author,BS_BookCatalog.presscount, "
	" BS_OrderNoteHeader.HdTime,BS_StorageNote.amount as stgamount,"
	" BS_PressInfo.AbbreviatedName,dbo.UF_BS_GetClientName(BS_OrderNoteHeader.VendorID) as clientname,BS_OrderNote.Amount, "
	" BS_OrderNote.SendAmount,BS_OrderNote.UnsendAmount,order_lock.stkamount,BS_OrderNote.localnum,order_lock.usableamount "
	" from BS_StorageNote join BS_OrderNote on BS_StorageNote.BkcatalogID = BS_OrderNote.BkcatalogID "
	" left join BS_OrderNoteHeader on BS_OrderNote.OrderNtHeaderID = BS_OrderNoteHeader.id "
	" left join BS_BookCatalog on BS_OrderNote.BkcatalogID = BS_BookCatalog.id "
	" left join BS_PressInfo on BS_BookCatalog.pressid = BS_PressInfo.id "
	" left join order_lock on BS_BookCatalog.id = order_lock.bkcatalogid "
	" where BS_OrderNote.state = 0 and BS_OrderNote.UnsendAmount > 0 and BS_OrderNoteHeader.type = 1 "
	" and order_lock.stgid = " + IntToStr(stgid) + " and BS_StorageNote.StgNtHeaderID = " + IntToStr(headerid);

	query->Connection = con;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmunitinorder::DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumn *Column, Grids::TGridDrawState State)
{
	if (DBGrid1->DataSource->DataSet->FieldByName("xuhao")->AsInteger%2  == 0) {
		//DBGrid1->Canvas->Brush->Color = clBtnFace;
		DBGrid1->Canvas->FillRect(Rect);
		DBGrid1->Canvas->Font->Color = clBlue ;
		//DBGrid1->Canvas->Font->Style =  TFontStyles()<<fsBold;
		DBGrid1->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}
	if (DBGrid1->DataSource->DataSet->FieldByName("xuhao")->AsInteger%2  == 1 ) {
		//DBGrid1->Canvas->Brush->Color = clBtnFace;
		DBGrid1->Canvas->FillRect(Rect);
		DBGrid1->Canvas->Font->Color = clBlack ;
		//DBGrid1->Canvas->Font->Style =  TFontStyles()<<fsBold;
		DBGrid1->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmunitinorder::BtnLastRecordClick(TObject *Sender)
{
	cmdAddNote->Parameters->ParamByName("@stghdid")->Value = hdid;
	cmdAddNote->Parameters->ParamByName("@StgID")->Value = fstgid;
	cmdAddNote->Parameters->ParamByName("@user")->Value = userid;
	//cmdAddNtHeader->Parameters->ParamByName("@ReturnCode")->Value = "1";
	cmdAddNote->Execute();
	returncode =  cmdAddNote->Parameters->ParamByName("@ReturnCode")->Value ;
	sgfirsthid =  cmdAddNote->Parameters->ParamByName("@Returnint")->Value ;
	//sgheaderid =  cmdAddNote->Parameters->ParamByName("@RETURN_VALUE")->Value;
	AnsiString returncode1 = "已生成配送单：\n" + returncode + "\n是否查看？";
        ;
	if (ShowMsg(Handle ,returncode1.c_str(),1)==1 )
	{
	//转配送查询
		AnsiString sql = "select * from BS_ZN_DiaoNoteHeader where ZNDiaoNtCode in (" + returncode + ")";
		Tfrmdiaobo * frm = new Tfrmdiaobo(Application,fcon,fstgid,userid,1);
		frm->aqhd->Close();
		frm->aqhd->SQL->Clear();
		frm->aqhd->SQL->Add(sql);
		frm->aqhd->Open();
		frm->QryNtHeader(sgfirsthid);
		frm->cbinstorage->Enabled = false;
			//cbinbkstack->Enabled = false;
		frm->BtnSaveAll->Enabled = false;
		frm->membk->Enabled = false;
		frm->DBNavigator1->Enabled = true;
	}
    Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmunitinorder::BtnExportClick(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
	DbgridToExcel(DBGrid1);
}
//---------------------------------------------------------------------------
//Excel导出函数
bool Tfrmunitinorder::DbgridToExcel(TDBGrid* dbg)
{
	AnsiString temptext,path  ;
	savedlg->FileName = rkcode + "内部订单";
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = Sysutils::ExtractFilePath(savedlg->FileName .c_str()  );
		Name = Sysutils::ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".xls";
		path =  DBPath;
	}
	else
	{
		return false;
	}

	if(FileExists(path))
		try {
			DeleteFileA(path);
		} catch (...) {
			return false;
		}
	int n;

	Variant  v,vSheet,R,xWorkbook;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
	xWorkbook = v.OlePropertyGet("ActiveWorkBook");
	vSheet =  xWorkbook.OlePropertyGet("ActiveSheet");

	n = 0;

	int t1= 0;
	temptext = "\n";
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
	dbg->DataSource ->DataSet->DisableControls();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				if (dbg->Columns ->Items [j-1]->FieldName == "isbn") {
					t1++;
					temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );
					//mptext = temptext + "'" + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
				else if (dbg->Columns ->Items [j-1]->FieldName == "id" || dbg->Columns ->Items [j-1]->FieldName == "backdot"){

				}
				else
				{
					t1++;
					temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
				}
			}
		}
		dbg->DataSource ->DataSet ->Next() ;
	}
	R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",n+1,1),vSheet.OlePropertyGet("Cells",t2+n+1,t1)); //取得合并的区域
	R.OlePropertyGet("Borders",2).OlePropertySet("linestyle",1);
	R.OlePropertyGet("Borders",4).OlePropertySet("linestyle",1);
	dbg->DataSource ->DataSet->EnableControls();

	try {
		xWorkbook.OleFunction("SaveAs",path.c_str());
	} catch (Exception &E) {
		//ShowMessage(E.Message);
	}
	return false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmunitinorder::BtnSaveClick(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
	if (query->State == dsEdit ) {
        query->Post();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmunitinorder::BtnDeleteClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmunitinorder::BtnDeleteRecordClick(TObject *Sender)
{
WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmunitinorder::FormClose(TObject *Sender, TCloseAction &Action)

{
Action =  caFree;
}
//---------------------------------------------------------------------------

