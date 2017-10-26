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

	BOOL InitializeContext();  //!��ʼ��SOCKET������
	BOOL Connect();            //!���ӷ����
	BOOL SendPostData();       //!�������ݣ��ǣ�
	void ParseCookieFromRecvData(const CString cstrRecvData);  //!�������յ������ݣ���ȡcookie��Ϣ
public:
	WSADATA * wsaData;
	SOCKET socketClient;
	SOCKADDR_IN * socketAddrClient;

	CString cstrServerUrl;         //!��������ַ
	int nServerPort;               //!�������˿�
	CString cstrUserName;          //!��¼�û���
	CString cstrPassWord;          //!��¼����

	CString cstrCookieUid;          //!cookie�з��ص��û�UID

	hash_map<CString, CString, CStringHash>    hmapCookiesSet;       //!���cookie��Ϣ��hash��
};

