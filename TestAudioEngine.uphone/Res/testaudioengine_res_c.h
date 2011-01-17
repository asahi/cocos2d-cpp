//------------------------------------------------------------------------------
//                      TestAudioEngine_Res_c.h
//              ��Դ������ת���ļ����ݶ����ļ�
//
//
//        Copyright (C) Tranzda CORPORATION
//
//---�ȱ�������Ϣ��---
//   ����������: TR3C.exe 
//   �������汾: TG3 ��Դ������ �汾V1.5  Build 94
//
//---��ע���---
// ���棺δ�������κ��˲�׼�����޸Ĵ��ļ�!!!�������Ը�!
//
//------------------------------------------------------------------------------
#include "testaudioengine_res_h.h" //���Ͷ���ͷ�ļ� 
#ifndef WIN32 
//#pragma diag_remark 1296 
#endif
#if 11<RES_VERSION 
#error Resource file version too low!Must be compiled with higher version TR3C.
#endif


/************************************************************
*     Language:CHS
*************************************************************/


const ResProjectType  TESTAU_project=
{ 
  320,	//screenWidth 
  480,	//screenHeight 
  16500,	//screenDPI 
};


/*-------------------------------------------------------------
*     IDΪTESTAU_ID_Form1002���������
------------------------------------------------------------*/


/*"TestAudioEngine"*/
const TUChar TESTAU_Form1002TitleStr[]={0x0054,0x0065,0x0073,0x0074,0x0041,0x0075,0x0064,0x0069,0x006F,0x0045,0x006E,0x0067,0x0069,0x006E,0x0065,0x0000};

extern const ResCommonType * const TESTAU_Form1002_ControlList[];
const ResWindowType TESTAU_Form1002 =
{
  {//��Դ����ͷ������
    TESTAU_ID_Form1002,//��ԴID
    RES_CLASS_FORM,//��Դ����ΪFORM(����)����
    sizeof(ResWindowType),//��Դ��С
    -1,//����ԴID(����û�й�Ϊ-1)
    0,//Tag
    0//StyleOption
  },//��Դ����ͷ���������
  {//ControlAttrType����
    0,//Enabled,(nouse here)
    0,//Visibled,(nouse here)
    0,//Ctl3D,,(nouse here)
    0,//TabStop,(nouse here)
    0,//ReadOnly,(nouse here)
    0,//ImeEnable,(nouse here)
    0,//WordWrap,(nouse here)
    0,//TopLeftIsLock,(nouse here)
    0,//Check,(nouse here)
    0,//MultiLine,(nouse here) 
    0,//AutoSize,(nouse here)
    0,//Modal, 
    0,//Numeric ,Field Use
    0,//AutoShift,Field Use
    0,//DynamicSize,Field Use
    0,//UnderLine,Field Use
    1,//BIClose
    0,//HasStatusBar
    0,//BIAction
    0,//BIMaximize
    0,//ForceShowTitle
    0,//Graphical,(nouse here)
    0,//sbmHasVertical,��ֱ������
    0,//sbmHasHorizontal��ˮƽ������
    0,//sbmAuto,�������Զ�����
    0,//hasImage
    0,//hasCheckBox
    1,//UseSYSDefColor
    0,//Smooth
    0,//ShowText
    1,//TransParent
    0//OwnerDraw
  },
  {//PanelAttr
    2,//HScrollMode,0-auto,1-enable,2-disable
    0,//VScrollMode,0-auto,1-enable,2-disable
  },
  0X3, // BackColor
  0X2, // ForeColor
  {{0, 0}, {320, 480}}, // RectangleType windowBounds
  10, // �ؼ�����
  {//ResWindowExAttrType
    0,//closeBtnStyle
    0,//actionBtnStyle
    1,//DisableSystemStatusBar
    1,//fullScreen
    0,//rotateMode
  },
  (TUChar *)TESTAU_Form1002TitleStr, //�����ı�������!��
  NULL, // �رհ�ť���֣���ǰΪ�գ���
  NULL, // action button text = null
  0, //CharSet
  stdFont,//Font
  -1, //MainMenuID(-1Ϊû�����˵�)
  TG3_WINDOW_MOVIE_MODE_DEFAULT						, // ��������ģʽ
  TG3_WINDOW_MOVIE_MODE_DEFAULT						, // �رն���ģʽ
  (ResCommonType **)TESTAU_Form1002_ControlList, // ָ��ؼ��б�
  0, // ��ת�ο����������
  NULL // ������ת�ο���(��)
};//����TESTAU_Form1002��Դ���ݳ�������

//----------------------- Button TESTAU_PlayBack���Զ��� Begin------------------------
/*"PlayBackgroundMusic"*/
const TUChar TESTAU_PlayBackCaption[]={0x0050,0x006C,0x0061,0x0079,0x0042,0x0061,0x0063,0x006B,0x0067,0x0072,0x006F,0x0075,0x006E,0x0064,0x004D,0x0075,0x0073,0x0069,0x0063,
0x0000};

const ResButtonType TESTAU_PlayBack=//
{
  {//��Դ����ͷ������
    TESTAU_ID_Form1002_PlayBack, //��ԴID�� 
    RES_CLASS_BUTTON,
    sizeof(ResButtonType),//��С
    TESTAU_ID_Form1002,//��������ԴID 
    0,//Tag
    0//StyleOption
  },//��Դ����ͷ���������
  {//���Ա�־
    1,//enabled
    1,//visibled
    0,//ctl3D
    1,//tabStop
    0,//readOnly
    0,//imeEnable
    0,//wordWrap
    0,//topLeftIsLock
    0,//check 
    0,//multiLine,(nouse here) 
    0,//autoSize,(nouse here)
    0,//modal,(Formʹ��) 
    0,//numeric,(nouse here)
    0,//autoShift,(nouse here)
    0,//dynamicSize,(nouse here)
    0,//underLine,(nouse here)
    0,//bIClose,(nouse here)
    0,//HasStatusBar,(nouse here)
    0,//bIAction,(nouse here)
    0,//bIMaximize,(nouse here)
    0,//ForceShowTitle,(nouse here)
    0,//graphical
    0,//sbmHasVertical,��ֱ������
    0,//sbmHasHorizontal��ˮƽ������
    0,//sbmAuto,�������Զ�����
    0,//hasImage
    0,//hasCheckBox
    1,//UseSYSDefColor
    0,//Smooth
    0,//ShowText
    1,//TransParent
    0//OwnerDraw
  },//���Ա�־����
  {{5, 60}, {200, 30}},//rect
  0x3,//backColor
  0x2,//boreColor
  0x4,//selectedBackColor
  0x5,//selectedForeColor
  0x6,//focusBackColor
  0x7,//focusForeColor
  (TUChar *)TESTAU_PlayBackCaption,//Caption
  0,//charSet
  stdFont,//Font
  -1,//BitmapID
  -1,//SelectedBitmapID
  -1,//FocusBitmapID
  0,//Style
  1,//TabOrder
  0//TabOrderGroup
};//TESTAU_PlayBack�������

//----------------------- Button TESTAU_PlayBack���Զ��� End------------------------

//----------------------- Button TESTAU_StopBack���Զ��� Begin------------------------
/*"StopBackgroundMusic"*/
const TUChar TESTAU_StopBackCaption[]={0x0053,0x0074,0x006F,0x0070,0x0042,0x0061,0x0063,0x006B,0x0067,0x0072,0x006F,0x0075,0x006E,0x0064,0x004D,0x0075,0x0073,0x0069,0x0063,
0x0000};

