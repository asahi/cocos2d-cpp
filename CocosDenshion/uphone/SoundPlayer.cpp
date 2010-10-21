#include "SoundPlayer.h"
#include "TCOM_MediaPlayer_IIDs.h"
#include "TCOM_Generic_DataType_IIDs.h"

#define BREAK_IF(cond)      if (cond) break;

SoundPlayer::SoundPlayer()
: m_pPlayer(NULL)
, m_pMediaFile(NULL)
, m_MethodEmun(NULL)
, m_nCurrentSoundID(0)
, m_bPaused(FALSE)
{
    // TCOM��ʼ����ʹ��TCOM���ǰ�����ȳ�ʼ��
    TCoInitialize(NULL);           
    // �������������ʵ��
    if(m_MethodEmun.EnumMethod(TIID_DataType_SysFile, 0,  TIID_MediaPlayer_Method_Play )>0) //<=0��ʾû�ҵ�����
    {           
        //����������ͽӿ�
        if(m_MethodEmun.GetDataTypeInterface(0,TCOM_CLSCTX_INPROC_SERVER,(LPVOID *)&m_pMediaFile)>= 0) 
        {
            //��ѯ�����ӿ�
            HRESULT hr = m_pMediaFile->QueryInterface( TIID_MediaPlayer_Method_Play ,(LPVOID*)&m_pPlayer);
            if(TCOM_S_FAIL(hr))
            {
                // ������
            }
            else
            {
                // ����Ĭ�ϵ�����
                m_pPlayer->SetVolume(100);
            }
        }
    }

    MemSet(m_fileName, 0, sizeof(m_fileName));
}

SoundPlayer::~SoundPlayer()
{
    Release();
}

Boolean SoundPlayer::OpenAudioFile(const char* pszFilePath)
{
    Boolean bRet = FALSE;

    do 
    {
        BREAK_IF(!m_pMediaFile);

        TUString::StrGBToUnicode(m_fileName, (const Char*)pszFilePath);
        BREAK_IF(!EOS_IsFileExist(m_fileName));

        m_pMediaFile->SetName(m_fileName);
        BREAK_IF(! m_pPlayer->Open());

        bRet = TRUE;
    } while (0);

    return bRet;
}

void SoundPlayer::PlaySoundFile(const char* pFileName, Int32 nTimes)
{
    if (OpenAudioFile(pFileName))
    {
        m_pPlayer->Start();
        m_pPlayer->SetLoopTimes(nTimes);
    }
}

void SoundPlayer::PlaySoundFromMem(UInt8* pData, Int32 nSize, const char* FileName, Int32 nTimes)
{
    if (m_pMediaFile)
    {
        Int32 nRet = m_pMediaFile->SetContent(pData, nSize);

        if (! strlen(FileName))
        {
            // û��ָ���ļ��������� .wav ��ʽ����
            const TUChar ExtendName[] = {'.', 'w', 'a', 'v', 0};
            const TUChar format[]     = { '%', 'd', 0};
            TUString::StrPrintF(m_fileName, format, nSize);
            TUString::StrCat(m_fileName, ExtendName);
        }
        else
        {
            // ʹ��ָ�����ļ���
            TUString::StrGBToUnicode(m_fileName, (const Char*)(FileName));
        }

        m_pMediaFile->SetName(m_fileName);
        m_pMediaFile->SetMode(SYS_FILE_MEMORY_FILE_TYPE);

        if (m_pPlayer->Open())
        {
            m_pPlayer->Start();
            m_pPlayer->SetLoopTimes(nTimes);
        }
    }
}

void SoundPlayer::SetVolumeValue(Int32 nValue)
{
    if (m_pPlayer)
    {
        m_pPlayer->SetVolume(nValue);
    }
}

void SoundPlayer::Release()
{
    // �ͷŲ��������ָ��
    if (m_pPlayer)
    {
        m_pPlayer->Release();
        m_pPlayer = NULL;
    }
    if (m_pMediaFile)
    {
        m_pMediaFile->Release();
        m_pMediaFile = NULL;
    }

    TCoUninitialize(); // TCOM����ʼ�����ͷ�TCOM��Դ
}

void SoundPlayer::Pause()
{
    if (! m_bPaused)
    {
        m_pPlayer->Pause();
        m_bPaused = TRUE;
    }
}

void SoundPlayer::Resume()
{
    if (m_bPaused)
    {
        m_pPlayer->Pause();
        m_bPaused = FALSE;
    }
}

void SoundPlayer::Stop()
{
    if (m_pPlayer)
    {
        m_pPlayer->Stop();
    }
}

void SoundPlayer::Rewind()
{
    if (m_pPlayer && m_pPlayer->HasAudio())
    {
        m_pPlayer->Stop();
        m_pPlayer->Start();
    }
}

void SoundPlayer::Mute(bool bMute)
{
    if (m_pPlayer)
    {
        m_pPlayer->Mute(bMute);
    }
}

bool SoundPlayer::IsPlaying()
{
//     TMediaPlayerStatus status = m_pPlayer->GetCurrentStatus();
// 
//     return (status == PLAYER_STATUS_PLAYING || status == PLAYER_STATUS_PAUSED);
    return false;
}

Int32 SoundPlayer::GetFileBufferSize(const char* pszFilePath)
{
    Int32 nRet = -1;

    if (OpenAudioFile(pszFilePath))
    {
        const TMM_AudioInfo* pAudioInfo = m_pPlayer->GetAudioInfo();
        Int32  samplesPerSec = pAudioInfo->samplesPerSec;
        Int32  bitsPerSample = pAudioInfo->bitsPerSample;
        Int32  channelNum    = pAudioInfo->channelNum;
        UInt32 durationInSec = pAudioInfo->durationInSec;

        if (durationInSec == 0)
        {
            durationInSec = 1;
        }
        nRet = samplesPerSec * bitsPerSample * channelNum / 8 * durationInSec;

//        nRet = m_pPlayer->GetDecodedAudioSize();

        m_pPlayer->Close();
    }

    return nRet;
}

Int32 SoundPlayer::DecodeFile(void* buffer, Int32 bufferLen, const char* pszFilePath)
{
    Int32 nRet = -1;

    UInt8* pBuffer = (UInt8*) buffer;

    if (OpenAudioFile(pszFilePath))
    {
        nRet = m_pPlayer->DecodeAudioToBuffer(pBuffer, bufferLen, TMM_AUDIO_FILE_WAV);

        m_pPlayer->Close();
    }

    return nRet;
}

void SoundPlayer::SetCurrentSoundID(Int32 nSoundID)
{
    m_nCurrentSoundID = nSoundID;
}

Int32 SoundPlayer::GetCurrentSoundID()
{
    return m_nCurrentSoundID;
}
