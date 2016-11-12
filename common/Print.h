//---------------------------------------------------------------------------

#ifndef PrintH
#define PrintH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RpBase.hpp"
#include "RpDefine.hpp"
#include "RpRave.hpp"
#include "RpSystem.hpp"
#include "RpCon.hpp"
#include "RpConDS.hpp"
#include <ADODB.hpp>
#include <DB.hpp>
#include "global.h"
#include "frxClass.hpp"
//---------------------------------------------------------------------------
class TfrmPrint : public TForm
{
__published:	// IDE-managed Components
	TRvSystem *RvSystem1;
	TRvProject *prjretail;
	TRvDataSetConnection *conRVretail;
	TADOQuery *aquerybs;
	TfrxReport *frxre;
private:	// User declarations
public:		// User declarations
	__fastcall TfrmPrint(TComponent* Owner);
	void RetailPrint(String ID,TADOConnection* con,int stgid);
	void RetailjiaojiePrint(String userid,TADOConnection* con,int stgid);
        void moneyboxopen();

        };
//---------------------------------------------------------------------------
extern PACKAGE TfrmPrint *frmPrint;
//---------------------------------------------------------------------------
#endif
