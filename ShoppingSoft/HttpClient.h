#pragma once
/************************************************************************/
/* 利用MFC的类库封装HTTP请求                                                                     */
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
	BOOL        bIsPost;                       //!是否为POST请求
	CString      strServerUrl;                  //!请求服务器的URL地址
	CInternetSession     *pSession;            //!HTTP会话
	CHttpConnection      *pConnection;         //!管理到HTTP服务器的连接
	CHttpFile            *pHttpFile;           //!读写HTTP服务器

	list<CString>        lstCookiesList;       //!存放cookie信息
};