const ResButtonType TESTAU_StopBack=//
{
  {//��Դ����ͷ������
    TESTAU_ID_Form1002_StopBack, //��ԴID�� 
    RES_CLASS_BUTTON,
    sizeof(ResButtonType),//��С
    TESTAU_ID_Form1002,//��������ԴID 
    0,//Tag
    0//StyleOption
  },//��Դ����ͷ���������
  {//���Ա�־
    1,//enabled
    1,//visibled
    0,//ctl3D
    1,//tabStop
    0,//readOnly
    0,//imeEnable
    0,//wordWrap
    0,//topLeftIsLock
    0,//check 
    0,//multiLine,(nouse here) 
    0,//autoSize,(nouse here)
    0,//modal,(Formʹ��) 
    0,//numeric,(nouse here)
    0,//autoShift,(nouse here)
    0,//dynamicSize,(nouse here)
    0,//underLine,(nouse here)
    0,//bIClose,(nouse here)
    0,//HasStatusBar,(nouse here)
    0,//bIAction,(nouse here)
    0,//bIMaximize,(nouse here)
    0,//ForceShowTitle,(nouse here)
    0,//graphical
    0,//sbmHasVertical,��ֱ������
    0,//sbmHasHorizontal��ˮƽ������
    0,//sbmAuto,�������Զ�����
    0,//hasImage
    0,//hasCheckBox
    1,//UseSYSDefColor
    0,//Smooth
    0,//ShowText
    1,//TransParent
    0//OwnerDraw
  },//���Ա�־����
  {{5, 95}, {200, 30}},//rect
  0x3,//backColor
  0x2,//boreColor
  0x4,//selectedBackColor
  0x5,//selectedForeColor
  0x6,//focusBackColor
  0x7,//focusForeColor
  (TUChar *)TESTAU_StopBackCaption,//Caption
  0,//charSet
  stdFont,//Font
  -1,//BitmapID
  -1,//SelectedBitmapID
  -1,//FocusBitmapID
  0,//Style
  2,//TabOrder
  0//TabOrderGroup
};//TESTAU_StopBack�������

//----------------------- Button TESTAU_StopBack���Զ��� End------------------------

//----------------------- Button TESTAU_LoadEffect���Զ��� Begin------------------------
/*"LoadEffect"*/
const TUChar TESTAU_LoadEffectCaption[]={0x004C,0x006F,0x0061,0x0064,0x0045,0x0066,0x0066,0x0065,0x0063,0x0074,0x0000};

const ResButtonType TESTAU_LoadEffect=//
{
  {//��Դ����ͷ������
    TESTAU_ID_Form1002_LoadEffect, //��ԴID�� 
    RES_CLASS_BUTTON,
    sizeof(ResButtonType),//��С
    TESTAU_ID_Form1002,//��������ԴID 
    0,//Tag
    0//StyleOption
  },//��Դ����ͷ���������
  {//���Ա�־
    1,//enabled
    1,//visibled
    0,//ctl3D
    1,//tabStop
    0,//readOnly
    0,//imeEnable
    0,//wordWrap
    0,//topLeftIsLock
    0,//check 
    0,//multiLine,(nouse here) 
    0,//autoSize,(nouse here)
    0,//modal,(Formʹ��) 
    0,//numeric,(nouse here)
    0,//autoShift,(nouse here)
    0,//dynamicSize,(nouse here)
    0,//underLine,(nouse here)
    0,//bIClose,(nouse here)
    0,//HasStatusBar,(nouse here)
    0,//bIAction,(nouse here)
    0,//bIMaximize,(nouse here)
    0,//ForceShowTitle,(nouse here)
    0,//graphical
    0,//sbmHasVertical,��ֱ������
    0,//sbmHasHorizontal��ˮƽ������
    0,//sbmAuto,�������Զ�����
    0,//hasImage
    0,//hasCheckBox
    1,//UseSYSDefColor
    0,//Smooth
    0,//ShowText
    1,//TransParent
    0//OwnerDraw
  },//���Ա�־����
  {{5, 250}, {107, 30}},//rect
  0x3,//backColor
  0x2,//boreColor
  0x4,//selectedBackColor
  0x5,//selectedForeColor
  0x6,//focusBackColor
  0x7,//focusForeColor
  (TUChar *)TESTAU_LoadEffectCaption,//Caption
  0,//charSet
  stdFont,//Font
  -1,//BitmapID
  -1,//SelectedBitmapID
  -1,//FocusBitmapID
  0,//Style
  3,//TabOrder
  0//TabOrderGroup
};//TESTAU_LoadEffect�������

//----------------------- Button TESTAU_LoadEffect���Զ��� End------------------------

//----------------------- Button TESTAU_PlayEffect���Զ��� Begin------------------------
/*"PlayEffect"*/
const TUChar TESTAU_PlayEffectCaption[]={0x0050,0x006C,0x0061,0x0079,0x0045,0x0066,0x0066,0x0065,0x0063,0x0074,0x0000};

const ResButtonType TESTAU_PlayEffect=//
{
  {//��Դ����ͷ������
    TESTAU_ID_Form1002_PlayEffect, //��ԴID�� 
    RES_CLASS_BUTTON,
    sizeof(ResButtonType),//��С
    TESTAU_ID_Form1002,//��������ԴID 
    0,//Tag
    0//StyleOption
  },//��Դ����ͷ���������
  {//���Ա�־
    1,//enabled
    1,//visibled
    0,//ctl3D
    1,//tabStop
    0,//readOnly
    0,//imeEnable
    0,//wordWrap
    0,//topLeftIsLock
    0,//check 
    0,//multiLine,(nouse here) 
    0,//autoSize,(nouse here)
    0,//modal,(Formʹ��) 
    0,//numeric,(nouse here)
    0,//autoShift,(nouse here)
    0,//dynamicSize,(nouse here)
    0,//underLine,(nouse here)
    0,//bIClose,(nouse here)
    0,//HasStatusBar,(nouse here)
    0,//bIAction,(nouse here)
    0,//bIMaximize,(nouse here)
    0,//ForceShowTitle,(nouse here)
    0,//graphical
    0,//sbmHasVertical,��ֱ������
    0,//sbmHasHorizontal��ˮƽ������
    0,//sbmAuto,�������Զ�����
    0,//hasImage
    0,//hasCheckBox
    1,//UseSYSDefColor
    0,//Smooth
    0,//ShowText
    1,//TransParent
    0//OwnerDraw
  },//���Ա�־����
  {{5, 288}, {107, 30}},//rect
  0x3,//backColor
  0x2,//boreColor
  0x4,//selectedBackColor
  0x5,//selectedForeColor
  0x6,//focusBackColor
  0x7,//focusForeColor
  (TUChar *)TESTAU_PlayEffectCaption,//Caption
  0,//charSet
  stdFont,//Font
  -1,//BitmapID
  -1,//SelectedBitmapID
  -1,//FocusBitmapID
  0,//Style
  4,//TabOrder
  0//TabOrderGroup
};//TESTAU_PlayEffect�������

//----------------------- Button TESTAU_PlayEffect���Զ��� End------------------------

//----------------------- Button TESTAU_UnLoadBtn���Զ��� Begin------------------------
/*"UnLoadEffect"*/
const TUChar TESTAU_UnLoadBtnCaption[]={0x0055,0x006E,0x004C,0x006F,0x0061,0x0064,0x0045,0x0066,0x0066,0x0065,0x0063,0x0074,0x0000};

