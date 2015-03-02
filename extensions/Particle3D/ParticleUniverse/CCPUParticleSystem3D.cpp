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

#include "Particle3D/ParticleUniverse/CCPUParticleSystem3D.h"
#include "Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DEmitter.h"
#include "Particle3D/ParticleUniverse/ParticleEmitters/CCPUParticle3DEmitterManager.h"
#include "Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DAffector.h"
#include "Particle3D/ParticleUniverse/ParticleAffectors/CCPUParticle3DAffectorManager.h"
#include "Particle3D/CCParticle3DRender.h"
#include "Particle3D/ParticleUniverse/CCPUParticle3DScriptCompiler.h"
#include "Particle3D/ParticleUniverse/CCPUParticle3DMaterialManager.h"
#include "Particle3D/ParticleUniverse/CCPUParticle3DTranslateManager.h"
#include "Particle3D/ParticleUniverse/CCPUParticle3DListener.h"
#include "Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DObserver.h"
#include "Particle3D/ParticleUniverse/ParticleObservers/CCPUParticle3DObserverManager.h"
#include "Particle3D/ParticleUniverse/ParticleBehaviours/CCPUParticle3DBehaviour.h"
#include "platform/CCFileUtils.h"

NS_CC_BEGIN

float PUParticle3D::DEFAULT_TTL = 10.0f;
float PUParticle3D::DEFAULT_MASS = 1.0f;

float PUParticle3D::calculateVelocity() const
{
    if (originalScaledDirectionLength != 0)
    {
        return originalVelocity * (direction.length() / originalScaledDirectionLength);
    }
    else
    {
        // Assume originalScaledDirectionLength to be 1.0 (unit vector)
        return originalVelocity * direction.length();
    }
}

void PUParticle3D::setOwnDimensions( float newWidth, float newHeight, float newDepth )
{
    ownDimensions = true;
    if (newWidth)
        width = newWidth;
    if (newHeight)
        height = newHeight;
    if (newDepth)
        depth = newDepth;
    calculateBoundingSphereRadius();
    //parentEmitter->getParentTechnique()->_notifyParticleResized();
}

void PUParticle3D::calculateBoundingSphereRadius()
{
    //radius = 0.5 * Math::Sqrt(width*width + height*height + depth*depth);
    radius = 0.5f * std::max(depth, std::max(width, height)); // approximation
}

void PUParticle3D::initForEmission()
{
    eventFlags = 0;
    timeFraction = 0.0f;
    /*	Note, that this flag must only be set as soon as the particle is emitted. As soon as the particle has
        been moved once, the flag must be removed again.
    */
    addEventFlags(PUParticle3D::PEF_EMITTED);

    // Reset freeze flag
    freezed = false;

    for (auto it : behaviours) {
        it->initParticleForEmission(this);
    }
}

void PUParticle3D::initForExpiration( float timeElapsed )
{
    for (auto it : behaviours) {
        it->initParticleForExpiration(this, timeElapsed);
    }
}

void PUParticle3D::process( float timeElapsed )
{
    timeFraction = (totalTimeToLive - timeToLive) / totalTimeToLive;

    for (auto it : behaviours) {
        it->updateBehaviour(this, timeElapsed);
    }
}

PUParticle3D::PUParticle3D():
    //position(Vec3::ZERO),
    particleEntityPtr(nullptr),
    visualData(nullptr),
    particleType(PT_VISUAL),
    direction(Vec3::ZERO),
    timeToLive(DEFAULT_TTL),
    totalTimeToLive(DEFAULT_TTL),
    timeFraction(0.0f),
    mass(DEFAULT_MASS),
    eventFlags(0),
    freezed(false),
    originalPosition(Vec3::ZERO),
    latestPosition(Vec3::ZERO),
    originalDirection(Vec3::ZERO),
    originalDirectionLength(0.0f),
    originalScaledDirectionLength(0.0f),
    originalVelocity(0.0f),
    parentEmitter(nullptr),
    //color(Vec4::ONE),
    originalColor(Vec4::ONE),
    //zRotation(0.0f),
    zRotationSpeed(0.0f),
    rotationSpeed(0.0f),
    rotationAxis(Vec3::UNIT_Z),
    ownDimensions(false),
    radius(0.87f),
    textureAnimationTimeStep(0.1f),
    textureAnimationTimeStepCount(0.0f),
    textureCoordsCurrent(0),
    textureAnimationDirectionUp(true),
    depthInView(0.0f),
    zRotation(0.0f)
    //widthInWorld(width),
    //heightInWorld(height),
    //depthInWorld(depth)
{
}

PUParticle3D::~PUParticle3D()
{
    for (auto it : behaviours) {
        it->release();
    }

    //CC_SAFE_RELEASE(particleEntityPtr);
}

void PUParticle3D::copyBehaviours( const ParticleBehaviourList &list )
{
    for (auto it : list){
        auto behaviour = it->clone();
        behaviour->retain();
        behaviours.push_back(behaviour);
    }
}

//-----------------------------------------------------------------------

const float PUParticleSystem3D::DEFAULT_WIDTH = 50;
const float PUParticleSystem3D::DEFAULT_HEIGHT = 50;
const float PUParticleSystem3D::DEFAULT_DEPTH = 50;
const unsigned int PUParticleSystem3D::DEFAULT_PARTICLE_QUOTA = 500;
const unsigned int PUParticleSystem3D::DEFAULT_EMITTED_EMITTER_QUOTA = 50;
const unsigned int PUParticleSystem3D::DEFAULT_EMITTED_SYSTEM_QUOTA = 10;
const float PUParticleSystem3D::DEFAULT_MAX_VELOCITY = 9999.0f;

