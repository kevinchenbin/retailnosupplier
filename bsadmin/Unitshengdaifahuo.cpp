//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
                       #include "WholesaleMngForm.h"
#include "Unitshengdaifahuo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzDBGrid"
#pragma link "RzDTP"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
Tfrmshengdaifahuo *frmshengdaifahuo;
//---------------------------------------------------------------------------
__fastcall Tfrmshengdaifahuo::Tfrmshengdaifahuo(TComponent* Owner)
	: TForm(Owner)
{
}
void Tfrmshengdaifahuo::init(LandInfo* li)
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
        aqnote->Connection =fcn;
    aq->Connection =fcn;
    adoexec->Connection =fcn;

    dtpend->DateTime = Now();
    dtpstart->DateTime = Now();
    rukudateend->DateTime = Now();
    dtrukubegin->DateTime = Now();

}
//---------------------------------------------------------------------------

void __fastcall Tfrmshengdaifahuo::sbsearchClick(TObject *Sender)
{
//
  AnsiString sql,sql1;

   if (chisbn->Checked) {
       sql =sql+ " and isbn ='"+edisbn->Text+"'";
   }
    if (chauthor->Checked) {
      sql =sql+ " and Author like '%"+edauthor->Text+"%'";
   }
    if (chname->Checked) {
       sql =sql+ " and c.name like '%"+edname->Text+"%'";
   }
    if (chuserdef->Checked) {
      sql =sql+ " and UserDefCode ='"+eduserdef->Text+"'";
     eduserdef->Text="";
   }
   try
   {
 	if (cbruku->Checked ) {

		sql = sql + " and datediff(day,'" + FormatDateTime("yyyy-mm-dd",dtpstart->DateTime)+ "',a.HdTime) >= 0";

		sql = sql + " and datediff(day,'" + FormatDateTime("yyyy-mm-dd",dtpend->DateTime) + "',a.HdTime) <= 0";
	}

    if (cbrukuselect->Checked ) {

    sql = sql + " and datediff(day,'" + FormatDateTime("yyyy-mm-dd",dtrukubegin->DateTime) + "',sh.HdTime) >= 0";

    sql = sql + " and datediff(day,'" + FormatDateTime("yyyy-mm-dd",rukudateend->DateTime) + "',sh.HdTime) <= 0";
    }
    }catch(...)
    {}
   if(cbfahuofanshi->Checked)
   {
     	sql = sql +" and fahuofashi='"+cbfahuo->Text+"'";

   }
 sql1="SELECT DISTINCT RANK() OVER(order by b.id desc) as xuhao,b.id as diaxiaonoteid,b.clientid,c.id as bkcatalogid,c.UserDefCode, c.price,c.Name as bookname, c.Author, d.Name AS clientname, a.Daixiaocode, b.benqicaigou,b.benqicaigou as fahuoamount, b.orderdiscount, c.Price * b.benqicaigou AS fixprice,";
 sql1 = sql1 + " c.Price * b.benqicaigou * b.orderdiscount * 0.01 AS discountprice, a.HdTime, b.fahuofashi FROM  dbo.BS_DaixiaoHeader AS a INNER JOIN ";
 sql1=sql1 +" dbo.BS_DaixiaoNote AS b ON a.id = b.daixiaoheadid LEFT OUTER JOIN dbo.BS_BookCatalog AS c ON a.bkcatalogid = c.ID LEFT OUTER JOIN  dbo.CUST_CustomerInfo AS d ON b.clientid = d.ID left join dbo.BS_StorageNote s on s.bkcatalogid = a.bkcatalogid left join dbo.BS_StorageNoteHeader sh on sh.id=s.StgNtHeaderID where sh.TStgNtcodeint=0 and sh.stgid="+IntToStr(StgID)+" and yifa<>benqicaigou "+sql;

 aqnote->Close();
 aqnote->SQL->Clear();
 aqnote->SQL->Add(sql1);
 aqnote->Open();

 aqnote->DisableControls();
 int totalcaigou=0,totalfahuo=0;
 aqnote->First();
 while(!aqnote->Eof)
 {
   totalcaigou=totalcaigou+aqnote->FieldByName("benqicaigou")->AsInteger;
   totalfahuo=totalfahuo+aqnote->FieldByName("fahuoamount")->AsInteger;
   aqnote->Next();
 }
  aqnote->First();
  aqnote->EnableControls();

  editcaigoutotal->Text = IntToStr(totalcaigou);
  editfahuototal->Text = IntToStr(totalfahuo);

}
//---------------------------------------------------------------------------

