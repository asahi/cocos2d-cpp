/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

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

#include "CCMeshSkin.h"
#include "CCBundle3D.h"

#include "base/ccMacros.h"
#include "base/CCPlatformMacros.h"
#include "platform/CCFileUtils.h"

NS_CC_BEGIN

/**
 * Sets the inverse bind pose matrix.
 *
 * @param m C3DMatrix representing the inverse bind pose for this Bone.
 */
void Bone::setInverseBindPose(const Mat4& m)
{
    _bindPose = m;
}

const Mat4& Bone::getInverseBindPose()
{
    return _bindPose;
}

void Bone::setWorldMatDirty(bool dirty)
{
    _worldDirty = dirty;
    for (auto it : _children) {
        it->setWorldMatDirty(dirty);
    }
}

//update own world matrix and children's
void Bone::updateWorldMat()
{
    getWorldMat();
    for (auto itor : _children) {
        itor->updateWorldMat();
    }
}

const Mat4& Bone::getWorldMat()
{
    //if (_worldDirty)
    {
        updateLocalMat();
        if (_parent)
        {
            _world = _parent->getWorldMat() * _local;
        }
        else
            _world = _local;
        
        _worldDirty = false;
    }
    
    return _world;
}

///**
// * Set AnimationValue. set to its transform
// */
//void Bone::setAnimationValueTranslation(float* value, float weight)
//{
//    static const int bytes = 3 * sizeof(float);
//    if (memcmp(&_localTranslate.x, value, bytes) != 0)
//    {
//        _dirtyFlag |= Dirty_Translate;
//        _localTranslate.set(value);
//    }
//}
//void Bone::setAnimationValueRotation(float* value, float weight)
//{
//    static const int bytes = 4 * sizeof(float);
//    if (memcmp(&_localRot.x, value, bytes) != 0)
//    {
//        _dirtyFlag |= Dirty_Rotation;
//        _localRot.set(value);
//    }
//}
//void Bone::setAnimationValueScale(float* value, float weight)
//{
//    static const int bytes = 3 * sizeof(float);
//    if (memcmp(&_localScale.x, value, bytes) != 0)
//    {
//        _dirtyFlag |= Dirty_Scale;
//        _localScale.set(value);
//    }
//}

void Bone::setAnimationValue(float* trans, float* rot, float* scale, float weight)
{
    BoneBlendState state;
    if (trans)
        state.localTranslate.set(trans);
    if (rot)
        state.localRot.set(rot);
    if (scale)
        state.localScale.set(scale);
    state.weight = weight;
    
    _blendStates.clear();
    _blendStates.push_back(state);
    _localDirty = true;
}

/**
 * Creates C3DBone.
 */
Bone* Bone::create(const std::string& id)
{
    auto bone = new Bone(id);
    bone->autorelease();
    return bone;
}



/**
 * Updates the joint matrix.
 *
 * @param bindShape The bind shape matrix.
 * @param matrixPalette The matrix palette to update.
 */
void Bone::updateJointMatrix(const Mat4& bindShape, Vec4* matrixPalette)
{
    
    //if (_skinCount > 1 || _jointMatrixDirty)
    {
        //_jointMatrixDirty = false;
        static Mat4 t;
        Mat4::multiply(_world, getInverseBindPose(), &t);
        //Mat4::multiply(t, bindShape, &t);
        //Mat4::multiply(getInverseBindPose(), _world, &t);
        
        //t.setIdentity();
        matrixPalette[0].set(t.m[0], t.m[4], t.m[8], t.m[12]);
        matrixPalette[1].set(t.m[1], t.m[5], t.m[9], t.m[13]);
        matrixPalette[2].set(t.m[2], t.m[6], t.m[10], t.m[14]);
    }
}

//bone tree, we do not inherit from Node, Node has too many properties that we do not need. A clean Node is needed.
Bone* Bone::getParentBone()
{
    return _parent;
}
int Bone::getChildBoneCount() const
{
    return _children.size();
}
Bone* Bone::getChildBoneByIndex(int index)
{
    return _children.at(index);
}
void Bone::addChildBone(Bone* bone)
{
    if (_children.find(bone) == _children.end())
       _children.pushBack(bone);
}
void Bone::removeChildBoneByIndex(int index)
{
    _children.erase(index);
}
void Bone::removeChildBone(Bone* bone)
{
    _children.eraseObject(bone);
}
void Bone::removeAllChildBone()
{
    _children.clear();
}

Bone::Bone(const std::string& id)
: _name(id)
, _parent(nullptr)
, _localDirty(true)
, _worldDirty(true)
{
    
}

