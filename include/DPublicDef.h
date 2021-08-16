#pragma once
#include <QObject>

#ifdef _MSC_VER
#		if _MSC_VER >= 1600
#			pragma execution_character_set("utf-8")
#		endif
#endif

class DPublicDef
{
    Q_GADGET
public:
    enum VideoListType
    {
        VideoListType_All = -1,     // ����
        VideoListType_Song = 0,     // ����
        VideoListType_Dance,        // �赸
		VideoListType_Fitness,		// ����
		VideoListType_Quyi,			// ����
		VideoListType_USB,			// USB��Ƶ
		VideoListType_Online,		// ������Ƶ
    };
    Q_ENUM(VideoListType);

	enum VideoListItemType
	{
		VideoListType_UnKonw = -1,
		VideoListType_Tencent = 0,     // ��Ѷ��Ƶ
		VideoListType_AQY,			   // ������
		VideoListType_YouKu,		   // �ſ�
		VideoListType_Baidu,		   // �ٶ���Ƶ
		VideoListType_Mangguo,		   // â��
		VideoListType_BliBli,		   // ��������
	};
	Q_ENUM(VideoListItemType);

};

// �ļ���
#define VideFileName  "videoList.txt"
// �汾��Ϣ
#define Project_Version "version"
//  ��Ƶ�б�
#define VideoList "videoList"
// ��Ƶ����
#define VideoType "videoType"
// ��Ƶ����
#define VideoURL "videoUrl"
// ��Ƶ����
#define VideoName "VideoName"



//========================= URL ======================

#define VIDEO_HOME               QString("%1api/api/vdieo/home")
#define VIDEO_URL                QString("%1api/api/vdieo/type/list")
#define VIDEO_PATH               QString("%1assets/")