const ResButtonType TESTAU_UnLoadBtn=//
{
  {//��Դ����ͷ������
    TESTAU_ID_Form1002_UnLoadBtn, //��ԴID�� 
    RES_CLASS_BUTTON,
    sizeof(ResButtonType),//��С
    TESTAU_ID_Form1002,//��������ԴID 
    0,//Tag
    0//StyleOption
  },//��Դ����ͷ���������
  {//���Ա�־
    1,//enabled
    1,//visibled
    0,//ctl3D
    1,//tabStop
    0,//readOnly
    0,//imeEnable
    0,//wordWrap
    0,//topLeftIsLock
    0,//check 
    0,//multiLine,(nouse here) 
    0,//autoSize,(nouse here)
    0,//modal,(Formʹ��) 
    0,//numeric,(nouse here)
    0,//autoShift,(nouse here)
    0,//dynamicSize,(nouse here)
    0,//underLine,(nouse here)
    0,//bIClose,(nouse here)
    0,//HasStatusBar,(nouse here)
    0,//bIAction,(nouse here)
    0,//bIMaximize,(nouse here)
    0,//ForceShowTitle,(nouse here)
    0,//graphical
    0,//sbmHasVertical,��ֱ������
    0,//sbmHasHorizontal��ˮƽ������
    0,//sbmAuto,�������Զ�����
    0,//hasImage
    0,//hasCheckBox
    1,//UseSYSDefColor
    0,//Smooth
    0,//ShowText
    1,//TransParent
    0//OwnerDraw
  },//���Ա�־����
  {{125, 250}, {120, 30}},//rect
  0x3,//backColor
  0x2,//boreColor
  0x4,//selectedBackColor
  0x5,//selectedForeColor
  0x6,//focusBackColor
  0x7,//focusForeColor
  (TUChar *)TESTAU_UnLoadBtnCaption,//Caption
  0,//charSet
  stdFont,//Font
  -1,//BitmapID
  -1,//SelectedBitmapID
  -1,//FocusBitmapID
  0,//Style
  5,//TabOrder
  0//TabOrderGroup
};//TESTAU_UnLoadBtn�������

//----------------------- Button TESTAU_UnLoadBtn���Զ��� End------------------------

//----------------------- Button TESTAU_PauseBack���Զ��� Begin------------------------
/*"Pause"*/
const TUChar TESTAU_PauseBackCaption[]={0x0050,0x0061,0x0075,0x0073,0x0065,0x0000};

const ResButtonType TESTAU_PauseBack=//
{
  {//��Դ����ͷ������
    TESTAU_ID_Form1002_PauseBack, //��ԴID�� 
    RES_CLASS_BUTTON,
    sizeof(ResButtonType),//��С
    TESTAU_ID_Form1002,//��������ԴID 
    0,//Tag
    0//StyleOption
  },//��Դ����ͷ���������
  {//���Ա�־
    1,//enabled
    1,//visibled
    0,//ctl3D
    1,//tabStop
    0,//readOnly
    0,//imeEnable
    0,//wordWrap
    0,//topLeftIsLock
    0,//check 
    0,//multiLine,(nouse here) 
    0,//autoSize,(nouse here)
    0,//modal,(Formʹ��) 
    0,//numeric,(nouse here)
    0,//autoShift,(nouse here)
    0,//dynamicSize,(nouse here)
    0,//underLine,(nouse here)
    0,//bIClose,(nouse here)
    0,//HasStatusBar,(nouse here)
    0,//bIAction,(nouse here)
    0,//bIMaximize,(nouse here)
    0,//ForceShowTitle,(nouse here)
    0,//graphical
    0,//sbmHasVertical,��ֱ������
    0,//sbmHasHorizontal��ˮƽ������
    0,//sbmAuto,�������Զ�����
    0,//hasImage
    0,//hasCheckBox
    1,//UseSYSDefColor
    0,//Smooth
    0,//ShowText
    1,//TransParent
    0//OwnerDraw
  },//���Ա�־����
  {{209, 60}, {100, 30}},//rect
  0x3,//backColor
  0x2,//boreColor
  0x4,//selectedBackColor
  0x5,//selectedForeColor
  0x6,//focusBackColor
  0x7,//focusForeColor
  (TUChar *)TESTAU_PauseBackCaption,//Caption
  0,//charSet
  stdFont,//Font
  -1,//BitmapID
  -1,//SelectedBitmapID
  -1,//FocusBitmapID
  0,//Style
  6,//TabOrder
  0//TabOrderGroup
};//TESTAU_PauseBack�������

//----------------------- Button TESTAU_PauseBack���Զ��� End------------------------

//----------------------- Button TESTAU_BackVolumeUp���Զ��� Begin------------------------
/*"BackVolumeUp"*/
const TUChar TESTAU_BackVolumeUpCaption[]={0x0042,0x0061,0x0063,0x006B,0x0056,0x006F,0x006C,0x0075,0x006D,0x0065,0x0055,0x0070,0x0000};

const ResButtonType TESTAU_BackVolumeUp=//
{
  {//��Դ����ͷ������
    TESTAU_ID_Form1002_BackVolumeUp, //��ԴID�� 
    RES_CLASS_BUTTON,
    sizeof(ResButtonType),//��С
    TESTAU_ID_Form1002,//��������ԴID 
    0,//Tag
    0//StyleOption
  },//��Դ����ͷ���������
  {//���Ա�־
    1,//enabled
    1,//visibled
    0,//ctl3D
    1,//tabStop
    0,//readOnly
    0,//imeEnable
    0,//wordWrap
    0,//topLeftIsLock
    0,//check 
    0,//multiLine,(nouse here) 
    0,//autoSize,(nouse here)
    0,//modal,(Formʹ��) 
    0,//numeric,(nouse here)
    0,//autoShift,(nouse here)
    0,//dynamicSize,(nouse here)
    0,//underLine,(nouse here)
    0,//bIClose,(nouse here)
    0,//HasStatusBar,(nouse here)
    0,//bIAction,(nouse here)
    0,//bIMaximize,(nouse here)
    0,//ForceShowTitle,(nouse here)
    0,//graphical
    0,//sbmHasVertical,��ֱ������
    0,//sbmHasHorizontal��ˮƽ������
    0,//sbmAuto,�������Զ�����
    0,//hasImage
    0,//hasCheckBox
    1,//UseSYSDefColor
    0,//Smooth
    0,//ShowText
    1,//TransParent
    0//OwnerDraw
  },//���Ա�־����
  {{5, 135}, {170, 40}},//rect
  0x3,//backColor
  0x2,//boreColor
  0x4,//selectedBackColor
  0x5,//selectedForeColor
  0x6,//focusBackColor
  0x7,//focusForeColor
  (TUChar *)TESTAU_BackVolumeUpCaption,//Caption
  0,//charSet
  stdFont,//Font
  -1,//BitmapID
  -1,//SelectedBitmapID
  -1,//FocusBitmapID
  0,//Style
  7,//TabOrder
  0//TabOrderGroup
};//TESTAU_BackVolumeUp�������

//----------------------- Button TESTAU_BackVolumeUp���Զ��� End------------------------

//----------------------- Button TESTAU_BackVolumeDown���Զ��� Begin------------------------
/*"BackVolumeDown"*/
const TUChar TESTAU_BackVolumeDownCaption[]={0x0042,0x0061,0x0063,0x006B,0x0056,0x006F,0x006C,0x0075,0x006D,0x0065,0x0044,0x006F,0x0077,0x006E,0x0000};

