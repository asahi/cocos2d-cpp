//
// Created by NiTe Luo on 10/31/13.
//



#ifndef __CC_RENDERER_H_
#define __CC_RENDERER_H_

#include "CCPlatformMacros.h"
#include "RenderCommand.h"
#include "CCGLProgram.h"
#include "CCGL.h"
#include <vector>
#include <stack>

#define VBO_SIZE 1024
#define DEFAULT_RENDER_QUEUE 0

NS_CC_BEGIN
using namespace std;

typedef vector<RenderCommand*> RenderQueue;

struct RenderStackElement
{
    int renderQueueID;
    size_t currentIndex;
};

class Renderer : public Object
{
public:
    static Renderer* getInstance();
    static void destroyInstance();

    //TODO support multiple viewport
    void addCommand(RenderCommand* command);
    void addCommand(RenderCommand* command, int renderQueue);
    void pushGroup(int renderQueueID);
    void popGroup();
    
    int createRenderQueue();
    void render();

protected:
    Renderer();
    ~Renderer();

    bool init();
    void setupIndices();
    void setupVBOAndVAO();

    //Draw the previews queued quads and flush previous context
    void flush();

protected:
    stack<int> _commandGroupStack;
    
    stack<RenderStackElement> _renderStack;
    vector<RenderQueue> _renderGroups;

    int _lastMaterialID;

    size_t _firstCommand;
    size_t _lastCommand;

    V3F_C4B_T2F_Quad _quads[VBO_SIZE];
    GLushort _indices[6 * VBO_SIZE];
    GLuint _VAOname;
    GLuint _buffersVBO[2]; //0: vertex  1: indices

    int _numQuads;

    void drawBatchedQuads();
};

NS_CC_END

#endif //__CC_RENDERER_H_
