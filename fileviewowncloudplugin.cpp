#include <kpluginfactory.h>
#include <kpluginloader.h>

#include "fileviewowncloudplugin.h"

K_PLUGIN_FACTORY(FileViewOwncloudPluginFactory, registerPlugin<FileViewOwncloudPlugin>();)
K_EXPORT_PLUGIN(FileViewOwncloudPluginFactory("fileviewowncloudplugin"))

class FileViewOwncloudPlugin::Private
{
public:

};

FileViewOwncloudPlugin::FileViewOwncloudPlugin(QObject* parent, const QList<QVariant>& args):
    KVersionControlPlugin2(parent),
    d(new Private(this))
{
    // qDebug() << "OCP: started oc plugin";

}

FileViewOwncloudPlugin::~FileViewOwncloudPlugin()
{
    // qDebug() << "OCP: oc plugin exit";
    delete d;
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

