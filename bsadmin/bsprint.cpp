//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "bsprint.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RpCon"
#pragma link "RpConBDE"
#pragma link "RpConDS"
#pragma link "RpDefine"
#pragma link "RpRave"
#pragma link "RpBase"
#pragma link "RpSystem"
#pragma link "frxClass"
#pragma link "frxDBSet"
#pragma link "frxCross"
#pragma link "frxRich"
#pragma link "frxExportXLS"
#pragma link "frxExportPDF"
#pragma resource "*.dfm"
Tfrmwsaleprinta *frmwsaleprinta;
//---------------------------------------------------------------------------
__fastcall Tfrmwsaleprinta::Tfrmwsaleprinta(TComponent* Owner,TADOConnection *cn)
	: TForm(Owner)
{
	Rpdefine::DataID = IntToStr((int)HInstance);
	aqdetail->Connection = cn;
	aqHeader->Connection = cn;
	aqtotalnum->Connection = cn;
	aqhead->Connection = cn;
	aqrvstoragedetail->Connection = cn;
	aqorderdetail->Connection = cn;
	aqorderhead->Connection = cn;
	aqProcureDetail->Connection = cn;
	aqProcureHeader ->Connection = cn;
	aqstoragechashu->Connection = cn;
        aqmuildetail->Connection = cn;
        aqmuilprinthead->Connection = cn;
        queryA5->Connection=cn;
        queryA4->Connection =cn;
	PrintType = 0;
	fcon = cn;
        lianxueprint = false;
}
//---------------------------------------------------------------------------
void Tfrmwsaleprinta::PrintStorage(int ID)
{
	aqhead->Parameters->ParamByName("ID")->Value =ID ;
	aqrvstoragedetail->Parameters->ParamByName("ID")->Value = ID;
	aqhead->Active = true;
	aqrvstoragedetail->Active = true;
	TADOQuery *aq =new TADOQuery(this);
	aq->Connection = fcon;
	AnsiString sql = "select count(*) as count from BS_StorageNote where StgNtHeaderID = " + IntToStr(ID);
	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
	Kind = aq->FieldByName("count")->AsInteger ;
	delete aq;
}
//---------------------------------------------------------------------------
void Tfrmwsaleprinta::PrintStoragechashu(int ID)
{
	   aqhead->Parameters->ParamByName("headID")->Value =ID ;
	   aqstoragechashu->Parameters->ParamByName("ID")->Value = ID;
	   aqhead->Active = true;
	   aqstoragechashu->Active = true;
}
void Tfrmwsaleprinta::PrintStorageExe(int type)
{
    AnsiString sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	sql = "select * from sys_bsset where name = 'xiaoshudian'" ;
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

	if (tuihuo == 1) {
		frxstorage->LoadFromFile(Sysutils::ExtractFilePath(Application->ExeName) + "storagereturn.fr3");
	}
	else
	{
		frxstorage->LoadFromFile(Sysutils::ExtractFilePath(Application->ExeName) + "storage.fr3");
	}


	frxstorage->PrepareReport(true);
	if (type == 0) {
		frxstorage->PrintOptions->ShowDialog = false;
		frxstorage->Print();
	}
	else
	{      // =frxformat;
		frxstorage->ShowPreparedReport();
	}
	frxstorage->Free();
	return;
}

void Tfrmwsaleprinta::PrintStorageExe()
{
	int prientcount;
   int num = 0;
   float totalfixedprice = 0.0,totaldiscountprice = 0.0;
   wholesale->ProjectFile  = ExtractFilePath(Application->ExeName)+"chashustorage.rav";
			wholesale->SetParam("title",printtitle+"入库单异常");
			wholesale->SetParam("bk",aqhead->FieldByName("remarks")->AsAnsiString);  //单号
			if (DanhaoChange) {
			 wholesale->SetParam("Danhao",aqhead->FieldByName("stgntcodestr")->AsAnsiString);
			}else                               //change danhao
			{
			  wholesale->SetParam("Danhao",aqhead->FieldByName("Stgntcode")->AsAnsiString);
			}
   aqstoragechashu->First() ;
	while (!aqstoragechashu->Eof)
	{
		num = num + aqstoragechashu->FieldByName("amount")->AsInteger ;
		totalfixedprice = totalfixedprice + (aqstoragechashu->FieldByName("amount")->AsInteger)*(aqstoragechashu->FieldByName("price")->AsFloat) ;
		totaldiscountprice = totaldiscountprice + (aqstoragechashu->FieldByName("amount")->AsInteger)*(aqstoragechashu->FieldByName("price")->AsFloat)*(aqstoragechashu->FieldByName("discount")->AsFloat)/100 ;
		aqstoragechashu->Next();
	}

	wholesale->Open();
	wholesale->SetParam("num",num);
	wholesale->SetParam("totalfixedprice",totalfixedprice);
	wholesale->SetParam("totaldiscountprice",totaldiscountprice);
	wholesale->SetParam("rkbk",rkbk);
	  wholesale->SetParam("operator",Maker) ;

	  /*TRavePage *RavePage;
		TRaveRegion *RaveRegion;
		double top,hight;
		RavePage = (TRavePage *)wholesale->ProjMan->FindRaveComponent("Report1.Page1",NULL);
		RaveRegion = (TRaveRegion *)wholesale->ProjMan->FindRaveComponent("Region1",RavePage);
		prientcount = aqstoragechashu->RecordCount ;
		aqstoragechashu->First();
		while (!aqstoragechashu->Eof )
		{
			if (aqstoragechashu->FieldByName("Name")->AsAnsiString.Length() > 72  ) {
				prientcount = prientcount + 2;
			}
			else if (aqstoragechashu->FieldByName("Name")->AsAnsiString.Length() > 36  ) {
				prientcount++;
			}
			aqstoragechashu->Next();
		}
		//aqrvstoragedetail->First();

		hight = 0.18*prientcount;

		if (rkbk == "") {
			RavePage->PageHeight = hight + 2.96;
			//RavePage->PageWidth = 8;
			RaveRegion->Height = hight + 2.95;
		}
		else
		{
			RavePage->PageHeight = hight + 3.16;
			//RavePage->PageWidth = 8;
			RaveRegion->Height = hight + 3.15;
		}
		   */

	wholesale->Execute();
	wholesale->Close();
}

