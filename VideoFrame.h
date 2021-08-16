#ifndef VIDEOFRAME_H
#define VIDEOFRAME_H

#include <QFrame>
#include "DVideoList.h"

namespace Ui {
class VideoFrame;
}

class VideoFrame : public QFrame
{
    Q_OBJECT

public:
    explicit VideoFrame(QWidget *parent = nullptr);
    ~VideoFrame();

    void connectVideoList(DVideoList *list);
	void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *object, QEvent *e) override;
	void setExpand(bool bExpand);

protected slots:
    void onVideoAdd(DPublicDef::VideoListType eType, DVideoInformation* info);
    void onVideoDel(DPublicDef::VideoListType eType, DVideoInformation* info);

signals:
    void signalExpand(DPublicDef::VideoListType eType);

public:
    QString                     m_strListId;
    DPublicDef::VideoListType   m_eListType;
	bool						m_bExpand;

private:
    Ui::VideoFrame              *ui;
};

#endif // VIDEOFRAME_H
