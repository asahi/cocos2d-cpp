#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include "SimpleAudioEngine.h"
#include "cocos2dsimplegame_res_def.h"
#include "cocos2d.h"

const T_ResourceInfo ResInfo[] =
{
    { "CloseNormal",    COCOS2_ID_BITMAP_CloseNormal },
    { "CloseSelected",  COCOS2_ID_BITMAP_CloseSelected },
    { "Player",         COCOS2_ID_BITMAP_Player },
    { "Projectile",     COCOS2_ID_BITMAP_Projectile },
    { "Target",         COCOS2_ID_BITMAP_Target },
    { "CloseNormal@WVGA",    COCOS2_ID_BITMAP_CloseNormal_WVGA },
    { "CloseSelected@WVGA",  COCOS2_ID_BITMAP_CloseSelected_WVGA },
    { "Player@WVGA",         COCOS2_ID_BITMAP_Player_WVGA },
    { "Projectile@WVGA",     COCOS2_ID_BITMAP_Projectile_WVGA },
    { "Target@WVGA",         COCOS2_ID_BITMAP_Target_WVGA },
};

/**
@warning ������������Ϣ�Ľṹ���У�FileName��������ļ�����չ����������Ҫ��ԭʼ�ļ�����չ��һ��
         �����޷�����
*/
const T_SoundResInfo SoundResInfo[] =
{
    { "background-music-aac.mp3",     COCOS2_ID_RAWDATA_background_music_aac },
    { "pew-pew-lei.wav",              COCOS2_ID_RAWDATA_pew_pew_lei },
};

#endif
