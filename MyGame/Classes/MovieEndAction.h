//
//  MovieEndAction.h
//  MyGame
//
//  Created by popplecui on 8/12/13.
//
//

#ifndef MyGame_MovieEndAction_h
#define MyGame_MovieEndAction_h
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class MovieEndAction:public CCActionInterval
{
public:
    string movieEnd;
    MovieEndAction(string movie);
    ~MovieEndAction();
    virtual bool isDone(void);

    virtual void step(float dt);
    virtual void startWithTarget(CCNode *pTarget);
    static MovieEndAction* create(string movie);
protected:
    string m_watch_movies;
    bool mIsDone;
};


#endif
