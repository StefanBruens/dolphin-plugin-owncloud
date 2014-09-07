#include <kpluginfactory.h>
#include <kpluginloader.h>

#include "fileviewowncloudplugin.h"

K_PLUGIN_FACTORY(FileViewOwncloudPluginFactory, registerPlugin<FileViewOwncloudPlugin>();)
K_EXPORT_PLUGIN(FileViewOwncloudPluginFactory("fileviewowncloudplugin"))

FileViewOwncloudPlugin::FileViewOwncloudPlugin(QObject* parent, const QList<QVariant>& args)
{
}

FileViewOwncloudPlugin::~FileViewOwncloudPlugin()
{
}

QList<QAction*>
FileViewOwncloudPlugin::actions (const KFileItemList &items) const
{
    return QList<QAction*>();
}

bool
FileViewOwncloudPlugin::beginRetrieval (const QString &directory)
{
    return true;
}

void
FileViewOwncloudPlugin::endRetrieval()
{
    return;
}

QString
FileViewOwncloudPlugin::fileName() const
{
    return ".owncloudsync.log";
}

KVersionControlPlugin2::ItemVersion
FileViewOwncloudPlugin::itemVersion (const KFileItem &item) const
{
    return NormalVersion;
}

