//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "fastcheck.h"
#include "fastcheckprint.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzEdit"
#pragma link "RzButton"
#pragma link "RzDBGrid"
#pragma resource "*.dfm"
Tfrmfastcheck *frmfastcheck;
//---------------------------------------------------------------------------
__fastcall Tfrmfastcheck::Tfrmfastcheck(TComponent* Owner,TADOConnection *cn,int stgid)
	: TfrmMDIChild(Owner)
{
	fcn = cn;
	fstgid = stgid;
	query->Connection = fcn;
	AnsiString sql ;
	sql = "select BS_WsaleNoteHeader.*,BS_Wsalechecknote.ID AS checknoteid,BS_Wsalechecknote.WsaleNoteHeaderID, "
		"BS_Wsalechecknote.checkmoney,BS_Wsalechecknote.state AS checknotestate,case BS_Wsalechecknote.state when 1 then '已审核' when 0 then '未审核' else '未收款' end  as notestate, "
		"case BS_Wsalechecknote.state when 1 then BS_Wsalechecknote.checkmoney else 0 end  as checkedmoney ,"
		"CUST_CustomerInfo.name from BS_WsaleNoteHeader left join CUST_CustomerInfo "
		 "on BS_WsaleNoteHeader.VendorID = CUST_CustomerInfo.id  "
		"LEFT JOIN BS_Wsalechecknote ON BS_WsaleNoteHeader.ID = BS_Wsalechecknote.WsaleNoteHeaderID where StgID = " + IntToStr(fstgid) ;
	sql = sql + " and BS_WsaleNoteHeader.HdTime >= '" + DateToStr(Date()) + " 0:00:00' and BS_WsaleNoteHeader.HdTime <= '" + DateToStr(Date()) + " 23:59:59' and BS_WsaleNoteHeader.WsaleNtCode > 0 order by BS_WsaleNoteHeader.HdTime DESC ";

	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	TotalView();
	edmoney->Height = 50;
	String lab = "当日快捷结款(" + DateToStr(Date()) + ")";
	Label2->Caption = lab;
	//change danhao

	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcn;
	sql = "select * from SYS_BSSET where name = 'changeDanHaoDisplay'";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();

	ChangeDisplay  = aq->FieldByName("value")->AsBoolean ;
	if (ChangeDisplay) {
		DBGrid1->Columns->Items[0]->Visible = false;
		DBGrid1->Columns->Items[1]->Visible = true;
	}
	else
	{
		DBGrid1->Columns->Items[0]->Visible = true;
		DBGrid1->Columns->Items[1]->Visible = false;
	}
	sql = "select ID,Name from SYS_StorageInfo where id = " + IntToStr(fstgid);
	aq->Close();
    aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	Label7->Caption = "当前店：" + aq->FieldByName("Name")->AsString;

	delete aq;
  DBGrid1->OnDrawColumnCell=DBGrid1DrawColumnCell;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfastcheck::btexitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfastcheck::btrefreshClick(TObject *Sender)
{
	query->Active = false;
	query->Active = true;
	TotalView();
}
//---------------------------------------------------------------------------


void __fastcall Tfrmfastcheck::edmoneyKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
		if (edmoney->Text == "") {
            return;
		}
		float money;
		try {
			money = StrToFloat(edmoney->Text);
		} catch (...) {

                        ShowMsg(Handle ,"请输入正确的结款金额！",3);
		}
		if (money < 0) {

                        ShowMsg(Handle ,"不能输入负数！",3);
			return;
		}
		if (query->FieldByName("checknotestate")->AsInteger == 1 ) {

                        ShowMsg(Handle ,"已审核单据不能修改！",3);
			return;
		}
		float checked = query->FieldByName("Checked")->AsFloat ;
		if (checked + money > query->FieldByName("DiscountedPrice")->AsFloat ) {

                         ShowMsg(Handle ,"输入的结款金额大于未结金额！",3);
			return;
		}
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcn;
		AnsiString sql ;
		sql = "select * from BS_Wsalechecknote where WsaleNoteHeaderID = " + query->FieldByName("ID")->AsString ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->RecordCount > 0) {
			sql = "update BS_Wsalechecknote set checkmoney = " + FloatToStr(money) + " where id = " + aq->FieldByName("id")->AsString ;
		}
		else
		{
			sql = "insert into BS_Wsalechecknote(WsaleNoteHeaderID,checkmoney) values(" + query->FieldByName("ID")->AsString + "," + FloatToStr(money) + ")" ;
		}
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->ExecSQL();
		delete aq;
		query->Active = false;
		query->Active = true;
		TotalView();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfastcheck::btshengjiClick(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
	float checked;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcn;
	AnsiString sql ;
	query->First();

	if (ShowMsg(Handle ,"确认审核结款?",1)!=1)
	{
		return;
	}
	query->DisableControls();

	while (!query->Eof )
	{
		if (query->FieldByName("checknotestate")->AsInteger == 0 ) {
        	query->Edit();
			checked = query->FieldByName("Checked")->AsFloat;
			query->FieldByName("Checked")->AsFloat = checked + query->FieldByName("checkmoney")->AsFloat ;
			sql = "update BS_Wsalechecknote set state = 1 where WsaleNoteHeaderID = " + query->FieldByName("ID")->AsString ;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
        }
		query->Next();
	}
	query->EnableControls();
	delete aq;
	query->UpdateBatch(arAll);
	query->Active = false;
	query->Active = true;
	TotalView();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfastcheck::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfastcheck::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Shift.Contains(ssCtrl)&& Key == 78 ) {
	   BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key == 70 ) {
	   BtnExit->Click();
	}
			if (Shift.Contains(ssCtrl)&& Key ==90) {
				WindowState = wsNormal  ;
		}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfastcheck::Button1Click(TObject *Sender)
{
	if (query->Active && query->RecordCount > 0) {
		DbgridToExcel(DBGrid1);
	}
}
//---------------------------------------------------------------------------

