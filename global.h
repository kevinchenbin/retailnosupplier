#ifndef GlobalH
#define GlobalH
 #include <DBGrids.hpp>
#include <vcl.h>
#include "LandForm.h"
#define WM_MYMESSAGE WM_USER+1
typedef enum
{
    MTBusiness = 1,
	MTStock,
	MTFinance1,
	MTCatalog,
	MTSell,
	MTCustomer,
    MTSystem
}ModuleType1;
bool Login(String name,String pwd,int& user, int& storage);
void AddEvent(int type,AnsiString SourceFrom,int user,int Stg,AnsiString Mg);
bool FindDog(int version);
class storage
{
   AnsiString Name;
   int ID;

};
struct PrintControl
{
   AnsiString name;
   float width;
};
class booklocal
{
   AnsiString Name;
   AnsiString StgID;
   AnsiString ID;
   AnsiString State;
};
static  int ShowMsg(HWND hWnd,AnsiString Texts,int type)
{
       int  fresult;
       fresult = 0;
	switch(type)
	{
	  case 0:
		fresult = MessageBox(hWnd,Texts.c_str() ,"��������ҵ�ǹ�ƽ̨-����" ,MB_ICONWARNING|MB_SYSTEMMODAL);  //����
		 break;
	  case 1:
		fresult =  MessageBox(hWnd,Texts.c_str() ,"��������ҵ�ǹ�ƽ̨-ѯ��" ,MB_ICONQUESTION|MB_SYSTEMMODAL|MB_OKCANCEL|MB_DEFBUTTON1);  //ѯ��
		 break;
	  case 2:
		fresult =  MessageBox(hWnd,Texts.c_str() ,"��������ҵ�ǹ�ƽ̨-����" ,MB_ICONERROR|MB_SYSTEMMODAL);  //����
		 break;
	  case 3:
		fresult =  MessageBox(hWnd,Texts.c_str() ,"��������ҵ�ǹ�ƽ̨-��ʾ" ,MB_ICONASTERISK|MB_SYSTEMMODAL);  //��ʾ
		 break;

          case 4:
		  fresult =  MessageBox(hWnd,Texts.c_str() ,"��������ҵ�ǹ�ƽ̨-ѯ��" ,MB_ICONQUESTION|MB_SYSTEMMODAL|MB_OKCANCEL|MB_DEFBUTTON1);  //ѯ��
		 break;
	}
        return fresult;

}

