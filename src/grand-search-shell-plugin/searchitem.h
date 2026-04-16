// SPDX-FileCopyrightText: 2024 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <applet.h>
#include <dock/dappletdock.h>
#include <dock/dockiteminfo.h>
// #include "dsglobal.h"

#include <QGuiApplication>

class QDBusMessage;
namespace dock
{

class SearchItem : public DS_NAMESPACE::DAppletDock
{
    Q_OBJECT
    Q_PROPERTY(bool grandSearchVisible READ grandSearchVisible NOTIFY grandSearchVisibleChanged)
public:
    explicit SearchItem(QObject *parent = nullptr);

    Q_INVOKABLE void toggleGrandSearch();
    Q_INVOKABLE void toggleGrandSearchConfig();

    Q_INVOKABLE bool grandSearchVisible() const
    {
        return m_grandSearchVisible;
    }

    bool load() override
    {
        return true;
    }
    DockItemInfo dockItemInfo();

Q_SIGNALS:
    void grandSearchVisibleChanged(bool);

private slots:
    void onGrandSearchVisibleChanged(bool);

private:
    bool m_grandSearchVisible;
};

}
