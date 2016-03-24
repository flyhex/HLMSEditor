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

// Include
#include "constants.h"
#include "magus_core.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMenuBar>
#include "mainwindow.h"
#include "OgreItem.h"
#include "OgreHlmsPbs.h"
#include "OgreHlmsUnlit.h"
#include "OgreHlmsPbsDatablock.h"
#include "OgreHlmsUnlitDatablock.h"
#include "OgreHlmsManager.h"
#include "hlms_builder.h"

//****************************************************************************/
MainWindow::MainWindow(void) :
    mIsClosing(false),
    mFirst(true),
    mSaveTextureBrowserTimerActive(false)
{
    installEventFilter(this);

    // Create the Ogre Manager
    mOgreManager = new Magus::OgreManager();
    mHlmsName = QString("");
    mTempString = QString("");
    
	// Perform standard functions
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    createDockWindows();
    mMaterialBrowser = new MaterialBrowserDialog(this);
    loadMaterialBrowserCfg();
    loadTextureBrowserCfg();
    mOgreManager->initialize();

    // Set the title
    setWindowTitle(QString("HLMS editor"));

    // Set the stylesheet of the application
    QFile File(QString("dark.qss"));
    File.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(File.readAll());
    setStyleSheet(styleSheet);
	showMaximized();
}

//****************************************************************************/
MainWindow::~MainWindow(void)
{
    delete mOgreManager;
}

//****************************************************************************/
bool MainWindow::eventFilter(QObject* object, QEvent* event)
{
    if (event->type()==QEvent::KeyPress)
    {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if (key->key() == Qt::Key_F5)
        {
            // F5 was pressed
            mNodeEditorDockWidget->generateDatablock();
        }
        if (key->key() == Qt::Key_S && (QApplication::keyboardModifiers() & Qt::ControlModifier))
        {
            // CTRL+S was pressed
            doSaveDatablockMenuAction();
        }
    }
    return QObject::eventFilter(object, event);
}

//****************************************************************************/
void MainWindow::closeEvent(QCloseEvent* event)
{
    mIsClosing = true;
}

//****************************************************************************/
void MainWindow::createActions(void)
{
    // File menu
    mNewHlmsPbsAction = new QAction(QString("Pbs"), this);
    connect(mNewHlmsPbsAction, SIGNAL(triggered()), this, SLOT(doNewHlmsPbsAction()));
    mNewHlmsUnlitAction = new QAction(QString("Unlit"), this);
    connect(mNewHlmsUnlitAction, SIGNAL(triggered()), this, SLOT(doNewHlmsUnlitAction()));
    mOpenDatablockMenuAction = new QAction(QString("Open Hlms"), this);
    connect(mOpenDatablockMenuAction, SIGNAL(triggered()), this, SLOT(doOpenDatablockMenuAction()));
    mSaveDatablockMenuAction = new QAction(QString("Save Hlms"), this);
    connect(mSaveDatablockMenuAction, SIGNAL(triggered()), this, SLOT(doSaveDatablockMenuAction()));
    mSaveAsDatablockMenuAction = new QAction(QString("Save Hlms as"), this);
    connect(mSaveAsDatablockMenuAction, SIGNAL(triggered()), this, SLOT(doSaveAsDatablockMenuAction()));
    mQuitMenuAction = new QAction(QString("Quit"), this);
    connect(mQuitMenuAction, SIGNAL(triggered()), this, SLOT(doQuitMenuAction()));

    // Materials menu
    mMaterialBrowserOpenMenuAction = new QAction(QString("Open browser"), this);
    connect(mMaterialBrowserOpenMenuAction, SIGNAL(triggered()), this, SLOT(doMaterialBrowserOpenMenuAction()));
    mMaterialBrowserAddMenuAction = new QAction(QString("Add Hlms to browser"), this);
    connect(mMaterialBrowserAddMenuAction, SIGNAL(triggered()), this, SLOT(doMaterialBrowserAddMenuAction()));

    // Texture menu
    mTextureBrowserImportMenuAction = new QAction(QString(ACTION_IMPORT_TEXTURES_FROM_DIR), this);
    connect(mTextureBrowserImportMenuAction, SIGNAL(triggered()), this, SLOT(doTextureBrowserImportMenuAction()));
    mTextureBrowserAddImageMenuAction = new QAction(QString(ACTION_ADD_TEXTURES), this);
    connect(mTextureBrowserAddImageMenuAction, SIGNAL(triggered()), this, SLOT(doTextureBrowserAddImageMenuAction()));

    // Window menu
    mResetWindowLayoutMenuAction = new QAction(QString("Reset Window Layout"), this);
    connect(mResetWindowLayoutMenuAction, SIGNAL(triggered()), this, SLOT(doResetWindowLayoutMenuAction()));
}

