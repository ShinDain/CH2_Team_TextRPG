#include "pch.h"
#include "StringHelper.h"

void StringHelper::Unquote(string& InString)
{
	InString.erase(find_if(InString.rbegin(), InString.rend(), [](char ch)
		{
			return ch != '\"';
		}).base(), InString.end());
	InString.erase(InString.begin(), find_if(InString.begin(), InString.end(), [](char ch)
		{
			return ch != '\"';
		}));
}
