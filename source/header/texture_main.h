/****************************************************************************
**
** Copyright (C) 2016 - 2017
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

#ifndef TEXTURE_MAIN_H
#define TEXTURE_MAIN_H

#include <QCloseEvent>
#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QToolBar>
#include "constants.h"
#include "texture_thumbs.h"
#include "texture_tree.h"

QT_BEGIN_NAMESPACE

QT_END_NAMESPACE

/****************************************************************************
MainWindow is the main container window
***************************************************************************/
class TextureMain : public QMainWindow
{
    Q_OBJECT

    public:
        TextureMain(const QString& iconDir, QWidget * parent = 0);
        ~TextureMain(void);

        // Returns a list of all resources in the resource tree. This includes both groups, subgroups and assets
        QVector<Magus::QtResourceInfo*>& getResources (void);

        // Creates the resourcetree and loads the assets.
        void setResources (const QVector<Magus::QtResourceInfo*>& resources);

        // Initialise the resourcetree
        void initResourceTree(void);

        // Returns the qualified name of the currently selected item from the resource tree
        const QString& getSelectedFullQualifiedName(void);

        void addTextureFile (const QString& fileName);
        void addTextureFile (const QString& fileName, const QString& group);
        void deleteTexture (const QString& fileName);
        const QString& getCurrentFileName (void);
        const QPixmap* getCurrentPixmap (void);

        // Empty the texture browser
        void clearResources(void);

        bool mIsClosing;

    protected:
        QMessageBox::StandardButton fileDoesNotExistsWarning(const QString& fileName);

    signals:
        void textureDoubleClicked(int toplevelId, int parentId, int resourceId, const QString& name, const QString& baseName);
        void customContextMenuItemSelected(const QString& menuItemText);
        void textureMutationOccured(void);

    private slots:
        void handleTextureSelected(int toplevelId, int parentId, int resourceId, const QString& name, const QString& baseName, int resourceType);
        void handleTextureDoubleClicked(int toplevelId, int parentId, int resourceId, const QString& name, const QString& baseName);
        void handleTextureMoved(int toplevelId, int parentId, int resourceId, const QString& name, const QString& baseName, int resourceType);
        void handleTextureChanged(int toplevelId, int parentId, int resourceId, const QString& name, const QString& baseName, int resourceType);
        void handleTextureAdded(int toplevelId, int parentId, int resourceId, const QString& name, const QString& baseName, int resourceType);
        void handleTextureDeleted(int toplevelId, int parentId, int resourceId, const QString& name, const QString& baseName);
        void handleTextureSearched(const QString& searchPattern);
        void handleTextureSearchReset(void);
        void handleThumbDeleted(const QString& name, const QString& baseName);
        void handleThumbSelected(const QString& name, const QString& baseName);
        void handleTextureFileDropped(const QString& name, const QString& baseName);
        void handleThumbDoubleClicked(const QString& name, const QString& baseName);
        void handleCustomContextMenuItemSelected(const QString& menuItemText);

    private:
        void createActions(void);
        void createMenus(void);
        void createToolBars(void);
        void createStatusBar(void);
        void createDockWindows(void);
        void closeEvent(QCloseEvent* event);

        TextureTreeDockWidget* mTextureTreeDockWidget;
        TextureThumbsDockWidget* mTextureThumbsDockWidget;
        QString mIconDir;
        QString mSelectedFileName;
};

#endif

