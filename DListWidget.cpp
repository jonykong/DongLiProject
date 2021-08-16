#include "DListWidget.h"
#include "DBaseWidget.h"
#include <QScrollBar>

#define  ITEM_WIDTH		144
#define  ITEM_HEIGHT	109

DListWidget::DListWidget(QWidget *parent)
	: QListWidget(parent)
{
	this->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
	this->setViewMode(QListView::IconMode);
	this->setFlow(QListWidget::LeftToRight);
	this->setMovement(QListView::Snap);
	this->setLayoutMode(QListView::SinglePass);
	this->setWrapping(true);
	this->setSpacing(5);
	this->setGridSize(QSize(ITEM_WIDTH + 5, ITEM_HEIGHT + 15));
	m_colotBar = nullptr;
	mColorBarIndex = -1;
	connect(this, &QListWidget::itemSelectionChanged, this, &DListWidget::onItemSelectionChanged);

	this->setItemDelegate(new DListWidgetDelegate(this));

	this->verticalScrollBar()->setVisible(false);

    m_size = QSize(ITEM_WIDTH, ITEM_HEIGHT);

}

DListWidget::~DListWidget()
{

}

QListWidgetItem* DListWidget::GetItemByWidget(const QWidget *widget) const
{
	if (nullptr == widget)
	{
		return nullptr;
	}
	for (int var = 0; var < this->count(); ++var)
	{
		QListWidgetItem *pItem = item(var);
		if (pItem)
		{
			if (widget == this->itemWidget(pItem))
			{
				return pItem;
			}
		}
	}
	return nullptr;
}

QListWidgetItem* DListWidget::GetItemByID(const QString &strID) const
{
	for (int var = 0; var < this->count(); ++var)
	{
		QListWidgetItem *pItem = item(var);
		if (pItem)
		{
			DBaseWidget *widget = dynamic_cast<DBaseWidget*>(itemWidget(pItem));
			if (widget && widget->getID() == strID)
			{
				return pItem;
			}
		}
	}
	return nullptr;
}

DBaseWidget* DListWidget::GetBaseWidget(const QString &ID)
{
	for each (DBaseWidget* var in m_widgets)
	{
		if (var->getID() == ID)
		{
			return var;
		}
	}
	return nullptr;
}


QList<QString> DListWidget::GetSelectedIDs() const
{
	QList<QString> ids;
	for each (DBaseWidget* var in m_widgets)
	{
		if (var->isSelected())
		{
			ids.push_back(var->getID());
		}
	}
	return ids;
}

void DListWidget::showInsertColorBar(int index)
{
	if (mColorBarIndex == index) return;
	if (m_colotBar)
	{
		QListWidgetItem *citem = this->GetItemByWidget(m_colotBar);
		if (citem)
		{
			this->removeItemWidget(citem);
			delete citem;
			citem = nullptr;
			delete m_colotBar;
			m_colotBar = nullptr;
		}
	}
	if (!m_colotBar)
	{
		m_colotBar = new DColorBar(nullptr);
		QListWidgetItem *item = new QListWidgetItem();
		item->setSizeHint(QSize(2, m_size.height()));
		this->insertItem(index, item);
		this->setItemWidget(item, m_colotBar);
		mColorBarIndex = index;
	}
}

void DListWidget::hideInsertColorBar()
{
	if (m_colotBar)
	{
		QListWidgetItem *citem = this->GetItemByWidget(m_colotBar);
		if (citem)
		{
			this->removeItemWidget(citem);
			delete citem;
			citem = nullptr;
			delete m_colotBar;
			m_colotBar = nullptr;
		}
	}
}

int DListWidget::getIndexOfItem(QListWidgetItem* item)
{
	if (item)
	{
		return m_widgets.indexOf((DBaseWidget*)this->itemWidget(item), 0);
	}
	return -1;
}

int DListWidget::getColorBarIndex() const
{
	int nIndex = mColorBarIndex;

	if (nIndex < 0)
	{
		return 0;
	}

	bool bLess = true;

	for (int i = mColorBarIndex; i < m_widgets.count(); ++i)
	{
		if (m_widgets[i]->isSelected())
		{
			bLess = false;
			break;
		}
	}

	if (bLess)
	{
		--nIndex;
	}

	return nIndex;
}

