/**
 * Copyright (c) 2018, Dubo Dubon Duponey <dubodubonduponey@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
\mainpage
This library is primarily meant to be used by the Dubo Webrunner.
This code is distributed under the terms of the BSD license.
*/

#ifndef DUBOPLATIPUS_ROOT_H
#define DUBOPLATIPUS_ROOT_H

#include "libduboplatipus/libduboplatipus_global.h"
#include <QtCore/qobject.h>

/*! \namespace DuboPlatipus
\brief The library namespace.
*/

namespace DuboPlatipus
{
    /*!
      \brief A dummy object exposing version and name informations.
    */
    class LIBDUBOPLATIPUSSHARED_EXPORT Root: public QObject {
        Q_OBJECT
    public:

        /*! \brief The name of the library.*/
        Q_PROPERTY(const QString DUBO_NAME READ getName)
        /*! \brief The name of the vendor.*/
        Q_PROPERTY(const QString DUBO_VENDOR READ getVendor)
        /*! \brief The version of the library.*/
        Q_PROPERTY(const QString DUBO_VERSION READ getVersion)
        /*! \brief The (git) revision of the library.*/
        Q_PROPERTY(const QString DUBO_REVISION READ getRevision)
        /*! \brief The (git) changeset of the library.*/
        Q_PROPERTY(const QString DUBO_CHANGESET READ getChangeset)

        /*! \brief The build type (release / debug of the library).*/
        Q_PROPERTY(const QString DUBO_BUILD READ getBuildType)
        /*! \brief The type of the library (static / dynamic).*/
        Q_PROPERTY(const QString DUBO_LINK READ getLinkType)
//        /*! \brief The name of the build host.*/
//        Q_PROPERTY(const QString DUBO_HOST READ getHost)
//        /*! \brief Infos returned by the compiler at build time.*/
//        Q_PROPERTY(const QString DUBO_COMPILER READ getCompiler)
        /*! \brief QT Version used to build.*/
        Q_PROPERTY(const QString DUBO_QT READ getQt)

        /*! \brief The nameof the underlying updater library.*/
        Q_PROPERTY(const QString PLUGIN_NAME READ getLibName)
        /*! \brief The version of the underlying updater library.*/
        Q_PROPERTY(const QString PLUGIN_VERSION READ getLibVersion)
        /*! \brief The revision of the underlying updater library.*/
        Q_PROPERTY(const QString PLUGIN_REVISION READ getLibRevision)

        /*! \cond */
        const QString getName();
        const QString getVendor();
        const QString getVersion();
        const QString getRevision();
        const QString getChangeset();

        const QString getBuildType();
        const QString getLinkType();
//        const QString getHost();
//        const QString getCompiler();
        const QString getQt();

        const QString getLibName();
        const QString getLibVersion();
        const QString getLibRevision();
        /*! \endcond */
    };
}

#endif // DUBOPLATIPUS_ROOT_H
