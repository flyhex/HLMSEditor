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
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDir>
#include <QLabel>
#include <QImageReader>
#include <QTextStream>
#include <QListWidgetItem>
#include <QProcess>
#include <QDrag>
#include <QMimeData>

#include "tool_generic_assetwidget.h"

namespace Magus
{
    //****************************************************************************/
    QtGenericAssetAndText::QtGenericAssetAndText(const QPixmap& assetPixmap,
                                                 const QString& name,
                                                 const QString& baseName,
                                                 const QSize& size,
                                                 QWidget* parent) :
        QWidget(parent)
    {
        setContentsMargins(-8, -8, -8, -8);
        setMinimumSize(size);
        setMaximumSize(size);
        QHBoxLayout* mainLayout = new QHBoxLayout;
        QVBoxLayout* assetAndNameLayout = new QVBoxLayout;
        mPixmapGenericAsset = assetPixmap;

        mName = name;
        mBaseName = baseName;
        mBaseNameEdit = new QLineEdit;
        mBaseNameEdit->setText(mBaseName);
        mBaseNameEdit->setEnabled(false);

        mTextureLabel = new QLabel();
        mTextureLabel->setPixmap(mPixmapGenericAsset);
        mTextureLabel->setScaledContents(true);
        setMouseTracking(true);

        // Layout
        assetAndNameLayout->addWidget(mTextureLabel, 1000);
        assetAndNameLayout->addWidget(mBaseNameEdit, 1);
        mainLayout->addLayout(assetAndNameLayout);
        setLayout(mainLayout);
    }

    //****************************************************************************/
    QtGenericAssetAndText::~QtGenericAssetAndText(void)
    {
        // drag and mimeData created in mouseMoveEvent are automatically deleted when the QtGenericAssetAndText object is deleted
    }

    //****************************************************************************/
    void QtGenericAssetAndText::mouseMoveEvent(QMouseEvent *event)
    {
        // If not left button - return
        if (!(event->buttons() & Qt::LeftButton))
            return;

        // Start drag
        QDrag* drag = new QDrag(this);
        QMimeData* mimeData = new QMimeData;
        drag->setMimeData(mimeData);
        mimeData->setText(mName);
        drag->exec(Qt::CopyAction | Qt::MoveAction);
    }

    //****************************************************************************/
    //****************************************************************************/
    //****************************************************************************/
    QtGenericAssetListWidget::QtGenericAssetListWidget(QWidget* parent) : QListWidget(parent)
    {
        setMouseTracking(true);
        setAcceptDrops(true);
        setDropIndicatorShown(true);
    }

    //****************************************************************************/
    QtGenericAssetListWidget::~QtGenericAssetListWidget(void)
    {
    }

    //****************************************************************************/
    void QtGenericAssetListWidget::keyPressEvent(QKeyEvent* event)
    {
        switch (event->key())
        {
            case Qt::Key_Delete:
            {
                if (count() > 0)
                {
                    QListWidgetItem* item = currentItem();
                    if (item)
                    {
                        QWidget* widget = itemWidget(item);
                        if (widget)
                        {
                            int r = row(item);
                            QtGenericAssetAndText* assetAndText = static_cast<QtGenericAssetAndText*>(widget);
                            QString name = assetAndText->mName;
                            QString baseName = assetAndText->mBaseName;
                            removeItemWidget(item);
                            takeItem(r);
                            emit assetDeleted(name, baseName);
                        }
                    }
                }
            }
            break;
        }

        event->accept();
    }

    //****************************************************************************/
    void QtGenericAssetListWidget::dropEvent(QDropEvent* event)
    {
        const QMimeData *mimeData = event->mimeData();
        if (mimeData->hasUrls())
        {
            QList<QUrl> urlList = mimeData->urls();
            for (int i = 0; i < urlList.size(); ++i)
            {
                QString baseName = urlList.at(i).fileName();
                if (isTypeBasedOnExtension(baseName, mAllowedExtensions, mAllowedExtensionsLength))
                {
                    QString name = urlList.at(i).path();
                    stripLeadingSlashes(name);
                    emit fileDropped(name, baseName);
                }
            }
        }
        event->acceptProposedAction();
    }

    //****************************************************************************/
    void QtGenericAssetListWidget::setAllowedExtensions(const QString ext[], int arrayLength)
    {
        for (int i = 0; i < arrayLength; ++i)
        {
            //QMessageBox::information(0, QString("test"), ext[i]); // test
            mAllowedExtensions[i] = ext[i];
        }

        mAllowedExtensionsLength = arrayLength;
    }

    //****************************************************************************/
    void QtGenericAssetListWidget::dragEnterEvent(QDragEnterEvent *event)
    {
        event->acceptProposedAction();
    }

    //****************************************************************************/
    void QtGenericAssetListWidget::dragMoveEvent(QDragMoveEvent *event)
    {
        event->acceptProposedAction();
    }

