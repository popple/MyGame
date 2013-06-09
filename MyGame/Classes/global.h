//
//  global.h
//  MyTest
//
//  Created by popplecui on 5/30/13.
//
//

#ifndef MyTest_global_h
#define MyTest_global_h

extern std::string m_replace(std::string str,std::string pattern,std::string dstPattern,int count);
extern CCArray* getSpriteFrameByBat(std::string param,int start,int stop);
extern CCSpriteFrame * getSpriteFrameByName(std::string name);
extern CCArray* getSpriteFrameByArray(CCArray* data);
#endif