void __fastcall Tfrmshengdaifahuo::BtnViewClick(TObject *Sender)
{
WindowState = wsMinimized ;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmshengdaifahuo::tlbtn7Click(TObject *Sender)
{
Close();
HANDLE hWindow = FindWindow("TfrmMain",NULL);
        SendMessage(hWindow ,WM_MYMESSAGE,0,0);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmshengdaifahuo::FormClose(TObject *Sender, TCloseAction &Action)

{
    Action =caFree;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmshengdaifahuo::SpeedButton1Click(TObject *Sender)
{
//

int count=0;
if (!aqnote->Active) {
     return;
}
if (aqnote->IsEmpty()) {
      return;
}
Screen->Cursor = crHourGlass ;
   AnsiString sql;
    TBookmark bm;
    Screen->Cursor = crHourGlass ;
    sql = "delete BS_Temp_DaixiaoCaiGouFaHuo where  userid = " + IntToStr(UserID)+" and stgid="+IntToStr(StgID);
    aq->Close();
    aq->SQL->Clear();
    aq->SQL->Add(sql);
    aq->ExecSQL();

    sql = "select * from BS_Temp_DaixiaoCaiGouFaHuo where userid="+ IntToStr(UserID)+" and stgid="+IntToStr(StgID);
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
                MessageBox(NULL,"请先选择采购书目！","提示",MB_OK|MB_ICONINFORMATION);
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


                        aq->FieldByName("bkcatalogid")->AsInteger = RzDBGrid1->DataSource->DataSet->FieldByName("bkcatalogid")->AsInteger;
                        aq->FieldByName("amount")->AsInteger = RzDBGrid1->DataSource->DataSet->FieldByName("fahuoamount")->AsInteger;
                        aq->FieldByName("discount")->AsFloat=RzDBGrid1->DataSource->DataSet->FieldByName("orderdiscount")->AsFloat;;
                        aq->FieldByName("vendorid")->AsInteger = RzDBGrid1->DataSource->DataSet->FieldByName("clientid")->AsInteger;;
                        aq->FieldByName("fahuofashi")->AsString = RzDBGrid1->DataSource->DataSet->FieldByName("fahuofashi")->AsString;;
                        aq->FieldByName("stgid")->AsInteger = StgID;
                        aq->FieldByName("userid")->AsInteger = UserID;

                        aq->FieldByName("DaixiaoNoteID")->AsInteger = RzDBGrid1->DataSource->DataSet->FieldByName("diaxiaonoteid")->AsInteger;
			aq->Post();
                        RzDBGrid1->DataSource->DataSet->Next();
                        //count++;
                        }
                RzDBGrid1->DataSource->DataSet->EnableControls() ;
    }
    catch(...)
    {}

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
         }

        sbsearch->Click();

}
bool Tfrmshengdaifahuo::createproc()
 {

      AnsiString sql,sql1;
        try
        {
          sql = "exec USP_BS_DaixiaoCaiGouWsale "+IntToStr(UserID)+","+IntToStr(StgID)+","+"@ReturnCode = @ReturnCode OUTPUT,@ReturnCodeint = @ReturnCodeint OUTPUT,@ReturnCodeold=@ReturnCodeold OUTPUT";
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

//---------------------------------------------------------------------------

void __fastcall Tfrmshengdaifahuo::BtnAlignBottomClick(TObject *Sender)
{
WindowState = wsMinimized ;

}
//---------------------------------------------------------------------------

void __fastcall Tfrmshengdaifahuo::BtnNewClick(TObject *Sender)
{
     //

}
//---------------------------------------------------------------------------

void __fastcall Tfrmshengdaifahuo::edisbnChange(TObject *Sender)
{
   if (edisbn->Text!="") {
     chisbn->Checked =true;
   }

}
//---------------------------------------------------------------------------

void __fastcall Tfrmshengdaifahuo::ednameChange(TObject *Sender)
{
     if (edname->Text!="") {
     chname->Checked =true;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmshengdaifahuo::edauthorChange(TObject *Sender)
{
 if (edauthor->Text!="") {
     chauthor->Checked =true;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmshengdaifahuo::eduserdefChange(TObject *Sender)
{
 if (eduserdef->Text!="") {
     chuserdef->Checked =true;
   }
}
//---------------------------------------------------------------------------


void __fastcall Tfrmshengdaifahuo::cbfahuoChange(TObject *Sender)
{
    cbfahuofanshi->Checked=true;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmshengdaifahuo::editfahuoKeyPress(TObject *Sender, wchar_t &Key)

{
   //
   if (Key == '\r')
	{
        if (aqnote->Active) {
           RzDBGrid1->DataSource->DataSet->Edit();
          RzDBGrid1->DataSource->DataSet->FieldByName("fahuoamount")->AsInteger=StrToInt(editfahuo->Text);

        }


        }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmshengdaifahuo::RzDBGrid1CellClick(TColumn *Column)
{        if (aqnote->Active) {
          editfahuo->Text=  RzDBGrid1->DataSource->DataSet->FieldByName("fahuoamount")->AsAnsiString;
            }

}
//---------------------------------------------------------------------------

void __fastcall Tfrmshengdaifahuo::tlbtn8Click(TObject *Sender)
{
     sbsearch->Click();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmshengdaifahuo::N1Click(TObject *Sender)
{
//
       if (aqnote->IsEmpty() ) {
		return;
	}
	for (int i = 1; i <= aqnote->RecordCount; i++) {
		RzDBGrid1->DataSource->DataSet->RecNo = i;
		RzDBGrid1->SelectedRows->CurrentRowSelected = true;
	}
}
//---------------------------------------------------------------------------



void __fastcall Tfrmshengdaifahuo::toolshowmainmenuClick(TObject *Sender)
{
 if (toolshowmainmenu->Caption =="显示\r主菜单")
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

