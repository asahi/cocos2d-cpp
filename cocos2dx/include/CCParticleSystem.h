/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
#ifndef __CCPARTICLE_SYSTEM_H__
#define __CCPARTICLE_SYSTEM_H__

#include "CCProtocols.h"
#include "CCNode.h"
#include "platform/platform.h"
namespace cocos2d {

#if CC_ENABLE_PROFILERS
	class CCProfilingTimer;
#endif

	//* @enum
	enum {
		/** The Particle emitter lives forever */
		kCCParticleDurationInfinity = -1,

		/** The starting size of the particle is equal to the ending size */
		kCCParticleStartSizeEqualToEndSize = -1,

		/** The starting radius of the particle is equal to the ending radius */
		kCCParticleStartRadiusEqualToEndRadius = -1,

		// backward compatible
		kParticleStartSizeEqualToEndSize = kCCParticleStartSizeEqualToEndSize,
		kParticleDurationInfinity = kCCParticleDurationInfinity,
	};

	//* @enum
	enum {
		/** Gravity mode (A mode) */
		kCCParticleModeGravity,

		/** Radius mode (B mode) */
		kCCParticleModeRadius,	
	};


	/** @typedef tCCPositionType
	possible types of particle positions
	*/
	typedef enum {
		/** If the emitter is repositioned, the living particles won't be repositioned */
		kCCPositionTypeFree,
		/** If the emitter is repositioned, the living particles will be repositioned too */
		kCCPositionTypeGrouped,
	}tCCPositionType;

	// backward compatible
	enum {
		kPositionTypeFree = kCCPositionTypeFree,
		kPositionTypeGrouped = kCCPositionTypeGrouped,
	}; 

	/** @struct tCCParticle
	Structure that contains the values of each particle
	*/
	typedef struct sCCParticle {
		CGPoint				pos;
		CGPoint				startPos;

		ccColor4F	color;
		ccColor4F	deltaColor;

		float		size;
		float		deltaSize;

		float		rotation;
		float		deltaRotation;

		ccTime		timeToLive;

		// Mode A: gravity, direction, radial accel, tangential accel
		struct {
			CGPoint		dir;
			float		radialAccel;
			float		tangentialAccel;
		} modeA;

		// Mode B: radius mode
		struct {
			float		angle;
			float		degreesPerSecond;
			float		radius;
			float		deltaRadius;
		} modeB;

	}tCCParticle;

	//typedef void (*CC_UPDATE_PARTICLE_IMP)(id, SEL, tCCParticle*, CGPoint);

	class CCTexture2D;

	/** Particle System base class
	Attributes of a Particle System:
	- emmision rate of the particles
	- Gravity Mode (Mode A):
	- gravity
	- direction
	- speed +-  variance
	- tangential acceleration +- variance
	- radial acceleration +- variance
	- Radius Mode (Mode B):
	- startRadius +- variance
	- endRadius +- variance
	- rotate +- variance
	- Properties common to all modes:
	- life +- life variance
	- start spin +- variance
	- end spin +- variance
	- start size +- variance
	- end size +- variance
	- start color +- variance
	- end color +- variance
	- life +- variance
	- blending function
	- texture

	cocos2d also supports particles generated by Particle Designer (http://particledesigner.71squared.com/).
	'Radius Mode' in Particle Designer uses a fixed emit rate of 30 hz. Since that can't be guarateed in cocos2d,
	cocos2d uses a another approach, but the results are almost identical. 

	cocos2d supports all the variables used by Particle Designer plus a bit more:
	- spinning particles (supported when using CCQuadParticleSystem)
	- tangential acceleration (Gravity mode)
	- radial acceleration (Gravity mode)
	- radius direction (Radius mode) (Particle Designer supports outwards to inwards direction only)

	It is possible to customize any of the above mentioned properties in runtime. Example:

	@code
	emitter.radialAccel = 15;
	emitter.startSpin = 0;
	@endcode

	*/
	class CCX_DLL CCParticleSystem : public CCNode, public CCTextureProtocol
	{	
	protected:
		// time elapsed since the start of the system (in seconds)
		float m_fElapsed;

		// Different modes
		// Mode A:Gravity + Tangential Accel + Radial Accel
		struct {
			// gravity of the particles
			CGPoint gravity;
			// The speed the particles will have.
			float speed;
			// The speed variance
			float speedVar;
			// Tangential acceleration
			float tangentialAccel;
			// Tangential acceleration variance
			float tangentialAccelVar;
			// Radial acceleration
			float radialAccel;
			// Radial acceleration variance
			float radialAccelVar;
		} modeA;