const ResButtonType TESTAU_BackVolumeDown=//
{
  {//��Դ����ͷ������
    TESTAU_ID_Form1002_BackVolumeDown, //��ԴID�� 
    RES_CLASS_BUTTON,
    sizeof(ResButtonType),//��С
    TESTAU_ID_Form1002,//��������ԴID 
    0,//Tag
    0//StyleOption
  },//��Դ����ͷ���������
  {//���Ա�־
    1,//enabled
    1,//visibled
    0,//ctl3D
    1,//tabStop
    0,//readOnly
    0,//imeEnable
    0,//wordWrap
    0,//topLeftIsLock
    0,//check 
    0,//multiLine,(nouse here) 
    0,//autoSize,(nouse here)
    0,//modal,(Formʹ��) 
    0,//numeric,(nouse here)
    0,//autoShift,(nouse here)
    0,//dynamicSize,(nouse here)
    0,//underLine,(nouse here)
    0,//bIClose,(nouse here)
    0,//HasStatusBar,(nouse here)
    0,//bIAction,(nouse here)
    0,//bIMaximize,(nouse here)
    0,//ForceShowTitle,(nouse here)
    0,//graphical
    0,//sbmHasVertical,��ֱ������
    0,//sbmHasHorizontal��ˮƽ������
    0,//sbmAuto,�������Զ�����
    0,//hasImage
    0,//hasCheckBox
    1,//UseSYSDefColor
    0,//Smooth
    0,//ShowText
    1,//TransParent
    0//OwnerDraw
  },//���Ա�־����
  {{5, 180}, {170, 40}},//rect
  0x3,//backColor
  0x2,//boreColor
  0x4,//selectedBackColor
  0x5,//selectedForeColor
  0x6,//focusBackColor
  0x7,//focusForeColor
  (TUChar *)TESTAU_BackVolumeDownCaption,//Caption
  0,//charSet
  stdFont,//Font
  -1,//BitmapID
  -1,//SelectedBitmapID
  -1,//FocusBitmapID
  0,//Style
  8,//TabOrder
  0//TabOrderGroup
};//TESTAU_BackVolumeDown�������

//----------------------- Button TESTAU_BackVolumeDown���Զ��� End------------------------

//----------------------- Button TESTAU_EffectVolumeUp���Զ��� Begin------------------------
/*"EffectVolumeUp"*/
const TUChar TESTAU_EffectVolumeUpCaption[]={0x0045,0x0066,0x0066,0x0065,0x0063,0x0074,0x0056,0x006F,0x006C,0x0075,0x006D,0x0065,0x0055,0x0070,0x0000};

const ResButtonType TESTAU_EffectVolumeUp=//
{
  {//��Դ����ͷ������
    TESTAU_ID_Form1002_EffectVolumeUp, //��ԴID�� 
    RES_CLASS_BUTTON,
    sizeof(ResButtonType),//��С
    TESTAU_ID_Form1002,//��������ԴID 
    0,//Tag
    0//StyleOption
  },//��Դ����ͷ���������
  {//���Ա�־
    1,//enabled
    1,//visibled
    0,//ctl3D
    1,//tabStop
    0,//readOnly
    0,//imeEnable
    0,//wordWrap
    0,//topLeftIsLock
    0,//check 
    0,//multiLine,(nouse here) 
    0,//autoSize,(nouse here)
    0,//modal,(Formʹ��) 
    0,//numeric,(nouse here)
    0,//autoShift,(nouse here)
    0,//dynamicSize,(nouse here)
    0,//underLine,(nouse here)
    0,//bIClose,(nouse here)
    0,//HasStatusBar,(nouse here)
    0,//bIAction,(nouse here)
    0,//bIMaximize,(nouse here)
    0,//ForceShowTitle,(nouse here)
    0,//graphical
    0,//sbmHasVertical,��ֱ������
    0,//sbmHasHorizontal��ˮƽ������
    0,//sbmAuto,�������Զ�����
    0,//hasImage
    0,//hasCheckBox
    1,//UseSYSDefColor
    0,//Smooth
    0,//ShowText
    1,//TransParent
    0//OwnerDraw
  },//���Ա�־����
  {{5, 330}, {170, 40}},//rect
  0x3,//backColor
  0x2,//boreColor
  0x4,//selectedBackColor
  0x5,//selectedForeColor
  0x6,//focusBackColor
  0x7,//focusForeColor
  (TUChar *)TESTAU_EffectVolumeUpCaption,//Caption
  0,//charSet
  stdFont,//Font
  -1,//BitmapID
  -1,//SelectedBitmapID
  -1,//FocusBitmapID
  0,//Style
  9,//TabOrder
  0//TabOrderGroup
};//TESTAU_EffectVolumeUp�������

//----------------------- Button TESTAU_EffectVolumeUp���Զ��� End------------------------

//----------------------- Button TESTAU_EffectVolumeDown���Զ��� Begin------------------------
/*"EffectVolumeDown"*/
const TUChar TESTAU_EffectVolumeDownCaption[]={0x0045,0x0066,0x0066,0x0065,0x0063,0x0074,0x0056,0x006F,0x006C,0x0075,0x006D,0x0065,0x0044,0x006F,0x0077,0x006E,0x0000};

const ResButtonType TESTAU_EffectVolumeDown=//
{
  {//��Դ����ͷ������
    TESTAU_ID_Form1002_EffectVolumeDown, //��ԴID�� 
    RES_CLASS_BUTTON,
    sizeof(ResButtonType),//��С
    TESTAU_ID_Form1002,//��������ԴID 
    0,//Tag
    0//StyleOption
  },//��Դ����ͷ���������
  {//���Ա�־
    1,//enabled
    1,//visibled
    0,//ctl3D
    1,//tabStop
    0,//readOnly
    0,//imeEnable
    0,//wordWrap
    0,//topLeftIsLock
    0,//check 
    0,//multiLine,(nouse here) 
    0,//autoSize,(nouse here)
    0,//modal,(Formʹ��) 
    0,//numeric,(nouse here)
    0,//autoShift,(nouse here)
    0,//dynamicSize,(nouse here)
    0,//underLine,(nouse here)
    0,//bIClose,(nouse here)
    0,//HasStatusBar,(nouse here)
    0,//bIAction,(nouse here)
    0,//bIMaximize,(nouse here)
    0,//ForceShowTitle,(nouse here)
    0,//graphical
    0,//sbmHasVertical,��ֱ������
    0,//sbmHasHorizontal��ˮƽ������
    0,//sbmAuto,�������Զ�����
    0,//hasImage
    0,//hasCheckBox
    1,//UseSYSDefColor
    0,//Smooth
    0,//ShowText
    1,//TransParent
    0//OwnerDraw
  },//���Ա�־����
  {{5, 380}, {170, 40}},//rect
  0x3,//backColor
  0x2,//boreColor
  0x4,//selectedBackColor
  0x5,//selectedForeColor
  0x6,//focusBackColor
  0x7,//focusForeColor
  (TUChar *)TESTAU_EffectVolumeDownCaption,//Caption
  0,//charSet
  stdFont,//Font
  -1,//BitmapID
  -1,//SelectedBitmapID
  -1,//FocusBitmapID
  0,//Style
  10,//TabOrder
  0//TabOrderGroup
};//TESTAU_EffectVolumeDown�������

//----------------------- Button TESTAU_EffectVolumeDown���Զ��� End------------------------
const ResCommonType * const TESTAU_Form1002_ControlList[10]=
{
  (ResCommonType *)&TESTAU_PlayBack
  ,(ResCommonType *)&TESTAU_StopBack
  ,(ResCommonType *)&TESTAU_LoadEffect
  ,(ResCommonType *)&TESTAU_PlayEffect
  ,(ResCommonType *)&TESTAU_UnLoadBtn
  ,(ResCommonType *)&TESTAU_PauseBack
  ,(ResCommonType *)&TESTAU_BackVolumeUp
  ,(ResCommonType *)&TESTAU_BackVolumeDown
  ,(ResCommonType *)&TESTAU_EffectVolumeUp
  ,(ResCommonType *)&TESTAU_EffectVolumeDown
};

const ResourceLangRegisterEntry TESTAU_CHS_Resource[] = 
{
  {kProjectRscType,0,(void*)&TESTAU_project,sizeof(TESTAU_project)}   
  ,{kWindowRscType,TESTAU_ID_Form1002,(void*)&TESTAU_Form1002,sizeof(TESTAU_Form1002)}   
};

const ResourceLangRegisterEntry2  TESTAU_CHS_ResourceEntry = 
{
  tgresource_tag,
  11,//res version
  0,//subVersionValue
  0,//reserved1
  0,//reserved2
  TESTAU_CHS_Resource
};


/************************************************************
*     Language:ENU
*************************************************************/


const ResProjectType  TESTAU_ENU_project=
{ 
  320,	//screenWidth 
  480,	//screenHeight 
  16500,	//screenDPI 
};


