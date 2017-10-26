#pragma once

#include "BaseClient.h"
#include "StaticUtility.h"
#include "CStringHash.h"

#include <WinSock2.h>
#include <hash_map>
#include <list>
#include <algorithm>

using namespace std;

class SocketClient : public BaseClient
{
public:
	SocketClient(void);
	~SocketClient(void);

public:
	BOOL ConnectToServer(const CString strServerUrl, const int nPort);
	BOOL LoginToServer(const CString strUsername, const CString strPasswd);
	BOOL LogoutOfServer();

	BOOL InitializeContext();  //!初始化SOCKET上下文
	BOOL Connect();            //!连接服务端
	BOOL SendPostData();       //!发送数据（登）
	void ParseCookieFromRecvData(const CString cstrRecvData);  //!解析接收到的数据，获取cookie信息
public:
	WSADATA * wsaData;
	SOCKET socketClient;
	SOCKADDR_IN * socketAddrClient;

	CString cstrServerUrl;         //!服务器地址
	int nServerPort;               //!服务器端口
	CString cstrUserName;          //!登录用户名
	CString cstrPassWord;          //!登录密码

	CString cstrCookieUid;          //!cookie中返回的用户UID

	hash_map<CString, CString, CStringHash>    hmapCookiesSet;       //!存放cookie信息的hash表
};