//****************************************************************************/
void MainWindow::createMenus(void)
{
    mFileMenu = menuBar()->addMenu(QString("&File"));
    mMaterialBrowserMenu = menuBar()->addMenu(QString("&Materials"));
    mTextureBrowserMenu = menuBar()->addMenu(QString("&Textures"));
    QMenu* fileMenuAction = mFileMenu->addMenu("New Hlms");
    fileMenuAction->addAction(mNewHlmsPbsAction);
    fileMenuAction->addAction(mNewHlmsUnlitAction);
    mFileMenu->addAction(mOpenDatablockMenuAction);
    mFileMenu->addAction(mSaveDatablockMenuAction);
    mFileMenu->addAction(mSaveAsDatablockMenuAction);
    mFileMenu->addAction(mQuitMenuAction);
    mMaterialBrowserMenu->addAction(mMaterialBrowserOpenMenuAction);
    mMaterialBrowserMenu->addAction(mMaterialBrowserAddMenuAction);
    mTextureBrowserMenu->addAction(mTextureBrowserImportMenuAction);
    mTextureBrowserMenu->addAction(mTextureBrowserAddImageMenuAction);
    mWindowMenu = menuBar()->addMenu(QString("&Window"));
    mWindowMenu->addAction(mResetWindowLayoutMenuAction);
}

//****************************************************************************/
void MainWindow::createToolBars(void)
{

}

//****************************************************************************/
void MainWindow::createStatusBar(void)
{

}

//****************************************************************************/
void MainWindow::createDockWindows(void)
{
    mRenderwindowDockWidget = new RenderwindowDockWidget("Renderwindow", this);
    addDockWidget(Qt::LeftDockWidgetArea, mRenderwindowDockWidget);
    mPropertiesDockWidget = new PropertiesDockWidget("Properties", this);
    addDockWidget(Qt::LeftDockWidgetArea, mPropertiesDockWidget);

    mTextureDockWidget = new TextureDockWidget("Textures", this);
    addDockWidget(Qt::RightDockWidgetArea, mTextureDockWidget);
    mNodeEditorDockWidget = new NodeEditorDockWidget("NodeEditor", this);
    addDockWidget(Qt::RightDockWidgetArea, mNodeEditorDockWidget);
    connect(mTextureDockWidget, SIGNAL(textureDoubleClicked(QString,QString)), this, SLOT(handleTextureDoubleClicked(QString,QString)));
    connect(mTextureDockWidget, SIGNAL(customContextMenuItemSelected(QString)), this, SLOT(handleCustomContextMenuItemSelected(QString)));
    connect(mTextureDockWidget, SIGNAL(textureMutationOccured()), this, SLOT(handleTextureMutationOccured()));
}

//****************************************************************************/
void MainWindow::doNewHlmsPbsAction(void)
{
    initDatablocks();
    mPropertiesDockWidget->clear();
    mNodeEditorDockWidget->newHlmsPbs();
}

//****************************************************************************/
void MainWindow::doNewHlmsUnlitAction(void)
{
    initDatablocks();
    mPropertiesDockWidget->clear();
    mNodeEditorDockWidget->newHlmsUnlit();
}

//****************************************************************************/
void MainWindow::doOpenDatablockMenuAction(void)
{
    // Load the materials
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, QString("Open Hlms file"),
                                            QString(""),
                                            QString("Json material (*.json)"));
    loadDatablock(fileName);
}

