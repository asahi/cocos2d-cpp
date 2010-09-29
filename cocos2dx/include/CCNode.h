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

#ifndef __CCNODE_H__
#define __CCNODE_H__

#include "Cocos2dDefine.h"
#include "ccMacros.h"
#include "CGAffineTransform.h"
#include "NSMutableArray.h"
#include "ccConfig.h"
#include "ccxCommon.h"
#include "selector_protocol.h"

#include <gles/gl.h>

namespace   cocos2d {
class CCCamera;
class CCGridBase;
class CGPoint;
class CCTouch;
class CCAction;
class CCRGBAProtocol;
class CCLabelProtocol;

enum {
	kCCNodeTagInvalid = -1,
};

/** @brief CCNode is the main element. Anything thats gets drawn or contains things that get drawn is a CCNode.
The most popular CCNodes are: CCScene, CCLayer, CCSprite, CCMenu.

The main features of a CCNode are:
- They can contain other CCNode nodes (addChild, getChildByTag, removeChild, etc)
- They can schedule periodic callback (schedule, unschedule, etc)
- They can execute actions (runAction, stopAction, etc)

Some CCNode nodes provide extra functionality for them or their children.

Subclassing a CCNode usually means (one/all) of:
- overriding init to initialize resources and schedule callbacks
- create callbacks to handle the advancement of time
- overriding draw to render the node

Features of CCNode:
- position
- scale (x, y)
- rotation (in degrees, clockwise)
- CCCamera (an interface to gluLookAt )
- CCGridBase (to do mesh transformations)
- anchor point
- size
- visible
- z-order
- openGL z position

Default values:
- rotation: 0
- position: (x=0,y=0)
- scale: (x=1,y=1)
- contentSize: (x=0,y=0)
- anchorPoint: (x=0,y=0)

Limitations:
- A CCNode is a "void" object. It doesn't have a texture

Order in transformations with grid disabled
-# The node will be translated (position)
-# The node will be rotated (rotation)
-# The node will be scaled (scale)
-# The node will be moved according to the camera values (camera)

Order in transformations with grid enabled
-# The node will be translated (position)
-# The node will be rotated (rotation)
-# The node will be scaled (scale)
-# The grid will capture the screen
-# The node will be moved according to the camera values (camera)
-# The grid will render the captured screen

Camera:
- Each node has a camera. By default it points to the center of the CCNode.
*/ 

class CCX_DLL CCNode : public SelectorProtocol, public NSObject
{

	// variable property

	/** The z order of the node relative to it's "brothers": children of the same parent */
	CCX_PROPERTY_READONLY(int, m_nZOrder, ZOrder)

	/** The real openGL Z vertex.
	Differences between openGL Z vertex and cocos2d Z order:
	- OpenGL Z modifies the Z vertex, and not the Z order in the relation between parent-children
	- OpenGL Z might require to set 2D projection
	- cocos2d Z order works OK if all the nodes uses the same openGL Z vertex. eg: vertexZ = 0
	@warning: Use it at your own risk since it might break the cocos2d parent-children z order
	@since v0.8
	*/
	CCX_PROPERTY(float, m_fVertexZ, VertexZ)

	/** The rotation (angle) of the node in degrees. 0 is the default rotation angle. Positive values rotate node CW. */
	CCX_PROPERTY(float, m_fRotation, Rotation)

	/** Get the scale factor of the node.
	@warning: Assert when m_fScaleX != m_fScaleY.
	*/
	float getScale();
	/** The scale factor of the node. 1.0 is the default scale factor. It modifies the X and Y scale at the same time. */
	void setScale(float scale);

	/** The scale factor of the node. 1.0 is the default scale factor. It only modifies the X scale factor. */
	CCX_PROPERTY(float, m_fScaleX, ScaleX)

	/** The scale factor of the node. 1.0 is the default scale factor. It only modifies the Y scale factor. */
	CCX_PROPERTY(float, m_fScaleY, ScaleY)

	/** Position (x,y) of the node in OpenGL coordinates. (0,0) is the left-bottom corner. */
	CCX_PROPERTY(CGPoint, m_tPosition, Position)

