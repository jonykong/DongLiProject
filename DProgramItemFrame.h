#ifndef HIPROGRAMITEMFRAME_H
#define HIPROGRAMITEMFRAME_H

#include <QFrame>
#include "DBaseWidget.h"
#include "DVideoInformation.h"

namespace Ui 
{
class DProgramItemFrame;
}

class QPixmap;
class DProgramItemFrame : public DBaseWidget
{
    Q_OBJECT

public:
    explicit DProgramItemFrame(const QString &programId, QWidget *parent = nullptr);
    ~DProgramItemFrame();

    void connectVideoInfo(DVideoInformation *info);

public:
    virtual QString getID() const override;
    virtual void setSelected(const bool selected) override;
    virtual bool isSelected() const;
    virtual void doRightButtonClicked() override;
    // 处理节点时间
    virtual bool doKeyPressEvent(int nKey) override;
    // 选中 播放
    virtual void doSelected() override;
    // 节点是否正在播放
    virtual bool isPlaying() ;

protected:
    virtual bool eventFilter(QObject *watched, QEvent *event) override;
    void paintEvent(QPaintEvent *event);

protected:
    virtual void dragEnterEvent(QDragEnterEvent *event) override;

private:
    Ui::DProgramItemFrame					*ui;
    QPixmap									 m_pix;
    DVideoInformation                       *m_info;

    volatile bool							 m_bSelected;			// 选中状态
    volatile bool							 m_bHover;				// 悬浮状态
    volatile bool							 m_bPlay;				// 播放状态
};

#endif