bool Tfrmfastcheck::DbgridToExcel(TDBGrid* dbg)
{
	AnsiString temptext  ;
	int count =0,row =0,col =0;
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

	temptext = "'" + Label2->Caption ;
	v.OlePropertyGet("Cells",1,4).OlePropertySet("Value",temptext .c_str());

	n = 2;

	int t1= 0;
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
			v.OlePropertyGet("Cells",1+n,t1).OleFunction("BorderAround",1,2,1);
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
				temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->DisplayText;
				v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
				v.OlePropertyGet("Cells",i,t1).OleFunction("BorderAround",1,2,1);
			}
		}
		dbg->DataSource ->DataSet ->Next() ;
	}

	t1= 0;
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			v.OlePropertyGet("Cells",t2+2+n,t1).OleFunction("BorderAround",1,2,1);
		}
	}

	v.OlePropertyGet("Cells",t2+2+n,1).OlePropertySet("Value","合计：" );
	temptext = "'"+ edchecked->Text;
	v.OlePropertyGet("Cells",t2+2+n,4).OlePropertySet("Value",temptext .c_str() );
	temptext = "'"+ ednochecked->Text;
	v.OlePropertyGet("Cells",t2+2+n,5).OlePropertySet("Value",temptext .c_str() );
	temptext = "'"+ eddaymoney->Text;
	v.OlePropertyGet("Cells",t2+2+n,6).OlePropertySet("Value",temptext .c_str() );
	temptext = "'"+ edchenkedmoney->Text;
	v.OlePropertyGet("Cells",t2+2+n,7).OlePropertySet("Value",temptext .c_str() );
	return false;
}

//---------------------------------------------------------------------------
void Tfrmfastcheck::TotalView()
{
	float checked = 0.00,nochecked = 0.00,daymoney = 0.00,checkedmoney;
	query->DisableControls();
	query->First();
	while (!query->Eof )
	{
		checked = checked + query->FieldByName("Checked")->AsFloat ;
		nochecked = nochecked + query->FieldByName("Nochecked")->AsFloat;
		daymoney = daymoney + query->FieldByName("checkmoney")->AsFloat ;
		checkedmoney = checkedmoney + query->FieldByName("checkedmoney")->AsFloat;
		query->Next();
	}
	query->EnableControls();
	edchecked->Text = FormatFloat("￥0.0",checked );
	ednochecked->Text = FormatFloat("￥0.0",nochecked );
	eddaymoney->Text = FormatFloat("￥0.0",daymoney );
	edchenkedmoney->Text =  FormatFloat("￥0.0",checkedmoney );
	((TFloatField *)DBGrid1->DataSource->DataSet->FieldByName("checkmoney"))->DisplayFormat = "￥0.0";
	((TFloatField *)DBGrid1->DataSource->DataSet->FieldByName("Checked"))->DisplayFormat = "￥0.0";
	((TFloatField *)DBGrid1->DataSource->DataSet->FieldByName("Nochecked"))->DisplayFormat = "￥0.0";
	((TFloatField *)DBGrid1->DataSource->DataSet->FieldByName("checkedmoney"))->DisplayFormat = "￥0.0";
}

//---------------------------------------------------------------------------