//****************************************************************************/
void MainWindow::loadDatablock(const QString jsonFileName)
{
    // Load the materials
    if (!jsonFileName.isEmpty())
    {
        // Read the json file as text file and feed it to the HlmsManager::loadMaterials() function
        // Note, that the resources (textures, etc.) must be present

        // First, delete all datablocks before loading the new ones
        initDatablocks();
        mPropertiesDockWidget->clear();

        // Read the json file
        Ogre::HlmsManager* hlmsManager = mOgreManager->getOgreRoot()->getHlmsManager();
        QFile file(jsonFileName);
        file.open(QFile::ReadOnly | QFile::Text);
        QTextStream readFile(&file);
        QString jsonString = readFile.readAll();
        QByteArray ba = jsonString.toLatin1();
        char* jsonChar = ba.data();
        Ogre::String fname = jsonFileName.toStdString();
        Ogre::HlmsJson hlmsJson(hlmsManager);
        try
        {
            // Load the datablocks (which also creates them)
            hlmsJson.loadMaterials(fname, jsonChar);
        }
        catch (Ogre::Exception e)
        {
            Ogre::LogManager::getSingleton().logMessage("MainWindow::doOpenDatablockMenuAction(); Could not load the materials\n");
        }
        file.close();
        mHlmsName = jsonFileName;

        // Get the (list of) datablocks and assign the first one to the current 'item' to be rendered
        getAndSetFirstDatablock();
    }
}

//****************************************************************************/
void MainWindow::destroyAllDatablocks(void)
{
    // Get the datablock from the item and remove it
    mOgreManager->getOgreWidget(OGRE_WIDGET_RENDERWINDOW)->setDefaultDatablockItem();
    Ogre::HlmsManager* hlmsManager = mOgreManager->getOgreRoot()->getHlmsManager();
    Ogre::HlmsPbs* hlmsPbs = static_cast<Ogre::HlmsPbs*>( hlmsManager->getHlms(Ogre::HLMS_PBS));
    Ogre::HlmsUnlit* hlmsUnlit = static_cast<Ogre::HlmsUnlit*>( hlmsManager->getHlms(Ogre::HLMS_UNLIT));

    // Iterate through all pbs datablocks and remove them
    Ogre::Hlms::HlmsDatablockMap::const_iterator itorPbs = hlmsPbs->getDatablockMap().begin();
    Ogre::Hlms::HlmsDatablockMap::const_iterator endPbs  = hlmsPbs->getDatablockMap().end();
    Ogre::HlmsPbsDatablock* pbsDatablock;
    while( itorPbs != endPbs)
    {
        pbsDatablock = static_cast<Ogre::HlmsPbsDatablock*>(itorPbs->second.datablock);
        if (pbsDatablock != hlmsPbs->getDefaultDatablock() &&
                pbsDatablock != hlmsUnlit->getDefaultDatablock())
        {
            hlmsPbs->destroyDatablock(pbsDatablock->getName());
            itorPbs = hlmsPbs->getDatablockMap().begin(); // Start from the beginning again
        }
        else
            ++itorPbs;
    }

    // Iterate through all unlit datablocks and remove them
    Ogre::Hlms::HlmsDatablockMap::const_iterator itorUnlit = hlmsUnlit->getDatablockMap().begin();
    Ogre::Hlms::HlmsDatablockMap::const_iterator endUnlit  = hlmsUnlit->getDatablockMap().end();
    Ogre::HlmsUnlitDatablock* unlitDatablock;
    while( itorUnlit != endUnlit)
    {
        unlitDatablock = static_cast<Ogre::HlmsUnlitDatablock*>(itorUnlit->second.datablock);
        if (unlitDatablock != hlmsPbs->getDefaultDatablock() &&
                unlitDatablock != hlmsUnlit->getDefaultDatablock())
        {
            hlmsUnlit->destroyDatablock(unlitDatablock->getName());
            itorUnlit = hlmsUnlit->getDatablockMap().begin(); // Start from the beginning again
        }
        else
            ++itorUnlit;
    }
}

