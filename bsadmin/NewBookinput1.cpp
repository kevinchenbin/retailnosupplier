//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "NewBookinput1.h"
#include "..\catalogadmin\PressAdminForm.h"
#include "..\catalogadmin\BooKTypeAdminForm.h"
#include "Selecttype.h"
#include "BooKTypeAdminForm.h"
#include "global.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzCmboBx"
#pragma link "RzDBGrid"
#pragma link "RzRadChk"
#pragma link "RzEdit"
#pragma link "RzSpnEdt"
#pragma link "RzLine"
#pragma resource "*.dfm"
Tfrmnewbook1 *frmnewbook1;
//---------------------------------------------------------------------------
__fastcall Tfrmnewbook1::Tfrmnewbook1(TComponent* Owner,TADOConnection *con)
	: TForm(Owner)
{
   aquery->Connection = con;
   aqinsert->Connection = con;
   fcon = con;
   String sql;
   sql = "select max(id) as id from bs_bookcatalog";
   TADOQuery *aq = new TADOQuery(this);
   aq->Connection = con;
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->Open();
   int id = aq->FieldByName("id")->AsInteger ;
   sql = "select value from sys_bsset where name = 'crtuserbarcode'";
   aq->Close();
   aq->SQL->Clear();
   aq->SQL->Add(sql);
   aq->Open();
   userbar = aq->FieldByName("value")->AsBoolean ;
   delete aq;
   sql = "select A.pressid as pid,"
		 "A.*,"
		 "B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
		 " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID where A.ID > " + IntToStr(id) ;
   if (cbsaletype->Text == "图书") {
		sql = sql + " and A.type = 0";
   }
   else if (cbsaletype->Text == "期刊") {
		sql = sql + " and A.type = 1";
   }
   else if (cbsaletype->Text == "文具") {
		sql = sql + " and A.type = 2";
   }
   else
   {
   		sql = sql + " and A.type > 2";
   }
   aquery->Close();
   aquery->SQL->Clear();
   aquery->SQL->Add(sql);
   aquery->Open();
   ReadyData();
   datapressday->Date = Date();
   AnsiString date = DateToStr(Date());
	date = date.SubString(0,4);
	sedyear->Value = StrToInt(date);
	constbarcode = "9780000000000";
        NewBooKCatalogID = -1;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmnewbook1::BtnExitClick(TObject *Sender)
{
	ModalResult = mbCancel  ;
}

//---------------------------------------------------------------------------
void __fastcall Tfrmnewbook1::FormClose(TObject *Sender, TCloseAction &Action)
{
	ModalResult = mbCancel  ;
  	Action = caFree ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmnewbook1::editcodeKeyPress(TObject *Sender, wchar_t &Key)
{
	String sql;
	if (Key==VK_RETURN)
	{
	   sql = "select A.ID,A.barcode,A.userdefcode,A.UserBarcode,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.author,A.Unavailable,A.TotalAmount,A.date,A.type,A.huojiangstate,"
		 "A.Yizhe,A.Pressdate,A.PressCount,A.Printcount,A.ISBNType,A.Collectbook,A.Bookformat,A.Bind,A.BookWords,A.Affix,A.Bk,A.daixiao,A.wordscount,A.yinzhang,"
		 "B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
		 " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID where A.barcode =  '" + editcode->Text + "'";
		if (cbsaletype->Text == "图书") {
			sql = sql + " and A.type = 0";
		}

	   aquery->Close();
	   aquery->SQL->Clear();
	   aquery->SQL->Add(sql);
	   aquery->Open();
	   /*aqinsert->Close();
	   aqinsert->SQL->Clear();
	   aqinsert->SQL->Add(sql);
	   aqinsert->Open(); */
	   int pressid;
	   pressid = BrocodeToPress(editcode->Text);
	   if (pressid >= 0) {
		rcbpress->ItemIndex = rcbpress->Items->IndexOfObject((TObject*)pressid);
	   }
	   else
	   {
       	rcbpress->ItemIndex = -1;
	   }
	   ((TFloatField *)RzDBGrid1->DataSource->DataSet->FieldByName("price"))->DisplayFormat = "0.00";
	   if (aquery->RecordCount == 0) {

	   }
	   editisbn->Text = editcode->Text ;
	   editbookname->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmnewbook1::SpeedButton1Click(TObject *Sender)
{
  	editisbn->Text =  BuildISBNCode(editisbn->Text);
}
//---------------------------------------------------------------------------
void __fastcall Tfrmnewbook1::editbooknameKeyPress(TObject *Sender, wchar_t &Key)
{
	   if (Key==VK_RETURN) {
		 if (editbookname->Text =="") {

                                  ShowMsg(Handle ,"书名不能为空！",3);
				return;
		 }
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
                        if (k<=58&&k>=48) {    //数字
                          t4=t4+t3;
                        }
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

			AnsiString sql = "select A.ID,A.barcode,A.userdefcode,A.UserBarcode,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.author,A.Unavailable,A.TotalAmount,A.date,A.type,A.huojiangstate,"
				"A.Yizhe,A.Pressdate,A.PressCount,A.Printcount,A.ISBNType,A.Collectbook,A.Bookformat,A.Bind,A.BookWords,A.Affix,A.Bk,A.wordscount,A.yinzhang,"
				"B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
				" on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID where A.name like '%" + editbookname->Text + "%'";
				if (cbsaletype->Text == "图书") {
					sql = sql + " and A.type = 0";
		 		}

			aquery->Close();
			aquery->SQL->Clear();
			aquery->SQL->Add(sql);
			aquery->Open();

			editbookself->SetFocus();
	   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrmnewbook1::editpriceKeyPress(TObject *Sender, wchar_t &Key)
{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '-')&&(Key != '\b')) {
		Key = NULL;
	}
	if (Key==VK_RETURN) {
		if (editprice->Text == "" ) {
			editprice->Text = "0";
		}

        try {
		float price = StrToFloat(editprice->Text) ;
                editprice->Text = FormatFloat("0.00",price);
		editauthor->SetFocus();
	} catch (...) {
                ShowMsg(Handle ,"请输入正确的定价！",3);
                editprice->SetFocus();
		return;
	}


	}

}
//---------------------------------------------------------------------------
void Tfrmnewbook1::ReadyData()
{
	try
	{
		String sql ;
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		sql = "select ID,presentnum,abbreviatedname from BS_PressInfo ";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		while(!aq->Eof)
		{
			rcbpress->AddItem(aq->FieldByName("abbreviatedname")->AsAnsiString, (TObject*)aq->FieldByName("ID")->AsInteger );
			cbpress->AddItem(aq->FieldByName("abbreviatedname")->AsAnsiString, (TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}

               	sql = "select id,code,name from BS_BookType ";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		while(!aq->Eof)
		{
			cbtype->AddItem(aq->FieldByName("code")->AsAnsiString+aq->FieldByName("name")->AsAnsiString, (TObject*)aq->FieldByName("ID")->AsInteger );
			qcbtype->AddItem(aq->FieldByName("code")->AsAnsiString+aq->FieldByName("name")->AsAnsiString, (TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}



		delete aq;
	}catch(...)
	{}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmnewbook1::editauthorKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key==VK_RETURN)
	{
		spepack->SetFocus();
	}
}
//---------------------------------------------------------------------------
int  Tfrmnewbook1:: GetID()
{
	return NewBooKCatalogID;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmnewbook1::rcbpressKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key==VK_RETURN)
	{
          if (edquery->Text !="")
          {
          if (rcbpress->Items->Count >0) {
               rcbpress->ItemIndex =0;
          }
          }
	  datapressday->SetFocus();
	}
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall Tfrmnewbook1::BtnSaveClick(TObject *Sender)
{
   try
   {
	if (1== type) {
		int pressid = -1,booktypeid = -1;
		if (cbpress->Text != "") {
			try {
				pressid = (int)cbpress->Items->Objects[cbpress->ItemIndex];
			} catch (...) {
				ShowMsg(Handle ,"请选择正确的出版社！",3);
				return;
			}
		}
		if (edyearprice->Text == "") {
			edyearprice->Text = "0";
		}
		if (editqikanname->Text == "" )
		{
			ShowMsg(Handle ,"刊名不能为空！",3);
			return;
		}
		if ((editqikanprice->Text == "￥0.00")||(editqikanprice->Text == "")) {
			ShowMsg(Handle ,"定价不能为空！",3);
			return;
		}
		int totalkanqi;
		float price = 0.0;
		int qikanshu;
	     //	if (editqikanqihao->Text == "") {
	     //		ShowMsg(Handle ,"期刊号不能为空！",3);
	     //		editqikanqihao->SetFocus();
	      //		return;
	     //	}
		try {
			price = StrToFloat(editqikanprice->Text);
                        if (editqikanqihao->Text =="") {
                               AnsiString s1,selft,qihao;
                     selft = editqikanself->Text.Trim();
                     s1 = RightStr(selft,4);
                     qihao = RightStr(s1,2);  //取出期号
                     qikanshu=StrToInt(qihao);
                        }else
                        {
                         qikanshu = StrToInt(editqikanqihao->Text);
                        }

		} catch (...) {
			return;
		}
		if (cbkanqi->Text != "") {
			if (cbkanqi->Text == "周刊") {
				totalkanqi = 52;
			}
			else if (cbkanqi->Text == "半月刊") {
				totalkanqi = 24;
			}
			else if (cbkanqi->Text == "月刊") {
				totalkanqi = 12;
			}
			else if (cbkanqi->Text == "双月刊") {
				totalkanqi = 6;
			}
			else if (cbkanqi->Text == "季刊") {
				totalkanqi = 4;
			}
			else if (cbkanqi->Text == "半年刊") {
				totalkanqi = 2;
			}
			else if (cbkanqi->Text == "年刊") {
				totalkanqi = 1;
			}
		       //	if (totalkanqi < qikanshu) {
			   //   ／	editqikanqihao->SetFocus();
			   //	ShowMsg(Handle ,"录入期数过大，请重新录入！",3);
			   //	return;
		       //	}
		}
		try
		{
			if (ShowMsg(Handle ,"确定要产生新期刊吗?",1)== 1) {

                        
				aqinsert->Append();
				aqinsert->FieldByName("isbn")->AsAnsiString = editqikanissn->Text ;
				aqinsert->FieldByName("name")->AsAnsiString = editqikanname->Text ;
				aqinsert->FieldByName("userdefcode")->AsAnsiString = editqikanself->Text ;
				aqinsert->FieldByName("price")->AsFloat = StrToFloat(editqikanprice->Text);
				aqinsert->FieldByName("barcode")->AsAnsiString = editqikanmao->Text ;
				aqinsert->FieldByName("date")->AsDateTime = Now();
				aqinsert->FieldByName("Unavailable")->AsInteger = 1;
				aqinsert->FieldByName("type")->AsInteger = 1;
				aqinsert->FieldByName("presscount")->AsAnsiString = editqikanqihao->Text ;
				aqinsert->FieldByName("year")->AsAnsiString = sedyear->Text ;
				aqinsert->FieldByName("pid")->AsInteger = pressid;
                                aqinsert->FieldByName("bk")->AsAnsiString =editbk->Text ;
                                aqinsert->FieldByName("daixiao")->AsAnsiString = cbshengdaia->Text;
				if (qcbtype->Text == "") {
					aqinsert->FieldByName("smallBookTypeID")->AsInteger = -1;
				}
				else
				{                                                      //////////////////////
                                        TypeID = GetIDFromText(2);
					aqinsert->FieldByName("smallBookTypeID")->AsInteger = TypeID;
				}
				aqinsert->FieldByName("Bookformat")->AsAnsiString = cbkanqi->Text ;
				aqinsert->FieldByName("duokan")->AsBoolean = chduokan->Checked;
				if (chduokan->Checked ) {
					aqinsert->FieldByName("duokantext")->AsAnsiString = cbduokan->Text;
					aqinsert->FieldByName("duokannum")->AsInteger = sedkannum->Value;
				}
				aqinsert->FieldByName("yearprice")->AsFloat =  StrToFloat(edyearprice->Text);
				aqinsert->FieldByName("kanhao")->AsAnsiString =  edkanhao->Text ;
				aqinsert->FieldByName("tongyikanhao")->AsAnsiString =  edtykanhao->Text ;
				aqinsert->UpdateBatch(arAll);

				editqikanissn->Text ="";
				editqikanname->Text = "";
				editqikanself->Text = "";
				editqikanprice->Text="0.00";
				editqikanmao->Text= "";
				editqikanqihao->Text="";
				chduokan->Checked = false;
				cbduokan->ItemIndex = 0;
				cbduokan->Visible = false;
				sedkannum->Value = 1;
				sedkannum->Visible = false;
				Label31->Visible = false;
				edyearprice->Text = "0.00";
				edkanhao->Text = "";
				edtykanhao->Text = "";
				TypeID = -1;
				edpequery->Text = "";
				edpequery->Text = "";
                                 editbk->Text="";
				AnsiString date = DateToStr(Date());
				date = date.SubString(0,4);
				sedyear->Value = StrToInt(date);
				Press1(0);

                                ID = aqinsert->FieldByName("ID")->AsInteger;
                                NewBooKCatalogID = ID;
				if (!rzcbinput->Checked) {

					if (modle == 1) {
						StorageMng->AddNote(-1,ID);
					}
					else if (modle == 3) {
						ProcureMng->AddNote(0,ID);
					}
					else if (modle == 4) {
						BIorder->AddNote(0,ID);
					}
					ModalResult = mbOK ;
				}else     //连续录入
				{

					if (modle == 1) {
						StorageMng->AddNote(-1,ID);
					}
					else if (modle == 3) {
						ProcureMng->AddNote(0,ID);
					}
					else if (modle == 4) {
						BIorder->AddNote(0,ID);
					}
					return;
				}
			}
		}
		catch(...)
		{}
	}
	if (2 == type) {
		if ((editwenjuprice->Text=="￥0.00")||(editwenjuprice->Text=="")) {
			ShowMsg(Handle ,"请输入定价！",3);
			return;
		}
		if (editwenjuname->Text == "") {
			ShowMsg(Handle ,"请输入品名！",3);
			return;
		}
		if (ShowMsg(Handle ,"确定要产生文具吗?",1)== 1) {
			try
			{
				AnsiString code = editwenjutiaomao->Text ;
				AnsiString userbarcode,sql;
				if (userbar) {
                	TADOQuery *aq = new TADOQuery(this);
					aq->Connection = fcon;
					if (code != "") {
						sql = "select * from BS_BookCatalog where ISBN like '%" + code + "%' or Barcode like '%" + code + "%'" ;
						aq->Close();
						aq->SQL->Clear();
						aq->SQL->Add(sql);
						aq->Open();
						if (aq->RecordCount > 0) {
							sql = "select max(id) as id from BS_BookCatalog " ;
							aq->Close();
							aq->SQL->Clear();
							aq->SQL->Add(sql);
							aq->Open();
							if (aq->FieldByName("id")->AsAnsiString == "" ) {
								userbarcode = "0";
							}
							else
							{
								userbarcode = IntToStr(aq->FieldByName("id")->AsInteger + 1) ;
							}
							userbarcode = constbarcode.SubString(0,13-userbarcode.Length()) + userbarcode;
						}
						else
						{
							userbarcode = editwenjutiaomao->Text.Trim();
						}
					}
					else
					{
						sql = "select max(id) as id from BS_BookCatalog " ;
						aq->Close();
						aq->SQL->Clear();
						aq->SQL->Add(sql);
						aq->Open();
						if (aq->FieldByName("id")->AsAnsiString == "" ) {
							userbarcode = "0";
						}
						else
						{
							userbarcode = IntToStr(aq->FieldByName("id")->AsInteger + 1) ;
						}
						userbarcode = constbarcode.SubString(0,13-userbarcode.Length()) + userbarcode;
					}
					delete aq;
				}
				else
				{
					userbarcode =  editwenjutiaomao->Text;
				}

				aqinsert->Insert();
				aqinsert->Append();
				aqinsert->FieldByName("isbn")->AsAnsiString =  editwenjutiaomao->Text ;
				aqinsert->FieldByName("name")->AsAnsiString = editwenjuname->Text ;
				aqinsert->FieldByName("userdefcode")->AsAnsiString =  editwenjuself->Text ;
                aqinsert->FieldByName("UserBarcode")->AsAnsiString =  userbarcode ;
				aqinsert->FieldByName("price")->AsFloat  =  StrToFloat(editwenjuprice->Text);
				aqinsert->FieldByName("barcode")->AsAnsiString = editwenjutiaomao->Text ;
				aqinsert->FieldByName("date")->AsDateTime  =  Now();
				aqinsert->FieldByName("Unavailable")->AsInteger  =  1;
				aqinsert->FieldByName("type")->AsInteger  =  2;
				aqinsert->FieldByName("Author")->AsAnsiString = edchangshang->Text;
				aqinsert->FieldByName("presscount")->AsAnsiString = edguige->Text;
				if (edtypename->Text != "") {
					aqinsert->FieldByName("smallBookTypeID")->AsInteger = TypeID;
				}

				aqinsert->UpdateBatch(arCurrent);
				editwenjutiaomao->Text ="";
				editwenjuname->Text = "";
				editwenjuself->Text = "";
				editwenjuprice->Text = "0.00";
				editwenjutiaomao->Text= "";
				editwenjutiaomao->SetFocus();
				edchangshang->Text = "";
				edtyquery->Text = "";
				edtypename->Text = "";
				edguige->Text = "";
				TypeID = -1;

                                ID =  aqinsert->FieldByName("ID")->AsInteger  ;
                                NewBooKCatalogID=ID;
				if (!rzcbinput->Checked) {

					if (modle == 1) {
						StorageMng->AddNote(-1,ID);
					}
					else if (modle == 3) {
						ProcureMng->AddNote(0,ID);
					}
					else if (modle == 4) {
						BIorder->AddNote(0,ID);
					}
					ModalResult = mbOK ;
				}else     //连续录入
				{
				       //	ID =  aqinsert->FieldByName("ID")->AsInteger  ;
					if (modle == 1) {
						StorageMng->AddNote(-1,ID);
					}
					else if (modle == 3) {
						ProcureMng->AddNote(0,ID);
					}
					else if (modle == 4) {
						BIorder->AddNote(0,ID);
					}
					return;
				}
			}catch(...)
			{}
		}
	}
	if (0==type) {
		if (editbookname->Text == "") {
			ShowMsg(Handle ,"书名不能为空！",3);
			return;
		}
		if ((editprice->Text == "")||(editprice->Text == "￥0.00")) {
			ShowMsg(Handle ,"定价不能为空！",3);
			return;
		}
		if (editprice->Text == "") {
			editprice->Text = "0.00";
		}
		if (meditwords->Text == "") {
            meditwords->Text = "0";
		}

		AnsiString sql;

		int pressid,bktypeid;
		if (rcbpress->Text!="") {
			try {
				pressid = (int)(rcbpress->Items->Objects[rcbpress->ItemIndex]);
			} catch (...) {
				ShowMsg(Handle ,"请选择正确的出版社！",3);
				return;
			}
		}
		AnsiString code = editcode->Text ,userbarcode;
		if (code == "") {
			code = editisbn->Text ;
		}
		if (code.Length() == 13 ) {
			code = code.SubString(4,9);
		}
		if (code.Length() == 10 ) {
			code = code.SubString(1,9);
		}
		if (ShowMsg(Handle ,"确定产生新书吗?",1)==1) {
            TADOQuery *aq = new TADOQuery(this);
			aq->Connection = fcon;
			if (code != "") {
				sql = "select * from BS_BookCatalog where ISBN like '%" + code + "%' or Barcode like '%" + code + "%'" ;
				aq->Connection = fcon;
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				aq->Open();
				if (aq->RecordCount > 0) {

					if (ShowMsg(Handle ,"该书目在书目库中已存在，是否继续增加此书目？",1)!=1) {
						delete aq;
                        Close();
						return;
					}
					if (userbar) {
                    	sql = "select max(id) as id from BS_BookCatalog " ;
						aq->Close();
						aq->SQL->Clear();
						aq->SQL->Add(sql);
						aq->Open();
						if (aq->FieldByName("id")->AsAnsiString == "" ) {
							userbarcode = "0";
						}
						else
						{
							userbarcode = IntToStr(aq->FieldByName("id")->AsInteger + 1) ;
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
					aq->Close();
					aq->SQL->Clear();
					aq->SQL->Add(sql);
					aq->Open();
					if (aq->FieldByName("id")->AsAnsiString == "" ) {
						userbarcode = "0";
					}
					else
					{
						userbarcode = IntToStr(aq->FieldByName("id")->AsInteger + 1) ;
					}
					userbarcode = constbarcode.SubString(0,13-userbarcode.Length()) + userbarcode;
				}
				else
				{
					userbarcode = "";
				}
			}

			/*sql = "select * from BS_BookCatalog where ISBN = '" + editisbn->Text + "' and Name = '" + editbookname->Text.Trim() + "' and Price = " + editprice->Text ;
			aq->Connection = fcon;
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->Open();
			if (aq->RecordCount > 0) {
				if (MessageBox(0,"是不是重复录入？","新录书目",MB_ICONQUESTION|MB_OKCANCEL )!=1) {
                	return;
				}
			}   */
			delete aq;
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
			} else
			{
				aquery->FieldByName("pid")->AsInteger = (int)(rcbpress->Items->Objects[rcbpress->ItemIndex]);
			}
			if (cbtype->Text == "") {
				aquery->FieldByName("smallbooktypeid")->AsInteger = -1;
			} else
			{
                         TypeID = GetIDFromText(1);
				aquery->FieldByName("smallbooktypeid")->AsInteger = TypeID;
			}
			aquery->FieldByName("Pressdate")->AsDateTime = datapressday->Date;
			aquery->FieldByName("PressCount")->AsString = edpresscount->Text ;
			aquery->FieldByName("ISBNType")->AsString = edISBNtype->Text ;
			aquery->FieldByName("Yizhe")->AsString = edyizhe->Text ;
			aquery->FieldByName("Printcount")->AsString = edprintcount->Text ;
			aquery->FieldByName("Affix")->AsString = edaffix->Text ;
			aquery->FieldByName("Bookformat")->AsString = cbformat->Text ;
			aquery->FieldByName("Bind")->AsString = cbbind->Text ;
			aquery->FieldByName("Collectbook")->AsString = edbook->Text ;
			aquery->FieldByName("huojiangstate")->AsString = edhuojiangstate->Text ;
			aquery->FieldByName("BookWords")->AsString = spepack->Text ;
                        if (meditwords->Text=="") {
                            meditwords->Text="0";
                        }
                         if (medityinzhang->Text=="") {
                            medityinzhang->Text="0";
                        }
			aquery->FieldByName("wordscount")->AsInteger  = StrToInt(meditwords->Text);
			aquery->FieldByName("yinzhang")->AsInteger  = StrToInt(medityinzhang->Text);
			aquery->UpdateBatch(arAll);

                        ID =  aquery->FieldByName("ID")->AsInteger ;
                        NewBooKCatalogID=ID;
			if (!rzcbinput->Checked) {


				if (modle == 1) {
					StorageMng->AddNote(-1,ID);
				}
				else if (modle == 3) {
					ProcureMng->AddNote(0,ID);
				}
				else if (modle == 4) {
					BIorder->AddNote(0,ID);
				}
				ModalResult = mbOK ;
			}else     //连续录入
			{
				editcode->Text  = "";
				editisbn->Text = "";
				editbookname->Text = "";
				editbookself->Text = "";
				editauthor->Text = "";
				rcbpress->ItemIndex = -1;
				editprice->Text = "0.00";
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
				medityinzhang->Text = "";
				edpyquery->Text = "";
				edtyname->Text = "";
				TypeID = -1;
				PageControlBook->ActivePage = tsbase;
				editcode->SetFocus();

				if (modle == 1) {
					StorageMng->AddNote(-1,ID);
				}
				else if (modle == 3) {
					ProcureMng->AddNote(0,ID);
				}
				else if (modle == 4) {
					BIorder->AddNote(0,ID);
				}
				edquery->Text = "";
				Press(0);
			}
		}
	}
        }catch(...)
        {}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmnewbook1::RzDBGrid1CellClick(TColumn *Column)
{
	if (aquery->IsEmpty()) {
		return;
	}
	editcode->Text = aquery->FieldByName("barcode")->AsAnsiString;
	editisbn->Text = aquery->FieldByName("ISBN")->AsAnsiString;
	editbookname->Text = aquery->FieldByName("name")->AsAnsiString;
	editbookself->Text = aquery->FieldByName("userdefcode")->AsAnsiString;
	editauthor->Text = aquery->FieldByName("author")->AsAnsiString;
	editprice->Text = FormatFloat("0.00",aquery->FieldByName("price")->AsFloat);
	rcbpress->ItemIndex = rcbpress->Items->IndexOfObject((TObject*)aquery->FieldByName("pid")->AsInteger );
	edtyname->Text = aquery->FieldByName("typename")->AsAnsiString ;
	TypeID = aquery->FieldByName("smallBookTypeID")->AsInteger ;
        cbtype->ItemIndex = cbtype->Items->IndexOfObject((TObject*)aquery->FieldByName("smallBookTypeID")->AsInteger);

	datapressday->Date = aquery->FieldByName("Pressdate")->AsDateTime ;
	edpresscount->Text = aquery->FieldByName("PressCount")->AsString ;
	edISBNtype->Text = aquery->FieldByName("ISBNType")->AsString ;
	edyizhe->Text = aquery->FieldByName("Yizhe")->AsString ;
	edprintcount->Text = aquery->FieldByName("Printcount")->AsString ;
	edaffix->Text = aquery->FieldByName("Affix")->AsString ;
	cbformat->Text = aquery->FieldByName("Bookformat")->AsString ;
	cbbind->Text = aquery->FieldByName("Bind")->AsString ;
	edbook->Text = aquery->FieldByName("Collectbook")->AsString ;
	edhuojiangstate->Text = aquery->FieldByName("huojiangstate")->AsString ;
	spepack->Text = aquery->FieldByName("BookWords")->AsString ;
	medityinzhang->Text = aquery->FieldByName("yinzhang")->AsAnsiString ;
	meditwords->Text = aquery->FieldByName("wordscount")->AsAnsiString;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::datapressdayKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
		edpresscount->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::sedpresscountKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
	   BtnSave->Click();
		editcode->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::edISBNtypeKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
    	edyizhe->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::edyizheKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        edprintcount->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::edprintcountKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        edaffix->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::edaffixKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        cbformat->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::cbformatKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        cbbind->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::cbbindKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        edbook->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::edbookKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
		edhuojiangstate->SetFocus();
	}
}
//---------------------------------------------------------------------------


void __fastcall Tfrmnewbook1::edbkKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
        BtnSave->Click();
	}
}
int Tfrmnewbook1::BrocodeToPress(String brocode)
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
	TADOQuery * query = new TADOQuery(NULL);
	query->Connection = fcon;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	int pressid;
	if (query->IsEmpty() ) {
		pressid = -1;
	}
	else
	{
    	pressid = query->FieldByName("ID")->AsInteger ;
	}
	return pressid;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::cbsaletypeChange(TObject *Sender)
{
	if (cbsaletype->Text == "图书") {
		PageControlBook->Visible = true;
		pcqikan->Visible = false;
		pcwenju->Visible = false;
		dg->Visible = false;
		RzDBGrid1->Visible = true;
		type = 0;
		Press(0);
		TypeID = -1;
	}
	if (cbsaletype->Text == "期刊") {
		pcqikan->Visible = true;
		pcwenju->Visible = false;
		PageControlBook->Visible = false;
		type = 1;
		ShowInput(1);
		TypeID = -1;
	}
	if (cbsaletype->Text == "文具") {
		pcwenju->Visible = true;
		PageControlBook->Visible = false;
		pcqikan->Visible = false;
		type = 2;
		ShowInput(2);
		TypeID = -1;
	}
}
//---------------------------------------------------------------------------
void Tfrmnewbook1::ShowInput(int type)
{
	AnsiString sql;
	TColumn *Column;

	switch (type) {
		case 0:
			dg->Visible = false;
			RzDBGrid1->Visible = true;
		break;
		case 1:                   //期刊
			dg->Columns->Clear();
			dg->Visible = true;
			RzDBGrid1->Visible = false;
			aqinsert->Active = false;
			sql = "select rank() over (order by A.ID) as xuhao,A.ID,A.barcode,A.userdefcode,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.Unavailable,A.date,A.Type,  "
				" A.Bookformat,A.Bk,A.year,A.yearprice,A.duokan,A.duokantext,A.duokannum,A.youfa,A.youfacode,A.pressarea,A.kanhao,A.tongyikanhao,A.PressCount,A.daixiao, "
				" B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B  "
				" on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID "
				" where  A.type = 1 and unavailable =1 and 1 = 2" ;
					//sql = "select ID,isbn,name,userdefcode,price,barcode,date,Unavailable,type,presscount,bk from bs_bookcatalog where type = 1  and unavailable =1 and 1=2" ;
			aqinsert->Connection = fcon ;
			aqinsert->Close();
			aqinsert->SQL->Clear();
			aqinsert->SQL->Add(sql);
			aqinsert->Active = true;

			Column = dg->Columns->Add();
			Column->FieldName = "isbn";
			Column->Title->Caption = "ISSN";
			Column->Width =60;

			Column = dg->Columns->Add();
			Column->FieldName = "name";
			Column->Title->Caption = "刊名";
			Column->Width = 200;

			Column = dg->Columns->Add();
			Column->FieldName = "price";
			Column->Title->Caption = "定价";
			Column->Width = 60;
			Column = dg->Columns->Add();

			Column->FieldName = "presscount";
			Column->Title->Caption = "期号";
			Column->Width = 40;
			Column = dg->Columns->Add();

			Column->FieldName = "duokantext";
			Column->Title->Caption = "多刊号";
			Column->Width = 40;
		break;
		case 2:                    //文具
		dg->Columns->Clear();
		dg->Visible = true;
		RzDBGrid1->Visible = false;
		aqinsert->Connection = fcon ;

		sql = "select bs_bookcatalog.ID,isbn,bs_bookcatalog.name,userdefcode,UserBarcode,Author,price,barcode,date,Unavailable,type,presscount,smallBookTypeID,BS_BookType.name as typename from bs_bookcatalog left join BS_BookType on bs_bookcatalog.smallBookTypeID = BS_BookType.id where bs_bookcatalog.type = 2  and unavailable =1 and 1=2" ;
		aqinsert->Connection = fcon ;
		aqinsert->Close();
		aqinsert->SQL->Clear();
		aqinsert->SQL->Add(sql);
		aqinsert->Active = true;

		Column = dg->Columns->Add();
		Column->FieldName = "barcode";
		Column->Title->Caption = "条码";
		Column->Width = 90;

		Column = dg->Columns->Add();
		Column->FieldName = "name";
		Column->Title->Caption = "品名";
		Column->Width =150;

		Column = dg->Columns->Add();
		Column->FieldName = "userdefcode";
		Column->Title->Caption = "自编码";
		Column->Width =90;

		Column = dg->Columns->Add();
		Column->FieldName = "price";
		Column->Title->Caption = "定价";
		Column->Width =60;

		Column = dg->Columns->Add();
		Column->FieldName = "UserBarcode";
		Column->Title->Caption = "条码(附加)";
		Column->Width =100;

		Column = dg->Columns->Add();
		Column->FieldName = "typename";
		Column->Title->Caption = "类别";
		Column->Width =60;

		Column = dg->Columns->Add();
		Column->FieldName = "Author";
		Column->Title->Caption = "厂商";
		Column->Width =100;

		Column = dg->Columns->Add();
		Column->FieldName = "presscount";
		Column->Title->Caption = "规格";
		Column->Width =100;
		break;
		default:
			 ;
	}
}

//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::editwenjupriceKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '\b')) {
		Key = NULL;
	}
	if (Key == '\r') {
        edchangshang->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::editqikanmaoKeyPress(TObject *Sender, wchar_t &Key)
{

	if (Key == VK_RETURN) {
		if (editqikanmao->Text != "") {
			if (editqikanmao->Text.Length() >= 13 ) {
				editqikanqihao->Text = editqikanmao->Text.SubString(14,editqikanmao->Text.Length()-13);
				editqikanmao->Text = editqikanmao->Text.SubString(0,13);

				AnsiString sql;
				sql = "select rank() over (order by A.ID) as xuhao,A.ID,A.barcode,A.userdefcode,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.Unavailable,A.date,A.Type,"
						"A.Bookformat,A.Bk,A.year,A.yearprice,A.duokan,A.duokantext,A.duokannum,A.youfa,A.youfacode,A.pressarea,A.kanhao,A.tongyikanhao,A.PressCount,"
						"B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "                                                                                                      //期刊类型选择
						" on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID where A.type = 1 and (barcode like '%" + editqikanmao->Text + "%' or ISBN like '%" + editqikanmao->Text + "%')";// and A.PressCount like '%" + editqikanqihao->Text + "%'";
				aqinsert->Connection = fcon ;
				aqinsert->Close();
				aqinsert->SQL->Clear();
				aqinsert->SQL->Add(sql);
				aqinsert->Open();
				editqikanissn->Text = BarCodeToISSN(editqikanmao->Text.Trim());
				editqikanname->SetFocus();
				return;
			}
			else if (editqikanmao->Text.Length() != 13) {

                                ShowMsg(Handle ,"请输入正确的条码！",3);
				return;
			}
			editqikanissn->Text = BarCodeToISSN(editqikanmao->Text.Trim());
		}
		editqikanqihao->SetFocus();
	}
}
//---------------------------------------------------------------------------
AnsiString Tfrmnewbook1::GetSelf(AnsiString context)
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
                        if (k<=58&&k>=48) {    //数字
                          t4=t4+t3;
                        }
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
AnsiString Tfrmnewbook1::BarCodeToISSN(AnsiString BarCode)
{
AnsiString ISSN;
if (BarCode=="") {
    return "";
}
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
AnsiString Tfrmnewbook1::ISSNToBarCode(AnsiString ISSN)
{
  //ISSN与EAN的对应关系为：977 + ISSN前7码 + 00 + EAN检查码
         if (ISSN == "") {
             return "";
         }
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
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::editqikanissnKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
		if (editqikanissn->Text.Length() < 8  )
		{

                        ShowMsg(Handle ,"请输入正确的ISSN编号！",3);
			return;
		}
		if (editqikanissn->Text != "" && editqikanmao->Text == "") {
			editqikanmao->Text = ISSNToBarCode(editqikanissn->Text.Trim() )  ;
		}
		Perform(WM_NEXTDLGCTL, 0, 0);
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::editqikannameKeyPress(TObject *Sender, wchar_t &Key)

{        AnsiString selft,s1,qikanname;
  AnsiString nian,qihao;
	if (Key == VK_RETURN) {
		if (editqikanname->Text == "") {

                        ShowMsg(Handle ,"请输入期刊名！",3);
			return;
		}
		editqikanself->Text = GetSelfQiKan(editqikanname->Text.Trim() );


               selft = editqikanself->Text.Trim();
                s1 = RightStr(selft,4);
                qihao = RightStr(s1,2);  //取出期号
                nian = LeftStr(s1,2);

               // if(nian!="") sedyear->Value = StrToInt("20"+nian);
			   if (qihao!="") {
					 //	editqikanqihao->Text=qihao;
			    }
		sedyear->SetFocus();
                qikanname=editqikanname->Text;

               AnsiString sql1 = "select rank() over (order by A.ID) as xuhao,A.ID,A.barcode,A.userdefcode,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.Unavailable,A.date,A.Type,  "
                " A.Bookformat,A.Bk,A.year,A.yearprice,A.duokan,A.duokantext,A.duokannum,A.youfa,A.youfacode,A.pressarea,A.kanhao,A.tongyikanhao,A.PressCount,A.daixiao, "
                " B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B  "
                " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID "
                " where  A.type = 1 and unavailable =1 and A.name = '"+qikanname+"'"; ;


               // AnsiString sql1 = "select a.pressid as pid,a.smallbooktypeid,a.id,a.barcode,a.isbn,a.name,a.price,a.UserDefCode,a.presscount,a.author,b.AbbreviatedName from dbo.BS_BookCatalog a left join dbo.BS_PressInfo b  ";
               // sql1=sql1+" on a.pressid = b.id where Unavailable=1 and A.name like '"+Strutils::LeftStr(qikanname,qikanname.Length()-2)+"%'";
                aqinsert->Connection = fcon ;
                aqinsert->Close();
                aqinsert->SQL->Clear();
                aqinsert->SQL->Add(sql1);
                aqinsert->Active = true;


                AnsiString sql2;
                sql2 = "select id from BS_BookCatalog where name='" +editqikanname->Text.Trim()+"'" ;
                TADOQuery *aq1 = new TADOQuery(Application);
                aq1->Connection = fcon;
                aq1->Close();
                aq1->SQL->Clear();
                aq1->SQL->Add(sql2);
                aq1->Open();
                if (aq1->RecordCount > 0) {

                    ShowMsg(Handle ,"该书目在书目库中已存在!",3);

                }

	}
}
AnsiString Tfrmnewbook1::GetSelfQiKan(AnsiString context)
{
        char* t;
	AnsiString t2;
	String t1,t3,t4;
	t1 = context;//.TrimLeft().TrimLeft()  ;//.TrimRight();//  .TrimLeft()  ;
	int t5=1,i = context.Length()  ;
	for( int j=1;j<=i;j++)
	{
	t3 = t1.SubString(j,1);
	t = t3.t_str();
	Word k = int (t[0])<<8;
	k = k >> 8;



        if (k<=58&&k>=48) {    //数字
                  t4=t4+t3;
          }else if (t3 >= 'a' && t3 <= 'z' || t3 >= 'A' && t3 <= 'Z') {    //字母

                if (t5 == 5) continue;  //只取前４个汉字
                t4=t4+t3.UpperCase();
                t5++;

          }else if (k>=160){       //汉字
                 if (t5 == 5) continue;  //只取前４个汉字
                t = t3.t_str();
                t2 = GetPYIndexChar(t);
                t4 = t4 + t2;
                t5++;//取到了一个汉字
           }

          }

	return t4;

}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::editqikanpriceKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '\b')) {
		Key = NULL;
	}
	if (Key == VK_RETURN) {
	if (editqikanprice->Text=="0.00") {

                ShowMsg(Handle ,"请输入定价！",3);
		return;
	}
	edpress->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::editqikanfaxingKeyPress(TObject *Sender, wchar_t &Key)

{
 if (Key == VK_RETURN) {
	Perform(WM_NEXTDLGCTL, 0, 0);
 }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::editwenjutiaomaoKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
		AnsiString sql;
		sql = "select ID,isbn,name,userdefcode,UserBarcode,Author,price,barcode,date,Unavailable,type,presscount,bk,smallBookTypeID from bs_bookcatalog where type = 2  and unavailable =1 " ;
		sql = sql + " and barcode = '" + editwenjutiaomao->Text + "'";
		aqinsert->Connection = fcon ;
		aqinsert->Close();
		aqinsert->SQL->Clear();
		aqinsert->SQL->Add(sql);
		aqinsert->Open();
		Perform(WM_NEXTDLGCTL, 0, 0);
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::editwenjunameKeyPress(TObject *Sender, wchar_t &Key)

{
  if (Key == VK_RETURN) {

   if (editwenjuname->Text == "") {

                  ShowMsg(Handle ,"请输入品名！",3);
	   return;
  }
	editwenjuself->Text = GetSelf(editwenjuname->Text.Trim());
	Perform(WM_NEXTDLGCTL, 0, 0);
 }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::dgCellClick(TColumn *Column)
{
	if ( aqinsert->IsEmpty() ) {
		return;
	}
	if (1 == type ) {
		editqikanissn->Text  = aqinsert->FieldByName("isbn")->AsAnsiString   ;
		editqikanname->Text  =	aqinsert->FieldByName("name")->AsAnsiString  ;
		editqikanself->Text =	aqinsert->FieldByName("userdefcode")->AsAnsiString ;
		editqikanprice->Text =	aqinsert->FieldByName("price")->AsAnsiString  ;
		editqikanmao->Text =	aqinsert->FieldByName("barcode")->AsAnsiString  ;
	       //	editqikanqihao->Text=  aqinsert->FieldByName("presscount")->AsAnsiString ;
		sedyear->Text = aqinsert->FieldByName("year")->AsAnsiString ;
		cbpress->ItemIndex = cbpress->Items->IndexOfObject((TObject*)aqinsert->FieldByName("pid")->AsInteger);
		cbkanqi->Text = aqinsert->FieldByName("Bookformat")->AsAnsiString ;
		chduokan->Checked = aqinsert->FieldByName("duokan")->AsBoolean ;
		if (aqinsert->FieldByName("duokan")->AsBoolean) {
			cbduokan->Text = aqinsert->FieldByName("duokantext")->AsAnsiString ;
			sedkannum->Text = aqinsert->FieldByName("duokannum")->AsAnsiString ;
			cbduokan->Visible = true;
			sedkannum->Visible = true;
			Label31->Visible = true;
		}
		else
		{
			cbduokan->Visible = false;
			sedkannum->Visible = false;
			Label31->Visible = false;
		}
		edyearprice->Text = aqinsert->FieldByName("yearprice")->AsAnsiString ;
		edkanhao->Text = aqinsert->FieldByName("kanhao")->AsAnsiString ;
		edtykanhao->Text = aqinsert->FieldByName("tongyikanhao")->AsAnsiString ;
	       //	edpequery->Text = aqinsert->FieldByName("typename")->AsAnsiString ;

		TypeID = aqinsert->FieldByName("smallBookTypeID")->AsInteger ;
                 qcbtype->ItemIndex = qcbtype->Items->IndexOfObject((TObject*)aqinsert->FieldByName("smallBookTypeID")->AsInteger);
	}
	if (2 == type ) {
		editwenjutiaomao->Text = aqinsert->FieldByName("isbn")->AsAnsiString   ;
		editwenjuname->Text = aqinsert->FieldByName("name")->AsAnsiString  ;
		editwenjuself->Text = aqinsert->FieldByName("userdefcode")->AsAnsiString ;
		editwenjuprice->Text = aqinsert->FieldByName("price")->AsAnsiString ;
		editwenjutiaomao->Text = aqinsert->FieldByName("barcode")->AsAnsiString  ;
		edchangshang->Text = aqinsert->FieldByName("author")->AsAnsiString ;
	       //	edtypename->Text = aqinsert->FieldByName("typename")->AsAnsiString ;
		edguige->Text = aqinsert->FieldByName("presscount")->AsAnsiString ;
		TypeID = aqinsert->FieldByName("smallBookTypeID")->AsInteger ;
             //   cbtype->ItemIndex = cbtype->Items->IndexOfObject((TObject*)aqinsert->FieldByName("smallBookTypeID")->AsInteger);
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F4) {
		BtnSave->Click();
	}
	if (Shift.Contains(ssCtrl)&& Key ==81  ) {
		BtnExit->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::edqueryKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		if (edquery->Text != "") {
			Press(1);
		}else
                {
                    if(rcbpress->Text =="")  //如果版别从书号中获取了，就不需要再查询了
                    {
                      Press(2);
                    }else rcbpress->ItemIndex=-1;

                }
		rcbpress->SetFocus();
	}
}
//---------------------------------------------------------------------------

void Tfrmnewbook1::Press(int mode)
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
                if (mode==0) {
                  rcbpress->ItemIndex = -1;
                }
                if (aq->RecordCount>0) {
                   if (edquery->Text!="") {
                     rcbpress->ItemIndex = 0;
                   } else  rcbpress->ItemIndex = -1;

                }else rcbpress->ItemIndex = -1;

		delete aq;

}
//---------------------------------------------------------------------------
void __fastcall Tfrmnewbook1::editisbnKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		AnsiString bro;
		try {
			bro = ISBNToBarcode(editisbn->Text);
		} catch (...) {
		}
		editcode->Text =  bro;
        editbookname->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::editbookselfKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        editprice->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::chduokanClick(TObject *Sender)
{
	if (chduokan->Checked ) {
		cbduokan->Visible = true;
		Label31->Visible = true;
		sedkannum->Visible = true;
	}
	else
	{
		cbduokan->Visible = false;
		Label31->Visible = false;
		sedkannum->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::edpressKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		if (edpress->Text != "") {
			Press1(1);
		}else
                {
                   Press1(2);
                   cbpress->ItemIndex=-1;
                }
		cbpress->SetFocus();
	}
}
//---------------------------------------------------------------------------
 void Tfrmnewbook1::presstype(int mode,int selecttype)
 {
                TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		AnsiString sql;

                if (mode==10) {     //图书
                        if (selecttype == 1) {
                            sql = "select id,code,name from BS_BookType where code+name like '%" + edpyquery->Text.Trim() + "%'" ;
                        }
                        else
                        {
                            sql = "select id,code,name from BS_BookType ";
                        }

                        aq->Close();
                        aq->SQL->Clear();
                        aq->SQL->Add(sql);
                        aq->Open();
                        cbtype->Clear();
                        while(!aq->Eof)
                        {
                            cbtype->AddItem("["+aq->FieldByName("code")->AsAnsiString+"]"+aq->FieldByName("name")->AsAnsiString, (TObject*)aq->FieldByName("ID")->AsInteger );
                            aq->Next();
                        }

                        if (aq->RecordCount>0) {
                         aq->First();
                         cbtype->ItemIndex = 0;
                        }

                }else if (mode==12) { //期刊
                  if (selecttype == 1) {
                            sql = "select id,code,name from BS_BookType where code+name like '%" + edpequery->Text.Trim() + "%'" ;
                        }
                        else
                        {
                            sql = "select id,code,name from BS_BookType ";
                        }

                        aq->Close();
                        aq->SQL->Clear();
                        aq->SQL->Add(sql);
                        aq->Open();
                        qcbtype->Clear();
                        while(!aq->Eof)
                        {
                            qcbtype->AddItem("["+aq->FieldByName("code")->AsAnsiString+"]"+aq->FieldByName("name")->AsAnsiString, (TObject*)aq->FieldByName("ID")->AsInteger );
                           aq->Next();
                        }
                        if (aq->RecordCount > 0) {
                           aq->First();
                           qcbtype->ItemIndex = 0;
                        }

                }


		delete aq;


 }
void Tfrmnewbook1::Press1(int mode)
{

		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcon;
		AnsiString sql;
		if (mode == 1) {
			sql = "select ID,presentnum,abbreviatedname from BS_PressInfo where abbreviatedname like '%" + edpress->Text.Trim() + "%'" ;
		}
		else
		{
			sql = "select ID,presentnum,abbreviatedname from BS_PressInfo ";
		}
		cbpress->Clear();
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		while(!aq->Eof)
		{
			cbpress->AddItem(aq->FieldByName("abbreviatedname")->AsAnsiString, (TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		aq->First();
		if (mode == 1) {
			cbpress->ItemIndex = 0;
		}

		delete aq;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::sedyearKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		editqikanprice->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::cbpressKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
               if (edpress->Text !="") {
                if (cbpress->Items->Count >0) {
                   cbpress->ItemIndex = 0;
                }
               }
               
		edpequery->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::editqikanqihaoKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
		if (editqikanqihao->Text == "") {
			ShowMsg(Handle ,"请录入期号！",3);
			editqikanqihao->SetFocus();
			return;
		}
		editqikanname->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::cbkanqiKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        chduokan->SetFocus();
	       //	BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::edkanhaoKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        //edtykanhao->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::edtykanhaoKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
       // edyearprice->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::edyearpriceKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {

	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::editqikanpriceExit(TObject *Sender)
{
	float price;
	try {
		price = StrToFloat(editqikanprice->Text);
	} catch (...) {
                ShowMsg(Handle ,"请输入正确的定价！",3);
                editqikanprice->SetFocus();
		return;
	}
	editqikanprice->Text = FormatFloat("0.00",price);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::cbkanqiExit(TObject *Sender)
{
	int totalkanqi;
	float price = 0.0;
	int qikanshu;
	try {
		price = StrToFloat(editqikanprice->Text);
	} catch (...) {
    	return;
	}
	if (cbkanqi->Text != "") {
		if (cbkanqi->Text == "周刊") {
			totalkanqi = 52;
		}
		else if (cbkanqi->Text == "半月刊") {
			totalkanqi = 24;
		}
		else if (cbkanqi->Text == "月刊") {
			totalkanqi = 12;
		}
		else if (cbkanqi->Text == "双月刊") {
			totalkanqi = 6;
		}
		else if (cbkanqi->Text == "季刊") {
			totalkanqi = 4;
		}
		else if (cbkanqi->Text == "半年刊") {
			totalkanqi = 2;
		}
		else if (cbkanqi->Text == "年刊") {
			totalkanqi = 1;
		}
		edyearprice->Text = FloatToStr(price*totalkanqi);
	}
	try {
                if (editqikanqihao->Text=="") {
                   qikanshu=0;
                }else
                {
		qikanshu = StrToInt(editqikanqihao->Text);
                }
	} catch (...) {
	}
	if (totalkanqi < qikanshu) {
		editqikanqihao->SetFocus();

                ShowMsg(Handle ,"录入期数过大，请重新录入！",3);
		return;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::chduokanKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		if (cbduokan->Visible ) {
			cbduokan->SetFocus();
		}
		else
		{
			editbk->SetFocus();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::cbduokanKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        sedkannum->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::sedkannumExit(TObject *Sender)
{
	int totalkanqi;
	float price = 0.0;
	try {
		price = StrToFloat(editqikanprice->Text);
	} catch (...) {
		return;
	}
	if (cbkanqi->Text != "") {
		if (cbkanqi->Text == "周刊") {
			totalkanqi = 52;
		}
		else if (cbkanqi->Text == "半月刊") {
			totalkanqi = 24;
		}
		else if (cbkanqi->Text == "月刊") {
			totalkanqi = 12;
		}
		else if (cbkanqi->Text == "双月刊") {
			totalkanqi = 6;
		}
		else if (cbkanqi->Text == "季刊") {
			totalkanqi = 4;
		}
		else if (cbkanqi->Text == "半年刊") {
			totalkanqi = 2;
		}
		else if (cbkanqi->Text == "年刊") {
			totalkanqi = 1;
		}
		edyearprice->Text = FloatToStr(price*totalkanqi*sedkannum->Value);
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::sedkannumKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
       // edkanhao->SetFocus();
       editbk->SetFocus();
	}
}
//---------------------------------------------------------------------------


void __fastcall Tfrmnewbook1::edpresscountKeyPress(TObject *Sender, wchar_t &Key)

{
    if (Key == '\r') {
             BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::spepackKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == '\r') {
		edpyquery->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::edhuojiangstateKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == '\r') {
		meditwords->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::meditwordsKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		medityinzhang->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::medityinzhangKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::btaddtypeClick(TObject *Sender)
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
		edpequery->Text = "[" + aq->FieldByName("Code")->AsAnsiString + "]" + aq->FieldByName("Name")->AsAnsiString ;
		edtyname->Text = "[" + aq->FieldByName("Code")->AsAnsiString + "]" + aq->FieldByName("Name")->AsAnsiString ;
		edtypename->Text = "[" + aq->FieldByName("Code")->AsAnsiString + "]" + aq->FieldByName("Name")->AsAnsiString ;
	}
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::spselectTypeClick(TObject *Sender)
{
	Tfrmselecttype * frm = new Tfrmselecttype(Application,fcon,"");
	if (mrOk == frm->ShowModal())
	{
		TypeID = frm->GetSelectID();
		edtypename->Text = frm->GetSelect();
		edtyname->Text = frm->GetSelect();
		edpequery->Text = frm->GetSelect();
	}
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::edtyqueryKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		Tfrmselecttype * frm = new Tfrmselecttype(Application,fcon,edtyquery->Text);
		if (mrOk == frm->ShowModal())
		{
			TypeID = frm->GetSelectID();
			edtypename->Text = frm->GetSelect();
		}
		delete frm;
		edguige->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::edguigeKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
		BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::edchangshangKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        edtyquery->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::edpyqueryKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {

		if (edpyquery->Text != "") {
			presstype(10,1);
		}else
                {
                   presstype(10,2);
                   cbtype->ItemIndex=-1;
                }

		cbtype->SetFocus();
	}
        /*
		Tfrmselecttype * frm = new Tfrmselecttype(Application,fcon,edpyquery->Text);
		if (mrOk == frm->ShowModal())
		{
			TypeID = frm->GetSelectID();
			edtyname->Text = frm->GetSelect();
		}
		delete frm;
	   	edquery->SetFocus();   */

}
//---------------------------------------------------------------------------
int Tfrmnewbook1::GetIDFromText(int type)
{

   if (type==1) { //图书
          return (int)(cbtype->Items->Objects[cbtype->ItemIndex]);
   }else     //期刊
   {
        return (int)(qcbtype->Items->Objects[qcbtype->ItemIndex]);

   }
}
void __fastcall Tfrmnewbook1::edpequeryKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {

		if (edpequery->Text != "") {
			presstype(12,1);
		}else
                {
                   presstype(12,2);
                   qcbtype->ItemIndex=-1;
                }
	    	qcbtype->SetFocus();
	}
/*	if (Key == '\r') {
		Tfrmselecttype * frm = new Tfrmselecttype(Application,fcon,edpequery->Text);
		if (mrOk == frm->ShowModal())
		{
			TypeID = frm->GetSelectID();
			edpename->Text = frm->GetSelect();
		}
		delete frm;
		cbkanqi->SetFocus();
	}  */
}

//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::qcbtypeKeyPress(TObject *Sender, wchar_t &Key)
{
      //  ShowMessage("fff");
	if (Key == VK_RETURN) {
                if (edpequery->Text !="") {
                 if (qcbtype->Items->Count>0 ) {
                    qcbtype->ItemIndex = 0;
                   }
                }

         	cbkanqi->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::cbtypeKeyPress(TObject *Sender, wchar_t &Key)
{
     	if (Key == VK_RETURN) {
           if (edpyquery->Text !="") {
                   if (cbtype->Items->Count >0) {
                    cbtype->ItemIndex =0;
                   }
           }
		edquery->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::editbkKeyPress(TObject *Sender, wchar_t &Key)
{
    	if (Key == VK_RETURN) {

	//	cbshengdaia->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmnewbook1::cbshengdaiaKeyPress(TObject *Sender, wchar_t &Key)
{
     	if (Key == '\r') {

        //   ShowMessage("ff");

         BtnSave->Click();
        }
}
//---------------------------------------------------------------------------


void __fastcall Tfrmnewbook1::ComboBox1KeyPress(TObject *Sender, wchar_t &Key)
{    	if (Key == '\r') {

           ShowMessage("ff");
       // BtnSave->Click();
        //edkanhao->SetFocus();
        }

}
//---------------------------------------------------------------------------


void __fastcall Tfrmnewbook1::FormShow(TObject *Sender)
{
   if (cbsaletype->ItemIndex==1) {
	   editqikanmao->SetFocus();
   }
   if (cbsaletype->ItemIndex==2) {
   editwenjutiaomao->SetFocus();
   }
}
//---------------------------------------------------------------------------

