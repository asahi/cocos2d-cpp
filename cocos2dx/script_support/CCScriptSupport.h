/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __SCRIPT_SUPPORT_H__
#define __SCRIPT_SUPPORT_H__

#include "platform/CCCommon.h"
#include "CCAccelerometer.h"
#include "touch_dispatcher/CCTouch.h"
#include "cocoa/CCSet.h"
#include "CCAccelerometer.h"
#include <map>
#include <string>
#include <list>

typedef struct lua_State lua_State;

NS_CC_BEGIN

class Timer;
class Layer;
class MenuItem;
class NotificationCenter;
class CallFunc;
class Acceleration;

enum ccScriptType {
    kScriptTypeNone = 0,
    kScriptTypeLua,
    kScriptTypeJavascript
};

class ScriptHandlerEntry : public Object
{
public:
    static ScriptHandlerEntry* create(int nHandler);
    ~ScriptHandlerEntry(void);
    
    int getHandler(void) {
        return _handler;
    }
    
    int getEntryId(void) {
        return _entryId;
    }
    
protected:
    ScriptHandlerEntry(int nHandler)
    : _handler(nHandler)
    {
        static int newEntryId = 0;
        newEntryId++;
        _entryId = newEntryId;
    }
    
    int _handler;
    int _entryId;
};

/**
 * @addtogroup script_support
 * @{
 */

class SchedulerScriptHandlerEntry : public ScriptHandlerEntry
{
public:
    // nHandler return by tolua_ref_function(), called from LuaCocos2d.cpp
    static SchedulerScriptHandlerEntry* create(int nHandler, float fInterval, bool bPaused);
    ~SchedulerScriptHandlerEntry(void);
    
    cocos2d::Timer* getTimer(void) {
        return _timer;
    }
    
    bool isPaused(void) {
        return _paused;
    }
    
    void markedForDeletion(void) {
        _markedForDeletion = true;
    }
    
    bool isMarkedForDeletion(void) {
        return _markedForDeletion;
    }
    
private:
    SchedulerScriptHandlerEntry(int nHandler)
    : ScriptHandlerEntry(nHandler)
    , _timer(NULL)
    , _paused(false)
    , _markedForDeletion(false)
    {
    }
    bool init(float fInterval, bool bPaused);
    
    cocos2d::Timer*   _timer;
    bool                _paused;
    bool                _markedForDeletion;
};



class TouchScriptHandlerEntry : public ScriptHandlerEntry
{
public:
    static TouchScriptHandlerEntry* create(int nHandler, bool bIsMultiTouches, int nPriority, bool bSwallowsTouches);
    ~TouchScriptHandlerEntry(void);
    
    bool isMultiTouches(void) {
        return _isMultiTouches;
    }
    
    int getPriority(void) {
        return _priority;
    }
    
    bool getSwallowsTouches(void) {
        return _swallowsTouches;
    }
    
private:
    TouchScriptHandlerEntry(int nHandler)
    : ScriptHandlerEntry(nHandler)
    , _isMultiTouches(false)
    , _priority(0)
    , _swallowsTouches(false)
    {
    }
    bool init(bool bIsMultiTouches, int nPriority, bool bSwallowsTouches);
    
    bool    _isMultiTouches;
    int     _priority;
    bool    _swallowsTouches;
};

enum ScriptEventType
{
    kNodeEvent = 0,
    kMenuItemEvent,
    kNotificationEvent,
    kCallFuncEvent,
    kScheduleEvent,
    kLayerTouchesEvent,
    kLayerTouchEvent,
    kLayerKeypadEvent,
    kAccelerometerEvent,
    kCommonEvent,
};

struct SchedulerScriptEvent
{
    //lua use
    int handler;
    float elapse;
    //js use
    Node* node;
    SchedulerScriptEvent(int inHandler,float inElapse,Node* inNode = NULL)
    :handler(inHandler),
    elapse(inElapse),
    node(inNode)
    {
    }
};

struct LayerTouchesScriptEvent
{
    int  actionType;
    Set* touches;
    LayerTouchesScriptEvent(int inActiontype,Set* inTouches)
    :actionType(inActiontype),
    touches(inTouches)
    {
    }
};

struct LayerTouchScriptEvent
{
    int actionType;
    Touch* touch;
    LayerTouchScriptEvent(int inActionType,Touch* inTouch)
    :actionType(inActionType),
    touch(inTouch)
    {
    }
};

struct CommonScriptEvent
{
    //now,only use lua 
    int handler;
    char eventName[64];
    Object* eventSource;
    char eventSourceClassName[64];
    CommonScriptEvent(int inHandler,const char* inName,Object* inSource = NULL,const char* inClassName = NULL)
    :handler(inHandler),
    eventSource(inSource)
    {
        strncpy(eventName, inName, 64);
        
        if (NULL == inClassName)
        {
            memset(eventSourceClassName, 0, 64*sizeof(char));
        }
        else
        {
            strncpy(eventSourceClassName, inClassName, 64);
        }
    }
};

