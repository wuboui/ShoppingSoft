#pragma once
#include <hash_map>

class CStringHash : public hash_compare<CString>
{
public:
	size_t operator()(const CString &str) const
	{
		size_t value = _HASH_SEED;   
		size_t size  = str.GetLength();   
		if (size > 0)
		{   
			size_t temp = (size / 16) + 1;   
			size -= temp;   
			for (size_t idx = 0; idx <= size; idx += temp) 
			{   
				value += (size_t)str[(int)idx];   
			}   
		}   
		return(value); 
	}

	bool operator()(const CString &a, const CString &b) const
	{
		return a.Compare(b) == 0;
	}
};