static void DBGrid2Word(TDBGrid *dbg, String strDocFile)
{
    if(!dbg->DataSource->DataSet->Active) // ���ݼ�û�д򿪾ͷ���
        return;
    Variant vWordApp, vTable, vCell;
    try
    {
        vWordApp = Variant::CreateObject("Word.Application");
    }
    catch(...)
    {
        MessageBox(0, "���� Word ����, ������û�а�װWord.",
                "DBGrid2Word", MB_OK | MB_ICONERROR);
        vWordApp = Unassigned;
        return;
    }
    // ����Word����
    vWordApp.OlePropertySet("Visible", false);
    // �½�һ���ĵ�
    vWordApp.OlePropertyGet("Documents").OleFunction("Add");
    //
    Variant vSelect = vWordApp.OlePropertyGet("Selection");
    // ����һ�����壬��С
    vSelect.OlePropertyGet("Font").OlePropertySet("Size", dbg->Font->Size);
    vSelect.OlePropertyGet("Font").OlePropertySet("Name", dbg->Font->Name.c_str());
    // Ҫ�����������
    int nRowCount(dbg->DataSource->DataSet->RecordCount + 1);
    nRowCount = nRowCount < 2? 2: nRowCount;
    // Ҫ�����������
    int nColCount(dbg->Columns->Count);
    nColCount = nColCount < 1? 1: nColCount;
    // ��Word�ĵ��в�����DBGrid��������������ͬ��һ�����
    vWordApp.OlePropertyGet("ActiveDocument").OlePropertyGet("Tables")
        .OleProcedure("Add",
        vSelect.OlePropertyGet("Range"),
        nRowCount, // ����
        nColCount, // ����
        1, // DefaultTableBehavior:=wdWord9TableBehavior
        0); // AutoFitBehavior:=wdAutoFitFixed
    // ����������
    vTable = vWordApp.OlePropertyGet("ActiveDocument").
        OleFunction("Range").OlePropertyGet("Tables").OleFunction("Item", 1);
    // ���õ�Ԫ��Ŀ��
    for(int i=0; i<nColCount; i++)
    {
        int nColWidth = dbg->Columns->Items[i]->Width;
        vTable.OlePropertyGet("Columns").OleFunction("Item", i + 1)
                .OlePropertySet("PreferredWidthType", 3); // wdPreferredWidthPoints
        vTable.OlePropertyGet("Columns").OleFunction("Item", i + 1)
                .OlePropertySet("PreferredWidth", nColWidth);
    }
    //----------------------------------------------------------------------------
    // ��Ǹ�������ʾ�����ˣ�Ϊ�˷�ֹ�������ε�ת���ߣ�ֻ���ڴ���Щ��Ϣ��
    // ���ߣ�ccrun(����) info@ccrun.com
    // ����ת�� C++Builder �о� - http://www.ccrun.com/article/go.asp?i=635&d=g75jbn
    //----------------------------------------------------------------------------
    // �Ƚ�����д��Word���
    for(int j=0; j<dbg->Columns->Count; j++)
    {
        vCell = vTable.OleFunction("Cell", 1, j + 1);
        vCell.OlePropertySet("Range", dbg->Columns->Items[j]->FieldName.c_bstr());
        // ������Ԫ�񱳾���ɫ // wdColorGray125
        vCell.OlePropertyGet("Shading")
                .OlePropertySet("BackgroundPatternColor", 14737632);
    }
    // ��DBGrid�е�����д��Word���
    dbg->DataSource->DataSet->First();
    for(int i=0; i<nRowCount; i++)
    {
        // 63 63 72 75 6E 2E 63 6F 6D
        for(int j=0; j<dbg->Columns->Count; j++)
        {
            vCell = vTable.OleFunction("Cell", i + 2, j + 1);
            vCell.OlePropertySet("Range",
                dbg->DataSource->DataSet->FieldByName(
                dbg->Columns->Items[j]->FieldName)->AsString.c_str());
        }
        dbg->DataSource->DataSet->Next();
    }
    // ����Word�ĵ����˳�
    vWordApp.OlePropertyGet("ActiveDocument")
            .OleProcedure("SaveAs", strDocFile.c_str());
    vWordApp.OlePropertyGet("ActiveDocument").OleProcedure("Close");
    Application->ProcessMessages();
    vWordApp.OleProcedure("Quit");
    Application->ProcessMessages();
    vWordApp = Unassigned;
    // ��������
    MessageBox(0, "DBGrid2Word ת������!",
            "DBGrid2Word", MB_OK | MB_ICONINFORMATION);
}

