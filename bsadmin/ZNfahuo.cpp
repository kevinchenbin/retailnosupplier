//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ZNfahuo.h"
#include "orderpipeiresurt.h"
#include "firstfahuo.h"
#include "WholesaleMngForm.h"
#include "UnitOrdertofahuo.h"
#include "unitinitfahuo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma link "MDIChild"
TfrmZNfahuo *frmZNfahuo;
//---------------------------------------------------------------------------
__fastcall TfrmZNfahuo::TfrmZNfahuo(TComponent* Owner)
	: TfrmMDIChild(Owner)
{
	groupid = -1;
	firstfahuo = -1;
	confirmfahuo = -1;
	headgroupid = -1;
	detail = false;
}
//---------------------------------------------------------------------------
void TfrmZNfahuo::Init(LandInfo* li)
{
	TfrmMDIChild::Init(li);
	linfo.app = li->app ;
	linfo.con = li->con ;
	linfo.userID = li->userID ;
	linfo.UserName = li->UserName ;
	linfo.storageID = li->storageID ;
	linfo.FormatStr = li->FormatStr ;
	aq->Connection = m_con;
	query->Connection = li->con ;
	cmdAddNtHeader->Connection = m_con ;
	cmdAddNote->Connection = m_con ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNfahuo::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree ;
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNfahuo::SpeedButton3Click(TObject *Sender)
{
	AnsiString sql;
	if (headgroupid == -1) {
		sql = "select max(groupid) as groupid from BS_Tmpheader ";
		query->Close();
		query->SQL->Clear();
		query->SQL->Add(sql);
		query->Open();
		if (query->IsEmpty() ) {
			headgroupid = 1;
		}
		else
		{
			headgroupid = query->FieldByName("groupid")->AsInteger + 1;
		}
	}

	TfrmOrdertoFahuo *frm = new TfrmOrdertoFahuo(Application,linfo.con,linfo.storageID,linfo.userID,headgroupid);
	if (frm->ShowModal() == mrOk ) {
		Tfrmfirstfahuo * fram = new Tfrmfirstfahuo(Application);
		fram->groupid = headgroupid;
		fram->Init(&linfo);
		if (fram->ShowModal() ==  mrOk ) {
			Tfrminitfahuo *frm = new Tfrminitfahuo(Application);
			frm->fgroupid = headgroupid;
			frm->Init(&linfo);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmZNfahuo::SpeedButton2Click(TObject *Sender)
{
	Tfrminitfahuo *frm = new Tfrminitfahuo(Application);
	frm->fgroupid = 0;
	frm->Init(&linfo);
}
//---------------------------------------------------------------------------