	CCX_PROPERTY_READONLY(NSMutableArray<CCNode *> *, m_pChildren, Children)

	/** A CCCamera object that lets you move the node using a gluLookAt
	*/
	CCX_PROPERTY_READONLY(CCCamera *, m_pCamera, Camera)

	/** A CCGrid object that is used when applying effects */
	CCX_PROPERTY(CCGridBase *, m_pGrid, Grid)

	/** Whether of not the node is visible. Default is true */
	CCX_PROPERTY(bool, m_bIsVisible, IsVisible)

	/** anchorPoint is the point around which all transformations and positioning manipulations take place.
	It's like a pin in the node where it is "attached" to its parent.
	The anchorPoint is normalized, like a percentage. (0,0) means the bottom-left corner and (1,1) means the top-right corner.
	But you can use values higher than (1,1) and lower than (0,0) too.
	The default anchorPoint is (0.5,0.5), so it starts in the center of the node.
	@since v0.8
	*/
	CCX_PROPERTY(CGPoint, m_tAnchorPoint, AnchorPoint)

	/** The anchorPoint in absolute pixels.
	Since v0.8 you can only read it. If you wish to modify it, use anchorPoint instead
	*/
	CCX_PROPERTY_READONLY(CGPoint, m_tAnchorPointInPixels, AnchorPointInPixels)
	
	/** The untransformed size of the node.
	The contentSize remains the same no matter the node is scaled or rotated.
	All nodes has a size. Layer and Scene has the same size of the screen.
	@since v0.8
	*/
	CCX_PROPERTY(CGSize, m_tContentSize, ContentSize)

	/** whether or not the node is running */
	CCX_PROPERTY_READONLY(bool, m_bIsRunning, IsRunning)

	/** A weak reference to the parent */
	CCX_PROPERTY(CCNode *, m_pParent, Parent)

	/** If true the transformtions will be relative to it's anchor point.
	* Sprites, Labels and any other sizeble object use it have it enabled by default.
	* Scenes, Layers and other "whole screen" object don't use it, have it disabled by default.
	*/
	CCX_PROPERTY(bool, m_bIsRelativeAnchorPoint, IsRelativeAnchorPoint)

	/** A tag used to identify the node easily */
	CCX_PROPERTY(int, m_nTag, Tag)

	/** A custom user data pointer */
	CCX_PROPERTY(void *, m_pUserData, UserData)
	
protected:

	// transform
	CGAffineTransform m_tTransform, m_tInverse;

#ifdef	CC_NODE_TRANSFORM_USING_AFFINE_MATRIX
	GLfloat	m_pTransformGL[16];
#endif
	// To reduce memory, place bools that are not properties here:
	bool m_bIsTransformDirty;
	bool m_bIsInverseDirty;

#ifdef	CC_NODE_TRANSFORM_USING_AFFINE_MATRIX
	bool m_bIsTransformGLDirty;
#endif
    
private:

	// lazy allocs
	void childrenAlloc(void);

	// helper that reorder a child
	void insertChild(CCNode* child, int z);

	// used internally to alter the zOrder variable. DON'T call this method manually
	void setZOrder(int z);

	void detachChild(CCNode *child, bool doCleanup);

	typedef void (CCNode::*callbackFunc)(void);

	void arrayMakeObjectsPerformSelector(NSMutableArray<CCNode*> * pArray, callbackFunc func);

	CGPoint convertToWindowSpace(CGPoint nodePoint);

public:

	CCNode();

	virtual ~CCNode();

	char * description(void);

	/** allocates and initializes a node.
	The node will be created as "autorelease".
	*/
	static CCNode * node(void);

	//scene managment

	/** callback that is called every time the CCNode enters the 'stage'.
	If the CCNode enters the 'stage' with a transition, this callback is called when the transition starts.
	During onEnter you can't a "sister/brother" node.
	*/
	virtual void onEnter();

	/** callback that is called when the CCNode enters in the 'stage'.
	If the CCNode enters the 'stage' with a transition, this callback is called when the transition finishes.
	@since v0.8
	*/
	virtual void onEnterTransitionDidFinish();

