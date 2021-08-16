#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QPainter>
#include "DPlatform.h"
#include "DVideoListManagement.h"
#include "DVideoList.h"
#include "VideoFrame.h"
#include <QDateTime>
#include <QMessageBox>
#include <windows.h>
#include <winbase.h>
#include <winnls.h>
#include <winioctl.h>
#include <ioapiset.h>
#include <iostream>
#include <stdio.h>
#include "Dbt.h"

#ifdef _MSC_VER
#		if _MSC_VER >= 1600
#			pragma execution_character_set("utf-8")
#		endif
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
	m_nTimerId(-1),
    m_eCurrentType(DPublicDef::VideoListType_All)
{
    ui->setupUi(this);

	m_pix = QPixmap(":/icon/resource/background.png");
	m_pixList = QPixmap(":/icon/resource/list.png");

    connect(videoManagement(), &DVideoListManagement::signalVideoListAdd, this, &MainWindow::onVideoListAdd);
    connect(videoManagement(), &DVideoListManagement::signalVideoListDel, this, &MainWindow::onVideoListDel);

	ui->logo->installEventFilter(this);

	m_nTimerId = this->startTimer(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.drawPixmap(this->rect(), m_pix);
}

void MainWindow::timerEvent(QTimerEvent *event)
{
	if (m_nTimerId != -1)
	{
		killTimer(m_nTimerId);
		m_nTimerId = -1;
	}

	if (dateTimeCheck())
	{
		platform()->InitVideoList();
        findUSBDisk();
	}
	else
	{
		qApp->quit();
	}
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
	if (event->type() == QEvent::Paint)
	{
		if (watched == ui->logo)
		{
			QPainter painter(ui->logo);

			QPixmap pixList = QPixmap(":/icon/resource/logo.png");
			/*pixList = pixList.scaled(ui->logo->size(), Qt::KeepAspectRatio);*/
			painter.drawPixmap(ui->logo->rect(), pixList);
		}
	}

	return QMainWindow::eventFilter(watched, event);
}

char FirstDriveFromMask(ULONG unitmask)
{
	char i;

	for (i = 0; i < 26; ++i)
	{
		if (unitmask & 0x1)
			break;
		unitmask = unitmask >> 1;
	}
	return (i + 'A');
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
	MSG* msg = reinterpret_cast<MSG*>(message);
	int msgType = msg->message;
	if (msgType == WM_DEVICECHANGE)
	{
		qDebug() << "Recv Event ";
		PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)msg->lParam;
		switch (msg->wParam)
		{
		case DBT_DEVNODES_CHANGED:
		{
			findUSBDisk();
			break;
		}
		default:
			break;
		}
	}
	return QWidget::nativeEvent(eventType, message, result);
}

void MainWindow::onVideoListAdd(DVideoList* info)
{
    VideoFrame *frame = new VideoFrame(this);
    frame->connectVideoList(info);

    connect(frame, &VideoFrame::signalExpand, this, &MainWindow::onExpand);
    
    int column = m_listFrame.size() / 3;
    int row = m_listFrame.size() % 3;

    ui->gridLayout->addWidget(frame, column, row);

    m_listFrame.insert(frame->m_eListType, frame);
}

void MainWindow::onVideoListDel(DVideoList* info)
{

}

void MainWindow::onExpand(DPublicDef::VideoListType eType)
{
    if (DPublicDef::VideoListType_All == m_eCurrentType)
    {
        VideoFrame *frame = dynamic_cast<VideoFrame*>(sender());
        if (!frame)
        {
            return;
        }
        m_eCurrentType = eType;

		for (QMap<DPublicDef::VideoListType, VideoFrame*>::iterator iter = m_listFrame.begin(); iter != m_listFrame.end(); ++iter)
		{
			if (iter.key() != m_eCurrentType)
			{
				iter.value()->setVisible(false);
			}
		}

    }
    else
    {
        m_eCurrentType = DPublicDef::VideoListType_All;

		for (QMap<DPublicDef::VideoListType, VideoFrame*>::iterator iter = m_listFrame.begin(); iter != m_listFrame.end(); ++iter)
		{
			iter.value()->setVisible(true);
		}
    }
}

void MainWindow::initVideoList()
{
	
}

bool MainWindow::dateTimeCheck()
{
	return true;

	qint64 endTime = QDateTime::fromString(QString("2021-07-01 12:00:00"), "yyyy-MM-dd hh:mm:ss").toMSecsSinceEpoch();
	qint64 beginTime = QDateTime::currentDateTime().toMSecsSinceEpoch();

	if (beginTime > endTime)
	{
		QMessageBox::warning(this, "错误","试用期已过,请购买!");
		return false;
	}

	return true;
}

#define MAX_PATH 1024
bool isUsb(std::wstring dis_name) 
{
    HANDLE hDevice = INVALID_HANDLE_VALUE;
    BOOL bResult = FALSE;
    DWORD junk = 0;
    STORAGE_DEVICE_DESCRIPTOR storage_dev_Des = {0};
    storage_dev_Des.BusType = STORAGE_BUS_TYPE::BusTypeUnknown;
    
    STORAGE_PROPERTY_QUERY query;
    memset(&query, 0, sizeof(query));

    //
    wchar_t buff[MAX_PATH] = {0};
    wsprintf(buff, L"\\\\.\\%s", dis_name.c_str());

    std::wstring device_name = buff;

    hDevice = CreateFileW(device_name.c_str(), 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
    if (hDevice == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    bResult = DeviceIoControl(hDevice, IOCTL_STORAGE_QUERY_PROPERTY, &query, sizeof(query), &storage_dev_Des, sizeof(storage_dev_Des), &junk, NULL);
    CloseHandle(hDevice);

    if (!bResult)
    {
        return false;
    }

    if (storage_dev_Des.BusType == BusTypeUsb)
    {
        return true;
    }

    return false;
}


void MainWindow::findUSBDisk()
{
	bool bFind = false;
    char diskPath[5] = { 0 };
    for (int i = 0; i < 26; i++)     //假定最多有25个磁盘从A开始计数
    {
        sprintf(diskPath, "%c", 'A' + i);
        strcat(diskPath, ":");

        if (isUsb((QString(diskPath).toStdWString())))
        {
            platform()->CheckUsbDiskFile(QString(diskPath));
			bFind = true;
			break;
        }
    }

	if (!bFind)
	{
		platform()->RemoveUSBFile();
	}

}