PUParticleSystem3D::PUParticleSystem3D()
: _emittedEmitterQuota(DEFAULT_EMITTED_EMITTER_QUOTA)
, _emittedSystemQuota(DEFAULT_EMITTED_SYSTEM_QUOTA)
, _prepared(false)
, _poolPrepared(false)
, _particleSystemScaleVelocity(1.0f)
, _defaultWidth(DEFAULT_WIDTH)
, _defaultHeight(DEFAULT_HEIGHT)
, _defaultDepth(DEFAULT_DEPTH)
, _maxVelocity(DEFAULT_MAX_VELOCITY)
, _maxVelocitySet(false)
, _isMarkedForEmission(false)
, _timeElapsedSinceStart(0.0f)
, _parentParticleSystem(nullptr)
{
    _particleQuota = DEFAULT_PARTICLE_QUOTA;
}
PUParticleSystem3D::~PUParticleSystem3D()
{
    stopParticleSystem();
    unPrepared();

    _particlePool.removeAllDatas();

    for (auto iter : _emittedEmitterParticlePool){
        auto pool = iter.second;
        auto lockedList = pool.getUnActiveDataList();
        for (auto iter : lockedList){
            static_cast<PUParticle3D *>(iter)->particleEntityPtr->release();
        }
        iter.second.removeAllDatas();
    }

    for (auto iter : _emittedSystemParticlePool){
        auto pool = iter.second;
        auto lockedList = pool.getUnActiveDataList();
        for (auto iter : lockedList){
            static_cast<PUParticle3D *>(iter)->particleEntityPtr->release();
        }
        iter.second.removeAllDatas();
    }

    //release all emitters
    for (auto it : _emitters) {
        it->release();
    }
    _emitters.clear();

    for (auto it : _observers){
        it->release();
    }

    for (auto it : _behaviourTemplates) {
        it->release();
    }

    _observers.clear();
}

PUParticleSystem3D* PUParticleSystem3D::create()
{
    auto pups = new PUParticleSystem3D();
    pups->autorelease();
    return pups;
}

PUParticleSystem3D* PUParticleSystem3D::create( const std::string &filePath, const std::string &materialPath )
{
    std::string matfullPath = FileUtils::getInstance()->fullPathForFilename(materialPath);
    convertToUnixStylePath(matfullPath);
    PUParticle3DMaterialCache::Instance()->loadMaterials(matfullPath);
    PUParticleSystem3D* ps = PUParticleSystem3D::create();
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filePath);
    convertToUnixStylePath(fullPath);
    if (!ps->initSystem(fullPath)){
        CC_SAFE_DELETE(ps);
    }
    return ps;
}

PUParticleSystem3D* PUParticleSystem3D::create( const std::string &filePath )
{
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filePath);
    convertToUnixStylePath(fullPath);
    std::string::size_type pos = fullPath.find_last_of("/");
    std::string materialFolder = "materials";
    if (pos != std::string::npos){
        std::string temp = fullPath.substr(0, pos);
        pos = temp.find_last_of("/");
        if (pos != std::string::npos){
            materialFolder = temp.substr(0, pos + 1) + materialFolder;
        }
    }
    static std::vector<std::string> loadedFolder;
    if (std::find(loadedFolder.begin(), loadedFolder.end(), materialFolder) == loadedFolder.end())
    {
        PUParticle3DMaterialCache::Instance()->loadMaterialsFromSearchPaths(materialFolder);
        loadedFolder.push_back(materialFolder);
    }
    
    PUParticleSystem3D* ps = PUParticleSystem3D::create();
    if (!ps->initSystem(fullPath)){
        CC_SAFE_DELETE(ps);
    }
    return ps;
}

void PUParticleSystem3D::startParticleSystem()
{
    stopParticleSystem();

    if (_state != State::RUNNING)
    {
        //if (_emitter)
        //{
        //    auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
        //    emitter->notifyStart();
        //}

        if (_render)
            _render->notifyStart();

        for (auto &it : _observers){
            it->notifyStart();
        }

        for (auto& it : _emitters) {
            auto emitter = static_cast<PUParticle3DEmitter*>(it);
            emitter->notifyStart();
        }

        for (auto& it : _affectors) {
            auto affector = static_cast<PUParticle3DAffector*>(it);
            affector->notifyStart();
        }

        scheduleUpdate();
        _state = State::RUNNING;
        _latestPosition = getDerivedPosition(); // V1.3.1
    }

    for (auto iter : _children)
    {
        PUParticleSystem3D *system = dynamic_cast<PUParticleSystem3D *>(iter);
        if (system){
            system->_parentParticleSystem = this;
            system->startParticleSystem();
        }
    }
}

void PUParticleSystem3D::stopParticleSystem()
{
    if (_state != State::STOP)
    {
        _state = State::STOP;
    }

    for (auto iter : _children)
    {
        PUParticleSystem3D *system = dynamic_cast<PUParticleSystem3D *>(iter);
        if (system)
            system->stopParticleSystem();
    }
}

void PUParticleSystem3D::pauseParticleSystem()
{
    if (_state == State::RUNNING)
    {
        //if (_emitter)
        //{
        //    auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
        //    emitter->notifyPause();
        //}

        for (auto& it : _emitters) {
            auto emitter = static_cast<PUParticle3DEmitter*>(it);
            emitter->notifyPause();
        }

        for (auto& it : _affectors) {
            auto affector = static_cast<PUParticle3DAffector*>(it);
            affector->notifyPause();
        }

        _state = State::PAUSE;
    }

    for (auto iter : _children)
    {
        PUParticleSystem3D *system = dynamic_cast<PUParticleSystem3D *>(iter);
        if (system)
            system->pauseParticleSystem();
    }
}