	/** callback that is called every time the CCNode leaves the 'stage'.
	If the CCNode leaves the 'stage' with a transition, this callback is called when the transition finishes.
	During onExit you can't a "sister/brother" node.
	*/
	virtual void onExit();

	// composition: ADD

	/** Adds a child to the container with z-order as 0.
	It returns self, so you can chain several addChilds.
	@since v0.7.1
	*/
	virtual CCNode * addChild(CCNode * child);

	/** Adds a child to the container with a z-order
	It returns self, so you can chain several addChilds.
	@since v0.7.1
	*/
	virtual CCNode * addChild(CCNode * child, int zOrder);

	/** Adds a child to the container with z order and tag
	It returns self, so you can chain several addChilds.
	@since v0.7.1
	*/
	virtual CCNode * addChild(CCNode * child, int zOrder, int tag);

	// composition: REMOVE

	/** Remove itself from its parent node. If cleanup is true, then also remove all actions and callbacks.
	If the node orphan, then nothing happens.
	@since v0.99.3
	*/
	void removeFromParentAndCleanup(bool cleanup);

	/** Removes a child from the container. It will also cleanup all running actions depending on the cleanup parameter.
	@since v0.7.1
	*/
	virtual void removeChild(CCNode* child, bool cleanup);

	/** Removes a child from the container by tag value. It will also cleanup all running actions depending on the cleanup parameter
	@since v0.7.1
	*/
	void removeChildByTag(int tag, bool cleanup);

	/** Removes all children from the container and do a cleanup all running actions depending on the cleanup parameter.
	@since v0.7.1
	*/
	virtual void removeAllChildrenWithCleanup(bool cleanup);

	// composition: GET
	/** Gets a child from the container given its tag
	@return returns a CCNode object
	@since v0.7.1
	*/
	CCNode * getChildByTag(int tag);

	/** Reorders a child according to a new z value.
	* The child MUST be already added.
	*/
	virtual void reorderChild(CCNode * child, int zOrder);

	/** Stops all running actions and schedulers
	@since v0.8
	*/
	virtual void cleanup(void);

	// draw

	/** Override this method to draw your own node.
	The following GL states will be enabled by default:
	- glEnableClientState(GL_VERTEX_ARRAY);
	- glEnableClientState(GL_COLOR_ARRAY);
	- glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	- glEnable(GL_TEXTURE_2D);

	AND YOU SHOULD NOT DISABLE THEM AFTER DRAWING YOUR NODE

	But if you enable any other GL state, you should disable it after drawing your node.
	*/
	virtual void draw(void);

	/** recursive method that visit its children and draw them */
	virtual void visit(void);

	// transformations

	/** performs OpenGL view-matrix transformation based on position, scale, rotation and other attributes. */
	void transform(void);

	/** performs OpenGL view-matrix transformation of it's ancestors.
	Generally the ancestors are already transformed, but in certain cases (eg: attaching a FBO)
	it's necessary to transform the ancestors again.
	@since v0.7.2
	*/
	void transformAncestors(void);

	/** returns a "local" axis aligned bounding box of the node.
	The returned box is relative only to its parent.

	@since v0.8.2
	*/
	CGRect boundingBox(void);

	// actions

	/** Executes an action, and returns the action that is executed.
	The node becomes the action's target.
	@warning Starting from v0.8 actions don't retain their target anymore.
	@since v0.7.1
	@return An Action pointer
	*/
	
	CCAction* runAction(CCAction* action);

	/** Removes all actions from the running action list */
	void stopAllActions(void);

	/** Removes an action from the running action list */
	void stopAction(CCAction* action);

	/** Removes an action from the running action list given its tag
	@since v0.7.1
	*/
	void stopActionByTag(int tag);

	/** Gets an action from the running action list given its tag
	@since v0.7.1
	@return the Action the with the given tag
	*/
	CCAction* getActionByTag(int tag);