static AnsiString GetPYIndexChar(char *as_HzString)
{
    static   int   li_SecPosValue[]={1601,1637,1833,2078,2274,2302,2433,2594,2787,3106,3212,3472,3635,3722,3730,3858,4027,4086,4390,4558,4684,4925,5249};
    static   char*   lc_FirstLetter[]     =   {"A",   "B","C","D","E","F","G","H","J","K","L","M","N","O","P","Q","R","S","T","W","X","Y","Z"};
    static   char*   ls_SecondSecTable   =
    "CJWGNSPGCGNE[Y[BTYYZDXYKYGT[JNNJQMBSGZSCYJSYY[PGKBZGY[YWJKGKLJYWKPJQHY[W[DZLSGMRYPYWWCCKZNKYYGTTNJJNYKKZYTCJNMCYLQLYPYQFQRPZSLWBTGKJFYXJWZLTBNCXJJJJTXDTTSQZYCDXXHGCK[PHFFSS[YBGXLPPBYLL[HLXS[ZM[JHSOJNGHDZQYKLGJHSGQZHXQGKEZZWYSCSCJXYEYXADZPMDSSMZJZQJYZC[J[WQJBYZPXGZNZCPWHKXHQKMWFBPBYDTJZZKQHY"
    "LYGXFPTYJYYZPSZLFCHMQSHGMXXSXJ[[DCSBBQBEFSJYHXWGZKPYLQBGLDLCCTNMAYDDKSSNGYCSGXLYZAYBNPTSDKDYLHGYMYLCXPY[JNDQJWXQXFYYFJLEJPZRXCCQWQQSBNKYMGPLBMJRQCFLNYMYQMSQYRBCJTHZTQFRXQHXMJJCJLXQGJMSHZKBSWYEMYLTXFSYDSWLYCJQXSJNQBSCTYHBFTDCYZDJWYGHQFRXWCKQKXEBPTLPXJZSRMEBWHJLBJSLYYSMDXLCLQKXLHXJRZJMFQHXHWY"
    "WSBHTRXXGLHQHFNM[YKLDYXZPYLGG[MTCFPAJJZYLJTYANJGBJPLQGDZYQYAXBKYSECJSZNSLYZHSXLZCGHPXZHZNYTDSBCJKDLZAYFMYDLEBBGQYZKXGLDNDNYSKJSHDLYXBCGHXYPKDJMMZNGMMCLGWZSZXZJFZNMLZZTHCSYDBDLLSCDDNLKJYKJSYCJLKWHQASDKNHCSGANHDAASHTCPLCPQYBSDMPJLPZJOQLCDHJJYSPRCHN[NNLHLYYQYHWZPTCZGWWMZFFJQQQQYXACLBHKDJXDGMMY"
    "DJXZLLSYGXGKJRYWZWYCLZMSSJZLDBYD[FCXYHLXCHYZJQ[[QAGMNYXPFRKSSBJLYXYSYGLNSCMHZWWMNZJJLXXHCHSY[[TTXRYCYXBYHCSMXJSZNPWGPXXTAYBGAJCXLY[DCCWZOCWKCCSBNHCPDYZNFCYYTYCKXKYBSQKKYTQQXFCWCHCYKELZQBSQYJQCCLMTHSYWHMKTLKJLYCXWHEQQHTQH[PQ[QSCFYMNDMGBWHWLGSLLYSDLMLXPTHMJHWLJZYHZJXHTXJLHXRSWLWZJCBXMHZQXSDZP"
    "MGFCSGLSXYMJSHXPJXWMYQKSMYPLRTHBXFTPMHYXLCHLHLZYLXGSSSSTCLSLDCLRPBHZHXYYFHB[GDMYCNQQWLQHJJ[YWJZYEJJDHPBLQXTQKWHLCHQXAGTLXLJXMSL[HTZKZJECXJCJNMFBY[SFYWYBJZGNYSDZSQYRSLJPCLPWXSDWEJBJCBCNAYTWGMPAPCLYQPCLZXSBNMSGGFNZJJBZSFZYNDXHPLQKZCZWALSBCCJX[YZGWKYPSGXFZFCDKHJGXDLQFSGDSLQWZKXTMHSBGZMJZRGLYJB"
    "PMLMSXLZJQQHZYJCZYDJWBMYKLDDPMJEGXYHYLXHLQYQHKYCWCJMYYXNATJHYCCXZPCQLBZWWYTWBQCMLPMYRJCCCXFPZNZZLJPLXXYZTZLGDLDCKLYRZZGQTGJHHGJLJAXFGFJZSLCFDQZLCLGJDJCSNZLLJPJQDCCLCJXMYZFTSXGCGSBRZXJQQCTZHGYQTJQQLZXJYLYLBCYAMCSTYLPDJBYREGKLZYZHLYSZQLZNWCZCLLWJQJJJKDGJZOLBBZPPGLGHTGZXYGHZMYCNQSYCYHBHGXKAMTX"
    "YXNBSKYZZGJZLQJDFCJXDYGJQJJPMGWGJJJPKQSBGBMMCJSSCLPQPDXCDYYKY[CJDDYYGYWRHJRTGZNYQLDKLJSZZGZQZJGDYKSHPZMTLCPWNJAFYZDJCNMWESCYGLBTZCGMSSLLYXQSXSBSJSBBSGGHFJLYPMZJNLYYWDQSHZXTYYWHMZYHYWDBXBTLMSYYYFSXJC[DXXLHJHF[SXZQHFZMZCZTQCXZXRTTDJHNNYZQQMNQDMMG[YDXMJGDHCDYZBFFALLZTDLTFXMXQZDNGWQDBDCZJDXBZGS"
    "QQDDJCMBKZFFXMKDMDSYYSZCMLJDSYNSBRSKMKMPCKLGDBQTFZSWTFGGLYPLLJZHGJ[GYPZLTCSMCNBTJBQFKTHBYZGKPBBYMTDSSXTBNPDKLEYCJNYDDYKZDDHQHSDZSCTARLLTKZLGECLLKJLQJAQNBDKKGHPJTZQKSECSHALQFMMGJNLYJBBTMLYZXDCJPLDLPCQDHZYCBZSCZBZMSLJFLKRZJSNFRGJHXPDHYJYBZGDLQCSEZGXLBLGYXTWMABCHECMWYJYZLLJJYHLG[DJLSLYGKDZPZXJ"
    "YYZLWCXSZFGWYYDLYHCLJSCMBJHBLYZLYCBLYDPDQYSXQZBYTDKYXJY[CNRJMPDJGKLCLJBCTBJDDBBLBLCZQRPPXJCJLZCSHLTOLJNMDDDLNGKAQHQHJGYKHEZNMSHRP[QQJCHGMFPRXHJGDYCHGHLYRZQLCYQJNZSQTKQJYMSZSWLCFQQQXYFGGYPTQWLMCRNFKKFSYYLQBMQAMMMYXCTPSHCPTXXZZSMPHPSHMCLMLDQFYQXSZYYDYJZZHQPDSZGLSTJBCKBXYQZJSGPSXQZQZRQTBDKYXZK"
    "HHGFLBCSMDLDGDZDBLZYYCXNNCSYBZBFGLZZXSWMSCCMQNJQSBDQSJTXXMBLTXZCLZSHZCXRQJGJYLXZFJPHYMZQQYDFQJJLZZNZJCDGZYGCTXMZYSCTLKPHTXHTLBJXJLXSCDQXCBBTJFQZFSLTJBTKQBXXJJLJCHCZDBZJDCZJDCPRNPQCJPFCZLCLZXZDMXMPHJSGZGSZZQLYLWTJPFSYASMCJBTZKYCWMYTCSJJLJCQLWZMALBXYFBPNLSFHTGJWEJJXXGLLJSTGSHJQLZFKCGNNNSZFDEQ"
    "FHBSAQTGYLBXMMYGSZLDYDQMJJRGBJTKGDHGKBLQKBDMBYLXWCXYTTYBKMRTJZXQJBHLMHMJJZMQASLDCYXYQDLQCAFYWYXQHZ";
    AnsiString   result   =   "";
    int   H,L,W;
    unsigned   stringlen   =   strlen(as_HzString);

    for(int     i   =   0;   i   <   stringlen;   i   ++   )
    {
       H   =   (unsigned   char)(as_HzString[i]);
       L   =   (unsigned   char)(as_HzString[i+1]);
       if(H   <   0xA1   ||   L   <   0xA1)
       {
           result   +=   as_HzString[i];
           continue;
       }
       else   W   =   (H   -   160)   *   100   +   L   -   160;
       if(W   >   1600   &&   W   <   5590)
       {
             for(int   j   =   22;   j   >=   0;   j   --)
                if(W   >=   li_SecPosValue[j])
                {
                    result   +=   lc_FirstLetter[j];
                    i++;
                    break;
                }
                continue;
       }
       else
       {
         i++;
         W   =   (   H   -   160   -   56   )*94   +   L   -   161;
         if(W   >=   0   &&   W   <=   3007)
            result   +=   ls_SecondSecTable[W];
         else
         {
            result   +=   (char)H;
            result   +=   (char)L;
         }
       }
    }
    return   result;
}

static int GetVersionNum()
{

   	 AnsiString configfile;
         int version;
	  configfile =  ExtractFilePath(Application->ExeName) + "dbconfig" +  ".INI" ;
	  TIniFile *ini;
	   ini   = new    TIniFile(configfile);
           version = ini->ReadInteger("dbserver","Version",0);
	   delete ini;
           return version;

}
#endif