/**
 * Destructor.
 */
Bone::~Bone()
{
    removeAllChildBone();
}

void Bone::updateLocalMat()
{
    if (_blendStates.size() == 0)
        return;
    
    if (!_localDirty)
        return;
    
    Vec3 translate(0.f, 0.f, 0.f), scale(0.f, 0.f, 0.f);
    Quaternion quat(0.f, 0.f, 0.f, 0.f);
    if (_blendStates.size())
    {
        float total = 0.f;
        for (auto it: _blendStates) {
            total += it.weight;
        }
        if (total)
        {
            if (_blendStates.size() == 1)
            {
                translate = _blendStates[0].localTranslate;
                scale = _blendStates[0].localScale;
                quat = _blendStates[0].localRot;
            }
            else
            {
                float invTotal = 1.f / total;
                for (auto it : _blendStates) {
                    float weight = (it.weight * invTotal);
                    translate += it.localTranslate * weight;
                    if (!it.localScale.isZero())
                    {
                        scale.x *= it.localScale.x * weight;
                        scale.y *= it.localScale.y * weight;
                        scale.z *= it.localScale.z * weight;
                    }
                    if (!it.localRot.isZero())
                    {
                        if (!quat.isZero())
                        {
                            Quaternion& q = _blendStates[0].localRot;
                            if (q.x * quat.x + q.y * quat.y + q.z * quat.z + q.w * quat.w < 0)
                            weight = -weight;
                        }
                        quat = Quaternion(it.localRot.x * weight + quat.x, it.localRot.y * weight + quat.y, it.localRot.z * weight + quat.z, it.localRot.w * weight + quat.w);
                    }
                }
            }  
        }
        
        bool hasTrans = !translate.isZero();
        bool hasRot = !quat.isZero();
        bool hasScale = !scale.isZero();
        
        if (hasTrans)
        {
            Mat4::createTranslation(translate, &_local);
            if (hasRot)
                _local.rotate(quat);
            if (hasScale)
                _local.scale(scale);
        }
        else if (hasRot)
        {
            Mat4::createRotation(quat, &_local);
            if (hasScale)
                _local.scale(scale);
        }
        else if (hasScale)
        {
            Mat4::createScale(scale, &_local);
        }
        else
            _local.setIdentity();
        
        _blendStates.clear();
        _localDirty = false;
    }
    
    
}

void Bone::clearBlendState()
{
    _blendStates.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int PALETTE_ROWS = 3;

MeshSkin::MeshSkin()
: _rootBone(nullptr)
, _matrixPalette(nullptr)
{
    
}

MeshSkin::~MeshSkin()
{
    removeAllBones();
}

MeshSkin* MeshSkin::getOrCreate(const std::string& fileName, const std::string& name)
{
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(fileName);
    std::string key = fullPath + "#" + name;
    auto skin = MeshSkinCache::getInstance()->getMeshSkin(key);
    if (skin != nullptr)
        return skin;
    
    skin = create(fileName, name);
    MeshSkinCache::getInstance()->addMeshSkin(key, skin);
    
    return skin;
}

//create a new meshskin if do not want to share meshskin
MeshSkin* MeshSkin::create(const std::string& filename, const std::string& name)
{
    
    //load skin here;
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filename);
    auto instance = Bundle3D::getInstance();
    bool ret = instance->load(fullPath);
    if (ret)
    {
        SkinData skindata;
        if (instance->loadSkinData(name, &skindata))
        {
            auto skin = new MeshSkin();
            skin->_bindShape = skindata.bindShape;
            skin->setBoneCount((int)skindata.boneNames.size());
            for (size_t i = 0; i < skindata.boneNames.size(); i++) {
                auto bone = Bone::create(skindata.boneNames[i]);
                bone->_bindPose = skindata.inverseBindPoseMatrices[i];
                skin->addBone(bone);
            }
            for (auto it : skindata.boneChild) {
                auto parent = skin->getBoneByIndex(it.first);
                for (auto childIt : it.second) {
                    auto child = skin->getBoneByIndex(childIt);
                    child->_parent = parent;
                    parent->_children.pushBack(child);
                }
            }
            
            skin->setRootBone(skin->getBoneByIndex(skindata.rootBoneIndex));
            
            skin->autorelease();
            return skin;
        }
    }
    
    
    return nullptr;
}

//get & set bind shape matrix
const Mat4& MeshSkin::getBindShape() const
{
    return _bindShape;
}
void MeshSkin::setBindShape(const float* matrix)
{
    _bindShape.set(matrix);
}

