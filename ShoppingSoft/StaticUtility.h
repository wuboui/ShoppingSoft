#pragma once

/************************************************************************/
/* ע�⣺����Ϊʵ�ù����࣬�����ṩͨ�÷���
         �����е����з�����Ϊstatic��̬����
		 ����ͨ��   ����::������   �ķ�ʽֱ��ʹ��
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
	  @���ܣ����ַ������зָ�
	  @���룺cstrOriginalΪԭʼ������ַ���
	         cstrSeparatorΪ�ָ��ַ���
	  @�����vector<CString>����
	 */
	static void StringSplit(const CString cstrOriginal, const CString cstrSeparator, vector<CString> &vecContainer);
};