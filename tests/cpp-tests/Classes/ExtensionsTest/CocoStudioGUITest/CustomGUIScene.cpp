

#include "CustomGUIScene.h"
#include "CocoStudioGUITest.h"
#include "CustomTest/CustomImageTest/CustomImageTest.h"
#include "CustomTest/CustomParticleWidgetTest/CustomParticleWidgetTest.h"


enum
{
    LINE_SPACE = 40,
    kItemTagBasic = 1000,
};

static struct
{
	const char *name;
	std::function<void(Ref* sender)> callback;
}
g_guisTests[] =
{
	{
        "custom gui image Test",
        [](Ref* sender)
        {
            CustomImageScene* pScene = new CustomImageScene();
            pScene->runThisTest();
            pScene->release();
        }
	},
    {
        "custom gui particle widget Test",
        [](Ref* sender)
        {
            CustomParticleWidgetScene* pScene = new CustomParticleWidgetScene();
            pScene->runThisTest();
            pScene->release();
        }
	},
};

static const int g_maxTests = sizeof(g_guisTests) / sizeof(g_guisTests[0]);

////////////////////////////////////////////////////////
//
// CustomGUITestMainLayer
//
////////////////////////////////////////////////////////

static Point _curPos = Point::ZERO;


void CustomGUITestMainLayer::onEnter()
{
    Layer::onEnter();
    
    auto s = Director::getInstance()->getWinSize();
    
    _itemMenu = Menu::create();
    _itemMenu->setPosition( _curPos );
    MenuItemFont::setFontName("fonts/arial.ttf");
    MenuItemFont::setFontSize(24);
    for (int i = 0; i < g_maxTests; ++i)
    {
        auto pItem = MenuItemFont::create(g_guisTests[i].name, g_guisTests[i].callback);
//        pItem->setPosition(Point(s.width / 2, s.height / 2));
        pItem->setPosition(Point(s.width / 2, s.height - (i + 1) * LINE_SPACE));
        _itemMenu->addChild(pItem, kItemTagBasic + i);
    }
    
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(CustomGUITestMainLayer::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(CustomGUITestMainLayer::onTouchesMoved, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    addChild(_itemMenu);
}

void CustomGUITestMainLayer::onTouchesBegan(const std::vector<Touch *> &touches, cocos2d::Event *event)
{
    auto touch = static_cast<Touch*>(touches[0]);
    
    _beginPos = touch->getLocation();
}

/*
void CustomGUITestMainLayer::onTouchesMoved(const std::vector<Touch *> &touches, cocos2d::Event *event)
{
    auto touch = static_cast<Touch*>(touches[0]);
    
    auto touchLocation = touch->getLocation();
    
    float nMoveY = touchLocation.y - _beginPos.y;
    
    Point curPos  = _itemMenu->getPosition();
    Point nextPos = ccp(curPos.x, curPos.y + nMoveY);
    
    if (nextPos.y < 0.0f)
    {
        _itemMenu->setPosition(CCPointZero);
        return;
    }        
    
    _itemMenu->setPosition(nextPos);
    _beginPos = touchLocation;
    _curPos   = nextPos;
}
 */

////////////////////////////////////////////////////////
//
// CustomGUITestScene
//
////////////////////////////////////////////////////////

void CustomGUITestScene::onEnter()
{
    CCScene::onEnter();
    
    auto label = Label::createWithFont("Back", "fonts/arial.ttf", 20);
    //#endif
    MenuItemLabel* pMenuItem = MenuItemLabel::create(label, CC_CALLBACK_1(CustomGUITestScene::BackCallback, this));
    
    Menu* pMenu = Menu::create(pMenuItem, NULL);
    
    pMenu->setPosition( Point::ZERO );
    pMenuItem->setPosition( Point( VisibleRect::right().x - 50, VisibleRect::bottom().y + 25) );
    
    addChild(pMenu, 1);
}

void CustomGUITestScene::runThisTest()
{
    Layer* pLayer = new CustomGUITestMainLayer();
    addChild(pLayer);
    pLayer->release();
    
    CCDirector::getInstance()->replaceScene(this);
}

void CustomGUITestScene::BackCallback(Ref* pSender)
{
    CocoStudioGUITestScene* pScene = new CocoStudioGUITestScene();
    pScene->runThisTest();
    pScene->release();
}
