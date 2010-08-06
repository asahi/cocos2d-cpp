// Application application cpp file.
 
// Original file name: test_uphoneApp.cpp
// Generated by TOPS Builder:Project wizard,Date:2010-7-26
 

#include  "test_uphoneApp.h"
#include  "test_uphoneMainForm.h"

#include "CCDirector.h"
#include "CCScene.h"
#include "tests/controller.h"

using namespace cocos2d;

Ttest_uphoneApp::Ttest_uphoneApp()
: m_pMainWnd(NULL)
{

}

Ttest_uphoneApp::~Ttest_uphoneApp()
{

}

bool Ttest_uphoneApp::initCocos2d()
{
    CCDirector::getSharedDirector()->setOpenGLView(m_pMainWnd);
    //CCDirector::getSharedDirector()->setDeviceOrientation(kCCDeviceOrientationLandscapeLeft);

    CCScene * pScene = CCScene::node();
    CCLayer * pLayer = new TestController();
    pLayer->autorelease();

    pScene->addChild(pLayer);
    CCDirector::getSharedDirector()->runWithScene(pScene);

    return true;
}

Boolean  Ttest_uphoneApp::EventHandler(EventType*  pEvent)
{
	Boolean     bHandled = FALSE;

	switch(pEvent->eType)
	{
	case EVENT_AppLoad:
		{
			m_pMainWnd = new TMainForm(this);
			if (m_pMainWnd)
			{
				SetActiveWindow(m_pMainWnd);
			}
			else
			{	// 窗口创建失败，退出应用。
				SendStopEvent();
			}
		}
		break;

	case EVENT_AppStopNotify:
		{
			
		}
		bHandled = FALSE;
		break;
	}
	if (FALSE == bHandled) 
	{
		return CCXApplication::EventHandler(pEvent);
	}

	return bHandled;
}
