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

	BOOL InitializeSocketContext();                            //!��ʼ���׽��ֻ���
	BOOL InitializeSslContext();                               //!��ʼ��SSL����
	BOOL SocketConnect();                                      //!Socket����
	BOOL SslConnect();                                         //!SSL����
	BOOL SendLoginPostData();							       //!���͵�¼����
	void RecvLoginPostData(CString &cstrRecvData);             //!���յ�¼����
	void ParseCookieFromRecvData(const CString cstrRecvData);  //!�������յ������ݣ���ȡcookie��Ϣ

	/*
	  @���ܣ���ȡ����ͷ�������֤
	  @ע�⣺�ò����ǿ�ѡ�ģ���Ӱ�������ͨ��
	         ֻ��Ϊ�˰�ȫ�Կ���
	 */
	BOOL SslGetCipherAndCertification();

public:
	WSADATA *wsaData;
	SOCKET  socketClient;
	SOCKADDR_IN *socketAddrClient;

	CString cstrServerUrl;                //!��������ַ
	int nServerPort;                      //!�������˿�
	CString cstrUserName;				  //!��¼�û���
	CString cstrPassWord;                 //!��¼����

	SSL *ssl;
	SSL_CTX *sslCtx;
	SSL_METHOD *sslMethod;
	X509 *serverCertification;

	CString cstrSslCipher;
	CString cstrSslSubject;
	CString cstrSslIssuer;
	CString cstrCookieUid;

	hash_map<CString, CString, CStringHash>    hmapCookiesSet;       //!���cookie��Ϣ��hash��
};

