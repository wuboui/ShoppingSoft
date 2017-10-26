#include "StdAfx.h"
#include "HttpClient.h"


HttpClient::HttpClient(void):
            pConnection(NULL),
			pHttpFile(NULL)
{
	//!创建会话，并设置会话选项
	pSession = new CInternetSession(_T("session"), 0, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, INTERNET_FLAG_DONT_CACHE);
	pSession->SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 1000 * 20);
	pSession->SetOption(INTERNET_OPTION_CONNECT_BACKOFF, 1000);
	pSession->SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);
}


HttpClient::~HttpClient(void)
{
    //!句柄销毁，资源释放
	if(NULL != pConnection)
	{
		pConnection->Close();
		delete pConnection;
	}

	if(NULL != pSession)
	{
		pSession->Close();
		delete pSession;
	}
}

BOOL HttpClient::ConnectToServer(const CString strServerUrl, const int nPort = 80)
{
	try
	{
		pConnection = pSession->GetHttpConnection(strServerUrl, 0, nPort, NULL,NULL);
	}
	catch(CInternetException* e)
	{
		if (pConnection)
		{
			pConnection->Close();
			pConnection = NULL;
		}

		e->m_dwContext;
		e->Delete();

		return FALSE;
	}

	return TRUE;
}

BOOL HttpClient::LoginToServer(const CString strUsername, const CString strPasswd)
{
	try
	{
		CString strPostData ;
		strPostData.Format(_T("redirect=&username=%s&password=%s&auto_login=checked"), strUsername, strPasswd);
		strPostData += "&submit=%E7%99%BB%E5%BD%95";
		
		pHttpFile = pConnection->OpenRequest(CHttpConnection::HTTP_VERB_POST, _T("/user/login"));

		//!请求头
		pHttpFile->AddRequestHeaders(_T("Host: account.vsochina.com\r\n"));
		pHttpFile->AddRequestHeaders(_T("User-Agent: Mozilla/5.0 (Windows NT 6.3; WOW64; rv:35.0) Gecko/20100101 Firefox/35.0\r\n"));
		pHttpFile->AddRequestHeaders(_T("Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"));
		pHttpFile->AddRequestHeaders(_T("Accept-Language: zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3\r\n"));
		pHttpFile->AddRequestHeaders(_T("Accept-Encoding: gzip, deflate\r\n"));
	    pHttpFile->AddRequestHeaders(_T("DNT: 1\r\n"));
		pHttpFile->AddRequestHeaders(_T("Referer: http://account.vsochina.com/user/login\r\n"));
		pHttpFile->AddRequestHeaders(_T("Connection: Keep-Alive\r\n"));
		pHttpFile->AddRequestHeaders(_T("Content-Type: application/x-www-form-urlencoded\r\n"));
		pHttpFile->AddRequestHeaders(_T("Content-Length: 90\r\n"));

		pHttpFile->SendRequest(NULL, 0, (LPVOID)strPostData.GetBuffer(), strPostData.GetLength());

		DWORD nReturnStatus;
		pHttpFile->QueryInfoStatusCode(nReturnStatus);

		if(HTTP_STATUS_OK == nReturnStatus)
		{
			//!接收网页返回的信息
			//CString strResponse, strLine;
			//while(pHttpFile->ReadString(strLine))
			//{
			//	strResponse += strLine + "\r\n";
			//}

			char strCookie[1000];
			DWORD dw;
			pHttpFile->QueryInfo(HTTP_QUERY_RAW_HEADERS_CRLF, (LPVOID)strCookie, &dw);

			
			//pSession->GetCookie("account.vsochina.com/user/login", _T("vso_uname"), strCookieUsername);
			
			MessageBoxA(NULL, "登录成功!","友情提示", MB_OK);
		}
		else
		{
			MessageBoxA(NULL, "登录失败，请重新登陆!","友情提示", MB_OK);
			ClearHandle();
			return FALSE;
		}
	}
	catch(CInternetException * e)
	{
		e->m_dwContext;
		e->Delete();
		ClearHandle();
		return FALSE;
	}

	return TRUE;
}

BOOL HttpClient::LogoutOfServer()
{
	return FALSE;
}

void HttpClient::GetCookieDatas(list<CString> &lstCookies)
{

}

void HttpClient::ClearHandle()
{
	if(NULL != pHttpFile)
	{
		pHttpFile->Close();
		pHttpFile = NULL;
	}

	if (NULL != pConnection)
	{
		pConnection->Close();
		pConnection = NULL;
	}

	if (NULL != pSession)
	{
		pSession->Close();
		pSession = NULL;
	}
}