	/** Returns the numbers of actions that are running plus the ones that are schedule to run (actions in actionsToAdd and actions arrays). 
	* Composable actions are counted as 1 action. Example:
	*    If you are running 1 Sequence of 7 actions, it will return 1.
	*    If you are running 7 Sequences of 2 actions, it will return 7.
	*/
	int numberOfRunningActions(void);


	// timers

	/** check whether a selector is scheduled. */
	bool isScheduled(SEL_SCHEDULE selector);

	/** schedules the "update" method. It will use the order number 0. This method will be called every frame.
	Scheduled methods with a lower order value will be called before the ones that have a higher order value.
	Only one "update" method could be scheduled per node.

	@since v0.99.3
	*/
	void scheduleUpdate(void);

	/** schedules the "update" selector with a custom priority. This selector will be called every frame.
	Scheduled selectors with a lower priority will be called before the ones that have a higher value.
	Only one "update" selector could be scheduled per node (You can't have 2 'update' selectors).

	@since v0.99.3
	*/
	void scheduleUpdateWithPriority(int priority);

	/* unschedules the "update" method.

	@since v0.99.3
	*/
	void unscheduleUpdate(void);

	/** schedules a selector.
	The scheduled selector will be ticked every frame
	*/
	void schedule(SEL_SCHEDULE selector);

	/** schedules a custom selector with an interval time in seconds.
	If time is 0 it will be ticked every frame.
	If time is 0, it is recommended to use 'scheduleUpdate' instead.
	If the selector is already scheduled, then the interval parameter 
	will be updated without scheduling it again.
	*/
	void schedule(SEL_SCHEDULE selector, ccTime interval);

	/** unschedules a custom selector.*/
	void unschedule(SEL_SCHEDULE selector);

	/** unschedule all scheduled selectors: custom selectors, and the 'update' selector.
	Actions are not affected by this method.
	@since v0.99.3
	*/
	void unscheduleAllSelectors(void);

	/** resumes all scheduled selectors and actions.
	Called internally by onEnter
	*/
	void resumeSchedulerAndActions(void);
	/** pauses all scheduled selectors and actions.
	Called internally by onExit
	*/
	void pauseSchedulerAndActions(void);

	// SelecterProtocol methods

	virtual void selectorProtocolRetain(void);
	virtual void selectorProtocolRelease(void);

	virtual CCRGBAProtocol* convertToRGBAProtocol(void) { return NULL; }
	virtual CCLabelProtocol* convertToLabelProtocol(void) { return NULL; }

	// transformation methods

	/** Returns the local affine transform matrix
	@since v0.7.1
	*/
	CGAffineTransform nodeToParentTransform(void);

	/** Returns the inverse local affine transform matrix
	@since v0.7.1
	*/
	CGAffineTransform parentToNodeTransform(void);

	/** Retrusn the world affine transform matrix
	@since v0.7.1
	*/
	CGAffineTransform nodeToWorldTransform(void);

	/** Returns the inverse world affine transform matrix
	@since v0.7.1
	*/
	CGAffineTransform worldToNodeTransform(void);

	/** converts a world coordinate to local coordinate
	@since v0.7.1
	*/
	CGPoint convertToNodeSpace(CGPoint worldPoint);
	/** converts local coordinate to world space
	@since v0.7.1
	*/
	CGPoint convertToWorldSpace(CGPoint nodePoint);
	/** converts a world coordinate to local coordinate
	treating the returned/received node point as anchor relative
	@since v0.7.1
	*/
	CGPoint convertToNodeSpaceAR(CGPoint worldPoint);
	/** converts local coordinate to world space
	treating the returned/received node point as anchor relative
	@since v0.7.1
	*/
	CGPoint convertToWorldSpaceAR(CGPoint nodePoint);
	/** convenience methods which take a CCTouch instead of CGPoint
	@since v0.7.1
	*/
	CGPoint convertTouchToNodeSpace(CCTouch * touch);

	/** converts a CCTouch (world coordinates) into a local coordiante. This method is AR (Anchor Relative).
	@since v0.7.1
	*/
	CGPoint convertTouchToNodeSpaceAR(CCTouch * touch);

};
}//namespace   cocos2d 

#endif // __CCNODE_H__


 
