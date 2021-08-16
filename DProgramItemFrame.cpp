#include "DProgramItemFrame.h"
#include "ui_DProgramItemFrame.h"
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>
#include <QTime>
#include <QMenu>
#include "PlayDialog.h"
#include <QDesktopServices>
#include "DPlatform.h"
#include "player.h"

DProgramItemFrame::DProgramItemFrame(const QString &programId, QWidget *parent)
    : DBaseWidget(parent)
    , ui(new Ui::DProgramItemFrame)
{
    ui->setupUi(this);
	ui->widget->installEventFilter(this);
	m_pix = QPixmap(":/icon/resource/ItemBackground.png");
}

DProgramItemFrame::~DProgramItemFrame()
{
    delete ui;
}

void DProgramItemFrame::connectVideoInfo(DVideoInformation *info)
{
    if (!info)
    {
        return;
    }
    m_info = info;

    ui->label->setText(info->m_strName);

	switch (info->m_eItemType)
	{
	case DPublicDef::VideoListType_Tencent:
		m_pix = QPixmap(":/icon/resource/tengxun.png");
		break;
	case DPublicDef::VideoListType_AQY:
		m_pix = QPixmap(":/icon/resource/aiqiyi.png");
		break;
	case DPublicDef::VideoListType_YouKu:
		m_pix = QPixmap(":/icon/resource/youku.png");
		break;
	case DPublicDef::VideoListType_Baidu:
		m_pix = QPixmap(":/icon/resource/baidu.png");
		break;
	case DPublicDef::VideoListType_Mangguo:
		m_pix = QPixmap(":/icon/resource/mangguo.png");
		break;
	case DPublicDef::VideoListType_BliBli:
		m_pix = QPixmap(":/icon/resource/blibli.png");
		break;
	default:
		break;
	}
}

QString DProgramItemFrame::getID() const
{
    return m_info->m_strID;
}

void DProgramItemFrame::setSelected(const bool selected)
{
}

bool DProgramItemFrame::isSelected() const
{
    return m_bSelected;
}

void DProgramItemFrame::doRightButtonClicked()
{
    QMenu menu;
    menu.exec(QCursor::pos());
}

bool DProgramItemFrame::doKeyPressEvent(int nKey)
{
    return false;
}

void DProgramItemFrame::doSelected()
{
    setSelected(true);
}

bool DProgramItemFrame::isPlaying()
{
    return false;
}

bool DProgramItemFrame::eventFilter(QObject *watched, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::Leave:
    {
        return true;
    }
    case QEvent::Enter:
    {
        return true;
    }
    case QEvent::Paint:
    {
		if (watched == ui->widget)
		{
			QPainter painter(ui->widget);
			painter.drawPixmap(ui->widget->rect(), m_pix);
		}
        break;
    }
    case QEvent::MouseButtonPress:
    {
		if (m_info->m_eType != DPublicDef::VideoListType_USB)
		{
			QString URL = QString("%1play?meida=%2&senderId=%3&receiverId=%4").arg(platform()->getURL()).arg(m_info->m_strID).arg(platform()->getSenderId()).arg(platform()->getReceiverId());
			QDesktopServices::openUrl(QUrl(URL));
		}
		else
		{
			Player * player = platform()->getPlayer();
			if (player)
			{
				if (!player->isVisible())
				{
					player->show();
					player->resize(1080, 577);
				}

				QString strUrl = QString("file:///%1").arg(m_info->m_strVideoFilePath);
				player->addToPlay(QUrl(strUrl));
			}
		}
        break;
    }
    case QEvent::MouseButtonRelease:
    {
        break;
    }
    case QEvent::MouseButtonDblClick:
    {
        break;
    }
    case QEvent::MouseMove:
    {
        break;
    }
    default:
        break;
    }
    return QFrame::eventFilter(watched,event);
}

void DProgramItemFrame::paintEvent(QPaintEvent *event)
{
// 	QPen pen;
// 	pen.setBrush(QBrush(Qt::black));//设置笔刷，你可以不用设置
// 	QVector<qreal> dashes;
// 
// 	qreal space = 3;
// 
// 	dashes << 5 << space << 5 << space;
// 
// 	pen.setDashPattern(dashes);
// 
// 	pen.setWidth(1);
// 
//     QPainter p(this);
//     p.setPen(pen);
// 
// 	QRect rect = ui->widget->rect();
// 
// 	QPoint topLeft(0, 0);
// 	QPoint topRight(this->width() - 1, 0);
// 	QPoint bottomLeft(0, rect.height() + 1);
// 	QPoint bottomRight(this->width() - 1, rect.height() + 1);
// 
// 	p.drawLine(topLeft, topRight);
// 	p.drawLine(topRight, bottomRight);
// 	p.drawLine(bottomRight, bottomLeft);
// 	p.drawLine(bottomLeft, topLeft);
}

void DProgramItemFrame::dragEnterEvent(QDragEnterEvent *event)
{

}
