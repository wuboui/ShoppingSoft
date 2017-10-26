#pragma once

#include "BaseClient.h"
#include "openssl/ssl.h"
#include "StaticUtility.h"
#include "CStringHash.h"

#include <list>
#include <hash_map>
#include <algorithm>
#include <iostream>
using namespace std;

class HttpsClient :	public BaseClient
{
public:
	HttpsClient(void);
	~HttpsClient(void);

public:
	BOOL ConnectToServer(const CString strServerUrl, const int nPort);
	BOOL LoginToServer(const CString strUsername, const CString strPasswd);
	BOOL LogoutOfServer();

	BOOL InitializeSocketContext();                            //!初始化套接字环境
	BOOL InitializeSslContext();                               //!初始化SSL环境
	BOOL SocketConnect();                                      //!Socket连接
	BOOL SslConnect();                                         //!SSL连接
	BOOL SendLoginPostData();							       //!发送登录数据
	void RecvLoginPostData(CString &cstrRecvData);             //!接收登录数据
	void ParseCookieFromRecvData(const CString cstrRecvData);  //!解析接收到的数据，获取cookie信息

	/*
	  @功能：获取密码和服务器端证
	  @注意：该操作是可选的，不影响下面的通信
	         只是为了安全性考虑
	 */
	BOOL SslGetCipherAndCertification();

public:
	WSADATA *wsaData;
	SOCKET  socketClient;
	SOCKADDR_IN *socketAddrClient;

	CString cstrServerUrl;                //!服务器地址
	int nServerPort;                      //!服务器端口
	CString cstrUserName;				  //!登录用户名
	CString cstrPassWord;                 //!登录密码

	SSL *ssl;
	SSL_CTX *sslCtx;
	SSL_METHOD *sslMethod;
	X509 *serverCertification;

	CString cstrSslCipher;
	CString cstrSslSubject;
	CString cstrSslIssuer;
	CString cstrCookieUid;

	hash_map<CString, CString, CStringHash>    hmapCookiesSet;       //!存放cookie信息的hash表
};

