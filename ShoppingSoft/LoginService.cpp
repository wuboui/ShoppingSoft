#include "StdAfx.h"
#include "LoginService.h"


LoginService::LoginService(void):
              strUsername(""),
			  strPassword(""),
			  //strUrl("account.vsochina.com")
			  strUrl("account.xiaomi.com")
{
}

LoginService::LoginService(const CString strName, const CString strPass):
			  strUrl("account.xiaomi.com")
{
	strUsername = strName;
	strPassword = strPass;
	//pHttpClient = new HttpClient;     //!http��ʽ��¼
	//pHttpClient = new SocketClient;   //!socket��ʽ��¼
	pHttpClient = new HttpsClient;      //!https��ʽ��¼
}

LoginService::~LoginService(void)
{
}

BOOL LoginService::Login()
{
	BOOL bRet = FALSE;
	do 
	{
		if (NULL == pHttpClient)
		{
			break;
		}

		if (!pHttpClient->ConnectToServer(strUrl, 443))
		{
			break;
		}

		if (!pHttpClient->LoginToServer(strUsername, strPassword))
		{
			break;
		}

		bRet = TRUE;
	} while (FALSE);

	return bRet;
}

BOOL LoginService::Logout()
{
	return TRUE;
}