//****************************************************************************/
void MainWindow::getAndSetFirstDatablock(void)
{
    // Get the name/fullname from the current item in the renderwindow
    Ogre::Item* item = mOgreManager->getOgreWidget(OGRE_WIDGET_RENDERWINDOW)->getItem();
    Ogre::HlmsDatablock* oldDatablock = item->getSubItem(0)->getDatablock();
    Ogre::String oldDatablockName = *oldDatablock->getFullName();
    Ogre::IdString oldDatablockId = oldDatablock->getName();

    // Determine whether the HlmsManager contains a HLMS_PBS datablock or a HLMS_UNLIT datablock.
    // Depending on the result, the datablock of that type is retrieved and set in the mesh (item).
    Ogre::HlmsManager* hlmsManager = mOgreManager->getOgreRoot()->getHlmsManager();
    Ogre::HlmsPbs* hlmsPbs = static_cast<Ogre::HlmsPbs*>( hlmsManager->getHlms(Ogre::HLMS_PBS));
    Ogre::HlmsUnlit* hlmsUnlit = static_cast<Ogre::HlmsUnlit*>( hlmsManager->getHlms(Ogre::HLMS_UNLIT));
    if (hlmsPbs)
    {
        int size = hlmsPbs->getDatablockMap().size();
        //QMessageBox::information(0, QString("info"), QVariant(size).toString());
        if (size> 1)
        {
            // It is a PBS; Note, that there is also a default (so always 1)
            Ogre::Hlms::HlmsDatablockMap::const_iterator itor = hlmsPbs->getDatablockMap().begin();
            Ogre::Hlms::HlmsDatablockMap::const_iterator end  = hlmsPbs->getDatablockMap().end();
            Ogre::HlmsPbsDatablock* newDatablock;
            Ogre::String newDatablockName;
            while( itor != end )
            {
                newDatablock = static_cast<Ogre::HlmsPbsDatablock*>(itor->second.datablock);
                if (newDatablock != hlmsPbs->getDefaultDatablock() && newDatablock != hlmsUnlit->getDefaultDatablock())
                {
                    // Get the first datablock
                    newDatablockName = *newDatablock->getFullName();
                    if (oldDatablockName != newDatablockName)
                    {
                        // Assign the datablock to the item (and destroy the items' old datablock, if still available)
                        item->setDatablock(newDatablock);
                        if (oldDatablock != hlmsPbs->getDefaultDatablock() && oldDatablock != hlmsUnlit->getDefaultDatablock())
                        {
                            if (oldDatablock->getCreator()->getType() == Ogre::HLMS_PBS)
                                hlmsPbs->destroyDatablock(oldDatablockId);
                            else if (hlmsUnlit && oldDatablock->getCreator()->getType() == Ogre::HLMS_UNLIT)
                                hlmsUnlit->destroyDatablock(oldDatablockId);
                        }

                        // Create the node structure
                        QString s = newDatablockName.c_str();
                        mNodeEditorDockWidget->createPbsNodeStructure(s);
                        mPropertiesDockWidget->setTextureTypePropertyVisible(true);
                        mPropertiesDockWidget->setDetailMapPropertyVisible(true);
                        break;
                    }
                }
                ++itor;
            }
            return;
        }
    }

    if (hlmsUnlit)
    {
        int size = hlmsUnlit->getDatablockMap().size();
        //QMessageBox::information(0, QString("info"), QVariant(size).toString());
        if (size > 1)
        {
            // It is an Unlit; Note, that there is also a default (so always 1)
            Ogre::Hlms::HlmsDatablockMap::const_iterator itor = hlmsUnlit->getDatablockMap().begin();
            Ogre::Hlms::HlmsDatablockMap::const_iterator end  = hlmsUnlit->getDatablockMap().end();
            Ogre::HlmsUnlitDatablock* newDatablock;
            Ogre::String newDatablockName;
            while( itor != end )
            {
                newDatablock = static_cast<Ogre::HlmsUnlitDatablock*>(itor->second.datablock);
                if (newDatablock != hlmsPbs->getDefaultDatablock() && newDatablock != hlmsUnlit->getDefaultDatablock())
                {
                    // Get the first datablock
                    newDatablockName = *newDatablock->getFullName();
                    if (oldDatablockName != newDatablockName)
                    {
                        // Assign the datablock to the item (and destroy the items' old datablock, if still available)
                        item->setDatablock(newDatablock);
                        if (oldDatablock != hlmsPbs->getDefaultDatablock() && oldDatablock != hlmsUnlit->getDefaultDatablock())
                        {
                            if (oldDatablock->getCreator()->getType() == Ogre::HLMS_UNLIT)
                                hlmsUnlit->destroyDatablock(oldDatablockId);
                            else if (hlmsPbs && oldDatablock->getCreator()->getType() == Ogre::HLMS_PBS)
                                hlmsPbs->destroyDatablock(oldDatablockId);
                        }

                        // Create the node structure
                        QString s = newDatablockName.c_str();
                        mNodeEditorDockWidget->createUnlitNodeStructure(s);
                        mPropertiesDockWidget->setTextureTypePropertyVisible(false);
                        mPropertiesDockWidget->setDetailMapPropertyVisible(false);
                        break;
                    }
                }
                ++itor;
            }
            return;
        }
    }
}