void PUParticleSystem3D::resumeParticleSystem()
{
    if (_state == State::PAUSE)
    {
        //if (_emitter)
        //{
        //    auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
        //    emitter->notifyResume();
        //}

        for (auto& it : _emitters) {
            auto emitter = static_cast<PUParticle3DEmitter*>(it);
            emitter->notifyResume();
        }

        for (auto& it : _affectors) {
            auto affector = static_cast<PUParticle3DAffector*>(it);
            affector->notifyResume();
        }

        _state = State::RUNNING;
    }

    for (auto iter : _children)
    {
        PUParticleSystem3D *system = dynamic_cast<PUParticleSystem3D *>(iter);
        if (system)
            system->resumeParticleSystem();
    }
}

void PUParticleSystem3D::update(float delta)
{
    if (_isMarkedForEmission) return;
    if (_state != State::RUNNING){
        if (_state == State::PAUSE) 
            return;
        else if (_state == State::STOP && getAliveParticleCnt() <= 0){
            if (!_emitters.empty()){
                if (_render)
                    _render->notifyStop();

                for (auto &it : _observers){
                    it->notifyStop();
                }

                for (auto& it : _emitters) {
                    auto emitter = static_cast<PUParticle3DEmitter*>(it);
                    emitter->notifyStop();
                }

                for (auto& it : _affectors) {
                    auto affector = static_cast<PUParticle3DAffector*>(it);
                    affector->notifyStop();
                }

                unscheduleUpdate();
                unPrepared();
                return;
            }
        }
    }

    forceUpdate(delta);
}

void PUParticleSystem3D::forceUpdate( float delta )
{
    if (!_emitters.empty()){
        calulateRotationOffset();
        prepared();
        emitParticles(delta);
        preUpdator(delta);
        updator(delta);
        postUpdator(delta);
    }

    Vec3 currentPos = getDerivedPosition();
    _latestPositionDiff = currentPos - _latestPosition;
    _latestPosition = currentPos;
    _latestOrientation = getDerivedOrientation();
    _timeElapsedSinceStart += delta;
}

float PUParticleSystem3D::getParticleSystemScaleVelocity() const
{
    return _particleSystemScaleVelocity;
}

void PUParticleSystem3D::rotationOffset( Vec3& pos )
{
    Mat4 rotMat;
    Mat4::createRotation(_rotationOffset, &rotMat);
    pos = _rotationCentre + rotMat * (pos - _rotationCentre);
}

void PUParticleSystem3D::prepared()
{
    if (!_prepared){
        //if (_emitter && _emitter->isEnabled())
        //{
        //    auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
        //    emitter->prepare();
        //}

        if (_render)
            static_cast<PUParticle3DRender *>(_render)->prepare();

        for (auto it : _behaviourTemplates) {
            it->prepare();
        }

        for (auto it : _emitters) {
            //if (it->isEnabled())
                (static_cast<PUParticle3DEmitter*>(it))->prepare();
        }

        for (auto it : _affectors) {
            //if (it->isEnabled())
                (static_cast<PUParticle3DAffector*>(it))->prepare();
        }
        
        if (!_poolPrepared){
            for (auto it : _emitters) {
                //if (it->isEnabled())
                PUParticle3DEmitter *emitter = static_cast<PUParticle3DEmitter*>(it);
                if (emitter->getEmitsType() == PUParticle3D::PT_EMITTER){
                    PUParticle3DEmitter *emitted = static_cast<PUParticle3DEmitter*>(emitter->getEmitsEntityPtr());
                    for (unsigned int i = 0; i < _emittedEmitterQuota; ++i){
                        auto p = new PUParticle3D();
                        p->particleType = PUParticle3D::PT_EMITTER;
                        p->particleEntityPtr = emitted->clone();
                        p->particleEntityPtr->retain();
                        p->autorelease();
                        p->copyBehaviours(_behaviourTemplates);
                        _emittedEmitterParticlePool[emitted->getName()].addData(p);
                    }
                }
                else if (emitter->getEmitsType() == PUParticle3D::PT_TECHNIQUE){
                    PUParticleSystem3D *emitted = static_cast<PUParticleSystem3D*>(emitter->getEmitsEntityPtr());
                    for (unsigned int i = 0; i < _emittedSystemQuota; ++i){
                        PUParticleSystem3D *clonePS = emitted->clone();
                        auto p = new PUParticle3D();
                        p->particleType = PUParticle3D::PT_TECHNIQUE;
                        p->particleEntityPtr = clonePS;
                        p->particleEntityPtr->retain();
                        p->autorelease();
                        p->copyBehaviours(_behaviourTemplates);
                        _emittedSystemParticlePool[emitted->getName()].addData(p);
                        clonePS->prepared();
                    }
                    //emitted->stopParticle();
                }

            }

            for (unsigned int i = 0; i < _particleQuota; ++i){
                auto p = new PUParticle3D();
                p->autorelease();
                p->copyBehaviours(_behaviourTemplates);
                _particlePool.addData(p);
            }
            _poolPrepared = true;
        }

        _prepared = true;
        _timeElapsedSinceStart = 0.0f;
    }

    notifyRescaled(getDerivedScale());
}

