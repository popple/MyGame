//
//  MyGame.h
//  MyGame
//
//  Created by popplecui on 7/12/13.
//
//

#ifndef MyGame_MyGame_h
#define MyGame_MyGame_h

enum EViewType
{
    IMAGE=0,
    SKELTON,
    ROLEVIEW
};
struct TypeKey
{
    std::string name;
    EViewType type;
    bool operator<(const TypeKey& other) const
    {
        if(strcmp(name.c_str(), other.name.c_str())!=0&&type==other.type)
        {
            return true;
        }
        return false;
    }
};
#endif
