/****************************************************************************
**
** Copyright (C) 2016
**
** This file is generated by the Magus toolkit
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
****************************************************************************/

#ifndef MATERIAL_TREE_H
#define MATERIAL_TREE_H

#include <QtWidgets>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QToolBar>
#include <QTabWidget>
#include "constants.h"
#include "tool_resourcetree_widget.h"

QT_BEGIN_NAMESPACE
class QDockWidget;
QT_END_NAMESPACE

/****************************************************************************
This class represents a generic dock widget for sources. The MaterialTreeDockWidget
contains the resourcetree with groups and assets. MaterialTreeDockWidget uses the
following settings:
- The resourcetree contains audio, materials, meshes, scripts and textures groups by default
- The contexmenu is enabled (default)
- Toplevel groups are added up front (by means of its parent
- Disable the contextmenu-item to add/create a new toplevel group
- Don't register the resource (with mResourceTreeWidget->registerResource)
  => icons of subgroups cannot be selected from the contextmenu, but are inherited from toplevel group
- Toplevel groups cannot be deleted
- Subgroups and assets are not added up front
  => Add them by means of the contextmenu

IMPORTANT:
=========
This class is changed to facilitate the HLMS editor. Do not use it as a
generic Magus class.
***************************************************************************/
class MaterialTreeDockWidget : public QDockWidget
{
    Q_OBJECT

    public:
        MaterialTreeDockWidget(const QString& iconDir, const QString& title, QMainWindow* parent, Qt::WindowFlags flags = 0);
        ~MaterialTreeDockWidget(void);

        // Returns a list of all resources in the resource tree. This includes both groups, subgroups and assets
        QVector<Magus::QtResourceInfo*>& getResources (void);

        // Set the resources
        void setResources (const QVector<Magus::QtResourceInfo*>& resources);

        // Add a material to  the resourcetree
        bool addMaterial(const QString& baseNameJson,
                         const QString& fullNameJson,
                         const QString& baseNameThumb,
                         EditorHlmsTypes type);

        // Select a toplevel resource.
        void selectTopLevel(int toplevelId);

        // Clear all content in the resourcetree
        void clearContent(void);

        // Add an asset entry to the resource tree, but don't signal anything.
        // This is typcially used when a file has been dropped to an asset widget (eg. audio) and the
        // resource tree must be updated with the asset name.
        // Suppressing the signal prevents that an asset is added to the asset widget twice.
        bool addAssetQuiet(int toplevelId,
                           const QString& name,
                           const QString& baseName,
                           const QString& baseNameThumb);


        // Select an asset entry in the resource tree, but don't signal anything.
        const QString& setSelectAssetQuiet(const QString& baseNameThumb);

        // The entry is selected and choosen for further processing
        const QString& doubleClicked(const QString& baseNameThumb);

        // Delete an asset entry from the resource tree, but don't signal anything.
        void deleteAssetQuiet(int toplevelId, const QString& name, const QString& baseName);

        // Delete an asset entry from the resource tree, but don't signal anything.
        // The entry is found based on the baseNameThumb
        void deleteAssetQuiet(const QString& baseNameThumb);

        // Check whether a resource already exists (by its basename)
        bool isResourceExisting(const QString& baseName);

        // Return the resourceId based on the thumb name
        int getResourceId(const QString& baseNameThumb);

        // Return the full qualified name of the currently selected resource
        const QString& getSelectedFullQualifiedName(void);

        void initializeResourceTree (void);

    protected:
        const QString& determineSubgroupIcon(int toplevelId);

    signals:
        void resourceSelected(int toplevelId, int parentId, int resourceId, const QString& name, const QString& baseName);
        void resourceDoubleClicked(int toplevelId, int parentId, int resourceId, const QString& name, const QString& baseName);
        void resourceAdded(int toplevelId, int parentId, int resourceId, const QString& name, const QString& baseName);
        void resourceDeleted(int toplevelId, int parentId, int resourceId, const QString& name, const QString& baseName);
        void resourceSearched(const QString& searchPattern);
        void resourceSearchReset(void);

    private slots:
        void handleResourceSelected(int resourceId);
        void handleResourceDoubleClicked(int resourceId);
        void handleResourceAdded(int resourceId);
        void handleResourceDeleted(int resourceId);
        void handleResourceMoved(int resourceId);
        void handleResourceSearched(const QString& searchPattern);
        void handleResourceSearchReset(void);

    private:
        QMainWindow* mParent;
        QMainWindow* mInnerMain;
        Magus::QtResourceTreeWidget* mResourceTreeWidget;
        QString mIconDir;
        QString mEmptyString;
        QMap<int, QtSourcesInfo> mSourceInfo;
};

#endif

