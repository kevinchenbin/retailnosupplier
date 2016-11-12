//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "wenjukanli.h"
#include "ExcelImport.h"
#include "BookQuery.h"
#include "BooKTypeAdminForm.h"
#include "Addsyslog.h"
#include "Unitprintbarcode.h"
#include "global.h"
#include "Selecttype.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzCmboBx"
#pragma link "RzDBGrid"
#pragma link "RzRadChk"
#pragma link "RzEdit"
#pragma link "RzLine"
#pragma link "RzRadGrp"
#pragma link "RzLabel"
#pragma link "RzSpnEdt"
#pragma link "RzDTP"
#pragma link "frxClass"
#pragma resource "*.dfm"
Tfrmwenjukanli *frmwenjukanli;
//---------------------------------------------------------------------------
__fastcall Tfrmwenjukanli::Tfrmwenjukanli(TComponent* Owner,TADOConnection *con,int stgid,int userid)
	: TForm(Owner)
{
   fcon = con;
   aquery->Connection = con;
   query->Connection = con;
   fcon = con;
   fstgid = stgid;
   fuserid = userid;
   int maxid;
   AnsiString sql;
   sql ="select value from sys_bsset where name = 'crtuserbarcode'";
   query->Close();
   query->SQL->Clear();
   query->SQL->Add(sql);
   query->Open();
   userbar = query->FieldByName("value")->AsBoolean ;
   sql = "select count(*) as count from BS_BookCatalog where Unavailable = 1 and type = 2";
   query->Close();
   query->SQL->Clear();
   query->SQL->Add(sql);
   query->Open();
   edpinzhong->Text = query->FieldByName("count")->AsAnsiString ;

   sql = "select max(id) as id from BS_BookCatalog " ;
   query->Close();
   query->SQL->Clear();
   query->SQL->Add(sql);
   query->Open();
   maxid = query->FieldByName("id")->AsInteger + 1;
   sql = "select A.ID,A.barcode,A.userdefcode,A.UserBarcode,case when A.UserBarcode = A.Barcode then '' else A.UserBarcode end as UserBarcode1,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.author,A.Unavailable,A.type,"
		 "A.PressCount,C.name as typename from bs_bookcatalog A left join BS_BookType C on A.smallbooktypeid = C.ID where A.ID > " + IntToStr(maxid) ;
		sql = sql + " and A.type = 2";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->Open();
   if (userbar) {
		DBGrid1->Columns->Items [2]->Visible = true;
   }
   else
   {
    	DBGrid1->Columns->Items [2]->Visible = false;
   }
	constbarcode = "9780000000000";
	TypeID = -1;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmwenjukanli::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmwenjukanli::FormClose(TObject *Sender, TCloseAction &Action)
{
  	Action = caFree ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmwenjukanli::editcodeKeyPress(TObject *Sender, wchar_t &Key)
{
	String sql;
	if (Key==VK_RETURN)
	{
		AnsiString barcode = editcode->Text.Trim() ;
		if (modle == 1) {
			sql = "select A.ID,A.barcode,A.userdefcode,A.UserBarcode,case when A.UserBarcode = A.Barcode then '' else A.UserBarcode end as UserBarcode1,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.author,A.Unavailable,A.type,"
				"A.PressCount,C.name as typename from bs_bookcatalog A left join BS_BookType C on A.smallbooktypeid = C.ID where barcode = '" + editcode->Text + "'";
			sql = sql + " and A.type = 2";
			aquery->Close();
			aquery->SQL->Clear();
			aquery->SQL->Add(sql);
			aquery->Open();

			((TFloatField *)DBGrid1->DataSource->DataSet->FieldByName("price"))->DisplayFormat = "￥0.00";
		}
		editbookname->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmwenjukanli::editbooknameKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key==VK_RETURN) {
		if (editbookname->Text =="") {
			ShowMsg(Handle ,"品名不能为空！",3);
			return;
		 }
		 if (editbookself->Text == "") {
         	char* t;
			AnsiString t2;
			String t1,t3,t4;
			t1 = editbookname->Text;//.TrimLeft().TrimLeft()  ;//.TrimRight();//  .TrimLeft()  ;
			int t5=1,i = editbookname->Text.Length() ;
			for( int j=1;j<=i;j++)
			{
				//if (j == 9) break;
				t3 = t1.SubString(j,1);
				t = t3.t_str();
				//if(t3 < 160) continue;
				Word k = int (t[0])<<8;
				k = k >> 8;
				if(k<160) continue;
				//if(int(t[0])< 160) continue;
				//if (t3 >= 'a' && t3 <= 'z' || t3 >= 'A' && t3 <= 'Z'|| t3 >= 0 && t3 <= 9||t3 == '!'||t3 == '@'||t3=='#'||t3=='$'||t3=='%') continue;
				t5++;
				if (t5 == 9) break;
				t = t3.t_str();
				t2 = GetPYIndexChar(t);
				t4 = t4 + t2;
			}
			editbookself->Text = t4;
		}
		editbookself->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmwenjukanli::editpriceKeyPress(TObject *Sender, wchar_t &Key)
{
	String sql;
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '-')&&(Key != '\b')) {
	  Key = NULL;
	}

	if (Key==VK_RETURN) {
		if (editprice->Text == "") {
			editprice->Text = "0.00";
		}
		else
		{
			String price = editprice->Text ;
			price = price.SubString(price.Pos("￥")+1,price.Length()-price.Pos("￥") );
			editprice->Text = price;
		}
		float fprice = StrToFloat(editprice->Text) ;
		editprice->Text = FormatFloat("￥0.00",fprice);
		editauthor->SetFocus();
	}
}

//---------------------------------------------------------------------------
String  Tfrmwenjukanli:: GetID()
{
	return ID;
}

//---------------------------------------------------------------------------
void __fastcall Tfrmwenjukanli::BtnSaveClick(TObject *Sender)
{
	if (modle == 0) {
        return;
	}
	AnsiString sql;
	if (editbookname->Text == "") {
		ShowMsg(Handle ,"品名不能为空！",3);
		return;
	}
	if (editprice->Text  == "") {
		ShowMsg(Handle ,"定价不能为空！",3);
		return;
	}
	if (editprice->Text == "") {
		editprice->Text = "0.00";
	}
	else
	{
		String price = editprice->Text ;
		price = price.SubString(price.Pos("￥")+1,price.Length()-price.Pos("￥") );
		editprice->Text = price;
	}

	int pressid,bktypeid;
	AnsiString code = editcode->Text ;
	AnsiString userbarcode;
   	if (modle == 1) {
		if (ShowMsg(Handle ,"确定产生新文具吗?",1)==1) {
			if (code != "") {
				sql = "select * from BS_BookCatalog where ISBN like '%" + code + "%' or Barcode like '%" + code + "%'" ;
				query->Connection = fcon;
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				query->Open();
				if (query->RecordCount > 0) {
					if (userbar) {
                    	sql = "select max(id) as id from BS_BookCatalog " ;
						query->Close();
						query->SQL->Clear();
						query->SQL->Add(sql);
						query->Open();
						if (query->FieldByName("id")->AsAnsiString == "" ) {
							userbarcode = "0";
						}
						else
						{
							userbarcode = IntToStr(query->FieldByName("id")->AsInteger + 1) ;
						}
						userbarcode = constbarcode.SubString(0,13-userbarcode.Length()) + userbarcode;
					}
					else
					{
                    	userbarcode = editcode->Text.Trim();
					}
				}
				else
				{
					userbarcode = editcode->Text.Trim();
				}
			}
			else
			{
				if (userbar) {
                	sql = "select max(id) as id from BS_BookCatalog " ;
					query->Close();
					query->SQL->Clear();
					query->SQL->Add(sql);
					query->Open();
					if (query->FieldByName("id")->AsAnsiString == "" ) {
						userbarcode = "0";
					}
					else
					{
						userbarcode = IntToStr(query->FieldByName("id")->AsInteger + 1) ;
					}
					userbarcode = constbarcode.SubString(0,13-userbarcode.Length()) + userbarcode;
				}
				else
				{
					userbarcode =  editcode->Text.Trim();
				}
			}

			aquery->Insert();
			aquery->Append();
			aquery->FieldByName("barcode")->AsAnsiString = editcode->Text ;
			aquery->FieldByName("ISBN")->AsAnsiString = editcode->Text ;
			aquery->FieldByName("name")->AsAnsiString = editbookname->Text ;
			aquery->FieldByName("userdefcode")->AsAnsiString = editbookself->Text ;
			aquery->FieldByName("UserBarcode")->AsAnsiString = userbarcode ;
			aquery->FieldByName("author")->AsAnsiString = editauthor->Text ;
			aquery->FieldByName("price")->AsAnsiString = editprice->Text ;
			aquery->FieldByName("type")->AsAnsiString = 2 ;
			if (edtypename->Text == "") {
				aquery->FieldByName("smallbooktypeid")->AsInteger = -1;
			}
			else
			{
				aquery->FieldByName("smallbooktypeid")->AsInteger = TypeID;
			}
			aquery->FieldByName("PressCount")->AsString  = edpresscount->Text ;
			
			try {
				aquery->UpdateBatch(arAll);
			} catch (...) {
				ShowMsg(this->Handle,"请确认文具信息正确，添加失败！",3);
				return;
			}

			if (!rzcbinput->Checked) {
				ID =  aquery->FieldByName("ID")->AsAnsiString ;
				ModalResult = mbOK ;
				modle = 0;

				BtnView->Enabled = true;
				BtnNew->Enabled = true;
				BtnClear->Enabled = true;
				BtnCancel->Enabled = true;
				BtnUndo->Enabled = true;
				BtnDelete->Enabled = true;
				BtnExport->Enabled = true;
				RzToolButton1->Enabled = true;
				BtnSave->Enabled = false;
				btncnacelsave->Enabled = false;
				GroupBox1->Enabled = false;
			}else     //连续录入
		 	{
				editcode->Text  = "";
				editbookname->Text = "";
				editbookself->Text = "";
				editauthor->Text = "";
				editprice->Text = "￥0.00";
				editauthor->Text = "";
				edquery->Text = "";
				edtypename->Text = "";
				edpresscount->Text = "";
                TypeID = -1;

				edpresscount->Text = "";
				editcode->SetFocus();
				ID = aquery->FieldByName("ID")->AsAnsiString ;
				modle = 1;
			}
		}
	}
	if (modle == 2) {
		AnsiString sql;
    	int pressid,booktypeid;
		if(editbookname->Text == "" )
			return;
		if (aquery->RecordCount == 0)
			return;
		if (edtypename->Text == "") {
			booktypeid = -1;
		} else
		{
			booktypeid = TypeID;
		}
		if (ShowMsg(Handle ,"确认修改文具信息?",1)==1)
		{
			logmessage = "修改文具《" + aquery->FieldByName("name")->AsAnsiString + "》的信息为《" + editbookname->Text.Trim() + "》";
			AddEvent(1,"文具目录管理",fuserid,fstgid,logmessage,fcon);

			sql = "update BS_BookCatalog set name = '" + editbookname->Text.Trim() + "',userdefcode = '" + editbookself->Text.Trim() + "',isbn = '" + editcode->Text.Trim() + "',Barcode = '" + editcode->Text ;
			sql = sql + "',author = '" +  editauthor->Text.Trim()  + "',price = " + editprice->Text ;
			sql = sql + ",smallbooktypeid = " + IntToStr(booktypeid) + ",PressCount = '" + edpresscount->Text ;
			sql = sql + "' where ID = " + aquery->FieldByName("ID")->AsString ;
			try {
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				try {
					query->ExecSQL();
				} catch (...) {
                	ShowMsg(this->Handle,"请确认文具信息正确，修改失败！",3);
					return;
				}

				BtnView->Enabled = true;
				BtnNew->Enabled = true;
				BtnClear->Enabled = true;
				BtnCancel->Enabled = true;
				BtnUndo->Enabled = true;
				BtnDelete->Enabled = true;
				BtnExport->Enabled = true;
				RzToolButton1->Enabled = true;
				BtnSave->Enabled = false;
				btncnacelsave->Enabled = false;
				GroupBox1->Enabled = false;
				modle = 0;
			} catch (...) {
			}
			aquery->Active = false;
			aquery->Active = true;
			((TFloatField *)DBGrid1->DataSource->DataSet->FieldByName("price"))->DisplayFormat = "￥0.00";
			editprice->Enabled = true;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmwenjukanli::BtnNewClick(TObject *Sender)
{
	int maxid;
	AnsiString sql;
	sql = "select max(id) as id from BS_BookCatalog " ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	maxid = query->FieldByName("id")->AsInteger + 1;

	sql = "select A.ID,A.barcode,A.userdefcode,A.UserBarcode,case when A.UserBarcode = A.Barcode then '' else A.UserBarcode end as UserBarcode1,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.author,A.Unavailable,A.type,"
		 "A.PressCount,C.name as typename from bs_bookcatalog A left join BS_BookType C on A.smallbooktypeid = C.ID where A.ID > " + IntToStr(maxid) ;
		sql = sql + " and A.type = 2";
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Active = true;
	edpinzhong->Text = IntToStr(aquery->RecordCount);

	//PageControlBook->Enabled = true;


	modle = 1;// 添加模式
	BtnView->Enabled = false;
	BtnNew->Enabled = false;
	BtnClear->Enabled = false;
	BtnCancel->Enabled = false;
	BtnUndo->Enabled = false;
	BtnDelete->Enabled = false;
	BtnExport->Enabled = false;
	RzToolButton1->Enabled = false;
	BtnSave->Enabled = true;
	btncnacelsave->Enabled = true;
	GroupBox1->Enabled = true;
	editcode->SetFocus();
	editcode->Text = "";
	editbookname->Text = "";
	editbookself->Text = "";
	editprice->Text = "￥0.00";
	editauthor->Text = "";
	edpresscount->Text = "";
	edquery->Text = "";
	edtypename->Text = "";
	TypeID = -1;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmwenjukanli::BtnClearClick(TObject *Sender)
{
	modle = 2;//  修改模式
	if (type == 0 && (!aquery->Active || aquery->RecordCount == 0) ) {
		return;
	}
	else if ((type == 1 || type == 2)&& (!aqinsert->Active || aqinsert->RecordCount == 0)) {
    	return;
	}
	AnsiString sql;
	if (type == 0) {
    	sql = "declare @modify int ;"
			" exec modifprice " + aquery->FieldByName("ID")->AsString  + ",-1," + IntToStr(fstgid) + ",@modify output ; "
			" select @modify as modify" ;
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		if (query->FieldByName("modify")->AsInteger == 1 ) {
			editprice->Enabled = false;
		}
	}
	BtnView->Enabled = false;
	BtnNew->Enabled = false;
	BtnClear->Enabled = false;
	BtnCancel->Enabled = false;
	BtnUndo->Enabled = false;
	BtnDelete->Enabled = false;
	BtnExport->Enabled = false;
	RzToolButton1->Enabled = false;
	BtnSave->Enabled = true;
	btncnacelsave->Enabled = true;
	GroupBox1->Enabled = true;
}
//---------------------------------------------------------------------------
void Tfrmwenjukanli::cumvalue(AnsiString sqlsum)
{
    TADOQuery *aquery;
    aquery = new TADOQuery(NULL);
    aquery->Connection =fcon ;
    aquery->Close();
    aquery->SQL->Clear();
    aquery->SQL->Add(sqlsum);
    aquery->Open();
    delete aquery;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmwenjukanli::BtnCancelClick(TObject *Sender)
{
	for (int i =0; i < DBGrid1->SelectedRows->Count ; i++) {
		aquery->GotoBookmark(DBGrid1->SelectedRows->Items[i]);
		if (aquery->RecordCount > 0) {
			try {
				aquery->Edit();
				aquery->FieldByName("Unavailable")->Value = 0;
				aquery->UpdateBatch(arCurrent);
			} catch (...) {
			}
		}
	}
	aquery->Active = false;
	aquery->Active = true;
	edpinzhong->Text = IntToStr(aquery->RecordCount);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwenjukanli::BtnDeleteClick(TObject *Sender)
{
	AnsiString delIDstr;
	AnsiString sql;
	if (aquery->IsEmpty() ) {
		return;
	}
	if (ShowMsg(Handle ,"确认删除吗?",1)!=1)
	{
		return;
	}
        delIDstr = "(";
	for (int i =0; i < DBGrid1->SelectedRows->Count ; i++) {
		aquery->GotoBookmark(DBGrid1->SelectedRows->Items[i]);
		if (aquery->RecordCount > 0) {
			delIDstr = delIDstr+aquery->FieldByName("ID")->AsString +",";
		}
	}

        try
        {
            delIDstr = delIDstr + "-1)";
            sql = "delete from BS_BookCatalog where ID in "+delIDstr;
            query->Close();
            query->SQL->Clear();
            query->SQL->Add(sql);
            query->ExecSQL();
        }catch (Exception &E) {
        ShowMsg(Handle ,"该数据跟系统其他数据有关联，不能删除！",3);

        }

	aquery->Active = false;
	aquery->Active = true;
	edpinzhong->Text = IntToStr(aquery->RecordCount);
	editcode->Text = "";
	editbookname->Text = "";
	editbookself->Text = "";
	editprice->Text = "￥0.00";
	editauthor->Text = "";
	edpresscount->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwenjukanli::FormShow(TObject *Sender)
{
  //	edtQuery->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwenjukanli::BtnExportClick(TObject *Sender)
{
	if (aquery->Active &&  aquery->RecordCount > 0) {
		DbgridToExcel(DBGrid1);
   }
}
//---------------------------------------------------------------------------

//Excel导出函数
bool __fastcall Tfrmwenjukanli::DbgridToExcel(TDBGrid* dbg)
{
	AnsiString temptext,path,ss;
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = Sysutils::ExtractFilePath(savedlg->FileName .c_str()  );
		Name = Sysutils::ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".csv";
		path =  DBPath;
	}
        else
        {
          return false;
        }
	int  iFileHandle;
	int   iFileLength;
	if(FileExists(path))
	   iFileHandle = FileOpen(path.c_str() ,fmOpenReadWrite);
	else
		iFileHandle = FileCreate(path.c_str());

	temptext = ",,,图书品目管理";
			iFileLength   =   FileSeek(iFileHandle,0,2);
			FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;
	/*if(k == 0)
	{
		MessageBox(0,"没有数据！","错误确认" ,MB_OK);
		return false;
	}
	Variant     v;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
//  在Excel中成字符串显示
	v.OlePropertyGet("Cells",1,4).OlePropertySet("Value","图书品目管理" );
	n = 1;

	int t1= 0;  */
	temptext = "\n";
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			/*t1++;
			temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() ); */
			temptext = temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
		}
	}
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	int t2 = dbg->DataSource ->DataSet ->RecordCount ;
	dbg->DataSource ->DataSet ->First();
	dbg->DataSource ->DataSet->DisableControls();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		//t1=0;
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				/*t1++;
				temptext = "'"+ dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
				v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()         */
				ss = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
				temptext = temptext + ss + ",";
			}
		}
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}
	dbg->DataSource ->DataSet->EnableControls();
	FileClose(iFileHandle);

        ShowMsg(Handle ,"导出完毕！",3);
	return false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwenjukanli::DBGrid1CellClick(TColumn *Column)
{
	if (aquery->IsEmpty()) {
	 	return ;
	}
	if (modle == 1) {
		if (ShowMsg(this->Handle,"正在添加文具，确定复制该文具信息到录入框？",1)!= 1)
		{
			editcode->SetFocus();
			return;
		}
	}
	if (modle == 2) {
		return;
	}
	editcode->Text  = aquery->FieldByName("barcode")->AsAnsiString.Trim() ;
	editbookname->Text = aquery->FieldByName("name")->AsAnsiString.Trim() ;
	editbookself->Text = aquery->FieldByName("userdefcode")->AsAnsiString.Trim();
	editauthor->Text =aquery->FieldByName("author")->AsAnsiString.Trim();
	editprice->Text = FormatFloat("￥0.00",aquery->FieldByName("price")->AsFloat);

	edtypename->Text = aquery->FieldByName("typename")->AsAnsiString ;
	edpresscount->Text = aquery->FieldByName("PressCount")->AsString.Trim() ;
	TypeID = aquery->FieldByName("smallBookTypeID")->AsInteger ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwenjukanli::datapressdayKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
		edpresscount->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwenjukanli::sedpresscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
	   //	PageControlBook->ActivePage = tsdetail;
       BtnSave->Click();
	   editcode->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwenjukanli::btaddtypeClick(TObject *Sender)
{
    String sql ;
	sql = "select max(id) as id from BS_BookType ";
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	int id = aq->FieldByName("id")->AsInteger ;

	TfrmBookTypeAdmin* frm = new TfrmBookTypeAdmin(Application);
	frm->Init(Application,fcon);
    frm->Visible = false;
	frm->ShowModal();
	delete frm;

	sql = "select * from BS_BookType where id > " + IntToStr(id) ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->RecordCount > 0) {
		aq->Last();
		TypeID = aq->FieldByName("ID")->AsInteger;
		edtypename->Text = "[" + aq->FieldByName("Code")->AsAnsiString + "]" + aq->FieldByName("Name")->AsAnsiString ;
	}

	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwenjukanli::editwenjutiaomaoKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
		Perform(WM_NEXTDLGCTL, 0, 0);
	}
}
//---------------------------------------------------------------------------

AnsiString Tfrmwenjukanli::GetSelf(AnsiString context)
{

			char* t;
			AnsiString t2;
			String t1,t3,t4;
			t1 = context;//.TrimLeft().TrimLeft()  ;//.TrimRight();//  .TrimLeft()  ;
			int t5=1,i = context.Length()  ;
			for( int j=1;j<=i;j++)
			{
			//if (j == 9) break;
			t3 = t1.SubString(j,1);
			t = t3.t_str();
			//if(t3 < 160) continue;
			Word k = int (t[0])<<8;
			k = k >> 8;
			if(k<160) continue;
			//if(int(t[0])< 160) continue;
			//if (t3 >= 'a' && t3 <= 'z' || t3 >= 'A' && t3 <= 'Z'|| t3 >= 0 && t3 <= 9||t3 == '!'||t3 == '@'||t3=='#'||t3=='$'||t3=='%') continue;
			t5++;
			if (t5 == 9) break;
			t = t3.t_str();
			t2 = GetPYIndexChar(t);
			t4 = t4 + t2;
            }
			return t4;

}
AnsiString Tfrmwenjukanli::BarCodeToISSN(AnsiString BarCode)
{
  AnsiString ISSN;
  int j[7];
  int k[7] = {8,7,6,5,4,3,2};
  int p = 0;
  for (int i = 4; i < 11;i++,p++) {
		 j[p] = StrToInt(BarCode.SubString(i,1));
  }
  int a = 0;
  int b= 0;
  int c = 0;
  int d = 0;

  for (int i = 0; i < 7; i++) {
	  a = a + j[i]*k[i];
  }

  b = a % 11;
  c = 11 -b;
  for (int i = 0; i < 7; i++) {
	  ISSN = ISSN + IntToStr(j[i]) ;
  }
  if (c == 10) {
	  ISSN = ISSN + "X";
  }else
  {
	 ISSN = ISSN + IntToStr(c);
  }
  return ISSN;
}
AnsiString Tfrmwenjukanli::ISSNToBarCode(AnsiString ISSN)
{
  //ISSN与EAN的对应关系为：977 + ISSN前7码 + 00 + EAN检查码
	 ISSN = ReplaceStr(ISSN,"-","");

	 AnsiString BarCode;
	 BarCode = "977";
	 for (int i = 1; i < 8; i++) {
		 BarCode = BarCode + ISSN.SubString(i,1);
	 }
	 int a=0;
	 int b= 0;
	 int c= 0;
	 int d = 0;
	 for (int i = 2; i < 11; i++) {
		 a = a + StrToInt(BarCode.SubString(i,1) );
		 i++;
	 }
	 for (int i = 1; i < 11; i++) {
	   b = b + StrToInt(BarCode.SubString(i,1) );
	   i++;
	 }
	 a = a *3;
	 c = b + a;
	 d = c % 10;           //取得校验码
	 d = 10 -d;
	 BarCode = BarCode + "00" + IntToStr(d);
	 return BarCode;

}

void __fastcall Tfrmwenjukanli::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
		if (Key == VK_F2) {  //添加
		 BtnNew->Click();
	}	if (Key == VK_F4) {     //保存
		BtnSave->Click();
	}
		if (Key == VK_F5) {     //修改
		BtnClear->Click();
	}
		if (Key == VK_F9) {     //作废
		BtnCancel->Click();
	}
		if (Key == VK_F8) {      //删除
		BtnDelete->Click();
	}

	if (Key == VK_F6) {      //导出
		BtnExport->Click();
	}
	if (Key == VK_F11) {      //撤销
		btncnacelsave->Click();
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



void __fastcall Tfrmwenjukanli::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmwenjukanli::editbookselfKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        editprice->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwenjukanli::N1Click(TObject *Sender)
{
	for (int i = 1; i <= aquery->RecordCount; i++) {
		DBGrid1->DataSource->DataSet->RecNo = i;
		DBGrid1->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwenjukanli::DBGrid1TitleClick(TColumn *Column)
{
	if (aquery->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (aquery->Sort == "") {
		aquery->Sort =  Column->FieldName + " ASC";
	}
	else if (aquery->Sort == qusort) {
		aquery->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		aquery->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwenjukanli::BtnUndoClick(TObject *Sender)
{
	for (int i =0; i < DBGrid1->SelectedRows->Count ; i++) {
		aquery->GotoBookmark(DBGrid1->SelectedRows->Items[i]);
		if (aquery->RecordCount > 0) {
			try {
				aquery->Edit();
				aquery->FieldByName("Unavailable")->Value = 1;
				aquery->UpdateBatch(arCurrent);
			} catch (...) {
			}
		}
	}
	aquery->Active = false;
	aquery->Active = true;
	edpinzhong->Text = IntToStr(aquery->RecordCount);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwenjukanli::RzToolButton1Click(TObject *Sender)
{
	AnsiString catalogid,sql;
	catalogid = "-1";
	if (aquery->IsEmpty() ) {
		return;
	}
	if (DBGrid1->SelectedRows->Count > 0) {
		for (int i=0; i < DBGrid1->SelectedRows->Count; i++)
		{
			aquery->Bookmark = DBGrid1->SelectedRows->Items[i];
			catalogid = catalogid + "," + aquery->FieldByName("ID")->AsString;
		}
	}
	else
	{
		catalogid = catalogid + "," + aquery->FieldByName("ID")->AsString;
	}
	sql = "delete from bs_userbarcode where userid = " + IntToStr(fuserid);
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->ExecSQL();
	sql = "insert into bs_userbarcode(Name,UserBarcode,amount,userid,Price,catalogid) select bs_bookcatalog.name,bs_bookcatalog.barcode,0," + IntToStr(fuserid) +
		",bs_bookcatalog.price,bs_bookcatalog.id from bs_bookcatalog where id in(" + catalogid + ")";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->ExecSQL();
	Tfrmprintbarcode *frm = new Tfrmprintbarcode(Application,fcon,fuserid);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwenjukanli::btncnacelsaveClick(TObject *Sender)
{
	if (modle == 0) {
		return;
	}
	if (modle == 1) {
		if (ShowMsg(this->Handle,"正在添加书目，确定离开？",1)!= 1)
		{
			editcode->SetFocus();
			return;
		}
	}
	if (modle == 2) {
		if (ShowMsg(this->Handle,"正在修改书目，确定离开？",1)!= 1)
		{
        	editcode->SetFocus();
			return;
		}
	}
	modle = 0;
	BtnView->Enabled = true;
	BtnNew->Enabled = true;
	BtnClear->Enabled = true;
	BtnCancel->Enabled = true;
	BtnUndo->Enabled = true;
	BtnDelete->Enabled = true;
	BtnExport->Enabled = true;
	RzToolButton1->Enabled = true;
	BtnSave->Enabled = false;
	btncnacelsave->Enabled = false;
	editprice->Enabled = true;


}
//---------------------------------------------------------------------------

void __fastcall Tfrmwenjukanli::RzButton1Click(TObject *Sender)
{
	if (aquery->IsEmpty() ) {
		return;
	}
	aquery->Active = false;
	aquery->Filtered = false;
	aquery->Active = true;
	edpinzhong->Text = IntToStr(aquery->RecordCount);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwenjukanli::RzButton2Click(TObject *Sender)
{
	if (aquery->IsEmpty() ) {
		return;
	}
	aquery->Active = false;
	aquery->Filtered = true;
	aquery->Filter =  " Unavailable = 0";
	aquery->Active = true;
	edpinzhong->Text = IntToStr(aquery->RecordCount);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwenjukanli::RzButton3Click(TObject *Sender)
{
	if (aquery->IsEmpty() ) {
		return;
	}
	aquery->Active = false;
	aquery->Filtered = true;
	aquery->Filter =  " Unavailable = 1";
	aquery->Active = true;
	edpinzhong->Text = IntToStr(aquery->RecordCount);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwenjukanli::edqrybarChange(TObject *Sender)
{
	if (edqrybar->Text != "") {
		chbarcode->Checked = true;
	}
	else
	{
    	chbarcode->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwenjukanli::edqrynameChange(TObject *Sender)
{
	if (edqryname->Text != "") {
		chname->Checked = true;
	}
	else
	{
    	chname->Checked = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwenjukanli::BtnViewClick(TObject *Sender)
{
	AnsiString sql;
	sql = "select A.ID,A.barcode,A.userdefcode,A.UserBarcode,case when A.UserBarcode = A.Barcode then '' else A.UserBarcode end as UserBarcode1,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.author,A.Unavailable,A.type,"
		 "A.PressCount,C.name as typename from bs_bookcatalog A left join BS_BookType C on A.smallbooktypeid = C.ID where A.type = 2 ";
	if (chbarcode->Checked && edqrybar->Text != "") {
		sql = sql + " and barcode like '%" + edqrybar->Text.Trim() + "%'";
	}
	if (chname->Checked && edqryname->Text != "") {
		sql = sql + " and name like '%" + edqryname->Text.Trim() + "%'";
	}
	if (chprice->Checked && edqryprice->Text != "") {
		try {
			StrToFloat(edqryprice->Text);
		} catch (...) {
        	ShowMsg(this->Handle,"请输入正确的定价！",3);
		}
		sql = sql + " and price = " + edqryprice->Text ;
	}
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Active = true;
	edpinzhong->Text = IntToStr(aquery->RecordCount);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwenjukanli::edpresscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwenjukanli::spselectTypeClick(TObject *Sender)
{
	Tfrmselecttype * frm = new Tfrmselecttype(Application,fcon,"");
	if (mrOk == frm->ShowModal())
	{
		TypeID = frm->GetSelectID();
		edtypename->Text = frm->GetSelect();
	}
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwenjukanli::edqueryKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
    	Tfrmselecttype * frm = new Tfrmselecttype(Application,fcon,edquery->Text);
		if (mrOk == frm->ShowModal())
		{
			TypeID = frm->GetSelectID();
			edtypename->Text = frm->GetSelect();
		}
		delete frm;
		edpresscount->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwenjukanli::editauthorKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		edquery->SetFocus();
	}
}
//---------------------------------------------------------------------------