/*-------------------------------------------------------------
*     IDΪTESTAU_ID_Form1002���������
------------------------------------------------------------*/


/*"TestAudioEngine"*/
const TUChar TESTAU_ENU_Form1002TitleStr[]={0x0054,0x0065,0x0073,0x0074,0x0041,0x0075,0x0064,0x0069,0x006F,0x0045,0x006E,0x0067,0x0069,0x006E,0x0065,0x0000};

extern const ResCommonType * const TESTAU_ENU_Form1002_ControlList[];
const ResWindowType TESTAU_ENU_Form1002 =
{
  {//��Դ����ͷ������
    TESTAU_ID_Form1002,//��ԴID
    RES_CLASS_FORM,//��Դ����ΪFORM(����)����
    sizeof(ResWindowType),//��Դ��С
    -1,//����ԴID(����û�й�Ϊ-1)
    0,//Tag
    0//StyleOption
  },//��Դ����ͷ���������
  {//ControlAttrType����
    0,//Enabled,(nouse here)
    0,//Visibled,(nouse here)
    0,//Ctl3D,,(nouse here)
    0,//TabStop,(nouse here)
    0,//ReadOnly,(nouse here)
    0,//ImeEnable,(nouse here)
    0,//WordWrap,(nouse here)
    0,//TopLeftIsLock,(nouse here)
    0,//Check,(nouse here)
    0,//MultiLine,(nouse here) 
    0,//AutoSize,(nouse here)
    0,//Modal, 
    0,//Numeric ,Field Use
    0,//AutoShift,Field Use
    0,//DynamicSize,Field Use
    0,//UnderLine,Field Use
    1,//BIClose
    0,//HasStatusBar
    0,//BIAction
    0,//BIMaximize
    0,//ForceShowTitle
    0,//Graphical,(nouse here)
    0,//sbmHasVertical,��ֱ������
    0,//sbmHasHorizontal��ˮƽ������
    0,//sbmAuto,�������Զ�����
    0,//hasImage
    0,//hasCheckBox
    1,//UseSYSDefColor
    0,//Smooth
    0,//ShowText
    1,//TransParent
    0//OwnerDraw
  },
  {//PanelAttr
    2,//HScrollMode,0-auto,1-enable,2-disable
    0,//VScrollMode,0-auto,1-enable,2-disable
  },
  0X3, // BackColor
  0X2, // ForeColor
  {{0, 0}, {320, 480}}, // RectangleType windowBounds
  10, // �ؼ�����
  {//ResWindowExAttrType
    0,//closeBtnStyle
    0,//actionBtnStyle
    1,//DisableSystemStatusBar
    1,//fullScreen
    0,//rotateMode
  },
  (TUChar *)TESTAU_ENU_Form1002TitleStr, //�����ı�������!��
  NULL, // �رհ�ť���֣���ǰΪ�գ���
  NULL, // action button text = null
  0, //CharSet
  stdFont,//Font
  -1, //MainMenuID(-1Ϊû�����˵�)
  TG3_WINDOW_MOVIE_MODE_DEFAULT						, // ��������ģʽ
  TG3_WINDOW_MOVIE_MODE_DEFAULT						, // �رն���ģʽ
  (ResCommonType **)TESTAU_ENU_Form1002_ControlList, // ָ��ؼ��б�
  0, // ��ת�ο����������
  NULL // ������ת�ο���(��)
};//����TESTAU_ENU_Form1002��Դ���ݳ�������

//----------------------- Button TESTAU_ENU_PlayBack���Զ��� Begin------------------------
/*"PlayBackgroundMusic"*/
const TUChar TESTAU_ENU_PlayBackCaption[]={0x0050,0x006C,0x0061,0x0079,0x0042,0x0061,0x0063,0x006B,0x0067,0x0072,0x006F,0x0075,0x006E,0x0064,0x004D,0x0075,0x0073,0x0069,0x0063,
0x0000};

const ResButtonType TESTAU_ENU_PlayBack=//
{
  {//��Դ����ͷ������
    TESTAU_ID_Form1002_PlayBack, //��ԴID�� 
    RES_CLASS_BUTTON,
    sizeof(ResButtonType),//��С
    TESTAU_ID_Form1002,//��������ԴID 
    0,//Tag
    0//StyleOption
  },//��Դ����ͷ���������
  {//���Ա�־
    1,//enabled
    1,//visibled
    0,//ctl3D
    1,//tabStop
    0,//readOnly
    0,//imeEnable
    0,//wordWrap
    0,//topLeftIsLock
    0,//check 
    0,//multiLine,(nouse here) 
    0,//autoSize,(nouse here)
    0,//modal,(Formʹ��) 
    0,//numeric,(nouse here)
    0,//autoShift,(nouse here)
    0,//dynamicSize,(nouse here)
    0,//underLine,(nouse here)
    0,//bIClose,(nouse here)
    0,//HasStatusBar,(nouse here)
    0,//bIAction,(nouse here)
    0,//bIMaximize,(nouse here)
    0,//ForceShowTitle,(nouse here)
    0,//graphical
    0,//sbmHasVertical,��ֱ������
    0,//sbmHasHorizontal��ˮƽ������
    0,//sbmAuto,�������Զ�����
    0,//hasImage
    0,//hasCheckBox
    1,//UseSYSDefColor
    0,//Smooth
    0,//ShowText
    1,//TransParent
    0//OwnerDraw
  },//���Ա�־����
  {{5, 60}, {200, 30}},//rect
  0x3,//backColor
  0x2,//boreColor
  0x4,//selectedBackColor
  0x5,//selectedForeColor
  0x6,//focusBackColor
  0x7,//focusForeColor
  (TUChar *)TESTAU_ENU_PlayBackCaption,//Caption
  0,//charSet
  stdFont,//Font
  -1,//BitmapID
  -1,//SelectedBitmapID
  -1,//FocusBitmapID
  0,//Style
  1,//TabOrder
  0//TabOrderGroup
};//TESTAU_ENU_PlayBack�������

//----------------------- Button TESTAU_ENU_PlayBack���Զ��� End------------------------

//----------------------- Button TESTAU_ENU_StopBack���Զ��� Begin------------------------
/*"StopBackgroundMusic"*/
const TUChar TESTAU_ENU_StopBackCaption[]={0x0053,0x0074,0x006F,0x0070,0x0042,0x0061,0x0063,0x006B,0x0067,0x0072,0x006F,0x0075,0x006E,0x0064,0x004D,0x0075,0x0073,0x0069,0x0063,
0x0000};

const ResButtonType TESTAU_ENU_StopBack=//
{
  {//��Դ����ͷ������
    TESTAU_ID_Form1002_StopBack, //��ԴID�� 
    RES_CLASS_BUTTON,
    sizeof(ResButtonType),//��С
    TESTAU_ID_Form1002,//��������ԴID 
    0,//Tag
    0//StyleOption
  },//��Դ����ͷ���������
  {//���Ա�־
    1,//enabled
    1,//visibled
    0,//ctl3D
    1,//tabStop
    0,//readOnly
    0,//imeEnable
    0,//wordWrap
    0,//topLeftIsLock
    0,//check 
    0,//multiLine,(nouse here) 
    0,//autoSize,(nouse here)
    0,//modal,(Formʹ��) 
    0,//numeric,(nouse here)
    0,//autoShift,(nouse here)
    0,//dynamicSize,(nouse here)
    0,//underLine,(nouse here)
    0,//bIClose,(nouse here)
    0,//HasStatusBar,(nouse here)
    0,//bIAction,(nouse here)
    0,//bIMaximize,(nouse here)
    0,//ForceShowTitle,(nouse here)
    0,//graphical
    0,//sbmHasVertical,��ֱ������
    0,//sbmHasHorizontal��ˮƽ������
    0,//sbmAuto,�������Զ�����
    0,//hasImage
    0,//hasCheckBox
    1,//UseSYSDefColor
    0,//Smooth
    0,//ShowText
    1,//TransParent
    0//OwnerDraw
  },//���Ա�־����
  {{5, 95}, {200, 30}},//rect
  0x3,//backColor
  0x2,//boreColor
  0x4,//selectedBackColor
  0x5,//selectedForeColor
  0x6,//focusBackColor
  0x7,//focusForeColor
  (TUChar *)TESTAU_ENU_StopBackCaption,//Caption
  0,//charSet
  stdFont,//Font
  -1,//BitmapID
  -1,//SelectedBitmapID
  -1,//FocusBitmapID
  0,//Style
  2,//TabOrder
  0//TabOrderGroup
};//TESTAU_ENU_StopBack�������

