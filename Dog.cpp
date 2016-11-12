//---------------------------------------------------------------------------


#pragma hdrstop
#include "AES.h"
#include "Dog.h"

//---------------------------------------------------------------------------
int ReadDog::ReadDevNumber()
{
	 res = LIV_get_hardware_info(pdhandle,&info);
	 if (res) {
		 LIV_close(pdhandle);
		 return 0;
	 }
	 return info.developerNumber ;

}

String ReadDog::ReadDogInfo()
{
	/*	   char msg[100];

 unsigned char data[100] = "Hi SenseLock!Hi SenseLock!Hi SenseLock!Hi SenseLock!Hi SenseLock!Hi SenseLock!";

	memset(data, 0, 100);
	res = LIV_read(pdhandle, 0, data);
	if(res) {
	   // LIV_close(pdhandle);
	  //	wsprintf(msg,"读区块0失败。 错误代码：%d(%s)", res, error[res]);
	//	ListBox1->Items->Add(msg);
        return msg;
	}*/

	byte pd4[16]={0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16};

	memset(ciphtext,0X00,16);


	 unsigned char data[512] ="";
		memset(data, 0, 512);


	char a[17];
	res = LIV_read(pdhandle, 0, data);

	if(res) {
	LIV_close(pdhandle);
	return "";
	}
	 byte pd2[16];
	 memset(pd2,0X00,16);
	 for (int i=0; i < 16; i++) {
			 ciphtext[i] =data[i];
	   }


	 AES *pd = new AES(0,pd4);
	 pd->InvCipher(ciphtext,pd2);
	 delete pd;


	   for (int i=0; i < 16; i++) {
			 a[i] =pd2[i];
	   }
	   a[16]='\0';
		return a;

}
int ReadDog::OpenDog()
{
  //	res =  LIV_open(0x43445044,0,&pdhandle);
   res =  LIV_open(0x53584a43,0,&pdhandle);
   if (pdhandle==0) {
     res =  LIV_open(0x43445044,0,&pdhandle);
   }
	if(res) {
	  // LIV_close(pdhandle);
		return -1;
	}
	res =  LIV_passwd(pdhandle,0,(unsigned char *)"391928ch");
	if (res) {
	  //	LIV_close(pdhandle);
		return -2;
	}
	return res;
}

int ReadDog::CloseDog()
{
   if (pdhandle!=0) {
	 res =  LIV_close(pdhandle);
	if(res) {
	   return 0;
	}
	  return 1;
   } else return 1;


}
boolean ReadDog::FindSeier()
{
   boolean re;
   re=false;
   char seier[8];
	int res = LIV_get_hardware_info(pdhandle,&info);
	 if (res) {
		 LIV_close(pdhandle);
		 return 0;
	 }
	 for (int t=0; t < 8; t++) {
		seier[t] =info.serialNumber[t]  ;
	 }


		AnsiString seierlist ="00142976|01093659|01093657|01093699|01093653|01093724|01888951|01093676|01888937|01888924|01889001|01888979|";
		TStringList *List=new TStringList();
		List->Delimiter='|'; //指定分隔符
		List->StrictDelimiter=true; //强制使用上面指定的字符来分隔字符串
		List->DelimitedText=seierlist;
		for(int i=0,ci=List->Count;i<ci;++i)
		{
			if (List->Strings[i] == seier)
			{
				re=true;
                break;
			}

		}

    return re;
   /*	byte pd4[16]={0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16};

	memset(ciphtext,0X00,16);
			  AES *pd = new AES(0,pd4);
	 pd->Cipher((unsigned char *)(seierlist[0].c_str()),ciphtext);
	 pd->InvCipher(ciphtext,plantext);
	 delete pd; */

}

#pragma package(smart_init)
