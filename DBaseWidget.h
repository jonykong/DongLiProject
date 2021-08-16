#pragma once

#include <QFrame>

#define PLAY_BACKGROUND  "#FF8000"
#define PREVIEW_BACKGROUND "#7B9DFF"
#define SELECTED_BACKGROUND "#9A9A9A"
#define HOVER_BACKGROUND "#76B4B4"
#define NORMAL_BACKGROUND "#1C1C1C"

class DBaseWidget : public QFrame
{
	Q_OBJECT
public:
    DBaseWidget(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    virtual ~DBaseWidget();

public:
	// ��ҪID�������ǽڵ�ID����ĿID��
	virtual QString getID() const = 0;
	// ����Widgetѡ��
	virtual void setSelected(const bool selected) = 0;
	// doSelected ���ܴ�������
	virtual void doSelected() = 0;
	// �ڵ��Ƿ�Ϊѡ��״̬
	virtual bool isSelected() const = 0;
	// �����ʼ�����
	virtual void doRightButtonClicked() = 0;
	// ����ڵ㰴��
	virtual bool doKeyPressEvent(int nKey) {return false;}
	// �ڵ��Ƿ����ڲ���
	virtual bool isPlaying() { return false; };
	// �ڵ��Ƿ���PPT
	virtual bool isPPTProgram() { return false; }

signals:
	void doDropEvent();
};