//----------------------- Button TESTAU_ENU_StopBack���Զ��� End------------------------

//----------------------- Button TESTAU_ENU_LoadEffect���Զ��� Begin------------------------
/*"LoadEffect"*/
const TUChar TESTAU_ENU_LoadEffectCaption[]={0x004C,0x006F,0x0061,0x0064,0x0045,0x0066,0x0066,0x0065,0x0063,0x0074,0x0000};

const ResButtonType TESTAU_ENU_LoadEffect=//
{
  {//��Դ����ͷ������
    TESTAU_ID_Form1002_LoadEffect, //��ԴID�� 
    RES_CLASS_BUTTON,
    sizeof(ResButtonType),//��С
    TESTAU_ID_Form1002,//��������ԴID 
    0,//Tag
    0//StyleOption
  },//��Դ����ͷ���������
  {//���Ա�־
    1,//enabled
    1,//visibled
    0,//ctl3D
    1,//tabStop
    0,//readOnly
    0,//imeEnable
    0,//wordWrap
    0,//topLeftIsLock
    0,//check 
    0,//multiLine,(nouse here) 
    0,//autoSize,(nouse here)
    0,//modal,(Formʹ��) 
    0,//numeric,(nouse here)
    0,//autoShift,(nouse here)
    0,//dynamicSize,(nouse here)
    0,//underLine,(nouse here)
    0,//bIClose,(nouse here)
    0,//HasStatusBar,(nouse here)
    0,//bIAction,(nouse here)
    0,//bIMaximize,(nouse here)
    0,//ForceShowTitle,(nouse here)
    0,//graphical
    0,//sbmHasVertical,��ֱ������
    0,//sbmHasHorizontal��ˮƽ������
    0,//sbmAuto,�������Զ�����
    0,//hasImage
    0,//hasCheckBox
    1,//UseSYSDefColor
    0,//Smooth
    0,//ShowText
    1,//TransParent
    0//OwnerDraw
  },//���Ա�־����
  {{5, 250}, {107, 30}},//rect
  0x3,//backColor
  0x2,//boreColor
  0x4,//selectedBackColor
  0x5,//selectedForeColor
  0x6,//focusBackColor
  0x7,//focusForeColor
  (TUChar *)TESTAU_ENU_LoadEffectCaption,//Caption
  0,//charSet
  stdFont,//Font
  -1,//BitmapID
  -1,//SelectedBitmapID
  -1,//FocusBitmapID
  0,//Style
  3,//TabOrder
  0//TabOrderGroup
};//TESTAU_ENU_LoadEffect�������

//----------------------- Button TESTAU_ENU_LoadEffect���Զ��� End------------------------

//----------------------- Button TESTAU_ENU_PlayEffect���Զ��� Begin------------------------
/*"PlayEffect"*/
const TUChar TESTAU_ENU_PlayEffectCaption[]={0x0050,0x006C,0x0061,0x0079,0x0045,0x0066,0x0066,0x0065,0x0063,0x0074,0x0000};

const ResButtonType TESTAU_ENU_PlayEffect=//
{
  {//��Դ����ͷ������
    TESTAU_ID_Form1002_PlayEffect, //��ԴID�� 
    RES_CLASS_BUTTON,
    sizeof(ResButtonType),//��С
    TESTAU_ID_Form1002,//��������ԴID 
    0,//Tag
    0//StyleOption
  },//��Դ����ͷ���������
  {//���Ա�־
    1,//enabled
    1,//visibled
    0,//ctl3D
    1,//tabStop
    0,//readOnly
    0,//imeEnable
    0,//wordWrap
    0,//topLeftIsLock
    0,//check 
    0,//multiLine,(nouse here) 
    0,//autoSize,(nouse here)
    0,//modal,(Formʹ��) 
    0,//numeric,(nouse here)
    0,//autoShift,(nouse here)
    0,//dynamicSize,(nouse here)
    0,//underLine,(nouse here)
    0,//bIClose,(nouse here)
    0,//HasStatusBar,(nouse here)
    0,//bIAction,(nouse here)
    0,//bIMaximize,(nouse here)
    0,//ForceShowTitle,(nouse here)
    0,//graphical
    0,//sbmHasVertical,��ֱ������
    0,//sbmHasHorizontal��ˮƽ������
    0,//sbmAuto,�������Զ�����
    0,//hasImage
    0,//hasCheckBox
    1,//UseSYSDefColor
    0,//Smooth
    0,//ShowText
    1,//TransParent
    0//OwnerDraw
  },//���Ա�־����
  {{5, 288}, {107, 30}},//rect
  0x3,//backColor
  0x2,//boreColor
  0x4,//selectedBackColor
  0x5,//selectedForeColor
  0x6,//focusBackColor
  0x7,//focusForeColor
  (TUChar *)TESTAU_ENU_PlayEffectCaption,//Caption
  0,//charSet
  stdFont,//Font
  -1,//BitmapID
  -1,//SelectedBitmapID
  -1,//FocusBitmapID
  0,//Style
  4,//TabOrder
  0//TabOrderGroup
};//TESTAU_ENU_PlayEffect�������

//----------------------- Button TESTAU_ENU_PlayEffect���Զ��� End------------------------

//----------------------- Button TESTAU_ENU_UnLoadBtn���Զ��� Begin------------------------
/*"UnLoadEffect"*/
const TUChar TESTAU_ENU_UnLoadBtnCaption[]={0x0055,0x006E,0x004C,0x006F,0x0061,0x0064,0x0045,0x0066,0x0066,0x0065,0x0063,0x0074,0x0000};

const ResButtonType TESTAU_ENU_UnLoadBtn=//
{
  {//��Դ����ͷ������
    TESTAU_ID_Form1002_UnLoadBtn, //��ԴID�� 
    RES_CLASS_BUTTON,
    sizeof(ResButtonType),//��С
    TESTAU_ID_Form1002,//��������ԴID 
    0,//Tag
    0//StyleOption
  },//��Դ����ͷ���������
  {//���Ա�־
    1,//enabled
    1,//visibled
    0,//ctl3D
    1,//tabStop
    0,//readOnly
    0,//imeEnable
    0,//wordWrap
    0,//topLeftIsLock
    0,//check 
    0,//multiLine,(nouse here) 
    0,//autoSize,(nouse here)
    0,//modal,(Formʹ��) 
    0,//numeric,(nouse here)
    0,//autoShift,(nouse here)
    0,//dynamicSize,(nouse here)
    0,//underLine,(nouse here)
    0,//bIClose,(nouse here)
    0,//HasStatusBar,(nouse here)
    0,//bIAction,(nouse here)
    0,//bIMaximize,(nouse here)
    0,//ForceShowTitle,(nouse here)
    0,//graphical
    0,//sbmHasVertical,��ֱ������
    0,//sbmHasHorizontal��ˮƽ������
    0,//sbmAuto,�������Զ�����
    0,//hasImage
    0,//hasCheckBox
    1,//UseSYSDefColor
    0,//Smooth
    0,//ShowText
    1,//TransParent
    0//OwnerDraw
  },//���Ա�־����
  {{125, 250}, {120, 30}},//rect
  0x3,//backColor
  0x2,//boreColor
  0x4,//selectedBackColor
  0x5,//selectedForeColor
  0x6,//focusBackColor
  0x7,//focusForeColor
  (TUChar *)TESTAU_ENU_UnLoadBtnCaption,//Caption
  0,//charSet
  stdFont,//Font
  -1,//BitmapID
  -1,//SelectedBitmapID
  -1,//FocusBitmapID
  0,//Style
  5,//TabOrder
  0//TabOrderGroup
};//TESTAU_ENU_UnLoadBtn�������

