#pragma once

/************************************************************************/
/*��GET��POST���͵Ļ��࣬���ڹ涨�����������ʵ�ֵĽӿ�                                                                      */
/************************************************************************/

class BaseClient
{
public:
	BaseClient(void);
	~BaseClient(void);

public:
	virtual BOOL ConnectToServer(const CString strServerUrl, const int nPort) = 0;  //!���ӵ�������
	virtual BOOL LoginToServer(const CString strUsername, const CString strPasswd) = 0;
	virtual BOOL LogoutOfServer() = 0;
};