void Tfrmwsaleprinta::InputPara(AnsiString ID)
{
	AnsiString sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcon;
	if (PrintType ==1 ) {      //订单
		aqorderdetail->Parameters->ParamByName("ID")->Value = ID;
		aqorderhead->Parameters->ParamByName("ID")->Value = ID;
		aqorderdetail->Active = true;
		aqorderhead->Active = true;
		wholesale->SetParam("title",aqorderhead->FieldByName("name")->AsAnsiString+ " 收订单" );
		sql = "select count(*) as count from BS_OrderNote where OrderNtHeaderID = " + ID;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		Kind =aq->FieldByName("count")->AsInteger ;
	}else if (PrintType == 2) {            //采购
		aqProcureDetail->Parameters->ParamByName("ID")->Value = ID;
		aqProcureHeader->Parameters->ParamByName("ID")->Value = ID;
		aqProcureDetail->Active = true;
		aqProcureHeader->Active = true;
		sql = "select count(*) as count from BS_ProcureNote where ProcureNtHeaderID = " + ID;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		Kind =aq->FieldByName("count")->AsInteger ;
	}
	else
	{       aqtotalnum->Active = false;
		aqtotalnum->Parameters->ParamByName("headID")->Value =ID ;
                AnsiString sql1;
              //  TADOQuery *aq = new TADOQuery(this);
              //  aq->Connection = fcon;
                sql1 = "select * from sys_bsset where name = 'salexiaoshudian'" ;
                aq->Close();
                aq->SQL->Clear();
                aq->SQL->Add(sql1);
                aq->Open();
                format = aq->FieldByName("bk")->AsAnsiString ;
                wsalexiaoshudian = format;
                if (format=="0.00") {
                    format="2";
                }else if (format=="0.0") {
                        format="1";
                      }


                aqHeader->Active = false;
		aqHeader->Parameters->ParamByName("ID")->Value = ID;

		sql = "SELECT RANK() OVER(order by F.ID asc) as xuhao,F.* FROM "
			" (select A.ID ID,rtrim(A.incode) AS incode,rtrim(C.ISBN) as ISBN,rtrim(C.Name) as CatalogName,rtrim(C.UserDefCode) as UserDefCode,rtrim(E.AbbreviatedName) as AbbreviatedName,rtrim(C.Author) as Author,C.Price,C.PressCount,C.BookWords,convert(nvarchar(10),C.Pressdate,120) as Pressdate,A.amount as Amount ,A.Discount discount, "
			" rtrim(c.huojiangstate) as huojiangstate,A.xiaoqu,A.xueyuan,A.course,cast(A.fixedprice as decimal(18,"+format+")) as FixedPrice,cast(A.discountedprice as decimal(18,"+format+")) as  DiscountedPrice "
			" from BS_WsaleNote A "
			" left join STK_BookInfo B on A.bkinfoid = B.ID "
			" left join BS_BookCatalog C on B.bkcatalogID = C.ID "
			" left join BS_PressInfo E on E.ID = C.pressID ";
                 if (pixiaoortuihuo) {
                  sql=sql+" where A.wsalentheaderid= " + ID+") F ";//批销里　有退货
                 }else
                 {
                  sql=sql+" where A.wsalentheaderid= " + ID+" and A.amount <= 0) F ";

                 }

		 //sql=sql+ " group by C.ID,C.ISBN,C.Name,C.UserDefCode,E.abbreviatedname,C.author,C.price,C.PressCount,c.huojiangstate,A.xiaoqu,A.xueyuan,A.course,C.BookWords,C.Pressdate,A.incode) F "
		 //	" ORDER BY ID ASC"  ;

                 //sql = sql+" ORDER BY F ASC";
		aqdetail->Close();
		aqdetail->SQL->Clear();
		aqdetail->SQL->Add(sql);
		aqdetail->Open();
		//aqdetail->Active = true;
		aqHeader->Active = true;
		aqtotalnum->Active = true;
		sql = "select count(bkcatalogID) as count from BS_WsaleNote where WsaleNtHeaderID = " + ID;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		Kind =aq->FieldByName("count")->AsInteger ;
	}
	delete aq;
}
void Tfrmwsaleprinta::previewprint(int type , int simple)         //type=0 打印,=1预览
{
	int prientcount;
        TfrxReportPage* P;
    format1 = "0.0";
	if (simple == 1 || simple == 2) {                            //1,批销单 2.批销退货单 //1打印格式1 2 打印格式2

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

		AnsiString ps,psplus;
		TADOQuery *aptitle = new TADOQuery(NULL);
		aptitle->Connection = fcon ;
		aptitle->Close();
		aptitle->SQL->Clear();
		if (printmodle > -1) {
			sql = "select reportname from sys_printhead where id = " + IntToStr(printmodle);
			aptitle->Close();
			aptitle->SQL->Clear();
			aptitle->SQL->Add(sql);
			aptitle->Open();
			ps = aptitle->FieldByName("reportname")->AsAnsiString.Trim() + ".fr3"  ;
			aptitle->Close();
			aptitle->SQL->Clear();
			sql = "select sys_printdetail.*,sys_printhead.typename from sys_printdetail left join sys_printhead on sys_printdetail.headid = sys_printhead.id where sys_printdetail.[print] = 1 and sys_printdetail.headid = "  + IntToStr(printmodle) + " order by sys_printdetail.id";
		}
		else
		{
            sql = "select reportname from sys_printhead where modle = 1 and sys_printhead.active = 1 and sys_printhead.stgid = " + IntToStr(stgid) ;
			aptitle->Close();
			aptitle->SQL->Clear();
			aptitle->SQL->Add(sql);
			aptitle->Open();
			ps = aptitle->FieldByName("reportname")->AsAnsiString.Trim() + ".fr3"  ;
			aptitle->Close();
			aptitle->SQL->Clear();
			sql = "select sys_printdetail.*,sys_printhead.typename from sys_printdetail left join sys_printhead on sys_printdetail.headid = sys_printhead.id where sys_printdetail.[print] = 1 and sys_printhead.modle = 1 and sys_printhead.active = 1 and sys_printhead.stgid = " + IntToStr(stgid) + " order by sys_printdetail.id";
		}
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
                if (lianxueprint) {
                 ps = ExtractFilePath(Application->ExeName) +"Wsalerlianxue.fr3";
                }else
		ps = ExtractFilePath(Application->ExeName) +"Wsalerec.fr3";
                psplus=ExtractFilePath(Application->ExeName) +"Wsalerecnofengye.fr3";

		frxWsale->LoadFromFile(ps);
		frxWsale->PrepareReport(true);

              //  ShowMessage(IntToStr(frxWsale->Engine->TotalPages));

             if (frxWsale->Engine->TotalPages==1) { //如果总页数小于1　就不用分页打应
                     frxWsale->Clear();
                     frxWsale->LoadFromFile(psplus);
                     frxWsale->PrepareReport(true);

                   // ((TfrxReportPage*)frxWsale->Pages[1])->EndlessHeight=true;
                 //  P->EndlessHeight =true;
                  // frxWsale->Pages[0]->

              }


		if (type == 0) {          //
			frxWsale->PrintOptions->ShowDialog = false;
		       frxWsale->Print();
                      //frxWsale->ShowPreparedReport();
		}
		else
		{     //  PrintSerial(frxWsale,0);
                   //    double heg;
                      // heg =frxWsale->Engine->TotalPages*297;
                       // frxWsale->Engine->
                    //   TfrxReportPage* P;
                    //   P= (TfrxReportPage*)frxWsale->Pages[0];
                   //    P->EndlessHeight =true;


                      //  frxWsale->Pages[0]->Page->Height= heg;
			frxWsale->ShowPreparedReport();

                       //  ShowMessage(FloatToStr(frxWsale->Height));
		}


	}else if (simple == 3) { //订单打印

		frxOrder->LoadFromFile(Sysutils::ExtractFilePath(Application->ExeName) + "Order.fr3");
		frxOrder->PrepareReport(true);
		if (type == 0) {
			frxOrder->PrintOptions->ShowDialog = false;
			frxOrder->Print();
		}
		else
		{
			frxOrder->ShowPreparedReport();
		}
		frxOrder->Free();

	}else if (simple == 4) {//采购打印
	      //	if (aqProcureHeader->FieldByName("inorder")->AsInteger == 1 ) {
		//	frxProcure->LoadFromFile(Sysutils::ExtractFilePath(Application->ExeName) + "Procurein.fr3");
	       //	}
	       //	else
	       //	{
			frxProcure->LoadFromFile(Sysutils::ExtractFilePath(Application->ExeName) + "Procure.fr3");
	       //	}

		frxProcure->PrepareReport(true);
		if (type == 0) {
			frxProcure->PrintOptions->ShowDialog = false;
			frxProcure->Print();
		}
		else
		{
			frxProcure->ShowPreparedReport();
		}
		frxProcure->Free();
	}
}
//---------------------------------------------------------------------------

