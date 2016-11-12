//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Qikanguanli.h"
#include "ExcelImport.h"
#include "BookQuery.h"
#include "PressAdminForm.h"
#include "BooKTypeAdminForm.h"
#include "Setunite.h"
#include "Selecttype.h"
#include "global.h"
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
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma resource "*.dfm"
TfrmQikanguanli *frmQikanguanli;
//---------------------------------------------------------------------------
__fastcall TfrmQikanguanli::TfrmQikanguanli(TComponent* Owner,TADOConnection *con,int stgid)
	: TForm(Owner)
{
	query->Connection = con;
	aqinsert->Connection = con;
	addqikan->Connection = con;
	aquery->Connection = con;
	fcon = con;
	fstgid = stgid;
	ReadyData();
	int maxid;
	AnsiString sql;
	sql = "select count(*) as count from BS_BookCatalog where type = 1 and Unavailable = 1" ;
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
	sql = "select rank() over (order by A.ID) as xuhao,A.ID,A.barcode,A.daixiao,A.userdefcode,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.Unavailable,A.date,A.Type,"
		 "A.Bookformat,A.Bk,A.year,A.yearprice,A.duokan,A.duokantext,A.duokannum,A.youfa,A.youfacode,A.pressarea,A.kanhao,A.tongyikanhao,A.PressCount,"
		 "B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
		 " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID where A.ID > " + IntToStr(maxid) ;

	sql = sql + " and A.type = 1";

	aqinsert->Close();
	aqinsert->SQL->Clear();
	aqinsert->SQL->Add(sql);
	aqinsert->Open();
	modle = 0;
	TypeID = -1;
}
//---------------------------------------------------------------------------
void __fastcall TfrmQikanguanli::BtnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmQikanguanli::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------
String  TfrmQikanguanli:: GetID()
{
	return ID;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void TfrmQikanguanli::Query(String condition)
{
	if (aqinsert->Active)
	{
		aqinsert->Active = false;
	}
	String sql;
	sql = "select rank() over (order by A.ID) as xuhao,A.ID,A.barcode,A.userdefcode,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.Unavailable,A.date,A.Type,"
			"A.Bookformat,A.Bk,A.year,A.yearprice,A.duokan,A.duokantext,A.duokannum,A.youfa,A.youfacode,A.pressarea,A.kanhao,A.tongyikanhao,A.PressCount,A.daixiao,"
			"B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
			" on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID " + condition + " and type = 1";
	aqinsert->Close();
	aqinsert->SQL->Clear();
	aqinsert->SQL->Add(sql);
	aqinsert->Active = true;
	edpinzhong->Text = IntToStr(aqinsert->RecordCount);
}

//---------------------------------------------------------------------------
void __fastcall TfrmQikanguanli::BtnNewClick(TObject *Sender)
{
	int maxid;
	AnsiString sql;
	sql = "select max(id) as id from BS_BookCatalog " ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	maxid = query->FieldByName("id")->AsInteger + 1;
	sql = "select rank() over (order by A.ID) as xuhao,A.ID,A.barcode,A.daixiao,A.userdefcode,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.Unavailable,A.date,A.Type,"
		 "A.Bookformat,A.Bk,A.year,A.yearprice,A.duokan,A.duokantext,A.duokannum,A.youfa,A.youfacode,A.pressarea,A.kanhao,A.tongyikanhao,A.PressCount,"
		 "B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
		 " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID where A.ID > " + IntToStr(maxid) ;

	sql = sql + " and A.type = 1";
	aqinsert->Close();
	aqinsert->SQL->Clear();
	aqinsert->SQL->Add(sql);
	aqinsert->Active = true;
	edpinzhong->Text = IntToStr(aqinsert->RecordCount);

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
	Label3->Visible = false;
	edyearprice->Text = "0.00";
	edkanhao->Text = "";
	edtykanhao->Text = "";
	cbyoufa->Text = "";
	youfacode->Text = "";
	edpressarea->Text = "";
	bk->Text = "";
	edtypequery->Text = "";
	edtypename->Text = "";
	TypeID = -1;
	Press(0);

	BtnView->Enabled = false;
	BtnNew->Enabled = false;
	BtnClear->Enabled = false;
	BtnCancel->Enabled = false;
	BtnUndo->Enabled = false;
	BtnDelete->Enabled = false;
	BtnExport->Enabled = false;
	BtnInsertRecord->Enabled = false;
	BtnJumptoLine->Enabled = false;

	BtnSave->Enabled = true;
	BtnSaveCancel->Enabled = true;
	GroupBox2->Enabled = true;
	editqikanmao->SetFocus();
	modle = 1;
}
//---------------------------------------------------------------------------


void __fastcall TfrmQikanguanli::BtnClearClick(TObject *Sender)
{
	//  修改模式
	if (aqinsert->IsEmpty() ) {
		return;
	}
	AnsiString sql;
	sql = "declare @modify int ;"
		" exec modifprice " + aqinsert->FieldByName("ID")->AsString  + ",-1," + IntToStr(fstgid) + ",@modify output ; "
		" select @modify as modify" ;
	query->Close();
	query->SQL->Clear();
	query->SQL->Add(sql);
	query->Open();
	if (query->FieldByName("modify")->AsInteger == 1 ) {
		editqikanprice->Enabled = false;
	}

	modle = 2;
	BtnView->Enabled = false;
	BtnNew->Enabled = false;
	BtnClear->Enabled = false;
	BtnCancel->Enabled = false;
	BtnUndo->Enabled = false;
	BtnDelete->Enabled = false;
	BtnExport->Enabled = false;
	BtnInsertRecord->Enabled = false;
	BtnJumptoLine->Enabled = false;

	BtnSave->Enabled = true;
	BtnSaveCancel->Enabled = true;
	GroupBox2->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::BtnCancelClick(TObject *Sender)
{
	if (!aqinsert->IsEmpty() ) {
		for (int i=0; i < dg->SelectedRows->Count; i++) {
			aqinsert->GotoBookmark(dg->SelectedRows->Items[i]);
			aqinsert->Edit();
			aqinsert->FieldByName("Unavailable")->Value = 0;
			aqinsert->UpdateBatch(arCurrent);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::BtnDeleteClick(TObject *Sender)
{
	AnsiString sql,ids;
	if (aqinsert->IsEmpty()) {
		return;
	}

	if (!aqinsert->IsEmpty()) {
		if (ShowMsg(this->Handle,"确认要删除吗？",1) == 1) {
			if (dg->SelectedRows->Count == 0)
			{
				ids = ids + aqinsert->FieldByName("ID")->AsString;
			}
			else if (dg->SelectedRows->Count > 0)
			{
				aqinsert->Bookmark = dg->SelectedRows->Items[0];
				ids = aqinsert->FieldByName("ID")->AsString;
				for (int i=1; i < dg->SelectedRows->Count; i++)
				{
					aqinsert->Bookmark = dg->SelectedRows->Items[i];
					ids = ids + "," + aqinsert->FieldByName("ID")->AsString;
				}
			}
			TADOQuery *aq = new TADOQuery(this);
			aq->Connection = fcon;
			AnsiString sql;
			sql = "delete from BS_BookCatalog where id in (" + ids + ")";
			aq->Close();
			aq->SQL->Clear();
			aq->SQL->Add(sql);
			aq->ExecSQL();
			delete aq;
			aqinsert->Active = false;
			aqinsert->Active = true;
			edpinzhong->Text = IntToStr(aqinsert->RecordCount);
		}
	}

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
	Label3->Visible = false;
	edyearprice->Text = "0.00";
	edkanhao->Text = "";
	edtykanhao->Text = "";
	cbyoufa->Text = "";
	youfacode->Text = "";
	edpressarea->Text = "";
	bk->Text = "";
	Press(0);

       //	editqikanmao->SetFocus();
}
//---------------------------------------------------------------------------

int __fastcall TfrmQikanguanli::BrocodeToPress(String brocode)
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
	int pressid = query->FieldByName("ID")->AsInteger ;
	return pressid;
}


void __fastcall TfrmQikanguanli::FormShow(TObject *Sender)
{
  //	edtQuery->SetFocus();
  //
  if(0==version)
  {

      cbdaixiao->Visible=false;
      dg->Columns->Items[11]->Visible=false;


  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::BtnExportClick(TObject *Sender)
{
	if (aqinsert->IsEmpty() ) {
		return;
	}
       	DbgridToExcel(dg);
}
//---------------------------------------------------------------------------


//Excel导出函数
bool __fastcall TfrmQikanguanli::DbgridToExcel(TRzDBGrid* dbg)
{
	AnsiString temptext,path,ss;
	savedlg->FileName = "期刊品目管理";
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = ExtractFilePath(savedlg->FileName .c_str()  );
		Name = ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".csv";
		path =  DBPath;
	}else
        {
          return false;
        }
	int  iFileHandle;
	int   iFileLength;
	if(FileExists(path))
	   if (DeleteFileA(path))
			iFileHandle = FileCreate(path.c_str());
	   else
			return false;
	else
		iFileHandle = FileCreate(path.c_str());

	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			temptext = temptext + dbg->Columns ->Items [q]->Title ->Caption + ",";
		}
	}
	iFileLength   =   FileSeek(iFileHandle,0,2);
	FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());

	int t2 = dbg->DataSource ->DataSet ->RecordCount ;
	dbg->DataSource ->DataSet ->First();
	dbg->DataSource ->DataSet->DisableControls();
	while(!dbg->DataSource ->DataSet->Eof )
	{
		//t1=0;
		temptext = "\n";
		for(int j=1;j<dbg->Columns ->Count+1  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {

				if (dbg->Columns ->Items [j-1]->FieldName == "ISBN" || dbg->Columns ->Items [j-1]->FieldName == "kanhao") {
					temptext = temptext + "'" + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
				else if (dbg->Columns ->Items [j-1]->FieldName == "name") {
					AnsiString bookname;
					int len;
					bookname = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString;
					bookname = StringReplace(bookname , ",",".",TReplaceFlags()<<rfReplaceAll);
					temptext = temptext + bookname + ",";
				}
				else
				{
					temptext = temptext + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}
			}
		}
		iFileLength   =   FileSeek(iFileHandle,0,2);
		FileWrite(iFileHandle,temptext.c_str() ,temptext.Length());
		dbg->DataSource ->DataSet ->Next() ;
	}
	dbg->DataSource ->DataSet->EnableControls();
	FileClose(iFileHandle);
	ShowMsg(this->Handle,"导出完毕！",3);
	return false;
}
//---------------------------------------------------------------------------


void __fastcall TfrmQikanguanli::BtnViewClick(TObject *Sender)
{
	TfrmBookQuery *frm = new  TfrmBookQuery(Application,fcon);
	if (mrOk == frm->ShowModal()) {
		//int type = frm->cbQueryType->ItemIndex ;
		String Condition = frm->getcontion();
		Query(Condition);
	}
	delete frm;
	modle = 0;
}
//---------------------------------------------------------------------------


void __fastcall TfrmQikanguanli::editqikanmaoKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
		if (editqikanmao->Text != "") {
			if (editqikanmao->Text.Length() >= 13 ) {
				editqikanqihao->Text = editqikanmao->Text.SubString(14,editqikanmao->Text.Length()-13);
				editqikanmao->Text = editqikanmao->Text.SubString(0,13);
				editqikanname->SetFocus();
				editqikanissn->Text = BarCodeToISSN(editqikanmao->Text.Trim());
				return;
			}
			else if (editqikanmao->Text.Length() != 13) {
				ShowMsg(this->Handle,"请输入正确的条码！",3);
				return;
			}
			editqikanissn->Text = BarCodeToISSN(editqikanmao->Text.Trim());
		}
		editqikanqihao->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::editqikanqihaoKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
		if (editqikanqihao->Text == "") {
			editqikanqihao->SetFocus();
			ShowMsg(this->Handle,"期号必须录入！",3);
			return;
		}
    	editqikanname->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::editqikannameKeyPress(TObject *Sender, wchar_t &Key)
{
  AnsiString selft,s1;
  AnsiString nian,qihao;
	if (Key == VK_RETURN) {
		if (editqikanname->Text == "") {
			ShowMsg(this->Handle,"请输入期刊名！",3);
			return;
		}
		editqikanself->Text = GetSelfQiKan(editqikanname->Text.Trim() );
                 selft = editqikanself->Text.Trim();
                s1 = RightStr(selft,4);
                qihao = RightStr(s1,2);  //取出期号
                nian = LeftStr(s1,2);

              //  if(nian!="") sedyear->Value = StrToInt("20"+nian);
                if (qihao!="") {
                        editqikanqihao->Text=qihao;
                }


		editqikanself->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::editqikanissnKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_RETURN) {
		if (editqikanissn->Text.Length() < 8  )
		{
			ShowMsg(this->Handle,"请输入正确的ISSN编号！",3);
			return;
		}
		if (editqikanissn->Text != "" && editqikanmao->Text == "") {
			editqikanmao->Text = ISSNToBarCode(editqikanissn->Text.Trim() )  ;
		}
		Perform(WM_NEXTDLGCTL, 0, 0);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::editqikanpriceKeyPress(TObject *Sender, wchar_t &Key)
{
	if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '\b')) {
		Key = NULL;
	}
	if (Key == VK_RETURN) {
		if (editqikanprice->Text=="￥0.00" || editqikanprice->Text == "") {
			ShowMsg(this->Handle,"请输入定价！",3);
			return;
		}
		edtypequery->SetFocus();
	}
}
//---------------------------------------------------------------------------
  AnsiString TfrmQikanguanli::GetSelfQiKan(AnsiString context)
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
AnsiString TfrmQikanguanli::GetSelf(AnsiString context)
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
//---------------------------------------------------------------------------
AnsiString TfrmQikanguanli::BarCodeToISSN(AnsiString BarCode)
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
AnsiString TfrmQikanguanli::ISSNToBarCode(AnsiString ISSN)
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
void __fastcall TfrmQikanguanli::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

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
	if (Key == VK_F11) {     //撤销
		BtnSaveCancel->Click();
	}
		if (Key == VK_F6) {      //导出
		BtnExport->Click();
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

void __fastcall TfrmQikanguanli::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::chtaoshuKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == VK_RETURN) {
		BtnSave->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::BtnSaveClick(TObject *Sender)
{
	int pressid = -1,booktypeid = -1;
	AnsiString sql;
	if (rcbpress->Text != "") {
		try {
			pressid = (int)rcbpress->Items->Objects[rcbpress->ItemIndex];
		} catch (...) {
			ShowMsg(this->Handle,"请选择正确的出版社！",3);
			return;
		}
	}
	if (edyearprice->Text == "") {
        edyearprice->Text = "0";
	}
	int totalkanqi;
	float price = 0.0;
	int qikanshu;
       //	if (editqikanqihao->Text == "") {
	  //	editqikanqihao->SetFocus();
	  //	ShowMsg(this->Handle,"期号必须录入！",3);
	   //	return;
      //	}
	try {
		price = StrToFloat(editqikanprice->Text);
                if (editqikanqihao->Text=="") {
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
		ShowMsg(this->Handle,"请录入正确的期号和定价！",3);
    	return;
	}
	if (edtypename->Text == "") {
		booktypeid = -1;
	}
	else
	{
    	booktypeid = TypeID;
	}
	if (modle == 1) {
		if (editqikanprice->Text=="￥0.00" || editqikanprice->Text == "") {
			ShowMsg(this->Handle,"请输入定价！",3);
			return;
		}
		if (editqikanname->Text == "") {
			ShowMsg(this->Handle,"请输入期刊名！",3);
			return;
		}
		sql = "select * from BS_BookCatalog where type = 1 and name = '" + editqikanname->Text.Trim() + "' and presscount = '" + editqikanqihao->Text.Trim() + "' and (isbn = '" + editqikanissn->Text.Trim() + "' or Barcode = '" + editqikanmao->Text.Trim() + "') and year = '" + sedyear->Text.Trim() + "'" ;
		aquery->Close();
		aquery->SQL->Clear();
		aquery->SQL->Add(sql);
		aquery->Open();
		if (!aquery->IsEmpty() ) {
			ShowMsg(this->Handle,"该期刊已存在，请重新录入期刊！",3);
			return;
		}
		try
		{
                //判断是否是年度期刊

              /*
                if (cbkanqi->ItemIndex==7) {
                   	if (ShowMsg(this->Handle,"您选择的是年度期刊,需要自动生成吗？",1) == 1)
                        {


                        }
                }
                   */




			if (ShowMsg(this->Handle,"确定要产生新期刊吗？",1) == 1) {
				aqinsert->Append();
				aqinsert->FieldByName("isbn")->AsAnsiString =  editqikanissn->Text ;
				aqinsert->FieldByName("name")->AsAnsiString = editqikanname->Text ;
				aqinsert->FieldByName("userdefcode")->AsAnsiString =   editqikanself->Text ;
				aqinsert->FieldByName("price")->AsFloat  =  StrToFloat(editqikanprice->Text);
				aqinsert->FieldByName("barcode")->AsAnsiString = editqikanmao->Text ;
				aqinsert->FieldByName("date")->AsDateTime  =  Now();
				aqinsert->FieldByName("Unavailable")->AsInteger  =  1;
				aqinsert->FieldByName("type")->AsInteger  =  1;
				aqinsert->FieldByName("presscount")->AsAnsiString =  editqikanqihao->Text ;
				aqinsert->FieldByName("year")->AsAnsiString =  sedyear->Text ;
				aqinsert->FieldByName("pid")->AsInteger  =  pressid;
				aqinsert->FieldByName("smallBookTypeID")->AsInteger  =  booktypeid;
				aqinsert->FieldByName("Bookformat")->AsAnsiString =  cbkanqi->Text ;
				aqinsert->FieldByName("duokan")->AsBoolean = chduokan->Checked;
				if (chduokan->Checked ) {
					aqinsert->FieldByName("duokantext")->AsAnsiString = cbduokan->Text;
					aqinsert->FieldByName("duokannum")->AsInteger = sedkannum->Value;
				}
				aqinsert->FieldByName("yearprice")->AsFloat =  StrToFloat(edyearprice->Text);
				aqinsert->FieldByName("kanhao")->AsAnsiString =  edkanhao->Text ;
				aqinsert->FieldByName("tongyikanhao")->AsAnsiString =  edtykanhao->Text ;
				aqinsert->FieldByName("youfa")->AsAnsiString =  cbyoufa->Text ;
				aqinsert->FieldByName("youfacode")->AsAnsiString =  youfacode->Text ;
				aqinsert->FieldByName("pressarea")->AsAnsiString =  edpressarea->Text ;
				aqinsert->FieldByName("Bk")->AsAnsiString =  bk->Text ;
                                 aqinsert->FieldByName("daixiao")->AsAnsiString =  cbdaixiao->Text;
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
				Label3->Visible = false;
				edyearprice->Text = "0.00";
				edkanhao->Text = "";
				edtykanhao->Text = "";
				cbyoufa->Text = "";
				youfacode->Text = "";
				edpressarea->Text = "";
				bk->Text = "";
				edtypequery->Text = "";
				edtypename->Text = "";
                TypeID = -1;
				Press(0);
				editqikanmao->SetFocus();
				if (rzcbinput->Checked) {
					modle = 1;
				}
				else
				{
					modle = 0;
					BtnView->Enabled = true;
					BtnNew->Enabled = true;
					BtnClear->Enabled = true;
					BtnCancel->Enabled = true;
					BtnUndo->Enabled = true;
					BtnDelete->Enabled = true;
					BtnExport->Enabled = true;
					BtnInsertRecord->Enabled = true;
					BtnJumptoLine->Enabled = true;

					BtnSave->Enabled = false;
					BtnSaveCancel->Enabled = false;
					GroupBox2->Enabled = false;
				}
			}
		}
		catch(...)
		{}
	}
	if (modle == 2) {   //修改
		if (aqinsert->IsEmpty() ) {
			return;
		}
		if(ShowMsg(this->Handle,"确认修改期刊信息？",1) == 1) {
			sql = "update BS_BookCatalog set isbn ='" + editqikanissn->Text + "', name='" +editqikanname->Text + "',userdefcode = '";
			sql = sql +  editqikanself->Text + "', price = " + editqikanprice->Text + ",barcode = '" + editqikanmao->Text ;
			sql = sql + "', presscount = '" + editqikanqihao->Text + "',year = '" + sedyear->Text + "',PressID = " + IntToStr(pressid) + ",smallBookTypeID = " + IntToStr(booktypeid) ;
			sql = sql + ",Bookformat = '" + cbkanqi->Text + "',yearprice = " + edyearprice->Text + ",kanhao = '" + edkanhao->Text + "',tongyikanhao = '" + edtykanhao->Text + "'";
			sql = sql + ",youfa = '" + cbyoufa->Text + "',youfacode = '" + youfacode->Text + "',pressarea = '" + edpressarea->Text + "',daixiao='"+cbdaixiao->Text+"',Bk = '" + bk->Text + "',duokan = " + BoolToStr(chduokan->Checked);
			if (chduokan->Checked ) {
				sql = sql + ",duokantext = '" + cbduokan->Text + "',duokannum = " + sedkannum->Text ;
			}
			else
			{
				sql = sql + ",duokantext = '',duokannum = 0 ";
			}
			sql = sql  + " where ID = " + aqinsert->FieldByName("ID")->AsAnsiString ;

			TADOQuery * aq = new TADOQuery(NULL);
			aq->Connection = fcon;
			aq->SQL->Add(sql);
			try {
				aq->ExecSQL();
            } catch (...) {
			}

			delete aq;

            TLocateOptions   Opts;
			Opts.Clear();
			Opts   <<   loPartialKey;
			String   str   = aqinsert->FieldByName("ID")->AsAnsiString;
			aqinsert->Active = false;
			aqinsert->Active = true;
			aqinsert->Locate("ID",str,Opts);

			BtnView->Enabled = true;
			BtnNew->Enabled = true;
			BtnClear->Enabled = true;
			BtnCancel->Enabled = true;
			BtnUndo->Enabled = true;
			BtnDelete->Enabled = true;
			BtnExport->Enabled = true;
			BtnInsertRecord->Enabled = true;
			BtnJumptoLine->Enabled = true;

			BtnSave->Enabled = false;
			BtnSaveCancel->Enabled = false;
			GroupBox2->Enabled = false;
			editqikanprice->Enabled = true;
			modle = 0;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::chduokanClick(TObject *Sender)
{
	if (chduokan->Checked ) {
		cbduokan->Visible = true;
		Label3->Visible = true;
		sedkannum->Visible = true;
	}
	else
	{
		cbduokan->Visible = false;
		Label3->Visible = false;
		sedkannum->Visible = false;
	}
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::edqueryKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		if (edquery->Text != "") {
			Press(1);
		}
		rcbpress->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::rcbpressKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        editqikanname->SetFocus();
	}
}
//---------------------------------------------------------------------------

void TfrmQikanguanli::Press(int mode)
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
	delete aq;
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::editqikanselfKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        editqikanprice->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::rcbtypeKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        cbkanqi->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::cbkanqiKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        chduokan->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::chduokanKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		if (chduokan->Checked ) {
        	cbduokan->SetFocus();
		}
		else
		{
        	edyearprice->SetFocus();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::edyearpriceKeyPress(TObject *Sender, wchar_t &Key)

{
    if ((Key < '0' || Key > '9')&&(Key != VK_RETURN)&&(Key !='.')&&(Key != '\b')) {
		Key = NULL;
	}
	if (Key == '\r') {
           cbdaixiao->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::edkanhaoKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
		edtykanhao->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::edtykanhaoKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        cbyoufa->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::cbyoufaKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        youfacode->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::youfacodeKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        edpressarea->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::edpressareaKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        bk->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::bkKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        BtnSave->Click();
	}
}
//---------------------------------------------------------------------------
void TfrmQikanguanli::ReadyData()
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

        sql = "select id,code,name from BS_BookType ";
        aq->Close();
        aq->SQL->Clear();
        aq->SQL->Add(sql);
        aq->Open();
        while(!aq->Eof)
        {
               // cbtype->AddItem(aq->FieldByName("code")->AsAnsiString+aq->FieldByName("name")->AsAnsiString, (TObject*)aq->FieldByName("ID")->AsInteger );
                qcbtype->AddItem(aq->FieldByName("code")->AsAnsiString+aq->FieldByName("name")->AsAnsiString, (TObject*)aq->FieldByName("ID")->AsInteger );
                aq->Next();
        }

	delete aq;
	AnsiString date = DateToStr(Date());
	date = date.SubString(0,4);
	sedyear->Value = StrToInt(date);
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::sedyearKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
        edquery->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::sedkannumKeyPress(TObject *Sender, wchar_t &Key)

{
	if (Key == '\r') {
        edyearprice->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::cbduokanKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == '\r') {
    	sedkannum->SetFocus();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmQikanguanli::BtnInsertRecordClick(TObject *Sender)
{
	if (aqinsert->IsEmpty() ) {
		return;
	}
	if (ShowMsg(this->Handle,"确认期刊书目信息正确，若生成后发现书目有误，需要一本一本修改。是否继续生成？",1) != 1) {
		return;
	}
        AnsiString year;
        year = FormatDateTime("yyyy",Now());
	addqikan->ProcedureName = "USP_BS_Createqikan";
	addqikan->Parameters->Clear();
	addqikan->Parameters->CreateParameter("@ID",ftInteger,pdInput,sizeof(int),aqinsert->FieldByName("ID")->AsInteger);
	addqikan->Parameters->CreateParameter("@year",ftString,pdInput,10,year );
	addqikan->Parameters->CreateParameter("@insertcount",ftString,pdOutput,10,"0" );
	try {
		addqikan->ExecProc();
		if (addqikan->Parameters->ParamByName("@insertcount")->Value > 0  ) {
			ShowMsg(this->Handle,"年度期刊生成成功！",3);
			aqinsert->Active = false;
			aqinsert->Active = true;
			edpinzhong->Text = IntToStr(aqinsert->RecordCount);
		}
		else
		{
			ShowMsg(this->Handle,"期刊存在，不需再生成！",3);
		}
	} catch (...) {
		ShowMsg(this->Handle,"年度期刊生成失败！",3);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::cbkanqiExit(TObject *Sender)
{
	int totalkanqi;
	float price = 0.00;
	int qikanshu;
	try {
		price = StrToFloat(editqikanprice->Text);
                if (editqikanqihao->Text=="") {
                     qikanshu=0;
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
		else if (cbkanqi->Text == "旬刊") {
			totalkanqi = 36;
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
		edyearprice->Text = FormatFloat("0.00",price*totalkanqi);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::sedkannumExit(TObject *Sender)
{
	int totalkanqi;
	float price = 0.00;
	try {
		price = StrToFloat(editqikanprice->Text);
	} catch (...) {
		return;
	}
	if (cbkanqi->Text != "") {
		if (cbkanqi->Text == "周刊") {
			totalkanqi = 52;
		}
		else if (cbkanqi->Text == "旬书") {
			totalkanqi = 36;
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
		edyearprice->Text = FormatFloat("0.00",price*totalkanqi*sedkannum->Value);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::editqikanqihaoExit(TObject *Sender)
{
	if (editqikanqihao->Text != "") {
		if (editqikanqihao->Text.Length() == 1 ) {
            editqikanqihao->Text = "0" + editqikanqihao->Text;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::BtnUndoClick(TObject *Sender)
{
	if (!aqinsert->IsEmpty() ) {
		for (int i=0; i < dg->SelectedRows->Count; i++) {
			aqinsert->GotoBookmark(dg->SelectedRows->Items[i]);
			aqinsert->Edit();
			aqinsert->FieldByName("Unavailable")->Value = 1;
			aqinsert->UpdateBatch(arAll);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::dgCellClick(TColumn *Column)
{
	if ( aqinsert->IsEmpty() ) {
		return;
	}
	if (modle == 2) {
		return;
	}
	if (modle == 1) {
		if (ShowMsg(this->Handle,"正在添加期刊，确定复制该期刊信息到录入框？",1)!= 1)
		{
			editqikanmao->SetFocus();
			return;
		}
	}

	editqikanissn->Text  = aqinsert->FieldByName("isbn")->AsAnsiString   ;
	editqikanname->Text  =	aqinsert->FieldByName("name")->AsAnsiString  ;
	editqikanself->Text =	aqinsert->FieldByName("userdefcode")->AsAnsiString ;
	editqikanprice->Text =	aqinsert->FieldByName("price")->AsAnsiString  ;
	editqikanmao->Text =	aqinsert->FieldByName("barcode")->AsAnsiString  ;
	editqikanqihao->Text=  aqinsert->FieldByName("presscount")->AsAnsiString ;
	sedyear->Text = aqinsert->FieldByName("year")->AsAnsiString ;
	TypeID = aqinsert->FieldByName("smallbooktypeid")->AsInteger;
	edtypename->Text = aqinsert->FieldByName("typename")->AsAnsiString ;
	rcbpress->ItemIndex = rcbpress->Items->IndexOfObject((TObject*)aqinsert->FieldByName("pid")->AsInteger);
	cbkanqi->Text = aqinsert->FieldByName("Bookformat")->AsAnsiString ;
	chduokan->Checked = aqinsert->FieldByName("duokan")->AsBoolean ;
	if (aqinsert->FieldByName("duokan")->AsBoolean) {
		cbduokan->Text = aqinsert->FieldByName("duokantext")->AsAnsiString ;
		sedkannum->Text = aqinsert->FieldByName("duokannum")->AsAnsiString ;
		cbduokan->Visible = true;
		sedkannum->Visible = true;
		Label3->Visible = true;
	}
	else
	{
		cbduokan->Visible = false;
		sedkannum->Visible = false;
		Label3->Visible = false;
	}
	edyearprice->Text = aqinsert->FieldByName("yearprice")->AsAnsiString ;
	edkanhao->Text = aqinsert->FieldByName("kanhao")->AsAnsiString ;
	edtykanhao->Text = aqinsert->FieldByName("tongyikanhao")->AsAnsiString ;
	cbyoufa->Text = aqinsert->FieldByName("youfa")->AsAnsiString ;
	youfacode->Text = aqinsert->FieldByName("youfacode")->AsAnsiString ;
	edpressarea->Text = aqinsert->FieldByName("pressarea")->AsAnsiString ;
	bk->Text = aqinsert->FieldByName("Bk")->AsAnsiString ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::dgTitleClick(TColumn *Column)
{

	if (aqinsert->IsEmpty() ) {
		return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (aqinsert->Sort == "") {
		aqinsert->Sort =  Column->FieldName + " ASC";
	}
	else if (aqinsert->Sort == qusort) {
		aqinsert->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		aqinsert->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::BtnSaveCancelClick(TObject *Sender)
{
	if (modle == 0) {
		return;
	}
	if (modle == 1) {
		if (ShowMsg(this->Handle,"正在添加期刊，确定撤销？",1) != 1){
			return;
		}
	}
	if (modle == 2) {
		if (ShowMsg(this->Handle,"正在修改期刊，确定撤销？",1) != 1){
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
	BtnInsertRecord->Enabled = true;
	BtnJumptoLine->Enabled = true;

	BtnSave->Enabled = false;
	BtnSaveCancel->Enabled = false;
	GroupBox2->Enabled = false;
	editqikanprice->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::RzButton1Click(TObject *Sender)
{
Screen->Cursor = crHourGlass;
AnsiString sql;
       sql = "select rank() over (order by A.ID) as xuhao,A.ID,A.barcode,A.userdefcode,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.Unavailable,A.date,A.Type,"
		 "A.Bookformat,A.Bk,A.year,A.daixiao,A.yearprice,A.duokan,A.duokantext,A.duokannum,A.youfa,A.youfacode,A.pressarea,A.kanhao,A.tongyikanhao,A.PressCount,"
		 "B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
		 " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID where A.type = 1";



          aqinsert->Close();
        aqinsert->SQL->Clear();
        aqinsert->SQL->Add(sql);
        aqinsert->Open();


	edpinzhong->Text = IntToStr(aqinsert->RecordCount);
        Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::RzButton2Click(TObject *Sender)
{
        Screen->Cursor = crHourGlass;
        AnsiString sql;
      sql = "select rank() over (order by A.ID) as xuhao,A.ID,A.barcode,A.userdefcode,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.Unavailable,A.date,A.Type,"
		 "A.Bookformat,A.Bk,A.year,A.yearprice,A.duokan,A.duokantext,A.duokannum,A.youfa,A.youfacode,A.pressarea,A.kanhao,A.tongyikanhao,A.PressCount,"
		 "B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
		 " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID where Unavailable = 0 and A.type = 1";



          aqinsert->Close();
        aqinsert->SQL->Clear();
        aqinsert->SQL->Add(sql);
        aqinsert->Open();

	//aqinsert->Active = false;
      //	aqinsert->Filtered = true;
      //	aqinsert->Filter =  " Unavailable = 0";
      //	aqinsert->Active = true;
	edpinzhong->Text = IntToStr(aqinsert->RecordCount);
        Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::RzButton3Click(TObject *Sender)
{                  AnsiString sql;
    Screen->Cursor = crHourGlass;
           sql = "select rank() over (order by A.ID) as xuhao,A.ID,A.barcode,A.userdefcode,A.name,A.ISBN,A.pressid as pid,A.smallbooktypeid,A.price,A.Unavailable,A.date,A.Type,"
		 "A.Bookformat,A.Bk,A.year,A.yearprice,A.duokan,A.duokantext,A.duokannum,A.youfa,A.youfacode,A.pressarea,A.kanhao,A.tongyikanhao,A.PressCount,"
		 "B.abbreviatedname,C.name as typename from bs_bookcatalog A left join BS_PressInfo B "
		 " on A.pressid = B.ID left join BS_BookType C on A.smallbooktypeid = C.ID where Unavailable = 1 and A.type = 1";



          aqinsert->Close();
        aqinsert->SQL->Clear();
        aqinsert->SQL->Add(sql);
        aqinsert->Open();

      //	aqinsert->Active = false;
	//aqinsert->Filtered = true;
	////aqinsert->Filter =  " Unavailable = 1";
       //	aqinsert->Active = true;
	edpinzhong->Text = IntToStr(aqinsert->RecordCount);
         Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::btaddtypeClick(TObject *Sender)
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

void __fastcall TfrmQikanguanli::spselectTypeClick(TObject *Sender)
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



void __fastcall TfrmQikanguanli::edtypequeryKeyPress(TObject *Sender, wchar_t &Key)

{

	if (Key == '\r') {
	      /*	Tfrmselecttype * frm = new Tfrmselecttype(Application,fcon,edtypequery->Text);
		if (mrOk == frm->ShowModal())
		{
			TypeID = frm->GetSelectID();
			edtypename->Text = frm->GetSelect();
		}                   edtypequery
		delete frm;   */
                AnsiString sql;
                  TADOQuery *aq = new TADOQuery(this);
	          aq->Connection = fcon;
                 if (edtypequery->Text != "") {
                            sql = "select id,code,name from BS_BookType where code like '%" + edtypequery->Text.Trim() + "%'" ;
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

                        if (edtypequery->Text != "")
                        {
                             if (aq->RecordCount > 0) {
                              //aq->First();
                              qcbtype->ItemIndex = 0;
                            }
                        }else {
                             qcbtype->ItemIndex = -1;

                        }
                        delete aq;
                        qcbtype->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::qcbtypeKeyPress(TObject *Sender, wchar_t &Key)
{
   if (Key == VK_RETURN) {
                if (edtypequery->Text !="") {
                 if (qcbtype->Items->Count>0 ) {
                    qcbtype->ItemIndex = 0;
                   }
                }
                cbkanqi->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmQikanguanli::cbdaixiaoKeyPress(TObject *Sender, wchar_t &Key)

{  if (Key == VK_RETURN) {
    edkanhao->SetFocus();
}
}
//---------------------------------------------------------------------------

