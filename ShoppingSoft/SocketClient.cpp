#include "StdAfx.h"
#include "SocketClient.h"


SocketClient::SocketClient(void):
              wsaData(NULL),
		      socketClient(NULL),
			  socketAddrClient(NULL)
{
}


SocketClient::~SocketClient(void)
{
	if (NULL != socketClient)
	{
		closesocket(socketClient);
		socketClient = NULL;
	}

	WSACleanup();
}

BOOL SocketClient::ConnectToServer(const CString strServerUrl, const int nPort)
{
	cstrServerUrl = strServerUrl;
	nServerPort = nPort;
	BOOL bRet = FALSE;

	do 
	{
		if (!InitializeContext())
		{
			break;
		}

		if(!Connect())
		{
			break;
		}

		bRet = TRUE;
	} while (FALSE);
	return bRet;
}

BOOL SocketClient::LoginToServer(const CString strUsername, const CString strPasswd)
{
	cstrUserName = strUsername;
	cstrPassWord = strPasswd;
	BOOL bRet = FALSE;

	do 
	{
		if (!SendPostData())
		{
			break;
		}

		bRet = TRUE;
	} while (FALSE);

	return bRet;
}

BOOL SocketClient::LogoutOfServer()
{
	return FALSE;
}

BOOL SocketClient::InitializeContext()
{
	BOOL bRet = FALSE;
	wsaData = new WSADATA;
	WORD wVersion = MAKEWORD(2, 2);

	do 
	{
		if(0 != WSAStartup(wVersion, wsaData))
		{
			break;
		}

		if(LOBYTE( wsaData->wVersion ) != 2 || HIBYTE( wsaData->wVersion ) != 2 )
		{
			WSACleanup();
			break;
		}

		LPHOSTENT lpHostTent;
		lpHostTent = gethostbyname(cstrServerUrl);
		if (NULL == lpHostTent)
		{
			break;
		}

		socketClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (socketClient == INVALID_SOCKET)
		{
			WSACleanup();
			break;
		}

		socketAddrClient = new SOCKADDR_IN;
		socketAddrClient->sin_family = AF_INET;
		socketAddrClient->sin_port = htons(nServerPort);
		socketAddrClient->sin_addr = *((LPIN_ADDR)*lpHostTent->h_addr_list);
		memset(socketAddrClient->sin_zero, 0, sizeof(socketAddrClient->sin_zero));

		bRet = TRUE;
	} while (FALSE);

	return bRet;
}

BOOL SocketClient::Connect()
{
	BOOL bRet = FALSE;

	do 
	{
		if (SOCKET_ERROR == connect(socketClient, (LPSOCKADDR)socketAddrClient, sizeof(SOCKADDR_IN)))
		{
			 int nErrorCode = WSAGetLastError();
			closesocket(socketClient);
			break;
		}

		bRet = TRUE;
	} while (FALSE);

	return bRet;
}

BOOL SocketClient::SendPostData()
{
	CString cstrSendData;
	CString cstrSendParam = "redirect=&username="+cstrUserName+"&password="+cstrPassWord+"&auto_login=checked&submit=%E7%99%BB%E5%BD%95";
	BOOL bRet = FALSE;

	CString cstrSendParamLen;
	cstrSendParamLen.Format("%d", cstrSendParam.GetLength());

	cstrSendData = "POST http://account.vsochina.com/user/login HTTP/1.1\r\n";
	cstrSendData += "Host: account.vsochina.com\r\n";
	cstrSendData += "User-Agent: Mozilla/5.0 (Windows NT 6.3; WOW64; rv:35.0) Gecko/20100101 Firefox/35.0\r\n";
	cstrSendData += "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n";
	cstrSendData += "Accept-Language: zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3\r\n";
	cstrSendData += "Accept-Encoding: gzip, deflate\r\n";
	cstrSendData += "DNT: 1\r\n";
	cstrSendData += "Referer: http://account.vsochina.com/user/login\r\n";
	cstrSendData += "Connection: keep-alive\r\n";
	cstrSendData += "Content-Type: application/x-www-form-urlencoded\r\n";
	cstrSendData += "Content-Length: " + cstrSendParamLen +"\r\n";
	cstrSendData += "\r\n";
	cstrSendData += cstrSendParam;

	CString cstrRecvData;
	do 
	{
		if (-1 == send(socketClient, cstrSendData.GetBuffer(), cstrSendData.GetLength(), 0))
		{
			break;
		}

		char recvData[1000] = {0};
		int nRecvLen;

		while((nRecvLen = recv(socketClient, recvData, sizeof(recvData), 0)) > 0)
		{
			cstrRecvData += recvData;
		}

		if (cstrRecvData.GetLength() == 0)
		{
			break;
		}

		ParseCookieFromRecvData(cstrRecvData);

		//!判断返回的COOKIE信息中，UID是否存在
		if (cstrCookieUid.IsEmpty())
		{
			break;
		}

		bRet = TRUE;
	} while (FALSE);


	return bRet;
}

void SocketClient::ParseCookieFromRecvData(const CString cstrRecvData)
{
	list<CString> lstCookiesLine;        //!存放Set-Cookie的一行，例：Set-Cookie: vso_uname=houqd_1111;
	CString cstrFind = "Set-Cookie:";    //!查找标记
	CString cstrSeperator = "\r\n";      //!以"\r\n"分割号来分割字符串

	int nPos = 0;
	int nStart = cstrRecvData.Find(cstrSeperator);

	while(nStart != -1)
	{
		CString cstrSessionLine = cstrRecvData.Mid(nPos, nStart - nPos + 1);

		if (cstrSessionLine.Find(cstrFind) != -1)
		{
			CString cstrRealRecord = cstrSessionLine.Right(cstrSessionLine.GetLength() - cstrFind.GetLength() - 3);
			list<CString>::iterator it = find(lstCookiesLine.begin(), lstCookiesLine.end(), cstrRealRecord);
			if (it == lstCookiesLine.end())
			{
				lstCookiesLine.push_back(cstrRealRecord);
			}
		}

		nPos = nStart;
		nStart = cstrRecvData.Find(cstrSeperator, nPos + 2);
	}

	//!根据每行获取的cookie值，解析为key-value的形式
	vector<CString> vecCookieSet;
	for (list<CString>::iterator it = lstCookiesLine.begin(); it != lstCookiesLine.end(); it++)
	{
		CString cstrCookies = *it;
		CString cstrSeperator = ";";
		StaticUtility::StringSplit(cstrCookies, cstrSeperator, vecCookieSet);
	}

	vector<CString> vecTemp;
	for (vector<CString>::iterator it = vecCookieSet.begin(); it != vecCookieSet.end(); it++)
	{
		vecTemp.clear();
		CString cstrOneCookies = *it;
		CString cstrSeperator = "=";

		StaticUtility::StringSplit(cstrOneCookies, cstrSeperator, vecTemp);
		CString cstrKey = vecTemp[0];
		CString cstrVal = vecTemp[1];

		if(cstrKey.Compare("vso_uid") == 0)
		{
			cstrCookieUid = cstrVal;
			break;
		}

		//if (vecTemp.size() == 2 && hmapCookiesSet.find(vecTemp[0]) == hmapCookiesSet.end())
		//{
		//	hmapCookiesSet.insert(hash_map<CString, CString>::value_type(cstrKey, cstrVal));
		//}
	}
}