//----------------------- Button TESTAU_ENU_UnLoadBtn���Զ��� End------------------------

//----------------------- Button TESTAU_ENU_PauseBack���Զ��� Begin------------------------
/*"Pause"*/
const TUChar TESTAU_ENU_PauseBackCaption[]={0x0050,0x0061,0x0075,0x0073,0x0065,0x0000};

const ResButtonType TESTAU_ENU_PauseBack=//
{
  {//��Դ����ͷ������
    TESTAU_ID_Form1002_PauseBack, //��ԴID�� 
    RES_CLASS_BUTTON,
    sizeof(ResButtonType),//��С
    TESTAU_ID_Form1002,//��������ԴID 
    0,//Tag
    0//StyleOption
  },//��Դ����ͷ���������
  {//���Ա�־
    1,//enabled
    1,//visibled
    0,//ctl3D
    1,//tabStop
    0,//readOnly
    0,//imeEnable
    0,//wordWrap
    0,//topLeftIsLock
    0,//check 
    0,//multiLine,(nouse here) 
    0,//autoSize,(nouse here)
    0,//modal,(Formʹ��) 
    0,//numeric,(nouse here)
    0,//autoShift,(nouse here)
    0,//dynamicSize,(nouse here)
    0,//underLine,(nouse here)
    0,//bIClose,(nouse here)
    0,//HasStatusBar,(nouse here)
    0,//bIAction,(nouse here)
    0,//bIMaximize,(nouse here)
    0,//ForceShowTitle,(nouse here)
    0,//graphical
    0,//sbmHasVertical,��ֱ������
    0,//sbmHasHorizontal��ˮƽ������
    0,//sbmAuto,�������Զ�����
    0,//hasImage
    0,//hasCheckBox
    1,//UseSYSDefColor
    0,//Smooth
    0,//ShowText
    1,//TransParent
    0//OwnerDraw
  },//���Ա�־����
  {{209, 60}, {100, 30}},//rect
  0x3,//backColor
  0x2,//boreColor
  0x4,//selectedBackColor
  0x5,//selectedForeColor
  0x6,//focusBackColor
  0x7,//focusForeColor
  (TUChar *)TESTAU_ENU_PauseBackCaption,//Caption
  0,//charSet
  stdFont,//Font
  -1,//BitmapID
  -1,//SelectedBitmapID
  -1,//FocusBitmapID
  0,//Style
  6,//TabOrder
  0//TabOrderGroup
};//TESTAU_ENU_PauseBack�������

//----------------------- Button TESTAU_ENU_PauseBack���Զ��� End------------------------

//----------------------- Button TESTAU_ENU_BackVolumeUp���Զ��� Begin------------------------
/*"BackVolumeUp"*/
const TUChar TESTAU_ENU_BackVolumeUpCaption[]={0x0042,0x0061,0x0063,0x006B,0x0056,0x006F,0x006C,0x0075,0x006D,0x0065,0x0055,0x0070,0x0000};

const ResButtonType TESTAU_ENU_BackVolumeUp=//
{
  {//��Դ����ͷ������
    TESTAU_ID_Form1002_BackVolumeUp, //��ԴID�� 
    RES_CLASS_BUTTON,
    sizeof(ResButtonType),//��С
    TESTAU_ID_Form1002,//��������ԴID 
    0,//Tag
    0//StyleOption
  },//��Դ����ͷ���������
  {//���Ա�־
    1,//enabled
    1,//visibled
    0,//ctl3D
    1,//tabStop
    0,//readOnly
    0,//imeEnable
    0,//wordWrap
    0,//topLeftIsLock
    0,//check 
    0,//multiLine,(nouse here) 
    0,//autoSize,(nouse here)
    0,//modal,(Formʹ��) 
    0,//numeric,(nouse here)
    0,//autoShift,(nouse here)
    0,//dynamicSize,(nouse here)
    0,//underLine,(nouse here)
    0,//bIClose,(nouse here)
    0,//HasStatusBar,(nouse here)
    0,//bIAction,(nouse here)
    0,//bIMaximize,(nouse here)
    0,//ForceShowTitle,(nouse here)
    0,//graphical
    0,//sbmHasVertical,��ֱ������
    0,//sbmHasHorizontal��ˮƽ������
    0,//sbmAuto,�������Զ�����
    0,//hasImage
    0,//hasCheckBox
    1,//UseSYSDefColor
    0,//Smooth
    0,//ShowText
    1,//TransParent
    0//OwnerDraw
  },//���Ա�־����
  {{5, 135}, {170, 40}},//rect
  0x3,//backColor
  0x2,//boreColor
  0x4,//selectedBackColor
  0x5,//selectedForeColor
  0x6,//focusBackColor
  0x7,//focusForeColor
  (TUChar *)TESTAU_ENU_BackVolumeUpCaption,//Caption
  0,//charSet
  stdFont,//Font
  -1,//BitmapID
  -1,//SelectedBitmapID
  -1,//FocusBitmapID
  0,//Style
  7,//TabOrder
  0//TabOrderGroup
};//TESTAU_ENU_BackVolumeUp�������

//----------------------- Button TESTAU_ENU_BackVolumeUp���Զ��� End------------------------

//----------------------- Button TESTAU_ENU_BackVolumeDown���Զ��� Begin------------------------
/*"BackVolumeDown"*/
const TUChar TESTAU_ENU_BackVolumeDownCaption[]={0x0042,0x0061,0x0063,0x006B,0x0056,0x006F,0x006C,0x0075,0x006D,0x0065,0x0044,0x006F,0x0077,0x006E,0x0000};

const ResButtonType TESTAU_ENU_BackVolumeDown=//
{
  {//��Դ����ͷ������
    TESTAU_ID_Form1002_BackVolumeDown, //��ԴID�� 
    RES_CLASS_BUTTON,
    sizeof(ResButtonType),//��С
    TESTAU_ID_Form1002,//��������ԴID 
    0,//Tag
    0//StyleOption
  },//��Դ����ͷ���������
  {//���Ա�־
    1,//enabled
    1,//visibled
    0,//ctl3D
    1,//tabStop
    0,//readOnly
    0,//imeEnable
    0,//wordWrap
    0,//topLeftIsLock
    0,//check 
    0,//multiLine,(nouse here) 
    0,//autoSize,(nouse here)
    0,//modal,(Formʹ��) 
    0,//numeric,(nouse here)
    0,//autoShift,(nouse here)
    0,//dynamicSize,(nouse here)
    0,//underLine,(nouse here)
    0,//bIClose,(nouse here)
    0,//HasStatusBar,(nouse here)
    0,//bIAction,(nouse here)
    0,//bIMaximize,(nouse here)
    0,//ForceShowTitle,(nouse here)
    0,//graphical
    0,//sbmHasVertical,��ֱ������
    0,//sbmHasHorizontal��ˮƽ������
    0,//sbmAuto,�������Զ�����
    0,//hasImage
    0,//hasCheckBox
    1,//UseSYSDefColor
    0,//Smooth
    0,//ShowText
    1,//TransParent
    0//OwnerDraw
  },//���Ա�־����
  {{5, 180}, {170, 40}},//rect
  0x3,//backColor
  0x2,//boreColor
  0x4,//selectedBackColor
  0x5,//selectedForeColor
  0x6,//focusBackColor
  0x7,//focusForeColor
  (TUChar *)TESTAU_ENU_BackVolumeDownCaption,//Caption
  0,//charSet
  stdFont,//Font
  -1,//BitmapID
  -1,//SelectedBitmapID
  -1,//FocusBitmapID
  0,//Style
  8,//TabOrder
  0//TabOrderGroup
};//TESTAU_ENU_BackVolumeDown�������

