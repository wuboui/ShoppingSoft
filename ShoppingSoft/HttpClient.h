#pragma once
/************************************************************************/
/* ����MFC������װHTTP����                                                                     */
/************************************************************************/

#include <afxinet.h>
#include <string>
#include <list>

#include "BaseClient.h"
using namespace std;

class HttpClient : public BaseClient
{
public:
	HttpClient(void);
	~HttpClient(void);

public:
	BOOL ConnectToServer(const CString strServerUrl, const int nPort);
	BOOL LoginToServer(const CString strUsername, const CString strPasswd);
	BOOL LogoutOfServer();
	void ClearHandle();
	void GetCookieDatas(list<CString> &lstCookies);

public:
	BOOL        bIsPost;                       //!�Ƿ�ΪPOST����
	CString      strServerUrl;                  //!�����������URL��ַ
	CInternetSession     *pSession;            //!HTTP�Ự
	CHttpConnection      *pConnection;         //!����HTTP������������
	CHttpFile            *pHttpFile;           //!��дHTTP������

	list<CString>        lstCookiesList;       //!���cookie��Ϣ
};

