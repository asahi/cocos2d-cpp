/****************************************************************************
Copyright (c) 2010      cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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
#ifndef __SUPPORT_CC_UTILS_H__
#define __SUPPORT_CC_UTILS_H__
#include <functional>
#include "math/CCGeometry.h"
#include "renderer/CCCustomCommand.h"

/** @file ccUtils.h
Misc free functions
*/

NS_CC_BEGIN
/*
ccNextPOT function is licensed under the same license that is used in Texture2D.m.
*/

/** returns the Next Power of Two value.

Examples:
- If "value" is 15, it will return 16.
- If "value" is 16, it will return 16.
- If "value" is 17, it will return 32.

@since v0.99.5
*/

int ccNextPOT(int value);
    
class CC_DLL UtilsHelper
{
public:
    static UtilsHelper* getInstance();
    static void destroyInstance();
    
    /** capture screen */
    void captureScreen(const std::function<void(bool, const std::string&)>& afterCaptued, const std::string& filename, const Rect& rect = Rect::ZERO);
    
protected:
    UtilsHelper();
    virtual ~UtilsHelper();
    
    void onCaptureScreen(const std::function<void(bool, const std::string&)>& afterCaptued, const std::string& fileanme, const Rect& rect);

    
    static UtilsHelper* s_sharedHelper;
    
    CustomCommand _captureScreen;
};

NS_CC_END

#endif // __SUPPORT_CC_UTILS_H__