    //****************************************************************************/
    //****************************************************************************/
    //****************************************************************************/
    QtGenericAssetWidget::QtGenericAssetWidget(QPixmap defaultPixmap, bool viewEnabled, QWidget* parent) : QWidget(parent)
    {
        mNameAsset = QString("");
        mBaseNameAsset = QString("");
        mSystemCommandEditAsset = QString("");
        mDefaultPixmapAsset = defaultPixmap;
        setWindowTitle(QString("Texture selection"));
        mTextureSize = QSize(128, 128);
        mOriginIsFile = true;
        QHBoxLayout* mainLayout = new QHBoxLayout;
        QVBoxLayout* textureSelectionLayout = new QVBoxLayout;

        // Define selection widget (QtGenericAssetListWidget)
        mSelectionList = new QtGenericAssetListWidget();
        mSelectionList->setViewMode(QListView::ListMode);
        mSelectionList->setWrapping(true);
        mSelectionList->setWordWrap(true);
        mSelectionList->setSpacing(0);
        mSelectionList->setUniformItemSizes(true);
        mSelectionList->setMovement(QListView::Snap);
        mSelectionList->setFlow(QListView::LeftToRight);
        connect(mSelectionList, SIGNAL(fileDropped(QString,QString)), this, SLOT(handleFileDropped(QString,QString)));
        connect(mSelectionList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(handleSelected(QListWidgetItem*)));
        connect(mSelectionList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(handleDoubleClicked(QListWidgetItem*)));
        connect(mSelectionList, SIGNAL(itemEntered(QListWidgetItem*)), this, SLOT(handleMouseOver(QListWidgetItem*)));
        connect(mSelectionList, SIGNAL(assetDeleted(QString,QString)), this, SLOT(handleAssetDeleted(QString,QString)));

        // Textviewer
        mTextViewer = new QPlainTextEdit();
        mTextViewer->setWindowFlags(Qt::WindowStaysOnTopHint);
        mViewEnabled = viewEnabled;

        // Layout
        textureSelectionLayout->addWidget(mSelectionList);
        mainLayout->addLayout(textureSelectionLayout);
        setLayout(mainLayout);
    }

    //****************************************************************************/
    QtGenericAssetWidget::~QtGenericAssetWidget(void)
    {
    }

    //****************************************************************************/
    void QtGenericAssetWidget::addAsset(const QPixmap& assetPixmap, const QString& name, const QString& baseName)
    {
        QtGenericAssetAndText* assetAndText = new QtGenericAssetAndText(assetPixmap, name, baseName, mTextureSize, this);
        QListWidgetItem* item = new QListWidgetItem();
        item->setSizeHint(mTextureSize); // Must be present, otherwise the widget is not shown
        mSelectionList->addItem(item);
        mSelectionList->setItemWidget(item, assetAndText);
    }

    //****************************************************************************/
    bool QtGenericAssetWidget::assetExists(const QString& name, bool nameIsFullName)
    {
        QtGenericAssetAndText* assetAndText;
        QWidget* widget;
        int row;
        QList<QListWidgetItem*> list = mSelectionList->findItems(QString("*"), Qt::MatchWildcard);
        foreach (QListWidgetItem* item, list)
        {
            widget = mSelectionList->itemWidget(item);
            if (widget)
            {
                assetAndText = static_cast<QtGenericAssetAndText*>(widget);
                if ((assetAndText->mName == name && nameIsFullName) ||
                    (assetAndText->mBaseName == name && !nameIsFullName))
                    return true;
            }
        }
        return false;
    }

    //****************************************************************************/
    void QtGenericAssetWidget::deleteAsset(const QString& name, bool nameIsFullName)
    {
        QtGenericAssetAndText* assetAndText;
        QWidget* widget;
        int row;
        QList<QListWidgetItem*> list = mSelectionList->findItems(QString("*"), Qt::MatchWildcard);
        foreach (QListWidgetItem* item, list)
        {
            widget = mSelectionList->itemWidget(item);
            if (widget)
            {
                assetAndText = static_cast<QtGenericAssetAndText*>(widget);
                if ((assetAndText->mName == name && nameIsFullName) ||
                    (assetAndText->mBaseName == name && !nameIsFullName))
                {
                    row = mSelectionList->row(item);
                    mSelectionList->removeItemWidget(item);
                    mSelectionList->takeItem(row);
                    return;
                }
            }
        }
    }

    //****************************************************************************/
    void QtGenericAssetWidget::deleteAsset(const QString& name, const QString& baseName)
    {
        QtGenericAssetAndText* assetAndText;
        QWidget* widget;
        int row;
        QList<QListWidgetItem*> list = mSelectionList->findItems(QString("*"), Qt::MatchWildcard);
        foreach (QListWidgetItem* item, list)
        {
            widget = mSelectionList->itemWidget(item);
            if (widget)
            {
                assetAndText = static_cast<QtGenericAssetAndText*>(widget);
                if (assetAndText->mName == name && assetAndText->mBaseName == baseName)
                {
                    row = mSelectionList->row(item);
                    mSelectionList->removeItemWidget(item);
                    mSelectionList->takeItem(row);
                    return;
                }
            }
        }
    }

    //****************************************************************************/
    const QString& QtGenericAssetWidget::getNameAsset(void)
    {
        return mNameAsset;
    }

