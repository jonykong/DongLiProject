#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DPublicDef.h"
#include <QMap>

namespace Ui {
class MainWindow;
}

class DVideoList;
class VideoFrame;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

	void paintEvent(QPaintEvent *event);
	void timerEvent(QTimerEvent *event);

protected:
	bool eventFilter(QObject *watched, QEvent *event);
	bool nativeEvent(const QByteArray &eventType, void *message, long *result);

protected slots:
    void onVideoListAdd(DVideoList* info);
    void onVideoListDel(DVideoList* info);
    void onExpand(DPublicDef::VideoListType eType);

private:
	void initVideoList();
	bool dateTimeCheck();
    void findUSBDisk();

private:
    Ui::MainWindow *									  ui;
    QPixmap												  m_pix;
    int													  m_nTimerId;
	QPixmap												  m_pixList;

    QMap<DPublicDef::VideoListType, VideoFrame*>          m_listFrame;
    DPublicDef::VideoListType							  m_eCurrentType;
};

#endif // MAINWINDOW_H