unsigned int MeshSkin::getBoneCount() const
{
    return _bones.size();
}

//get bone
Bone* MeshSkin::getBoneByIndex(unsigned int index) const
{
    return _bones.at(index);
}
Bone* MeshSkin::getBoneByName(const std::string& id) const
{
    for (auto it : _bones) {
        if (it->getName() == id )
            return it;
    }
    return nullptr;
}

//get & set root bone
Bone* MeshSkin::getRootBone() const
{
    return _rootBone;
}
void MeshSkin::setRootBone(Bone* joint)
{
    CC_SAFE_RETAIN(joint);
    CC_SAFE_RELEASE(_rootBone);
    _rootBone = joint;
}

void MeshSkin::setBoneCount(int boneCount)
{
    removeAllBones();
    
    // Resize the joints vector and initialize to NULL
    _bones.reserve(boneCount);
//    for (auto i = 0; i < boneCount; i++)
//    {
//        _bones.pushBack(nullptr);
//    }
    
    // Rebuild the matrix palette. Each matrix is 3 rows of Vec4.
    CC_SAFE_DELETE_ARRAY(_matrixPalette);
    
    if (boneCount > 0)
    {
        _matrixPalette = new Vec4[boneCount * PALETTE_ROWS];
        for (unsigned int i = 0; i < boneCount * PALETTE_ROWS; i+=PALETTE_ROWS)
        {
            _matrixPalette[i+0].set(1.0f, 0.0f, 0.0f, 0.0f);
            _matrixPalette[i+1].set(0.0f, 1.0f, 0.0f, 0.0f);
            _matrixPalette[i+2].set(0.0f, 0.0f, 1.0f, 0.0f);
        }
    }
}

int MeshSkin::getBoneIndex(Bone* joint) const
{
    for (auto i = 0; i < _bones.size(); i++) {
        if (_bones.at(i) == joint)
            return i;
    }
    return -1;
}

//compute matrix palette used by gpu skin
Vec4* MeshSkin::getMatrixPalette()
{
    updateBoneMatrix();
    
    int i = 0;
	for (auto it : _bones )
	{
        it->updateJointMatrix(getBindShape(), &_matrixPalette[i++ * PALETTE_ROWS]);
	}
    
    return _matrixPalette;
}

//getBoneCount() * 3
unsigned int MeshSkin::getMatrixPaletteSize() const
{
    return _bones.size() * PALETTE_ROWS;
}

//refresh bone world matrix
void MeshSkin::updateBoneMatrix()
{
    _rootBone->setWorldMatDirty(true);
    _rootBone->updateWorldMat();
}

void MeshSkin::removeAllBones()
{
    _bones.clear();
    CC_SAFE_DELETE_ARRAY(_matrixPalette);
    CC_SAFE_RELEASE(_rootBone);
}

void MeshSkin::addBone(Bone* bone)
{
    _bones.pushBack(bone);
}

////////////////////////////////////////////////////////////////////////
MeshSkinCache* MeshSkinCache::_cacheInstance = nullptr;

MeshSkinCache* MeshSkinCache::getInstance()
{
    if (_cacheInstance == nullptr)
        _cacheInstance = new MeshSkinCache();
    return _cacheInstance;
}
void MeshSkinCache::purgeMeshSkinCache()
{
    if (_cacheInstance)
    {
        CC_SAFE_DELETE(_cacheInstance);
    }
}

MeshSkin* MeshSkinCache::getMeshSkin(const std::string& key)
{
    auto it = _skins.find(key);
    if (it != _skins.end())
        return it->second;
    
    return nullptr;
}

bool MeshSkinCache::addMeshSkin(const std::string& key, MeshSkin* skin)
{
    if (_skins.find(key) != _skins.end())
        return false; // already have this key
    
    _skins[key] = skin;
    skin->retain();
    return true;
}

void MeshSkinCache::removeAllMeshSkin()
{
    for (auto itr = _skins.begin(); itr != _skins.end(); itr++) {
        CC_SAFE_RELEASE_NULL(itr->second);
    }
    _skins.clear();
}
void MeshSkinCache::removeUnusedMeshSkin()
{
    for( auto it=_skins.cbegin(); it!=_skins.cend(); /* nothing */) {
        auto value = it->second;
        if( value->getReferenceCount() == 1 ) {
            CC_SAFE_RELEASE(value);
            _skins.erase(it++);
        } else {
            ++it;
        }
    }
}

MeshSkinCache::MeshSkinCache()
{
    
}
MeshSkinCache::~MeshSkinCache()
{
    
}

NS_CC_END
