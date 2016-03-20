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

#ifndef MATERIAL_THUMBS_H
#define MATERIAL_THUMBS_H

#include <QtWidgets>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QToolBar>
#include <QTabWidget>
#include "constants.h"
#include "tool_default_texturewidget.h"
#include "tool_resourcetree_widget.h"

QT_BEGIN_NAMESPACE
class QDockWidget;
QT_END_NAMESPACE

/****************************************************************************
This class represents a generic MaterialThumbsDockWidget

IMPORTANT:
=========
This class is changed to facilitate the HLMS editor. Do not use it as a
generic Magus class.
***************************************************************************/
class MaterialThumbsDockWidget : public QDockWidget
{
    Q_OBJECT

    public:
        MaterialThumbsDockWidget(const QString& iconDir, const QString& title, QMainWindow* parent, Qt::WindowFlags flags = 0);
        ~MaterialThumbsDockWidget(void);
        void createActions(void);
        void createMenus(void);
        void createToolBars(void);

        // Add a tab to this widget. The tab represents an asset (mesh, texture, etc.). The widget is a widget that corresponds wuth
        // the asset type.
        void addTab(QWidget* widget, const QIcon& icon, const QString& name);

        // Add material resources to both Pbs and Unlit widgets
        void setResources(const QVector<Magus::QtResourceInfo*>& resources);

        // Add a material to the asset widget
        bool addMaterial(const QString& baseNameJson,
                         const QString& fullNameJson,
                         const QString& baseNameThumb,
                         EditorHlmsTypes type);

        // Add an asset to a particular asset widget
        void addAsset(int toplevelId, int parentId, int resourceId, const QString& name, const QString& baseName);

        // Delete an asset from a particular asset widget
        void deleteAsset(int toplevelId,
                         const QString& name,
                         bool nameIsFullName = true); // name is either full qualified name (filename + path) or only basename
        void deleteAsset(int toplevelId, const QString& name, const QString& baseName);
        void deleteAsset(const QString& name, bool nameIsFullName); // name is either full qualified name (filename + path) or only basename

        // Select the appropriate tab, based on the given arguments
        void selectTab(int toplevelId, int parentId, int resourceId, const QString& name, const QString& baseName);

        // Set baseNameThumb selected
        void setSelectThumb(int toplevelId, const QString& baseNameThumb);

        // Apply filtering to the underlying widgets
        void filter(const QString& pattern);

        // Reset the filtering in the underlying widgets
        void resetFilter(void);

        // Clear all content in the underlying widgets
        void clearContent(void);

    signals:
        void tabChanged(int index);
        void assetDeleted(const QString& name, const QString& baseName);
        void assetSelected(const QString& name, const QString& baseName);
        void assetDoubleClicked(const QString& name, const QString& baseName);

    private slots:
        void handleTabChanged(int index);
        void handleAssetDeleted(const QString& name, const QString& baseName);
        void handleAssetSelected(const QString& name, const QString& baseName);
        void handleAssetDoubleClicked(const QString& name, const QString& baseName);

    private:
        QMainWindow* mParent;
        QMainWindow* mInnerMain;
        QTabWidget* mTabWidget;
        QString mIconDir;
        Magus::QtDefaultTextureWidget* mPbsSelection;
        Magus::QtDefaultTextureWidget* mUnlitSelection;
};

#endif

