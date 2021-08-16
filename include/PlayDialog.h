#ifndef PLAYDIALOG_H
#define PLAYDIALOG_H

#include <QDialog>
#include <QPaintEvent>
#include <QMediaPlayer>

namespace Ui {
class PlayDialog;
}

class PlayDialog : public QDialog
{
    Q_OBJECT
public:
	static PlayDialog* instance();

	void play(const QString &strFile);

protected:
    explicit PlayDialog(QWidget *parent = nullptr);
    ~PlayDialog();

private:
    Ui::PlayDialog			   *ui;
	QPixmap						m_pix;
	QMediaPlayer*				m_pMediaPlayer;
};


inline PlayDialog* playDialog()
{
	return PlayDialog::instance();
}

#endif // PLAYDIALOG_H
