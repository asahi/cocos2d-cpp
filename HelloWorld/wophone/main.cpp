// Application main file.
 
// Original file name: cocosTemplateEntry.cpp
// Generated by TOPS Builder:Project wizard,Date:2010-09-27

// wophone header
#include "TG3.h"

// game
#include "AppDelegate.h"


Int32 TG3AppMain(const TUChar * pAppID, UInt32 nCmd, void * pCmdParam)
{
	AppDelegate app;
    cocos2d::CCApplication::sharedApplication().Run();

	return 1;
}


