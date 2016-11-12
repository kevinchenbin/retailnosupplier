//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitwsalehuizhongsearch.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "RzDBGrid"
#pragma link "frxClass"
#pragma link "frxDBSet"
#pragma link "RzEdit"
#pragma resource "*.dfm"
Tfrmwsalehuizhong *frmwsalehuizhong;
//---------------------------------------------------------------------------
__fastcall Tfrmwsalehuizhong::Tfrmwsalehuizhong(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall Tfrmwsalehuizhong::tlbtn8Click(TObject *Sender)
{
  //查询
  AnsiString sql,totalsql;
  sql = " select RANK() OVER(order by bookname,price,barcode,abbreviatedname ) as xuhao,";
  sql = sql +" sum(amount) as amount,sum(fixedprice) as FixedPrice,sum(DiscountedPrice) as DiscountedPrice,";
  sql = sql +" cast(sum(discountedprice)/sum(fixedprice)*100 as nvarchar(100))+'%' as avgdiscount,bookname,userdefcode,price,barcode,presscount,abbreviatedname ";
   sql = sql +"  from Qry_WsaleHuiZhongQuery where fixedprice <>0 and amount >0 ";


    if (cbruku->Checked ) {

            sql = sql + " and datediff(day,'" + FormatDateTime("yyyy-mm-dd",dtpstart->DateTime)+ "',HdTime) >= 0";

            sql = sql + " and datediff(day,'" + FormatDateTime("yyyy-mm-dd",dtpend->DateTime) + "',HdTime) <= 0";
    }
    if ((cbfahuofanshi->Checked)&&(cbfahuo->Text!="")){
        sql = sql +" and remarks like '%"+cbfahuo->Text+"%' ";
    }

    if ((cbstag->Checked)&&(cbstgcheck->Text!="")) {
                 sql =sql+" and stgid="+IntToStr((int)(cbstgcheck->Items->Objects[cbstgcheck->ItemIndex]));
    }

    if ((cbfahuotuihuo->Checked)&&(cbfahuocheck->Checked)) {

    }else
    {
        if (cbfahuocheck->Checked) {
           sql = sql +" and WsaleNtCodeInt>0";
        }
        if (cbfahuotuihuo->Checked) {
          sql = sql +" and TWsaleNtCodeInt>0";
        }
    }

   sql = sql +" group by bookname,userdefcode,price,barcode,presscount,abbreviatedname ";
    aqdetail->Close();
    aqdetail->SQL->Clear();
    aqdetail->SQL->Add(sql);
    aqdetail->Open();
dbgrid1->DataSource->DataSet->DisableControls();
totalamount=0;
   totaldis=0;
    totalfix=0;
   while(!aqdetail->Eof)
   {
    totalamount=totalamount+aqdetail->FieldByName("Amount")->AsInteger ;
    totaldis=totaldis+aqdetail->FieldByName("DiscountedPrice")->AsFloat ;
    totalfix=totalfix+aqdetail->FieldByName("FixedPrice")->AsFloat ;
    aqdetail->Next();
   }

   dbgrid1->DataSource->DataSet->EnableControls();
   aqdetail->First();
    GetTotal();

}
void Tfrmwsalehuizhong::init(LandInfo* li)
{

     	UserID = li->userID ;
	StgID = li->storageID ;
        linfo.app = li->app ;
        linfo.con = li->con ;
        fcn =  li->con ;
        linfo.userID = li->userID ;
        linfo.UserName = li->UserName ;
        linfo.storageID = li->storageID ;
        linfo.FormatStr = li->FormatStr ;
        username=li->UserName;
    aqdetail->Connection =fcn;
    aqhead->Connection =fcn;

    dtpend->DateTime = Now();
    dtpstart->DateTime = Now();

    TADOQuery * aq = new TADOQuery(Application);
    aq->Connection = fcn;
    aq->Close();
    aq->SQL->Add("select id,name from dbo.SYS_StorageInfo");
    aq->Open();
    while (!aq->Eof)
        {

        if (linfo.storageID==aq->FieldByName("id")->AsInteger) {
           stgname= aq->FieldByName("name")->AsAnsiString;
        }
        cbstgcheck->AddItem(aq->FieldByName("name")->AsAnsiString,(TObject*)aq->FieldByName("id")->AsInteger);

        aq->Next();
        }
        cbstgcheck->ItemIndex=0;
       
   delete aq;



}
//---------------------------------------------------------------------------
void __fastcall Tfrmwsalehuizhong::cbstgcheckChange(TObject *Sender)
{
  if (cbstgcheck->Text !="") {
   cbstag->Checked = true;
  }

}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsalehuizhong::cbfahuoChange(TObject *Sender)
{
 if (cbfahuo->Text !="") {
   cbfahuofanshi->Checked = true;
 }

}
//---------------------------------------------------------------------------
void __fastcall Tfrmwsalehuizhong::dtpstartChange(TObject *Sender)
{
  cbruku->Checked = true;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmwsalehuizhong::frxhuizhongGetValue(const UnicodeString VarName,
          Variant &Value)
{
      //
      	if (CompareText(VarName,"\"Title\"")==0 ) {   //出版日期
		Value = stgname+"批销汇总单";
	}
        	if (CompareText(VarName,"\"riqi\"")==0 ) {   //出版日期
		Value = "日期: "+FormatDateTime("yyyy-mm-dd",dtpstart->DateTime)+"到"+FormatDateTime("yyyy-mm-dd",dtpend->DateTime);
	}
        
        	if (CompareText(VarName,"\"user\"")==0 ) {   //出版日期
		Value = "操作员: "+username;
	}
}
void Tfrmwsalehuizhong::print(int type)
{
        AnsiString ps;
        ps = ExtractFilePath(Application->ExeName) +"pixiaohuizhong.fr3";


        frxhuizhong->LoadFromFile(ps);
        frxhuizhong->PrepareReport(true);
        if (type == 0) {          //
            frxhuizhong->PrintOptions->ShowDialog = false;
            frxhuizhong->Print();
        }
        else
        {
            frxhuizhong->ShowPreparedReport();
        }


}
//---------------------------------------------------------------------------
void __fastcall Tfrmwsalehuizhong::RzToolButton1Click(TObject *Sender)
{
 if (!aqdetail->Active) {
    return;
 }
dbgrid1->DataSource->DataSet->DisableControls();
print(0);
 dbgrid1->DataSource->DataSet->EnableControls();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsalehuizhong::RzToolButton2Click(TObject *Sender)
{
 if (!aqdetail->Active) {
    return;
 }
 dbgrid1->DataSource->DataSet->DisableControls();
print(1);
 dbgrid1->DataSource->DataSet->EnableControls();
}
//---------------------------------------------------------------------------
void __fastcall Tfrmwsalehuizhong::BtnAlignBottomClick(TObject *Sender)
{
      WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmwsalehuizhong::tlbtn7Click(TObject *Sender)
{
 Close();
 HANDLE hWindow = FindWindow("TfrmMain",NULL);
        SendMessage(hWindow ,WM_MYMESSAGE,0,0);
}
//---------------------------------------------------------------------------
void __fastcall Tfrmwsalehuizhong::FormClose(TObject *Sender, TCloseAction &Action)

{                      Action=caFree;

}

void Tfrmwsalehuizhong::GetTotal()
{


        RzNumericEdit1->Value = totalamount;
         RzNumericEdit2->Value  =  totalfix;
          RzNumericEdit3->Value  = totaldis;

}
//---------------------------------------------------------------------------
void __fastcall Tfrmwsalehuizhong::BtnNewClick(TObject *Sender)
{
 if (!aqdetail->Active) {
    return;
 }

   	if (aqdetail->Active && aqdetail->RecordCount >= 1)
	{     try
        {
		DbgridToExcel(dbgrid1);
        }catch(...)
        {}
	}

}
//---------------------------------------------------------------------------
void __fastcall Tfrmwsalehuizhong::dbgrid1CellClick(TColumn *Column)
{
//显示总实洋
  if (!aqdetail->Active) {
    return;
 }
 if (aqdetail->FieldByName("bookname")->AsAnsiString =="") {
     return;
 }
 ShowHead() ;
}
void Tfrmwsalehuizhong::ShowHead()
{

//bookname,userdefcode,price,barcode,presscount,abbreviatedname
     aqhead->Active = false;
     aqhead->Parameters->ParamByName("bn")->Value =aqdetail->FieldByName("bookname")->AsAnsiString.Trim();
     aqhead->Parameters->ParamByName("uc")->Value =aqdetail->FieldByName("userdefcode")->AsAnsiString.Trim();
     aqhead->Parameters->ParamByName("pc")->Value =aqdetail->FieldByName("price")->AsAnsiString;
     aqhead->Parameters->ParamByName("bcode")->Value =Trim(aqdetail->FieldByName("barcode")->AsAnsiString);
     aqhead->Parameters->ParamByName("pcount")->Value =aqdetail->FieldByName("presscount")->AsAnsiString;
     aqhead->Parameters->ParamByName("abb")->Value =Trim(aqdetail->FieldByName("abbreviatedname")->AsAnsiString);
     aqhead->Active = true;




}

//Excel导出函数
bool  Tfrmwsalehuizhong::DbgridToExcel(TDBGrid *dbg)
{
	AnsiString temptext,strXlsFile ,title ;
	int k = dbg->DataSource ->DataSet ->RecordCount ,n=0;


	savedlg->FileName = StringReplace(stgname ,"\\","-",TReplaceFlags()<<rfReplaceAll) + "批销汇总单";
        title = savedlg->FileName ;
	if (savedlg->Execute())
	{
		String DBPath,Name;
		DBPath = Sysutils::ExtractFilePath(savedlg->FileName .c_str()  );
		Name = Sysutils::ExtractFileName(savedlg->FileName .c_str() );
		DBPath = DBPath + Name + ".xls";
		strXlsFile =  DBPath;
	}
	else
	{
    	return false;
	}
        Screen->Cursor = crHourGlass;
	if(FileExists(strXlsFile))
		try {
			DeleteFileA(strXlsFile);
		} catch (...) {
			return false;
		}



    Variant v, vSheet,R;
    try
    {
        v = Variant::CreateObject("Excel.Application");
    }
    catch(...)
    {
    ShowMsg(Handle ,"启动 Excel 出错, 可能是没有安装Excel！",2);
   
        return false;
    }
    // 隐藏Excel界面
    v.OlePropertySet("Visible", false);
    // 新建一个工作表
    v.OlePropertyGet("Workbooks").OleFunction("Add", 1); // 工作表
    // 操作这个工作表
    vSheet = v.OlePropertyGet("ActiveWorkbook")
            .OlePropertyGet("Sheets", 1);

    	n=0 ;


         //标题
        AnsiString riqi= "日期: "+FormatDateTime("yyyy-mm-dd",dtpstart->DateTime)+"到"+FormatDateTime("yyyy-mm-dd",dtpend->DateTime);

       AnsiString op;
       op = "操作员:"+username;

       R = vSheet.OlePropertyGet("Range","A1:K1");
       R.OleFunction("Merge",true);

       R.OlePropertySet("Value",title.c_str());
           R.OlePropertySet("HorizontalAlignment",3);
        R.OlePropertyGet("Font").OlePropertySet("Bold",true);
        R.OlePropertyGet("Font").OlePropertySet("Size",18);

       R = vSheet.OlePropertyGet("Range","A2:E2");
       R.OleFunction("Merge",true);
       R.OlePropertySet("Value",riqi.c_str());
        R = vSheet.OlePropertyGet("Range","H2:K2");
       R.OleFunction("Merge",true);
       R.OlePropertySet("Value",op.c_str());



        n=2;

	int t1= 0;
	temptext = "\n";
	for(int q=0;q<dbg->FieldCount ;++q)
	{
		if (dbg->Columns->Items[q]->Visible == true) {
			t1++;
			temptext = "'"+ dbg->Columns ->Items [q]->Title ->Caption;
			v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );

		}
	}


	int t2 = dbg->DataSource ->DataSet ->RecordCount ;

	dbg->DataSource ->DataSet ->First();
	dbg->DataSource ->DataSet->DisableControls();
	for(int   i=2+n;i<=t2+1+n ;i++)
	{
		t1=0;
		temptext = "\n";
		for(int j=1;j<=dbg->Columns ->Count  ;j++)
		{
			if (dbg->Columns->Items[j-1]->Visible == true) {
				if (dbg->Columns ->Items [j-1]->FieldName == "ISBN") {
					t1++;
					temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsString;
                    v.OlePropertyGet("Cells",i,t1).OlePropertySet("NumberFormatLocal","@");
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );
					//mptext = temptext + "'" + dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsAnsiString + ",";
				}

				else if (dbg->Columns ->Items [j-1]->FieldName == "id" || dbg->Columns ->Items [j-1]->FieldName == "backdot"){

				}
				else
				{

					t1++;
					temptext = dbg->DataSource ->DataSet ->FieldByName(dbg->Columns ->Items [j-1]->FieldName )->AsString;
					v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
				}
			}
		}

		dbg->DataSource ->DataSet ->Next() ;
	}

    R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",n+1,1),vSheet.OlePropertyGet("Cells",t2+n+2,t1)); //取得合并的区域
	R.OlePropertyGet("Borders",2).OlePropertySet("linestyle",1);
	R.OlePropertyGet("Borders",4).OlePropertySet("linestyle",1);

	v.OlePropertyGet("Cells",t2+2+n,1).OlePropertySet("Value","合计");
      	temptext = RzNumericEdit1->Text ;
	v.OlePropertyGet("Cells",t2+2+n,8).OlePropertySet("Value",temptext .c_str() );
      	temptext = RzNumericEdit2->Text ;
	v.OlePropertyGet("Cells",t2+2+n,9).OlePropertySet("Value",temptext .c_str() );
     	temptext = RzNumericEdit3->Text ;
	v.OlePropertyGet("Cells",t2+2+n,11).OlePropertySet("Value",temptext .c_str() );
	dbg->DataSource ->DataSet->EnableControls();

    try {

                v.OlePropertyGet("ActiveWorkbook")
            .OleFunction("SaveAs", strXlsFile.c_str());
    v.OleFunction("Quit");
    vSheet = Unassigned;
    v = Unassigned;
    Screen->Cursor = crDefault ;
ShowMsg(Handle ,"导出成功！",3);
	} catch (Exception &E) {
        Screen->Cursor = crDefault ;
            v.OleFunction("Quit");
            vSheet = Unassigned;
            v = Unassigned;


		//ShowMessage(E.Message);
	}





}
//---------------------------------------------------------------------------

void __fastcall Tfrmwsalehuizhong::toolshowmainmenuClick(TObject *Sender)
{     if (toolshowmainmenu->Caption =="显示\r主菜单")
    {

      HANDLE hWindow = FindWindow("TfrmMain",NULL);
      SendMessage(hWindow ,WM_MYMESSAGE,1,0);
      toolshowmainmenu->Caption ="隐藏\r主菜单";
    }else

    {
    HANDLE hWindow = FindWindow("TfrmMain",NULL);
    SendMessage(hWindow ,WM_MYMESSAGE,0,0);
      toolshowmainmenu->Caption ="显示\r主菜单";

    }

}
//---------------------------------------------------------------------------

