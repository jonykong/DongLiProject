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
        VideoListType_All = -1,     // 歌曲
        VideoListType_Song = 0,     // 歌曲
        VideoListType_Dance,        // 舞蹈
		VideoListType_Fitness,		// 健身
		VideoListType_Quyi,			// 曲艺
		VideoListType_USB,			// USB视频
		VideoListType_Online,		// 网络视频
    };
    Q_ENUM(VideoListType);

	enum VideoListItemType
	{
		VideoListType_UnKonw = -1,
		VideoListType_Tencent = 0,     // 腾讯视频
		VideoListType_AQY,			   // 爱奇艺
		VideoListType_YouKu,		   // 优酷
		VideoListType_Baidu,		   // 百度视频
		VideoListType_Mangguo,		   // 芒果
		VideoListType_BliBli,		   // 哔哩哔哩
	};
	Q_ENUM(VideoListItemType);

};

// 文件名
#define VideFileName  "videoList.txt"
// 版本信息
#define Project_Version "version"
//  视频列表
#define VideoList "videoList"
// 视频类型
#define VideoType "videoType"
// 视频链接
#define VideoURL "videoUrl"
// 视频名称
#define VideoName "VideoName"



//========================= URL ======================

#define VIDEO_HOME               QString("%1api/api/vdieo/home")
#define VIDEO_URL                QString("%1api/api/vdieo/type/list")
#define VIDEO_PATH               QString("%1assets/")