void PUParticleSystem3D::unPrepared()
{
    //if (_emitter && _emitter->isEnabled())
    //{
    //     auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
    //    emitter->unPrepare();
    //}

    if (_render)
        static_cast<PUParticle3DRender *>(_render)->unPrepare();

    for (auto it : _behaviourTemplates) {
        it->unPrepare();
    }

    for (auto it : _emitters) {
        if (it->isEnabled())
            (static_cast<PUParticle3DEmitter*>(it))->unPrepare();
    }

    for (auto it : _affectors) {
        if (it->isEnabled())
            (static_cast<PUParticle3DAffector*>(it))->unPrepare();
    }

    _particlePool.lockAllDatas();
    for (auto &iter : _emittedEmitterParticlePool){
        PUParticle3D *particle = static_cast<PUParticle3D *>(iter.second.getFirst());
        while (particle)
        {
            static_cast<PUParticle3DEmitter*>(particle->particleEntityPtr)->unPrepare();
            particle = static_cast<PUParticle3D *>(iter.second.getNext());
        }
        iter.second.lockAllDatas();
    }

    for (auto &iter : _emittedSystemParticlePool){
        PUParticle3D *particle = static_cast<PUParticle3D *>(iter.second.getFirst());
        while (particle)
        {
            static_cast<PUParticleSystem3D*>(particle->particleEntityPtr)->unPrepared();
            particle = static_cast<PUParticle3D *>(iter.second.getNext());
        }
        iter.second.lockAllDatas();
    }
    _prepared = false;
}

void PUParticleSystem3D::preUpdator( float elapsedTime )
{
    //if (_emitter && _emitter->isEnabled())
    //{
    //     auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
    //    emitter->preUpdateEmitter(elapsedTime);
    //}
    //bool hasNoEmitted = true;
    for (auto it : _emitters) {
        if (!it->isEmitterDone()){
            (static_cast<PUParticle3DEmitter*>(it))->preUpdateEmitter(elapsedTime);
            //hasNoEmitted = false;
        }
    }

    //if (hasNoEmitted){
    //    if (_particlePool.getActiveParticleList().empty())
    //        stopParticle();
    //}

    for (auto it : _affectors) {
        if (it->isEnabled()){
            (static_cast<PUParticle3DAffector*>(it))->preUpdateAffector(elapsedTime);
        }
    }

    for (auto it : _observers){
        if (it->isEnabled()){
            it->preUpdateObserver(elapsedTime);
        }
    }

    for (auto &iter : _emittedEmitterParticlePool){
        PUParticle3D *particle = static_cast<PUParticle3D *>(iter.second.getFirst());
        while (particle)
        {
            static_cast<PUParticle3DEmitter*>(particle->particleEntityPtr)->preUpdateEmitter(elapsedTime);
            particle = static_cast<PUParticle3D *>(iter.second.getNext());
        }
    }

    for (auto &iter : _emittedSystemParticlePool){
        PUParticle3D *particle = static_cast<PUParticle3D *>(iter.second.getFirst());
        while (particle)
        {
            static_cast<PUParticleSystem3D*>(particle->particleEntityPtr)->preUpdator(elapsedTime);
            particle = static_cast<PUParticle3D *>(iter.second.getNext());
        }
    }
}

void PUParticleSystem3D::updator( float elapsedTime )
{
    bool firstActiveParticle = true;
    bool firstParticle = true;
    processParticle(_particlePool, firstActiveParticle, firstParticle, elapsedTime);

    for (auto &iter : _emittedEmitterParticlePool){
        processParticle(iter.second, firstActiveParticle, firstParticle, elapsedTime);
    }

    for (auto &iter : _emittedSystemParticlePool){
        processParticle(iter.second, firstActiveParticle, firstParticle, elapsedTime);
    }
}

void PUParticleSystem3D::postUpdator( float elapsedTime )
{
    //if (_emitter && _emitter->isEnabled())
    //{
    //    auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
    //    emitter->postUpdateEmitter(elapsedTime);
    //}

    for (auto it : _emitters) {
        if (it->isEnabled()){
            (static_cast<PUParticle3DEmitter*>(it))->postUpdateEmitter(elapsedTime);
        }
    }

    for (auto it : _affectors) {
        if (it->isEnabled())
        {
            auto affector = static_cast<PUParticle3DAffector*>(it);
            affector->postUpdateAffector(elapsedTime);
        }
    }

    for (auto it : _observers){
        if (it->isEnabled()){
            it->postUpdateObserver(elapsedTime);
        }
    }

    for (auto &iter : _emittedEmitterParticlePool){
        PUParticle3D *particle = static_cast<PUParticle3D *>(iter.second.getFirst());
        while (particle)
        {
            static_cast<PUParticle3DEmitter*>(particle->particleEntityPtr)->postUpdateEmitter(elapsedTime);
            particle = static_cast<PUParticle3D *>(iter.second.getNext());
        }
    }

    for (auto &iter : _emittedSystemParticlePool){
        PUParticle3D *particle = static_cast<PUParticle3D *>(iter.second.getFirst());
        while (particle)
        {
            static_cast<PUParticleSystem3D*>(particle->particleEntityPtr)->postUpdator(elapsedTime);
            particle = static_cast<PUParticle3D *>(iter.second.getNext());
        }
    }
}

void PUParticleSystem3D::emitParticles( float elapsedTime )
{
    //Vec3 scale = getDerivedScale();
    for (auto iter : _emitters){
        //if (!_emitter) return;
        //auto emitter = static_cast<PUParticle3DEmitter*>(_emitter);
        auto emitter = iter;
        //emitter->notifyRescaled(scale);
        if (!iter->isMarkedForEmission()){
            unsigned short requested = emitter->calculateRequestedParticles(elapsedTime);
            executeEmitParticles(emitter, requested, elapsedTime);
        }
    }

}

const float PUParticleSystem3D::getDefaultWidth( void ) const
{
    return _defaultWidth;
}

void PUParticleSystem3D::setDefaultWidth( const float width )
{
    _defaultWidth = width;
}

const float PUParticleSystem3D::getDefaultHeight( void ) const
{
    return _defaultHeight;
}

void PUParticleSystem3D::setDefaultHeight( const float height )
{
    _defaultHeight = height;
}

