//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "accountdetail.h"
#include "..\bsadmin\UnitSelectClient.h"
#include "global.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "RzCmboBx"
#pragma link "RzEdit"
#pragma link "RzDBGrid"
#pragma link "RzRadChk"
#pragma link "RpBase"
#pragma link "RpCon"
#pragma link "RpConDS"
#pragma link "RpDefine"
#pragma link "RpRave"
#pragma link "RpSystem"
#pragma link "frxClass"
#pragma link "frxDBSet"
#pragma link "frxExportPDF"
#pragma link "frxExportCSV"
#pragma link "frxExportHTML"
#pragma link "frxExportImage"
#pragma link "frxExportRTF"
#pragma link "frxExportXLS"
#pragma resource "*.dfm"
TAccDetail *AccDetail;
//---------------------------------------------------------------------------
__fastcall TAccDetail::TAccDetail(TComponent* Owner,int Type,TADOConnection *cn,int stgid)
	: TForm(Owner)
{
	type = Type;
	type1 = Type;
	fcon = cn;
        fstgid = stgid;
	aquery->Connection = cn;
	Querydetail->Connection = cn;
	Querybance->Connection = cn;
	Querybase->Connection = cn;
	aqprint->Connection = cn;
	aq->Connection = cn;
	if (Type == 1) {
		this->Caption = "应付明细";
		Label9->Caption = "合计应付";
	}
	Disc = "0.00";

	AnsiString sql;
   sql = "select value from sys_bsset where name = 'changeDanHaoDisplay'";
   TADOQuery *aq1 = new TADOQuery(NULL);
   aq1->Connection = cn;
   aq1->SQL->Clear();
   aq1->SQL->Add(sql);
   aq1->Open();
   ChangeDisplay = aq1->FieldByName("value")->AsBoolean;


	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add("select * from sys_bsset where name ='xiaoshudian'");
	aq1->Open();
	storageformat =  "########" + aq1->FieldByName("bk")->AsAnsiString ;
	aq1->Close();
	aq1->SQL->Clear();
	aq1->SQL->Add("select * from sys_bsset where name ='salexiaoshudian'");
	aq1->Open();
	saleformat =  "########" + aq1->FieldByName("bk")->AsAnsiString ;

   delete aq1;
   if (ChangeDisplay) {
		DBGridbase->Columns->Items[2]->Visible = false;
		DBGridbase->Columns->Items[3]->Visible = true;
   }
   else
   {
		DBGridbase->Columns->Items[2]->Visible = true;
		DBGridbase->Columns->Items[3]->Visible = false;
   }
   DTPstart->Date = Date();
   DTPend->Date = Date();
}
//---------------------------------------------------------------------------
void __fastcall TAccDetail::FormShow(TObject *Sender)
{
	AnsiString sql ;
        qfclient=false;
        qfsupplier=false;
	if (type == 2) {
          if (qfclient) {
                  sql = "select ID,Name from CUST_CustomerInfo where Type in(3,2) and name <> '' and customerstate=1 and stgid="+IntToStr(fstgid)+" order by name ";
          }else sql = "select ID,Name from CUST_CustomerInfo where Type in(3,2) and name <> '' and customerstate=1  order by name ";

	}else
	{
          if (qfsupplier) {
              sql = "select ID,Name from CUST_CustomerInfo where Type =1 and name <> ''  and customerstate=1 and stgid="+IntToStr(fstgid)+" order by name" ;
          }else sql = "select ID,Name from CUST_CustomerInfo where Type =1 and name <> ''  and customerstate=1  order by name" ;

	}
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	if (aquery->RecordCount == 0) {
              //  ShowMsg(Handle ,"没有客户！",3);
	}
	else
	{
		while (!aquery->Eof ) {
			CBcustom->AddItem(aquery->FieldByName("Name")->AsString,(TObject*)aquery->FieldByName("ID")->AsInteger );
			aquery->Next();
		}
		//aquery->First();
		//CBcustom->ItemIndex = CBcustom->Items->IndexOfObject((TObject*)aquery->FieldByName("ID")->AsInteger);
	}
	if (type == 1) {
		Label1->Caption = "供应商";
		DBGridbase->Columns->Items[1]->Title->Caption = "供应商名称";
		DBGridbase->Columns->Items[2]->Title->Caption = "入库单号";
		DBGridbase->Columns->Items[3]->Title->Caption = "入库单号";
                  cbf->Caption = "入库";
                cbt->Caption = "入库退货";
	}
	if (type == 2) {
		Label1->Caption = "客户";
		DBGridbase->Columns->Items[1]->Title->Caption = "客户名称";
		DBGridbase->Columns->Items[2]->Title->Caption = "发货单号";
		DBGridbase->Columns->Items[3]->Title->Caption = "发货单号";
		DBGridbase->Columns->Items[8]->Title->Caption = "总应收";
                 cbf->Caption = "发货";
                cbt->Caption = "发货退货";
	}
	edquery->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TAccDetail::BtnViewClick(TObject *Sender)
{
	AnsiString sql,sqlwhere;
	int clientid;
	try {
		if (CBcustom->Text != "") {
			clientid = (int)CBcustom->Items->Objects[CBcustom->ItemIndex];
		}
	} catch (...) {
                ShowMsg(Handle ,"请选择正确的单位！",3);
		return;
	}

          fh = " and 1=1";
        rk = " and 1=1";
	if (type == 1) {
		sql = "select distinct RANK() OVER(order by BS_StorageNoteHeader.ID desc) as xuhao,BS_StorageNoteHeader.id,StgNtCode as NtCode,StgNtCodeStr as CodeStr,TotalFixedPrice as FixedPrice,TotalDiscountedPrice as DiscountedPrice,CUST_CustomerInfo.Name as clientname,"
			  "TotalAmount,AddCosts,AddCosts + TotalDiscountedPrice as totalyingfu,Checked,NoChecked,Convert(varchar(20),HdTime,111) as HdTime,Remarks from BS_StorageNoteHeader left join CUST_CustomerInfo on BS_StorageNoteHeader.SupplierID = CUST_CustomerInfo.id where 1 = 1 and StgNtCode<>0 and BS_StorageNoteHeader.stgid="+IntToStr(fstgid);
		if (chguolv->Checked ) {
			sql = sql + " and BS_StorageNoteHeader.ID in(select StgNtHeaderID from BS_StorageNote) ";
		}
		if (CBcustom->Text != "") {
			sql = sql + " and  SupplierID= "+IntToStr(clientid) ;
		}

              if (!cbf->Checked) {
                   rk = " and TotalAmount < 0 ";
               }
               if (!cbt->Checked) {

                   rk = " and TotalAmount > 0 ";
               }
	}
	if (type == 2) {
		sql = "select RANK() OVER(order by substring(WsaleNtCodeStr,1,2)  desc,BS_WsaleNoteHeader.id) as xuhao,WsaleNtCode as NtCode,BS_WsaleNoteHeader.id,WsaleNtCodeStr as CodeStr,FixedPrice,DiscountedPrice,TotalAmount,dbo.uf_bs_getclientname(BS_WsaleNoteHeader.VendorID) as clientname,"
			  "AddCosts,AddCosts + DiscountedPrice as totalyingfu, Checked,NoChecked,Convert(varchar(20),HdTime,111) as HdTime,Remarks from BS_WsaleNoteHeader left join CUST_CustomerInfo on BS_WsaleNoteHeader.VendorID = CUST_CustomerInfo.id where 1 = 1 and WsaleNtCode <>0 and BS_WsaleNoteHeader.stgid="+IntToStr(fstgid);

		if (chguolv->Checked ) {
			sql = sql + " and BS_WsaleNoteHeader.ID in(select WsaleNtHeaderID from BS_WsaleNote) ";
		}
		if (CBcustom->Text != "") {
        	sql = sql + " and VendorID in (select ID from GetChild(" + IntToStr(clientid) + "))";
		}


                   if (!cbf->Checked) {
                   fh = " and TotalAmount < 0 ";
               }
               if (!cbt->Checked) {

                   fh = " and TotalAmount > 0 ";
               }

	}

	if (CBstart->Checked ) {
		sqlwhere =  " and HdTime >='" + DateToStr(DTPstart->Date) + " 0:00:00'";
	}
	if (CBend->Checked ) {
		sqlwhere = sqlwhere + " and HdTime <='" + DateToStr(DTPend->Date) + " 23:59:59'";
	}
	if (CBstate->Text=="已结") {
		sqlwhere=sqlwhere+" and State=1" ;
	}
	else if (CBstate->Text=="未结") {
		sqlwhere=sqlwhere+" and State=0";
	}

         if (type ==1) {
          sqlwhere=sqlwhere+rk+" order by StgNtCodeStr ";
        }else if (type ==2) {
             sqlwhere=sqlwhere+fh+ "  order by substring(WsaleNtCodeStr,1,2)  desc,BS_WsaleNoteHeader.id";
         }
	sql = sql + sqlwhere;
	Querybase->Close();
	Querybase->SQL->Clear();
	Querybase->SQL->Add(sql);

        DBGridbase->DataSource->DataSet->DisableControls();

	Querybase->Open();

	sql1 =sql;
	if (type == 1) {
		((TFloatField *)DBGridbase->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = storageformat;
		((TFloatField *)DBGridbase->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = storageformat;
		((TFloatField *)DBGridbase->DataSource->DataSet->FieldByName("AddCosts"))->DisplayFormat = storageformat;
		((TFloatField *)DBGridbase->DataSource->DataSet->FieldByName("Checked"))->DisplayFormat = storageformat;
		((TFloatField *)DBGridbase->DataSource->DataSet->FieldByName("NoChecked"))->DisplayFormat = storageformat;
		((TFloatField *)DBGridbase->DataSource->DataSet->FieldByName("totalyingfu"))->DisplayFormat = storageformat;
		((TFloatField *)DBGridbase->DataSource->DataSet->FieldByName("TotalAmount"))->DisplayFormat = "###,###,##0";
	}
	else
	{
		((TFloatField *)DBGridbase->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = saleformat;
		((TFloatField *)DBGridbase->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = saleformat;
		((TFloatField *)DBGridbase->DataSource->DataSet->FieldByName("AddCosts"))->DisplayFormat = saleformat;
		((TFloatField *)DBGridbase->DataSource->DataSet->FieldByName("Checked"))->DisplayFormat = saleformat;
		((TFloatField *)DBGridbase->DataSource->DataSet->FieldByName("NoChecked"))->DisplayFormat = saleformat;
		((TFloatField *)DBGridbase->DataSource->DataSet->FieldByName("totalyingfu"))->DisplayFormat = saleformat;
		((TFloatField *)DBGridbase->DataSource->DataSet->FieldByName("TotalAmount"))->DisplayFormat = "###,###,##0";
	}

	float  DiscountedPrice=0.00;
	float  checked=0.00;
	float  AddCosts=0.00;
	float  bance=0.00;
        td=0;
        tf=0;
        ta=0;
        getheaderid = "(-1";
	while (!Querybase->Eof)              //FixedPrice,DiscountedPrice,TotalAmount
	{
		DiscountedPrice+=Querybase->FieldByName("DiscountedPrice")->AsFloat;
                ta = ta+Querybase->FieldByName("TotalAmount")->AsFloat;
                tf = tf+ Querybase->FieldByName("FixedPrice")->AsFloat;
                td=td+Querybase->FieldByName("DiscountedPrice")->AsFloat;
		AddCosts+=Querybase->FieldByName("AddCosts")->AsFloat;
		checked+=Querybase->FieldByName("Checked")->AsFloat;
                getheaderid = getheaderid +","+Querybase->FieldByName("id")->AsAnsiString ;
		Querybase->Next();
	}
        getheaderid += ")";
	sql = "select B.balance + B.totalyue as totalyue from CUST_CustomerStartMoney B " ;
	if ( CBcustom->Text != "") {
		sql = sql + " where B.CustomerID in (select ID from GetChild(" + IntToStr(clientid) + "))";
	}
	Querybance->Close();
	Querybance->SQL->Clear();
	Querybance->SQL->Add(sql);
	Querybance->Open();
	bance = Querybance->FieldByName("totalyue")->AsFloat;
	float s=DiscountedPrice+AddCosts-checked;
	if (type == 1) {
		etshiyang->Text = FormatFloat(storageformat,DiscountedPrice);
		etchecked->Text = FormatFloat(storageformat,checked);
		etaddcost->Text=FormatFloat(storageformat,AddCosts);
		etleftmoney->Text=FormatFloat(storageformat,bance);
		etcount->Text=FormatFloat(storageformat,s);
	}
	else
	{
		etshiyang->Text = FormatFloat(saleformat,DiscountedPrice);
		etchecked->Text = FormatFloat(saleformat,checked);
		etaddcost->Text=FormatFloat(saleformat,AddCosts);
		etleftmoney->Text=FormatFloat(saleformat,bance);
		etcount->Text=FormatFloat(saleformat,s);
	}
	Querydetail->Close();
        DBGridbase->DataSource->DataSet->EnableControls();
}
//---------------------------------------------------------------------------

void __fastcall TAccDetail::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TAccDetail::DBGridbaseCellClick(TColumn *Column)
{
	AnsiString sql;
	if (Querybase->IsEmpty() ) {
		return;
	}
	if (Querybase->RecordCount > 0) {
		if (type == 1) {
			sql="select rank() over(order by BS_BookCatalog.id) as xuhao,Convert(varchar(20),HdTime,111) as HdTime,ISBN,Name,Price,PressCount,AbbreviatedName,BS_StorageNote.Amount as Amount,Discount ,FixedPrice,DiscountedPrice  from BS_StorageNote  left join STK_BookInfo on STK_BookInfo.id=BkInfoID left join BS_BookCatalog on STK_BookInfo.BkcatalogID=BS_BookCatalog.id left join BS_StorageNoteHeader on BS_StorageNoteHeader.id=StgNtHeaderID left join bs_pressinfo on bs_bookcatalog.pressid = bs_pressinfo.id where StgNtCode="+Querybase->FieldByName("NtCode")->AsString;
		}
		if (type == 2) {
			sql="select rank() over(order by BS_BookCatalog.id) as xuhao,Convert(varchar(20),HdTime,111) as HdTime,ISBN,Name,Price,PressCount,AbbreviatedName,sum(BS_WsaleNote.Amount) as Amount,avg(Discount) as Discount ,sum(BS_WsaleNote.FixedPrice) as FixedPrice,sum(BS_WsaleNote.DiscountedPrice) as DiscountedPrice from BS_WsaleNote  left join STK_BookInfo on STK_BookInfo.id=BkInfoID left join BS_BookCatalog on STK_BookInfo.BkcatalogID=BS_BookCatalog.id left join BS_WsaleNoteHeader on BS_WsaleNoteHeader.id=WsaleNtHeaderID left join bs_pressinfo on bs_bookcatalog.pressid = bs_pressinfo.id where WsaleNtCode="+Querybase->FieldByName("NtCode")->AsString
			+ " group by BS_BookCatalog.id,HdTime,ISBN,Name,Price,PressCount,AbbreviatedName";
		}
		Querydetail->Close();
		Querydetail->SQL->Clear();
		Querydetail->SQL->Add(sql);
		Querydetail->Open();
		/*DBGriddetail->Columns->Items[0]->Width = 84;
		DBGriddetail->Columns->Items[1]->Width = 120;
		DBGriddetail->Columns->Items[2]->Width = 64;
		DBGriddetail->Columns->Items[3]->Width = 64;
		DBGriddetail->Columns->Items[4]->Width = 64;
		DBGriddetail->Columns->Items[5]->Width = 64;
		DBGriddetail->Columns->Items[6]->Width = 64;
		DBGriddetail->Columns->Items[7]->Width = 64;
		DBGriddetail->Columns->Items[8]->Width = 80;  */
		if (type == 1) {
			((TFloatField *)DBGriddetail->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "##0.00";
			((TFloatField *)DBGriddetail->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "##0.00";
			((TFloatField *)DBGriddetail->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = storageformat;
			((TFloatField *)DBGriddetail->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = storageformat;
			((TFloatField *)DBGriddetail->DataSource->DataSet->FieldByName("Amount"))->DisplayFormat = "###,###,##0";
		}
		else
		{
			((TFloatField *)DBGriddetail->DataSource->DataSet->FieldByName("Price"))->DisplayFormat = "##0.00";
			((TFloatField *)DBGriddetail->DataSource->DataSet->FieldByName("Discount"))->DisplayFormat = "##0.00";
			((TFloatField *)DBGriddetail->DataSource->DataSet->FieldByName("FixedPrice"))->DisplayFormat = saleformat;
			((TFloatField *)DBGriddetail->DataSource->DataSet->FieldByName("DiscountedPrice"))->DisplayFormat = saleformat;
			((TFloatField *)DBGriddetail->DataSource->DataSet->FieldByName("Amount"))->DisplayFormat = "###,###,##0";
		}
	}
}
//---------------------------------------------------------------------------


void __fastcall TAccDetail::FormClose(TObject *Sender, TCloseAction &Action)
{
  Action = caFree ;
}
//---------------------------------------------------------------------------

bool __fastcall TAccDetail::DbgridToExcel(TRzDBGrid* dbg)
{



	AnsiString temptext,path;
        bool dantou=true;
        bool mixi =true;
        double totaldis,totalfix;
        int totalamount;
	savedlg->FileName = CBcustom->Text + "(" + this->Caption + ")";


	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = Sysutils::ExtractFilePath(savedlg->FileName .c_str());
		Name = Sysutils::ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".xls";
		path =  DBPath;
	}
	else
	{
		return false;
	}
	int  iFileHandle;
	int   iFileLength;
	if(FileExists(path))
	   DeleteFileA(path);



          Screen->Cursor = crHourGlass;




            Variant vExcelApp, vSheet;
           AnsiString hebing;


    try
    {
        vExcelApp = Variant::CreateObject("Excel.Application");
    }
    catch(...)
    {
        MessageBox(0, "启动 Excel 出错, 可能是没有安装Excel.","ExcelOut", MB_OK | MB_ICONERROR);
       // return;
    }
    try
    {
    // 隐藏Excel界面
    vExcelApp.OlePropertySet("Visible", false);
    // 新建一个工作表
    vExcelApp.OlePropertyGet("Workbooks").OleFunction("Add", 1); // 工作表
    // 操作这个工作表
    vSheet = vExcelApp.OlePropertyGet("ActiveWorkbook")
            .OlePropertyGet("Sheets", 1);
      vSheet.OlePropertyGet("Range","H:I").OlePropertyGet("Columns").OlePropertySet("NumberFormatLocal","@");
       vSheet.OlePropertyGet("Range","A:A").OlePropertyGet("Columns").OlePropertySet("NumberFormatLocal","@");
        int l=1;
        int h=1;
	dbg->DataSource ->DataSet ->First();
	dbg->DataSource ->DataSet->DisableControls();
	Querydetail->DisableControls();
	while(!Querybase->Eof)
	{
            //写入单头
            temptext = "发货单号";
             vSheet.OlePropertyGet("Cells", l, h).OlePropertySet("Value",temptext.c_str());
             temptext = "数量";
             vSheet.OlePropertyGet("Cells", l, h+5).OlePropertySet("Value",temptext.c_str());
             temptext = "码洋";
             vSheet.OlePropertyGet("Cells", l, h+7).OlePropertySet("Value",temptext.c_str());
             temptext = "实洋";
             vSheet.OlePropertyGet("Cells", l, h+8).OlePropertySet("Value",temptext.c_str());
             temptext = "日期";
             vSheet.OlePropertyGet("Cells", l, h+9).OlePropertySet("Value",temptext.c_str());
             temptext = "备注";
             vSheet.OlePropertyGet("Cells", l, h+10).OlePropertySet("Value",temptext.c_str());
                l++; //下一行
             //写入单头数据
               temptext = Querybase->FieldByName("CodeStr")->AsAnsiString ;
             vSheet.OlePropertyGet("Cells", l, h).OlePropertySet("Value",temptext.c_str());
             temptext = Querybase->FieldByName("TotalAmount")->AsAnsiString ;
             vSheet.OlePropertyGet("Cells", l, h+5).OlePropertySet("Value",temptext.c_str());
             temptext = Querybase->FieldByName("FixedPrice")->AsAnsiString ;
             vSheet.OlePropertyGet("Cells", l, h+7).OlePropertySet("Value",temptext.c_str());
             temptext =Querybase->FieldByName("DiscountedPrice")->AsAnsiString ;
             vSheet.OlePropertyGet("Cells", l, h+8).OlePropertySet("Value",temptext.c_str());
             temptext = Querybase->FieldByName("HdTime")->AsAnsiString ;
             vSheet.OlePropertyGet("Cells", l, h+9).OlePropertySet("Value",temptext.c_str());
             temptext = Querybase->FieldByName("Remarks")->AsAnsiString ;
             vSheet.OlePropertyGet("Cells", l, h+10).OlePropertySet("Value",temptext.c_str());

             l++;


		if (type == 1) {
			sql="select rank() over(order by BS_BookCatalog.id) as xuhao,Convert(varchar(10),HdTime,120) as HdTime,ISBN,Name,Price,PressCount,AbbreviatedName,BS_StorageNote.Amount as Amount,Discount ,FixedPrice,DiscountedPrice  from BS_StorageNote  left join BS_BookCatalog on BS_StorageNote.BkcatalogID=BS_BookCatalog.id left join BS_StorageNoteHeader on BS_StorageNoteHeader.id=StgNtHeaderID left join bs_pressinfo on bs_bookcatalog.pressid = bs_pressinfo.id where BS_StorageNoteHeader.id="+Querybase->FieldByName("ID")->AsString;
		}
		if (type == 2) {
			sql="select rank() over(order by BS_BookCatalog.id) as xuhao,Convert(varchar(10),HdTime,120) as HdTime,ISBN,Name,Price,PressCount,AbbreviatedName,BS_WsaleNote.Amount as Amount,Discount ,BS_WsaleNote.FixedPrice,BS_WsaleNote.DiscountedPrice  from BS_WsaleNote   left join BS_BookCatalog on BS_WsaleNote.BkcatalogID=BS_BookCatalog.id left join BS_WsaleNoteHeader on BS_WsaleNoteHeader.id=WsaleNtHeaderID left join bs_pressinfo on bs_bookcatalog.pressid = bs_pressinfo.id where BS_WsaleNoteHeader.id="+Querybase->FieldByName("ID")->AsString;
		}
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		//temptext = "\n";
                aq->First();
		while(!aq->Eof)
                {
                         //写入明细单头        第一次需要写入标头
                         if (dantou) {
                                temptext = "ISBN";
                                vSheet.OlePropertyGet("Cells", l, 1).OlePropertySet("Value",temptext.c_str());
                                temptext = "书名";
                                vSheet.OlePropertyGet("Cells", l, 2).OlePropertySet("Value",temptext.c_str());
                                temptext = "定价";
                                vSheet.OlePropertyGet("Cells", l, 3).OlePropertySet("Value",temptext.c_str());
                                temptext = "出版社";
                                vSheet.OlePropertyGet("Cells", l, 4).OlePropertySet("Value",temptext.c_str());
                                temptext = "版次";
                                vSheet.OlePropertyGet("Cells", l, 5).OlePropertySet("Value",temptext.c_str());
                                temptext = "数量";
                                vSheet.OlePropertyGet("Cells", l, 6).OlePropertySet("Value",temptext.c_str());
                                temptext = "折扣%";
                                vSheet.OlePropertyGet("Cells", l, 7).OlePropertySet("Value",temptext.c_str());
                                temptext = "码洋";
                                vSheet.OlePropertyGet("Cells", l, 8).OlePropertySet("Value",temptext.c_str());
                                temptext = "实洋";
                                vSheet.OlePropertyGet("Cells", l, 9).OlePropertySet("Value",temptext.c_str());

                       dantou=false;

                       l++;
                 }else    //写入数据
                 {
                                temptext = aq->FieldByName("ISBN")->AsAnsiString ;
                                vSheet.OlePropertyGet("Cells", l, 1).OlePropertySet("Value",temptext.c_str());
                                temptext =   aq->FieldByName("Name")->AsAnsiString ;
                                vSheet.OlePropertyGet("Cells", l, 2).OlePropertySet("Value",temptext.c_str());
                                temptext =   aq->FieldByName("Price")->AsAnsiString ;
                                vSheet.OlePropertyGet("Cells", l, 3).OlePropertySet("Value",temptext.c_str());
                                temptext =    aq->FieldByName("AbbreviatedName")->AsAnsiString ;
                                vSheet.OlePropertyGet("Cells", l, 4).OlePropertySet("Value",temptext.c_str());
                                temptext =      aq->FieldByName("PressCount")->AsAnsiString ;
                                vSheet.OlePropertyGet("Cells", l, 5).OlePropertySet("Value",temptext.c_str());
                                temptext =      aq->FieldByName("Amount")->AsAnsiString ;
                                vSheet.OlePropertyGet("Cells", l, 6).OlePropertySet("Value",temptext.c_str());
                                temptext =    aq->FieldByName("Discount")->AsAnsiString ;
                                vSheet.OlePropertyGet("Cells", l, 7).OlePropertySet("Value",temptext.c_str());
                                temptext =       aq->FieldByName("FixedPrice")->AsAnsiString ;
                                vSheet.OlePropertyGet("Cells", l, 8).OlePropertySet("Value",temptext.c_str());
                                temptext =     aq->FieldByName("DiscountedPrice")->AsAnsiString ;
                                vSheet.OlePropertyGet("Cells", l, 9).OlePropertySet("Value",temptext.c_str());
                                l++;


                  aq->Next();
                 }
                   // vSheet.OlePropertyGet("Range","H:I")




                }
            Querybase->Next();

	}

            temptext = "合计";
            vSheet.OlePropertyGet("Cells", l, 1).OlePropertySet("Value",temptext.c_str());
             temptext = IntToStr(ta);
            vSheet.OlePropertyGet("Cells", l, 6).OlePropertySet("Value",temptext.c_str());
            temptext =  FormatFloat("0.00",tf);
            vSheet.OlePropertyGet("Cells", l, 8).OlePropertySet("Value",temptext.c_str());
            temptext =  FormatFloat("0.00",td);
            vSheet.OlePropertyGet("Cells", l, 9).OlePropertySet("Value",temptext.c_str());
        Variant R,EBorders;
        AnsiString kl;
        kl = "A1:K"+IntToStr(l);

         R = vSheet.OlePropertyGet("Range",kl.c_str()); //取得合并的区域
                    EBorders = R.OlePropertyGet("Borders");
                    EBorders.OlePropertySet("linestyle",1);
                    EBorders.OlePropertySet("weight",2);
	Querydetail->EnableControls();
	dbg->DataSource ->DataSet->EnableControls();
         vExcelApp.OlePropertyGet("ActiveWorkbook")
            .OleFunction("SaveAs", path.c_str());

    vExcelApp.OleFunction("Quit");
    Screen->Cursor = crDefault;
       // ShowMsg(Handle ,"导出完毕！",3);
        ShowMsg(Handle ,"导出完毕！",3);

       }catch(...)
       {
          ShowMsg(Handle ,"导出失败！",3);
       }
       	//return false;
}

//---------------------------------------------------------------------------

void TAccDetail::PrintFunction(int  type)
{
					 //预览
	// AnsiString sql;
   /*	 sql = " select RANK() OVER(order by B.ID desc) as xuhao,A.HdTime,A.WsaleNtCode,A.FixedPrice,A.DiscountedPrice, "
		  " A.TotalAmount,A.Checked,B.discount,A.Nochecked,BS_BookCatalog.Name as bookname,BS_BookCatalog.Price,BS_BookCatalog.ISBN "
		  " ,p.abbreviatedName,B.Amount,B.Discount,B.fixedprice,B.discountedprice from BS_WsaleNoteHeader A "
		  " join BS_WsaleNote B ON A.ID = B.WsaleNtHeaderID  join STK_BookInfo on STK_BookInfo.id=BkInfoID "
		  " join BS_BookCatalog on BkcatalogID=BS_BookCatalog.id left join BS_PressInfo P on P.ID = BS_BookCatalog.pressID ";
	 sql = sql + sqlwhere;    */
	 if (Querybase->IsEmpty()) {
         return;
	 }
	  aqprint->Close();
	  aqprint->SQL->Clear();
	  aqprint->SQL->Add(sql1);
	  aqprint->Open();
       //	RvSystem1->SystemSetups >>ssAllowSetup;
       ///	RvSystem1->SystemSetups >>ssAllowDestPreview;
       //	RvSystem1->SystemSetups >>ssAllowDestPrinter;
       //	RvSystem1->SystemSetups >>ssAllowPrinterSetup;
       //	RvSystem1->SystemSetups >>ssAllowDestFile;
	if (type==1) {
		RvSystem1->DefaultDest   = rdPreview  ;
	}else
	{
		RvSystem1->DefaultDest   = rdPrinter ;
	}
	//RvSystem1->DefaultDest = rdFile ;
	//RvSystem1->OutputFileName = "D://FYingShouDetail.html";
	RvSystem1->SystemSetups<<ssAllowDestPrinter;
  //
		RvProject1->ProjectFile = ExtractFilePath(Application->ExeName) + "FYingShouDetail.rav";
		RvProject1->Open();



		if (type1 == 1)
		{
		RvProject1->SetParam("title",stogName+"应付明细");
		RvProject1->SetParam("supplier","供应商："+CBcustom->Text);
		}
		if (type1 == 2) {
		 {
		  RvProject1->SetParam("supplier","客户："+CBcustom->Text);}
			RvProject1->SetParam("title",stogName+"应收明细");
		}

		RvProject1->SetParam("maker",Maker);
		RvProject1->SetParam("jiekuan",CBstate->Text);
		if (CBstart->Checked) {
		  RvProject1->SetParam("begin",DateToStr(DTPstart->Date));
		}
		if (CBend->Checked) {
		  RvProject1->SetParam("end",DateToStr(DTPend->Date));
		}
		RvProject1->SetParam("yihu",etcount->Text);
		RvProject1->Execute();
   }



void __fastcall TAccDetail::edqueryKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		AnsiString sql;
		if (type == 1) {
			sql = "select ID,Name from CUST_CustomerInfo where type = 1  and customerstate=1 and Name like '%" + edquery->Text + "%' and name <> '' ";
        	aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			CBcustom->Clear();
			while (!aq->Eof )
			{
				CBcustom->AddItem(aq->FieldByName("Name")->AsString,(TObject*)aq->FieldByName("ID")->AsInteger );
				aq->Next();
			}
			aq->First();
			CBcustom->ItemIndex = CBcustom->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger);
		}
		else
		{
			sql = "select ID,Name from CUST_CustomerInfo where type in(2,3)  and customerstate=1  and Name like '%" + edquery->Text + "%' and name <> '' ";
        	aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			CBcustom->Clear();
			while (!aq->Eof )
			{
				CBcustom->AddItem(aq->FieldByName("Name")->AsString,(TObject*)aq->FieldByName("ID")->AsInteger );
				aq->Next();
			}
			aq->First();
			CBcustom->ItemIndex = CBcustom->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TAccDetail::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TAccDetail::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
    if (Key == VK_F6 ) {    //导入
		BtnExport->Click();
	}
	if (Key == VK_F7 ) {    //预览
		BtnPrintPreview->Click();
	}
	if (Key == VK_F8 ) {    //打印
		BtnPrint->Click();
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


void __fastcall TAccDetail::DTPstartChange(TObject *Sender)
{
	CBstart->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TAccDetail::DTPendChange(TObject *Sender)
{
	CBend->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TAccDetail::DBGridbaseTitleClick(TColumn *Column)
{
	if (Querybase->IsEmpty() ) {
    	return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (Querybase->Sort == "") {
		Querybase->Sort =  Column->FieldName + " ASC";
	}
	else if (Querybase->Sort == qusort) {
		Querybase->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		Querybase->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall TAccDetail::DBGriddetailTitleClick(TColumn *Column)
{
	if (Querydetail->IsEmpty() ) {
    	return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (Querydetail->Sort == "") {
		Querydetail->Sort =  Column->FieldName + " ASC";
	}
	else if (Querydetail->Sort == qusort) {
		Querydetail->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		Querydetail->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall TAccDetail::N1Click(TObject *Sender)
{
PrintFunction(1);
}
//---------------------------------------------------------------------------

void __fastcall TAccDetail::N3Click(TObject *Sender)
{
PrintFunction(2);
}
 AnsiString TAccDetail::GetSearchID()
 {
    AnsiString IDstr;
    IDstr= "(-1";
    for (int i= 0; i < Querybase->RecordCount; i++) {
    IDstr = IDstr +","+ Querybase->FieldByName("id")->AsAnsiString ;
    Querybase->Next();
    }
    IDstr = IDstr+")";
    return IDstr;
 }
//---------------------------------------------------------------------------


void __fastcall TAccDetail::frxReport1GetValue(const UnicodeString VarName, Variant &Value)

{
	//ShowMessage(VarName);
	//传递宽度
	if (CompareText(VarName,"\"xuhao\"")==0  ) {  //序号
		 Value = FindTitlewith("xuhao");
	}
      //	if (CompareText(VarName,"\"incode\"")==0  ) {  //内部识别码
       //		 Value = FindTitlewith("incode");
       //	}
	if (CompareText(VarName,"\"ISBN\"")==0  ) {    //书号
		Value = FindTitlewith("ISBN");
	}
	if (CompareText(VarName,"\"CatalogName\"")==0 ) {   //书名
		Value = FindTitlewith("CatalogName");
	}
	if (CompareText(VarName,"\"Price\"")==0 ) {   //定价
		Value = FindTitlewith("Price");
	}
	if (CompareText(VarName,"\"Author\"")==0 ) {  //作者
		Value = FindTitlewith("Author");
	}
	if (CompareText(VarName,"\"AbbreviatedName\"")==0 ) {    //出版社
		Value = FindTitlewith("AbbreviatedName");
	}
    //	if (CompareText(VarName,"\"Pressdate\"")==0 ) {   //出版日期
     //		Value = FindTitlewith("Pressdate");
     //	}
	if (CompareText(VarName,"\"PressCount\"")==0 ) {  //版次
		Value = FindTitlewith("PressCount");
	}
       //	if (CompareText(VarName,"\"BookWords\"")==0 ) {    //册/包
       //		Value = FindTitlewith("BookWords");
       //	}
	if (CompareText(VarName,"\"Amount\"")==0 ) {      //数量
		Value = FindTitlewith("Amount");
	}
	if (CompareText(VarName,"\"Discount\"")==0 ) {     //折扣
		Value = FindTitlewith("Discount");
	}
	if (CompareText(VarName,"\"FixedPrice\"")==0 ) {   //码洋
		Value = FindTitlewith("FixedPrice");
	}
	if (CompareText(VarName,"\"DiscountedPrice\"")==0 ) {        //实洋
		Value = FindTitlewith("DiscountedPrice");
	}
      /*	if (CompareText(VarName,"\"huojiangstate\"")==0 ) {   //获奖情况
		Value = FindTitlewith("huojiangstate");
	}
       	if (CompareText(VarName,"\"xiaoqu\"")==0 ) {   //校区
       		Value = FindTitlewith("xiaoqu");
      	}
       	if (CompareText(VarName,"\"xueyuan\"")==0 ) {        //学院
       		Value = FindTitlewith("xueyuan");
      	}
       	if (CompareText(VarName,"\"course\"")==0 ) {   //课程名称
       		Value = FindTitlewith("course");
       	}        */

	//传递参数
	if (CompareText(VarName,"\"title\"")==0 ) {

			Value = stogName + "对帐单";

	}
    //	if (CompareText(VarName,"\"yingshou\"")==0 ) {
	//	  Value = FormatFloat("￥0.00",yingshou);
       //	}
      /*	if (CompareText(VarName,"\"fandian\"")==0 ) {
		  Value = FormatFloat("￥0.00",fandian); Totaladdcosts= FormatFloat(storageformat,aq->FieldByName("totaladdcosts")->AsFloat);
            TotalHuikuan
	}*/
        	if (CompareText(VarName,"\"Totaladdcosts\"")==0 ) {
		  Value = Totaladdcosts;
	}
        	if (CompareText(VarName,"\"TotalNoChecked\"")==0 ) {
		  Value = TotalNoChecked;
	}
        	if (CompareText(VarName,"\"TotalChecked\"")==0 ) {
		  Value = TotalChecked;
	}
	if (CompareText(VarName,"\"contact\"")==0 ) {
		  Value = contact;
	}
	if (CompareText(VarName,"\"telephone\"")==0 ) {
		  Value =telephone;
	}
	if (CompareText(VarName,"\"Address\"")==0 ) {
		  Value = address;
	}
	if (CompareText(VarName,"\"ClientName\"")==0 ) {
		  Value = ClientName;
	}
	if (CompareText(VarName,"\"heji\"")==0 ) {
		  Value = TotalFixDaxie;
	}
        	if (CompareText(VarName,"\"totalamount\"")==0 ) {
		  Value =TotalAmount;
	}
        	if (CompareText(VarName,"\"totalfixedprice\"")==0 ) {
		  Value = TotalFix;
	}
        	if (CompareText(VarName,"\"totaldiscountedprice\"")==0 ) {
		  Value = TotalDis;
	}

          	if (CompareText(VarName,"\"stgmaker\"")==0 ) {
		  Value = user;
	}
               //stgcontact
               	if (CompareText(VarName,"\"stgcontact\"")==0 ) {
		  Value = stgcontact;
                }
          	if (CompareText(VarName,"\"stgtel\"")==0 ) {
		  Value = stgtel;
	}

          	if (CompareText(VarName,"\"stgaddress\"")==0 ) {
		  Value = stgaddress;
	}

          	if (CompareText(VarName,"\"stgpxbk\"")==0 ) {
		  Value = "";
	}
}
void TAccDetail::GetPrintWith()
{
   	struct PrintControl *item;
		PrintTile = new TStringList(NULL);
		// PrintTile->AddObject();
        AnsiString sql;
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		sql = "select * from sys_bsset where name = 'salexiaoshudian'" ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		format = aq->FieldByName("bk")->AsAnsiString ;
		if (format.Length() == 0) {
			format = "%2.0f";
			format1 = "0";
		}
		else if (format.Length() == 3) {
			format = "%2.1f";
			format1 = "0.0";
		}
		else if (format.Length() == 4) {
			format = "%2.2f";
			format1 = "0.00";
		}
		else if (format.Length() == 5) {
			format = "%2.3f";
			format1 = "0.000";
		}
		else if (format.Length() == 6) {
			format = "%2.4f";
			format1 = "0.0000";
		}
		delete aq;

		AnsiString ps;
		TADOQuery *aptitle = new TADOQuery(NULL);
		aptitle->Connection = fcon ;
		aptitle->Close();
		aptitle->SQL->Clear();



                sql = "select sys_printdetail.*,sys_printhead.typename from sys_printdetail left join sys_printhead on sys_printdetail.headid = sys_printhead.id where sys_printdetail.[print] = 1 and sys_printhead.modle = 1 and sys_printhead.active = 1 and sys_printhead.stgid =0 order by sys_printdetail.id";
		aptitle->SQL->Add(sql);
		aptitle->Open();
		while(!aptitle->Eof)
		{
			item = new PrintControl();
			item->name = aptitle->FieldByName("name")->AsAnsiString ;
			item->width = aptitle->FieldByName("with")->AsFloat ;
			PrintTile->AddObject(aptitle->FieldByName("columnname")->AsAnsiString ,(TObject*)item);
			aptitle->Next();
		}
                PrintTile->IndexOf("FixedPrice");
                delete aptitle;


}
void TAccDetail::PrintReport(int mode)
{
     AnsiString sql,sql1,sql2;
             AnsiString sqlstg;
             AnsiString sqlclient;
             int clientid;
             if (CBcustom->ItemIndex==-1) {
                  ShowMsg(Handle ,"请选择客户或供应商！",3);
             return ;
             }
             clientid =  (int)CBcustom->Items->Objects[CBcustom->ItemIndex];
             sqlclient = "select name, address,telephone,fax,contact from dbo.CUST_CustomerInfo where id =  "+ IntToStr(clientid);
             if (type == 1) {//供应商
              sql1 = "select sum(TotalAmount) as totalamount,sum(totalfixedprice) as totalfixedprice,sum(totaldiscountedprice) as totaldicountedprice ,sum(addcosts) as totaladdcosts,sum(nochecked) as nochecked,sum(checked) as checked from dbo.BS_StorageNoteHeader where id in "+getheaderid+" and stgid="+IntToStr(fstgid);
              sql += " select   RANK() OVER(order by StorageNoteID desc) as xuhao,StorageNoteID as NoteID,StorageNoteStgNtHeaderID as wsaleNtHeaderID,StorageNoteHeaderStgNtCodeStr as wsaleNtCodeStr, ";
              sql += "  StorageNoteHeaderHdTime as WsaleNoteHeaderHdTime,bookcatalogISBN as ISBN,bookcatalogName as CatalogName,BookcatalogPrice as price,bookcatalogAuthor as author,b.abbreviatedName as AbbreviatedName,storageNoteAmount  as amount,StorageNoteDiscount as Discount, ";
               sql += " StorageNoteFixedPrice as FixedPrice, ";
              sql += " StorageNoteDiscountedPrice as  DiscountedPrice,storageNoteHeaderRemarks as remarks,'已结'+cast(StorageNoteHeaderChecked as varchar(40)) +' 未结'+ cast(StorageNoteHeaderNochecked as varchar(40)) as jinkuanqingkuang,storageNoteHeaderAddcosts as addcosts from dbo.UV_QryStorageNote a left join dbo.BS_PressInfo b on a.bookcatalogPressID = b.id where  StorageNoteStgNtHeaderID in "+getheaderid+" and storageNoteHeaderStgID="+IntToStr(fstgid)+" order by wsaleNtCodeStr ";
             }else if (type==2) {//客户
               sql1 = "select sum(TotalAmount) as totalamount,sum(fixedprice) as totalfixedprice,sum(discountedprice) as totaldicountedprice,sum(addcosts) as totaladdcosts,sum(nochecked) as nochecked,sum(checked) as checked from dbo.BS_WsaleNoteHeader where id in "+getheaderid+" and stgid="+IntToStr(fstgid);
               sql = "select RANK() OVER(order by substring(wsaleNtCodeStr,1,2)  desc,wsalentheaderid) as xuhao,wsaleNoteID as NoteID,wsaleNtHeaderID,wsaleNtCodeStr,WsaleNoteHeaderHdTime,bookcatalogISBN as ISBN,bkcatalogName as CatalogName,BookcatalogPrice as price,bookcatalogAuthor as author,pressAbbName as AbbreviatedName,";
               sql = sql +" '' Pressdate,bookcatalogpresscount as PressCount,wsalenoteamount as amount,wsalenotediscount as Discount,wsalenotefixedprice as FixedPrice,wsalenotediscountedprice as  DiscountedPrice, wsaleNoteHeaderRemarks as remarks,'已结'+cast(wsaleNoteHeaderChecked as varchar(40)) +' 未结'+ cast(wsaleNoteHeaderNochecked as varchar(40)) as jinkuanqingkuang,wsaleNoteHeaderAddCosts as addcosts from dbo.UV_QryWsaleNote  where  wsaleNtHeaderID in "+getheaderid+" and wsaleNoteHeaderStgID="+IntToStr(fstgid)+" order by substring(wsaleNtCodeStr,1,2)  desc,wsalentheaderid";
             }


             aqprint->Connection = fcon;
             aqprint->Close();
             aqprint->SQL->Clear();
             aqprint->SQL->Add(sql);
             aqprint->Open();
            TADOQuery *aq = new TADOQuery(Application);
            aq->Connection = fcon;
            aq->Close();
            aq->SQL->Clear();
            aq->SQL->Add(sql1);
            aq->Open();               //统计
            TotalAmount = aq->FieldByName("totalamount")->AsAnsiString;
            TotalDis =  FormatFloat(storageformat,aq->FieldByName("totaldicountedprice")->AsFloat);;


            TotalFix  = FormatFloat(storageformat,aq->FieldByName("totalfixedprice")->AsFloat) ;

            Totaladdcosts= FormatFloat(storageformat,aq->FieldByName("totaladdcosts")->AsFloat);
           // TotalHuikuan = FormatFloat(storageformat,aq->FieldByName("totaladdcosts")->AsFloat+aq->FieldByName("totaldicountedprice")->AsFloat);
            TotalChecked =  FormatFloat(storageformat,aq->FieldByName("checked")->AsFloat);
            TotalNoChecked = FormatFloat(storageformat,aq->FieldByName("nochecked")->AsFloat);

            TotalFixDaxie = Doubletostring(StrToFloat(TotalDis));

            aq->Close();
            aq->SQL->Clear();
            aq->SQL->Add(sqlclient);
            aq->Open();           //客户资料

           ClientName = aq->FieldByName("name")->AsAnsiString;
           telephone =  aq->FieldByName("telephone")->AsAnsiString;
           contact =   aq->FieldByName("contact")->AsAnsiString;
           address =aq->FieldByName("address")->AsAnsiString;
           // AnsiString pxbk,rkbk,ClientName,supplycode,printtitle,contact,tel,address,shaddress,shtel,shcontact;

          sqlstg = " select * from dbo.SYS_StorageInfo where id ="+IntToStr(fstgid);
          aq->Close();
          aq->SQL->Clear();
          aq->SQL->Add(sqlstg);
          aq->Open();

         // stgname,stgtel,stgaddress;           //书店资料
              stgname = aq->FieldByName("name")->AsAnsiString;
           stgtel =  aq->FieldByName("tel")->AsAnsiString;
           stgcontact =   aq->FieldByName("contact")->AsAnsiString;
           stgaddress =aq->FieldByName("address")->AsAnsiString;

          delete aq;
GetPrintWith();
   if (mode==1) {//预览
            frxReport1->LoadFromFile(Sysutils::ExtractFilePath(Application->ExeName)+"duizhangprint.fr3");
     frxReport1->PrepareReport(true);                                           //
     frxReport1->ShowPreparedReport();
   }else
   {
           frxReport1->LoadFromFile(Sysutils::ExtractFilePath(Application->ExeName)+"duizhangprint.fr3");
     frxReport1->PrepareReport(true);                                           //
     frxReport1->Print();
   }


}
AnsiString TAccDetail::Touppnum(AnsiString ychar)
{
   	AnsiString mchar;
	if (ychar == "") {
    	return " ";
	}
	int i;
	try {
		i = StrToInt(ychar);
	} catch (...) {
		return " ";
	}
	switch (i) {
		case 0:
			mchar = "零";
		break;
		case 1:
			mchar = "壹";
		break;
		case 2:
			mchar = "贰";
		break;
		case 3:
			mchar = "叁";
		break;
		case 4:
			mchar = "肆";
		break;
		case 5:
			mchar = "伍";
		break;
		case 6:
			mchar = "陆";
		break;
		case 7:
			mchar = "柒";
		break;
		case 8:
			mchar = "捌";
		break;
		case 9:
			mchar = "玖";
		break;
    default:
		;
	}
	return mchar;





}
AnsiString TAccDetail::Doubletostring(double num)
{
      AnsiString outnum,ychar,outstring,outzs,outxs;
	outnum = FormatFloat(format1,num);
	outzs = outnum.SubString(0,outnum.Pos(".")-1);
	outxs = outnum.SubString(outnum.Pos(".") + 1,2);
	//outnum = outnum.SubString(0,outnum.Pos(".")-1) + outnum.SubString(outnum.Pos(".")+1,2);

	AnsiString danwei[8] = {"仟","佰","拾","万","仟","佰","拾","元"};
	int len = outzs.Length() ;
	for (int i = 0; i < 8; i++) {
		if (len < 8-i) {

		}
		else
		{
			if (outzs.SubString(len-7 + i,1) == "-") {
				outstring = "负";
			}
			else
			{
				outstring = outstring + Touppnum(outzs.SubString(len-7 + i,1)) + danwei[i];
			}
		}
	}
	AnsiString danwei1[2] = {"角","分"};
	len = outxs.Length() ;
	for (int i = 0; i < len; i++) {
		outstring = outstring + Touppnum(outxs.SubString(i+1,1)) + danwei1[i];
	}
	return  outstring;

}
AnsiString TAccDetail::FindTitleName(AnsiString ColumnName)
{
     	int i;
	i =  PrintTile->IndexOf(ColumnName);
	if (i != -1 ) {
		  return ((PrintControl*)PrintTile->Objects[i])->name ;
	}else return "NOTITLE";
}
float TAccDetail::FindTitlewith(AnsiString ColumnName)
{
          int i;
	i =  PrintTile->IndexOf(ColumnName);
	if (i != -1 ) {
		  return ((PrintControl*)PrintTile->Objects[i])->width ;
	}else return 0;

}

//---------------------------------------------------------------------------

void __fastcall TAccDetail::N2Click(TObject *Sender)
{
PrintReport(1);
}
//---------------------------------------------------------------------------

void __fastcall TAccDetail::N4Click(TObject *Sender)
{
    PrintReport(2);
}
//---------------------------------------------------------------------------


bool __fastcall TAccDetail::DbgridToExceler(TRzDBGrid* dbg)
{
  	AnsiString temptext,path;

	savedlg->FileName = CBcustom->Text + "(汇总单)";

       Variant vExcelApp, vSheet;
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = Sysutils::ExtractFilePath(savedlg->FileName .c_str());
		Name = Sysutils::ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".xls";
		path =  DBPath;
	}
	else
	{
		return false;
	}
	int  iFileHandle;
	int   iFileLength;
	if(FileExists(path))
	   DeleteFileA(path);
		      //	iFileHandle = FileCreate(path.c_str());



	       //	iFileHandle = FileCreate(path.c_str());
         Screen->Cursor = crHourGlass;
         try
    {
        vExcelApp = Variant::CreateObject("Excel.Application");
    }
    catch(...)
    {
        MessageBox(0, "启动 Excel 出错, 可能是没有安装Excel.","ExcelOut", MB_OK | MB_ICONERROR);
        return false;
    }
    try
    {
    // 隐藏Excel界面
    vExcelApp.OlePropertySet("Visible", false);
    // 新建一个工作表
    vExcelApp.OlePropertyGet("Workbooks").OleFunction("Add", 1); // 工作表
    // 操作这个工作表
    vSheet = vExcelApp.OlePropertyGet("ActiveWorkbook")
            .OlePropertyGet("Sheets", 1);
   





	int t1= 0;
        int l=1,h=1;
	dbg->DataSource ->DataSet ->First();
	dbg->DataSource ->DataSet->DisableControls();
	Querydetail->DisableControls();

               //	temptext = "\n";
		for(int q=0;q<dbg->FieldCount ;++q)
		{
			if (dbg->Columns->Items[q]->Visible == true) {
				t1++;
			       	temptext = dbg->Columns ->Items [q]->Title ->Caption ;

                               vSheet.OlePropertyGet("Cells", l, h).OlePropertySet("Value",temptext.c_str());
                              h++;

			}
		}

                int totalamount=0;
                float  m1=0,m2=0,s=0,f=0,y=0,w=0;
                 dbg->DataSource->DataSet->First();
	while(!dbg->DataSource ->DataSet->Eof)
	{


               totalamount=totalamount+dbg->DataSource ->DataSet ->FieldByName("TotalAmount")->AsInteger;
               m1=m1+dbg->DataSource ->DataSet ->FieldByName("FixedPrice")->AsFloat;
               m2=m2+dbg->DataSource ->DataSet ->FieldByName("DiscountedPrice")->AsFloat;
               s=s+dbg->DataSource ->DataSet ->FieldByName("AddCosts")->AsFloat;
               f=f+dbg->DataSource ->DataSet ->FieldByName("totalyingfu")->AsFloat;
               y=y+dbg->DataSource ->DataSet ->FieldByName("Checked")->AsFloat;
               w=w+dbg->DataSource ->DataSet ->FieldByName("NoChecked")->AsFloat;


                h=1;
                l++;
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
			      	temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString ;

                                vSheet.OlePropertyGet("Cells", l, h).OlePropertySet("Value",temptext.c_str());
                          h++;
			}

		}

                dbg->DataSource->DataSet->Next();

               }

       	Querydetail->EnableControls();
	dbg->DataSource ->DataSet->EnableControls();

        temptext = "合计";
         vSheet.OlePropertyGet("Cells", l+1, 1).OlePropertySet("Value",temptext.c_str());
        temptext = IntToStr(totalamount);
        vSheet.OlePropertyGet("Cells", l+1, 4).OlePropertySet("Value",temptext.c_str());
        temptext = FloatToStr(m1);
        vSheet.OlePropertyGet("Cells", l+1, 5).OlePropertySet("Value",temptext.c_str());

        temptext =  FloatToStr(m2);
        vSheet.OlePropertyGet("Cells", l+1, 6).OlePropertySet("Value",temptext.c_str());
        temptext = FloatToStr(s);
        vSheet.OlePropertyGet("Cells", l+1, 7).OlePropertySet("Value",temptext.c_str());
        temptext = FloatToStr(f);
        vSheet.OlePropertyGet("Cells", l+1, 8).OlePropertySet("Value",temptext.c_str());
        temptext = FloatToStr(y);
        vSheet.OlePropertyGet("Cells", l+1, 9).OlePropertySet("Value",temptext.c_str());
        temptext = FloatToStr(w);
        vSheet.OlePropertyGet("Cells", l+1, 10).OlePropertySet("Value",temptext.c_str());

           Variant R,EBorders;
        AnsiString kl;
        kl = "A1:L"+IntToStr(l+1);

         R = vSheet.OlePropertyGet("Range",kl.c_str()); //取得合并的区域
                    EBorders = R.OlePropertyGet("Borders");
                    EBorders.OlePropertySet("linestyle",1);
                    EBorders.OlePropertySet("weight",2);
         kl = "A"+IntToStr(l+1)+":L"+IntToStr(l+1);
         vSheet.OlePropertyGet("Range",kl.c_str()).OlePropertySet("NumberFormatLocal","@");
        vExcelApp.OlePropertyGet("ActiveWorkbook")
            .OleFunction("SaveAs", path.c_str());

    vExcelApp.OleFunction("Quit");

    vSheet = Unassigned;
    vExcelApp = Unassigned;
        }catch(...)
        { ShowMsg(Handle ,"导出失败！",3);}
    Screen->Cursor = crDefault;
        ShowMsg(Handle ,"导出完毕！",3);

}

void __fastcall TAccDetail::N6Click(TObject *Sender)
{
//

	if (Querybase->IsEmpty() ) {
		return;
	}
       DbgridToExcel(DBGridbase);
       /*
       	savedlg->FileName = CBcustom->Text + "(" + this->Caption + ")";

       // String DBPath,Name;

	if (savedlg->Execute())
	{
		AnsiString DBPath,Name;
		DBPath = Sysutils::ExtractFilePath(savedlg->FileName .c_str());
		Name = Sysutils::ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".xls";
                 ExcelOut(Querybase,DBGridbase,DBPath);
	       //	path =  DBPath;
	}    */


}
void  TAccDetail::ExcelOut(TADOQuery *adoquery,TDBGrid *dbg,AnsiString strfile)
{  // Sleep(2000);
    if(!adoquery->Active) // 数据集没有打开就返回
        return;
    Variant vExcelApp, vSheet;


    try
    {
        vExcelApp = Variant::CreateObject("Excel.Application");
    }
    catch(...)
    {
        MessageBox(0, "启动 Excel 出错, 可能是没有安装Excel.","ExcelOut", MB_OK | MB_ICONERROR);
        return;
    }
    // 隐藏Excel界面
    vExcelApp.OlePropertySet("Visible", false);
    // 新建一个工作表
    vExcelApp.OlePropertyGet("Workbooks").OleFunction("Add", 1); // 工作表
    // 操作这个工作表
    vSheet = vExcelApp.OlePropertyGet("ActiveWorkbook")
            .OlePropertyGet("Sheets", 1);                             // jdt->Position=3;
    // 设置Excel文档的字体
   /* vSheet.OleProcedure("Select");
    vSheet.OlePropertyGet("Cells").OleProcedure("Select");
    vExcelApp.OlePropertyGet("Selection").OlePropertyGet("Font")
            .OlePropertySet("Size", dbg->Font->Size);
    vExcelApp.OlePropertyGet("Selection").OlePropertyGet("Font")
            .OlePropertySet("Name", dbg->Font->Name.c_str());
    vExcelApp.OlePropertyGet("Selection").OlePropertyGet("Font")
            .OlePropertySet("FontStyle", "常规");
    vSheet.OlePropertyGet("Cells", 1, 1).OleProcedure("Select"); */
    // 表格的行数
    int nRowCount(dbg->DataSource->DataSet->RecordCount + 1);
    nRowCount = nRowCount < 2? 2: nRowCount;
    //  jdt->Position=4;  Sleep(100);
    // 表格的列数
    int nColCount(dbg->Columns->Count);
    nColCount = nColCount < 1? 1: nColCount;
    // 设置单元格的宽度
   // for(int i=0; i<nColCount; i++)
   // {
   //     int nColWidth = dbg->Columns->Items[i]->Width;
    //    vExcelApp.OlePropertyGet("Columns", i + 1)
    //            .OlePropertySet("ColumnWidth", nColWidth / 7);
   // }
  //  jdt->Position=5; Sleep(100);
    // 先将列名写入Excel表格
     AnsiString temx;
    for(int j=0; j<dbg->Columns->Count; j++)
    {
        // 标题行的行高
       // vExcelApp.OlePropertyGet("Rows", 1).OlePropertySet("RowHeight", 20);
       //  jdt->Position=6; Sleep(100);
        //
        if ((j==2)||(j==3)||(j==4)||(j==5)||(j==10)||(j==11)) {


         temx =dbg->Columns->Items[j]->Title->Caption ;
        vSheet.OlePropertyGet("Cells", 1, j + 1)
                .OlePropertySet("Value",
                temx.c_str());
        }
        // 设置列名单元格的背景色
       // Variant vInter = vSheet.OlePropertyGet(
       //         "Cells", 1, j + 1).OlePropertyGet("Interior");
       // vInter.OlePropertySet("ColorIndex", 15); // 灰色
       // vInter.OlePropertySet("Pattern", 1); // xlSolid
       // vInter.OlePropertySet("PatternColorIndex", -4105); // xlAutomatic
    }
     // jdt->Position=7;Sleep(100);
    // 将DBGrid中的数据写入Excel表格


    adoquery->First();
    float t=0;

        //t=t+90.0/nRowCount;
       // jdt->Position=7+(int)t; Sleep(100);
        // 普通数据行的行高16
       // vExcelApp.OlePropertyGet("Rows", i + 2).OlePropertySet("RowHeight", 16);
        // 63 63 72 75 6E 2E 63 6F 6D

        for(int   i=2;i< dbg->Columns->Count ;i++)
	{
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
                     if ((j==2)||(j==3)||(j==4)||(j==5)||(j==10)||(j==11)) {

			vSheet.OlePropertyGet("Cells",i,j).OlePropertySet("Value",dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString .c_str() );  // AsString .c_str()

                     }
		}
		dbg->DataSource ->DataSet ->Next() ;
	}

   // jdt->Position=98;  Sleep(100);
    // 保存Excel文档并退出
    vExcelApp.OlePropertyGet("ActiveWorkbook")
            .OleFunction("SaveAs", strfile.c_str());

    vExcelApp.OleFunction("Quit");
    
    vSheet = Unassigned;
    vExcelApp = Unassigned;
   // jdt->Position=98;
    // 工作结束
    MessageBox(0, "导出EXCEL结束!","ExcelOut", MB_OK | MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------

void __fastcall TAccDetail::N5Click(TObject *Sender)
{
	if (Querybase->IsEmpty() ) {
		return;
	}
	DbgridToExceler(DBGridbase);
}
//---------------------------------------------------------------------------

