//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ExcelImport.h"
#include "pdutil.h"
#include "global.h"
#include "windows.h"
#include "stdio.h"
#include <Shlobj.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzDBEdit"
#pragma link "RzDBGrid"
#pragma link "RzEdit"
#pragma link "RzPanel"
#pragma link "ModalDialog"
#pragma link "RzRadChk"
#pragma link "RzRadGrp"
#pragma link "RzShellDialogs"
#pragma link "RzPrgres"
#pragma link "RzCmboBx"
#pragma resource "*.dfm"
TfrmExcelImport *frmExcelImport;
//---------------------------------------------------------------------------
__fastcall TfrmExcelImport::TfrmExcelImport(TComponent* Owner,TADOQuery * query)
	: TfrmModalDialog(Owner)
{
   Import= true;
   dsdg = query;
   query1->Connection = query->Connection ;
   dspress->Connection = query->Connection ;
   adoinsert->Connection =  query->Connection ;
   aqinsert->Connection = query->Connection ;
}

//---------------------------------------------------------------------------
void __fastcall TfrmExcelImport::btn2Click(TObject *Sender)
{
	//
	if(edtExcelPath->Text == "")
	return;
	if (!chckbxName->Checked ) {
		ShowMsg(this->Handle,"书名必须要导入！",3);
		return;
	}
	else
	{
		if (ShowMsg(this->Handle,"确定要导入？",1) != 1) {
			return;
		}
		lblExcel->Visible = true;
		lblExcel->Caption = "导入正在进行,请稍后...";
	}
	Import= false;
        String sql;
		AnsiString insertsql;
        String str = " Provider=Microsoft.Jet.OLEDB.4.0;Extended Properties=Excel 8.0;Persist Security Info=false;Data Source=";

	str = str + edtExcelPath->Text ;

	try
	{
	      	con1->ConnectionString =  str ;

	}
	catch(...)
	{
			ShowMsg(this->Handle,"该数据已经导入！",3);
			Import = true;
			return;
	}
       	try
      {
			 con1->Connected = true;
       	}
     	catch(...)
		{
      		ShowMsg(this->Handle,"数据源配置错误！",3);
       		Import= true;
			return;
      	}
        TStringList * tablelist;
		tablelist = new TStringList();
        con1->GetTableNames(tablelist,false);
     	qry1->Connection = con1;
		  AnsiString excelsql;
          excelsql = "select * from ["+tablelist->Strings[0]+"]";
      	qry1->Active = false;
	qry1->SQL->Clear();
       	qry1->SQL ->Add(excelsql);
       	qry1->Open();
	ds1->DataSet = qry1;
        dsdg->Close();
		dsdg->SQL->Clear();
        dsdg->SQL->Add("select * from BS_BookCatalog where 1=2");
		dsdg->Active = true;
		//初始化数组
		int index;
		index = 0;
		for (int i=0; i < 25; i++) {
			InsertContent[i]="FLAGE";
			InsertTitle[i]="TITLE";
		}






	AnsiString BSID;
	dspress->Active = false;
	sql = "select ID from STK_BookstackInfo where Name = '默认库位' and stgid = " + IntToStr(fstgid) ;
	dspress->CommandText = sql;
	dspress->Active = true;
	BSID = dspress->FieldByName("ID")->AsString ;

	int j = qry1->RecordCount ;
	float percent = 0;
	qry1->DisableControls();
	TADOQuery *aq = new TADOQuery(NULL);
	aq->Connection = dspress->Connection ;
	for(int i=1;i<=j;i++)
	{
            index = 0;
            for (int i=0; i < 25; i++) {
                InsertContent[i]="FLAGE";
				InsertTitle[i]="TITLE";
            }

        bool cg = true;
		int catalogid = -2;
		String isbn =  qry1->FieldByName("ISBN")->AsString.Trim();
		isbn = StringReplace(isbn , "-","",TReplaceFlags()<<rfReplaceAll);
		sql = "select BS_BookCatalog.ID from BS_BookCatalog join BS_PressInfo on bs_pressinfo.id = bs_bookcatalog.pressid where bs_bookcatalog.Name = '" + qry1->FieldByName("书名")->AsString.Trim() + "' and bs_bookcatalog.Price = " + qry1->FieldByName("定价")->AsString + " and bs_bookcatalog.author = '" + qry1->FieldByName("作者")->AsString + "' and BS_PressInfo.AbbreviatedName = '" + qry1->FieldByName("版别")->AsString + "' and bs_bookcatalog.isbn = '" + isbn + "'";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->RecordCount > 0) {
			catalogid = aq->FieldByName("ID")->AsInteger ;
		}
		else
		{
			//书目导入
			//**********//
	      //	if (dsdg->State != dsInsert) {
		 // 	dsdg->Append();
	       	//}
                //insertsql = " insert into BS_BookCatalog(isbn,name,userdefcode,price,barcode,pressid,date,unavailable,pressdate,bigbooktypeid) values('";


		if(chckbxTypeName->Checked && qry1->FieldByName("类别")->AsString != "")
		{

				dspress->Active = false;
				sql = "select ID,Name from BS_BookType where Name = '" + qry1->FieldByName("类别")->AsString  + "'";
				dspress->CommandText = sql;
				dspress->Active = true;
				if (dspress->RecordCount == 0 ) {      //没找到类别，新建类别

                                        sql = "insert into BS_BookType(ParentID,name)values(1,'"+qry1->FieldByName("类别")->AsString+"')";
                                         dsdg->Close();
										 dsdg->SQL->Clear();
                                         dsdg->SQL->Add(sql);
                                         dsdg->SQL->Add("select @@IDENTITY as id");
                                         dsdg->Open();

                                        InsertTitle[index]="smallBookTypeID";
                                        InsertContent[index]=dsdg->FieldByName("id")->AsAnsiString ;
                                        index++;
				}
				else
				{
                                        InsertTitle[index]="smallBookTypeID";
										InsertContent[index]=dspress->FieldByName("ID")->AsAnsiString;;
                                        index++;

				}

		}

		if(chckbxBarcode->Checked )
		{
			String barcode = qry1->FieldByName("条码")->AsString.Trim() ;
			barcode = StringReplace(barcode , "-","",TReplaceFlags()<<rfReplaceAll);
                        InsertTitle[index]="Barcode";
						InsertContent[index]=barcode;
                       // index++;
		}

		if(chckbxISBN->Checked )
		{

                        InsertTitle[index]="ISBN";
						InsertContent[index]=isbn;
                      //  index++;


		}

                 if (chckbxISBN->Checked&&chckbxBarcode->Checked ) {

					String barcode = qry1->FieldByName("条码")->AsString.Trim() ;
			barcode = StringReplace(barcode , "-","",TReplaceFlags()<<rfReplaceAll);
                        InsertTitle[index]="Barcode";
                        InsertContent[index]=barcode;
						index++ ;
                        InsertTitle[index]="ISBN";
                        InsertContent[index]=isbn;



                 }




		if(!chckbxBarcode->Checked )
		if(chckbxISBN->Checked )
		{
			if (isbn != "") {
				try {
									isbn = ISBNToBarcode(isbn.Trim());

                                        InsertTitle[index]="ISBN";
                                        InsertContent[index]=isbn;
										barcode1 = isbn;
				} catch (...) {
				}
			}
		}

		if(!chckbxISBN->Checked )
		if(chckbxBarcode->Checked )
		{
			String barcode = qry1->FieldByName("条码")->AsString.Trim()  ;
			barcode = StringReplace(barcode , "-","",TReplaceFlags()<<rfReplaceAll);

			if (barcode != "") {
				try {
                                        barcode = BuildISBNCode(barcode);
					InsertTitle[index]="Barcode";
										InsertContent[index]=barcode;
				} catch (...) {
				}
			}
		}
                 index++;
		if(chckbxName->Checked )
		{

                        InsertTitle[index]="Name";
                        InsertContent[index]=qry1->FieldByName("书名")->AsString.Trim();
                        index++;
		}

		if(chckbxAuthor->Checked )
		{

                         InsertTitle[index]="Author";
                        InsertContent[index]=qry1->FieldByName("作者")->AsString.Trim();
                        index++;
		}

		if(chckbxUserDefCode->Checked && qry1->FieldByName("自编号")->AsString != "")
		{

                        InsertTitle[index]="UserDefCode";
                        InsertContent[index]=qry1->FieldByName("自编号")->AsString.Trim();
                        index++;

		}
		else
		{
			char* t;
			AnsiString t2;
			String t1,t3,t4;
			t1 = qry1->FieldByName("书名")->AsString;//.TrimLeft().TrimLeft()  ;//.TrimRight();//  .TrimLeft()  ;


			int t5=1,i =qry1->FieldByName("书名")->AsString.Length() ;
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
                        t41 =t4;
						 InsertTitle[index]="UserDefCode";
                        InsertContent[index]=t4;
                        index++;

		}

		if(chckbxDate->Checked )
		{
			try {
                         InsertTitle[index]="Pressdate";
                        InsertContent[index]=qry1->FieldByName("出版日期")->AsString ;
                        index++;

			} catch (...) {
			}
		}
		if(chckbxPrice->Checked )
		{
			try {
                        InsertTitle[index]="Price";
						InsertContent[index]=qry1->FieldByName("定价")->AsString ;
                        index++;

			} catch (...) {
			}
		}

		if(chhuojiangstate->Checked )
		{
			try {
                         InsertTitle[index]="huojiangstate";
                        InsertContent[index]=qry1->FieldByName("获奖情况")->AsString ;
						index++;

			} catch (...) {
			}
		}

		if(chbaoce->Checked )
		{
			try {
				if (qry1->FieldByName("包/册")->AsString == "") {

                                        InsertTitle[index]="BookWords";
										InsertContent[index]="1" ;
                                        index++;
				}
				else
				{

                                        InsertTitle[index]="BookWords";
                                        InsertContent[index]=qry1->FieldByName("包/册")->AsString ;;
										index++;
				}
			} catch (...) {
			}
		}

		if(chckbxPress->Checked )
		{
			dspress->Active = false;
			AnsiString press = qry1->FieldByName("版别")->AsString.Trim();
			if (press != "") {
				sql = "select ID,PresentNum from BS_PressInfo where AbbreviatedName = '" + qry1->FieldByName("版别")->AsString.Trim()  + "'";
				dspress->CommandText = sql;
				dspress->Active = true;
				if (dspress->FieldByName("PresentNum")->AsString != ""  ) {

										InsertTitle[index]="PressID";
                                        InsertContent[index]=dspress->FieldByName("ID")->AsInteger;
                                        index++;
				}
			}
		}
                if (cbbanchi->Checked) {   //版次
                    InsertTitle[index]="PressCount";
					InsertContent[index]= qry1->FieldByName("版次")->AsString;
                    index++;
                }
                 if (cbisbnfenlei->Checked) {   //ISBN分类
					InsertTitle[index]="ISBNType";
                    InsertContent[index]= qry1->FieldByName("ISBN分类")->AsString;
                    index++;
                }
				 if (cbyeze->Checked) {   //译者
                    InsertTitle[index]="Yizhe";
                    InsertContent[index]= qry1->FieldByName("译者")->AsString;
                    index++;
				}
                 if (cbprintcount->Checked) {   //印次
                    InsertTitle[index]="Printcount";
                    InsertContent[index]= qry1->FieldByName("印次")->AsString;
					index++;
                }
                 if (cbkaiben->Checked) {   //开本
                    InsertTitle[index]="Bookformat";
					InsertContent[index]= qry1->FieldByName("开本")->AsString;
                    index++;
                }
				 if (cbzhuangzeng->Checked) {   //装帧
                    InsertTitle[index]="Bind";
                    InsertContent[index]= qry1->FieldByName("装帧")->AsString;
					index++;
                }
				if (cbchongshu->Checked) {   //丛书
                    InsertTitle[index]="Collectbook";
					InsertContent[index]= qry1->FieldByName("丛书")->AsString;
                    index++;
				}
                if (cbwordcount->Checked) {   //字数
                    InsertTitle[index]="wordscount";
					InsertContent[index]= qry1->FieldByName("字数")->AsString;
                    index++;
                }
                if (cbprintzhang->Checked) {   //印张
					InsertTitle[index]="yinzhang";
                    InsertContent[index]= qry1->FieldByName("印张")->AsString;
                    index++;
                }
				if (cbleirong->Checked) {   //版次
                    InsertTitle[index]="bcontent";
                    InsertContent[index]= qry1->FieldByName("内容简介")->AsString;
                    index++;
				}


		try {


                   if (barcode1.Length()>13) {

					  barcode1=barcode1.SubString(1,13);
                   }
                   AnsiString insertsql;
                   insertsql = "INSERT INTO BS_BookCatalog(";
				   for (int i=0 ; i < 25; i++) {
                      if (InsertTitle[i]!="TITLE") {
                         insertsql=insertsql+InsertTitle[i].Trim()+",";
                      }

                   }
                      insertsql=insertsql.Delete(insertsql.Length(),1);//取掉最后一个逗号
                    insertsql =insertsql+")values('";
				   for (int i=0 ; i < 25; i++) {
                      if (InsertContent[i]!="FLAGE") {
                         insertsql=insertsql+InsertContent[i].Trim()+"','";
                      }

                   }
                     insertsql=insertsql.Delete(insertsql.Length()-1,2);
                     insertsql=insertsql+")";

             aqinsert->Close();
             aqinsert->SQL->Clear();
             aqinsert->SQL->Add(insertsql);
			 aqinsert->ExecSQL();

                                 //arAll  arCurrent
			//dsdg->UpdateBatch(arAll);
					   // dsdg->Post();
		} catch (...) {
			try {
				cg = false;
				   //	vExcelApp.OlePropertyGet("Cells",2+i,1).OlePropertySet("Value","添加书目信息出错" );
			} catch (...) {
			}
		}

	     //	dsdg->Append();

                }
			  //  qry1->Next();
        //***************//

		if (chckbxTotalAmount->Checked && cg) {
			AnsiString BCID,SPID;
			//STK_BookInfo的BkcatalogID
			if (catalogid > -2) {
				BCID = IntToStr(catalogid);
			}
			else
			{
            	dspress->Active = false;
				sql = "select max(id) as ID from BS_BookCatalog ";
				dspress->CommandText = sql;
				dspress->Active = true;
				BCID = dspress->FieldByName("ID")->AsString ;
			}

			dspress->Active = false;
			if (checkbsupplier->Checked ) {
				try {
					sql = "select ID from CUST_CustomerInfo where Name = '" + qry1->FieldByName("供应商")->AsString + "' and Type = 1";
				} catch (...) {
					sql = "select ID from CUST_CustomerInfo where Name = '" + cbsupplier->Text + "' and Type = 1";
				}
			}
			else
			{
							sql = "select ID from CUST_CustomerInfo where Name = '" + cbsupplier->Text + "' and Type = 1";
			}

			dspress->CommandText = sql;
			dspress->Active = true;
			SPID = dspress->FieldByName("ID")->AsString ;
                        if (SPID.IsEmpty()) {
                              AnsiString sqlll;
							  sqlll = "insert into CUST_CustomerInfo(name,type)values('"+qry1->FieldByName("供应商")->AsString+"',1)";
                            // dspress->Active = false;
                            // dspress->CommandText = sqlll;

							 TADOQuery *aq= new TADOQuery(Application);
                             aq->Connection = adoinsert->Connection ;
                             aq->Close();
                             aq->SQL->Clear();
							 aq->SQL->Add(sqlll);
                             aq->ExecSQL();




                               AnsiString sqlr = "select ID from CUST_CustomerInfo where Name = '" + qry1->FieldByName("供应商")->AsString + "' and Type = 1";
                               aq->Close();
							 aq->SQL->Clear();
                             aq->SQL->Add(sqlr);
                             aq->Open();
                             SPID = aq->FieldByName("ID")->AsString ;
							 delete aq;
                        }
			AnsiString totalamount = qry1->FieldByName("库存")->AsString ;
			if (totalamount != "") {
				int amount;
				try {
					amount = qry1->FieldByName("库存")->AsInteger ;
				} catch (...) {
				}

				if (amount < 0) {
					totalamount = "0";
				}
			}
			else
			{
				totalamount = "0" ;
			}
			sql = "insert into STK_BookInfo (Amount,BkcatalogID,BkstackID,SupplierID,stgid) values ("+totalamount + "," + BCID + "," + BSID + "," + SPID + "," + IntToStr(fstgid) + ")";
			query1->Close();
			query1->SQL->Clear();
			query1->SQL->Add(sql);
			query1->ExecSQL();
		}
		qry1->RecNo ++;
	}
	delete aq;
	qry1->EnableControls();
	lblExcel->Caption = "EXCEL导入完毕！";
	ShowMsg(this->Handle,"数据导入成功！",3);
	Import= true;

	   //	Wb.OleProcedure("Close");
	con1->Connected =false;
	  //	vExcelApp.OleProcedure("Quit");
	  //	vExcelApp = Unassigned;

	this->Close();
}
void TfrmExcelImport::delallfile(char *Path)
{
	char file[MAX_PATH];
	String filepathstr;
	lstrcpy(file,Path);
	lstrcat(file,"\\*.*");
	WIN32_FIND_DATA wfd;
	HANDLE Find = FindFirstFile(file,&wfd);
	if (Find == INVALID_HANDLE_VALUE)
		return;

	while (FindNextFile(Find, &wfd))
	{
		if (wfd.cFileName[0] == '.')
		{
			continue;
		}
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			char szFindPath[MAX_PATH];
			lstrcpy(szFindPath,Path);
			lstrcat(szFindPath,"\\");
			lstrcat(szFindPath,wfd.cFileName);
			delallfile(szFindPath);
		}

		char FilePath[MAX_PATH];
		lstrcpy(FilePath,Path);
		lstrcat(FilePath,"\\");
		lstrcat(FilePath,wfd.cFileName);
	  //	printf("%s\r\n",FilePath);
	  filepathstr= FilePath;
		 AlistPaht->Add(filepathstr);

		//DeleteFile(FilePath);
                //这里写上你要执行的操作
	}
	FindClose(Find);





}
void TfrmExcelImport::GmsInput()
{

	if(edtExcelPath->Text == "")
	return;
	AlistPaht=new TStringList();
	delallfile(edtExcelPath->Text.t_str());
	if (!chckbxName->Checked ) {
		ShowMsg(this->Handle,"书名必须要导入！",3);
		return;
	}
	else
	{
		if (ShowMsg(this->Handle,"确定要导入？",1) != 1) {
			return;
		}
		lblExcel->Visible = true;
		lblExcel->Caption = "导入正在进行,请稍后...";
	}

  for (int ip=0; ip < AlistPaht->Count; ip++) {




	Import= false;
		String sql;
		AnsiString insertsql;
        String str = " Provider=Microsoft.Jet.OLEDB.4.0;Extended Properties=Excel 8.0;Persist Security Info=false;Data Source=";
	//枚举所有的文件
	str = str + AlistPaht->Strings[ip] ;

	 SupplierName= ExtractFileName(AlistPaht->Strings[ip]);
	 SupplierName=ChangeFileExt(SupplierName,"");
	try
	{
			con1->ConnectionString =  str ;

	}
	catch(...)
	{
			ShowMsg(this->Handle,"该数据已经导入！",3);
			Import = true;
			return;
	}
       	try
      {
			 con1->Connected = true;
       	}
     	catch(...)
		{
      		ShowMsg(this->Handle,"数据源配置错误！",3);
       		Import= true;
			return;
      	}
        TStringList * tablelist;
		tablelist = new TStringList();
        con1->GetTableNames(tablelist,false);
     	qry1->Connection = con1;
		  AnsiString excelsql;
          excelsql = "select * from ["+tablelist->Strings[0]+"]";
		qry1->Active = false;
		qry1->Close();
	qry1->SQL->Clear();
       	qry1->SQL ->Add(excelsql);
       	qry1->Open();
	ds1->DataSet = qry1;
        dsdg->Close();
		dsdg->SQL->Clear();
		dsdg->SQL->Add("select * from BS_BookCatalog where 1=2");
		dsdg->Active = true;
		//初始化数组
		int index;
		index = 0;
		for (int i=0; i < 25; i++) {
			InsertContent[i]="FLAGE";
			InsertTitle[i]="TITLE";
		}






	AnsiString BSID;
	dspress->Active = false;
	sql = "select ID from STK_BookstackInfo where Name = '默认库位' and stgid = " + IntToStr(fstgid) ;
	dspress->CommandText = sql;
	dspress->Active = true;
	BSID = dspress->FieldByName("ID")->AsString ;

	int j = qry1->RecordCount ;
	float percent = 0;
	qry1->DisableControls();
	TADOQuery *aq = new TADOQuery(NULL);
	aq->Connection = dspress->Connection ;
	for(int i=1;i<=j;i++)
	{
            index = 0;
            for (int i=0; i < 25; i++) {
                InsertContent[i]="FLAGE";
				InsertTitle[i]="TITLE";
            }

        bool cg = true;
		int catalogid = -2;
		String isbn =  qry1->FieldByName("ISBN")->AsString.Trim();
		isbn = StringReplace(isbn , "-","",TReplaceFlags()<<rfReplaceAll);
		sql = "select BS_BookCatalog.ID from BS_BookCatalog join BS_PressInfo on bs_pressinfo.id = bs_bookcatalog.pressid where bs_bookcatalog.Name = '" + qry1->FieldByName("书名")->AsString.Trim() + "' and bs_bookcatalog.Price = " + qry1->FieldByName("定价")->AsString + " and bs_bookcatalog.author = '" + qry1->FieldByName("作者")->AsString + "' and BS_PressInfo.Fullname = '" + qry1->FieldByName("版别")->AsString + "' and bs_bookcatalog.isbn = '" + isbn + "'";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
		if (aq->RecordCount > 0) {
			catalogid = aq->FieldByName("ID")->AsInteger ;
		}
		else
		{
			//书目导入
			//**********//
	      //	if (dsdg->State != dsInsert) {
		 // 	dsdg->Append();
	       	//}
                //insertsql = " insert into BS_BookCatalog(isbn,name,userdefcode,price,barcode,pressid,date,unavailable,pressdate,bigbooktypeid) values('";


		if(chckbxTypeName->Checked && qry1->FieldByName("类别")->AsString != "")
		{

				dspress->Active = false;
				sql = "select ID,Name from BS_BookType where Name = '" + qry1->FieldByName("类别")->AsString  + "'";
				dspress->CommandText = sql;
				dspress->Active = true;
				if (dspress->RecordCount == 0 ) {      //没找到类别，新建类别

                                        sql = "insert into BS_BookType(ParentID,name)values(1,'"+qry1->FieldByName("类别")->AsString+"')";
                                         dsdg->Close();
										 dsdg->SQL->Clear();
                                         dsdg->SQL->Add(sql);
                                         dsdg->SQL->Add("select @@IDENTITY as id");
                                         dsdg->Open();

                                        InsertTitle[index]="smallBookTypeID";
                                        InsertContent[index]=dsdg->FieldByName("id")->AsAnsiString ;
                                        index++;
				}
				else
				{
                                        InsertTitle[index]="smallBookTypeID";
										InsertContent[index]=dspress->FieldByName("ID")->AsAnsiString;;
                                        index++;

				}

		}

		if(chckbxBarcode->Checked )
		{
			String barcode = qry1->FieldByName("条码")->AsString.Trim() ;
			barcode = StringReplace(barcode , "-","",TReplaceFlags()<<rfReplaceAll);
                        InsertTitle[index]="Barcode";
						InsertContent[index]=barcode;
                       // index++;
		}

		if(chckbxISBN->Checked )
		{

						InsertTitle[index]="ISBN";
						InsertContent[index]=isbn;
                      //  index++;


		}

                 if (chckbxISBN->Checked&&chckbxBarcode->Checked ) {

					String barcode = qry1->FieldByName("条码")->AsString.Trim() ;
			barcode = StringReplace(barcode , "-","",TReplaceFlags()<<rfReplaceAll);
                        InsertTitle[index]="Barcode";
                        InsertContent[index]=barcode;
						index++ ;
                        InsertTitle[index]="ISBN";
                        InsertContent[index]=isbn;



                 }




		if(!chckbxBarcode->Checked )
		if(chckbxISBN->Checked )
		{
			if (isbn != "") {
				try {
									isbn = ISBNToBarcode(isbn.Trim());

                                        InsertTitle[index]="ISBN";
										InsertContent[index]=isbn;
										barcode1 = isbn;
				} catch (...) {
				}
			}
		}

		if(!chckbxISBN->Checked )
		if(chckbxBarcode->Checked )
		{
			String barcode = qry1->FieldByName("条码")->AsString.Trim()  ;
			barcode = StringReplace(barcode , "-","",TReplaceFlags()<<rfReplaceAll);

			if (barcode != "") {
				try {
                                        barcode = BuildISBNCode(barcode);
					InsertTitle[index]="Barcode";
										InsertContent[index]=barcode;
				} catch (...) {
				}
			}
		}
                 index++;
		if(chckbxName->Checked )
		{

                        InsertTitle[index]="Name";
                        InsertContent[index]=qry1->FieldByName("书名")->AsString.Trim();
                        index++;
		}

		if(chckbxAuthor->Checked )
		{

                         InsertTitle[index]="Author";
                        InsertContent[index]=qry1->FieldByName("作者")->AsString.Trim();
                        index++;
		}

		if(chckbxUserDefCode->Checked && qry1->FieldByName("自编号")->AsString != "")
		{

                        InsertTitle[index]="UserDefCode";
                        InsertContent[index]=qry1->FieldByName("自编号")->AsString.Trim();
						index++;

		}
		else
		{
			char* t;
			AnsiString t2;
			String t1,t3,t4;
			t1 = qry1->FieldByName("书名")->AsString;//.TrimLeft().TrimLeft()  ;//.TrimRight();//  .TrimLeft()  ;


			int t5=1,i =qry1->FieldByName("书名")->AsString.Length() ;
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
                        t41 =t4;
						 InsertTitle[index]="UserDefCode";
                        InsertContent[index]=t4;
                        index++;

		}

		if(chckbxDate->Checked )
		{
			try {
                         InsertTitle[index]="Pressdate";
						InsertContent[index]=qry1->FieldByName("出版时间")->AsString ;
                        index++;

			} catch (...) {
			}
		}
		if(chckbxPrice->Checked )
		{
			try {
                        InsertTitle[index]="Price";
						InsertContent[index]=qry1->FieldByName("定价")->AsString ;
                        index++;

			} catch (...) {
			}
		}

		if(chhuojiangstate->Checked )
		{
			try {
                         InsertTitle[index]="huojiangstate";
                        InsertContent[index]=qry1->FieldByName("获奖情况")->AsString ;
						index++;

			} catch (...) {
			}
		}

		if(chbaoce->Checked )
		{
			try {
				if (qry1->FieldByName("包/册")->AsString == "") {

                                        InsertTitle[index]="BookWords";
										InsertContent[index]="1" ;
                                        index++;
				}
				else
				{

                                        InsertTitle[index]="BookWords";
                                        InsertContent[index]=qry1->FieldByName("包/册")->AsString ;;
										index++;
				}
			} catch (...) {
			}
		}

		if(chckbxPress->Checked )
		{
			dspress->Active = false;
			AnsiString press = qry1->FieldByName("版别")->AsString.Trim();
			if (press != "") {
				sql = "select ID,PresentNum from BS_PressInfo where Fullname = '" + qry1->FieldByName("版别")->AsString.Trim()  + "'";
				dspress->CommandText = sql;
				dspress->Active = true;
				if (dspress->FieldByName("PresentNum")->AsString != ""  ) {

										InsertTitle[index]="PressID";
                                        InsertContent[index]=dspress->FieldByName("ID")->AsInteger;
                                        index++;
				}
			}
		}
                if (cbbanchi->Checked) {   //版次
                    InsertTitle[index]="PressCount";
					InsertContent[index]= qry1->FieldByName("版次")->AsString;
                    index++;
                }
                 if (cbisbnfenlei->Checked) {   //ISBN分类
					InsertTitle[index]="ISBNType";
					InsertContent[index]= qry1->FieldByName("ISBN分类")->AsString;
                    index++;
                }
				 if (cbyeze->Checked) {   //译者
                    InsertTitle[index]="Yizhe";
                    InsertContent[index]= qry1->FieldByName("译者")->AsString;
                    index++;
				}
                 if (cbprintcount->Checked) {   //印次
                    InsertTitle[index]="Printcount";
                    InsertContent[index]= qry1->FieldByName("印次")->AsString;
					index++;
                }
                 if (cbkaiben->Checked) {   //开本
                    InsertTitle[index]="Bookformat";
					InsertContent[index]= qry1->FieldByName("开本")->AsString;
                    index++;
                }
				 if (cbzhuangzeng->Checked) {   //装帧
                    InsertTitle[index]="Bind";
                    InsertContent[index]= qry1->FieldByName("装帧")->AsString;
					index++;
                }
				if (cbchongshu->Checked) {   //丛书
                    InsertTitle[index]="Collectbook";
					InsertContent[index]= qry1->FieldByName("丛书")->AsString;
                    index++;
				}
                if (cbwordcount->Checked) {   //字数
                    InsertTitle[index]="wordscount";
					InsertContent[index]= qry1->FieldByName("字数")->AsString;
                    index++;
                }
                if (cbprintzhang->Checked) {   //印张
					InsertTitle[index]="yinzhang";
                    InsertContent[index]= qry1->FieldByName("印张")->AsString;
                    index++;
                }
				if (cbleirong->Checked) {   //版次
                    InsertTitle[index]="bcontent";
                    InsertContent[index]= qry1->FieldByName("内容简介")->AsString;
                    index++;
				}


		try {


                   if (barcode1.Length()>13) {

					  barcode1=barcode1.SubString(1,13);
                   }
                   AnsiString insertsql;
                   insertsql = "INSERT INTO BS_BookCatalog(";
				   for (int i=0 ; i < 25; i++) {
                      if (InsertTitle[i]!="TITLE") {
                         insertsql=insertsql+InsertTitle[i].Trim()+",";
                      }

                   }
                      insertsql=insertsql.Delete(insertsql.Length(),1);//取掉最后一个逗号
                    insertsql =insertsql+")values('";
				   for (int i=0 ; i < 25; i++) {
                      if (InsertContent[i]!="FLAGE") {
                         insertsql=insertsql+InsertContent[i].Trim()+"','";
                      }

                   }
                     insertsql=insertsql.Delete(insertsql.Length()-1,2);
                     insertsql=insertsql+")";

             aqinsert->Close();
             aqinsert->SQL->Clear();
             aqinsert->SQL->Add(insertsql);
			 aqinsert->ExecSQL();

                                 //arAll  arCurrent
			//dsdg->UpdateBatch(arAll);
					   // dsdg->Post();
		} catch (...) {
			try {
				cg = false;
				   //	vExcelApp.OlePropertyGet("Cells",2+i,1).OlePropertySet("Value","添加书目信息出错" );
			} catch (...) {
			}
		}

	     //	dsdg->Append();

                }
			  //  qry1->Next();
        //***************//

		if (chckbxTotalAmount->Checked && cg) {
			AnsiString BCID,SPID;
			//STK_BookInfo的BkcatalogID
			if (catalogid > -2) {
				BCID = IntToStr(catalogid);
			}
			else
			{
            	dspress->Active = false;
				sql = "select max(id) as ID from BS_BookCatalog ";
				dspress->CommandText = sql;
				dspress->Active = true;
				BCID = dspress->FieldByName("ID")->AsString ;
			}

			dspress->Active = false;
			if (checkbsupplier->Checked ) {
				try {                                                             //qry1->FieldByName("供应商")->AsString
					sql = "select ID from CUST_CustomerInfo where Name = '" + SupplierName + "' and Type = 1";
				} catch (...) {
					sql = "select ID from CUST_CustomerInfo where Name = '" + cbsupplier->Text + "' and Type = 1";
				}
			}
			else
			{
							sql = "select ID from CUST_CustomerInfo where Name = '" + cbsupplier->Text + "' and Type = 1";
			}

			dspress->CommandText = sql;
			dspress->Active = true;
			SPID = dspress->FieldByName("ID")->AsString ;
						if (SPID.IsEmpty()) {                                            //  qry1->FieldByName("供应商")->AsString
                              AnsiString sqlll;
							  sqlll = "insert into CUST_CustomerInfo(name,type)values('"+SupplierName+"',1)";
                            // dspress->Active = false;
                            // dspress->CommandText = sqlll;

							 TADOQuery *aq= new TADOQuery(Application);
                             aq->Connection = adoinsert->Connection ;
                             aq->Close();
                             aq->SQL->Clear();
							 aq->SQL->Add(sqlll);
                             aq->ExecSQL();




							   AnsiString sqlr = "select ID from CUST_CustomerInfo where Name = '" + SupplierName + "' and Type = 1";
                               aq->Close();
							 aq->SQL->Clear();
                             aq->SQL->Add(sqlr);
                             aq->Open();
                             SPID = aq->FieldByName("ID")->AsString ;
							 delete aq;
                        }
			AnsiString totalamount = qry1->FieldByName("库存")->AsString ;
			if (totalamount != "") {
				int amount;
				try {
					amount = qry1->FieldByName("库存")->AsInteger ;
				} catch (...) {
				}

				if (amount < 0) {
					totalamount = "0";
				}
			}
			else
			{
				totalamount = "0" ;
			}
			sql = "insert into STK_BookInfo (Amount,BkcatalogID,BkstackID,SupplierID,stgid) values ("+totalamount + "," + BCID + "," + BSID + "," + SPID + "," + IntToStr(fstgid) + ")";
			query1->Close();
			query1->SQL->Clear();
			query1->SQL->Add(sql);
			query1->ExecSQL();
		}
		qry1->RecNo ++;
	}
	delete aq;
	qry1->EnableControls();
   	DeleteFile(AlistPaht->Strings[ip]);
  con1->Connected =false;
}//for 循环
	lblExcel->Caption = "EXCEL导入完毕！";
	ShowMsg(this->Handle,"数据导入成功！",3);
	Import= true;

	   //	Wb.OleProcedure("Close");
   //	con1->Connected =false;
	  //	vExcelApp.OleProcedure("Quit");
	  //	vExcelApp = Unassigned;

	this->Close();




}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void TfrmExcelImport::Init(TApplication* app, TADOConnection* con,int stgid)
{
	TfrmModalDialog::Init(app, con);
	dset1->Connection = m_con;

	fstgid = stgid;
}