const float PUParticleSystem3D::getDefaultDepth( void ) const
{
    return _defaultDepth;
}

void PUParticleSystem3D::setDefaultDepth( const float depth )
{
    _defaultDepth = depth;
}

bool PUParticleSystem3D::isExpired( PUParticle3D* particle, float timeElapsed )
{
    bool expired = particle->timeToLive < timeElapsed;
    if (expired)
    {
        // Set the flag to indicate that the particle has been expired
        particle->addEventFlags(PUParticle3D::PEF_EXPIRED);
    }

    return expired;
}

cocos2d::Vec3 PUParticleSystem3D::getDerivedPosition()
{
    //if (_parentParticleSystem && _parentParticleSystem->isKeepLocal()) return Vec3::ZERO; 
    //if (_keepLocal) return Vec3::ZERO;
    if (_isMarkedForEmission){
        return Vec3(_position.x, _position.y, _positionZ);
    }else{
        Mat4 mat = getNodeToWorldTransform();
        return Vec3(mat.m[12], mat.m[13], mat.m[14]);
    }
}

cocos2d::Quaternion PUParticleSystem3D::getDerivedOrientation()
{
    //if (_parentParticleSystem && _parentParticleSystem->isKeepLocal()) return Quaternion(); 
    //if (_keepLocal) return Quaternion();
    if (_isMarkedForEmission){
        return getRotationQuat();
    }else{
        Quaternion q;
        Mat4 mat = getNodeToWorldTransform();
        mat.decompose(nullptr, &q, nullptr);
        return q;
    }
}

cocos2d::Vec3 PUParticleSystem3D::getDerivedScale()
{
    //if (_parentParticleSystem && _parentParticleSystem->isKeepLocal()) return Vec3::ONE; 
    //if (_keepLocal) return Vec3::ONE;
    if (_isMarkedForEmission){
        return Vec3(_scaleX, _scaleY, _scaleZ);
    }else{
        Vec3 s;
        Mat4 mat = getNodeToWorldTransform();
        mat.decompose(&s, nullptr, nullptr);
        return s;
    }
}

float PUParticleSystem3D::getMaxVelocity() const
{
    return _maxVelocity;
}

void PUParticleSystem3D::setMaxVelocity( float maxVelocity )
{
    _maxVelocity = maxVelocity;
    _maxVelocitySet = true;
}

bool PUParticleSystem3D::initSystem( const std::string &filePath )
{
    bool isFirstCompile = true;
    auto list = PUScriptCompiler::Instance()->compile(filePath, isFirstCompile);
    if (list == nullptr || list->empty()) return false;
    PUParticle3DTranslateManager::Instance()->translateParticleSystem(this, list);
    //std::string  data = FileUtils::getInstance()->getStringFromFile(filePath);
    return true;
}

void PUParticleSystem3D::addEmitter( PUParticle3DEmitter* emitter )
{
    if (emitter && std::find(_emitters.begin(), _emitters.end(), emitter) == _emitters.end()){
        emitter->_particleSystem = this;
        emitter->retain();
        _emitters.push_back(emitter);
    }
}

PUParticle3DAffector* PUParticleSystem3D::getAffector( const std::string &name )
{
    for (auto iter : _affectors){
        auto pa = static_cast<PUParticle3DAffector *>(iter);
        if (pa->getName() == name)
            return pa;
    }

    return nullptr;
}

PUParticle3DEmitter* PUParticleSystem3D::getEmitter( const std::string &name )
{
    for (auto iter : _emitters){
        auto pe = static_cast<PUParticle3DEmitter *>(iter);
        if (pe->getName() == name)
            return pe;
    }

    return nullptr;
}

void PUParticleSystem3D::addListener( PUParticle3DListener *listener )
{
    auto iter = std::find(_listeners.begin(), _listeners.end(), listener);
    if (iter == _listeners.end()){
        _listeners.push_back(listener);
    }
}

void PUParticleSystem3D::removeListener( PUParticle3DListener *listener )
{
    auto iter = std::find(_listeners.begin(), _listeners.end(), listener);
    if (iter != _listeners.end()){
        _listeners.erase(iter);
    }
}

void PUParticleSystem3D::forceEmission( PUParticle3DEmitter* emitter, unsigned requested )
{
    // Fast rejection: Don't emit if the technique is not enabled
    if (!_isEnabled)
        return;

    executeEmitParticles(emitter, requested, 0);
}

void PUParticleSystem3D::executeEmitParticles( PUParticle3DEmitter* emitter, unsigned requested, float elapsedTime )
{
    if (_state == State::STOP) return;
    if (emitter->getEmitsType() == PUParticle3D::PT_VISUAL){
        emitParticles(_particlePool, emitter, requested, elapsedTime);
    }else if (emitter->getEmitsType() == PUParticle3D::PT_EMITTER){
        emitParticles(_emittedEmitterParticlePool[emitter->getEmitsName()], emitter, requested, elapsedTime);
    }else if (emitter->getEmitsType() == PUParticle3D::PT_TECHNIQUE){
        emitParticles(_emittedSystemParticlePool[emitter->getEmitsName()], emitter, requested, elapsedTime);
    }
}