//****************************************************************************/
void MainWindow::getListOfResources(void)
{
    Ogre::ResourceGroupManager::ResourceManagerIterator it =
        Ogre::ResourceGroupManager::getSingletonPtr()->getResourceManagerIterator();
    while (it.hasMoreElements())
    {
        Ogre::ResourceManager* man = it.getNext();
        Ogre::LogManager::getSingleton().logMessage("Resource Type = " + man->getResourceType());
        Ogre::ResourceManager::ResourceMapIterator mapit = man->getResourceIterator() ;
        while (mapit.hasMoreElements())
        {
            Ogre::ResourcePtr ptr = mapit.getNext();
            Ogre::LogManager::getSingleton().logMessage("Resource Name = " + ptr->getName());
        }
    }
}

//****************************************************************************/
void MainWindow::doSaveDatablockMenuAction(void)
{
    if (mHlmsName.isEmpty())
        doSaveAsDatablockMenuAction();
    else
        saveDatablock();
}

//****************************************************************************/
void MainWindow::doSaveAsDatablockMenuAction(void)
{
    // Get hlms name
    mHlmsName = QString(mNodeEditorDockWidget->getCurrentDatablockName());
    mHlmsName = mHlmsName + QString(".material.json");
    QString fileName = mHlmsName;

    // Save all datablocks to one file
    fileName = QFileDialog::getSaveFileName(this,
                                            QString("Save the Hlms"),
                                            mHlmsName,
                                            QString("Json material (*.json)"));

    if (!fileName.isEmpty())
    {
        mHlmsName = fileName;
        saveDatablock();
    }
}

//****************************************************************************/
void MainWindow::saveDatablock(void)
{
    Ogre::String fname = mHlmsName.toStdString();
    QString baseNameJson = mHlmsName;
    baseNameJson = getBaseFileName(baseNameJson);
    QString thumb = baseNameJson + ".png";
    mOgreManager->getOgreWidget(OGRE_WIDGET_RENDERWINDOW)->saveToFile(THUMBS_PATH + thumb.toStdString());

    Ogre::HlmsManager* hlmsManager = mOgreManager->getOgreRoot()->getHlmsManager();
    if (getCurrentDatablockType() == EditorHlmsTypes::HLMS_PBS)
    {
        hlmsManager->saveMaterials (Ogre::HLMS_PBS, fname);
        mMaterialBrowser->addMaterial(baseNameJson, mHlmsName, thumb, HLMS_PBS);
    }
    else if (getCurrentDatablockType() == EditorHlmsTypes::HLMS_UNLIT)
    {
        hlmsManager->saveMaterials (Ogre::HLMS_UNLIT, fname);
        mMaterialBrowser->addMaterial(baseNameJson, mHlmsName, thumb, HLMS_UNLIT);
    }
}