void DListWidget::SetSizeHint(const QSize &size)
{
	if (size == m_size)
	{
		return;
	}

	m_size = size;

	for (int var = 0; var < this->count(); ++var)
	{
		QListWidgetItem *pItem = item(var);
		if (pItem)
		{
			pItem->setSizeHint(size);
		}
	}
	// 动态移动
	this->doItemsLayout();
}

void DListWidget::AddItem(DBaseWidget* widget)
{
	QListWidgetItem *item = new QListWidgetItem();

	this->addItem(item);
	item->setSizeHint(m_size);

	this->setItemWidget(item, widget);

	this->doItemsLayout();

	m_widgets.append(widget);
}

void DListWidget::AddItem(DBaseWidget* widget, int nIndex)
{
	if (nIndex < 0)
	{
		nIndex = 0;
	}
	else if (nIndex > m_widgets.size())
	{
		nIndex = m_widgets.size();
	}

	QListWidgetItem *item = new QListWidgetItem();

	this->insertItem(nIndex, item);
	item->setSizeHint(m_size);

	this->setItemWidget(item, widget);

	this->doItemsLayout();

	m_widgets.insert(nIndex, widget);
}

void DListWidget::RemoveItem(const QString &strID)
{
	QListWidgetItem *pItem = GetItemByID(strID);
	if (pItem)
	{
		DBaseWidget *widget = dynamic_cast<DBaseWidget*>(this->itemWidget(pItem));
		if (widget)
		{
			m_widgets.removeOne(widget);
			delete widget;
			widget = nullptr;
		}
		this->removeItemWidget(pItem);
		delete pItem;
		pItem = nullptr;
	}
	doItemsLayout();
}

void DListWidget::RemoveItemNoDestroy(const QString &strID)
{
	QListWidgetItem *pItem = GetItemByID(strID);
	if (pItem)
	{
		DBaseWidget *widget = dynamic_cast<DBaseWidget*>(this->itemWidget(pItem));
		if (widget)
		{
			m_widgets.removeOne(widget);
		}
		this->removeItemWidget(pItem);
		delete pItem;
		pItem = nullptr;
	}
	doItemsLayout();
}

void DListWidget::mousePressEvent(QMouseEvent *event)
{
	emit signalSelected();

	if (event->button() == Qt::RightButton)
	{
		QListWidgetItem *pItem = this->itemAt(event->pos());
		if (pItem)
		{
			if (!pItem->isSelected())
			{
				this->clearSelection();
				pItem->setSelected(true);
			}
			DBaseWidget *widget = dynamic_cast<DBaseWidget*>(itemWidget(pItem));
			if (widget)
			{
				widget->doRightButtonClicked();
			}
		}
		else
		{
			this->clearSelection();
			emit signalClearSelected();
		}
	}
	else if (event->button() == Qt::LeftButton)
	{
		QListWidgetItem *pItem = this->itemAt(event->pos());
		if (!pItem)
		{
			emit signalClearSelected();
		}
	}
	QListWidget::mousePressEvent(event);
}

void DListWidget::resizeEvent(QResizeEvent *e)
{
	QListWidget::resizeEvent(e);
	doItemsLayout();
}