AnsiString Tfrmwsaleprinta::Doubletostring(double num)
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
//---- -----------------------------------------------------------------------
AnsiString Tfrmwsaleprinta::Touppnum(AnsiString ychar)
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
//---------------------------------------------------------------------------

void __fastcall Tfrmwsaleprinta::frxProcureGetValue(const UnicodeString VarName, Variant &Value)

{
	if (CompareText(VarName,"\"num\"")==0 ) {
		  Value = num;
	}
	if (CompareText(VarName,"\"Name\"")==0 ) {
		  Value = printtitle;
	}
	if (CompareText(VarName,"\"printbk\"")==0 ) {
		  Value = pxbk;
	}
	if (CompareText(VarName,"\"contact\"")==0 ) {
		  Value = contact;
	}
	if (CompareText(VarName,"\"tel\"")==0 ) {
		  Value = tel;
	}
	if (CompareText(VarName,"\"address\"")==0 ) {
		  Value = address;
	}
	if (CompareText(VarName,"\"shcontact\"")==0 ) {
		  Value = shcontact;
	}
	if (CompareText(VarName,"\"shtel\"")==0 ) {
		  Value = shtel;
	}
	if (CompareText(VarName,"\"shaddress\"")==0 ) {
		  Value = shaddress;
	}
}
//---------------------------------------------------------------------------


