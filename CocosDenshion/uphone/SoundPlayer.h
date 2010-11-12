#ifndef _SOUNDPLAYER_UPHONE_H_
#define _SOUNDPLAYER_UPHONE_H_

#include "TG3.h"
#include "TCOM_MediaPlayer_Method.h"
#include "TCOM_Generic_DataType.h"
#include <string>

class SoundPlayer
{
public:
    SoundPlayer();
    ~SoundPlayer();

    void Release();

    /**
    @brief ���������ļ�
    @param pFileName ���ŵ������ļ����ƣ���Ҫ�����ļ���·��
    @param nTimes    ���������ļ���ѭ��������Ĭ��ֵΪ 1��������һ��
    */
    void PlaySoundFile(const char* pFileName, Int32 nTimes = 1);

    /**
    @brief �����ڴ��е���������
    @param pData  ��������ָ��
    @param nSize  �������ݵĴ�С
    @param nTimes ѭ���Ĵ�����Ĭ��ֻ����һ�Σ�
    @param pFileName ���ŵ��ļ��������ļ�������Ϊ�����ַ��������Ǳ���������ݵ���չ����
    @warning pFileName �е��ļ���չ��Ӱ�����ݵĲ��ţ������չ�������ݵ�ԭʼ���Ͳ�ƥ�����޷����š�
             Ĭ�� pFileName Ϊ NULL����ʱ�ᰴ�� .wav �ĸ�ʽ�����ݽ��н���
    */
    void PlaySoundFromMem(UInt8* pData, Int32 nSize, const char* pFileName = "", Int32 nTimes = 1);

    /**
    @brief ���ò�����������
    @oaram nValue ����ֵ��Ӧ���� 0~100 ֮��
    */
    void SetVolumeValue(Int32 nValue);

    /**
    @brief ��ͣ��������
    */
    void Pause();

    /**
    @brief ������������
    */
    void Resume();

    /**
    @brief ֹͣ��������
    */
    void Stop();

    /**
    @brief ���²���
    */
    void Rewind();

    /**
    @brief ����
    @param bMute �Ƿ�����TRUE��ʾ����Ϊ����
    */
    void Mute(bool bMute);

    /**
    @brief ��ȡ��������ǰ�Ƿ����ڲ�����
    */
    bool IsPlaying();

    /**
    @brief ���ļ����ݽ��뵽 buffer ��
    @param buffer [out] ����������
    @param pszFilePath Ҫ������ļ�·��
    @return ����ֵ >= 0 ��ʾ�ɹ��������ʾʧ��
    */
    Int32 DecodeFile(void* buffer, Int32 bufferLen, const char* pszFilePath);

    /**
    @brief ��ȡ��Ƶ�ļ������ݴ�С
    @param ��Ƶ�ļ���
    @return ������Ҫ��buffer��С�������ʧ�ܵĻ������� -1
    */
    Int32 GetFileBufferSize(const char* pszFilePath);

    /**
    @brief ���õ�ǰ���ŵ���Ч ID
    @param nSoundID ��Ҫ���ŵ���ЧID
    */
    void SetCurrentSoundID(Int32 nSoundID);

    /**
    @brief ��ȡ��ǰ���ŵ���Ч ID
    @return ��ǰ���ŵ���ЧID
    */
    Int32 GetCurrentSoundID();

private:
    Boolean OpenAudioFile(const char* pszFilePath);

private:
    // ���������������
    TCOM_MediaPlayer_Method_Play *m_pPlayer;
    TCOM_DataType_SysFile *m_pMediaFile;

    TCOM_MethodEmun m_MethodEmun; // ���ҷ���

    TUChar m_fileName[MAX_PATH];
    Int32  m_nCurrentSoundID;
};

#endif