void DListWidget::keyPressEvent(QKeyEvent *event)
{
	if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_A)
	{
		this->selectAll();
	}
	else if (event->modifiers() == Qt::NoModifier && (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right))
	{
		int nRow = getPlayingIndex();
		if (nRow < 0)
		{
			nRow = getSelectIndex();
			if (nRow < 0)
			{
				if (m_widgets.size() > 0)
				{
					if (event->key() == Qt::Key_Left)
					{
						nRow = m_widgets.size() - 1;
					}
					else
					{
						nRow = 0;
					}
				}
			}
			else
			{
				if (m_widgets.at(nRow)->doKeyPressEvent(event->key()))
				{
					nRow = -1;
				}
				else
				{
					if (event->key() == Qt::Key_Left)
					{
						nRow = (nRow - 1 + this->count()) % this->count();
					}
					else
					{
						nRow = (nRow + 1 + this->count()) % this->count();
					}
				}
			}
			if (nRow >= 0)
			{
				m_widgets.at(nRow)->doSelected();
				return;
			}
		}
		else
		{
			m_widgets.at(nRow)->doKeyPressEvent(event->key());
			return;
		}

	}
	else if (event->modifiers() == Qt::NoModifier && (event->key() == Qt::Key_Up || event->key() == Qt::Key_Down))
	{
		int nRow = getPlayingIndex();
		if (nRow >= 0)
		{
			m_widgets.at(nRow)->doKeyPressEvent(event->key());

		}
		else
		{
			nRow = getUpDownSelectIndex(event->key());
			if (nRow >= 0 && m_widgets.size() > nRow)
			{
				m_widgets.at(nRow)->doSelected();
			}
		}
		return;
	}
	else
	{
		emit signalNotifyKeyPress(event->modifiers(), event->key());
	}
	QListWidget::keyPressEvent(event);
}

void DListWidget::mouseMoveEvent(QMouseEvent *e)
{
	if (this->state() == DraggingState)
	{
		this->setState(NoState);
	}
	QListWidget::mouseMoveEvent(e);
}

void DListWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton && itemAt(event->pos()) == nullptr)
	{
		emit signalAddMedia();
	}
}

void DListWidget::onItemSelectionChanged()
{
	updateSelected();
}

void DListWidget::updateSelected()
{
	emit sinalSeletedMode(this->selectedItems().size() <= 1);

	for (int var = 0; var < this->count(); ++var)
	{
		QListWidgetItem *pItem = item(var);
		if (pItem)
		{
			DBaseWidget *widget = dynamic_cast<DBaseWidget*>(itemWidget(pItem));
			if (widget)
			{
				widget->setSelected(pItem->isSelected());
			}
		}
	}
}

int DListWidget::getSelectIndex()
{
	for (int i = 0; i < m_widgets.size(); ++i)
	{
		if (m_widgets.at(i)->isSelected())
		{
			return i;
		}
	}
	return -1;
}

int DListWidget::getPlayingIndex()
{
	for (int i = 0; i < m_widgets.size(); ++i)
	{
		if (m_widgets.at(i)->isPPTProgram() && m_widgets.at(i)->isPlaying())
		{
			return i;
		}
	}
	return -1;
}

int DListWidget::getUpDownSelectIndex(int key)
{
	// 获取当前列表在第几个位置
	int nIndex = getSelectIndex();
	if (nIndex < 0)
	{
		return -1;
	}

	DBaseWidget *widget = m_widgets.at(nIndex);
	if (!widget)
	{
		return -1;
	}

	// 一行能放几个
	int nColumnCount = (this->size().width() - 18) / (widget->size().width() + this->spacing());
	// 总计数
	int nCount = this->count();

	// 总行数
	int nRowCount = this->count() / nColumnCount;
	if (nRowCount * nColumnCount < this->count())
	{
		++nRowCount;
	}
	// 获取当前 所在第几行
	int nRow = nIndex / nColumnCount;
	// 获取第几个
	int nColumnIndex = nIndex - (nRow *nColumnCount);

	if (key == Qt::Key_Up)
	{
		nRow = ((nRow - 1) + nRowCount) % nRowCount;

		while ((nRow * nColumnCount + nColumnIndex) >= nCount)
		{
			nRow = ((nRow - 1) + nRowCount) % nRowCount;
		}
	}
	else
	{
		nRow = ((nRow + 1) + nRowCount) % nRowCount;

		while ((nRow * nColumnCount + nColumnIndex) >= nCount)
		{
			nRow = ((nRow + 1) + nRowCount) % nRowCount;
		}

	}
	return (nRow * nColumnCount + nColumnIndex);
}

DListWidgetDelegate::DListWidgetDelegate(QObject *parent)
	: QStyledItemDelegate(parent)
{

}

DListWidgetDelegate::~DListWidgetDelegate()
{

}

void DListWidgetDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	editor->setGeometry(option.rect);
}
