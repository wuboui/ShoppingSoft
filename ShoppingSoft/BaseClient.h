#pragma once

/************************************************************************/
/*各GET和POST类型的基类，用于规定各派生类必须实现的接口                                                                      */
/************************************************************************/

class BaseClient
{
public:
	BaseClient(void);
	~BaseClient(void);

public:
	virtual BOOL ConnectToServer(const CString strServerUrl, const int nPort) = 0;  //!连接到服务器
	virtual BOOL LoginToServer(const CString strUsername, const CString strPasswd) = 0;
	virtual BOOL LogoutOfServer() = 0;
};

