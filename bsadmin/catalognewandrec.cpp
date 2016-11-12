//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
 #include "WholesaleMngForm.h"
#include "catalognewandrec.h"
#include "bookhistory.h"
#include "global.h"
#include "Selecttype.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "RzDBGrid"
#pragma link "RzDTP"
#pragma resource "*.dfm"
Tfrmcatalogneworrec *frmcatalogneworrec;
//---------------------------------------------------------------------------
__fastcall Tfrmcatalogneworrec::Tfrmcatalogneworrec(TComponent* Owner,TADOConnection *con)
	: TForm(Owner)
{
	aq->Connection = con;
	query->Connection = con;
        adoexec->Connection = con;
	fcon = con;
	AnsiString sql;
	sql = "select ID,AbbreviatedName from BS_PressInfo ";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )
	{
		cbpress->AddItem(aq->FieldByName("AbbreviatedName")->AsString,(TObject *)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
        dtpbegin->Date = Now();
        dtpend->Date = Now();

        clientid = -1;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcatalogneworrec::edqueryKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		AnsiString sql;
		sql = "select ID,AbbreviatedName from BS_PressInfo where AbbreviatedName like '%" + edquery->Text + "%'";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		cbpress->Clear();
		while (!aq->Eof )
		{
        	cbpress->AddItem(aq->FieldByName("AbbreviatedName")->AsString,(TObject *)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		aq->First();
		cbpress->ItemIndex = cbpress->Items->IndexOfObject((TObject *)aq->FieldByName("ID")->AsInteger );
		cbpress->SetFocus();
	}
}
//---------------------------------------------------------------------------
void  Tfrmcatalogneworrec::Query()
{
	AnsiString sql,sqlwhere;
       //	sql = "select RANK() OVER(order by BS_BookCatalog.id) as xuhao,BS_BookCatalog.Name,ISBN,UserDefCode,Price,Author,Pressdate,PressCount,newbook,recomend,year ";
       //	sql = sql + " from BS_BookCatalog left join BS_BookType on BS_BookCatalog.smallBookTypeID = BS_BookType.id ";
       //	sql = sql + " left join BS_PressInfo on BS_BookCatalog.PressID = BS_PressInfo.id ";
        sql = "with TPP as (";
        sql = " SELECT  BS_BookCatalog.id , dbo.BS_BookCatalog.Name, dbo.BS_BookCatalog.UserDefCode,CONVERT(VARCHAR(10),BS_BookCatalog.Pressdate,120) Pressdate, dbo.BS_BookCatalog.Price, dbo.BS_BookCatalog.ISBN, dbo.BS_BookCatalog.Author,"
                     "  dbo.BS_PressInfo.AbbreviatedName,dbo.BS_BookCatalog.PressCount into #TPP"
                     "  FROM  BS_BookCatalog left join "
                     " dbo.BS_StorageNote ON dbo.BS_BookCatalog.ID = dbo.BS_StorageNote.bkcatalogID INNER JOIN "
                     " dbo.BS_StorageNoteHeader ON dbo.BS_StorageNote.StgNtHeaderID = dbo.BS_StorageNoteHeader.ID left JOIN  "
                     " dbo.BS_PressInfo ON dbo.BS_BookCatalog.PressID = dbo.BS_PressInfo.ID  ";
	if (chbookinfo->Checked ) {
	      //	sql = sql + " right join STK_BookInfo on STK_BookInfo.BkcatalogID = BS_BookCatalog.id ";
	}
        if (rg->ItemIndex==0) {
        sql = sql + " where BS_BookCatalog.type in(0,1) and BS_StorageNoteHeader.stgid="+IntToStr(fstgid);
        }else  sql = sql + " where BS_BookCatalog.type =2 and BS_StorageNoteHeader.stgid="+IntToStr(fstgid);

	if (chisbn->Checked) {
		sql = sql + " and (BS_BookCatalog.ISBN like '%" + edisbn->Text + "%' or BS_BookCatalog.Barcode like '%" + edisbn->Text + "%') ";
	}
	if (chname->Checked ) {
		sql = sql + " and BS_BookCatalog.Name like '%" + edname->Text + "%'";
	}
	if (chuserdef->Checked ) {
		sql = sql + " and BS_BookCatalog.UserDefCode like '%" + eduserdef->Text + "%'";
	}
	if (chauthor->Checked ) {
		sql = sql + " and BS_BookCatalog.Author like '%" + edauthor->Text + "%'";
	}
	if (chprice->Checked ) {
		if (edminprice->Text != "") {
			sql = sql + " and BS_BookCatalog.Price >= " + edminprice->Text;
		}
		if (edmaxprice->Text != "") {
			sql = sql + " and BS_BookCatalog.Price <= " + edmaxprice->Text ;
		}
	}
        if (cbruku->Checked) {
           sql = sql + " and datediff(d,'"+DateToStr(dtpbegin->Date) +"',BS_StorageNoteHeader.hdtime)>=0  and datediff(d,BS_StorageNoteHeader.hdtime,'"+DateToStr(dtpend->Date) +"')>=0";
        }
	if (chtype->Checked && edtyname->Text != "" ) {
		sql = sql + " and BS_BookCatalog.smallBookTypeID in(select id from dbo.GetTypeChild(" + IntToStr(TypeID) + ")) ";
	}
	if (chpress->Checked ) {
		int press;
        try {
			press = (int)cbpress->Items->Objects[cbpress->ItemIndex];
		} catch (...) {
			return;
		}
		sql = sql + " and BS_BookCatalog.PressID = " + IntToStr(press);
	}

        if (cbbk->Checked) {//批次查询

            sql = sql + "  and CHARINDEX(SUBSTRING(remarks,CHARINDEX('第',remarks),CHARINDEX('批',remarks)), ";
            sql = sql + "'"+editbk->Text.Trim()+"')>0";
        }


       if (cbbufahuo->Checked) {
             if (clientid==-1) {
                  //  MessageBox(NULL, "请先选择客户!","先行者软件提醒",MB_OK|MB_ICONINFORMATION);
                  //  return;
               }else
               {
                  sql = sql + " and BS_BOOKCATALOG.id not in(select bkcatalogid from Qry_wsalenote where datediff(d,getdate(),hdtime)>=0 and datediff(d,hdtime,getdate())>=0 and  vendorid = "+IntToStr(clientid)+")";
                }
        }else
        {

                sql = sql + " and BS_BOOKCATALOG.id  in(select bkcatalogid from Qry_wsalenote where  vendorid = "+IntToStr(clientid)+")";


        }
	sql = sql + " group by  BS_BookCatalog.id,BS_BookCatalog.Name,BS_PressInfo.AbbreviatedName,BS_BookCatalog.ISBN,BS_BookCatalog.UserDefCode,BS_BookCatalog.Price,BS_BookCatalog.Author,BS_BookCatalog.Pressdate,PressCount;";
        sql = sql +"  select RANK() OVER(order by #TPP.id) as xuhao,sum(s.amount) as kunchenamount,#TPP.*,#TPP.id as bkookcatalogid from STK_BookInfo s  join #TPP on s.bkcatalogid =#TPP.id  ";
        sql = sql + " group by #TPP.id,#TPP.Name,#TPP.AbbreviatedName,#TPP.ISBN,#TPP.UserDefCode,#TPP.Price,#TPP.Author,#TPP.Pressdate,#TPP.PressCount ";

           if (cbkuchen->Checked) {

            if (edit1->Text !="") {
                   sql=sql+"   having sum(s.amount) >="+edit1->Text;

            }
            if (edit2->Text!="") {
                    sql=sql+"  having sum(s.amount) <="+edit2->Text;
            }
            if ((edit1->Text!="")&&(edit2->Text!="")) {
                 sql=sql+"  having sum(s.amount) <="+edit2->Text+" and  sum(s.amount) >="+edit1->Text;
            }
        }

	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql+"; drop table #TPP;");

       // ShowMessage(sql);
	try {

		query->Open();
	} catch (Exception &E) {
    	ShowMessage(E.Message);
		return;
	}
	if (rg->ItemIndex == 0) {
		RzDBGrid1->Columns->Items[1]->Title->Caption = "ISBN";
		RzDBGrid1->Columns->Items[2]->Title->Caption = "书名";
		RzDBGrid1->Columns->Items[4]->Title->Caption = "作者";
		RzDBGrid1->Columns->Items[5]->Visible = true;
               RzDBGrid1->Columns->Items[6]->Visible = false;
	       //	RzDBGrid1->Columns->Items[7]->Title->Caption = "版次";
              //  RzDBGrid1->Columns->Items[8]->Title->Caption = "版次";
	}

	if (rg->ItemIndex == 1) {
		RzDBGrid1->Columns->Items[1]->Title->Caption = "条码";
		RzDBGrid1->Columns->Items[2]->Title->Caption = "品名";
		RzDBGrid1->Columns->Items[4]->Title->Caption = "厂商";
		RzDBGrid1->Columns->Items[5]->Visible = false;
		RzDBGrid1->Columns->Items[6]->Visible = false;
		RzDBGrid1->Columns->Items[7]->Title->Caption = "规格";
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcatalogneworrec::BtnViewClick(TObject *Sender)
{
	Query();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcatalogneworrec::edminpriceKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '-')&&(Key != '\b')) {
	  	Key = NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcatalogneworrec::edmaxpriceKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '-')&&(Key != '\b')) {
		Key = NULL;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcatalogneworrec::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcatalogneworrec::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcatalogneworrec::BtnExportClick(TObject *Sender)
{
	if (query->IsEmpty() ) {
		return;
	}
	DbgridToExcel(RzDBGrid1);
}
//---------------------------------------------------------------------------
//Excel导出函数
bool Tfrmcatalogneworrec::DbgridToExcel(TRzDBGrid* dbg)
{
	AnsiString temptext,path,s;
	//TStrings* ss = new TStringList();
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = Sysutils::ExtractFilePath(savedlg->FileName.c_str());
		Name = Sysutils::ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".csv";
		path =  DBPath;
	}else return false;
	//path =  ExtractFilePath(Application->ExeName) + "catalog.csv";
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;
	int count =0,row =0,col =0;
	if(k == 0)
	{
		ShowMsg(this->Handle,"没有数据！",3);
		return false;
	}
	/*Variant     v;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
//  在Excel中成字符串显示
	v.OlePropertyGet("Cells",1,5).OlePropertySet("Value","目录制作" ); */
   //	s = ",,,,目录制作";
   //	ss->Text = s;
   //	ss->SaveToFile(path);
	int  iFileHandle;
	int   iFileLength;
	if(FileExists(path))
	   iFileHandle = FileOpen(path.c_str() ,fmOpenReadWrite);
	else
		iFileHandle = FileCreate(path.c_str());





	if (rg->ItemIndex == 0) {
		temptext = "图书";
	}
	else if (rg->ItemIndex == 1) {
		temptext = "文具";
	}

	/*v.OlePropertyGet("Cells",3+row,3*col+1).OlePropertySet("Value","经营类型" );
	v.OlePropertyGet("Cells",3+row,3*col+2).OlePropertySet("Value",temptext .c_str() );
	count ++;
	if (chisbn->Checked ) {
		row = count/4,col = count%4;
		v.OlePropertyGet("Cells",3+row,3*col+1).OlePropertySet("Value","书号" );
		temptext = "'"+ edisbn->Text;
		v.OlePropertyGet("Cells",3+row,3*col+2).OlePropertySet("Value",temptext .c_str() );
		count ++;
	}

	if (chname->Checked ) {
		row = count/4,col = count%4;
		v.OlePropertyGet("Cells",3+row,3*col+1).OlePropertySet("Value","书名" );
		temptext = "'"+ edname->Text;
		v.OlePropertyGet("Cells",3+row,3*col+2).OlePropertySet("Value",temptext .c_str() );
		count ++;
	}

	if (chuserdef->Checked ) {
		row = count/4,col = count%4;
		v.OlePropertyGet("Cells",3+row,3*col+1).OlePropertySet("Value","自编码" );
		temptext = "'"+ eduserdef->Text;
		v.OlePropertyGet("Cells",3+row,3*col+2).OlePropertySet("Value",temptext .c_str() );
		count ++;
	}

	if (chauthor->Checked ) {
		row = count/4,col = count%4;
		v.OlePropertyGet("Cells",3+row,3*col+1).OlePropertySet("Value","作者" );
		temptext = "'"+ edauthor->Text;
		v.OlePropertyGet("Cells",3+row,3*col+2).OlePropertySet("Value",temptext .c_str() );
		count ++;
	}

	if (chtype->Checked ) {
		row = count/4,col = count%4;
		v.OlePropertyGet("Cells",3+row,3*col+1).OlePropertySet("Value","类别" );
		temptext = "'"+ cbtype->Text;
		v.OlePropertyGet("Cells",3+row,3*col+2).OlePropertySet("Value",temptext .c_str() );
		count ++;
	}

	if (chpress->Checked ) {
		row = count/4,col = count%4;
		v.OlePropertyGet("Cells",3+row,3*col+1).OlePropertySet("Value","版别" );
		temptext = "'"+ cbpress->Text;
		v.OlePropertyGet("Cells",3+row,3*col+2).OlePropertySet("Value",temptext .c_str() );
		count ++;
	}

	if (chprice->Checked ) {
		row = count/4,col = count%4;
		v.OlePropertyGet("Cells",3+row,3*col+1).OlePropertySet("Value","定价" );
		temptext = "'>="+ edminprice->Text;
		v.OlePropertyGet("Cells",3+row,3*col+2).OlePropertySet("Value",temptext .c_str() );
		temptext = "'<="+ edmaxprice->Text;
		v.OlePropertyGet("Cells",3+row,3*col+3).OlePropertySet("Value",temptext .c_str() );
		count ++;
	}    */

	if (count == 0) {
		n = 2;
	}
	else if (count%4 == 0) {
		n = 3+count/4;
	}
	else if (count%4 != 0){
		n = 4+count/4;
	}


	int t1= 0;
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			//t1++;
			//temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			//v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );
			//v.OlePropertyGet("Cells",1+n,t1).OleFunction("BorderAround",1,2,1);
			temptext = dbg->Columns ->Items [q]->Title ->Caption + ",";
			iFileLength   =   FileSeek(iFileHandle,0,2);
			FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		}
	}
	temptext = "\n";
			iFileLength   =   FileSeek(iFileHandle,0,2);
			FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());


	int t2 = dbg->DataSource ->DataSet ->RecordCount ;

	dbg->DataSource ->DataSet->DisableControls();
	dbg->DataSource ->DataSet ->First();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				if (dbg->Columns ->Items [j-1]->FieldName == "ISBN") {
					temptext = "'" + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->DisplayText + ",";
				}
				else
				{
					temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->DisplayText + ",";
                }
				iFileLength   =   FileSeek(iFileHandle,0,2);
				FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
			}
		}
		dbg->DataSource ->DataSet ->Next() ;
		temptext = "\n";
			iFileLength   =   FileSeek(iFileHandle,0,2);
			FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
	}
	dbg->DataSource ->DataSet->EnableControls();

	t1= 0;
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		/*if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			v.OlePropertyGet("Cells",t2+2+n,t1).OleFunction("BorderAround",1,2,1);
		} */
	}
	t1 = 0;
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		/*if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = "'"+ dbg->GetFooterValue(0,dbg->Columns->Items[q]);
			v.OlePropertyGet("Cells",t2+2+n,t1).OlePropertySet("Value",temptext .c_str() );
		}*/
	}
	FileClose(iFileHandle);
	ShowMsg(this->Handle,"导出完毕！",3);
	return false;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcatalogneworrec::edisbnChange(TObject *Sender)
{
	if (edisbn->Text == "") {
		chisbn->Checked = false;
	}
	else
	{
    	chisbn->Checked = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcatalogneworrec::edauthorChange(TObject *Sender)
{
	if (edauthor->Text == "") {
		chauthor->Checked = false;
	}
	else
	{
    	chauthor->Checked = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcatalogneworrec::ednameChange(TObject *Sender)
{
	if (edname->Text == "") {
		chname->Checked = false;
	}
	else
	{
    	chname->Checked = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcatalogneworrec::eduserdefChange(TObject *Sender)
{
	if (eduserdef->Text == "") {
		chuserdef->Checked = false;
	}
	else
	{
    	chuserdef->Checked = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcatalogneworrec::cbpressChange(TObject *Sender)
{
	if (cbpress->Text == "") {
		chpress->Checked = false;
	}
	else
	{
    	chpress->Checked = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcatalogneworrec::edminpriceChange(TObject *Sender)
{
	if (edminprice->Text == "") {
		chprice->Checked = false;
	}
	else
	{
		chprice->Checked = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcatalogneworrec::edmaxpriceChange(TObject *Sender)
{
	if (edmaxprice->Text == "") {
		chprice->Checked = false;
	}
	else
	{
    	chprice->Checked = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmcatalogneworrec::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcatalogneworrec::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == 117) {   //导出
		BtnExport->Click();
	}
	if (Key == VK_F4) {   //保存
		BtnSave->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 70 ) {    //查询
		BtnView->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 78 ) {    //最小化
		BtnAlignBottom->Click();
	}
	if (Shift.Contains(ssAlt)&& Key == 81 ) {    //退出
		BtnExit->Click();
	}
	if (Shift.Contains(ssAlt)&& Key ==90) {   //恢复窗口
		WindowState = wsNormal  ;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcatalogneworrec::BtnSaveClick(TObject *Sender)
{
	AnsiString sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	sql = "delete from BS_RecommendBook";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	sql = "insert into BS_RecommendBook(BookId,RecommendDate) select id,getdate() from BS_BookCatalog where recomend = 1";
    aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->ExecSQL();
	delete aq;
    Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcatalogneworrec::DBGridEh1TitleClick(TColumnEh *Column)
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

void __fastcall Tfrmcatalogneworrec::SpeedButton1Click(TObject *Sender)
{
	Tfrmselecttype * frm = new Tfrmselecttype(Application,fcon,"");
	if (mrOk == frm->ShowModal())
	{
		TypeID = frm->GetSelectID();
		edtyname->Text = frm->GetSelect();
		chtype->Checked = true;
	}
	delete frm;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmcatalogneworrec::sbcreatewsaleClick(TObject *Sender)
{
   //

   if (cbclient->Text == "") {
    MessageBox(NULL,"请先选择客户！","提示",MB_OK|MB_ICONINFORMATION);
     return;

   }



   clientid = (int)cbclient->Items->Objects[cbclient->ItemIndex];


   Screen->Cursor = crHourGlass ;
   AnsiString sql;
    TBookmark bm;
    Screen->Cursor = crHourGlass ;
    sql = "delete BS_Temp_NewBookToWsale where  userid = " + IntToStr(fuserid);
    aq->Close();
    aq->SQL->Clear();
    aq->SQL->Add(sql);
    aq->ExecSQL();

    sql = "select * from BS_Temp_NewBookToWsale where userid="+ IntToStr(fuserid);;
    aq->Close();
    aq->SQL->Clear();
    aq->SQL->Add(sql);
    aq->Open();

    TLocateOptions   Opts;
    Opts.Clear();
    Opts   <<   loPartialKey;

    try
    {
       if (RzDBGrid1->SelectedRows->Count==0) {
                MessageBox(NULL,"请先选择订单书目！","提示",MB_OK|MB_ICONINFORMATION);
		Screen->Cursor = crDefault ;
		return;
             }
		RzDBGrid1->DataSource->DataSet->DisableControls();
		for (int i = 0 ; i < RzDBGrid1->SelectedRows->Count ; i++) {

	       	 RzDBGrid1->DataSource->DataSet->Bookmark = RzDBGrid1->SelectedRows->Items[i];
	       	 bm = RzDBGrid1->DataSource->DataSet->GetBookmark();
	       	 RzDBGrid1->DataSource->DataSet->GotoBookmark(bm);

                 	if (aq->State != dsInsert) {
				aq->Append();
			}


                        aq->FieldByName("bookcatalogid")->AsInteger = RzDBGrid1->DataSource->DataSet->FieldByName("bkookcatalogid")->AsInteger;

                      //  aq->FieldByName("storagenoteid")->AsInteger = RzDBGrid1->DataSource->DataSet->FieldByName("storagenoteid")->AsInteger;
                        aq->FieldByName("stgid")->AsAnsiString=fstgid;
                        aq->FieldByName("userid")->AsInteger = fuserid;
                        aq->FieldByName("vendorid")->AsInteger = clientid;

			aq->Post();
                        RzDBGrid1->DataSource->DataSet->Next();
                        }
                RzDBGrid1->DataSource->DataSet->EnableControls() ;

        }
    catch(...)
    {
    MessageBox(NULL,"生成发货单失败！","提示",MB_OK|MB_ICONINFORMATION);
    }


     if(!createproc())
        {
          MessageBox(NULL, "生成发货单失败!","先行者软件提醒",MB_OK|MB_ICONINFORMATION);
          Screen->Cursor = crDefault;
          return;
        }
         Screen->Cursor = crDefault;
         AnsiString caigoudanstr;

          caigoudanstr = "已成功生成"+returncode+"发货单！"+" 是否查看?";
         if(MessageBox(NULL, caigoudanstr.c_str(),"先行者软件提醒",MB_YESNO|MB_ICONQUESTION)==6)
         {
            AnsiString awhere;
            awhere = " where wsaleNtCodeint in("+returncodeint+")";
            TfrmWholesaleMng* frm = new TfrmWholesaleMng(Application,1);
            frm->Init(&linfo);
            frm->SearchDanHao(awhere);
            frm->FindNote(oldcode);
           // Close();
         }else
         {
           Close();
         }
         BtnView->Click();

}
void Tfrmcatalogneworrec::ReadyData()
{
       AnsiString sql;
       sql = " select * from CUST_CustomerInfo where Type in(2,3) and customerstate=1 and stgid="+IntToStr(fstgid);
       	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while (!aq->Eof )

	{
		cbclient->AddItem(aq->FieldByName("name")->AsString,(TObject *)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}




}
//---------------------------------------------------------------------------

void __fastcall Tfrmcatalogneworrec::editclientnameKeyPress(TObject *Sender, wchar_t &Key)
          
{
	if (Key == '\r')
        {
          	AnsiString sql;
		sql = " select * from CUST_CustomerInfo where Type in(2,3) and customerstate=1 and stgid="+IntToStr(fstgid)+" and Name like '%"+ editclientname->Text.Trim() + "%' order by name";
                aq->Close();
                aq->SQL->Clear();
                aq->SQL->Add(sql);
                aq->Open();
                cbclient->Clear();
                while (!aq->Eof )
                {
                cbclient->AddItem(aq->FieldByName("name")->AsString,(TObject *)aq->FieldByName("ID")->AsInteger );
                aq->Next();
                }
                if (aq->RecordCount >0) {
                     cbclient->ItemIndex = 0;
                }
                if (cbclient->Items->Count >0) {
                     clientid = (int)cbclient->Items->Objects[cbclient->ItemIndex];
                }



        }
}
 bool Tfrmcatalogneworrec::createproc()
 {

      AnsiString sql,sql1;
        try
        {
          sql = "exec USP_BS_RukuToWsale "+IntToStr(fuserid)+","+IntToStr(fstgid)+","+"@ReturnCode = @ReturnCode OUTPUT,@ReturnCodeint = @ReturnCodeint OUTPUT,@ReturnCodeold=@ReturnCodeold OUTPUT";
          sql1=" SELECT	@ReturnCode as N'@ReturnCode',@ReturnCodeint as N'@ReturnCodeint',@ReturnCodeold as N'@ReturnCodeold'" ;
          adoexec->Close();
          adoexec->SQL->Clear();         //@ReturnCodeold
          adoexec->SQL->Add("DECLARE	@ReturnCode nvarchar(max)");
          adoexec->SQL->Add("DECLARE @ReturnCodeint nvarchar(max) ");
          adoexec->SQL->Add("DECLARE @ReturnCodeold nvarchar(max) ");
          adoexec->SQL->Add(sql);
          adoexec->SQL->Add(sql1);
          adoexec->Open();
           returncode = adoexec->FieldByName("@ReturnCode")->AsAnsiString ;
           returncodeint =  adoexec->FieldByName("@ReturnCodeint")->AsAnsiString ;
           oldcode =  adoexec->FieldByName("@ReturnCodeold")->AsAnsiString ;
           if (returncode=="") {
               return false;
           }
           return true;
           }
 catch(...)
 {
        return false;
 }
 }

 void Tfrmcatalogneworrec::init(LandInfo* li)
 {
 	fuserid = li->userID ;
	fstgid = li->storageID ;
        linfo.app = li->app ;
        linfo.con = li->con ;
        linfo.userID = li->userID ;
        linfo.UserName = li->UserName ;
        linfo.storageID = li->storageID ;
        linfo.FormatStr = li->FormatStr ;
        ReadyData();
   }


//---------------------------------------------------------------------------


void __fastcall Tfrmcatalogneworrec::N1Click(TObject *Sender)
{
//
	if (query->IsEmpty() ) {
		return;
	}
        if (RzDBGrid1->SelectedRows->Count > 1)
        {

         MessageBox(NULL,"请选一条记录！","提示",MB_OK|MB_ICONINFORMATION);
      return;
        }

	Tfrmbookhistory *frm = new Tfrmbookhistory(Application,fcon,fstgid,query->FieldByName("bkookcatalogid")->AsInteger );
	frm->Show();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcatalogneworrec::N2Click(TObject *Sender)
{
RzDBGrid1->DataSource->DataSet->DisableControls();
  query->First();
for (int i=0; i < RzDBGrid1->DataSource->DataSet->RecordCount; i++) {
    RzDBGrid1->SelectedRows->CurrentRowSelected = true;
    query->Next();
}
RzDBGrid1->DataSource->DataSet->EnableControls();
}
//---------------------------------------------------------------------------


void __fastcall Tfrmcatalogneworrec::cbclientChange(TObject *Sender)
{
 clientid = (int)cbclient->Items->Objects[cbclient->ItemIndex];
 Query();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcatalogneworrec::rgClick(TObject *Sender)
{
Query();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmcatalogneworrec::FormShow(TObject *Sender)
{
    Query();
}
//---------------------------------------------------------------------------