    //****************************************************************************/
    const QString& QtGenericAssetWidget::getBaseNameAsset(void)
    {
        return mBaseNameAsset;
    }

    //****************************************************************************/
    void QtGenericAssetWidget::setOriginIsFile(bool originIsFile)
    {
        mOriginIsFile = originIsFile;
    }

    //****************************************************************************/
    void QtGenericAssetWidget::clearContent(void)
    {
        mSelectionList->clear();
    }

    //****************************************************************************/
    void QtGenericAssetWidget::handleSelected(QListWidgetItem* item)
    {
        QWidget* widget = mSelectionList->itemWidget(item);
        if (widget)
        {
            QtGenericAssetAndText* assetAndText = static_cast<QtGenericAssetAndText*>(widget);
            mNameAsset = assetAndText->mName;
            mBaseNameAsset = assetAndText->mBaseName;
            emit selected(assetAndText->mName, assetAndText->mBaseName);
        }
    }

    //****************************************************************************/
    void QtGenericAssetWidget::handleDoubleClicked(QListWidgetItem* item)
    {
        QWidget* widget = mSelectionList->itemWidget(item);
        if (widget)
        {
            QtGenericAssetAndText* assetAndText = static_cast<QtGenericAssetAndText*>(widget);
            if (mViewEnabled)
            {
                if (mSystemCommandEditAsset.isEmpty())
                    loadFileInViewer(assetAndText->mName, assetAndText->mBaseName); // Currently only viewing files is implemented and no other sources
                else
                {
                    QProcess p;
                    QStringList sl;
                    sl.append(assetAndText->mName);
                    p.startDetached(mSystemCommandEditAsset, sl);
                }
            }
            emit doubleClicked(assetAndText->mName, assetAndText->mBaseName);
        }
    }

    //****************************************************************************/
    void QtGenericAssetWidget::handleFileDropped(const QString& name, const QString& baseName)
    {
        addAsset(mDefaultPixmapAsset, name, baseName);
        emit fileDropped(name, baseName);
    }

    //****************************************************************************/
    void QtGenericAssetWidget::handleMouseOver(QListWidgetItem* item)
    {
        QWidget* widget = mSelectionList->itemWidget(item);
        if (widget)
        {
            QtGenericAssetAndText* assetAndText = static_cast<QtGenericAssetAndText*>(widget);
            QString name = assetAndText->mName;
            mSelectionList->setToolTip(name);
        }
    }

    //****************************************************************************/
    void QtGenericAssetWidget::handleAssetDeleted(const QString& name, const QString& baseName)
    {
        emit assetDeleted(name, baseName);
    }

    //****************************************************************************/
    void QtGenericAssetWidget::loadFileInViewer(const QString& fileName, const QString& baseFileName)
    {
        QFile file(fileName);
        if(!file.exists())
            return;

        setCursor(Qt::WaitCursor);
        QString line;
        mTextViewer->clear();
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream stream(&file);
            while (!stream.atEnd())
            {
                line = stream.readLine();
                mTextViewer->appendPlainText(line);
            }
        }
        file.close();
        mTextViewer->moveCursor(QTextCursor::Start);
        mTextViewer->show();
        mTextViewer->setFocus();
        setCursor(Qt::ArrowCursor);
        mTextViewer->setWindowTitle(baseFileName);
    }

    //****************************************************************************/
    void QtGenericAssetWidget::setTextureSize (QSize size)
    {
        mTextureSize = size;
    }

    //****************************************************************************/
    void QtGenericAssetWidget::filter(const QString& pattern)
    {
        QtGenericAssetAndText* assetAndText;
        QWidget* widget;
        QString name;
        QList<QListWidgetItem*> list = mSelectionList->findItems(QString("*"), Qt::MatchWildcard);
        foreach (QListWidgetItem* item, list)
        {
            widget = mSelectionList->itemWidget(item);
            if (widget)
            {
                assetAndText = static_cast<QtGenericAssetAndText*>(widget);
                name = assetAndText->mBaseName;
                name = name.toLower();
                if (!name.contains(pattern))
                    item->setHidden(true);
            }
        }
    }

    //****************************************************************************/
    void QtGenericAssetWidget::resetFilter(void)
    {
        QList<QListWidgetItem*> list = mSelectionList->findItems(QString("*"), Qt::MatchWildcard);
        foreach (QListWidgetItem* item, list)
            item->setHidden(false);
    }

    //****************************************************************************/
    void QtGenericAssetWidget::setDropFilesAllowed(bool allowed)
    {
        mSelectionList->setMouseTracking(allowed);
        mSelectionList->setAcceptDrops(allowed);
        mSelectionList->setDropIndicatorShown(allowed);
    }

    //****************************************************************************/
    void QtGenericAssetWidget::setAllowedExtensions(const QString ext[], int arrayLength)
    {
        mSelectionList->setAllowedExtensions(ext, arrayLength);
    }

    //****************************************************************************/
    void QtGenericAssetWidget::setSystemCommandEditAsset(const QString& systemCommand)
    {
        mSystemCommandEditAsset = systemCommand;
    }
}
