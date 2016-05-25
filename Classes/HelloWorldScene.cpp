#include "HelloWorldScene.h"


USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void HelloWorld::addMonster(float dt)
{
    auto monster = Sprite::create("monster.png");
    
    //1
    auto monsterContentSize = monster->getContentSize();
    auto selfContentSize = this->getContentSize();
    int minY = monsterContentSize.height/2;
    int maxY = selfContentSize.height - monsterContentSize.height/2;
    int rangeY = maxY - minY;
    int randomY = (rand() % rangeY) + minY;
    
    monster->setPosition(Vec2(selfContentSize.width + monsterContentSize.width/2, randomY));
    this->addChild(monster);
    
    //2
    int minDuration = 2.0;
    int maxDuration = 4.0;
    int rangeDuration = maxDuration - minDuration;
    int randomDuration = (rand() % rangeDuration) + minDuration;
    
    //3
    auto actionMove = MoveTo::create(randomDuration, Vec2(-monsterContentSize.width/2, randomY));
    auto actionRemove = RemoveSelf::create();
    monster->runAction(Sequence::create(actionMove, actionRemove, nullptr));
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
    // 1
    auto node = unused_event->getCurrentTarget();
    
    // 2
    Vec2 touchLocation = touch->getLocation();
    Vec2 offset = touchLocation - _player->getPosition();
    
    // 3
    if (offset.x < 0) {
        return true;
    }
    
    const std::string arrSprite[3] = {"blow1.png", "blow2.png", "blow3.png"};
    int ind = rand() % 3;
    // 4
    //auto projectile = Sprite::create("projectile.png");
    auto projectile = Sprite::create(arrSprite[ind]);
    projectile->setPosition(_player->getPosition());
    this->addChild(projectile);
    
    // 5
    offset.normalize();
    auto shootAmount = offset * 1000;
    
    // 6
    auto realDest = shootAmount + projectile->getPosition();
    
    // 7
    auto actionMove = MoveTo::create(2.0f, realDest);
    auto actionRemove = RemoveSelf::create();
    projectile->runAction(Sequence::create(actionMove, actionRemove, nullptr));
    
    return true;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    // 2.
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto winSize = Director::getInstance()->getVisibleSize();

    /////////////////////////////
    // 3. add your codes below...
    auto background = DrawNode::create();
    background->drawSolidRect(origin, winSize, Color4F(0.8, 0.4, 0.6, 1.0));
    this->addChild(background);

    // 4
    _player = Sprite::create("ninja2.png");
    _player->setPosition(Vec2(winSize.width * 0.1, winSize.height * 0.5));
    // add the sprite as a child to this layer
    this->addChild(_player);
    
    srand((unsigned int)time(nullptr));
    this->schedule(schedule_selector(HelloWorld::addMonster), 1.5);
    
    auto eventListener = EventListenerTouchOneByOne::create();
    eventListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, _player);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
