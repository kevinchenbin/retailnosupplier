//---------------------------------------------------------------------------
 #ifdef USE_VCLDB
#define INC_VCLDB_HEADERS
#endif

#ifdef USE_VCLEXT
#define INC_VCLEXT_HEADERS
#endif

#ifdef USE_OLE
#define INC_OLE_HEADERS
#endif

#ifdef USE_ATL
#define INC_ATL_HEADERS
#endif
#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("userpurview\UnitStorToStor.cpp", frmStorToStor);
USEFORM("financial\Unitautojie.cpp", frmautojieshuan);
USEFORM("Unitpanbook.cpp", frmpanbook);
USEFORM("userpurview\AddUser.cpp", frmAddUser);
USEFORM("storagebsset.cpp", frmstoragebsset);
USEFORM("retailbsset.cpp", frmretailbsset);
USEFORM("common\MDIChild.cpp", frmMDIChild);
USEFORM("AreaSet.cpp", MemberAreaSet);
USEFORM("membermanager\CustomertypeSet.cpp", frmcustomertype);
USEFORM("Moneydiscount.cpp", frmMonerydiscount);
USEFORM("procureset.cpp", frmprocureset);
USEFORM("salebsset.cpp", frmsalebsset);
USEFORM("userpurview\UnitNewGroup.cpp", frmnewgroup);
USEFORM("UnitLog.cpp", frmLog);
USEFORM("storage\storagelocal.cpp", frmstorelocal);
USEFORM("diaoboset.cpp", frmdiaoboset);
USEFORM("bsquery\Notedetail.cpp", frmNotedetail);
USEFORM("Syspwdchange.cpp", frmsyspwdchange);
USEFORM("financial\Unitbalance.cpp", frmbalance);
USEFORM("financial\accoutnsdue.cpp", AccountDoe);
USEFORM("financial\accountquery.cpp", AccQuery);
USEFORM("orderbsset.cpp", frmorderbsset);
USEFORM("systemset.cpp", frmsystemset);
USEFORM("financial\Unitwanglai.cpp", frmwanglaizhang);
USEFORM("financial\Unitclientwanglai.cpp", frmclientwanglai);
USEFORM("unitprinttitle.cpp", frmprinttitle);
USEFORM("financial\accountdetail.cpp", AccDetail);
USEFORM("unitcfpandian.cpp", frmcfpandian);
USEFORM("ClientBackdot.cpp", frmClientBackdot);
USEFORM("userpurview\Unitfinduser.cpp", frmfinduser);
USEFORM("bsadmin\BIOrderManage\Unitfindbook.cpp", frmfindorderbook);
USEFORM("bsadmin\bookQuery.cpp", frmbookquery);
USEFORM("UnitPublicMsg.cpp", frmpublicMsg);
USEFORM("UnitTaskdetail.cpp", frmnewtask);
USEFORM("Teacher\Uniteachermanager.cpp", frmteachermanager);
USEFORM("Teacher\Unitteacher.cpp", frmteacher);
USEFORM("Document\Unitdocument.cpp", frmdocument);
USEFORM("bsadmin\BIOrderManage\UnitBIOrder.cpp", frmBIorder);
USEFORM("clientadddot.cpp", frmclientadddot);
USEFORM("UnitreceiverSelect.cpp", frmuserselect);
USEFORM("membermanager\MemberImport.cpp", FormMemImport);
USEFORM("common\QryNoteCodeForm1.cpp", frmQryNoteCode1);
USEFORM("financial\Unitweijieselect.cpp", frmselectjiedan);
USEFORM("storage\StockAdjust.cpp", frmStockAdjust);
USEFORM("userpurview\UnitpurviewManage.cpp", frmpurview);
USEFORM("MemberJifenMng.cpp", frmMemberjifen);
USEFORM("userpurview\UnitGroup.cpp", frmgroup);
USEFORM("userpurview\SpecialPasswordForm.cpp", frmSpecialPassword);
USEFORM("catalogadmin\Selecttype.cpp", frmselecttype);
USEFORM("membermanager\MemberClassSet.cpp", frmmemclassmg);
USEFORM("Unitkucunpandian.cpp", frmkucunpandian);
USEFORM("supplier\Staffdetail.cpp", frmStaffdetail);
USEFORM("userpurview\Unituser.cpp", frmuser);
USEFORM("stockalarmbsset.cpp", frmstockalarmbsset);
USEFORM("checkselbook.cpp", frmcatalogselect);
USEFORM("bsadmin\UnitSelectClient.cpp", frmselectClient);
USEFORM("membermanager\MemberCardaddvalue.cpp", frmaddvalue);
USEFORM("membermanager\MemberCardUnuse.cpp", frmMemberCardUnuse);
USEFORM("membermanager\MemberForm.cpp", frmMember);
USEFORM("common\QryNoteCodeForm.cpp", frmQryNoteCode);
USEFORM("storage\Stockalarm.cpp", frmalarm);
USEFORM("membermanager\MemberResult.cpp", frmMemberResult);
USEFORM("supplier\detailemessage.cpp", DetaileForm);
USEFORM("supplier\suppmanage.cpp", SuppMana);
USEFORM("supplier\CoustomerImport.cpp", FormCousImport);
USEFORM("membermanager\Unithuancard.cpp", frmhuancard);
USEFORM("membermanager\MemberCard.cpp", frmMemberCard);
USEFORM("LandForm.cpp", frmLand);
USEFORM("membermanager\RecordQuery.cpp", FormRecordQuery);
USEFORM("storage\StockalarmSet.cpp", frmalarmSet);
USEFORM("MainForm.cpp", frmMain);
USEFORM("membermanager\Unitjifendh.cpp", frmjifendh);
USEFORM("storage\NotCheckBook.cpp", frmNotCheckBook);
USEFORM("storage\localadjust.cpp", frmadjust);
USEFORM("membermanager\Unitchangeaddvalue.cpp", frmchangeaddvalue);
USEFORM("Unitsiglebook.cpp", frmsiglebook);
USEFORM("common\Print.cpp", frmPrint);
USEFORM("Unittuihuoset.cpp", frmtuihuoset);
USEFORM("Unitshengji.cpp", frmshengji);
USEFORM("common\ModalDialog.cpp", frmModalDialog);
USEFORM("supplier\Staffmanage.cpp", frmStaff);
USEFORM("membermanager\MemberCardchange.cpp", frmMemberCardChange);
USEFORM("financial\Unitestartsupclient.cpp", frmsupplierandclient);
USEFORM("financial\Unitweishenhe.cpp", frmweishenhe);
USEFORM("Unitabout.cpp", frmAboutsoftware);
USEFORM("financial\Unitaccountyfhz.cpp", accountyfhz);
USEFORM("Document\Unitnewfile.cpp", frmnewfile);
USEFORM("ClientDisforbook.cpp", frmclientdisforbook);
USEFORM("common\PwdForm.cpp", frmPwd);
USEFORM("Unitboolslect.cpp", frmselectbook);
USEFORM("Unitkemuset.cpp", frmkemuset);
USEFORM("Unitjizhang.cpp", frmjizhang);
USEFORM("storage\StockCheck.cpp", frmcheckstock);
USEFORM("Unitjizhangsearch.cpp", frmsearch);
USEFORM("financial\Unittishi.cpp", frmtishi);
USEFORM("UnitDataClear.cpp", Form2);
//---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TfrmMain), &frmMain);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
