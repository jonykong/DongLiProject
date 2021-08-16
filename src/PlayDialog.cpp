#include "PlayDialog.h"
#include "ui_PlayDialog.h"
#include <QPainter>
#include <QFileDialog>

PlayDialog* PlayDialog::instance()
{
	static PlayDialog m_pInstance;
	return &m_pInstance;
}

void PlayDialog::play(const QString &strFile)
{
	QString strFiles = QFileDialog::getOpenFileName(this, "选择视频文件", "", "*.mp4");

	QFile file(strFiles);
	if (!file.exists())
	{
		return;
	}
	m_pMediaPlayer->setMedia(QUrl::fromLocalFile(strFiles));
	m_pMediaPlayer->setVolume(100);
	//m_pMediaPlayer->play();

	this->exec();
}

PlayDialog::PlayDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayDialog)
{
    ui->setupUi(this);
	m_pMediaPlayer = new QMediaPlayer();
	m_pMediaPlayer->setVideoOutput(ui->widget);

	connect(ui->toolButton_start, &QToolButton::clicked, this, [this]
	{
		if (m_pMediaPlayer->state() != QMediaPlayer::PlayingState)
		{
			m_pMediaPlayer->play();
		}
		else
		{
			m_pMediaPlayer->pause();
		}
	});
	connect(ui->toolButton__stop, &QToolButton::clicked, this, [this]
	{
		m_pMediaPlayer->stop();
	});
}

PlayDialog::~PlayDialog()
{
	delete ui;
}