void PUParticleSystem3D::emitParticles( ParticlePool &pool, PUParticle3DEmitter* emitter, unsigned requested, float elapsedTime )
{
    Vec3 scale = getDerivedScale();
    Mat4 rotMat;
    Mat4::createRotation(getDerivedOrientation(), &rotMat);
    float timePoint = 0.0f;
    float timeInc = elapsedTime / requested;
    Ref *emittedPtr = nullptr;
    for (unsigned short i = 0; i < requested; ++i)
    {
        PUParticle3D *particle = static_cast<PUParticle3D *>(pool.createData());
        if (!particle) 
            return;

        particle->initForEmission();
        emitter->initParticleForEmission(particle);

        particle->direction = (rotMat * Vec3(particle->direction.x * scale.x, particle->direction.y * scale.y, particle->direction.z * scale.z));
        particle->originalDirection = (rotMat * Vec3(particle->originalDirection.x * scale.x, particle->originalDirection.y * scale.y, particle->originalDirection.z * scale.z));

        for (auto& it : _affectors) {
            if (it->isEnabled())
            {
                (static_cast<PUParticle3DAffector*>(it))->notifyRescaled(scale);
                (static_cast<PUParticle3DAffector*>(it))->initParticleForEmission(particle);
            }
        }

        initParticleForEmission(particle);

        particle->position += (particle->direction * _particleSystemScaleVelocity * timePoint);
        // Increment time fragment
        timePoint += timeInc;
    }
}

void PUParticleSystem3D::addObserver( PUParticle3DObserver *observer )
{
    auto iter = std::find(_observers.begin(), _observers.end(), observer);
    if (iter == _observers.end()){
        observer->retain();
        observer->_particleSystem = this;
        _observers.push_back(observer);
    }
}

PUParticle3DObserver* PUParticleSystem3D::getObserver( const std::string &name )
{
    for (auto iter : _observers){
        auto po = static_cast<PUParticle3DObserver *>(iter);
        if (po->getName() == name)
            return po;
    }

    return nullptr;
}

void PUParticleSystem3D::notifyRescaled(const Vec3 &scl)
{
    if (_render)
        _render->notifyRescaled(scl);

    for (auto it : _emitters) {
        (static_cast<PUParticle3DEmitter*>(it))->notifyRescaled(scl);
    }

    for (auto it : _affectors) {
        (static_cast<PUParticle3DAffector*>(it))->notifyRescaled(scl);
    }

    for (auto it : _observers){
        it->notifyRescaled(scl);
    }

    for (auto &iter : _emittedEmitterParticlePool){
        PUParticle3D *particle = static_cast<PUParticle3D *>(iter.second.getFirst());
        while (particle)
        {
            static_cast<PUParticle3DEmitter*>(particle->particleEntityPtr)->notifyRescaled(scl);
            particle = static_cast<PUParticle3D *>(iter.second.getNext());
        }
    }

    for (auto &iter : _emittedSystemParticlePool){
        PUParticle3D *particle = static_cast<PUParticle3D *>(iter.second.getFirst());
        while (particle)
        {
            static_cast<PUParticleSystem3D*>(particle->particleEntityPtr)->notifyRescaled(scl);
            particle = static_cast<PUParticle3D *>(iter.second.getNext());
        }
    }
}

void PUParticleSystem3D::initParticleForExpiration( PUParticle3D* particle, float timeElapsed )
{
    if (particle->particleType == PUParticle3D::PT_EMITTER){
        PUParticle3DEmitter *emitter = static_cast<PUParticle3DEmitter *>(particle->particleEntityPtr);
        emitter->unPrepare();
    }else if (particle->particleType == PUParticle3D::PT_TECHNIQUE){
        PUParticleSystem3D *system = static_cast<PUParticleSystem3D *>(particle->particleEntityPtr);
        system->unPrepared();
    }

    particle->initForExpiration(timeElapsed);

    for (auto it : _listeners){
        it->particleExpired(this, particle);
    }
    ///** Externs are also called to perform expiration activities. If needed, affectors and emitters may be added, but at the moment
    //	there is no reason for (and we don�t want to waste cpu resources).
    //*/
    //if (!mExterns.empty())
    //{
    //	ExternIterator itExtern;
    //	ExternIterator itExternEnd = mExterns.end();
    //	for (itExtern = mExterns.begin(); itExtern != itExternEnd; ++itExtern)
    //	{
    //		(*itExtern)->_initParticleForExpiration(particle);
    //	}
    //}
}

void PUParticleSystem3D::initParticleForEmission( PUParticle3D* particle )
{
    for (auto it : _listeners){
        it->particleEmitted(this, particle);
    }
}

void PUParticleSystem3D::addBehaviourTemplate( PUParticle3DBehaviour *behaviour )
{
    auto iter = std::find(_behaviourTemplates.begin(), _behaviourTemplates.end(), behaviour);
    if (iter == _behaviourTemplates.end()){
        behaviour->retain();
        behaviour->_particleSystem = this;
        _behaviourTemplates.push_back(behaviour);
    }
}


void PUParticleSystem3D::convertToUnixStylePath( std::string &path )
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    for (auto &iter : path){
        if (iter == '\\') iter = '/';
    }
#endif
}

void PUParticleSystem3D::clearAllParticles()
{
    _particlePool.lockAllDatas();
    for (auto &iter : _emittedEmitterParticlePool){
        iter.second.lockAllDatas();
    }

    for (auto &iter : _emittedSystemParticlePool){
        iter.second.lockAllDatas();
    }
}

