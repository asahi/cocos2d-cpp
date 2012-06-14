/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2009      Leonardo Kasperavičius
Copyright (c) 2011      Zynga Inc.
 
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
#ifndef __CC_PARTICLE_SYSTEM_QUAD_H__
#define __CC_PARTICLE_SYSTEM_QUAD_H__

#include  "CCParticleSystem.h"

NS_CC_BEGIN

class CCSpriteFrame;

/** @brief CCParticleSystemQuad is a subclass of CCParticleSystem

It includes all the features of ParticleSystem.

Special features and Limitations:    
- Particle size can be any float number.
- The system can be scaled
- The particles can be rotated
- It supports subrects
- It supports batched rendering since 1.1
@since v0.8
*/
class CC_DLL CCParticleSystemQuad : public CCParticleSystem
{
protected:
    ccV3F_C4B_T2F_Quad    *m_pQuads;        // quads to be rendered
    GLushort            *m_pIndices;    // indices

#if CC_TEXTURE_ATLAS_USE_VAO
    GLuint                m_uVAOname;
#endif

    GLuint                m_pBuffersVBO[2]; //0: vertex  1: indices

public:
    CCParticleSystemQuad();
    virtual ~CCParticleSystemQuad();

    /** creates an initializes a CCParticleSystemQuad from a plist file.
    This plist files can be creted manually or with Particle Designer:  
    @warning: This interface will be deprecated in future.
    */
    static CCParticleSystemQuad * particleWithFile(const char *plistFile);

    /** creates an initializes a CCParticleSystemQuad from a plist file.
    This plist files can be creted manually or with Particle Designer:  
    */
    static CCParticleSystemQuad * create(const char *plistFile);

    /** initialices the indices for the vertices*/
    void setupIndices();

    /** initilizes the texture with a rectangle measured Points */
    void initTexCoordsWithRect(const CCRect& rect);

    /** Sets a new CCSpriteFrame as particle.
    WARNING: this method is experimental. Use setTexture:withRect instead.
    @since v0.99.4
    */
    void setDisplayFrame(CCSpriteFrame *spriteFrame);

    /** Sets a new texture with a rect. The rect is in Points.
    @since v0.99.4
    */
    void setTextureWithRect(CCTexture2D *texture, const CCRect& rect);
    // super methods
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    virtual void setTexture(CCTexture2D* texture);
    virtual void updateQuadWithParticle(tCCParticle* particle, const CCPoint& newPosition);
    virtual void postStep();
    virtual void draw();
    virtual void setBatchNode(CCParticleBatchNode* batchNode);
    virtual void setTotalParticles(unsigned int tp);
    
    /** listen the event that coming to foreground on Android
     */
    void listenBackToForeground(CCObject *obj);

    static CCParticleSystemQuad * node();
private:
#if CC_TEXTURE_ATLAS_USE_VAO
    void setupVBOandVAO();
#else
    void setupVBO();
#endif
    bool allocMemory();
};

NS_CC_END

#endif //__CC_PARTICLE_SYSTEM_QUAD_H__