//****************************************************************************/
void MainWindow::loadMaterialBrowserCfg(void)
{
    QVector<Magus::QtResourceInfo*> resources;
    QFile file(FILE_MATERIAL_BROWSER);
    QString line;
    if (file.open(QFile::ReadOnly))
    {
        QTextStream readFile(&file);
        Magus::QtResourceInfo* info;
        while (!readFile.atEnd())
        {
            line = readFile.readLine();
            QStringList elements = line.split('\t', QString::SkipEmptyParts);

            if (elements.size() == 6)
            {
                info = new Magus::QtResourceInfo();
                info->topLevelId = QVariant(elements[0]).toInt();
                info->parentId = QVariant(elements[1]).toInt();
                info->resourceId = QVariant(elements[2]).toInt();
                info->resourceType = QVariant(elements[3]).toInt();
                info->resourceName = elements[4];
                info->fullQualifiedName = elements[5];

                if (info->topLevelId == TOOL_SOURCES_LEVEL_X000_PBS &&
                        info->resourceType == TOOL_RESOURCETREE_KEY_TYPE_TOPLEVEL_GROUP)
                    info->iconName = ICON_PBS_DATABLOCK_NO_PATH;
                else if (info->topLevelId == TOOL_SOURCES_LEVEL_X000_PBS &&
                         info->resourceType == TOOL_RESOURCETREE_KEY_TYPE_GROUP)
                    info->iconName = ICON_PBS_DATABLOCK_SMALL_NO_PATH;

                if (info->topLevelId == TOOL_SOURCES_LEVEL_X000_UNLIT &&
                        info->resourceType == TOOL_RESOURCETREE_KEY_TYPE_TOPLEVEL_GROUP)
                    info->iconName = ICON_UNLIT_DATABLOCK_NO_PATH;
                else if (info->topLevelId == TOOL_SOURCES_LEVEL_X000_UNLIT &&
                         info->resourceType == TOOL_RESOURCETREE_KEY_TYPE_GROUP)
                    info->iconName = ICON_UNLIT_DATABLOCK_SMALL_NO_PATH;

                resources.append(info);
            }
        }

        // In case the file is empty or contains garbage, add toplevel items
        if (resources.size() == 0)
        {
             info = new QtResourceInfo();
             info->topLevelId = TOOL_SOURCES_LEVEL_X000_PBS;
             info->parentId = 0;
             info->resourceId = TOOL_SOURCES_LEVEL_X000_PBS;
             info->resourceName = QString("PBS");
             info->fullQualifiedName = QString("PBS");
             info->resourceType = TOOL_RESOURCETREE_KEY_TYPE_TOPLEVEL_GROUP;
             info->iconName = ICON_PBS_DATABLOCK_NO_PATH;
             resources.append(info);

             info = new QtResourceInfo();
             info->topLevelId = TOOL_SOURCES_LEVEL_X000_UNLIT;
             info->parentId = 0;
             info->resourceId = TOOL_SOURCES_LEVEL_X000_UNLIT;
             info->resourceName = QString("Unlit");
             info->fullQualifiedName = QString("Unlit");
             info->resourceType = TOOL_RESOURCETREE_KEY_TYPE_TOPLEVEL_GROUP;
             info->iconName = ICON_UNLIT_DATABLOCK_NO_PATH;
             resources.append(info);
        }

        // Set the resources
        mMaterialBrowser->setResources(resources);
        file.close();
    }
}

//****************************************************************************/
void MainWindow::doQuitMenuAction(void)
{
    close();
}

//****************************************************************************/
void MainWindow::doMaterialBrowserOpenMenuAction(void)
{
    if (mMaterialBrowser->exec())
    {
        // A change is made in the material browser and accepted with ok or double click on an item
        QString fileName = mMaterialBrowser->getSelectedJsonFileName();
        if (!fileName.isEmpty())
            loadDatablock(fileName);

        // Save all current settings
        saveMaterialBrowserCfg();
    }
    else
        loadMaterialBrowserCfg(); // Reverses all changes
}

//****************************************************************************/
void MainWindow::saveMaterialBrowserCfg(void)
{
    // Save all current settings
    const QVector<Magus::QtResourceInfo*>& resources = mMaterialBrowser->getResources();
    saveResources(FILE_MATERIAL_BROWSER, resources);
}

//****************************************************************************/
void MainWindow::doMaterialBrowserAddMenuAction(void)
{
    if (mHlmsName.isEmpty())
        QMessageBox::information(0, QString("Error"), QString("No filename. The Hlms must be saved first"));
    else
    {
        QString baseNameJson = mHlmsName;
        baseNameJson = getBaseFileName(baseNameJson);
        QString thumb = baseNameJson + ".png";
        mOgreManager->getOgreWidget(OGRE_WIDGET_RENDERWINDOW)->saveToFile(THUMBS_PATH + thumb.toStdString());

        if (getCurrentDatablockType() == EditorHlmsTypes::HLMS_PBS)
            mMaterialBrowser->addMaterial(baseNameJson, mHlmsName, thumb, HLMS_PBS);
        else if (getCurrentDatablockType() == EditorHlmsTypes::HLMS_UNLIT)
            mMaterialBrowser->addMaterial(baseNameJson, mHlmsName, thumb, HLMS_UNLIT);

        saveMaterialBrowserCfg();
    }
}