struct ScriptEvent
{
    ScriptEventType type;
    void* data;
    ScriptEvent(ScriptEventType inType,void* inData)
    :type(inType),
    data(inData)
    {
    }
};

// Don't make ScriptEngineProtocol inherits from Object since setScriptEngine is invoked only once in AppDelegate.cpp,
// It will affect the lifecycle of ScriptCore instance, the autorelease pool will be destroyed before destructing ScriptCore.
// So a crash will appear on Win32 if you click the close button.
class CC_DLL ScriptEngineProtocol
{
public:
    virtual ~ScriptEngineProtocol() {};
    
    /** Get script type */
    virtual ccScriptType getScriptType() { return kScriptTypeNone; };

    /** Remove script object. */
    virtual void removeScriptObjectByObject(Object* pObj) = 0;
    
    /** Remove script function handler, only LuaEngine class need to implement this function. */
    virtual void removeScriptHandler(int nHandler) {};
    
    /** Reallocate script function handler, only LuaEngine class need to implement this function. */
    virtual int reallocateScriptHandler(int nHandler) { return -1;}
    
    /**
     @brief Execute script code contained in the given string.
     @param codes holding the valid script code that should be executed.
     @return 0 if the string is executed correctly.
     @return other if the string is executed wrongly.
     */
    virtual int executeString(const char* codes) = 0;
    
    /**
     @brief Execute a script file.
     @param filename String object holding the filename of the script file that is to be executed
     */
    virtual int executeScriptFile(const char* filename) = 0;
    
    /**
     @brief Execute a scripted global function.
     @brief The function should not take any parameters and should return an integer.
     @param functionName String object holding the name of the function, in the global script environment, that is to be executed.
     @return The integer value returned from the script function.
     */
    virtual int executeGlobalFunction(const char* functionName) = 0;
    
    /**
     @brief Execute a node event function
     @param pNode which node produce this event
     @param nAction kNodeOnEnter,kNodeOnExit,kMenuItemActivated,kNodeOnEnterTransitionDidFinish,kNodeOnExitTransitionDidStart
     @return The integer value returned from the script function.
     */
    virtual int executeNodeEvent(Node* pNode, int nAction) = 0;
    
    virtual int executeMenuItemEvent(MenuItem* pMenuItem) = 0;
    /** Execute a notification event function */
    virtual int executeNotificationEvent(NotificationCenter* pNotificationCenter, const char* pszName) = 0;
    
    /** execute a callfun event */
    virtual int executeCallFuncActionEvent(CallFunc* pAction, Object* pTarget = NULL) = 0;
    /** execute a schedule function */
    virtual int executeSchedule(int nHandler, float dt, Node* pNode = NULL) = 0;
    
    /** functions for executing touch event */
    virtual int executeLayerTouchesEvent(Layer* pLayer, int eventType, Set *pTouches) = 0;
    virtual int executeLayerTouchEvent(Layer* pLayer, int eventType, Touch *pTouch) = 0;

    /** functions for keypad event */
    virtual int executeLayerKeypadEvent(Layer* pLayer, int eventType) = 0;

    /** execute a accelerometer event */
    virtual int executeAccelerometerEvent(Layer* pLayer, Acceleration* pAccelerationValue) = 0;

    /** function for common event */
    virtual int executeEvent(int nHandler, const char* pEventName, Object* pEventSource = NULL, const char* pEventSourceClassName = NULL) = 0;

    /** called by CCAssert to allow scripting engine to handle failed assertions
     * @return true if the assert was handled by the script engine, false otherwise.
     */
    virtual bool handleAssert(const char *msg) = 0;
    
    //when trigger a script event ,call this func,add params needed into ScriptEvent object.nativeObject is object triggering the event, can be NULL in lua
    virtual int sendEvent(ScriptEvent* message,void* nativeObject = NULL){ return -1;}
    //
};

/**
 ScriptEngineManager is a singleton which holds an object instance of ScriptEngineProtocl
 It helps cocos2d-x and the user code to find back LuaEngine object
 @since v0.99.5-x-0.8.5
 */
class CC_DLL ScriptEngineManager
{
public:
    ~ScriptEngineManager(void);
    
    ScriptEngineProtocol* getScriptEngine(void) {
        return _scriptEngine;
    }
    void setScriptEngine(ScriptEngineProtocol *pScriptEngine);
    void removeScriptEngine(void);
    
    static ScriptEngineManager* sharedManager(void);
    static void purgeSharedManager(void);
    
private:
    ScriptEngineManager(void)
    : _scriptEngine(NULL)
    {
    }
    
    ScriptEngineProtocol *_scriptEngine;
};

// end of script_support group
/// @}

NS_CC_END

#endif // __SCRIPT_SUPPORT_H__