void __fastcall Tfrmfastcheck::Button2Click(TObject *Sender)
{
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcn;
	AnsiString sql ;
	sql = "select BS_WsaleNoteHeader.*,BS_Wsalechecknote.ID AS checknoteid,BS_Wsalechecknote.WsaleNoteHeaderID, "
		"BS_Wsalechecknote.checkmoney,BS_Wsalechecknote.state AS checknotestate,case BS_Wsalechecknote.state when 1 then '已审核' when 0 then '未审核' else '未收款' end  as notestate, "
		"case BS_Wsalechecknote.state when 1 then BS_Wsalechecknote.checkmoney else 0 end  as checkedmoney ,"
		"CUST_CustomerInfo.name from BS_WsaleNoteHeader left join CUST_CustomerInfo "
		 "on BS_WsaleNoteHeader.VendorID = CUST_CustomerInfo.id  "
		"LEFT JOIN BS_Wsalechecknote ON BS_WsaleNoteHeader.ID = BS_Wsalechecknote.WsaleNoteHeaderID where StgID = " + IntToStr(fstgid) ;
	sql = sql + " and BS_WsaleNoteHeader.HdTime >= '" + DateToStr(Date()) + " 0:00:00' and BS_WsaleNoteHeader.HdTime <= '" + DateToStr(Date()) + " 23:59:59' ";
	switch (rg->ItemIndex ) {
		case 1:
			sql  = sql + " and BS_Wsalechecknote.state = 1" ;
		break;
		case 2:
			sql  = sql + " and BS_Wsalechecknote.state = 0" ;
		break;
		case 3:
			sql  = sql + " and BS_WsaleNoteHeader.id not in (select WsaleNoteHeaderID from BS_Wsalechecknote)" ;
		break;
    default:
		;
	}
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	((TFloatField *)aq->FieldByName("checkmoney"))->DisplayFormat = "￥0.0";
	((TFloatField *)aq->FieldByName("Checked"))->DisplayFormat = "￥0.0";
	((TFloatField *)aq->FieldByName("Nochecked"))->DisplayFormat = "￥0.0";
	((TFloatField *)aq->FieldByName("checkedmoney"))->DisplayFormat = "￥0.0";
	if (aq->RecordCount >= 1)
	{
		Tfrmfastcheckprint* frm = new Tfrmfastcheckprint(this,m_con,aq);
		::ShowWindow(frm->Handle, SW_HIDE);
		frm->RvSystem1->SystemSetups >>ssAllowSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestPreview;
		frm->RvSystem1->SystemSetups >>ssAllowDestPrinter;
		frm->RvSystem1->SystemSetups >>ssAllowPrinterSetup;
		frm->RvSystem1->SystemSetups >>ssAllowDestFile;
		//frm->RvSystem1->DefaultDest  = rdPreview ;
		frm->RvSystem1->DefaultDest = rdPrinter ;
		frm->RvSystem1->SystemSetups<<ssAllowDestPreview;
		frm->title = Label2->Caption ;
		frm->username = username;
		frm->PrintExe();
		frm->Close();
		delete frm;
	}
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfastcheck::DBGrid1CellClick(TColumn *Column)
{
	if (query->IsEmpty() ) {
		return;
	}
	if (query->FieldByName("checkmoney")->AsString == "" ) {
		edmoney->Text = "0.00";
	}
	else
		edmoney->Text = query->FieldByName("checkmoney")->AsString;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfastcheck::DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect,
		  int DataCol, TColumn *Column, Grids::TGridDrawState State)
{
	if (State.Contains(gdSelected)) {
		DBGrid1->Canvas->Brush->Color = cl3DLight;
		DBGrid1->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}

	if (DBGrid1->DataSource->DataSet->FieldByName("checknotestate")->AsInteger == 1 ) {
		//DBGrid1->Canvas->Brush->Color = clBtnFace;
		DBGrid1->Canvas->FillRect(Rect);
		DBGrid1->Canvas->Font->Color  = clFuchsia;
	   //	DBGrid1->Canvas->Font->Style =  TFontStyles()<<fsBold;  //>>fsBold ;
		DBGrid1->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}
	if (DBGrid1->DataSource->DataSet->FieldByName("checknotestate")->AsInteger  == 0) {
		//DBGrid1->Canvas->Brush->Color = clBtnFace;
		DBGrid1->Canvas->FillRect(Rect);
		DBGrid1->Canvas->Font->Color = clRed;
		//DBGrid1->Canvas->Font->Style =  TFontStyles()<<fsBold;
		DBGrid1->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}
	if (DBGrid1->DataSource->DataSet->FieldByName("checkmoney")->AsString  == "" ) {
		//DBGrid1->Canvas->Brush->Color = clBtnFace;
		DBGrid1->Canvas->FillRect(Rect);
		DBGrid1->Canvas->Font->Color = clNavy ;
		//DBGrid1->Canvas->Font->Style =  TFontStyles()<<fsBold;
		DBGrid1->DefaultDrawColumnCell(Rect,DataCol,Column,State);
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfastcheck::BtnExitClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmfastcheck::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------


