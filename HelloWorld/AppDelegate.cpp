// Application application cpp file.
 
// Original file name: cocosTemplateApp.cpp
// Generated by TOPS Builder:Project wizard,Date:2010-09-27
 

#include "cocos2d.h"

#include "AppDelegate.h"
#include "HelloWorldScene.h"

using namespace cocos2d;


AppDelegate::AppDelegate()
:m_pMainWnd(NULL)
{

}

AppDelegate::~AppDelegate()
{
#if defined(CCX_PLATFORM_WIN32)
	CCX_SAFE_DELETE(m_pMainWnd);
#endif
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// init the window
#if defined(CCX_PLATFORM_UPHONE)
	if (!(m_pMainWnd = new CCXEGLView(this)) || 
		! m_pMainWnd->Create(&TRectangle(0,0,GetScreenWidth(),GetScreenHeight())))
#elif defined(CCX_PLATFORM_WIN32)
	if (! (m_pMainWnd = new CCXEGLView()) ||
		! m_pMainWnd->Create(L"HelloWorld", 320, 480))
#elif defined(CCX_PLATFORM_IPHONE)
	if (! (m_pMainWnd = new CCXEGLView() ) 
#elif defined(CCX_PLATFORM_ANDROID)
        if (!(m_pMainWnd = CCDirector::sharedDirector()->getOpenGLView()))
#else
	#error
#endif
	{
		delete m_pMainWnd;
		return false;
	}


	// init director
	CCDirector *pDirector = CCDirector::sharedDirector();
	pDirector->setOpenGLView(m_pMainWnd);

	// sets landscape mode
	pDirector->setDeviceOrientation(kCCDeviceOrientationLandscapeLeft);

	// turn on display FPS
	pDirector->setDisplayFPS(true);

	// create a scene. it's an autorelease object
	CCScene *pScene = HelloWorld::scene();

	// run
	pDirector->runWithScene(pScene);

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
	
	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
