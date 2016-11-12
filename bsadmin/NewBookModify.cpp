//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "NewBookModify.h"
#include "pdutil.h"
#include "Addsyslog.h"
#include "Selecttype.h"
#include "global.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma link "RzCmboBx"
#pragma link "RzDBCmbo"
#pragma link "RzEdit"
#pragma link "RzSpnEdt"
#pragma resource "*.dfm"
TfrmNewBookModify *frmNewBookModify;
//---------------------------------------------------------------------------
__fastcall TfrmNewBookModify::TfrmNewBookModify(TComponent* Owner,TADOConnection *con,int bkcatalogid,int stgid,int userid)
	: TForm(Owner)
{
	catalogid = bkcatalogid;
	fuserid = userid;
	fcon = con;
	comAddcatalog->Connection = fcon;
	aquery->Connection = con;
	fstgid = stgid;
	ybkcatalogid =  bkcatalogid;
	ReadyData();
	AnsiString sql ;

	sql = "select BS_BookCatalog.*,BS_BookType.name as typename from BS_BookCatalog left join BS_BookType on BS_BookCatalog.smallBookTypeID = BS_BookType.id where BS_BookCatalog.id = " + IntToStr(bkcatalogid);
	aquery->Close();
	aquery->SQL->Clear();
	aquery->SQL->Add(sql);
	aquery->Open();
	ybookname = aquery->FieldByName("name")->AsAnsiString.Trim();
	if (aquery->FieldByName("type")->AsInteger == 1 ) {
		pgqikan->Visible = true;
		PageControlBook->Visible = false;
		editqikanissn->Text  = aquery->FieldByName("isbn")->AsAnsiString.Trim() ;
		editqikanname->Text  =	aquery->FieldByName("name")->AsAnsiString.Trim() ;
		editqikanself->Text =	aquery->FieldByName("userdefcode")->AsAnsiString.Trim() ;
		editqikanprice->Text =	aquery->FieldByName("price")->AsAnsiString.Trim() ;
		editqikanmao->Text =	aquery->FieldByName("barcode")->AsAnsiString.Trim() ;
		editqikanqihao->Text=  aquery->FieldByName("presscount")->AsAnsiString.Trim() ;
		sedyear->Text = aquery->FieldByName("year")->AsAnsiString.Trim();
		TypeID = aquery->FieldByName("smallBookTypeID")->AsInteger ;
		edtypename->Text = aquery->FieldByName("typename")->AsAnsiString ;
		if (aquery->FieldByName("PressID")->AsString == "") {
			rcbpress->ItemIndex = -1;
		}
		else
		{
			cbpress->ItemIndex = cbpress->Items->IndexOfObject((TObject*)aquery->FieldByName("PressID")->AsInteger);
		}
		cbkanqi->Text = aquery->FieldByName("Bookformat")->AsAnsiString.Trim()  ;
		chduokan->Checked = aquery->FieldByName("duokan")->AsBoolean ;
		if (aquery->FieldByName("duokan")->AsBoolean) {
			cbduokan->Text = aquery->FieldByName("duokantext")->AsAnsiString.Trim()  ;
			sedkannum->Text = aquery->FieldByName("duokannum")->AsAnsiString.Trim()  ;
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
		edyearprice->Text = aquery->FieldByName("yearprice")->AsAnsiString.Trim()  ;
		edkanhao->Text = aquery->FieldByName("kanhao")->AsAnsiString.Trim()  ;
		edtykanhao->Text = aquery->FieldByName("tongyikanhao")->AsAnsiString.Trim()  ;
	}
	else
	{
		editcode->Text = aquery->FieldByName("Barcode")->AsString.Trim()  ;
		editisbn->Text = aquery->FieldByName("ISBN")->AsString.Trim()  ;
		editbookname->Text = aquery->FieldByName("Name")->AsString.Trim()  ;
		editbookself->Text = aquery->FieldByName("UserDefCode")->AsString.Trim();
		editprice->Text = FormatFloat("0.00",aquery->FieldByName("Price")->AsFloat);
		editauthor->Text = aquery->FieldByName("Author")->AsString.Trim();
		TypeID = aquery->FieldByName("smallBookTypeID")->AsInteger ;
                edtyname->Text = aquery->FieldByName("typename")->AsAnsiString ;
		if (aquery->FieldByName("PressID")->AsString == "") {
			rcbpress->ItemIndex = -1;
		}
		else
		{
			rcbpress->ItemIndex = rcbpress->Items->IndexOfObject((TObject*)aquery->FieldByName("PressID")->AsInteger );
		}

		datapressday->Date =  aquery->FieldByName("Pressdate")->AsDateTime ;
		edpresscount->Text = aquery->FieldByName("PressCount")->AsString.Trim() ;
		edISBNtype->Text = aquery->FieldByName("ISBNType")->AsString.Trim()  ;
		edyizhe->Text = aquery->FieldByName("Yizhe")->AsString.Trim()  ;
		edprintcount->Value = aquery->FieldByName("Printcount")->AsInteger ;
		edaffix->Text = aquery->FieldByName("Affix")->AsString.Trim()  ;
		cbformat->Text = aquery->FieldByName("Bookformat")->AsString.Trim()  ;
		cbbind->Text = aquery->FieldByName("Bind")->AsString.Trim()  ;
		edbook->Text = aquery->FieldByName("Collectbook")->AsString.Trim()  ;

		medityinzhang->Text = aquery->FieldByName("yinzhang")->AsAnsiString ;
		meditwords->Text = aquery->FieldByName("wordscount")->AsAnsiString;

                editbk->Text = aquery->FieldByName("bk")->AsAnsiString;
                cbshengdai->Text = aquery->FieldByName("daixiao")->AsAnsiString;
		edhuojiangstate->Text = aquery->FieldByName("huojiangstate")->AsAnsiString.Trim()  ;
		spepack->Text = aquery->FieldByName("BookWords")->AsAnsiString.Trim()  ;

	}
}
//---------------------------------------------------------------------------
void TfrmNewBookModify::ReadyData()
{
	String sql ;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	sql = "select ID,PresentNum,abbreviatedname from BS_PressInfo ";
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

   	sql = "declare @modify int ;"
			" exec modifprice " + IntToStr(ybkcatalogid) + ",-1," + IntToStr(fstgid) + ",@modify output ; "
			" select @modify as modify" ;
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	if (aq->FieldByName("modify")->AsInteger == 1 ) {
	     //	editqikanprice->Enabled = false;
	     //	editprice->Enabled = false;
	}
	delete aq;
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewBookModify::BtnSaveClick(TObject *Sender)
{
try
{
	AnsiString sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	int pressid = -1,booktypeid = -1;
	if (pgqikan->Visible ) {
		if (cbpress->Text != "") {
			try {
				pressid = (int)cbpress->Items->Objects[cbpress->ItemIndex];
			} catch (...) {
				ShowMsg(Handle ,"请选择正确的出版社！",3);
				return;
			}
		}else pressid = -1;
		if (edtypename->Text == "") {


			booktypeid = -1;
		}
		else
		{
        	booktypeid = TypeID;
		}
		if (edyearprice->Text == "") {
			edyearprice->Text = "0";
		}
		if (editqikanname->Text == "" )
		{
			ShowMsg(Handle ,"刊名不能为空！",3);
			return;
		}
		if (editqikanprice->Text == "") {
			editqikanprice->Text = "0";
		}

		int totalkanqi;
		float price = 0.0;
		int qikanshu;
		if (editqikanqihao->Text == "") {
			ShowMsg(Handle ,"期刊号不能为空！",3);
			editqikanqihao->SetFocus();
			return;
		}
		try {
			price = StrToFloat(editqikanprice->Text);
			qikanshu = StrToInt(editqikanqihao->Text);
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
			if (totalkanqi < qikanshu) {
				editqikanqihao->SetFocus();
				ShowMsg(Handle ,"录入期数过大，请重新录入！",3);
				return;
			}
		}
	}
	else
	{
		if (editbookname->Text == "") {
			ShowMsg(Handle ,"书名不能为空！",3);
			return;
		}
		if ((editprice->Text == "￥0.00")||(editprice->Text == "")) {
			ShowMsg(Handle ,"定价不能为空！",3);
			return;
		}

		if (rcbpress->Text=="") {
			pressid  = -1;
		} else
		{
			try {
				pressid = (int)(rcbpress->Items->Objects[rcbpress->ItemIndex]);
			} catch (...) {
				return;
			}
		}
	}

	if (newbook == 1) {

		sql = "select id from BS_BookCatalog where ISBN = '" + editisbn->Text + "' and Barcode = '" + editcode->Text + "' and Price = " + editprice->Text + " and Author = '" + editauthor->Text + "' and Name = '" + editbookname->Text + "' and PressID = " + IntToStr(pressid) + " and PressCount like '%" + edpresscount->Text + "%'" ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->IsEmpty() ) {
			comAddcatalog->Parameters->ParamByName("@ISBN")->Value = editisbn->Text;
			comAddcatalog->Parameters->ParamByName("@Name")->Value = editbookname->Text;
			comAddcatalog->Parameters->ParamByName("@Price")->Value = editprice->Text;
			comAddcatalog->Parameters->ParamByName("@Author")->Value = editauthor->Text;
			comAddcatalog->Parameters->ParamByName("@PressCount")->Value = edpresscount->Text;
			comAddcatalog->Parameters->ParamByName("@Press")->Value = rcbpress->Text;
			comAddcatalog->Execute();
			newcatalogid =  comAddcatalog->Parameters->ParamByName("@return_value")->Value;
		}
		else
		{
			newcatalogid = aq->FieldByName("id")->AsInteger ;
		}
		delete aq;
		ModalResult = mrOk ;
	}
	else
	{
		if (pgqikan->Visible ) {

			if (ShowMsg(Handle ,"确定修改该期刊吗？",1)==1) {

                sql = "update BS_BookCatalog set isbn ='" + editqikanissn->Text + "', name='" +editqikanname->Text + "',userdefcode = '";
				sql = sql +  editqikanself->Text + "', price = " + editqikanprice->Text + ",barcode = '" + editqikanmao->Text ;
				sql = sql + "', presscount = '" + editqikanqihao->Text + "',year = '" + sedyear->Text + "',PressID = " + IntToStr(pressid) + ",smallBookTypeID = " + IntToStr(booktypeid) ;
				sql = sql + ",Bookformat = '" + cbkanqi->Text + "',yearprice = " + edyearprice->Text + ",kanhao = '" + edkanhao->Text + "',tongyikanhao = '" + edtykanhao->Text + "'";
				sql = sql + ",duokan = " + BoolToStr(chduokan->Checked)+",bk='"+editbk->Text+"',daixiao='"+cbshengdai->Text+"'";
				if (chduokan->Checked ) {
					sql = sql + ",duokantext = '" + cbduokan->Text + "',duokannum = " + sedkannum->Text ;
				}
				else
				{
					sql = sql + ",duokantext = '',duokannum = 0 ";
				}
				sql = sql  + " where ID = " + IntToStr(catalogid) ;

				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				try {
					aq->ExecSQL();
				} catch (...) {
				}
				delete aq;
				Close();
			}
		}
		else
		{
			if (ShowMsg(Handle ,"确定修改该书目吗？",1)==1) {
				if (editprice->Text == "") {
					editprice->Text = "0.00";
				}
				if (meditwords->Text == "") {
					meditwords->Text = "0";
				}
				if (medityinzhang->Text == "") {
					medityinzhang->Text = "0";
				}
				int booktypeid;

				if (edtyname->Text == "") {
					booktypeid = -1;
				} else
				{
					booktypeid = TypeID;
				}

                logmessage = "修改书目《" + ybookname + "》的信息为《" + editbookname->Text.Trim() + "》";
				AddEvent(1,"书目信息修改",fuserid,fstgid,logmessage,fcon);

				sql = "update BS_BookCatalog set Barcode = '" + editcode->Text + "',ISBN = '" + editisbn->Text + "',Name = '" + editbookname->Text;
				sql = sql + "',UserDefCode = '" + editbookself->Text + "',Author = '" + editauthor->Text + "',Price = " + editprice->Text;
				sql = sql + ",PressID = " + IntToStr(pressid) + ",smallbooktypeid = " + IntToStr(booktypeid) + ",Pressdate = '" + DateToStr(datapressday->Date);
				sql = sql + "',PressCount = '" + edpresscount->Text + "',ISBNType = '" + edISBNtype->Text + "',Yizhe = '" + edyizhe->Text;
				sql = sql + "',Printcount = " + IntToStr(edprintcount->IntValue) + ",Affix = '" + edaffix->Text + "',Bookformat = '" + cbformat->Text;
				sql = sql + "',Bind = '" + cbbind->Text + "',Collectbook = '" + edbook->Text + "',BookWords = " + IntToStr(spepack->IntValue) ;
				sql = sql + ",wordscount = " + meditwords->Text + ",yinzhang = " + medityinzhang->Text + ",huojiangstate = '" + edhuojiangstate->Text + "' where id = " + IntToStr(catalogid);
				aq->Close();
				aq->SQL->Clear();
				aq->SQL->Add(sql);
				try {
					aq->ExecSQL();
				} catch (...) {
				}
				delete aq;
				Close();
			}
		}
	}
        }catch(...)
        {}
}
//---------------------------------------------------------------------------
void TfrmNewBookModify::Press1(int mode)
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
			cbpress->ItemIndex = rcbpress->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger);
		}

		delete aq;
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewBookModify::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = caFree ;
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewBookModify::editcodeKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
        editisbn->Text = editcode->Text ;
	  	editbookname->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::editbooknameKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if (Key==VK_RETURN) {
		if (editbookname->Text =="") {

                        ShowMsg(Handle ,"书名不能为空？",3);
			return;
		}
		char* t;
		AnsiString t2;
		String t1,t3,t4;
		t1 = editbookname->Text;
		int t5=1,i = editbookname->Text.Length() ;
		for( int j=1;j<=i;j++)
		{
			t3 = t1.SubString(j,1);
			t = t3.t_str();
			Word k = int (t[0])<<8;
			k = k >> 8;
			if(k<160) continue;
			t5++;
			if (t5 == 9) break;
			t = t3.t_str();
			t2 = GetPYIndexChar(t);
			t4 = t4 + t2;
		}
		editbookself->Text = t4;
		editprice->SetFocus();
	}
}

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TfrmNewBookModify::editpriceKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '-')&&(Key != '\b')) {
		Key = NULL;
	}
	if (Key==VK_RETURN) {
		editauthor->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::rcbtypeKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key==VK_RETURN)
	{
	   rcbpress->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::rcbpressKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {
		BtnSave->Click();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewBookModify::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
		if (Key == VK_F4) {
		BtnSave->Click();
	}
		if (Shift.Contains(ssCtrl)&& Key ==81  ) {
	   BtnExit->Click();
	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::edqueryKeyPress(TObject *Sender, wchar_t &Key)

{
  int indexid;
	if (Key == '\r') {
		if (edquery->Text != "") {
			Press(1);
		}
               indexid= rcbpress->ItemIndex;
		rcbpress->SetFocus();
                rcbpress->ItemIndex = indexid;
	}
}
//---------------------------------------------------------------------------
void TfrmNewBookModify::Press(int mode)
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
		rcbpress->ItemIndex = rcbpress->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger);
		delete aq;

}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::FormShow(TObject *Sender)
{
	if (newbook == 1) {
    	this->Caption = "更换书目";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::editcodeKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		AnsiString isbn;
		try {
			isbn = BuildISBNCode(editcode->Text);
		} catch (...) {
		}
		editisbn->Text = isbn;
		editisbn->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::editisbnKeyPress(TObject *Sender, wchar_t &Key)

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

void __fastcall TfrmNewBookModify::chduokanClick(TObject *Sender)
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

void __fastcall TfrmNewBookModify::editqikanmaoKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
		if (editqikanmao->Text != "") {
			if (editqikanmao->Text.Length() >= 13 ) {
				editqikanqihao->Text = editqikanmao->Text.SubString(14,editqikanmao->Text.Length()-13);
				editqikanmao->Text = editqikanmao->Text.SubString(0,13);

				editqikanname->SetFocus();
			}
			else if (editqikanmao->Text.Length() != 13) {

                                ShowMsg(Handle ,"请输入正确的条码",3);
				return;
			}
			editqikanissn->Text = BarCodeToISSN(editqikanmao->Text.Trim());
		}
		editqikanqihao->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::editqikanqihaoKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
    	if (editqikanqihao->Text == "") {

                         ShowMsg(Handle ,"期刊号不能为空!",3);
			editqikanqihao->SetFocus();
			return;
		}
		editqikanname->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::editqikanissnKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
		if (editqikanissn->Text.Length() < 8  )
		{

                        ShowMsg(Handle ,"请输入正确的ISSN编号",3);
			return;
		}
		if (editqikanissn->Text != "" && editqikanmao->Text == "") {
			editqikanmao->Text = ISSNToBarCode(editqikanissn->Text.Trim() )  ;
		}
		Perform(WM_NEXTDLGCTL, 0, 0);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::editqikannameKeyPress(TObject *Sender, wchar_t &Key)

{
  AnsiString selft,s1;
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
                if ((qihao!="")&&(editqikanqihao->Text =="")) {
                        editqikanqihao->Text=qihao;
                }
		sedyear->SetFocus();
	}
}
AnsiString TfrmNewBookModify::GetSelfQiKan(AnsiString context)
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

void __fastcall TfrmNewBookModify::sedyearKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		if (editqikanprice->Enabled ) {
			editqikanprice->SetFocus();
		}
		else
		{
        	edpress->SetFocus();
		}

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::editqikanpriceExit(TObject *Sender)
{
	float price;
	try {
		price = StrToFloat(editqikanprice->Text);
	} catch (...) {
		return;
	}
	editqikanprice->Text = FormatFloat("0.00",price);
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::editqikanpriceKeyPress(TObject *Sender, wchar_t &Key)

{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '\b')) {
		Key = NULL;
	}
	if (Key == VK_RETURN) {
	if (editqikanprice->Text=="￥0.00") {

                 ShowMsg(Handle ,"请输入定价！",3);
		return;
	}
	edpress->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::edpressKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		if (edpress->Text != "") {
			Press1(1);
		}
		cbpress->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::cbpressKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		edtypequery->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::cbkanqiExit(TObject *Sender)
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
		qikanshu = StrToInt(editqikanqihao->Text);
	} catch (...) {
	}
	if (totalkanqi < qikanshu) {
		editqikanqihao->SetFocus();

                ShowMsg(Handle ,"录入期数过大，请重新录入！",3);
		return;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::cbkanqiKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        chduokan->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::chduokanKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		if (cbduokan->Visible ) {
			cbduokan->SetFocus();
		}
		else
		{
		      //	edkanhao->SetFocus();
                       editbk->SetFocus();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::cbduokanKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        sedkannum->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::sedkannumExit(TObject *Sender)
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

void __fastcall TfrmNewBookModify::sedkannumKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
       // edkanhao->SetFocus();
           editbk->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::edkanhaoKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
      //  edtykanhao->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::edtykanhaoKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        //edyearprice->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::edyearpriceKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        BtnSave->Click();
	}
}
//---------------------------------------------------------------------------
AnsiString TfrmNewBookModify::BarCodeToISSN(AnsiString BarCode)
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
//---------------------------------------------------------------------------
AnsiString TfrmNewBookModify::ISSNToBarCode(AnsiString ISSN)
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
//---------------------------------------------------------------------------
AnsiString TfrmNewBookModify::GetSelf(AnsiString context)
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
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::editbooknameKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
	       	if (editbookname->Text != ""){
			editbookself->Text = GetSelf(editbookname->Text);
	      	}
		editbookself->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::editbookselfKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		if (editprice->Enabled ) {
			editprice->SetFocus();
		}
		else
		{
			editauthor->SetFocus();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::editpriceKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        editauthor->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::editauthorKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        spepack->SetFocus();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmNewBookModify::rcbpressKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        datapressday->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::datapressdayKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        edpresscount->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::edpresscountKeyPress(TObject *Sender, wchar_t &Key)

{
    if (Key == '\r') {
        BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::edISBNtypeKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        edyizhe->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::edyizheKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        edprintcount->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::edprintcountKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        edaffix->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::edaffixKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        cbformat->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::cbformatKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        cbbind->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::cbbindKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        edbook->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::edbookKeyPress(TObject *Sender, wchar_t &Key)
{

	if (Key == '\r') {
	   edhuojiangstate->SetFocus();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmNewBookModify::edbkKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::edhuojiangstateKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		meditwords->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::spepackKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		edpyquery->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::edpyqueryKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		Tfrmselecttype * frm = new Tfrmselecttype(Application,fcon,edpyquery->Text);
		if (mrOk == frm->ShowModal())
		{
			TypeID = frm->GetSelectID();
			edtyname->Text = frm->GetSelect();
		}
		delete frm;
		edquery->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::SpeedButton2Click(TObject *Sender)
{
   if (editisbn->Text.Trim().Length()!=10) {
      editisbn->Text =  BuildISBNCode(editcode->Text);

   }

}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::SpeedButton1Click(TObject *Sender)
{
	Tfrmselecttype * frm = new Tfrmselecttype(Application,fcon,"");
	if (mrOk == frm->ShowModal())
	{
		TypeID = frm->GetSelectID();
		edtyname->Text = frm->GetSelect();
		edtypename->Text = frm->GetSelect();
	}
	delete frm;
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::meditwordsKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		medityinzhang->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::medityinzhangKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::edtypequeryKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
		Tfrmselecttype * frm = new Tfrmselecttype(Application,fcon,edtypequery->Text);
		if (mrOk == frm->ShowModal())
		{
			TypeID = frm->GetSelectID();
			edtypename->Text = frm->GetSelect();
		}
		delete frm;
		cbkanqi->SetFocus();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmNewBookModify::cbshengdaiKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
 BtnSave->Click();
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmNewBookModify::editbkKeyPress(TObject *Sender, wchar_t &Key)
{
//
if (Key == '\r') {
cbshengdai->SetFocus();
}
}
//---------------------------------------------------------------------------


