#include "tests.h"
#include "controller.h"
#include "testBasic.h"
#include "touch_dispatcher/CCTouchDispatcher.h"

TestController::TestController()
{
    /**
    @todo ��Ӳ˵������ʼ���в���
    */
    
}

void TestController::onEnter()
{
    __super::onEnter();

    setIsTouchEnabled(true);
}

void TestController::registerWithTouchDispatcher()
{
    CCTouchDispatcher::getSharedDispatcher()->addTargetedDelegate(dynamic_cast<CCLayer*>(this), 0, true);
}

bool TestController::ccTouchBegan(CCTouch *pTouch, UIEvent *pEvent)
{
    // ����ActionsTest
    TestScene* pScene = new ActionsTestScene();

    pScene->runThisTest();
    return true;
}

// CCScene* NextTest()
// {
// 
// }
// 
// CCScene* PreTest()
// {
// 
// }
// 
// CCScene* CurrentTest()
// {
// 
// }
