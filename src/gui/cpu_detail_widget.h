/*
* Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd
*
* Author:      zhangsong<zhangsong@uniontech.com>
* Maintainer:  zhangsong<zhangsong@uniontech.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef CPU_DETAIL_WIDGET_H
#define CPU_DETAIL_WIDGET_H

#include <QWidget>
#include <DPushButton>
#include "base_detail_view_widget.h"

class CPUInfoModel;
class QScrollArea;
class CPUDetailGrapTableItem : public QWidget
{
    Q_OBJECT

public:
    explicit CPUDetailGrapTableItem(CPUInfoModel *model, int index, QWidget *parent = nullptr);

    ~CPUDetailGrapTableItem();

    void setMode(int mode);

    void sethorizontal(bool isHorizontalLast);

    void setVerticalLast(bool isVerticalLast);

    void setColor(QColor color);

public slots:
    void updateStat();

protected:
    void paintEvent(QPaintEvent *event);

    void drawNormalMode(QPainter &painter);

    void drawSimpleMode(QPainter &painter);

    void drawTextMode(QPainter &painter);

private:
    QList<qreal>  m_cpuPercents;
    CPUInfoModel *m_cpuInfomodel = nullptr;
    QColor m_color;
    int m_mode  = 1;        //1:normal 2:simple 3:text
    int m_index = -1;
    bool m_isHorizontalLast = false;
    bool m_isVerticalLast = false;
};

class CPUDetailGrapTable : public QWidget
{
    Q_OBJECT
public:
    CPUDetailGrapTable(CPUInfoModel *model, QWidget *parent);
};

struct CPUDetailInfoTableItem {
    QString first;
    QString second;
};

class CPUDetailInfoTable: public QWidget
{
    Q_OBJECT
public:
    CPUDetailInfoTable(QWidget *parent);

    void addItem(QString first, QString second);

    void modItem(int index, QString first, QString second);

    void paintEvent(QPaintEvent *);

private:
    QList<CPUDetailInfoTableItem> m_items;
};

class CPUDetailWidget : public BaseDetailViewWidget
{
    Q_OBJECT
public:
    explicit CPUDetailWidget(QWidget *parent = nullptr);

    void resizeEvent(QResizeEvent *event);

    void paintEvent(QPaintEvent *);

    void adjustGeometry(QSize rect);

private slots:
    void onCPUInfoUpdated();

    void fontChanged(const QFont &font);

private:
    CPUInfoModel *m_cpuInfomodel = nullptr;
    CPUDetailGrapTable *m_graphicsTable = nullptr;
    Dtk::Widget::DPushButton *m_backBtn = nullptr;
    QScrollArea *m_textArea = nullptr;
    CPUDetailInfoTable *m_textTable = nullptr;
};

#endif // CPU_DETAIL_WIDGET_H