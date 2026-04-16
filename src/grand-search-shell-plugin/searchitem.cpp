// SPDX-FileCopyrightText: 2024 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "searchitem.h"

#include <pluginfactory.h>

#include <DDBusSender>
#include <DDciIcon>
#include <DGuiApplicationHelper>

#include <QBuffer>
#include <QGuiApplication>
#include <QProcess>
#include <QLoggingCategory>

Q_LOGGING_CATEGORY(logShell, "org.deepin.dde.dock.shell.grandsearch")

DGUI_USE_NAMESPACE
namespace dock
{

const QString grandSearchService = "com.deepin.dde.GrandSearch";
const QString grandSearchPath = "/com/deepin/dde/GrandSearch";
const QString grandSearchInterface = "com.deepin.dde.GrandSearch";
static DDBusSender searchDbus()
{
    return DDBusSender().service(grandSearchService).path(grandSearchPath).interface(grandSearchInterface);
}

SearchItem::SearchItem(QObject *parent)
    : DAppletDock(parent)
    , m_grandSearchVisible(false)
{
    qCDebug(logShell) << "Grand Search shell plugin initialized";
}

void SearchItem::toggleGrandSearch()
{
    qCDebug(logShell) << "Toggling Grand Search visibility via shell plugin";
    searchDbus().method("SetVisible").arg(true).call();
}

void SearchItem::toggleGrandSearchConfig()
{
    qCDebug(logShell) << "Opening Grand Search configuration via shell plugin";
    QProcess::startDetached("dde-grand-search", QStringList() << "--setting");
}

DockItemInfo SearchItem::dockItemInfo()
{
    DockItemInfo info;
    info.name = "searchItem";
    info.displayName = tr("Search item");
    info.itemKey = "searchItem";
    info.settingKey = "searchItem";
    info.visible = visible();
    info.dccIcon = "search-view.svg";
    return info;
}
void SearchItem::onGrandSearchVisibleChanged(bool visible)
{
    qCDebug(logShell) << "Grand Search visibility change notification received - From:" << m_grandSearchVisible << "To:" << visible;

    if (m_grandSearchVisible != visible) {
        m_grandSearchVisible = visible;

        Q_EMIT grandSearchVisibleChanged(visible);
    }
}

D_APPLET_CLASS(SearchItem)
}

#include "searchitem.moc"
