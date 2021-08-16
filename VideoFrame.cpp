#include "VideoFrame.h"
#include "ui_VideoFrame.h"
#include <QPainter>
#include "DVideoListManagement.h"
#include "DProgramItemFrame.h"

#ifdef _MSC_VER
#		if _MSC_VER >= 1600
#			pragma execution_character_set("utf-8")
#		endif
#endif

VideoFrame::VideoFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::VideoFrame),
	m_bExpand(false)
{
    ui->setupUi(this);
    ui->label_more->installEventFilter(this);
	ui->frame->installEventFilter(this);

	connect(ui->toolButton, &QToolButton::clicked, this, [this]
	{
		setExpand(!m_bExpand);
		emit signalExpand(m_eListType);
	});
}

VideoFrame::~VideoFrame()
{
    delete ui;
}

void VideoFrame::connectVideoList(DVideoList *list)
{
    if (!list)
    {
        return;
    }

	if (list->m_strName.size() == 2)
	{
		ui->toolButton_logo1->setText(list->m_strName.at(0));
		ui->toolButton_logo2->setText(list->m_strName.at(1));
	}

    this->m_strListId = list->m_strID;
    m_eListType = list->m_eType;

    connect(list, &DVideoList::signalVideoAdd, this, &VideoFrame::onVideoAdd);
    connect(list, &DVideoList::signalVideoDel, this, &VideoFrame::onVideoDel);
}

void VideoFrame::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	QPixmap pixList = QPixmap(":/icon/resource/list.png");
	if (m_bExpand)
	{
		pixList = QPixmap(":/icon/resource/bigList.png");
	}
	pixList = pixList.scaled(this->rect().size(), Qt::KeepAspectRatio);

	painter.drawPixmap(this->rect(), pixList);
}

bool VideoFrame::eventFilter(QObject *object, QEvent *e)
{
    if (e->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(e);
        if (mouseEvent && mouseEvent->button() == Qt::LeftButton)
        {
            if (object == ui->label_more)
            {
				setExpand(!m_bExpand);
                emit signalExpand(m_eListType);
            }
        }
    }
	else if (e->type() == QEvent::Paint)
	{
		if (object == ui->frame)
		{
			QPainter painter(ui->frame);
			QPixmap pixList = QPixmap(":/resource/group.png");
			painter.drawPixmap(ui->frame->rect(), pixList);
		}
	}
    return QFrame::eventFilter(object, e);
}

void VideoFrame::setExpand(bool bExpand)
{
	if (bExpand != m_bExpand)
	{
		m_bExpand = bExpand;
		if (bExpand)
		{
			ui->verticalLayout_2->setContentsMargins(9, 47, 30, 9);
			ui->label_more->setText("返回");
		}
		else
		{
			ui->verticalLayout_2->setContentsMargins(9, 9, 9, 9);
			ui->label_more->setText("查看更多");
		}
	}
}

void VideoFrame::onVideoAdd(DPublicDef::VideoListType eType, DVideoInformation* info)
{
    DProgramItemFrame *frame = new DProgramItemFrame(info->m_strID);
    frame->connectVideoInfo(info);

    ui->listWidget->AddItem(frame);
}

void VideoFrame::onVideoDel(DPublicDef::VideoListType eType, DVideoInformation* info)
{
	ui->listWidget->RemoveItem(info->m_strID);
}
