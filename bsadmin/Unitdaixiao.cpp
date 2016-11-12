//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unitdaixiao.h"
#include "PwdForm.h"
#include "SelectCatalogForm.h"
#include "NewBookinput1.h"
#include "bookhistory.h"
#include "Unitcaigouquery.h"
#include "detailemessage.h"
#include "Unittongyidiscount.h"
#include "bookQuery.h"
#include "Unitaddclient.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzDBEdit"
#pragma link "RzEdit"
#pragma link "RzLabel"
#pragma link "RzDBDTP"
#pragma link "RzDTP"
#pragma link "RzDBGrid"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "RzDBCmbo"
#pragma link "RzCmboBx"
#pragma link "frxClass"
#pragma link "frxCross"
#pragma link "frxDBSet"
#pragma resource "*.dfm"
Tfrmdaixiao *frmdaixiao;
//---------------------------------------------------------------------------
__fastcall Tfrmdaixiao::Tfrmdaixiao(TComponent* Owner)
	: TForm(Owner)
{
}
void Tfrmdaixiao::init(TADOConnection *cn,int auserid,int astgid,AnsiString username)
{
    fcn=cn;
     StgID = astgid;
     UserID = auserid;
     ausername = username;
    m_catalogSearchMode = 1;
    aqnote->Connection = fcn;
    aqHeader->Connection = fcn;
    dsetVendor->Connection = fcn;
    adoreport->Connection = fcn;
    aqtotalhuizhong->Connection=fcn;
    dsetVendor->CommandText="select * from CUST_CustomerInfo where  Type=1 and customerstate=1 and stgid="+IntToStr(StgID)+" order by name";
    dsetVendor->Active = true;
     fmodify=1;

     lboperation->Caption="操作员:"+ausername;
    while(!dsetVendor->Eof)
    {

      	cbclient->AddItem(dsetVendor->FieldByName("Name")->AsAnsiString ,(TObject*)dsetVendor->FieldByName("ID")->AsInteger );
        dsetVendor->Next();
    }

     TADOQuery *aqselect = new TADOQuery(Application);
    aqselect->Connection = fcn;
    aqselect->Close();
    aqselect->SQL->Clear();
    aqselect->SQL->Add("select id,name from dbo.SYS_StaffInfo where career = 1 ");
    aqselect->Open();

      while(!aqselect->Eof)
    {

      	cbcaigou->AddItem(aqselect->FieldByName("Name")->AsAnsiString ,(TObject*)aqselect->FieldByName("ID")->AsInteger );
        aqselect->Next();
    }


    aqselect->Close();
    aqselect->SQL->Clear();
    aqselect->SQL->Add("select bk from dbo.SYS_BSSET where name = 'shengdaicaigoudingwei'");
    aqselect->Open();

    checkstr=aqselect->FieldByName("bk")->AsAnsiString ;

    delete aqselect;

    dbdate->DateTime=Now();

    deletesave = new TStringList(NULL);

    AnsiString values;

    values= checkstr.SubString(1,1);
    chfoceset->Checked = StrToBool(values);
     values= checkstr.SubString(2,1);
     chfsluru->Checked = StrToBool(values);
      values= checkstr.SubString(3,1);
     chfsamount->Checked = StrToBool(values);
      values= checkstr.SubString(4,1);
     chfsdiscount->Checked = StrToBool(values);
      values= checkstr.SubString(5,1);
     chjinjia->Checked = StrToBool(values);
   
}
//---------------------------------------------------------------------------
void __fastcall Tfrmdaixiao::tlbtn7Click(TObject *Sender)
{
 Close();
 HANDLE hWindow = FindWindow("TfrmMain",NULL);
        SendMessage(hWindow ,WM_MYMESSAGE,0,0);

}
//---------------------------------------------------------------------------
void __fastcall Tfrmdaixiao::BtnAlignBottomClick(TObject *Sender)
{
WindowState = wsMinimized ;
}
void Tfrmdaixiao::ChangeCatalogSearchMode()
{
	if (m_catalogSearchMode==3) {
		m_catalogSearchMode=5;
	}else
	{
	m_catalogSearchMode++;  }
	if (m_catalogSearchMode >= 7)
	{
		m_catalogSearchMode = 1;
	}

	switch (m_catalogSearchMode)
	{
	case 1:
		edtCatalog->MaxLength = 15;
		lblCatalog->Caption = "书号";
		break;
	case 2:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "自编码";
		break;
	case 3:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "书名";
		break;
	case 5:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "作者";
		break;
	case 6:
		edtCatalog->MaxLength = 0;
		lblCatalog->Caption = "定价";
		break;
    default:
        break;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmdaixiao::N1Click(TObject *Sender)
{

	lblCatalog->Caption = "书号";
	m_catalogSearchMode=1;
	edtCatalog->MaxLength = 15;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmdaixiao::N2Click(TObject *Sender)
{
	lblCatalog->Caption = "自编码";
	m_catalogSearchMode=2;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmdaixiao::N3Click(TObject *Sender)
{
	lblCatalog->Caption = "书名";
	m_catalogSearchMode=3;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmdaixiao::N4Click(TObject *Sender)
{
	lblCatalog->Caption = "定价";
	m_catalogSearchMode=6;
	edtCatalog->MaxLength = 0;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmdaixiao::lblCatalogMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft ) {
		TPoint  pt;
		GetCursorPos(&pt);
		pm->Popup(pt.x,pt.y);

	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmdaixiao::edtCatalogKeyPress(TObject *Sender, wchar_t &Key)
{
  if (m_catalogSearchMode == 6) {
		if ((Key < '0' || Key > '9') && (Key != '\b') && (Key != '.') && (Key != '\r') ) {
            Key = NULL;
		}
	}
	if (Key == '\r')
	{
                if (dbedtRetailNtCode->Text.IsEmpty()) {
                       	ShowMsg(Handle ,"请先保存！",3);
                        return ;
                }
		if (edtCatalog->Text == "") {
			ChangeCatalogSearchMode();
		}
		else
		{
			float price;
			if (m_catalogSearchMode == 6) {
			try {
					price = StrToFloat(edtCatalog->Text.Trim());
				} catch (...) {
					ShowMsg(Handle ,"请输入正确的定价！",3);
					return;
				}
			}
			int results;

			TfrmSelectCatalog* frm = new TfrmSelectCatalog(Application,fcn);
			LandInfo li;
			li.app = Application;
			li.con = fcn;
			li.userID = UserID ;
			li.storageID = StgID ;
			frm->Init(&li);
			frm->DoModalType = 4;

			frm->SetSearchMode(m_catalogSearchMode, edtCatalog->Text);
			frm->SelectAll = false;
                         frm->disableduoxuan();
                        //期刊处理
                        if (edtCatalog->Text.Trim().Length()>13) {

                           frm->qikan= true;
                           frm->qikanhao =edtCatalog->Text.SubString(14,edtCatalog->Text.Trim().Length()-13) ;
                        }

			frm->QryBkInfo();
			if (frm->findbooks == 3) {
				results= frm->ShowModal();
			}else if (frm->findbooks==1) {
				results = 1;
			}else if ((frm->findbooks==0)||(frm->findbooks==-1)) {
				results = -1 ;
			}

			if (mrOk == results)
			{
				int bkinfoid = -1,catalogID = -1;
				if (frm->SelectAll) {
					 for (int i = 0; i < frm->lengthint; i++) {
						// if (chongfutishi(frm->BkcatalogiD[i])) {
							AddNote(1,frm->BkcatalogiD[i]);
					     //	 }
					 }

				}else
				{
					frm->GetSelectResult(bkinfoid,catalogID);
					if (catalogID >= 0)
					{
                                          	AddNote(1,catalogID);
					}
				}
			}
			else
			{
			      	if (!frm->findbook) {     //产生新书
					if (aqHeader->Active && aqHeader->RecordCount >= 1)
					{
					      	Tfrmnewbook1 *frma = new Tfrmnewbook1(Application,fcn);

                                                         frma->cbsaletype->Text = "期刊";
                                                         frma->editqikanmao->Text =edtCatalog->Text.Trim();
                                                         frma->cbsaletypeChange(this);
                                                 frma->ShowModal();
						if (frma->GetID()!=-1)
						{

                                                         AddNote(0,frma->GetID());
						}
						delete frma;


					}
				}
			}
			delete frm;
		}
                edtCatalog->Text = "";
	}
}

void Tfrmdaixiao::AddNote(int ai,int bkcatalogid)
 {

    AnsiString sql = "select ISBN,Name,Price,UserDefCode,Author,PressCount,b.AbbreviatedName from dbo.BS_BookCatalog a left join dbo.BS_PressInfo b on a.PressID = b.id ";
    sql = sql +"where a.id = "+IntToStr(bkcatalogid);
   TADOQuery *aqselect = new TADOQuery(Application);
    aqselect->Connection = fcn;
    aqselect->Close();
    aqselect->SQL->Clear();
    aqselect->SQL->Add(sql);
    aqselect->Open();

    edname->Text = aqselect->FieldByName("Name")->AsAnsiString ;
    edqihao->Text = aqselect->FieldByName("PressCount")->AsAnsiString ;
    editselfcode->Text = aqselect->FieldByName("UserDefCode")->AsAnsiString ;
    editpress->Text = aqselect->FieldByName("AbbreviatedName")->AsAnsiString ;
    editprice->Text = aqselect->FieldByName("Price")->AsAnsiString ;

    SelectBkCatalogid= bkcatalogid;


    delete aqselect ;



  if (SelectBkCatalogid==-1) {
     ShowMsg(Handle ,"请先选择书目！",3);
     return;
  }
if (aqHeader->Active) {
     sql = "exec BS_NewDaiXiaoNote "+aqHeader->FieldByName("ID")->AsAnsiString+","+IntToStr(SelectBkCatalogid)+","+IntToStr(StgID);

    TADOQuery *aqexe = new TADOQuery(Application);
    aqexe->Connection = fcn;
    aqexe->Close();
    aqexe->SQL->Clear();
    aqexe->SQL->Add(sql);
    aqexe->ExecSQL();
    delete aqexe;
    RefreshDetail();
     nedaixiao->SetFocus();
     }


           //往期
           /*
    AnsiString context;
  AnsiString likename;
  context = edname->Text;

 likename = LeftStr(context,context.Length()-2);

 sqlstr = "select id,presscount from bs_bookcatalog where name like '"+likename+"%'";
             TADOQuery *aq1 =new TADOQuery(Application);
             aq1->Connection = fcn;
             aq1->Close();
             aq1->SQL->Clear();
             aq1->SQL->Add(sqlstr);
             aq1->Open();


             while(!aq1->Eof)
             {

             if (aq1->FieldByName("presscount")->AsAnsiString!="") {
               cbwangqi->AddItem("第"+aq1->FieldByName("presscount")->AsAnsiString+"期",(TObject*)aq1->FieldByName("id")->AsInteger);

             }
                 aq1->Next();
             }
             delete aq1;

         */

 }
//---------------------------------------------------------------------------
void __fastcall Tfrmdaixiao::tlbtn1Click(TObject *Sender)
{
//
    if (cbclient->Text=="") {
        ShowMsg(Handle ,"请选择供应商！",3);
        return;
    }

      try
      {
        int supplierid,caigouid;
        float addcost;

       if (cbcaigou->Text !="") {
              caigouid = (int)(cbcaigou->Items->Objects[cbcaigou->ItemIndex]);
       }else caigouid=-1;
       addcost = dbnbedtAddCosts->Value;
       if (cbclient->Text!="") {
           supplierid=(int)(cbclient->Items->Objects[cbclient->ItemIndex]);
       }else  supplierid=-1;

      AnsiString sql;
      if (fmodify==2) {    //修改模式
             sql = "exec USP_BS_NewDaixiaoHeader "+IntToStr(StgID)+","+IntToStr(UserID)+",'"+
            dm->Text+"',"+ IntToStr(supplierid)+","+IntToStr(caigouid)+","+FloatToStr(dbnbedtAddCosts->Value)+","+editcaigoudiscount->Text+",'"+FormatDateTime("yyyy-mm-dd",dbdate->DateTime)+"',"+aqHeader->FieldByName("ID")->AsAnsiString;
            aqHeader->Close();
            aqHeader->SQL->Clear();
            aqHeader->SQL->Add(sql);
            aqHeader->Open();
              cbclient->Enabled = false;
            cbcaigou->Enabled = false;
            dbdate->Enabled = false;
            dbnbedtAddCosts->Enabled = false;
            tlbtn1->Enabled=false;
            RzToolButton1->Enabled = true;
            dm->Enabled = false;
            editcaigoudiscount->Enabled = false;

            logmessage="修改单号为"+dbedtRetailNtCode->Text+"的省代采购";
            AddEventfx(1,"省代采购",UserID,StgID,logmessage);

      }else if (fmodify==1) {//添加模式
            sql = "exec USP_BS_NewDaixiaoHeader "+IntToStr(StgID)+","+IntToStr(UserID)+",'"+
            dm->Text+"',"+ IntToStr(supplierid)+","+IntToStr(caigouid)+","+FloatToStr(dbnbedtAddCosts->Value)+","+editcaigoudiscount->Text+",'"+FormatDateTime("yyyy-mm-dd",dbdate->DateTime)+"',-1";
            aqHeader->Close();
            aqHeader->SQL->Clear();
            aqHeader->SQL->Add(sql);
            aqHeader->Open();
            SelectBkCatalogid=-1;

            cbclient->Enabled = false;
            cbcaigou->Enabled = false;
            dbdate->Enabled = false;
            dbnbedtAddCosts->Enabled = false;
            tlbtn1->Enabled=false;
            RzToolButton1->Enabled = true;
            dm->Enabled = false;
            editcaigoudiscount->Enabled = false;

            logmessage="保存省代采购单:"+dbedtRetailNtCode->Text+"的省代采购";
            AddEventfx(1,"省代采购",UserID,StgID,logmessage);
      }

      }catch(Exception &E)
      {

        logmessage = E.Message;
        AddEventfx(3,"省代采购",UserID,StgID,logmessage);
        ShowMsg(Handle ,"保存失败！",3);
      }

}
void  Tfrmdaixiao::RefreshDetail()
{
    	aqnote->Active = false;
        if (aqHeader->FieldByName("ID")->AsAnsiString =="") {
           aqnote->Parameters->ParamByName("ID")->Value =-1;
        }else
        {
	   aqnote->Parameters->ParamByName("ID")->Value = aqHeader->FieldByName("ID")->AsInteger ;
        }

	aqnote->Active = true;
       ((TFloatField *)aqnote->FieldByName("orderdiscount"))->DisplayFormat = "0.00";
        refreshHuizhong();





}
//---------------------------------------------------------------------------
void __fastcall Tfrmdaixiao::FormClose(TObject *Sender, TCloseAction &Action)
{
     Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall Tfrmdaixiao::dbgridColumns5GetCellParams(TObject *Sender, bool EditMode,
          TColCellParamsEh *Params)
{
    //int t = dbgrid->Columns->Items[3]->Field->Value;
    //int p = dbgrid->Columns->Items[4]->Field->Value;
   // Params->Text = IntToStr(t+p);
  

}
//---------------------------------------------------------------------------
void __fastcall Tfrmdaixiao::SpeedButton1Click(TObject *Sender)
{
  //int  bkcatalogid;
       // bkcatalogid = (int)cbwangqi->Items->Objects[cbwangqi->ItemIndex];
        if (SelectBkCatalogid==-1) {
           return;
        }else
        {
   	Tfrmbookhistory *frm = new Tfrmbookhistory(Application,fcn,StgID,SelectBkCatalogid );
	frm->Show();
       //	delete frm;
        }
}
//---------------------------------------------------------------------------
void __fastcall Tfrmdaixiao::dblkpcbbVendorIDKeyPress(TObject *Sender, wchar_t &Key)

{
  	if (Key == '\r')
	{
		if (cbclient->Text == "") {
			ShowMsg(Handle ,"请选择供应商！",3);
			return;
		}
		//BtnSave->Click();
                  AnsiString sql ="update BS_DaixiaoHeader set supplierid="+dsetVendor->FieldByName("ID")->AsAnsiString + " where id="+aqHeader->FieldByName("ID")->AsAnsiString;
                   TADOQuery *aqupdatesupplier = new TADOQuery(Application);
    aqupdatesupplier->Connection = fcn;
    aqupdatesupplier->Close();
    aqupdatesupplier->SQL->Clear();
    aqupdatesupplier->SQL->Add(sql);
    aqupdatesupplier->ExecSQL();

    delete aqupdatesupplier;






		edtCatalog->SetFocus();
		if (!edtQryVendor->Enabled ) {
			cbclient->Enabled = false;
		}
		edtCatalog->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrmdaixiao::edtQryVendorKeyPress(TObject *Sender, wchar_t &Key)
{
      	if (Key == '\r')
	{
		
                if (!cbclient->Enabled) {
                       return;
                }
		TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcn;
		AnsiString sql;
		sql = "select ID,Name from CUST_CustomerInfo where type = 1 and customerstate =1 and stgid = "+IntToStr(StgID)+" and Name like '%" + edtQryVendor->Text + "%'";
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
		aq->Open();
        cbclient->Clear();
		while (!aq->Eof )
		{
			cbclient->AddItem(aq->FieldByName("Name")->AsAnsiString ,(TObject*)aq->FieldByName("ID")->AsInteger );
			aq->Next();
		}
		aq->First();
		cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)aq->FieldByName("ID")->AsInteger );
                if(cbclient->Enabled)
                {
                    cbclient->SetFocus();

                }
                edtQryVendor->Text = "";

          
	      //	dblkpcbbVendorID->SetFocus();
	}
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall Tfrmdaixiao::tlbtn8Click(TObject *Sender)
{
	Tfrmcaigouquery *frm = new Tfrmcaigouquery(Application,fcn,StgID,3,-1,true);
        if (frm->ShowModal() == mrOk)
        {
           	AnsiString code = frm->GetNoteCode();
		AnsiString sqlwhere = frm->GetWhere();
                AnsiString sql;
                sql = "select * from BS_DaixiaoHeader  "+sqlwhere;
                aqHeader->Close();
                aqHeader->SQL->Clear();
                aqHeader->SQL->Add(sql);
                aqHeader->Open();
                TLocateOptions Opts;
                Opts.Clear();
                Opts << loPartialKey;
                aqHeader->Locate("Daixiaocode", code, Opts);
                RefreshHeader();
                RefreshDetail();
                RefreshBook();
                tlbtn1->Enabled = false;
                RzToolButton1->Enabled = true;
        }
}
//---------------------------------------------------------------------------
void Tfrmdaixiao::RefreshHeader()
{

try
{
if(aqHeader->RecordCount>=1)
  {
    dbnbedtAddCosts->Value = aqHeader->FieldByName("AddCosts")->AsFloat;
  dbdate->DateTime =  aqHeader->FieldByName("HdTime")->AsDateTime;
     editcaigoudiscount->Text =aqHeader->FieldByName("caigoudiscount")->AsAnsiString;


  if (aqHeader->FieldByName("caigouyuan")->AsAnsiString !="") {
     cbcaigou->ItemIndex = cbcaigou->Items->IndexOfObject((TObject*)aqHeader->FieldByName("caigouyuan")->AsInteger );
  }else cbcaigou->ItemIndex = -1;


  if (aqHeader->FieldByName("supplierid")->AsAnsiString !="") {
     cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)aqHeader->FieldByName("supplierid")->AsInteger );
  }else cbclient->ItemIndex = -1;

   dm->Text =  aqHeader->FieldByName("bk")->AsAnsiString;


  }
  }catch(...)
  {}


}
void __fastcall Tfrmdaixiao::DBNavigator1Click(TObject *Sender, TNavigateBtn Button)

{
try
{
  if(aqHeader->RecordCount>1)
  {
   RefreshDetail();
  RefreshBook();



  dbnbedtAddCosts->Value = aqHeader->FieldByName("AddCosts")->AsFloat;
  dbdate->DateTime =  aqHeader->FieldByName("HdTime")->AsDateTime;
 editcaigoudiscount->Text =aqHeader->FieldByName("caigoudiscount")->AsAnsiString;


  if (aqHeader->FieldByName("caigouyuan")->AsAnsiString !="") {
     cbcaigou->ItemIndex = cbcaigou->Items->IndexOfObject((TObject*)aqHeader->FieldByName("caigouyuan")->AsInteger );
  }else cbcaigou->ItemIndex = -1;


  if (aqHeader->FieldByName("supplierid")->AsAnsiString !="") {
     cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)aqHeader->FieldByName("supplierid")->AsInteger );
  }else cbclient->ItemIndex = -1;

   dm->Text =  aqHeader->FieldByName("bk")->AsAnsiString;
  }


  }catch(...)
  {}

}
void Tfrmdaixiao::RefreshBook()
{

if (aqHeader->FieldByName("bkcatalogid")->AsAnsiString=="" ) {
    edname->Text = "";
    edqihao->Text = "";
    editselfcode->Text ="";
    editpress->Text = "";
    editprice->Text = "";
     return;
}
      AnsiString sql = "select ISBN,Name,Price,UserDefCode,Author,PressCount,b.AbbreviatedName from dbo.BS_BookCatalog a left join dbo.BS_PressInfo b on a.PressID = b.id ";
    sql = sql +"where a.id = "+aqHeader->FieldByName("bkcatalogid")->AsAnsiString;
   TADOQuery *aqselect = new TADOQuery(Application);
    aqselect->Connection = fcn;
    aqselect->Close();
    aqselect->SQL->Clear();
    aqselect->SQL->Add(sql);
    aqselect->Open();

    edname->Text = aqselect->FieldByName("Name")->AsAnsiString ;
    edqihao->Text = aqselect->FieldByName("PressCount")->AsAnsiString ;
    editselfcode->Text = aqselect->FieldByName("UserDefCode")->AsAnsiString ;
    editpress->Text = aqselect->FieldByName("AbbreviatedName")->AsAnsiString ;
    editprice->Text = aqselect->FieldByName("Price")->AsAnsiString ;
    delete aqselect;

   cbclient->ItemIndex = cbclient->Items->IndexOfObject((TObject*)aqHeader->FieldByName("supplierid")->AsInteger );
   SelectBkCatalogid=  aqHeader->FieldByName("bkcatalogid")->AsInteger ;



}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaixiao::cbclient2KeyPress(TObject *Sender, wchar_t &Key)
{
if (Key == '\r')
	{
        AnsiString sql;
              	TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcn;
               //保存到单透
               // = cbclient->Items->IndexOfObject((TObject*));
                  int clientid = int(cbclient->Items->Objects[cbclient->ItemIndex]);
                sql = "update BS_DaixiaoHeader set supplierid="+IntToStr(clientid) +" where id="+aqHeader->FieldByName("id")->AsAnsiString  ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
                aq->ExecSQL();
                delete aq;
cbclient->Enabled = false;
edtCatalog->SetFocus();
        }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaixiao::D1Click(TObject *Sender)
{
//
if (!aqnote->Active) {
       return;
   }
     if (aqnote->RecordCount==0) {
       return;
     }

     if (!aqHeader->Active) {
     return;

     }
     	if (dbgrid->DataSource->DataSet->RecordCount!=0 ) {
				if (MessageBoxA(0,"确定要删除该记录吗?","询问",MB_ICONQUESTION|MB_OKCANCEL)!=1 )
					return;
			}

AnsiString updateid="(",clientname;
AnsiString huifustr;
      	if (aqnote->Active && aqnote->RecordCount >= 1)
		{

             //	dbgrid->DataSource->DataSet->DisableControls();
		for (int i = 0 ; i < dbgrid->SelectedRows->Count ; i++) {

	       	 dbgrid->DataSource->DataSet->Bookmark = dbgrid->SelectedRows->Items[i];
	       	 bm = dbgrid->DataSource->DataSet->GetBookmark();
	       	 dbgrid->DataSource->DataSet->GotoBookmark(bm);


                 updateid = updateid+dbgrid->DataSource->DataSet->FieldByName("ID")->AsAnsiString+",";

                 huifustr="("+dbgrid->DataSource->DataSet->FieldByName("clientid")->AsAnsiString+","+
                 dbgrid->DataSource->DataSet->FieldByName("shanqicaigou")->AsAnsiString +","+
                 dbgrid->DataSource->DataSet->FieldByName("benqiorder")->AsAnsiString +","+
                 dbgrid->DataSource->DataSet->FieldByName("benqidaixiao")->AsAnsiString +","+
                 dbgrid->DataSource->DataSet->FieldByName("benqicaigou")->AsAnsiString +","+
                 dbgrid->DataSource->DataSet->FieldByName("orderdiscount")->AsAnsiString +","+
                 aqHeader->FieldByName("id")->AsAnsiString+",'"+
                 dbgrid->DataSource->DataSet->FieldByName("fahuofashi")->AsAnsiString +"','"+
                 dbgrid->DataSource->DataSet->FieldByName("remarks")->AsAnsiString +"')";
                 deletesave->Add(huifustr);
                 clientname=clientname+dbgrid->DataSource->DataSet->FieldByName("clientname")->AsAnsiString+":";

                }
               // dbgrid->DataSource->DataSet->EnableControls();
                }


                updateid =updateid+"-1)";

         	TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcn;
                AnsiString sql;
                sql = "delete BS_DaixiaoNote where id in "+updateid  ;
		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
                aq->ExecSQL();
                 logmessage="省代采购单:"+dbedtRetailNtCode->Text+" 删除明细"+clientname;
            AddEventfx(1,"省代采购",UserID,StgID,logmessage);
        delete aq;
          RefreshDetail();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------




void __fastcall Tfrmdaixiao::BtnNewClick(TObject *Sender)
{
    //


    if (!aqHeader->Active) {
         return;
    }
       	AnsiString sql;

  dsetVendor->Active = false;
   dsetVendor->CommandText="select * from CUST_CustomerInfo where  Type=1 and customerstate=1 and stgid="+IntToStr(StgID)+" order by name";
  dsetVendor->Active = true;

   cbclient->Clear();
   dsetVendor->First();
    while(!dsetVendor->Eof)
    {

      	cbclient->AddItem(dsetVendor->FieldByName("Name")->AsAnsiString ,(TObject*)dsetVendor->FieldByName("ID")->AsInteger );
      dsetVendor->Next();
    }
    cbclient->Enabled = true;
               //  AnsiString sql;

    fmodify=1;
    SelectBkCatalogid=-1;
     RefreshDetail();//刷新明细

     edtQryVendor->Text ="";
     dbnbedtAddCosts->Value = 0;
      cbcaigou->ItemIndex =-1;

     dbedtRetailNtCode->Text="";
     edtCatalog->Text = "";
     edname->Text = "";
    edqihao->Text = "" ;
    editselfcode->Text = "";
    editpress->Text = "" ;
    editprice->Text = "" ;
    dm->Text = "";


    editcaigou->Text = "";
    editorder->Text = "";
    editdaixiao->Text = "";
    editcaigoubeng->Text = "";

    nedaixiao->Text = "";
    necaigou->Text = "";
    neorder->Text = "";
    editbk->Text = "";

    tlbtn1->Enabled=true;
       cbclient->Enabled = true;
            cbcaigou->Enabled = true;
            dbdate->Enabled = true;
            dbnbedtAddCosts->Enabled = true;
            dm->Enabled = true;
             editcaigoudiscount->Enabled = true;
             editcaigoudiscount->Text="100";
    RzToolButton1->Enabled = false;
    aqnote->Active = false;
    aqnote->Parameters->ParamByName("ID")->Value =-1;
	aqnote->Active = true;
        if (edtQryVendor->Enabled) {
          edtQryVendor->SetFocus();
        }

}
//---------------------------------------------------------------------------



void __fastcall Tfrmdaixiao::RzToolButton1Click(TObject *Sender)
{
   tlbtn1->Enabled =true;
   fmodify=2;
    cbclient->Enabled = true;
            cbcaigou->Enabled = true;
            dbdate->Enabled = true;
            dbnbedtAddCosts->Enabled = true;
           // tlbtn1->Enabled=true;
           // RzToolButton1->Enabled = true;
            dm->Enabled = true;
            editcaigoudiscount->Enabled = true;
            RzToolButton1->Enabled=false;
}
//---------------------------------------------------------------------------
void Tfrmdaixiao::print(int type)
{


            if (!aqHeader->Active) {
                 return;
            }


             AnsiString sql;
	TADOQuery *aq = new TADOQuery(this);
	aq->Connection = fcn;
      /*	sql = "select * from sys_bsset where name = 'xiaoshudian'" ;
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
	}   */

        sql = "select name from dbo.SYS_StorageInfo where id ="+IntToStr(StgID);
        	aq->Close();
	aq->SQL->Clear();
	aq->SQL->Add(sql);
	aq->Open();
        title=aq->FieldByName("name")->AsAnsiString ;


        sql = "select sum(benqicaigou) as amount,fahuofashi  from BS_DaixiaoNote  where daixiaoheadid ="+aqHeader->FieldByName("id")->AsAnsiString+" group by fahuofashi";
        aq->Close();
        aq->SQL->Clear();
        aq->SQL->Add(sql);
        aq->Open();
        int heji1,heji2;
        heji1=0;
        heji2=0;
        while(!aq->Eof)
        {
          if (aq->FieldByName("fahuofashi")->AsAnsiString=="社直发") {
           heji1  =  aq->FieldByName("amount")->AsInteger;
          }
            if (aq->FieldByName("fahuofashi")->AsAnsiString=="淄转发") {
           heji2  =  aq->FieldByName("amount")->AsInteger;
          }

         aq->Next();
        }


        remarks=dm->Text;

	delete aq;
        bool onlyone=false;
       if (heji1==0) {
           heji1=heji2;
           onlyone=true;
       }
       if (heji2==0) {
            heji2=heji1;
            onlyone=true;
       }


  try {

     adoreport->Active = false;
     adoreport->Parameters->ParamByName("id")->Value= aqHeader->FieldByName("id")->AsInteger;
     adoreport->Active  = true;



	Variant  v,vSheet,R,xWorkbook,Range,EBorders;
	v   =Variant::CreateObject("Excel.Application");
	v.OlePropertySet("Visible",true);
	v.OlePropertyGet("WorkBooks").OleFunction("Add");
	xWorkbook = v.OlePropertyGet("ActiveWorkBook");
	vSheet =  xWorkbook.OlePropertyGet("ActiveSheet");
        v.OlePropertySet("StatusBar", "您好,请您稍等。正在查询！");
      int n=1 ;

	int t1= 0;
       AnsiString temptext = "";
       temptext = title+"采购单《"+edname->Text+"》";

       R = vSheet.OlePropertyGet("Range","A1:I1");
       R.OleFunction("Merge",true);

       R.OlePropertySet("Value",temptext.c_str());

        R.OlePropertySet("HorizontalAlignment",3);
        R.OlePropertyGet("Font").OlePropertySet("Bold",true);
        R.OlePropertyGet("Font").OlePropertySet("Size",18);
          
          vSheet.OlePropertyGet("Range","F3:F100").OlePropertySet("NumberFormatLocal","@");

        for(int j=0;j<adoreport->Fields->Count ;j++)
        {
            t1++;
            temptext =adoreport->Fields->Fields[j]->DisplayLabel;
            v.OlePropertyGet("Cells",1+n,(t1)).OlePropertySet("Value",temptext .c_str() );

        }
        vSheet.OlePropertyGet("Range","A2:I2").OlePropertyGet("Font").OlePropertySet("Bold",true);;


	int t2 = adoreport->RecordCount ;

	adoreport->First();
         bool zzf=true;
        int i;
	for(i=2+n;i<=t2+1+n+1 ;i++)
	{

           if ((adoreport->FieldByName("发货方式")->AsAnsiString=="淄转发")&&(zzf)) {
                    temptext ="小计" ;
                    v.OlePropertyGet("Cells",i,1).OlePropertySet("Value",temptext .c_str());

                    v.OlePropertyGet("Cells",i,1).OlePropertyGet("Font").OlePropertySet("Bold",true);;  // AsString .c_str()
                    temptext =IntToStr(heji1) ;
                    v.OlePropertyGet("Cells",i,4).OlePropertySet("Value",temptext .c_str() );
                    v.OlePropertyGet("Cells",i,4).OlePropertyGet("Font").OlePropertySet("Bold",true);;  // AsString .c_str()
                    i++;
                    zzf = false;
           }
		t1=0;
		temptext = "\n";
                 for(int j=0;j<adoreport->Fields->Count ;j++)
                 {
                    t1++;
                    temptext =adoreport->Fields->Fields[j]->AsAnsiString ;

                    v.OlePropertyGet("Cells",i,t1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()

                  }

		adoreport->Next() ;
	}
        //设成文件本格式



            temptext ="小计" ;
            v.OlePropertyGet("Cells",i,1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
             temptext =IntToStr(heji2) ;
             v.OlePropertyGet("Cells",i,1).OlePropertyGet("Font").OlePropertySet("Bold",true);
            v.OlePropertyGet("Cells",i,4).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
            v.OlePropertyGet("Cells",i,4).OlePropertyGet("Font").OlePropertySet("Bold",true);

             temptext ="合计" ;
            v.OlePropertyGet("Cells",i+1,1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
           if (onlyone) {
              temptext =IntToStr(heji1) ;
           }else temptext =IntToStr(heji1+heji2) ;

            v.OlePropertyGet("Cells",i+1,4).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
              v.OlePropertyGet("Cells",i+1,4).OlePropertyGet("Font").OlePropertySet("Bold",true);

              temptext ="备注" ;
            v.OlePropertyGet("Cells",i+2,1).OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
             temptext =remarks ;
             AnsiString he;
             he = "B"+IntToStr(i+2)+":I"+IntToStr(i+2);
             R = vSheet.OlePropertyGet("Range",he.c_str());
             R.OleFunction("Merge",true);
             R.OlePropertySet("Value",temptext .c_str() );  // AsString .c_str()
             R.OlePropertyGet("Font").OlePropertySet("Bold",true);



        R = vSheet.OlePropertyGet("Range",vSheet.OlePropertyGet("Cells",n+1,1),vSheet.OlePropertyGet("Cells",t2+n+2,t1)); //取得合并的区域
        EBorders = R.OlePropertyGet("Borders");
        EBorders.OlePropertySet("linestyle",1);
        EBorders.OlePropertySet("weight",3);
             //   OlePropertyGet("Borders",2)
       // EBorders.OlePropertySet("linestyle",1);
                // OlePropertyGet("Borders",4)
	} catch (Exception &E) {
        	ShowMsg(Handle ,E.Message,0);
		//ShowMessage(E.Message);
                // xWorkbook = Unassigned;
   // v = Unassigned;
	}

     //	return false;





     
}
void __fastcall Tfrmdaixiao::BtnPrintClick(TObject *Sender)
{
 if (!aqnote->Active) {
       return;
   }
     if (aqnote->RecordCount==0) {
       return;
     }

     if (!aqHeader->Active) {
     return;

     }
print(1);
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaixiao::caigoureportGetValue(const UnicodeString VarName, Variant &Value)

{




if (CompareText(VarName,"\"title\"")==0 ) {
		  Value = title;
	}
        	if (CompareText(VarName,"\"bk\"")==0 ) {
		  Value = remarks;
	}
       	if (CompareText(VarName,"\"heji\"")==0 ) {
		  Value = editcaigoubeng->Text;
	}

}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaixiao::RzToolButton2Click(TObject *Sender)
{
 if (!aqnote->Active) {
       return;
   }
     if (aqnote->RecordCount==0) {
       return;
     }

     if (!aqHeader->Active) {
     return;

     }
print(1);
}
//---------------------------------------------------------------------------


void __fastcall Tfrmdaixiao::dbgridColumns5UpdateData(TObject *Sender, UnicodeString &Text,
          Variant &Value, bool &UseText, bool &Handled)
{
//dm->Lines->Add(UseText+"+++"+Text);

}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaixiao::cbcaigouKeyPress(TObject *Sender, wchar_t &Key)
{
//
     if (Key == '\r')
	{

             if(dbnbedtAddCosts->Enabled)
                {
                    dbnbedtAddCosts->SetFocus();

                }


        }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaixiao::editcaigoudiscountKeyPress(TObject *Sender, wchar_t &Key)

{
     if (Key == '\r')
	{

            if (tlbtn1->Enabled) {
                tlbtn1->Click();
            }
             if(edtCatalog->Enabled)
                {
                    edtCatalog->SetFocus();

                }


        }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaixiao::dbnbedtAddCostsKeyPress(TObject *Sender, wchar_t &Key)

{
   //

     if (Key == '\r')
	{

             if(editcaigoudiscount->Enabled)
                {
                    editcaigoudiscount->SetFocus();

                }


        }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaixiao::cbclientKeyPress(TObject *Sender, wchar_t &Key)
{
       if (Key == '\r')
	{
              if (cbclient->Text=="") {
                  return;
              }
              if (tlbtn1->Enabled) {
              //  tlbtn1->Click();
              }



             if(dbnbedtAddCosts->Enabled)
                {
                    dbnbedtAddCosts->SetFocus();

                }


        }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaixiao::sbnewcustomerClick(TObject *Sender)
{
   //
        //添加新供应商
        String ID;
        ID = "";
        TDetaileForm * frm = new TDetaileForm(Application,1,1,ID.c_str() ,fcn,StgID);
        frm->ShowModal();
        newclientid=frm->clientid;

        delete frm;
         if (newclientid==0) {
         return;
        }
             	AnsiString sql;
                 dsetVendor->Active = false;
 dsetVendor->CommandText="select * from CUST_CustomerInfo where  Type=1 and customerstate=1 and stgid="+IntToStr(StgID)+" and id ="+IntToStr(newclientid);

  dsetVendor->Active = true;

   cbclient->Clear();
   dsetVendor->First();
    while(!dsetVendor->Eof)
    {

      	cbclient->AddItem(dsetVendor->FieldByName("Name")->AsAnsiString ,(TObject*)dsetVendor->FieldByName("ID")->AsInteger );
      dsetVendor->Next();
    }
    cbclient->Enabled = true;
    if (cbclient->Items->Count>0) {
       cbclient->ItemIndex = 0;
       cbclient->SetFocus();
    }



}
void Tfrmdaixiao::AddEventfx(int type,AnsiString SourceFrom,int user,int Stg,AnsiString Mg)
{
  AnsiString MsType;
  AnsiString sql;

  try
  {
  switch (type) {
	  case 1:
		   MsType = "信息";
			break;
	  case 2:
		   MsType = "警告";
		   break;
	  case 3:
		   MsType = "错误";
		   break;
  default:
	  ;
  }
  sql = "insert into sys_log (EventType,SourceFrom,EventDate,EventUser,EventMessage,stgName) values('";
  sql = sql + MsType + "','"+SourceFrom+ "',getDate()," +IntToStr(user) +",'" +  Mg + "'," +IntToStr(Stg) +")";
  TADOQuery *aq = new TADOQuery(NULL);
  aq->Connection = fcn;
  aq->Close();
  aq->SQL->Clear();
  aq->SQL->Add(sql);
  aq->ExecSQL();
  delete aq;

  }catch(...)
  {}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaixiao::RzToolButton4Click(TObject *Sender)
{
//统一
 AnsiString fahuofangshi;
 if (!aqnote->Active) {
       return;
   }
     if (aqnote->RecordCount==0) {
       return;
     }

     if (!aqHeader->Active) {
     return;

     }
    float discounta=0;
    if ((dbgrid->SelectedRows->Count == 0) || (dbgrid->SelectedRows->Count == 1)) {
          for (int i = 1; i <= aqnote->RecordCount ; i++) {
                            dbgrid->DataSource->DataSet->RecNo = i;
                            dbgrid->SelectedRows->CurrentRowSelected = true;
                    }
    }
  Tfrmtongyidiscount * frmdiscount = new Tfrmtongyidiscount(Application);
  frmdiscount->nedit->SelectAll();
   if ( frmdiscount->ShowModal()==mrOk)
   {

       discounta= frmdiscount->getdiscount();
       //更新折扣
       fahuofangshi=frmdiscount->getfahuofangshi();
       if (((discounta==-1)&&(fahuofangshi=="")) )
       {
          delete  frmdiscount;
          return ;

       }

       String updateid="(";

      	if (aqnote->Active && aqnote->RecordCount >= 1)
        {
			//统一模式
            	dbgrid->DataSource->DataSet->DisableControls();
		for (int i = 0 ; i < dbgrid->SelectedRows->Count ; i++) {

	       	 dbgrid->DataSource->DataSet->Bookmark = dbgrid->SelectedRows->Items[i];
	       	 bm = dbgrid->DataSource->DataSet->GetBookmark();
	       	 dbgrid->DataSource->DataSet->GotoBookmark(bm);

                 updateid = updateid+dbgrid->DataSource->DataSet->FieldByName("ID")->AsAnsiString+",";

                }
                dbgrid->DataSource->DataSet->EnableControls();
        }
                updateid =updateid+"-1)";

         	TADOQuery *aq = new TADOQuery(this);
		aq->Connection = fcn;
                AnsiString sql;
                if ((discounta!=-1)&&(fahuofangshi!="")) {
                    sql = "update BS_DaixiaoNote set orderdiscount="+FloatToStr(discounta)+",fahuofashi='"+fahuofangshi+"' where id in "+updateid  ;
                }else if ((discounta==-1)&&(fahuofangshi!="")) {
                    sql = "update BS_DaixiaoNote set fahuofashi='"+fahuofangshi+"' where id in "+updateid  ;

                }else if ((discounta!=-1)&&(fahuofangshi=="")) {
                     sql = "update BS_DaixiaoNote set orderdiscount="+FloatToStr(discounta)+" where id in "+updateid  ;

                }else if (((discounta==-1)&&(fahuofangshi=="")) ) {
                     sql = "update BS_DaixiaoNote set orderdiscount = -10 where id =-1000 ";
                }

		aq->Close();
		aq->SQL->Clear();
		aq->SQL->Add(sql);
                aq->ExecSQL();

               delete aq;
               RefreshDetail();

   }

   delete  frmdiscount;

}
//---------------------------------------------------------------------------


void __fastcall Tfrmdaixiao::dbgridColumns4UpdateData(TObject *Sender, UnicodeString &Text,
          Variant &Value, bool &UseText, bool &Handled)
{
        try
        {
            aqnote->Edit();
            aqnote->FieldByName("benqicaigou")->AsInteger =
            aqnote->FieldByName("benqiorder")->AsInteger+(int)Value;
            aqnote->UpdateRecord();
        }catch(...)
        {}
}



//---------------------------------------------------------------------------




void __fastcall Tfrmdaixiao::dsnoteDataChange(TObject *Sender, TField *Field)
{
   //   if (aqnote->Eof) {
     //    dbgrid->DataSource->DataSet->Cancel();
      //}

}
void Tfrmdaixiao::refreshHuizhong()
{
           if (aqHeader->FieldByName("ID")->AsAnsiString =="") {
           aqnote->Parameters->ParamByName("ID")->Value =-1;
        }else
        {
            aqtotalhuizhong->Active = false;

             aqtotalhuizhong->Parameters->ParamByName("id")->Value=aqHeader->FieldByName("ID")->AsInteger;
             aqtotalhuizhong->Active =true;

            editcaigou->Text = aqtotalhuizhong->FieldByName("shanqi")->AsAnsiString;
            editorder->Text = aqtotalhuizhong->FieldByName("benqi")->AsAnsiString;
            editdaixiao->Text = aqtotalhuizhong->FieldByName("daixao")->AsAnsiString;
            editcaigoubeng->Text = aqtotalhuizhong->FieldByName("benqicaigou")->AsAnsiString;

        }
             


}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaixiao::N5Click(TObject *Sender)
{
//
if (aqnote->IsEmpty()) {
    return;
}
if (!aqnote->Active) {
   return;
}
 	if (dbgrid->SelectedRows->Count == 1) {
            	for (int i = 1; i <= aqnote->RecordCount ; i++) {
					dbgrid->DataSource->DataSet->RecNo = i;
					dbgrid->SelectedRows->CurrentRowSelected = true;
				}
        }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaixiao::spnewbookClick(TObject *Sender)
{
//

    if (aqHeader->Active && aqHeader->RecordCount >= 1)
    {
            Tfrmnewbook1 *frma = new Tfrmnewbook1(Application,fcn);
         //	frma->memberorder = this;
           // frma->modle = 4;

           // frma->editcode->Text = edtCatalog->Text ;
            //处理期刊新书
          //  if ( edtCatalog->Text.Trim().Length()>13) {
                     frma->cbsaletype->Text = "期刊";
                     frma->editqikanmao->Text =edtCatalog->Text.Trim();
                     frma->cbsaletypeChange(this);
                  //   PostMessage(frma->editqikanmao->Handle, WM_KEYDOWN,VK_RETURN,0);
          //  }

            frma->ShowModal();
            if (frma->GetID()!=-1) {
             AddNote(0,frma->GetID());
            }


            delete frma;

    }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaixiao::RzToolButton5Click(TObject *Sender)
{
	Tfrmbookquery * frm = new Tfrmbookquery(Application,fcn,StgID);
	frm->ShowModal();
	delete frm;
}
//---------------------------------------------------------------------------


void __fastcall Tfrmdaixiao::N6Click(TObject *Sender)
{
//
AnsiString insertstr,values;


if (deletesave->Count!=0) {

    TADOQuery *aq = new TADOQuery(this);
    aq->Connection = fcn;
    aq->Close();
    aq->SQL->Clear();
   for (int i=0; i < deletesave->Count; i++) {

        values= deletesave->Strings[i];
        insertstr="insert into BS_DaixiaoNote(clientid,shanqicaigou,benqiorder,benqidaixiao,benqicaigou,orderdiscount,daixiaoheadid,fahuofashi,remarks) values"+values+";";

        aq->SQL->Add(insertstr);
    }
    try
    {
    aq->ExecSQL();

    }catch(...)
    {
          ShowMsg(Handle ,"恢复失败！",3);

    }
    logmessage="省代采购单:"+dbedtRetailNtCode->Text+" 恢复上次删除明细";
    AddEventfx(1,"省代采购",UserID,StgID,logmessage);
    deletesave->Clear();
    RefreshDetail();
  }
    if (deletesave->Count==0) {
        N6->Enabled=false;
  }else
  {
     N6->Enabled=false;

  }

}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaixiao::PopupMenu1Popup(TObject *Sender)
{
 if (deletesave->Count==0) {
        N6->Enabled=false;
    }else  N6->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaixiao::RzToolButton6Click(TObject *Sender)
{
 if (!aqnote->Active) {
       return;
   }
     if (aqnote->RecordCount==0) {
       return;
     }

     if (!aqHeader->Active) {
     return;

     }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaixiao::caigoureportBeforePrint(TfrxReportComponent *Sender)

{
     TfrxCrossView * Cross;
	int i, j;
	Variant Row,Col,Text;
	AnsiString titlename;
	int totalamount = 0;
	double caigou = 0;

	Cross = dynamic_cast <TfrxCrossView *> (Sender);
	AnsiString tojiTitle[3];
        bool zzf=true;


	if(Cross != NULL)
	{
        Cross->Left = 1;
        Cross->CellMemos[0]->Font->Size=5;
       // Cross->CellMemos[0]->Height=5.2;
		adoreport->First();
		i = 0;
		while (!adoreport->Eof)
		{

                if ((CompareText(adoreport->FieldByName("发货方式")->AsAnsiString,"淄转发")==0)&&zzf) {


                   Row = i;
                   Col ="到站";
                   Text="小计:";
                   Cross->AddValue(&Row, 1, &Col, 1, &Text, 1);
                      Col ="采购数";
                   Text=caigou;
                   Cross->AddValue(&Row, 1, &Col, 1, &Text, 1);

                   caigou=0;
                    zzf=false;
                   i++;

                }
			for(j = 0; j < adoreport->Fields->Count; j++)
			{
				Row = i;
				titlename = adoreport->Fields->Fields[j]->DisplayLabel;
				if (titlename != "NOTITLE") {
					Col = titlename ;
                                        if ((CompareText(titlename,"采购数")==0)) {
						Text =   adoreport->Fields->Fields[j]->AsAnsiString;
						tojiTitle[1]="实洋";
						caigou = caigou + adoreport->Fields->Fields[j]->AsInteger;
					  }

                                          else
                                          {
                                           Text = adoreport->Fields->Fields[j]->AsAnsiString ;
                                          }

                                          Cross->AddValue(&Row, 1, &Col, 1, &Text, 1);
				}
			}
			adoreport->Next();
			i++;
		}


                 Row = i;
                   Col ="到站";
                   Text="小计:";
                   Cross->AddValue(&Row, 1, &Col, 1, &Text, 1);
                      Col ="采购数";
                   Text=caigou;
                   Cross->AddValue(&Row, 1, &Col, 1, &Text, 1);

                }

                  




    	//合计
	     /*	Row = i;
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
	}     */
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaixiao::nedaixiaoKeyPress(TObject *Sender, wchar_t &Key)
{
        if (Key=='\r') {
           if (checknote())
           {

           
            //编缉的是本期采购       benqidaixiao


          //  if ((aqnote->RecNo>=1)&&(aqnote->RecNo<=aqnote->RecordCount)) {

                    aqnote->Edit();
                    aqnote->FieldByName("benqicaigou")->AsInteger=aqnote->FieldByName("benqiorder")->AsInteger +nedaixiao->Value;
                    aqnote->FieldByName("benqidaixiao")->AsInteger= nedaixiao->Value;
                    aqnote->Post();

                    focusset(1);
           // }
       
           }

        }
}
bool Tfrmdaixiao::checknote()
{

    if (!aqnote->Active) {
       return false;
   }
     if (aqnote->RecordCount==0) {
       return false;
     }

     if (!aqHeader->Active) {
     return false;

     }
      return true;

}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaixiao::necaigouKeyPress(TObject *Sender, wchar_t &Key)
{
    if (Key=='\r') {
           if(checknote())
           {

            
            //编缉的是本期采购       benqidaixiao   benqicaigou   benqiorder   nedaixiao->Value
            aqnote->Edit();
            aqnote->FieldByName("benqidaixiao")->AsInteger=necaigou->Value-aqnote->FieldByName("benqiorder")->AsInteger;
            aqnote->FieldByName("benqicaigou")->AsInteger =necaigou->Value;
            aqnote->Post();

            focusset(2);
             }

        }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaixiao::SpeedButton2Click(TObject *Sender)
{
	if (GroupBox2->Visible) {
		GroupBox2->Visible = false;
                TADOQuery *aqselect = new TADOQuery(Application);
                aqselect->Connection = fcn;

                AnsiString values;
                if (chfoceset->Checked) {
                  values="1";
                }else values="0";

                if (chfsluru->Checked) {
                   values=values+"1";
                }else values=values+"0";

                    if (chfsamount->Checked) {
                   values=values+"1";
                }else values=values+"0";


                    if (chfsdiscount->Checked) {
                   values=values+"1";
                }else values=values+"0";


                    if (chjinjia->Checked) {
                   values=values+"1";
                }else values=values+"0";
                 aqselect->Close();
                aqselect->SQL->Clear();
                aqselect->SQL->Add("update dbo.SYS_BSSET set bk='"+values+"' where name = 'shengdaicaigoudingwei'");
                aqselect->ExecSQL();
                delete aqselect;

	}
	else
	{
    	GroupBox2->Visible = true;
	}
}
void Tfrmdaixiao::focusset(int type)
{

     if (rb1->Checked) {
     if ((cbautochang->Checked)&&(type!=5)) {
     if (aqnote->RecNo<aqnote->RecordCount) {
     //   aqnote->RecNo =  aqnote->RecNo+1;

       aqnote->Next();
        dbgrid->SelectedRows->Clear();
       dbgrid->SelectedRows->CurrentRowSelected = true;
     }

     }else if (type==5) {
            if (aqnote->RecNo<aqnote->RecordCount) {
          //  aqnote->RecNo =  aqnote->RecNo+1;
       aqnote->Next();
        dbgrid->SelectedRows->Clear();
       dbgrid->SelectedRows->CurrentRowSelected = true;
     }
           }


     }else if (rb2->Checked) {
        if ((cbautochang->Checked)&&(type!=5)) {
               aqnote->Prior();
                 dbgrid->SelectedRows->Clear();
              dbgrid->SelectedRows->CurrentRowSelected = true;
        }else if (type==5) {
         if (aqnote->RecNo>1) {
       //  aqnote->RecNo =  aqnote->RecNo-1;
              aqnote->Prior();
              dbgrid->SelectedRows->Clear();
              dbgrid->SelectedRows->CurrentRowSelected = true;
             }

              }

     }
         necaigou->Value=  aqnote->FieldByName("benqicaigou")->AsInteger;
        nedaixiao->Value=  aqnote->FieldByName("benqidaixiao")->AsInteger;
        neorder->Value= aqnote->FieldByName("orderdiscount")->AsFloat;
        cbzhuanfa->Text= aqnote->FieldByName("fahuofashi")->AsAnsiString;
       editbk->Text=aqnote->FieldByName("remarks")->AsAnsiString;

        switch(type)
        {
        case 1:

              if (chfsluru->Checked) {
                necaigou->SetFocus();
                necaigou->SelectAll();
                break;
              }
              if (chfsamount->Checked) {
                  neorder->SetFocus();
                neorder->SelectAll();
              break;
              }
              if (chfsdiscount->Checked) {
                 cbzhuanfa->SetFocus();
                cbzhuanfa->SelectAll();
              break;
              }
              if (chjinjia->Checked) {
                 editbk->SetFocus();
                editbk->SelectAll();
              break;
              }


        case 2:
            //  if (chfsluru->Checked) {

             // }
              if (chfsamount->Checked) {
                  neorder->SetFocus();
                neorder->SelectAll();
                break;
              }
              if (chfsdiscount->Checked) {
                cbzhuanfa->SetFocus();
                cbzhuanfa->SelectAll();
              break;
              }
              if (chjinjia->Checked) {
                editbk->SetFocus();
                editbk->SelectAll();
              break;
              }
              if (chfoceset->Checked) {
                 nedaixiao->SetFocus();
                 nedaixiao->SelectAll();
                 break;
              }
              necaigou->SelectAll();
              break;
        case 3:

              if (chfsdiscount->Checked) {
               cbzhuanfa->SetFocus();
                cbzhuanfa->SelectAll();
              break;
              }
              if (chjinjia->Checked) {
                 editbk->SetFocus();
                editbk->SelectAll();
              break;
              }
                 if (chfoceset->Checked) {
                 nedaixiao->SetFocus();
                 nedaixiao->SelectAll();
                 break;
              }
               if (chfsluru->Checked) {
                necaigou->SetFocus();
                necaigou->SelectAll();
                break;
              }
              neorder->SelectAll();
              break;
        case 4:

              if (chjinjia->Checked) {
                 editbk->SetFocus();
                editbk->SelectAll();
                break;
              }
                if (chfoceset->Checked) {
                 nedaixiao->SetFocus();
                 nedaixiao->SelectAll();
                 break;
              }
               if (chfsluru->Checked) {
                necaigou->SetFocus();
                necaigou->SelectAll();
                break;
              }
               if (chfsamount->Checked) {
                  neorder->SetFocus();
                neorder->SelectAll();
                break;
              }

        case 5:
       if (chfoceset->Checked) {
                 nedaixiao->SetFocus();
                 nedaixiao->SelectAll();
                 break;
              }
               if (chfsluru->Checked) {
                necaigou->SetFocus();
                necaigou->SelectAll();
                break;
              }
               if (chfsamount->Checked) {
                  neorder->SetFocus();
                neorder->SelectAll();
                break;
              }
                if (chfsdiscount->Checked) {
               cbzhuanfa->SetFocus();
                cbzhuanfa->SelectAll();
              break;
              }
        };







 }
//---------------------------------------------------------------------------

void __fastcall Tfrmdaixiao::neorderKeyPress(TObject *Sender, wchar_t &Key)
{
 if (Key=='\r') {
             if(!checknote()) return;

             
            //编缉的是本期采购       benqidaixiao   benqicaigou   benqiorder   nedaixiao->Value
            aqnote->Edit();
            aqnote->FieldByName("orderdiscount")->AsFloat =neorder->Value;
            aqnote->Post();

            focusset(3);


        }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaixiao::editbkKeyPress(TObject *Sender, wchar_t &Key)
{
    if (Key=='\r') {
              if(!checknote()) return;


            //编缉的是本期采购       benqidaixiao   benqicaigou   benqiorder   nedaixiao->Value
            aqnote->Edit();
            aqnote->FieldByName("remarks")->AsAnsiString =editbk->Text;
            aqnote->Post();
            focusset(5);


        }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaixiao::dbgridCellClick(TColumn *Column)
{
    if (!checknote()) return;
    necaigou->Value=  aqnote->FieldByName("benqicaigou")->AsInteger;
    nedaixiao->Value=  aqnote->FieldByName("benqidaixiao")->AsInteger;
    neorder->Value= aqnote->FieldByName("orderdiscount")->AsFloat;
    cbzhuanfa->Text= aqnote->FieldByName("fahuofashi")->AsAnsiString;
    editbk->Text=aqnote->FieldByName("remarks")->AsAnsiString;
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaixiao::cbzhuanfaKeyPress(TObject *Sender, wchar_t &Key)
{
//
    if (Key=='\r') {
              if(!checknote()) return;

         
            //编缉的是本期采购       benqidaixiao   benqicaigou   benqiorder   nedaixiao->Value
            aqnote->Edit();
            aqnote->FieldByName("fahuofashi")->AsAnsiString =cbzhuanfa->Text;
            aqnote->Post();
            focusset(4);


        }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaixiao::dbgridTitleClick(TColumn *Column)
{
             	if (aqnote->IsEmpty() ) {
    	return;
	}
	AnsiString qusort;
	qusort =  Column->FieldName + " ASC";
	if (aqnote->Sort == "") {
		aqnote->Sort =  Column->FieldName + " ASC";
	}
	else if (aqnote->Sort == qusort) {
		aqnote->Sort =  Column->FieldName + " DESC";
	}
	else
	{
		aqnote->Sort =  Column->FieldName + " ASC";
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaixiao::toolshowmainmenuClick(TObject *Sender)
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

void __fastcall Tfrmdaixiao::N7Click(TObject *Sender)
{

   	if ((!aqHeader->Active)||(SelectBkCatalogid==-1)) {
    	return;
	}



        int clientid=-1;
        Tfrmaddclient * frm = new Tfrmaddclient(Application,fcn,StgID);
        if(frm->ShowModal()==mrOk)
        {
           clientid = frm->getselectclient();
        }
        delete frm;

        ///
        if (clientid!=-1) {
            if (aqHeader->Active) {
            //先进行搜索

            TLocateOptions   Opts;
            Opts.Clear();
            Opts   <<   loPartialKey;
            AnsiString str = AnsiString(clientid);



           if(aqnote->Locate("clientid",str,Opts))
           { dbgrid->SelectedRows->CurrentRowSelected=true;}
           else{
                AnsiString sql;
                sql = "exec BS_NewDaiXiaoNoteforoneclient "+aqHeader->FieldByName("ID")->AsAnsiString+","+IntToStr(SelectBkCatalogid)+","+IntToStr(StgID)+","+IntToStr(clientid);

                TADOQuery *aqexe = new TADOQuery(Application);
                aqexe->Connection = fcn;
                aqexe->Close();
                aqexe->SQL->Clear();
                aqexe->SQL->Add(sql);
                aqexe->ExecSQL();
                delete aqexe;
                RefreshDetail();
           }

     }
        }




}

//---------------------------------------------------------------------------


void __fastcall Tfrmdaixiao::dbgridMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
// if (!sel)//非选择状态，记录当前位置
 //  {
     	if (aqnote->IsEmpty() ) {
    	return;
	}
     if (!Shift.Contains(ssShift)) {
     // bookmark = dbgrid->DataSource->DataSet->GetBookmark() ;
      oldrec= dbgrid->DataSource->DataSet->RecNo;
     // Sel = true ;
        }
  // }
      if (Shift.Contains(ssShift)) {
        currrec = dbgrid->DataSource->DataSet->RecNo;
       // dbgrid->SelectedRows->CurrentRowSelected = true;
        dbgrid->DataSource->DataSet->DisableControls();
        if (currrec>oldrec) {
           while(oldrec<dbgrid->DataSource->DataSet->RecNo  )
           {
              dbgrid->SelectedRows->CurrentRowSelected = true;
              dbgrid->DataSource->DataSet->Prior();
           }


        }else{

            while(oldrec>dbgrid->DataSource->DataSet->RecNo  )
           {
              dbgrid->SelectedRows->CurrentRowSelected = true;
              dbgrid->DataSource->DataSet->Next();
           }


        }
        dbgrid->SelectedRows->CurrentRowSelected = true;
       dbgrid->DataSource->DataSet->EnableControls();
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaixiao::nedaixiaoClick(TObject *Sender)
{
  nedaixiao->SelectAll();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaixiao::necaigouClick(TObject *Sender)
{
necaigou->SelectAll();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaixiao::neorderClick(TObject *Sender)
{
neorder->SelectAll();
}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaixiao::F1Click(TObject *Sender)
{
//
 AnsiString bkcatalogid;
   	if (aqnote->IsEmpty() ) {
		return;
	}
         bkcatalogid="-1";
        aqnote->DisableControls();

        if (dbgrid->SelectedRows->Count > 0) {
    	for (int i=0; i < dbgrid->SelectedRows->Count; i++)
		{
			aqnote->Bookmark = dbgrid->SelectedRows->Items[i];
			bkcatalogid = bkcatalogid + "," + aqnote->FieldByName("ID")->AsString;
		}
	}
	else
	{
		bkcatalogid = bkcatalogid + "," + aqnote->FieldByName("ID")->AsString;
	}
       aqnote->EnableControls();

        TClipboard *pClipboard = new TClipboard();
        pClipboard->Clear();
    pClipboard->AsText = bkcatalogid;
    delete pClipboard;


}
//---------------------------------------------------------------------------

void __fastcall Tfrmdaixiao::N10Click(TObject *Sender)
{
//
  AnsiString bkcatalogid;
     Richcopy->Text="";
     Richcopy->PasteFromClipboard();
     bkcatalogid=Richcopy->Text ;
     AnsiString sql,caigouid;
     if (aqHeader->IsEmpty()) {
         return;
     }
     if(bkcatalogid!="")
     {
         //是否已审核

            try
            {
            caigouid = aqHeader->FieldByName("ID")->AsAnsiString ;

            sql ="exec StickdataToCaigoushengdaiNote "+caigouid+",'"+bkcatalogid+"'";
            TADOQuery *aqaa=new TADOQuery(Application);
            aqaa->Connection  = fcn;
             aqaa->Close();
            aqaa->SQL->Clear();
            aqaa->SQL->Add(sql);
            aqaa->ExecSQL();
            RefreshDetail();
            }catch(...)
            {}
           //  RefreshHead(aqhd->FieldByName("ID")->AsInteger );


     }
}
//---------------------------------------------------------------------------

