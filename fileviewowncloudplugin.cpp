#include <KPluginFactory>
#include <KPluginLoader>
#include <KFileItem>
#include <QDebug>
#include <QDir>
#include <QPointer>
#include <QTcpSocket>
#include <QHostAddress>

#include "fileviewowncloudplugin.h"

K_PLUGIN_FACTORY(FileViewOwncloudPluginFactory, registerPlugin<FileViewOwncloudPlugin>();)
K_EXPORT_PLUGIN(FileViewOwncloudPluginFactory("fileviewowncloudplugin"))

class FileViewOwncloudPlugin::Private
{
public:
    QPointer<QTcpSocket> ocQuerySocket;
    class OcMessage
    {
    public:
        OcMessage(const QByteArray& message);
        // OcMessage() = delete;

        QString path;
        enum Type {
            TYPE_Unknown = -1,
            REGISTER_PATH,
            UPDATE_VIEW,
            BROADCAST,
            STATUS,
        };
        enum Status {
            STATUS_Unknown = -1,
            OK,
            SYNC,
        };
        Type type;
        Status status; //< only for type == STATUS
    };

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
    // qDebug() << "OCP: started retrieval for " << directory;
    d->ocQuerySocket = new QTcpSocket;
    d->ocQuerySocket->connectToHost(QHostAddress::LocalHost, 33001, QIODevice::ReadWrite);
    return true;
}

void
FileViewOwncloudPlugin::endRetrieval()
{
    delete d->ocQuerySocket;
}

QString
FileViewOwncloudPlugin::fileName() const
{
    return ".owncloudsync.log";
}

KVersionControlPlugin2::ItemVersion
FileViewOwncloudPlugin::itemVersion (const KFileItem &item) const
{
    QString path = QDir(item.localPath()).canonicalPath();
    // qDebug() << "OCP: query version for " << item.name() << " | " << path;

    if (!d->ocQuerySocket->waitForConnected(1000)) {
        return UnversionedVersion;
    }

    int tries = 5;
    while (--tries) {
        QString command = "RETRIEVE_FILE_STATUS:" + path + "\n";
        d->ocQuerySocket->write(command.toUtf8());
        d->ocQuerySocket->waitForReadyRead();
        QByteArray answer = d->ocQuerySocket->readAll();

        QList<QByteArray> lines = answer.split('\n');
        foreach (const QByteArray& line, lines) {
            if (line.isEmpty())
                continue;

            Private::OcMessage response(line);
            if (response.type == Private::OcMessage::STATUS && response.path == path) {
                if(response.status == Private::OcMessage::OK)
                    return NormalVersion;
                if(response.status == Private::OcMessage::SYNC)
                    return UpdateRequiredVersion;
                return UnversionedVersion;
            }
        }
    }
    return UnversionedVersion;
}

FileViewOwncloudPlugin::Private::OcMessage::OcMessage(const QByteArray& response)
        : type(FileViewOwncloudPlugin::Private::OcMessage::TYPE_Unknown)
        , status(FileViewOwncloudPlugin::Private::OcMessage::STATUS_Unknown)
{
    int first = response.indexOf(':', 0);

    QByteArray typeS = response.mid(0,first);
    if      (typeS == "REGISTER_PATH") type = REGISTER_PATH;
    else if (typeS == "UPDATE_VIEW")   type = UPDATE_VIEW;
    else if (typeS == "BROADCAST")     type = BROADCAST;
    else if (typeS == "STATUS")        type = STATUS;

    // Workaround, BROADCAST may have extra ':'
    if (type == BROADCAST && response[first+1] == ':')
        first += 1;

    if (type == STATUS) {
        int second = response.indexOf(':', first+1);
        QByteArray statusS = response.mid(first+1, second-first-1);
        if      (statusS == "OK")   status = OK;
        else if (statusS == "SYNC") status = SYNC;

        path = QString::fromUtf8(response.mid(second+1, -1));
        // qDebug() << "OCP: STATUS response:" << statusS << path;
    } else if (type != TYPE_Unknown) {
        path = QString::fromUtf8(response.mid(first+1, -1));
        // qDebug() << "OCP:" << typeS << type << "response:" << path;
    } else {
        qDebug() << "OCP: unknown response:" << response;
    }
}