		// Mode B: circular movement (gravity, radial accel and tangential accel don't are not used in this mode)
		struct {
			// The starting radius of the particles
			float startRadius;
			// The starting radius variance of the particles
			float startRadiusVar;
			// The ending radius of the particles
			float endRadius;
			// The ending radius variance of the particles
			float endRadiusVar;			
			// Number of degress to rotate a particle around the source pos per second
			float rotatePerSecond;
			// Variance in degrees for rotatePerSecond
			float rotatePerSecondVar;
		} modeB;

		// Array of particles
		tCCParticle *m_pParticles;

		// color modulate
		//	BOOL colorModulate;

		// How many particles can be emitted per second
		float m_fEmitCounter;

		//  particle idx
		int m_nParticleIdx;

		// Optimization
		//CC_UPDATE_PARTICLE_IMP	updateParticleImp;
		//SEL						updateParticleSel;

		// profiling
#if CC_ENABLE_PROFILERS
		CCProfilingTimer* m_pProfilingTimer;
#endif

		/** Is the emitter active */
		CCX_PROPERTY_READONLY(bool, m_bIsActive, IsActive)
		/** Quantity of particles that are being simulated at the moment */
		CCX_PROPERTY_READONLY(int, m_nParticleCount, ParticleCount)
		/** How many seconds the emitter wil run. -1 means 'forever' */
		CCX_PROPERTY(float, m_fDuration, Duration)
		/** centerOfGravity of the emitter */
		CCX_PROPERTY(CGPoint, m_tCenterOfGravity, CenterOfGravity)
		/** Position variance of the emitter */
		CCX_PROPERTY(CGPoint, m_tPosVar, PosVar)
		/** life, and life variation of each particle */
		CCX_PROPERTY(float, m_fLife, Life)
		/** life variance of each particle */
		CCX_PROPERTY(float, m_fLifeVar, LifeVar)
		/** angle and angle variation of each particle */
		CCX_PROPERTY(float, m_fAngle, Angle)
		/** angle variance of each particle */
		CCX_PROPERTY(float, m_fAngleVar, AngleVar)

	//////////////////////////////////////////////////////////////////////////
	public:
		// mode A
		/** Gravity value. Only available in 'Gravity' mode. */
		virtual CGPoint getGravity();
		virtual void setGravity(CGPoint g);
		/** speed of each particle. Only available in 'Gravity' mode.  */
		virtual float getSpeed();
		virtual void setSpeed(float speed);
		/** speed variance of each particle. Only available in 'Gravity' mode. */
		virtual float getSpeedVar();
		virtual void setSpeedVar(float speed);
		/** tangential acceleration of each particle. Only available in 'Gravity' mode. */
		virtual float getTangentialAccel();
		virtual void setTangentialAccel(float t);
		/** tangential acceleration variance of each particle. Only available in 'Gravity' mode. */
		virtual float getTangentialAccelVar();
		virtual void setTangentialAccelVar(float t);
		/** radial acceleration of each particle. Only available in 'Gravity' mode. */
		virtual float getRadialAccel();
		virtual void setRadialAccel(float t);
		/** radial acceleration variance of each particle. Only available in 'Gravity' mode. */
		virtual float getRadialAccelVar();
		virtual void setRadialAccelVar(float t);
		// mode B
		/** The starting radius of the particles. Only available in 'Radius' mode. */
		virtual float getStartRadius();
		virtual void setStartRadius(float startRadius);
		/** The starting radius variance of the particles. Only available in 'Radius' mode. */
		virtual float getStartRadiusVar();
		virtual void setStartRadiusVar(float startRadiusVar);
		/** The ending radius of the particles. Only available in 'Radius' mode. */
		virtual float getEndRadius();
		virtual void setEndRadius(float endRadius);
		/** The ending radius variance of the particles. Only available in 'Radius' mode. */
		virtual float getEndRadiusVar();
		virtual void setEndRadiusVar(float endRadiusVar);
		/** Number of degress to rotate a particle around the source pos per second. Only available in 'Radius' mode. */
		virtual float getRotatePerSecond();
		virtual void setRotatePerSecond(float degrees);
		/** Variance in degrees for rotatePerSecond. Only available in 'Radius' mode. */
		virtual float getRotatePerSecondVar();
		virtual void setRotatePerSecondVar(float degrees);
	//////////////////////////////////////////////////////////////////////////
		
