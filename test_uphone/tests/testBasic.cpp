#include "testBasic.h"

TestLayer::TestLayer()
{
    /**
    @todo ������ڿ��Ƶ�ǰ�����в��ԵĲ˵�
    */
}

TestScene::TestScene()
{
    CCLayer* pLayer = new TestLayer();
    pLayer->autorelease();
    pLayer->retain();

    addChild(pLayer);
}
