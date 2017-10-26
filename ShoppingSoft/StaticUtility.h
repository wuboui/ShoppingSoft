#pragma once

/************************************************************************/
/* 注意：该类为实用工具类，对外提供通用服务
         该类中的所有方法均为static静态方法
		 可以通过   类名::方法名   的方式直接使用
*/
/************************************************************************/

#include <vector>
using namespace std;

class StaticUtility
{
public:
	StaticUtility(void);
	~StaticUtility(void);

public:

	/*
	  @功能：对字符串进行分割
	  @输入：cstrOriginal为原始输入的字符串
	         cstrSeparator为分割字符串
	  @输出：vector<CString>类型
	 */
	static void StringSplit(const CString cstrOriginal, const CString cstrSeparator, vector<CString> &vecContainer);
};