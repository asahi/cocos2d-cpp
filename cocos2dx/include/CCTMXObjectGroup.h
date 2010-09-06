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
#ifndef __CCTMX_OBJECT_GROUP_H__
#define __CCTMX_OBJECT_GROUP_H__
#include <string>
#include <vector>
#include <map>
#include "Cocos2dDefine.h"
#include "CGGeometry.h"
#include "NSObject.h"

namespace cocos2d {

	typedef std::map<std::string, std::string> StringToStringDictionary;
	typedef std::pair<std::string, std::string> StringToStringPair;
	/** only used in StringToStringDictionary, return "" if not found*/
	CCX_DLL const char * valueForKey(const char* key, StringToStringDictionary *dict);

	/** CCTMXObjectGroup represents the TMX object group.
	@since v0.99.0
	*/
	class CCX_DLL CCTMXObjectGroup : public NSObject
	{
		/** name of the group */
	protected:	
		std::string m_sGroupName;
	public:	
		inline const char* getGroupName(){ return m_sGroupName.c_str(); }
		inline void setGroupName(const char *groupName){ m_sGroupName = groupName; }
		/** offset position of child objects */
		CCX_SYNTHESIZE(CGPoint, m_tPositionOffset, PositionOffset);
		/** array of the objects */
		CCX_SYNTHESIZE(std::vector<StringToStringDictionary*>*, m_pObjects, Objects);
		/** list of properties stored in a dictionary */
		CCX_SYNTHESIZE(StringToStringDictionary*, m_pProperties, Properties);
	public:
		CCTMXObjectGroup();
		virtual ~CCTMXObjectGroup();

		/** return the value for the specific property name */
		const char *propertyNamed(const char* propertyName);

		/** return the dictionary for the specific object name.
		It will return the 1st object found on the array for the given name.
		*/
		StringToStringDictionary *objectNamed(const char *objectName);
	};

}// namespace cocos2d
#endif //__CCTMX_OBJECT_GROUP_H__