//****************************************************************************/
void MainWindow::doTextureBrowserImportMenuAction(void)
{
    QString textureFolder;
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::Directory);
    if (dialog.exec())
    {
        QStringList fileNames = dialog.selectedFiles();
        textureFolder = fileNames.at(0);

        // Add all texture files to a group in mTextureDockWidget
        //QString path;
        QString fileName;

        QDirIterator dirIt(textureFolder, QDirIterator::Subdirectories);
        while (dirIt.hasNext())
        {
            dirIt.next();
            if (QFileInfo(dirIt.filePath()).isFile())
            {
                fileName = dirIt.fileName();
                if (Magus::isTypeBasedOnExtension(fileName, Magus::MAGUS_SUPPORTED_IMAGE_FORMATS, Magus::MAGUS_SUPPORTED_IMAGE_FORMATS_LENGTH))
                {
                    fileName = textureFolder + QString("/") + fileName;
                    mTextureDockWidget->addTextureFile(fileName, GROUP_NAME_IMPORTED_TEXTURES); // Add it to a group
                }
            }
        }

        handleTextureMutationOccured();
    }
}

//****************************************************************************/
void MainWindow::doTextureBrowserAddImageMenuAction(void)
{
    QString fileName;
    QStringList fileNames;
    fileNames = QFileDialog::getOpenFileNames(this,
                                             QString("Select texture/image file(s)"),
                                             QString(""),
                                             QString("JPEG (*.jpg *.jpeg);;"
                                                     "PNG (*.png);;"
                                                     "DDS (*.dds);;"
                                                     "All files (*.*)"));
    foreach (fileName, fileNames)
    {
        if (!fileName.isEmpty())
            mTextureDockWidget->addTextureFile(fileName);
    }

    handleTextureMutationOccured();
}

//****************************************************************************/
void MainWindow::doResetWindowLayoutMenuAction(void)
{
    mRenderwindowDockWidget->show();
    addDockWidget(Qt::LeftDockWidgetArea, mRenderwindowDockWidget);
    mPropertiesDockWidget->show();
    addDockWidget(Qt::LeftDockWidgetArea, mPropertiesDockWidget);

    mTextureDockWidget->show();
    addDockWidget(Qt::RightDockWidgetArea, mTextureDockWidget);
    mNodeEditorDockWidget->show();
    addDockWidget(Qt::RightDockWidgetArea, mNodeEditorDockWidget);
}

//****************************************************************************/
void MainWindow::handleTextureDoubleClicked(const QString& fileName, const QString& baseName)
{
    if (Magus::fileExist(fileName))
    {
        mNodeEditorDockWidget->newSamplerblockNode(fileName);
    }
    else
    {
        QMessageBox::StandardButton reply = fileDoesNotExistsWarning(fileName);
        if (reply == QMessageBox::Yes)
        {
            mTextureDockWidget->deleteTexture(fileName);
        }
    }
}

//****************************************************************************/
void MainWindow::handleCustomContextMenuItemSelected(const QString& menuItemText)
{
    if (menuItemText == ACTION_IMPORT_TEXTURES_FROM_DIR)
        doTextureBrowserImportMenuAction();
    else if (menuItemText == ACTION_ADD_TEXTURES)
        doTextureBrowserAddImageMenuAction();
}

//****************************************************************************/
void MainWindow::handleTextureMutationOccured(void)
{
    // Do not save immediately, but only after some time; this is to prevent that saveTextureBrowserCfg
    // is called for every mutation in the texture tree (deletion of 100 textures in one go
    // triggers handleTextureMutationOccured also 100 times. We don't want to save 100 times).
    // This is the reason that a QTimer is used.
    if (mSaveTextureBrowserTimerActive)
        return;

    QTimer::singleShot(1000, this, SLOT(saveTextureBrowserCfg()));
    mSaveTextureBrowserTimerActive = true;
}

//****************************************************************************/
void MainWindow::saveTextureBrowserCfg(void)
{
    mSaveTextureBrowserTimerActive = false;
    const QVector<Magus::QtResourceInfo*>& resources = mTextureDockWidget->getResources();
    saveResources(FILE_TEXTURE_BROWSER, resources);
}

