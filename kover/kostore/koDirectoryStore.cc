/* This file is part of the KDE project
   Copyright (C) 2002 David Faure <david@mandrakesoft.com>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.
*/

#include "koDirectoryStore.h"
#include <qfile.h>
#include <qdir.h>
#include <kdebug.h>

// HMMM... I used QFile and QDir.... but maybe this should be made network transparent?

KoDirectoryStore::KoDirectoryStore( const QString& path, Mode _mode )
    : m_basePath( path )
{
    // The parameter must include "maindoc.xml"
    int pos = m_basePath.findRev( '/' );
    if ( pos != -1 && pos != (int)m_basePath.length()-1 )
        m_basePath = m_basePath.left( pos );
    if ( !m_basePath.endsWith("/") )
        m_basePath += '/';
    //if ( !m_basePath.startsWith("/") )
    //    m_basePath.prepend( QDir::currentDirPath() + '/' );
    m_currentPath = m_basePath;
    kdDebug(s_area) << "KoDirectoryStore::KoDirectoryStore base path:" << m_basePath << endl;
    m_bGood = init( _mode );
}

KoDirectoryStore::~KoDirectoryStore()
{
}

bool KoDirectoryStore::init( Mode _mode )
{
    KoStore::init( _mode );
    QDir dir( m_basePath );
    if ( dir.exists() )
        return true;
    dir = QDir::current();
    // Dir doesn't exist. If reading -> error. If writing -> create.
    if ( _mode == Write && dir.mkdir( m_basePath ) ) {
        kdDebug(s_area) << "KoDirectoryStore::init Directory created: " << m_basePath << endl;
        return true;
    }
    return false;
}

bool KoDirectoryStore::openReadOrWrite( const QString& name, int iomode )
{
    //kdDebug(s_area) << "KoDirectoryStore::openReadOrWrite m_currentPath=" << m_currentPath << " name=" << name << endl;
    int pos = name.findRev('/');
    if ( pos != -1 ) // there are subdirs in the name -> maybe need to create them, when writing
    {
        pushDirectory(); // remember where we were
        enterAbsoluteDirectory( QString::null );
        //kdDebug(s_area) << "KoDirectoryStore::openReadOrWrite entering " << name.left(pos) << endl;
        bool ret = enterDirectory( name.left( pos ) );
        popDirectory();
        if ( !ret )
            return false;
    }
    m_stream = new QFile( m_basePath + name );
    if ( !m_stream->open( iomode ) )
    {
        delete m_stream;
        m_stream = 0L;
        return false;
    }
    if ( iomode == IO_ReadOnly )
        m_iSize = m_stream->size();
    return true;
}

bool KoDirectoryStore::enterRelativeDirectory( const QString& dirName )
{
    QDir origDir( m_currentPath );
    m_currentPath += dirName;
    if ( !m_currentPath.endsWith("/") )
        m_currentPath += '/';
    //kdDebug(s_area) << "KoDirectoryStore::enterRelativeDirectory m_currentPath now " << m_currentPath << endl;
    QDir newDir( m_currentPath );
    if ( newDir.exists() )
        return true;
    // Dir doesn't exist. If reading -> error. If writing -> create.
    if ( mode() == Write && origDir.mkdir( dirName ) ) {
        kdDebug(s_area) << "Created " << dirName << " under " << origDir.absPath() << endl;
        return true;
    }
    return false;
}

bool KoDirectoryStore::enterAbsoluteDirectory( const QString& path )
{
    m_currentPath = m_basePath + path;
    //kdDebug(s_area) << "KoDirectoryStore::enterAbsoluteDirectory " << m_currentPath << endl;
    QDir newDir( m_currentPath );
    Q_ASSERT( newDir.exists() ); // We've been there before, therefore it must exist.
    return newDir.exists();
}

bool KoDirectoryStore::fileExists( const QString& absPath )
{
    kdDebug(s_area) << "KoDirectoryStore::fileExists " << m_basePath+absPath << endl;
    return QFile::exists( m_basePath + absPath );
}
