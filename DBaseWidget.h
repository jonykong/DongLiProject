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
	// 重要ID、可以是节点ID、节目ID等
	virtual QString getID() const = 0;
	// 设置Widget选中
	virtual void setSelected(const bool selected) = 0;
	// doSelected 可能触及播放
	virtual void doSelected() = 0;
	// 节点是否为选中状态
	virtual bool isSelected() const = 0;
	// 处理邮件弹框
	virtual void doRightButtonClicked() = 0;
	// 处理节点按键
	virtual bool doKeyPressEvent(int nKey) {return false;}
	// 节点是否正在播放
	virtual bool isPlaying() { return false; };
	// 节点是否有PPT
	virtual bool isPPTProgram() { return false; }

signals:
	void doDropEvent();
};