//****************************************************************************/
void MainWindow::loadTextureBrowserCfg(void)
{
    QVector<Magus::QtResourceInfo*> resources;
    QFile file(FILE_TEXTURE_BROWSER);
    QString line;
    if (file.open(QFile::ReadOnly))
    {
        QTextStream readFile(&file);
        Magus::QtResourceInfo* info;
        while (!readFile.atEnd())
        {
            line = readFile.readLine();
            QStringList elements = line.split('\t', QString::SkipEmptyParts);

            if (elements.size() == 6)
            {
                info = new Magus::QtResourceInfo();
                info->topLevelId = QVariant(elements[0]).toInt();
                info->parentId = QVariant(elements[1]).toInt();
                info->resourceId = QVariant(elements[2]).toInt();
                info->resourceType = QVariant(elements[3]).toInt();
                info->resourceName = elements[4];
                info->fullQualifiedName = elements[5];

                if (info->topLevelId == TOOL_SOURCES_LEVEL_X000_TEXTURE &&
                        info->resourceType == TOOL_RESOURCETREE_KEY_TYPE_TOPLEVEL_GROUP)
                    info->iconName = ICON_TEXTURE_NO_PATH;
                else if (info->topLevelId == TOOL_SOURCES_LEVEL_X000_TEXTURE &&
                         info->resourceType == TOOL_RESOURCETREE_KEY_TYPE_GROUP)
                    info->iconName = ICON_TEXTURE_SMALL_NO_PATH;

                resources.append(info);
            }
        }

        // In case the file is empty or contains garbage, add toplevel item
        if (resources.size() == 0)
        {
             info = new QtResourceInfo();
             info->topLevelId = TOOL_SOURCES_LEVEL_X000_TEXTURE;
             info->parentId = 0;
             info->resourceId = TOOL_SOURCES_LEVEL_X000_TEXTURE;
             info->resourceName = QString("Textures");
             info->fullQualifiedName = QString("Textures");
             info->resourceType = TOOL_RESOURCETREE_KEY_TYPE_TOPLEVEL_GROUP;
             info->iconName = ICON_TEXTURE_NO_PATH;
             resources.append(info);
        }

        // Set the resources
        mTextureDockWidget->setResources(resources);
        file.close();
    }
}

//****************************************************************************/
void MainWindow::saveResources(const QString& fileName, const QVector<Magus::QtResourceInfo*>& resources)
{
    // Save state of a resoruces from a resourcetree widget
    QFile file(fileName);
    if (file.open(QFile::WriteOnly|QFile::Truncate))
    {
        QTextStream stream(&file);
        QVectorIterator<Magus::QtResourceInfo*> it(resources);
        it.toFront();
        Magus::QtResourceInfo* info;
        while (it.hasNext())
        {
            // Write a line to the cfg file
            info = it.next();
            stream << info->topLevelId
                   << "\t"
                   << info->parentId
                   << "\t"
                   << info->resourceId
                   << "\t"
                   << info->resourceType
                   << "\t"
                   << info->resourceName
                   << "\t"
                   << info->fullQualifiedName
                   << "\n";
        }
        file.close();
    }
}

//****************************************************************************/
void MainWindow::update(void)
{
    if (mOgreManager)
        mOgreManager->renderOgreWidgetsOneFrame();

    if (mFirst)
    {
        // Only do this once, otherwise it is not possible to change the widget manually (by means of keyboard)
        mRenderwindowDockWidget->updateTransformationWidgetFromOgreWidget();
        mFirst = false;
    }
}

//****************************************************************************/
void MainWindow::initDatablocks(void)
{
    destroyAllDatablocks();
    mHlmsName = QString("");
}

//****************************************************************************/
EditorHlmsTypes MainWindow::getCurrentDatablockType(void)
{
    return mNodeEditorDockWidget->getCurrentDatablockType();
}

//****************************************************************************/
QMessageBox::StandardButton MainWindow::fileDoesNotExistsWarning(const QString& fileName)
{
    return QMessageBox::question(0,
                                 "Warning",
                                 fileName + QString(" does not exist. Remove it from the texture browser?"),
                                 QMessageBox::Yes|QMessageBox::No);
}