void __fastcall Tfrmwsaleprinta::frxWsale2GetValue(const UnicodeString VarName, Variant &Value)

{
	//传递宽度
	if (CompareText(VarName,"\"xuhao\"")==0  ) {  //序号
		 Value = FindTitlewith("xuhao");
	}
	if (CompareText(VarName,"\"incode\"")==0  ) {  //内部识别码
		 Value = FindTitlewith("incode");
	}
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
	if (CompareText(VarName,"\"Pressdate\"")==0 ) {   //出版日期
		Value = FindTitlewith("Pressdate");
	}
	if (CompareText(VarName,"\"PressCount\"")==0 ) {  //版次
		Value = FindTitlewith("PressCount");
	}
	if (CompareText(VarName,"\"BookWords\"")==0 ) {    //册/包
		Value = FindTitlewith("BookWords");
	}
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
	if (CompareText(VarName,"\"huojiangstate\"")==0 ) {   //获奖情况
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
	}

	//传递参数
	if (CompareText(VarName,"\"title\"")==0 ) {
		if (tuihuo == 1) {
			Value = printtitle + "发货退货单";
		}
		else
		{
			Value = printtitle + "发货单";
		}
	}
	if (CompareText(VarName,"\"yingshou\"")==0 ) {
		  Value = FormatFloat("￥0.00",yingshou);
	}
	if (CompareText(VarName,"\"fandian\"")==0 ) {
		  Value = FormatFloat("￥0.00",fandian);
	}
	if (CompareText(VarName,"\"pxbk\"")==0 ) {
		  Value = pxbk;
	}
	if (CompareText(VarName,"\"contact\"")==0 ) {
		  Value = contact;
	}
	if (CompareText(VarName,"\"tel\"")==0 ) {
		  Value = tel;
	}
	if (CompareText(VarName,"\"address\"")==0 ) {
		  Value = address;
	}
	if (CompareText(VarName,"\"ClientName\"")==0 ) {
		  Value = ClientName;
	}
	if (CompareText(VarName,"\"heji\"")==0 ) {
		  Value = Doubletostring(aqHeader->FieldByName("discountedprice")->AsFloat+aqHeader->FieldByName("addcosts")->AsFloat);
	}
	if (CompareText(VarName,"\"Danhao\"")==0 ) {
		if (DanhaoChange) {
			Value = aqHeader->FieldByName("WsaleNtCodeStr")->AsAnsiString;
		}else                               //change danhao
		{
			Value = aqHeader->FieldByName("WsaleNtCode")->AsAnsiString;
		}
	}

         if (CompareText(VarName,"\"totalyingshou\"")==0 )  {
            Value = FloatToStr(aqHeader->FieldByName("discountedprice")->AsFloat+aqHeader->FieldByName("addcosts")->AsFloat);
        }
}
//---------------------------------------------------------------------------

AnsiString Tfrmwsaleprinta::FindTitleName(AnsiString ColumnName)
{
	int i;
	i =  PrintTile->IndexOf(ColumnName);
	if (i != -1 ) {
		  return ((PrintControl*)PrintTile->Objects[i])->name ;
	}else return "NOTITLE";
}
//---------------------------------------------------------------------------
float Tfrmwsaleprinta::FindTitlewith(AnsiString ColumnName)
{
	int i;
	i =  PrintTile->IndexOf(ColumnName);
	if (i != -1 ) {
		  return ((PrintControl*)PrintTile->Objects[i])->width ;
	}else return 0;
}
void __fastcall Tfrmwsaleprinta::frxOrderGetValue(const UnicodeString VarName, Variant &Value)

