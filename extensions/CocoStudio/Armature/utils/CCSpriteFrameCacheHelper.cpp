/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#include "CCSpriteFrameCacheHelper.h"


NS_CC_EXT_ARMATURE_BEGIN

SpriteFrameCacheHelper *SpriteFrameCacheHelper::_spriteFrameCacheHelper = NULL;

SpriteFrameCacheHelper *SpriteFrameCacheHelper::sharedSpriteFrameCacheHelper()
{
    if(!_spriteFrameCacheHelper)
    {
        _spriteFrameCacheHelper = new SpriteFrameCacheHelper();
    }

    return _spriteFrameCacheHelper;
}

void SpriteFrameCacheHelper::purge()
{
    delete _spriteFrameCacheHelper;
    _spriteFrameCacheHelper = NULL;
}

void SpriteFrameCacheHelper::addSpriteFrameFromFile(const char *plistPath, const char *imagePath)
{
    CCSpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistPath, imagePath);
}

TextureAtlas *SpriteFrameCacheHelper::getTexureAtlasWithTexture(Texture2D *texture)
{
    int key = texture->getName();
    TextureAtlas *atlas = (TextureAtlas *)_textureAtlasDic->objectForKey(key);
    if (atlas == NULL)
    {
        atlas = TextureAtlas::createWithTexture(texture, 4);
        _textureAtlasDic->setObject(atlas, key);
    }
    return atlas;
}

SpriteFrameCacheHelper::SpriteFrameCacheHelper()
{
    _textureAtlasDic = new Dictionary();
}

SpriteFrameCacheHelper::~SpriteFrameCacheHelper()
{
    CC_SAFE_RELEASE_NULL(_textureAtlasDic);
}

NS_CC_EXT_ARMATURE_END
