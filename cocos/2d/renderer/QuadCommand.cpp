//
// Created by NiTe Luo on 11/6/13.
//


#include "QuadCommand.h"
#include "ccGLStateCache.h"

NS_CC_BEGIN
RenderCommandPool<QuadCommand> QuadCommand::_commandPool;

QuadCommand::QuadCommand()
:RenderCommand()
,_viewport(0)
,_depth(0)
,_textureID(0)
,_blendType(BlendFunc::DISABLE)
,_quadCount(0)
,_capacity(0)
{
    _type = QUAD_COMMAND;
    _shader = nullptr;
    _quad = nullptr;
}

void QuadCommand::init(int viewport, int32_t depth, GLuint textureID, GLProgram* shader, BlendFunc blendType, V3F_C4B_T2F_Quad* quad, int quadCount, const kmMat4 &mv)
{
    _viewport = viewport;
    _depth = depth;
    _textureID = textureID;
    _blendType = blendType;
    _quadCount = quadCount;
    _shader = shader;

    if(quadCount > _capacity ) {
//        _quad = (V3F_C4B_T2F_Quad*)malloc(sizeof(V3F_C4B_T2F_Quad) * quadCount);
        _quad = (V3F_C4B_T2F_Quad*) realloc(_quad, sizeof(*quad) * quadCount );
        _capacity = quadCount;
    }

    _quadCount = quadCount;
    memcpy(_quad, quad, sizeof(V3F_C4B_T2F_Quad) * quadCount);

    for(int i=0; i<quadCount; ++i) {
        V3F_C4B_T2F_Quad *q = &_quad[i];

        kmVec3 vec1, out1;
        vec1.x = q->bl.vertices.x;
        vec1.y = q->bl.vertices.y;
        vec1.z = q->bl.vertices.z;
        kmVec3Transform(&out1, &vec1, &mv);
        q->bl.vertices.x = out1.x;
        q->bl.vertices.y = out1.y;
        q->bl.vertices.z = out1.z;

        kmVec3 vec2, out2;
        vec2.x = q->br.vertices.x;
        vec2.y = q->br.vertices.y;
        vec2.z = q->br.vertices.z;
        kmVec3Transform(&out2, &vec2, &mv);
        q->br.vertices.x = out2.x;
        q->br.vertices.y = out2.y;
        q->br.vertices.z = out2.z;

        kmVec3 vec3, out3;
        vec3.x = q->tr.vertices.x;
        vec3.y = q->tr.vertices.y;
        vec3.z = q->tr.vertices.z;
        kmVec3Transform(&out3, &vec3, &mv);
        q->tr.vertices.x = out3.x;
        q->tr.vertices.y = out3.y;
        q->tr.vertices.z = out3.z;

        kmVec3 vec4, out4;
        vec4.x = q->tl.vertices.x;
        vec4.y = q->tl.vertices.y;
        vec4.z = q->tl.vertices.z;
        kmVec3Transform(&out4, &vec4, &mv);
        q->tl.vertices.x = out4.x;
        q->tl.vertices.y = out4.y;
        q->tl.vertices.z = out4.z;
    }
}

QuadCommand::~QuadCommand()
{
    free(_quad);
}

int64_t QuadCommand::generateID()
{
    _id = 0;

    //Generate Material ID
    //TODO fix shader ID generation
    CCASSERT(_shader->getProgram() < 64, "ShaderID is greater than 64");
    //TODO fix texture ID generation
    CCASSERT(_textureID < 1024, "TextureID is greater than 1024");

    //TODO fix blend id generation
    int blendID = 0;
    if(_blendType == BlendFunc::DISABLE)
    {
        blendID = 0;
    }
    else if(_blendType == BlendFunc::ALPHA_PREMULTIPLIED)
    {
        blendID = 1;
    }
    else if(_blendType == BlendFunc::ALPHA_NON_PREMULTIPLIED)
    {
        blendID = 2;
    }
    else if(_blendType == BlendFunc::ADDITIVE)
    {
        blendID = 3;
    }
    else
    {
        blendID = 4;
    }

    _materialID = (int32_t)_shader->getProgram() << 28
            | (int32_t)blendID << 24
            | (int32_t)_textureID << 14;

    //Generate RenderCommandID
    _id = (int64_t)_viewport << 61
            | (int64_t)1 << 60 //translucent
            | (int64_t)_depth << 36;

    return _id;
}

void QuadCommand::useMaterial()
{
    _shader->use();

    _shader->setUniformsForBuiltins();

    //Set texture
    GL::bindTexture2D(_textureID);

    //set blend mode
    GL::blendFunc(_blendType.src, _blendType.dst);
}

void QuadCommand::releaseToCommandPool()
{
    getCommandPool().pushBackCommand(this);
}

NS_CC_END