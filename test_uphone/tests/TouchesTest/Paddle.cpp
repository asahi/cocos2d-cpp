#include "Paddle.h"

Paddle::Paddle(void)
{
}

Paddle::~Paddle(void)
{
}

CGRect Paddle::rect()
{
	CGSize s = getTexture()->getContentSize();
	return CGRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
}

Paddle* Paddle::paddleWithTexture(CCTexture2D* aTexture)
{
	Paddle* pPaddle = new Paddle();
	pPaddle->initWithTexture( aTexture );
	pPaddle->autorelease();

	return pPaddle;
}

bool Paddle::initWithTexture(CCTexture2D* aTexture)
{
	if( __super::initWithTexture(aTexture) ) 
	{
		m_state = kPaddleStateUngrabbed;
	}
	
	return TRUE;
}

void Paddle::onEnter()
{
    CCTouchDispatcher::getSharedDispatcher()->addTargetedDelegate(this, 0, true);
	__super::onEnter();
}

void Paddle::onExit()
{
	CCTouchDispatcher::getSharedDispatcher()->removeDelegate(this);
	__super::onExit();
}	

bool Paddle::containsTouchLocation(CCTouch* touch)
{
	return CGRect::CGRectContainsPoint(rect(), convertTouchToNodeSpaceAR(touch));
}

bool Paddle::ccTouchBegan(CCTouch* touch, UIEvent* event)
{
	if (m_state != kPaddleStateUngrabbed) return false;
	if ( !containsTouchLocation(touch) ) return false;
	
	m_state = kPaddleStateGrabbed;
	return true;
}

void Paddle::ccTouchMoved(CCTouch* touch, UIEvent* event)
{
	// If it weren't for the TouchDispatcher, you would need to keep a reference
	// to the touch from touchBegan and check that the current touch is the same
	// as that one.
	// Actually, it would be even more complicated since in the Cocos dispatcher
	// you get NSSets instead of 1 UITouch, so you'd need to loop through the set
	// in each touchXXX method.
	
	NSAssert(m_state == kPaddleStateGrabbed, L"Paddle - Unexpected state!");	
	
	CGPoint touchPoint = touch->locationInView( touch->view() );
    touchPoint = CCDirector::getSharedDirector()->convertToGL( touchPoint );
	
	setPosition( CGPointMake(touchPoint.x, getPosition().y) );
}

void Paddle::ccTouchEnded(CCTouch* touch, UIEvent* event)
{
	NSAssert(m_state == kPaddleStateGrabbed, L"Paddle - Unexpected state!");	
	
	m_state = kPaddleStateUngrabbed;
} 