void __fastcall TfrmExcelImport::spselectpathClick(TObject *Sender)
{
	if (opndlgExcelPath->Execute())
	{
		String DBPath,Name;
		DBPath = ExtractFilePath(opndlgExcelPath->FileName .c_str()  );
		Name = ExtractFileName(opndlgExcelPath->FileName .c_str() );
		DBPath = DBPath + Name;
		edtExcelPath->Text = DBPath;
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmExcelImport::BtnImportClick(TObject *Sender)
{
	//btn2->Click();
	GmsInput();
}
//---------------------------------------------------------------------------


void __fastcall TfrmExcelImport::BtnExitClick(TObject *Sender)
{
	if (Import) {
		Close();
	}else
	{
		ShowMsg(this->Handle,"正在导入中，不能退出！",3);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmExcelImport::chckbxTotalAmountClick(TObject *Sender)
{
	if (chckbxTotalAmount->Checked ) {
		checkbsupplier->Enabled = true;
		cbsupplier->Enabled = true;
	}
	else
	{
		checkbsupplier->Enabled = false;
		cbsupplier->Enabled = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmExcelImport::FormShow(TObject *Sender)
{
	AnsiString sql;
	sql = "select Name from CUST_CustomerInfo where customerstate=1 and Type = 1 and stgid="+IntToStr(fstgid);
	dspress->Active = false;
	dspress->CommandText = sql;
	dspress->Active = true;
	while (!dspress->Eof)
	{
		cbsupplier->Add(dspress->FieldByName("Name")->AsString );
		dspress->Next();
	}
	cbsupplier->ItemIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmExcelImport::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_F7) {     //导入
		BtnImport->Click();
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

void __fastcall TfrmExcelImport::BtnAlignBottomClick(TObject *Sender)
{
	WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

