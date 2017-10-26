#pragma once

#include <string>
#include "HttpClient.h"
#include "HttpsClient.h"
#include "SocketClient.h"

using namespace std;

class LoginService
{
public:
	LoginService(void);
	LoginService(const CString strName, const CString strPass);
	~LoginService(void);

	BOOL Login();
	BOOL Logout();

public:
   CString strUsername;
   CString strPassword;
   CString strUrl;
   BaseClient *pHttpClient;
};