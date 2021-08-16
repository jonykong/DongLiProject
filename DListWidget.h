#pragma once

#include <QListWidget>
#include <QListWidgetItem>
#include <QMouseEvent>
#include <QStyledItemDelegate>

class DListWidgetDelegate : public QStyledItemDelegate
{
public:
	DListWidgetDelegate(QObject *parent = nullptr);
    ~DListWidgetDelegate();

public:
    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

class DColorBar : public QWidget
{
public:
    explicit DColorBar(QWidget *parent):
        QWidget(parent)
    {
        this->setStyleSheet("background-color: rgb(255, 255, 255);");
    }
};

class DBaseWidget;
class DListWidget : public QListWidget
{
    Q_OBJECT

public:
    explicit DListWidget(QWidget *parent = nullptr);
    ~DListWidget();

public:
    QListWidgetItem* GetItemByWidget(const QWidget *widget) const;
    QListWidgetItem* GetItemByID(const QString &strID) const;
    DBaseWidget* GetBaseWidget(const QString &ID);
    QList<QString> GetSelectedIDs() const;
    void showInsertColorBar(int index);
    void hideInsertColorBar();
    int getIndexOfItem(QListWidgetItem* item);
    int getColorBarIndex() const;

public:
    void SetSizeHint(const QSize &size);
    void AddItem(DBaseWidget* widget);
    void AddItem(DBaseWidget* widget, int nIndex);
    void RemoveItem(const QString &strID);
    void RemoveItemNoDestroy(const QString &strID);

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void resizeEvent(QResizeEvent *e) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *e) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event);

protected slots:
    void onItemSelectionChanged();

signals:
    void sinalSeletedMode(bool bSingle);
    void signalNotifyKeyPress(Qt::KeyboardModifiers modifiers, int nKey);
    void signalSelected();
    void signalAddMedia();
    void signalClearSelected();

private:
    // 更新选中
    void updateSelected();
    // 获取选中下标
    int getSelectIndex();
    // 获取播放下标
    int getPlayingIndex();
    // 获取向上/向下选中的下标
    int getUpDownSelectIndex(int key);

private:
    QSize									m_size;
    QList<DBaseWidget*>					m_widgets;
    volatile bool							m_bMultiSelection;
    DColorBar *								m_colotBar;
    volatile int							mColorBarIndex;
};
