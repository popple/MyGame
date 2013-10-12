//
//  MyGame.h
//  MyGame
//
//  Created by popplecui on 7/12/13.
//
//

#ifndef MyGame_MyGame_h
#define MyGame_MyGame_h
class GameObj;
enum EViewType
{
    IMAGE=0,
    SKELTON,
    ROLEVIEW
};
struct Result
{
    bool isCollision;
    float radius;
    GameObj* target;
};
struct TypeKey
{
    std::string name;
    EViewType type;
    bool operator<(const TypeKey& other) const
    {
        int r=strcmp(name.c_str(), other.name.c_str());
        if(r==0)
        {
            if(type<other.type)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        if(r<0)
        {
            return true;
        }
        if(r>0)
        {
            return false;
        }
        return false;
    }
};
#endif
