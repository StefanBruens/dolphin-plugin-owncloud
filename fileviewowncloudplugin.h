/***************************************************************************
 *   Copyright (C) 2014 by Stefan Brüns <stefan.bruens@rwth-aachen.de>     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA            *
 ***************************************************************************/

#ifndef FILEVIEW_OC_PLUGIN_H
#define FILEVIEW_OC_PLUGIN_H

#include <kversioncontrolplugin2.h>
// #include <QLocalSocket>

class FileViewOwncloudPlugin : public KVersionControlPlugin2 {

public:
    FileViewOwncloudPlugin(QObject* parent, const QList<QVariant>& args);
    virtual ~FileViewOwncloudPlugin();

    virtual QList<QAction*> actions (const KFileItemList &items) const;
    virtual bool beginRetrieval (const QString &directory);
    virtual void endRetrieval();
    virtual QString fileName() const;
    virtual ItemVersion itemVersion (const KFileItem &item) const;

};

#endif
