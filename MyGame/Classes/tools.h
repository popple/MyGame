#ifndef tools_h__
#define tools_h__
#include "cocos2d.h"
#include "string.h"
USING_NS_CC;
std::string m_replace(std::string str,std::string pattern,std::string dstPattern,int count=-1)
{
	std::string retStr="";
	std::string::size_type pos;
	std::string::size_type szStr=str.length();
	//int szPattern=pattern.size();
	std::string::size_type i=0;
	int l_count=0;
	if(-1 == count) // replace all
		count = szStr;

	for(i=0; i<szStr; i++)
	{
		pos=str.find(pattern,i);

		if(std::string::npos == pos)
			break;
		if(pos < szStr)
		{
			std::string s=str.substr(i,pos-i);
			retStr += s;
			retStr += dstPattern;
			i=pos+pattern.length()-1;
			if(++l_count >= count)
			{
				i++;
				break;
			}
		}
	}
	retStr += str.substr(i);
	return retStr;
}
CCArray* getSpriteFrameByBat(std::string param,int start,int stop)
{
	char temp[50];
	CCSpriteFrame *frame;
	CCArray *tem=CCArray::createWithCapacity(stop-start+1);
	tem->retain();
	for(int a=start;a<=stop;a++)
	{
		sprintf(temp,"%d",a);
		std::string t=m_replace(param.c_str(),"%NUM%",temp,-1);
		frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(t.c_str());

		if(frame)
		{
			tem->addObject(frame);
		}

		//CCLog("%s",t.c_str());
	}
    
	return tem;
};



CCSpriteFrame * getSpriteFrameByName(std::string name)
{
    return CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name.c_str());
};
CCArray* getSpriteFrameByArray(CCArray* data)
{
    return NULL;
};
#endif // tools_h__