void PUParticleSystem3D::copyAttributesTo( PUParticleSystem3D* system )
{
    system->removeAllEmitter();
    system->removeAllAffector();
    system->removerAllObserver();
    system->removeAllBehaviourTemplate();
    system->removeAllListener();
    system->_particlePool.removeAllDatas();
    for (auto iter : system->_emittedEmitterParticlePool){
        iter.second.removeAllDatas();
    }

    for (auto iter : system->_emittedSystemParticlePool){
        iter.second.removeAllDatas();
    }

    system->setName(_name);
    system->_state = _state;
    system->setRender(static_cast<PUParticle3DRender *>(_render)->clone());
    system->_particleQuota = _particleQuota;
    system->_blend = _blend;
    system->_keepLocal = _keepLocal;
    system->_isEnabled = _isEnabled;

    for (auto iter : _affectors){
        PUParticle3DAffector *affector = static_cast<PUParticle3DAffector *>(iter);
        PUParticle3DAffector *copy = PUParticle3DAffectorManager::Instance()->createAffector(affector->getAffectorType());
        affector->copyAttributesTo(copy);
        system->addAffector(copy);
    }

    for (auto iter : _emitters){
        PUParticle3DEmitter *emitter = static_cast<PUParticle3DEmitter *>(iter);
        PUParticle3DEmitter *copy = PUParticle3DEmitterManager::Instance()->createEmitter(emitter->getEmitterType());
        emitter->copyAttributesTo(copy);
        system->addEmitter(copy);
    }

    for (auto iter : _observers){
        PUParticle3DObserver *observer = static_cast<PUParticle3DObserver *>(iter);
        PUParticle3DObserver *copy = PUParticle3DObserverManager::Instance()->createObserver(observer->getObserverType());
        observer->copyAttributesTo(copy);
        system->addObserver(copy);
    }

    for (auto iter : _behaviourTemplates){
        PUParticle3DBehaviour *behaviour = static_cast<PUParticle3DBehaviour *>(iter);
        PUParticle3DBehaviour *copy = behaviour->clone();
        system->addBehaviourTemplate(copy);
    }

    system->_emittedEmitterQuota = _emittedEmitterQuota;
    system->_emittedSystemQuota = _emittedSystemQuota;
    system->_prepared = false;
    system->_particleSystemScaleVelocity = _particleSystemScaleVelocity;
    system->_defaultWidth = _defaultWidth;
    system->_defaultHeight = _defaultHeight;
    system->_defaultDepth = _defaultDepth;
    system->_maxVelocity = _maxVelocity;
    system->_maxVelocitySet = _maxVelocitySet;
    system->_matName = _matName;
    system->_isMarkedForEmission = _isMarkedForEmission;
    system->_parentParticleSystem = _parentParticleSystem;
}

PUParticleSystem3D* PUParticleSystem3D::clone()
{
    auto ps = PUParticleSystem3D::create();
    copyAttributesTo(ps);
    return ps;
}

void PUParticleSystem3D::removeAllEmitter()
{
    for (auto iter : _emitters){
        iter->release();
    }
    _emitters.clear();
}

void PUParticleSystem3D::removerAllObserver()
{
    for (auto iter : _observers){
        iter->release();
    }
    _observers.clear();
}

void PUParticleSystem3D::removeAllBehaviourTemplate()
{
    for (auto iter : _behaviourTemplates){
        iter->release();
    }
    _behaviourTemplates.clear();
}

void PUParticleSystem3D::removeAllListener()
{
    _listeners.clear();
}

void PUParticleSystem3D::draw( Renderer *renderer, const Mat4 &transform, uint32_t flags )
{
    if (getAliveParticleCnt() <= 0) return;
    if (_render)
        _render->render(renderer, transform, this);

    if (!_emittedSystemParticlePool.empty())
    {
        for (auto iter : _emittedSystemParticlePool){
            PUParticle3D *particle = static_cast<PUParticle3D *>(iter.second.getFirst());
            while (particle)
            {
                static_cast<PUParticleSystem3D *>(particle->particleEntityPtr)->draw(renderer, transform, flags);
                particle = static_cast<PUParticle3D *>(iter.second.getNext());
            }
        }
    }
}

void PUParticleSystem3D::processParticle( ParticlePool &pool, bool &firstActiveParticle, bool &firstParticle, float elapsedTime )
{
    PUParticle3D *particle = static_cast<PUParticle3D *>(pool.getFirst());
    //Mat4 ltow = getNodeToWorldTransform();
    //Vec3 scl;
    //Quaternion rot;
    //ltow.decompose(&scl, &rot, nullptr);
    while (particle){

        if (!isExpired(particle, elapsedTime)){
            particle->process(elapsedTime);

            //if (_emitter && _emitter->isEnabled())
            //    _emitter->updateEmitter(particle, elapsedTime);

            for (auto it : _emitters) {
                if (it->isEnabled() && !it->isMarkedForEmission()){
                    (static_cast<PUParticle3DEmitter*>(it))->updateEmitter(particle, elapsedTime);
                }
            }

            for (auto& it : _affectors) {
                if (it->isEnabled()){
                    (static_cast<PUParticle3DAffector*>(it))->process(particle, elapsedTime, firstActiveParticle);
                }
            }

            if (_render)
                static_cast<PUParticle3DRender *>(_render)->updateRender(particle, elapsedTime, firstActiveParticle);

            if (_isEnabled && particle->particleType != PUParticle3D::PT_VISUAL){
                if (particle->particleType == PUParticle3D::PT_EMITTER){
                    auto emitter = static_cast<PUParticle3DEmitter *>(particle->particleEntityPtr);
                    emitter->setLocalPosition(particle->position);
                    executeEmitParticles(emitter, emitter->calculateRequestedParticles(elapsedTime), elapsedTime);
                }else if (particle->particleType == PUParticle3D::PT_TECHNIQUE){
                    auto system = static_cast<PUParticleSystem3D *>(particle->particleEntityPtr);
                    system->setPosition3D(particle->position);
                    system->setRotationQuat(particle->orientation);
                    //system->setScaleX(scl.x);system->setScaleY(scl.y);system->setScaleZ(scl.z);
                    system->forceUpdate(elapsedTime);
                }
            }

            firstActiveParticle = false;
            // Keep latest position
            particle->latestPosition = particle->position;

            //if (_maxVelocitySet && particle->calculateVelocity() > _maxVelocity)
            //{
            //    particle->direction *= (_maxVelocity / particle->direction.length());
            //}

            //// Update the position with the direction.
            //particle->position += (particle->direction * _particleSystemScaleVelocity * elapsedTime);
            //particle->positionInWorld = particle->position;
            //particle->orientationInWorld = particle->orientation;
            //particle->widthInWorld = particle->width;
            //particle->heightInWorld = particle->height;
            //particle->depthInWorld = particle->depth;

            //bool keepLocal = _keepLocal;
            //PUParticleSystem3D *parent = dynamic_cast<PUParticleSystem3D *>(getParent());
            //if (parent) keepLocal = keepLocal || parent->isKeepLocal();

            //if (keepLocal){
            //    ltow.transformPoint(particle->positionInWorld, &particle->positionInWorld);
            //    Vec3 ori;
            //    ltow.transformVector(Vec3(particle->orientation.x, particle->orientation.y, particle->orientation.z), &ori);
            //    particle->orientationInWorld.x = ori.x; particle->orientationInWorld.y = ori.y; particle->orientationInWorld.z = ori.z;
            //    particle->widthInWorld = scl.x * particle->width;
            //    particle->heightInWorld = scl.y * particle->height;
            //    particle->depthInWorld = scl.z * particle->depth;
            //}
            processMotion(particle, elapsedTime, firstActiveParticle);
        }
        else{
            initParticleForExpiration(particle, elapsedTime);
            pool.lockLatestData();
        }

        for (auto it : _observers){
            if (it->isEnabled()){
                it->updateObserver(particle, elapsedTime, firstParticle);
            }
        }

        if (particle->hasEventFlags(PUParticle3D::PEF_EXPIRED))
        {
            particle->setEventFlags(0);
            particle->addEventFlags(PUParticle3D::PEF_EXPIRED);
        }
        else
        {
            particle->setEventFlags(0);
        }

        particle->timeToLive -= elapsedTime;
        firstParticle = false;
        particle = static_cast<PUParticle3D *>(pool.getNext());
    }
}

