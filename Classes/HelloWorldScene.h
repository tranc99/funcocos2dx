#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <string>
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

class HelloWorld : public cocos2d::Layer
{
    
private:
    Sprite* _player;
    
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void addMonster(float dt);
    
    bool onTouchBegan(Touch *touch, Event *unused_event);
    
    bool onContactBegan(PhysicsContact &contact);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