//----------------------- Button TESTAU_ENU_BackVolumeDown���Զ��� End------------------------

//----------------------- Button TESTAU_ENU_EffectVolumeUp���Զ��� Begin------------------------
/*"EffectVolumeUp"*/
const TUChar TESTAU_ENU_EffectVolumeUpCaption[]={0x0045,0x0066,0x0066,0x0065,0x0063,0x0074,0x0056,0x006F,0x006C,0x0075,0x006D,0x0065,0x0055,0x0070,0x0000};

const ResButtonType TESTAU_ENU_EffectVolumeUp=//
{
  {//��Դ����ͷ������
    TESTAU_ID_Form1002_EffectVolumeUp, //��ԴID�� 
    RES_CLASS_BUTTON,
    sizeof(ResButtonType),//��С
    TESTAU_ID_Form1002,//��������ԴID 
    0,//Tag
    0//StyleOption
  },//��Դ����ͷ���������
  {//���Ա�־
    1,//enabled
    1,//visibled
    0,//ctl3D
    1,//tabStop
    0,//readOnly
    0,//imeEnable
    0,//wordWrap
    0,//topLeftIsLock
    0,//check 
    0,//multiLine,(nouse here) 
    0,//autoSize,(nouse here)
    0,//modal,(Formʹ��) 
    0,//numeric,(nouse here)
    0,//autoShift,(nouse here)
    0,//dynamicSize,(nouse here)
    0,//underLine,(nouse here)
    0,//bIClose,(nouse here)
    0,//HasStatusBar,(nouse here)
    0,//bIAction,(nouse here)
    0,//bIMaximize,(nouse here)
    0,//ForceShowTitle,(nouse here)
    0,//graphical
    0,//sbmHasVertical,��ֱ������
    0,//sbmHasHorizontal��ˮƽ������
    0,//sbmAuto,�������Զ�����
    0,//hasImage
    0,//hasCheckBox
    1,//UseSYSDefColor
    0,//Smooth
    0,//ShowText
    1,//TransParent
    0//OwnerDraw
  },//���Ա�־����
  {{5, 330}, {170, 40}},//rect
  0x3,//backColor
  0x2,//boreColor
  0x4,//selectedBackColor
  0x5,//selectedForeColor
  0x6,//focusBackColor
  0x7,//focusForeColor
  (TUChar *)TESTAU_ENU_EffectVolumeUpCaption,//Caption
  0,//charSet
  stdFont,//Font
  -1,//BitmapID
  -1,//SelectedBitmapID
  -1,//FocusBitmapID
  0,//Style
  9,//TabOrder
  0//TabOrderGroup
};//TESTAU_ENU_EffectVolumeUp�������

//----------------------- Button TESTAU_ENU_EffectVolumeUp���Զ��� End------------------------

//----------------------- Button TESTAU_ENU_EffectVolumeDown���Զ��� Begin------------------------
/*"EffectVolumeDown"*/
const TUChar TESTAU_ENU_EffectVolumeDownCaption[]={0x0045,0x0066,0x0066,0x0065,0x0063,0x0074,0x0056,0x006F,0x006C,0x0075,0x006D,0x0065,0x0044,0x006F,0x0077,0x006E,0x0000};

const ResButtonType TESTAU_ENU_EffectVolumeDown=//
{
  {//��Դ����ͷ������
    TESTAU_ID_Form1002_EffectVolumeDown, //��ԴID�� 
    RES_CLASS_BUTTON,
    sizeof(ResButtonType),//��С
    TESTAU_ID_Form1002,//��������ԴID 
    0,//Tag
    0//StyleOption
  },//��Դ����ͷ���������
  {//���Ա�־
    1,//enabled
    1,//visibled
    0,//ctl3D
    1,//tabStop
    0,//readOnly
    0,//imeEnable
    0,//wordWrap
    0,//topLeftIsLock
    0,//check 
    0,//multiLine,(nouse here) 
    0,//autoSize,(nouse here)
    0,//modal,(Formʹ��) 
    0,//numeric,(nouse here)
    0,//autoShift,(nouse here)
    0,//dynamicSize,(nouse here)
    0,//underLine,(nouse here)
    0,//bIClose,(nouse here)
    0,//HasStatusBar,(nouse here)
    0,//bIAction,(nouse here)
    0,//bIMaximize,(nouse here)
    0,//ForceShowTitle,(nouse here)
    0,//graphical
    0,//sbmHasVertical,��ֱ������
    0,//sbmHasHorizontal��ˮƽ������
    0,//sbmAuto,�������Զ�����
    0,//hasImage
    0,//hasCheckBox
    1,//UseSYSDefColor
    0,//Smooth
    0,//ShowText
    1,//TransParent
    0//OwnerDraw
  },//���Ա�־����
  {{5, 380}, {170, 40}},//rect
  0x3,//backColor
  0x2,//boreColor
  0x4,//selectedBackColor
  0x5,//selectedForeColor
  0x6,//focusBackColor
  0x7,//focusForeColor
  (TUChar *)TESTAU_ENU_EffectVolumeDownCaption,//Caption
  0,//charSet
  stdFont,//Font
  -1,//BitmapID
  -1,//SelectedBitmapID
  -1,//FocusBitmapID
  0,//Style
  10,//TabOrder
  0//TabOrderGroup
};//TESTAU_ENU_EffectVolumeDown�������

//----------------------- Button TESTAU_ENU_EffectVolumeDown���Զ��� End------------------------
const ResCommonType * const TESTAU_ENU_Form1002_ControlList[10]=
{
  (ResCommonType *)&TESTAU_ENU_PlayBack
  ,(ResCommonType *)&TESTAU_ENU_StopBack
  ,(ResCommonType *)&TESTAU_ENU_LoadEffect
  ,(ResCommonType *)&TESTAU_ENU_PlayEffect
  ,(ResCommonType *)&TESTAU_ENU_UnLoadBtn
  ,(ResCommonType *)&TESTAU_ENU_PauseBack
  ,(ResCommonType *)&TESTAU_ENU_BackVolumeUp
  ,(ResCommonType *)&TESTAU_ENU_BackVolumeDown
  ,(ResCommonType *)&TESTAU_ENU_EffectVolumeUp
  ,(ResCommonType *)&TESTAU_ENU_EffectVolumeDown
};

const ResourceLangRegisterEntry TESTAU_ENU_Resource[] = 
{
  {kProjectRscType,0,(void*)&TESTAU_ENU_project,sizeof(TESTAU_ENU_project)}   
  ,{kWindowRscType,TESTAU_ID_Form1002,(void*)&TESTAU_ENU_Form1002,sizeof(TESTAU_ENU_Form1002)}   
};

const ResourceLangRegisterEntry2  TESTAU_ENU_ResourceEntry = 
{
  tgresource_tag,
  11,//res version
  0,//subVersionValue
  0,//reserved1
  0,//reserved2
  TESTAU_ENU_Resource
};

//��Դ����
#define TG_RESOURCE_DEFINE   \
{SYS_LANGUAGE_CHS,sizeof( TESTAU_CHS_Resource )/ sizeof(ResourceLangRegisterEntry), &TESTAU_CHS_ResourceEntry},   \
{SYS_LANGUAGE_ENU,sizeof( TESTAU_ENU_Resource )/ sizeof(ResourceLangRegisterEntry), &TESTAU_ENU_ResourceEntry},   