bool PUParticleSystem3D::makeParticleLocal( PUParticle3D* particle )
{
    if (!particle)
        return true;

    if (!_keepLocal)
        return false;

    particle->position += _latestPositionDiff;
    return true;
}

void PUParticleSystem3D::processMotion( PUParticle3D* particle, float timeElapsed, bool firstParticle )
{
    if (particle->isFreezed())
    return;


    /** Because everything is calculated in worldspace we recalculate it back to the techniques' origin (the result is still 
        worldspace) just by adding a relative offset of the particle system, technique, emitter or visual particle.
        Change in V1.4:
        The additional PEF_EMITTED check fixes the problem with scenenodese moving forward at extremely fast speeds 
        The bug is due to how PU code processes keep_local, and the calculation shouldn't be applied to newly emitted particles.
    */
    if (!particle->hasEventFlags(PUParticle3D::PEF_EMITTED))
    {
        if (!particle->parentEmitter->makeParticleLocal(particle))
        {
            if (!makeParticleLocal(particle))
            {
                _parentParticleSystem->makeParticleLocal(particle);
            }
        }
    }

    /** Adjust position of the particle if the parent has rotated (only in case of particle system with 'keep local').
        PU 1.4: Added check that technique may not be local, otherwise particles are rotated twice as fast.
    */
    if (_parentParticleSystem->isKeepLocal() && !_keepLocal)
    {
        /** Ignore some rendersystems, because they are rotated by Ogre itself.
            Entities for example are always rotated (even if not local), based on the node orientation. A Billboard not.
        */
        if (_render && !static_cast<PUParticle3DRender *>(_render)->autoRotate)
        {
            _parentParticleSystem->rotationOffset(particle->position);
        }
    }

    // Added for 1.3
    if (particle->hasEventFlags(PUParticle3D::PEF_EMITTED))
        return;

    // Adjust the velocity to the allowed maximum.
    if (_maxVelocitySet && particle->calculateVelocity() > _maxVelocity)
    {
        particle->direction *= (_maxVelocity / particle->direction.length());
    }

    // Update the position with the direction.
    particle->position += (particle->direction * _particleSystemScaleVelocity * timeElapsed);
}

void PUParticleSystem3D::calulateRotationOffset( void )
{
    if (_isMarkedForEmission)
    {
        // Use the uber particle system as centre of rotation and not the particle systems' own position.
        _rotationCentre = _parentParticleSystem->getDerivedPosition();
    }
    else
    {
        // Use its own position
        _rotationCentre = getDerivedPosition();
    }

    /** Use the derived orientation, which is the particle systems' own scenenode orientation,
        or the orientation of the uber particle system, if this particle system is emitted itself.
    */
    Quaternion latestOrientationInverse = _latestOrientation;
    latestOrientationInverse.inverse();
    _rotationOffset = getDerivedOrientation() * latestOrientationInverse;
}

int PUParticleSystem3D::getAliveParticleCnt() const
{
    int sz = 0;
    sz += _particlePool.getActiveDataList().size();

    if (!_emittedEmitterParticlePool.empty()){
        for (auto iter : _emittedEmitterParticlePool){
            sz += iter.second.getActiveDataList().size();
        }
    }

    if (_emittedSystemParticlePool.empty()) 
        return sz;

    for (auto iter : _emittedSystemParticlePool){
        auto pool = iter.second;
        sz += pool.getActiveDataList().size();
        PUParticle3D *particle = static_cast<PUParticle3D *>(pool.getFirst());
        while (particle)
        {
            sz += static_cast<PUParticleSystem3D*>(particle->particleEntityPtr)->getAliveParticleCnt();
            particle = static_cast<PUParticle3D *>(pool.getNext());
        }
    }
    return sz;
}

NS_CC_END