{
	if (CompareText(VarName,"\"ClientName\"")==0 ) {
		  Value = ClientName;
	}
	if (CompareText(VarName,"\"title\"")==0 ) {
		  Value = printtitle+"收订单";
	}
	if (CompareText(VarName,"\"printbk\"")==0 ) {
		  Value = pxbk;
	}
	if (CompareText(VarName,"\"contact\"")==0 ) {
		  Value = contact;
	}
	if (CompareText(VarName,"\"tel\"")==0 ) {
		  Value = tel;
	}
	if (CompareText(VarName,"\"address\"")==0 ) {
		  Value = address;
	}
	if (CompareText(VarName,"\"Kind\"")==0 ) {
		  Value = Kind;
	}
	if (CompareText(VarName,"\"Discount\"")==0 ) {
		if (aqorderhead->FieldByName("fixedprice")->AsFloat == 0) {
			Value = 0.00;
		}
		else
		{
			Value = aqorderhead->FieldByName("discountedprice")->AsFloat * 100 / aqorderhead->FieldByName("fixedprice")->AsFloat ;
		}
	}
	if (CompareText(VarName,"\"heji\"")==0 ) {
		  Value = Doubletostring(aqorderhead->FieldByName("discountedprice")->AsFloat);
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsaleprinta::frxstorageGetValue(const UnicodeString VarName, Variant &Value)

{
	if (CompareText(VarName,"\"title\"")==0 ) {
		if (tuihuo == 1) {
			Value = printtitle + "入库退货单";
		}
		else
		{
			Value = printtitle + "入库单";
		}
	}
	if (CompareText(VarName,"\"rkbk\"")==0 ) {
		  Value = rkbk;
	}
	if (CompareText(VarName,"\"supplycode\"")==0 ) {
		  Value = supplycode;
	}
	if (CompareText(VarName,"\"Danhao\"")==0 ) {
		if (DanhaoChange) {
			Value = aqhead->FieldByName("stgntcodestr")->AsAnsiString;
		}else                               //change danhao
		{
			Value = aqhead->FieldByName("Stgntcode")->AsAnsiString;
		}
	}
	if (CompareText(VarName,"\"contact\"")==0 ) {
		  Value = contact;
	}
	if (CompareText(VarName,"\"telephone\"")==0 ) {
		  Value = tel;
	}
	if (CompareText(VarName,"\"address\"")==0 ) {
		  Value = address;
	}
	if (CompareText(VarName,"\"Kind\"")==0 ) {
		  Value = Kind;
	}
	if (CompareText(VarName,"\"Discount\"")==0 ) {
		if (aqhead->FieldByName("totalfixedprice")->AsFloat == 0) {
			Value = 0.00;
		}
		else
		{
			Value = aqhead->FieldByName("totaldiscountedprice")->AsFloat * 100 / aqhead->FieldByName("totalfixedprice")->AsFloat ;
		}
	}
	if (CompareText(VarName,"\"heji\"")==0 ) {
		  Value = Doubletostring(aqhead->FieldByName("totaldiscountedprice")->AsFloat);
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsaleprinta::frxstorageBeforePrint(TfrxReportComponent *Sender)

{
	((TfrxMemoView *)frxstorage->FindObject("Memo8"))->DisplayFormat->FormatStr=format;
	((TfrxMemoView *)frxstorage->FindObject("Memo9"))->DisplayFormat->FormatStr=format;
}
void Tfrmwsaleprinta::ExcelExport(int type)
{
       




}
//---------------------------------------------------------------------------




void __fastcall Tfrmwsaleprinta::frxWsalemuilprintGetValue(const UnicodeString VarName,
          Variant &Value)
{
      	if (CompareText(VarName,"\"Title\"")==0 ) {
        if (tuihuo==1) {
              Value = printtitle+"发货退货单";
        }else  Value = printtitle+"发货单";

	}
        if (CompareText(VarName,"\"TotalAmount\"")==0 ) {
        Value = aqmuilprinthead->FieldByName("totalamount")->AsAnsiString;
        }
        if (CompareText(VarName,"\"TotalM\"")==0 ) {
        Value = aqmuilprinthead->FieldByName("fixedprice")->AsAnsiString ;
        }
         if (CompareText(VarName,"\"TotalS\"")==0 ) {
        Value = aqmuilprinthead->FieldByName("discountedprice")->AsAnsiString ;;
        }
        if (CompareText(VarName,"\"Contact\"")==0 ) {
        Value = contact;
        }
        if (CompareText(VarName,"\"Tel\"")==0 ) {
        Value = tel;
        }
        if (CompareText(VarName,"\"Address\"")==0 ) {
        Value = address;
        }
          if (CompareText(VarName,"\"bk\"")==0 ) {
        Value = pxbk+aqmuilprinthead->FieldByName("remarks")->AsAnsiString;
        }
        if (CompareText(VarName,"\"addcosts\"")==0 ) {
        Value = aqmuilprinthead->FieldByName("addcosts")->AsAnsiString ;;
        }
         if (CompareText(VarName,"\"Totalyingshou\"")==0 ) {
        Value = FloatToStr(aqmuilprinthead->FieldByName("discountedprice")->AsFloat+aqmuilprinthead->FieldByName("addcosts")->AsFloat);
        }

}
void Tfrmwsaleprinta::A4print(AnsiString ID)
{
//A4连续打印
   AnsiString sql;

    TStringList *IDStr = new TStringList(NULL);
    AnsiString ps;
    IDStr->DelimitedText=ID;
    IDStr->Delimiter=',';

    if (IDStr->Count>1) {
       ID=ID+"-1";
    }
    try
    {
   if (pixiaoortuihuo) {//批销打印
   sql = " select U.wsprinttitle+'发货单' as printName,dbo.usf_ChineseCost(A.discountedprice) as daxi, ";
   }else sql = " select U.wsprinttitle+'发货退货单' as printName,dbo.usf_ChineseCost(A.discountedprice) as daxi, ";

    sql = sql+" U.wscontact,U.wstel,U.wsaddress,U.wsprintbk,F.name as clientname,";
    sql = sql+" F.Address as clientaddress,F.Contact as clientcontact,D.tel,A.WsaleNtCode,";
    sql = sql+" F.telephone as clienttel,";
    sql = sql+" A.WsaleNtCodeStr ,A.hdtime  as maketime ,A.totalamount ,A.fixedprice ,A.discountedprice,A.checked,A.nochecked,A.remarks,";
    sql = sql+" A.addcosts,C.name as maker ,W.amount as amount,W.discount discount,W.FixedPrice as notefixed,W.DiscountedPrice as notediscounted,Z.name as bookname,Z.price,Z.isbn,P.AbbreviatedName";
    sql = sql+" from BS_WsaleNoteHeader A";
    sql = sql+" left join sys_staffinfo B on A.staffid = B.ID";
    sql = sql+" left join sys_user C on A.operatorid = C.ID ";
    sql = sql+" left join SYS_StorageInfo D on A.stgID = D.ID ";
    sql = sql+" left join CUST_CustomerInfo F on A.vendorid = F.ID ";
    sql = sql+" left join dbo.BS_WsaleNote W on W.WsaleNtheaderID=A.ID ";
    sql = sql+" left join dbo.BS_BookCatalog Z on W.bkcatalogid =Z.ID ";
    sql = sql+" left join dbo.BS_PressInfo P on Z.pressid = P.ID ";
    sql = sql+" left join sys_printtitle U on D.id=U.stgid ";
    sql = sql+" where A.id in("+ID+") order by A.WsaleNtCodeStr";
    if (pixiaoortuihuo) {
     //   sql = sql +" group by U.wsprinttitle+'发货单' ,U.wscontact,U.wstel,U.wsaddress,U.wsprintbk, ";
    }else {}// sql = sql +" group by U.wsprinttitle+'发货退货单' ,U.wscontact,U.wstel,U.wsaddress,U.wsprintbk, ";

   // sql = sql +" F.name ,F.Address ,F.Contact ,D.tel,A.WsaleNtCode,F.telephone,A.WsaleNtCodeStr , ";
   // sql = sql +" A.hdtime,A.totalamount,A.fixedprice,A.discountedprice,A.checked,A.nochecked,A.remarks, A.addcosts, ";
   // sql = sql +" C.name  ,z.id ,Z.name ,Z.price,Z.isbn,P.AbbreviatedName ";
   queryA4->Close();
   queryA4->SQL->Clear();
   queryA4->SQL->Add(sql);
   queryA4->Open();


    ps = ExtractFilePath(Application->ExeName) +"wsaleA4.fr3";

    frxWsaleA4->LoadFromFile(ps);

    frxWsaleA4->PrepareReport(true);
     frxWsaleA4->PrintOptions->ShowDialog = false;
   // frxWsaleA4->ShowPreparedReport();
    frxWsaleA4->Print();
   }catch(...)
   {


   }

}
void Tfrmwsaleprinta::wsalemuilPrint(AnsiString ID,int type,bool xiaopiao)
{
  ///A5打印
    TStringList *IDStr = new TStringList(NULL);
     AnsiString ps;
    IDStr->DelimitedText=ID;
    IDStr->Delimiter=',';
    if (IDStr->Count>1) {
         //lianxueprint=true;
         ID=ID+"-1";
    }
    if ((!xiaopiao)&&(type==3)) { //A5连续打印

       try
       {
       AnsiString sql;
       if (!pixiaoortuihuo) {
         sql = "select A.Remarks,U.wsprinttitle+'发货退货单' as printName,";
       }else
        sql = "select A.Remarks,U.wsprinttitle+'发货单' as printName,";

        sql = sql+" U.wscontact,U.wstel,U.wsaddress,U.wsprintbk,F.name as clientname,";
        sql = sql+" A.WsaleNtCodeStr,A.hdtime ,A.hdtime  as maketime ,A.fixedprice,A.discountedprice";
        sql = sql+" ,A.addcosts,C.name as maker ,W.amount amount,W.discount discount,Z.name as bookname,Z.price,A.totalamount from BS_WsaleNoteHeader A";
        sql = sql+" left join sys_staffinfo B on A.staffid = B.ID ";
        sql = sql+" left join sys_user C on A.operatorid = C.ID";
        sql = sql+" left join SYS_StorageInfo D on A.stgID = D.ID";
        sql = sql+" left join CUST_CustomerInfo F on A.vendorid = F.ID";
        sql = sql+" left join dbo.BS_WsaleNote W on W.WsaleNtheaderID=A.ID ";
        sql = sql+" left join dbo.BS_BookCatalog Z on W.bkcatalogid =Z.ID ";
        sql = sql+" left join sys_printtitle U on D.id=U.stgid";
        sql = sql+" where A.id in("+ID+") order by A.WsaleNtCodeStr ";
       /*
          if (!pixiaoortuihuo) {
          sql = sql + " group by U.wsprinttitle+'发货退货单' ,U.wscontact,U.wstel,U.wsaddress,U.wsprintbk,";
    }else  sql = sql + " group by U.wsprinttitle+'发货单' ,U.wscontact,U.wstel,U.wsaddress,U.wsprintbk,";


        sql = sql + "  A.WsaleNtCodeStr ,  A.hdtime,A.totalamount,A.fixedprice,A.discountedprice,";
        sql = sql + " A.addcosts,  C.name  ,Z.id ,Z.name ,Z.price,Z.isbn,A.remarks,BS_WsaleNote.amount ";
       */queryA5->Close();
       queryA5->SQL->Clear();
       queryA5->SQL->Add(sql);
       queryA5->Open();

        ps = ExtractFilePath(Application->ExeName) +"wsaleA5.fr3";

        frxReportA5->LoadFromFile(ps);

        frxReportA5->PrepareReport(true);
        frxReportA5->PrintOptions->ShowDialog = false;
       frxReportA5->Print();
       // frxReportA5->ShowPreparedReport();
        }catch(...)
        {


        }

    }else //
    {


       for (int i=0; i < IDStr->Count; i++) {


            if ((IDStr->Strings[i]!="-1")&&(IDStr->Strings[i]!="")) {




                        aqmuilprinthead->Active = false;
                        aqmuilprinthead->Parameters->ParamByName("id")->Value = StrToInt(IDStr->Strings[i]);
                        aqmuilprinthead->Active = true;

                        AnsiString sql = "select  a.amount amount,b.price,b.name,a.discount discount from dbo.BS_WsaleNote a  join dbo.BS_BookCatalog b on a.bkcatalogid = b.id ";
                        sql = sql +"  where a.WsaleNtHeaderID="+aqmuilprinthead->FieldByName("id")->AsAnsiString;

                        if (pixiaoortuihuo) {
                       // sql = sql +" and a.amount >=0 ";
                        }else
                        {
                        sql = sql +" and a.amount <=0 ";
                        }
                        //sql = sql + "  group by a.BkcatalogID,b.price,b.name";
                        aqmuildetail->Close();
                        aqmuildetail->SQL->Clear();
                        aqmuildetail->SQL->Add(sql);
                        aqmuildetail->Open();

                        AnsiString psyizhang;
                        if (xiaopiao) {
                            ps = ExtractFilePath(Application->ExeName) +"wsalexiaopiao.fr3";
                        } else
                         ps = ExtractFilePath(Application->ExeName) +"wsaleA5danda.fr3";
                         psyizhang  = ExtractFilePath(Application->ExeName) +"wsaleA5dandayizhang.fr3";
                frxWsalemuilprint->LoadFromFile(ps);    //计算分页

                frxWsalemuilprint->PrepareReport(true);


                if (frxWsalemuilprint->Engine->TotalPages==1) {//如果超过1衣开始分页打印
                     frxWsalemuilprint->Clear();
                    frxWsalemuilprint->LoadFromFile(psyizhang);

                frxWsalemuilprint->PrepareReport(true);
                }
                if (type == 0) {          //
			frxWsalemuilprint->PrintOptions->ShowDialog = false;
		       	frxWsalemuilprint->Print();
                      //frxWsalemuilprint->ShowPreparedReport();
		}
		else
		{
			frxWsalemuilprint->ShowPreparedReport();
		}
            }
    }
    }
}
//---------------------------------------------------------------------------


void __fastcall Tfrmwsaleprinta::frxWsale2BeforePrint(TfrxReportComponent *Sender)

{
   TfrxCrossView * Cross;
	int i, j;
	Variant Row,Col,Text;
	AnsiString titlename;
	int totalamount = 0;
	double shiyang = 0.00,mayang = 0.00;
	Cross = dynamic_cast <TfrxCrossView *> (Sender);
	AnsiString tojiTitle[3];
	if(Cross != NULL)
	{
        Cross->Left = 0.5;
		aqdetail->First();
		i = 0;
		while (!aqdetail->Eof)
		{
			for(j = 0; j < aqdetail->Fields->Count; j++)
			{
				Row = i;
				titlename = FindTitleName(aqdetail->Fields->Fields[j]->DisplayLabel);
				if (titlename != "NOTITLE") {
					Col = titlename ;

				if (CompareText(titlename,"码洋")==0){
					Text =   FormatFloat(wsalexiaoshudian,aqdetail->Fields->Fields[j]->AsFloat );
                                       // ShowMessage(aqdetail->Fields->Fields[j]->AsAnsiString);
					tojiTitle[0]="码洋";
					mayang = mayang + aqdetail->Fields->Fields[j]->AsCurrency;

				}else if ((CompareText(titlename,"实洋")==0)) {
						Text =   FormatFloat(wsalexiaoshudian,aqdetail->Fields->Fields[j]->AsFloat);
						tojiTitle[1]="实洋";
						shiyang = shiyang + aqdetail->Fields->Fields[j]->AsFloat;
					  }
				else if (CompareText(titlename,"定价")==0) {
						Text =   FormatFloat(wsalexiaoshudian,aqdetail->Fields->Fields[j]->AsFloat);
					 }
				else if ((CompareText(titlename,"数量")==0)) {
					   Text =   aqdetail->Fields->Fields[j]->AsAnsiString ;
					   tojiTitle[2]="数量";
					   totalamount = totalamount + aqdetail->Fields->Fields[j]->AsInteger ;
					 }
				else if((CompareText(titlename,"折扣")==0)) {
						Text =   FormatFloat("00%",aqdetail->Fields->Fields[j]->AsFloat);
				}
				else{
					Text = aqdetail->Fields->Fields[j]->AsAnsiString ;
				}
					//Text = aqdetail->Fields->Fields[j]->AsAnsiString ;
                                       // Cross->Height
					Cross->AddValue(&Row, 1, &Col, 1, &Text, 1);
				}
			}
			aqdetail->Next();
			i++;
		}
    	//合计
		Row = i;
		Col = "序号";
		Text = "合计";
		Cross->AddValue(&Row, 1, &Col, 1, &Text, 1);
		for (int p = 0 ; p < 3; p++) {
			if (tojiTitle[p] != "") {
				Col = tojiTitle[p];
				if (Col == "数量") {
					Text = IntToStr(totalamount);
				}
				if (Col == "码洋") {
					Text = FormatFloat(format1,mayang);
				}
				if (Col == "实洋") {
					Text = FormatFloat(format1,shiyang);
				}
				Cross->AddValue(&Row, 1, &Col, 1, &Text, 1);
			}
		}
	}
	((TfrxMemoView *)frxWsale->FindObject("Memo22"))->DisplayFormat->FormatStr=format;

	((TfrxMemoView *)frxWsale->FindObject("Memo23"))->DisplayFormat->FormatStr=format;
	try {
		((TfrxMemoView *)frxWsale->FindObject("Memo6"))->DisplayFormat->FormatStr=format;
		((TfrxMemoView *)frxWsale->FindObject("Memo32"))->DisplayFormat->FormatStr=format;
	} catch (...) {
	}

}
 void Tfrmwsaleprinta::SetAutoSetPageLength(TfrxReport frReport)
 {





 }
 int Tfrmwsaleprinta::GetMaxHeight(int aPageIndex,TfrxReport frReport)
 {
   int i;
   TfrxView *t;
   //frReport
 /*  if(frReport.Pages[aPageIndex]->Page!=NULL)
    {
      for (int i=0; i < frReport.Pages[aPageIndex]->Page->Objects->Count-1; i++) {

        if (t->) {

        }
      }


    }      */

   //  frReport.Engine->DoublePass

 }
//---------------------------------------------------------------------------
 
double Tfrmwsaleprinta::PelsTomm(double Pels)
 {

   return Pels/Screen->PixelsPerInch*25.4;
 }
 void Tfrmwsaleprinta::PrintSerial(TfrxReport *Frx,int SequencePage)
 {
   return;//连续打印
  TfrxReportPage* P;
  double R,R1;
  if (!Frx->Engine->DoublePass) {
  //  return ;

  }
  P= (TfrxReportPage*)Frx->Pages[0];
          //P->TopMargin
      //    P->EndlessHeight
  R1= P->TopMargin +P->BottomMargin;

   while (Frx->PrepareReport())
   {
   if (Frx->Engine->TotalPages<=1) {
     break;
   }
   R= PelsTomm(Frx->Engine->TotalPages*Frx->Engine->PageHeight-Frx->Engine->FreeSpace())+R1;
   P= (TfrxReportPage*)Frx->Pages[SequencePage];
   P->PaperHeight=R;

   }
   R= PelsTomm(Frx->Engine->TotalPages*Frx->Engine->PageHeight-Frx->Engine->FreeSpace())+R1;
   P= (TfrxReportPage*)Frx->Pages[SequencePage];
   P->PaperHeight=R;
   AnsiString sql1;
  AnsiString sqldetail;



 }

//---------------------------------------------------------------------------

