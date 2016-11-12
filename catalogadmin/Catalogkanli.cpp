//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Catalogkanli.h"
#include "ExcelImport.h"
#include "BookQuery.h"
#include "PressAdminForm.h"
#include "BooKTypeAdminForm.h"
#include "Setunite.h"
#include "mutibooktongyi.h"
#include "Addsyslog.h"
#include "Unitprintbarcode.h"
#include "global.h"
#include "Selecttype.h"
#include "Unitpassword.h"
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
TfrmCatalogkanli *frmCatalogkanli;
//---------------------------------------------------------------------------
__fastcall TfrmCatalogkanli::TfrmCatalogkanli(TComponent* Owner,TADOConnection *con,int stgid,int userid)
	: TForm(Owner)
{
   fcon = con;
   aquery->Connection = con;
   query->Connection = con;
   fcon = con;
   fstgid = stgid;
   fuserid = userid;
   ReadyData();
   int maxid;
   AnsiString sql;
   sql ="select value from sys_bsset where name = 'crtuserbarcode'";
   query->Close();
   query->SQL->Clear();
   query->SQL->Add(sql);
   query->Open();
   userbar = query->FieldByName("value")->AsBoolean ;

   sql ="select bk from sys_bsset where name = 'catalogdelpassword'";
   query->Close();
   query->SQL->Clear();
   query->SQL->Add(sql);
   query->Open();

   paw =  query->FieldByName("bk")->AsAnsiString ;

   sql = "select count(*) as count from BS_BookCatalog where Unavailable = 1 and type = 0";
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
   sql = "select A.ID,A.barcode,A.userdefcode,A.UserBarcode,case when A.UserBarcode = A.Barcode then '' else A.UserBarcode end as UserBarcode1,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.author,A.Unavailable,A.TotalAmount,A.huojiangstate,A.bcontent,A.wordscount,A.yinzhang,"
		 "A.Yizhe,A.Pressdate,convert(varchar(10),A.Pressdate,111) as pdate,A.PressCount,A.Printcount,A.ISBNType,A.Collectbook,A.Bookformat,A.Bind,A.BookWords,A.Affix,A.Bk,case isnull(A.taoshu ,0) when 1 then '是' when  0 then '否' end taoshu,"
		 "B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
		 " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID where A.ID > " + IntToStr(maxid) ;
		sql = sql + " and A.type = 0";
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->Open();
   datapressday->Date = Date();
   if (userbar) {
		DBGrid1->Columns->Items [3]->Visible = true;
   }
   else
   {
    	DBGrid1->Columns->Items [3]->Visible = false;
   }
	modle = 0;
	constbarcode = "9780000000000";
	TypeID = -1;

}
//---------------------------------------------------------------------------
void __fastcall TfrmCatalogkanli::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCatalogkanli::FormClose(TObject *Sender, TCloseAction &Action)
{
  	Action = caFree ;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCatalogkanli::editcodeKeyPress(TObject *Sender, wchar_t &Key)
{
	String sql;
	if (Key==VK_RETURN)
	{
		AnsiString barcode = editcode->Text.Trim() ;
		if (barcode != "" && barcode.Length() != 13 ) {
			ShowMsg(Handle ,"请输入正确条码！",3);
			return;
		}

		if (modle == 1) {
			sql = "select A.ID,A.barcode,A.userdefcode,A.UserBarcode,case when A.UserBarcode = A.Barcode then '' else A.UserBarcode end as UserBarcode1,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.author,A.Unavailable,A.TotalAmount,A.huojiangstate,A.bcontent,A.wordscount,A.yinzhang,"
			 "A.Yizhe,A.Pressdate,convert(varchar(10),A.Pressdate,111) as pdate,A.PressCount,A.Printcount,A.ISBNType,A.Collectbook,A.Bookformat,A.Bind,A.BookWords,A.Affix,A.Bk,case isnull(A.taoshu ,0) when 1 then '是' when  0 then '否' end taoshu,"
			 "B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
			 " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID where barcode =  '" + editcode->Text + "'";
			sql = sql + " and A.type = 0";
			aquery->Close();
			aquery->SQL->Clear();
			aquery->SQL->Add(sql);
			aquery->Open();

			((TFloatField *)DBGrid1->DataSource->DataSet->FieldByName("price"))->DisplayFormat = "￥0.00";
		}
		int pressid = BrocodeToPress(editcode->Text);
		rcbpress->ItemIndex = rcbpress->Items->IndexOfObject((TObject*)pressid );
		editisbn->Text = editcode->Text ;
		editbookname->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmCatalogkanli::SpeedButton1Click(TObject *Sender)
{
  	editisbn->Text =  BuildISBNCode(editisbn->Text);
}
//---------------------------------------------------------------------------
void __fastcall TfrmCatalogkanli::editbooknameKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key==VK_RETURN) {
		if (editbookname->Text =="") {
			ShowMsg(Handle ,"书名不能为空！",3);
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
		if (modle == 1) {
        	AnsiString sql;
			sql = "select A.ID,A.barcode,A.userdefcode,A.UserBarcode,case when A.UserBarcode = A.Barcode then '' else A.UserBarcode end as UserBarcode1,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.author,A.Unavailable,A.TotalAmount,A.huojiangstate,A.bcontent,A.wordscount,A.yinzhang,"
			 "A.Yizhe,A.Pressdate,convert(varchar(10),A.Pressdate,111) as pdate,A.PressCount,A.Printcount,A.ISBNType,A.Collectbook,A.Bookformat,A.Bind,A.BookWords,A.Affix,A.Bk,case isnull(A.taoshu ,0) when 1 then '是' when  0 then '否' end taoshu,"
			 "B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
			 " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID where A.name like '%" + editbookname->Text.Trim() + "%'";
			sql = sql + " and A.type = 0";
			aquery->Close();
			aquery->SQL->Clear();
			aquery->SQL->Add(sql);
			aquery->Open();

			((TFloatField *)DBGrid1->DataSource->DataSet->FieldByName("price"))->DisplayFormat = "￥0.00";
		}
		editbookself->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmCatalogkanli::editpriceKeyPress(TObject *Sender, wchar_t &Key)
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
void TfrmCatalogkanli::ReadyData()
{
   String sql ;
   TADOQuery *aq = new TADOQuery(this);
   aq->Connection = fcon;
	sql = "select ID,abbreviatedname,PresentNum from BS_PressInfo ";
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while(!aq->Eof)
	{
		rcbpress->AddItem(aq->FieldByName("abbreviatedname")->AsAnsiString, (TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
   	}
	delete aq;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCatalogkanli::editauthorKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key==VK_RETURN)
	{
		spepack->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmCatalogkanli::rcbtypeKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key==VK_RETURN)
	{
	   edquery->SetFocus();
	}
}
//---------------------------------------------------------------------------
String  TfrmCatalogkanli:: GetID()
{
	return ID;
}
void __fastcall TfrmCatalogkanli::rcbpressKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key==VK_RETURN)
	{
	   datapressday->SetFocus();
	}
}

//---------------------------------------------------------------------------
void __fastcall TfrmCatalogkanli::BtnSaveClick(TObject *Sender)
{
	if (modle == 0) {
        return;
	}
	AnsiString sql;
	if (editbookname->Text == "") {
		ShowMsg(Handle ,"书名不能为空！",3);
		return;
	}
	if (editprice->Text == "") {
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
	if (meditwords->Text == "") {
        meditwords->Text = "0";
	}

	int pressid,bktypeid;
	if (rcbpress->Text!="") {
		try {
			pressid = (int)(rcbpress->Items->Objects[rcbpress->ItemIndex]);
		} catch (...) {
			ShowMsg(Handle ,"请选择正确的出版社！",3);
			return;
		}
	}

	AnsiString code = editcode->Text ;
	if (code == "") {
		code = editisbn->Text ;
	}
	AnsiString userbarcode;
   	if (modle == 1) {
		if (ShowMsg(Handle ,"确定产生新书吗?",1)==1) {
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
			aquery->FieldByName("ISBN")->AsAnsiString = editisbn->Text ;
			aquery->FieldByName("name")->AsAnsiString = editbookname->Text ;
			aquery->FieldByName("userdefcode")->AsAnsiString = editbookself->Text ;
			aquery->FieldByName("UserBarcode")->AsAnsiString = userbarcode ;
			aquery->FieldByName("author")->AsAnsiString = editauthor->Text ;
			aquery->FieldByName("price")->AsAnsiString = editprice->Text ;
			if (rcbpress->Text=="") {
				aquery->FieldByName("pid")->AsInteger  = -1;
			}
			else
			{
				aquery->FieldByName("pid")->AsInteger = (int)(rcbpress->Items->Objects[rcbpress->ItemIndex]);
			}
			if (edtypename->Text == "") {
				aquery->FieldByName("smallbooktypeid")->AsInteger = -1;
			}
			else
			{
				aquery->FieldByName("smallbooktypeid")->AsInteger = TypeID;
			}
			aquery->FieldByName("Pressdate")->AsDateTime = datapressday->Date;
			aquery->FieldByName("PressCount")->AsString  = edpresscount->Text ;
			aquery->FieldByName("ISBNType")->AsString = edISBNtype->Text ;
			aquery->FieldByName("Yizhe")->AsString = edyizhe->Text ;
			aquery->FieldByName("Printcount")->AsInteger = edprintcount->Value ;
			aquery->FieldByName("Affix")->AsString = edaffix->Text ;
			aquery->FieldByName("Bookformat")->AsString = cbformat->Text ;
			aquery->FieldByName("Bind")->AsString = cbbind->Text ;
			aquery->FieldByName("Collectbook")->AsString = edbook->Text ;
			aquery->FieldByName("BookWords")->AsInteger  = spepack->Value ;
		  	aquery->FieldByName("huojiangstate")->AsString = edhuojiangstate->Text ;
			aquery->FieldByName("bcontent")->AsString = mcontent->Text ;
			aquery->FieldByName("wordscount")->AsInteger  = StrToInt(meditwords->Text);
            aquery->FieldByName("yinzhang")->AsInteger  = StrToInt(medityinzhang->Text);
			//aquery->FieldByName("taoshu")->AsString = edtaoshu->Text ;
			try {
				aquery->UpdateBatch(arAll);
			} catch (...) {
				ShowMsg(this->Handle,"请确认书目信息正确，添加失败！",3);
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
				BtnImport->Enabled = true;
				BtnExport->Enabled = true;
				BtnJumptoLine->Enabled = true;
				RzToolButton1->Enabled = true;
				BtnAlignClient->Enabled = true;

				BtnSave->Enabled = false;
				btncnacelsave->Enabled = false;
				GroupBox1->Enabled = false;
			 //PageControlBook->Enabled = false;
			}else     //连续录入
		 	{
				editcode->Text  = "";
				editisbn->Text = "";
				editbookname->Text = "";
				editbookself->Text = "";
				editauthor->Text = "";
				rcbpress->ItemIndex = -1;
				editprice->Text = "￥0.00";
				datapressday->Date = Date();
				edpresscount->Text = "";
				edISBNtype->Text = "";
				edyizhe->Text = "";
				edprintcount->Value = 0;
				edaffix->Text = "";
				cbformat->ItemIndex = -1;
				cbbind->ItemIndex = -1;
				edbook->Text = "";
				edhuojiangstate->Text = "";
				spepack->Value = 1;
				meditwords->Text = "0";
				medityinzhang->Text = "0";
				mcontent->Text = "";
				edtypequery->Text = "";
				edtypename->Text = "";
				TypeID = -1;

				editcode->SetFocus();
				ID =  aquery->FieldByName("ID")->AsAnsiString ;
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
		if (rcbpress->Text=="") {
			pressid  = -1;
		} else
		{
			pressid = (int)(rcbpress->Items->Objects[rcbpress->ItemIndex]);
		}
		if (edtypename->Text == "") {
			booktypeid = -1;
		} else
		{
			booktypeid = TypeID;
		}
		if (ShowMsg(Handle ,"确认修改书目信息?",1)==1)
		{
            logmessage = "修改书目《" + aquery->FieldByName("name")->AsAnsiString + "》的信息为《" + editbookname->Text.Trim() + "》";
			AddEvent(1,"图书目录管理",fuserid,fstgid,logmessage,fcon);

                            if (medityinzhang->Text=="") {
                               medityinzhang->Text="0"; 
                            }
			sql = "update BS_BookCatalog set name = '" + editbookname->Text.Trim() + "',userdefcode = '" + editbookself->Text.Trim() + "',isbn = '" + editisbn->Text.Trim() + "',Barcode = '" + editcode->Text ;
			sql = sql + "',author = '" +  editauthor->Text.Trim()  + "',price = " + editprice->Text + ",PressID = " + IntToStr(pressid);
			sql = sql + ",smallbooktypeid = " + IntToStr(booktypeid) + ",Pressdate = '" + DateToStr(datapressday->Date) + "',PressCount = '" + edpresscount->Text ;
			sql = sql + "',ISBNType = '" + edISBNtype->Text + "',Yizhe = '" + edyizhe->Text + "',Printcount = " + int(edprintcount->Value) ;
			sql = sql + ",Affix = '" + edaffix->Text + "',Bookformat = '" + cbformat->Text + "',Bind = '" + cbbind->Text ;
			sql = sql + "',Collectbook = '" + edbook->Text + "',BookWords = " + int(spepack->Value) + ",huojiangstate = '" + edhuojiangstate->Text + "'";
			sql = sql + ",yinzhang=" +medityinzhang->Text+",wordscount="+ meditwords->Text+",bcontent='"+ mcontent->Text.Trim()+"'";
			sql = sql + "  where ID = " + aquery->FieldByName("ID")->AsString ;
			try {
				query->Close();
				query->SQL->Clear();
				query->SQL->Add(sql);
				try {
					query->ExecSQL();
				} catch (...) {
                	ShowMsg(this->Handle,"请确认书目信息正确，修改失败！",3);
					return;
				}

				BtnView->Enabled = true;
				BtnNew->Enabled = true;
				BtnClear->Enabled = true;
				BtnCancel->Enabled = true;
				BtnUndo->Enabled = true;
				BtnDelete->Enabled = true;
				BtnImport->Enabled = true;
				BtnExport->Enabled = true;
				BtnJumptoLine->Enabled = true;
				RzToolButton1->Enabled = true;
				BtnAlignClient->Enabled = true;

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

void TfrmCatalogkanli::Query(String condition)
{
	if (aquery->Active)
	{
		aquery->Active = false;
	}
	String sql,sqlsum;
        if (condition==" where 1 = 1") {
			sql = "select  A.ID,A.barcode,A.userdefcode,A.UserBarcode,case when A.UserBarcode = A.Barcode then '' else A.UserBarcode end as UserBarcode1,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.author,A.Unavailable,A.TotalAmount,A.huojiangstate,A.bcontent,A.wordscount,A.yinzhang,"
			 "A.Yizhe,A.Pressdate,convert(varchar(10),A.Pressdate,111) as pdate,A.PressCount,A.Printcount,A.ISBNType,A.Collectbook,A.Bookformat,A.Bind,A.BookWords,A.Affix,A.Bk,case isnull(A.taoshu ,0) when 1 then '是' when  0 then '否' end taoshu,"
			 "B.abbreviatedname,A.bcontent,A.wordscount,A.yinzhang,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
			 " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID " + condition;

        }else
        {
			sql = "select A.ID,A.barcode,A.userdefcode,A.UserBarcode,case when A.UserBarcode = A.Barcode then '' else A.UserBarcode end as UserBarcode1,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.author,A.Unavailable,A.TotalAmount,A.huojiangstate,A.bcontent,A.wordscount,A.yinzhang,"
			 "A.Yizhe,A.Pressdate,convert(varchar(10),A.Pressdate,111) as pdate,A.PressCount,A.Printcount,A.ISBNType,A.Collectbook,A.Bookformat,A.Bind,A.BookWords,A.Affix,A.Bk,case isnull(A.taoshu ,0) when 1 then '是' when  0 then '否' end taoshu,"
			 "B.abbreviatedname,A.bcontent,A.wordscount,A.yinzhang,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
			 " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID " + condition;
         }
        sqlsum ="select count(*) as sumdanpin , sum(A.price) as totaljinge from bs_bookcatalog A left join BS_PressInfo B "
			 " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID " + condition;
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Active = true;
	 edpinzhong->Text = IntToStr(aquery->RecordCount);
	((TFloatField *)DBGrid1->DataSource->DataSet->FieldByName("price"))->DisplayFormat = "￥0.00";

        TADOQuery *aquery;
        aquery = new TADOQuery(NULL);
        aquery->Connection =fcon ;
        aquery->Close();
        aquery->SQL->Clear();
        aquery->SQL->Add(sqlsum);
        aquery->Open();
        delete aquery;
}

void __fastcall TfrmCatalogkanli::edtQueryKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
		if (Key==VK_RETURN) {
		   //	Query(edtQuery->Text);
			BtnClear->Enabled = true;
			BtnCancel->Enabled = true;
			BtnDelete->Enabled = true;
			BtnImport->Enabled = true;
			BtnExport->Enabled = true;
			BtnNew->Enabled = true;
			float totalprice = 0.00;
			while (!aquery->Eof)
			{
				totalprice = totalprice + aquery->FieldByName("Price")->AsFloat;
				aquery->Next();
			}
		}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::BtnNewClick(TObject *Sender)
{
	int maxid;
	AnsiString sql;
	sql = "select max(id) as id from BS_BookCatalog " ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	maxid = query->FieldByName("id")->AsInteger + 1;

	sql = "select A.ID,A.barcode,A.userdefcode,A.UserBarcode,case when A.UserBarcode = A.Barcode then '' else A.UserBarcode end as UserBarcode1,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.author,A.Unavailable,A.TotalAmount,A.huojiangstate,A.bcontent,A.wordscount,A.yinzhang,"
			 "A.Yizhe,A.Pressdate,convert(varchar(10),A.Pressdate,111) as pdate,A.PressCount,A.Printcount,A.ISBNType,A.Collectbook,A.Bookformat,A.Bind,A.BookWords,A.Affix,A.Bk,case isnull(A.taoshu ,0) when 1 then '是' when  0 then '否' end taoshu,"
			 "B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
			 " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID where A.ID > " + IntToStr(maxid) ;
			sql = sql + " and A.type = 0";
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Active = true;
	edpinzhong->Text = IntToStr(aquery->RecordCount);
	edquery->Text = "";
	Press(0);

	//PageControlBook->Enabled = true;


	modle = 1;// 添加模式
	BtnView->Enabled = false;
	BtnNew->Enabled = false;
	BtnClear->Enabled = false;
	BtnCancel->Enabled = false;
	BtnUndo->Enabled = false;
	BtnDelete->Enabled = false;
	BtnImport->Enabled = false;
	BtnExport->Enabled = false;
	BtnJumptoLine->Enabled = false;
	RzToolButton1->Enabled = false;
	BtnAlignClient->Enabled = false;
	BtnSave->Enabled = true;
	btncnacelsave->Enabled = true;
	GroupBox1->Enabled = true;
	editcode->SetFocus();

	editcode->Text = "";
	editisbn->Text = "";
	editbookname->Text = "";
	editbookself->Text = "";
	editprice->Text = "￥0.00";
	editauthor->Text = "";
	rcbpress->Text = "";
	datapressday->Date = Date();
	edpresscount->Text = "";
	edISBNtype->Text = "";
	edyizhe->Text = "";
	edprintcount->Value = 1;
	edaffix->Text = "";
	cbformat->ItemIndex = -1;
	cbbind->ItemIndex = -1;
	edbook->Text = "";
	spepack->Value = 1;
	edhuojiangstate->Text = "";
	meditwords->Text = "0";
	medityinzhang->Text = "0";
	mcontent->Text = "";
	edtypequery->Text = "";
	edtypename->Text = "";
	TypeID = -1;
}
//---------------------------------------------------------------------------


void __fastcall TfrmCatalogkanli::BtnClearClick(TObject *Sender)
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
                     //	AddEvent(1,"图书目录管理",fuserid,fstgid,"修改书目:"+logmessage,fcon);
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
	BtnImport->Enabled = false;
	BtnExport->Enabled = false;
	BtnJumptoLine->Enabled = false;
	RzToolButton1->Enabled = false;
	BtnAlignClient->Enabled = false;
	BtnSave->Enabled = true;
	btncnacelsave->Enabled = true;
	GroupBox1->Enabled = true;
}
//---------------------------------------------------------------------------
void TfrmCatalogkanli::cumvalue(AnsiString sqlsum)
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
void __fastcall TfrmCatalogkanli::BtnCancelClick(TObject *Sender)
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
       ShowMsg(Handle ,"已作废",3);
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::BtnDeleteClick(TObject *Sender)
{
	AnsiString delIDstr;
	AnsiString sql;
        AnsiString logmessage;
        Tfrmpassword *frm;
	if (aquery->IsEmpty() ) {
		return;
	}

        frm= new Tfrmpassword(NULL);
        //frm->password='';
        if (frm->ShowModal()==mrOk) {   //catalogdelpassword

           if (frm->editpassword->Text!=paw) {
              ShowMsg(Handle ,"密码错误!",3);
              return;
           }else delete frm;

        }else return;


	if (ShowMsg(Handle ,"确认删除吗?",1)!=1)
	{
		return;
	}
        delIDstr = "(";
	for (int i =0; i < DBGrid1->SelectedRows->Count ; i++) {
		aquery->GotoBookmark(DBGrid1->SelectedRows->Items[i]);
		if (aquery->RecordCount > 0) {
			delIDstr = delIDstr+aquery->FieldByName("ID")->AsString +",";
                logmessage =logmessage+aquery->FieldByName("name")->AsString+",";
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
	AddEvent(1,"图书目录管理",fuserid,fstgid,"删除书目:"+logmessage,fcon);
        }catch (Exception &E) {
        ShowMsg(Handle ,"该数据跟系统其他数据有关联，不能删除！",3);

        }

	aquery->Active = false;
	aquery->Active = true;
	edpinzhong->Text = IntToStr(aquery->RecordCount);
	editcode->Text = "";
	editisbn->Text = "";
	editbookname->Text = "";
	editbookself->Text = "";
	editprice->Text = "￥0.00";
	editauthor->Text = "";
	rcbpress->Text = "";
	datapressday->Date = Date();
	edpresscount->Text = "";
	edISBNtype->Text = "";
	edyizhe->Text = "";
	edprintcount->Value = 1;
	edaffix->Text = "";
	cbformat->ItemIndex = -1;
	cbbind->ItemIndex = -1;
	edbook->Text = "";
	spepack->Value = 1;
	edhuojiangstate->Text = "";
}
//---------------------------------------------------------------------------

int __fastcall TfrmCatalogkanli::BrocodeToPress(String brocode)
{
	if (brocode.Length() != 13 ) {
    	return -1;
	}
	String tmp = brocode.SubString(5,1),pressnum;
	int bit = StrToInt(tmp);
	switch (bit) {
		case 0:
			pressnum =  brocode.SubString(4,3);
			break;
		case 1:
		case 2:
		case 3:
			pressnum =  brocode.SubString(4,4);
			break;
		case 5:
		case 6:
		case 7:
			pressnum =  brocode.SubString(4,5);
			break;
		case 8:
			pressnum =  brocode.SubString(4,6);
			break;
	default:
		;
	}
	AnsiString sql;
	sql = "select ID from BS_PressInfo where PresentNum like '%" + pressnum + "%'";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	int pressid;
	if (query->RecordCount == 0) {
		pressid = -1;
	}
	else
	{
		pressid = query->FieldByName("ID")->AsInteger ;
	}

	return pressid;
}


void __fastcall TfrmCatalogkanli::FormShow(TObject *Sender)
{
  //	edtQuery->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::BtnExportClick(TObject *Sender)
{
	if (aquery->Active &&  aquery->RecordCount > 0) {
		DbgridToExcel(DBGrid1);
   }
}
//---------------------------------------------------------------------------

//Excel导出函数
bool __fastcall TfrmCatalogkanli::DbgridToExcel(TDBGrid* dbg)
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
void __fastcall TfrmCatalogkanli::BtnImportClick(TObject *Sender)
{
    int maxid;
	AnsiString sql;
	sql = "select max(id) as id from BS_BookCatalog " ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	ds->DataSet = NULL;
	maxid = query->FieldByName("id")->AsInteger + 1;
	sql = "select A.ID,A.barcode,A.userdefcode,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.author,A.Unavailable,A.TotalAmount,A.huojiangstate,"
		  "A.Yizhe,A.Pressdate,A.PressCount,A.Printcount,A.ISBNType,A.Collectbook,A.Bookformat,A.Bind,A.BookWords,A.Affix,A.Bk,case isnull(A.taoshu ,0) when 1 then '是' when  0 then '否' end taoshu,"
		  "B.abbreviatedname,C.name as typename,A.bcontent,A.wordscount,A.yinzhang from bs_bookcatalog A left join BS_PressInfo B "
		  " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID where A.ID > " + IntToStr(maxid) ;
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Active = true;
	edpinzhong->Text = IntToStr(aquery->RecordCount);
	TfrmExcelImport* frm = new TfrmExcelImport(Owner,aquery);
	frm->Init(Application,fcon,fstgid);
	if (frm->ShowModal() == mrOk)
	{

	}
	delete frm;
	ds->DataSet = aquery;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::DBGrid1CellClick(TColumn *Column)
{
	if (aquery->IsEmpty()) {
	 	return ;
	}
	if (modle == 1) {
		if (ShowMsg(this->Handle,"正在添加书目，确定复制该书目信息到录入框？",1)!= 1)
		{
			editcode->SetFocus();
			return;
		}
	}
	if (modle == 2) {
		return;
	}
	editcode->Text  = aquery->FieldByName("barcode")->AsAnsiString.Trim() ;
	editisbn->Text = aquery->FieldByName("ISBN")->AsAnsiString.Trim() ;
	editbookname->Text = aquery->FieldByName("name")->AsAnsiString.Trim() ;
	editbookself->Text = aquery->FieldByName("userdefcode")->AsAnsiString.Trim();
	editauthor->Text =aquery->FieldByName("author")->AsAnsiString.Trim();
	editprice->Text = FormatFloat("￥0.00",aquery->FieldByName("price")->AsFloat);
	if (aquery->FieldByName("pid")->AsAnsiString == "") {
		rcbpress->ItemIndex = -1;
	}
	else
	{
		rcbpress->ItemIndex = rcbpress->Items->IndexOfObject((TObject*)aquery->FieldByName("pid")->AsInteger );
	}
	TypeID = aquery->FieldByName("smallBookTypeID")->AsInteger ;
	edtypename->Text = aquery->FieldByName("typename")->AsAnsiString ;
	datapressday->Date = aquery->FieldByName("Pressdate")->AsDateTime ;
	edpresscount->Text = aquery->FieldByName("PressCount")->AsString.Trim() ;
	edISBNtype->Text = aquery->FieldByName("ISBNType")->AsString.Trim() ;
	edyizhe->Text = aquery->FieldByName("Yizhe")->AsString.Trim() ;
	edprintcount->Text = aquery->FieldByName("Printcount")->AsString.Trim() ;
	edaffix->Text = aquery->FieldByName("Affix")->AsString.Trim() ;
	cbformat->Text = aquery->FieldByName("Bookformat")->AsString.Trim() ;
	cbbind->Text = aquery->FieldByName("Bind")->AsString.Trim() ;
	edbook->Text = aquery->FieldByName("Collectbook")->AsString.Trim() ;
	edhuojiangstate->Text = aquery->FieldByName("huojiangstate")->AsString.Trim() ;
	spepack->Value = aquery->FieldByName("BookWords")->AsInteger ;
	edhuojiangstate->Text = aquery->FieldByName("huojiangstate")->AsString.Trim() ;
	mcontent->Text  = aquery->FieldByName("bcontent")->AsString;
	meditwords->Text =    aquery->FieldByName("wordscount")->AsAnsiString;
    medityinzhang->Text =   aquery->FieldByName("yinzhang")->AsAnsiString;
	//edtaoshu->Text = aquery->FieldByName("taoshu")->AsString ;
	//modle = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::datapressdayKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
		edpresscount->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::sedpresscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
	   //	PageControlBook->ActivePage = tsdetail;
       BtnSave->Click();
	   editcode->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::edISBNtypeKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
    	edyizhe->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::edyizheKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        edprintcount->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::edprintcountKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
        edaffix->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::edaffixKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
		edbook->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::cbformatKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
        cbbind->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::cbbindKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        meditwords->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::edbookKeyPress(TObject *Sender, wchar_t &Key)
{

	if (Key == '\r') {
		edhuojiangstate->SetFocus();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmCatalogkanli::edbkKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
		BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::BtnViewClick(TObject *Sender)
{
	
	TfrmBookQuery *frm = new  TfrmBookQuery(Application,fcon);
	if (mrOk == frm->ShowModal()) {
		//int type = frm->cbQueryType->ItemIndex ;
		String Condition = frm->getcontion();
		Query(Condition);
	}
	delete frm;

	modle = 0;
	edquery->Text = "";
	Press(0);
	BtnClear->Enabled = true;
	BtnCancel->Enabled = true;
	BtnDelete->Enabled = true;
	BtnImport->Enabled = true;
	BtnExport->Enabled = true;
	BtnNew->Enabled = true;
	editprice->Enabled = true;
	BtnJumptoLine->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::btaddtypeClick(TObject *Sender)
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

void __fastcall TfrmCatalogkanli::btaddpressClick(TObject *Sender)
{
	TfrmPressAdmin* frm = new TfrmPressAdmin(Application);
	frm->Init(Application, fcon);
	frm->FormStyle = fsNormal ;
    frm->Visible = false;
	frm->Position = poMainFormCenter ;
	frm->ShowModal();
	delete frm;
	String sql;
	sql = "select ID,abbreviatedname,PresentNum from BS_PressInfo ";
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	rcbpress->Clear();
	while(!aq->Eof)
	{
		rcbpress->AddItem(aq->FieldByName("PresentNum")->AsAnsiString.Trim() + aq->FieldByName("abbreviatedname")->AsAnsiString, (TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
   	}
	delete aq;
}

//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::cbsaletypeChange(TObject *Sender)
{
	DBGrid1->Visible = true;
	type = 0;
	BtnJumptoLine->Enabled = true;
}
//---------------------------------------------------------------------------


void __fastcall TfrmCatalogkanli::editwenjutiaomaoKeyPress(TObject *Sender, wchar_t &Key)

{
  if (Key == VK_RETURN) {
	Perform(WM_NEXTDLGCTL, 0, 0);
 }
}
//---------------------------------------------------------------------------

AnsiString TfrmCatalogkanli::GetSelf(AnsiString context)
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
AnsiString TfrmCatalogkanli::BarCodeToISSN(AnsiString BarCode)
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
AnsiString TfrmCatalogkanli::ISSNToBarCode(AnsiString ISSN)
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


void __fastcall TfrmCatalogkanli::BtnJumptoLineClick(TObject *Sender)
{
	if (!aquery->Active || aquery->RecordCount == 0) {
		return;
	}
	String sql;
	TfrmSetunite *frm = new TfrmSetunite(Application,fcon);
	if (frm->ShowModal() == mrOk ) {
		for (int i = 0; i < DBGrid1->SelectedRows->Count; i++) {
			aquery->GotoBookmark(DBGrid1->SelectedRows->Items[i]);
            sql = "select Price from BS_BookCatalog where id = " + aquery->FieldByName("ID")->AsString ;
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->Open();
			sql = "";
			if (frm->cbprice->Checked ) {
				sql = "update BS_BookCatalog set Price = " + frm->editprice->Text;
			}
			if (frm->cbbook->Checked && sql != "") {
				sql = sql + ",Collectbook = '" + frm->edbook->Text + "'";
			}
			if (frm->cbbook->Checked && sql == "") {
				sql = "update BS_BookCatalog set Collectbook = '" + frm->edbook->Text + "'";
			}
			if (frm->cbtype->Checked && sql != "") {
				sql = sql + ",smallBookTypeID = " + IntToStr(frm->Gettypeid() );
			}
			if (frm->cbtype->Checked && sql == "") {
				sql = "update BS_BookCatalog set smallBookTypeID = " + IntToStr(frm->Gettypeid() );
			}
			if (frm->cbpress->Checked && sql != "") {
				sql = sql + ",PressID = " + IntToStr(frm->Getpressid() );
			}
			if (frm->cbpress ->Checked && sql == "") {
				sql = "update BS_BookCatalog set PressID = " + IntToStr(frm->Getpressid() );
			}
			if (frm->cbpressday ->Checked && sql != "") {
				sql = sql + ",Pressdate = '" + DateToStr(frm->datapressday->Date) + "'";
			}
			if (frm->cbpressday ->Checked && sql == "") {
				sql = "update BS_BookCatalog set Pressdate = '" + DateToStr(frm->datapressday->Date) + "'";
			}
			if (frm->cbpresscount ->Checked && sql != "") {
				sql = sql + ",PressCount = " + IntToStr(frm->sedpresscount->IntValue);
			}
			if (frm->cbpresscount ->Checked && sql == "") {
				sql = "update BS_BookCatalog set PressCount = " + IntToStr(frm->sedpresscount->IntValue);
			}
			if (sql == "") {
				return;
			}
			if (sql != "") {
				sql = sql + " where id = " + aquery->FieldByName("ID")->AsString ;
			}
			query->Close();
			query->SQL->Clear();
			query->SQL->Add(sql);
			query->ExecSQL();
		}
	}
	delete frm;
	aquery->Active = false;
	aquery->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

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
		if (Key == VK_F3) {   //统一
		BtnJumptoLine->Click();
	}
	if (Key == VK_F7) {     //导入
		BtnImport->Click();
	}
	if (Key == VK_F6) {      //导出
		BtnExport->Click();
	}
	if (Key == VK_F10) {      //合并重书
		BtnAlignClient->Click();
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

void TfrmCatalogkanli::Press(int mode)
{
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql;
	if (mode == 1) {
		sql = "select ID,presentnum,abbreviatedname from BS_PressInfo where abbreviatedname like '%" + edquery->Text.Trim() + "%'" ;
	}
	else
	{
		sql = "select ID,presentnum,abbreviatedname from BS_PressInfo ";
	}
	rcbpress->Clear();
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	while(!aq->Eof)
	{
		rcbpress->AddItem(aq->FieldByName("abbreviatedname")->AsAnsiString, (TObject*)aq->FieldByName("ID")->AsInteger );
		aq->Next();
	}
	aq->First();
	if (mode == 1) {
		rcbpress->ItemIndex = rcbpress->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger);
	}
	else
	{
		rcbpress->ItemIndex = -1;
	}
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::edqueryKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		if (edquery->Text != "") {
			Press(1);
		}
		rcbpress->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::editisbnKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		AnsiString bro;
		try {
			bro = ISBNToBarcode(editisbn->Text);
		} catch (...) {
		}
		editcode->Text =  bro;
		int pressid = BrocodeToPress(editcode->Text);
		rcbpress->ItemIndex = rcbpress->Items->IndexOfObject((TObject*)pressid );
        editbookname->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------


void __fastcall TfrmCatalogkanli::editbookselfKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        editprice->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::N1Click(TObject *Sender)
{
	for (int i = 1; i <= aquery->RecordCount; i++) {
		DBGrid1->DataSource->DataSet->RecNo = i;
		DBGrid1->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::DBGrid1TitleClick(TColumn *Column)
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

void __fastcall TfrmCatalogkanli::BtnAlignClientClick(TObject *Sender)
{
	Tfrmmutibook *frm = new Tfrmmutibook(Application,fcon);
	frm->stgid = fstgid;
	frm->userid = fuserid;
	frm->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::edpresscountKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if (Key == '\r') {
		if (modle == 1) {
			switch (MessageBox(this->Handle,"是否继续录入下面信息？","先行者书业智管平台-询问",MB_ICONQUESTION|MB_YESNO+MB_DEFBUTTON2)) {
			case 6:
				edISBNtype->SetFocus();
			break;
			case 7:
				BtnSave->Click();
			break;
			default:
				;
			}
		}
		else
		{
			BtnSave->Click();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::BtnUndoClick(TObject *Sender)
{
	for (int i =0; i < DBGrid1->SelectedRows->Count ; i++) {
		aquery->GotoBookmark(DBGrid1->SelectedRows->Items[i]);
		if (aquery->RecordCount > 0) {
			try {
				aquery->Edit();
				aquery->FieldByName("Unavailable")->Value = 1;
				aquery->UpdateBatch(arAll);
			} catch (...) {
			}
		}
	}
	aquery->Active = false;
	aquery->Active = true;
	edpinzhong->Text = IntToStr(aquery->RecordCount);
        ShowMsg(Handle ,"已取消作废",3);
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::RzToolButton1Click(TObject *Sender)
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
	sql = "insert into bs_userbarcode(Name,UserBarcode,amount,userid,Price) select bs_bookcatalog.name,bs_bookcatalog.userbarcode,0," + IntToStr(fuserid) +
		",bs_bookcatalog.price from bs_bookcatalog where id in(" + catalogid + ")";
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->ExecSQL();
	Tfrmprintbarcode *frm = new Tfrmprintbarcode(Application,fcon,fuserid);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------


void __fastcall TfrmCatalogkanli::edhuojiangstateKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if (Key == '\r') {
        cbformat->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::meditwordsKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == '\r') {
		medityinzhang->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::medityinzhangKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if (Key == '\r') {
        mcontent->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::mcontentKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == '\r') {
        BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::btncnacelsaveClick(TObject *Sender)
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
	BtnImport->Enabled = true;
	BtnExport->Enabled = true;
	BtnJumptoLine->Enabled = true;
	RzToolButton1->Enabled = true;
	BtnAlignClient->Enabled = true;

	BtnSave->Enabled = false;
	btncnacelsave->Enabled = false;
	GroupBox1->Enabled = false;
	editprice->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::RzButton1Click(TObject *Sender)
{
    Screen->Cursor = crHourGlass;
        AnsiString sql;
           sql = "select A.ID,A.barcode,A.userdefcode,A.UserBarcode,case when A.UserBarcode = A.Barcode then '' else A.UserBarcode end as UserBarcode1,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.author,A.Unavailable,A.TotalAmount,A.huojiangstate,A.bcontent,A.wordscount,A.yinzhang,"
		 "A.Yizhe,A.Pressdate,convert(varchar(10),A.Pressdate,111) as pdate,A.PressCount,A.Printcount,A.ISBNType,A.Collectbook,A.Bookformat,A.Bind,A.BookWords,A.Affix,A.Bk,case isnull(A.taoshu ,0) when 1 then '是' when  0 then '否' end taoshu,"
		 "B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
		 " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID ";
		sql = sql + " and A.type = 0";

        aquery->Close();
        aquery->SQL->Clear();
        aquery->SQL->Add(sql);
        aquery->Open();
	//aquery->Active = false;
      //	aquery->Filtered = false;
       //	aquery->Active = true;
	edpinzhong->Text = IntToStr(aquery->RecordCount);
        Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::RzButton2Click(TObject *Sender)
{
 Screen->Cursor = crHourGlass;
        Screen->Cursor = crHourGlass;
        AnsiString sql;
        sql = "select A.ID,A.barcode,A.userdefcode,A.UserBarcode,case when A.UserBarcode = A.Barcode then '' else A.UserBarcode end as UserBarcode1,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.author,A.Unavailable,A.TotalAmount,A.huojiangstate,A.bcontent,A.wordscount,A.yinzhang,"
        "A.Yizhe,A.Pressdate,convert(varchar(10),A.Pressdate,111) as pdate,A.PressCount,A.Printcount,A.ISBNType,A.Collectbook,A.Bookformat,A.Bind,A.BookWords,A.Affix,A.Bk,case isnull(A.taoshu ,0) when 1 then '是' when  0 then '否' end taoshu,"
        "B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
        " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID where Unavailable = 0";
        sql = sql + " and A.type = 0";

        aquery->Close();
        aquery->SQL->Clear();
        aquery->SQL->Add(sql);
        aquery->Open();

       //	aquery->Active = false;
       //	aquery->Filtered = true;
       //	aquery->Filter =  " Unavailable = 0";
       //	aquery->Active = true;
	edpinzhong->Text = IntToStr(aquery->RecordCount);
       Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::RzButton3Click(TObject *Sender)
{
            Screen->Cursor = crHourGlass;

            AnsiString sql;
        sql = "select A.ID,A.barcode,A.userdefcode,A.UserBarcode,case when A.UserBarcode = A.Barcode then '' else A.UserBarcode end as UserBarcode1,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.author,A.Unavailable,A.TotalAmount,A.huojiangstate,A.bcontent,A.wordscount,A.yinzhang,"
        "A.Yizhe,A.Pressdate,convert(varchar(10),A.Pressdate,111) as pdate,A.PressCount,A.Printcount,A.ISBNType,A.Collectbook,A.Bookformat,A.Bind,A.BookWords,A.Affix,A.Bk,case isnull(A.taoshu ,0) when 1 then '是' when  0 then '否' end taoshu,"
        "B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
        " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID where Unavailable = 1";
        sql = sql + " and A.type = 0";

        aquery->Close();
        aquery->SQL->Clear();
        aquery->SQL->Add(sql);
        aquery->Open();
      Screen->Cursor = crDefault;

	edpinzhong->Text = IntToStr(aquery->RecordCount);
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::spselectTypeClick(TObject *Sender)
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


void __fastcall TfrmCatalogkanli::edtypequeryKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		Tfrmselecttype * frm = new Tfrmselecttype(Application,fcon,edtypequery->Text);
		if (mrOk == frm->ShowModal())
		{
			TypeID = frm->GetSelectID();
			edtypename->Text = frm->GetSelect();
		}
		delete frm;
		edquery->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogkanli::spepackKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		edtypequery->SetFocus();
	}
}
//---------------------------------------------------------------------------

