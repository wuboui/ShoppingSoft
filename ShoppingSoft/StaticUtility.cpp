#include "StdAfx.h"
#include "StaticUtility.h"


StaticUtility::StaticUtility(void)
{
}


StaticUtility::~StaticUtility(void)
{
}

void StaticUtility::StringSplit(const CString cstrOriginal, const CString cstrSeparator, vector<CString> &vecContainer)
{
	int pos;
	int tmp = 0;

	pos = cstrOriginal.Find(cstrSeparator, tmp);

	while(pos != -1)
	{
		CString sub_str = cstrOriginal.Mid(tmp, pos-tmp);
		if (!sub_str.IsEmpty())
		{
			vecContainer.push_back(sub_str);
		}

		tmp = pos + 1;

		pos = cstrOriginal.Find(cstrSeparator, tmp);  //!������tmp��ʼ�������Ļ�strԭ�ַ����Ͳ��ö���
	}

	CString sub_str = cstrOriginal.Mid(tmp, cstrOriginal.GetLength() - tmp);
	if (!sub_str.IsEmpty())
	{
		vecContainer.push_back(sub_str);
	}
}