		/** start size in pixels of each particle */
		CCX_PROPERTY(float, m_fStartSize, StartSize)
		/** size variance in pixels of each particle */
		CCX_PROPERTY(float, m_fStartSizeVar, StartSizeVar)
		/** end size in pixels of each particle */
		CCX_PROPERTY(float, m_fEndSize, EndSize)
		/** end size variance in pixels of each particle */
		CCX_PROPERTY(float, m_fEndSizeVar, EndSizeVar)
		/** start color of each particle */
		CCX_PROPERTY(ccColor4F, m_tStartColor, StartColor)
		/** start color variance of each particle */
		CCX_PROPERTY(ccColor4F, m_tStartColorVar, StartColorVar)
		/** end color and end color variation of each particle */
		CCX_PROPERTY(ccColor4F, m_tEndColor, EndColor)
		/** end color variance of each particle */
		CCX_PROPERTY(ccColor4F, m_tEndColorVar, EndColorVar)
		//* initial angle of each particle
		CCX_PROPERTY(float, m_fStartSpin, StartSpin)
		//* initial angle of each particle
		CCX_PROPERTY(float, m_fStartSpinVar, StartSpinVar)
		//* initial angle of each particle
		CCX_PROPERTY(float, m_fEndSpin, EndSpin)
		//* initial angle of each particle
		CCX_PROPERTY(float, m_fEndSpinVar, EndSpinVar)
		/** emission rate of the particles */
		CCX_PROPERTY(float, m_fEmissionRate, EmissionRate)
		/** maximum particles of the system */
		CCX_PROPERTY(int, m_nTotalParticles, TotalParticles)
		/** conforms to CocosNodeTexture protocol */
		CCX_PROPERTY(CCTexture2D*, m_pTexture, Texture)
		/** conforms to CocosNodeTexture protocol */
		CCX_PROPERTY(ccBlendFunc, m_tBlendFunc, BlendFunc)
		/** whether or not the particles are using blend additive.
		If enabled, the following blending function will be used.
		@code
		source blend function = GL_SRC_ALPHA;
		dest blend function = GL_ONE;
		@endcode
		*/
		CCX_PROPERTY(bool, m_bIsBlendAdditive, IsBlendAdditive)
		/** particles movement type: Free or Grouped
		@since v0.8
		*/
		CCX_PROPERTY(tCCPositionType, m_ePositionType, PositionType)
		/** whether or not the node will be auto-removed when it has no particles left.
		By default it is NO.
		@since v0.8
		*/
		CCX_PROPERTY(bool, m_bIsAutoRemoveOnFinish, IsAutoRemoveOnFinish)
		/** Switch between different kind of emitter modes:
		- kCCParticleModeGravity: uses gravity, speed, radial and tangential acceleration
		- kCCParticleModeRadius: uses radius movement + rotation
		*/
		CCX_PROPERTY(int, m_nEmitterMode, EmitterMode)

	public:
		CCParticleSystem()
			:m_pParticles(NULL)
#if CC_ENABLE_PROFILERS
			,m_pProfilingTimer(NULL)
#endif
			,m_pTexture(NULL)
		{}
		virtual ~CCParticleSystem();
		/** creates an initializes a CCParticleSystem from a plist file.
		This plist files can be creted manually or with Particle Designer:
		http://particledesigner.71squared.com/
		@since v0.99.3
		*/
		static CCParticleSystem * particleWithFile(const char *plistFile);

		/** initializes a CCParticleSystem from a plist file.
		This plist files can be creted manually or with Particle Designer:
		http://particledesigner.71squared.com/
		@since v0.99.3
		*/
		bool initWithFile(const char *plistFile);

		/** initializes a CCQuadParticleSystem from a NSDictionary.
		@since v0.99.3
		*/
		bool initWithDictionary(CCDictionary *dictionary);

		//! Initializes a system with a fixed number of particles
		bool initWithTotalParticles(int numberOfParticles);
		//! Add a particle to the emitter
		bool addParticle();
		//! Initializes a particle
		void initParticle(tCCParticle* particle);
		//! stop emitting particles. Running particles will continue to run until they die
		void stopSystem();
		//! Kill all living particles.
		void resetSystem();
		//! whether or not the system is full
		bool isFull();

		//! should be overriden by subclasses
		virtual void updateQuadWithParticle(tCCParticle* particle, CGPoint newPosition);
		//! should be overriden by subclasses
		virtual void postStep();

		virtual void update(ccTime dt);
	private:
		inline const char * valueForKey(const char *key, CCDictionary *dict)
		{
			CCDictionary::iterator it = dict->find(key);
			return ((std::string*)(it->second))->c_str();
		}
};

}// namespace cocos2d
#endif //__CCPARTICLE_SYSTEM_H__


