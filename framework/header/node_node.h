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

#ifndef MAGUS_NODE_H
#define MAGUS_NODE_H

#include <QGraphicsItem>
#include <QGraphicsPathItem>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QBrush>
#include <QPen>
#include "node_constants.h"

QT_BEGIN_NAMESPACE

QT_END_NAMESPACE

namespace Magus
{
    class QtPort;
    class QtPortType;
    class QtConnection;
    class QtNodeEditor;

    /****************************************************************************
    QtNode represents a Node-class which is visualised in a QGraphicsScene.
    ***************************************************************************/
    class QtNode : public QObject, public QGraphicsPathItem
    {
        Q_OBJECT

        public:
            void* mUserData;
            QtConnection* mActiveConnection;
            QtNode(QString title, QGraphicsItem* parent = 0);
            virtual ~QtNode(void);
            void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

            // Set the editor; this is called (by the editor) as soon as a node is added to the scene
            // Do not use this (only for internal use)
            void _setEditor(QtNodeEditor* editor);

            // Set the scene; this is called (by the editor) as soon as a node is added to the scene
            // Do not use this (only for internal use)
            void _setScene(QGraphicsScene* scene);

            // Called from the QNodeEditor when the node is selected.
            // Do not use this (only for internal use)
            void _emitNodeSelected(void);

            // Called from the QNodeEditor when a connection is deleted
            // Do not use this (only for internal use)
            void _emitConnectionDeleted(QtPort* port);

            // Called from the QNodeEditor; used for adding a node to a compound
            // Overridden
            void setParentItem(QGraphicsItem* parent);

            // Called from the QNodeEditor; used for removing a node from a compound
            void _restoreOriginalParentItem(void);

            // To be called just before the node is removed from te scene
            virtual void _prepareDelete();

            // Set the node - including its connections - visible / invisible
            // Overridden
            void setVisible(bool visible);

            // Determines whether a node is automatically sized when ports are added etc.
            void setAutoSize (bool autoSize);
            bool isAutoSize (void) const;

            // Return the title of the node
            const QString& getTitle(void) const {return mTitle;}

            // Set the type of the node
            void setType(unsigned int nodeType) {mNodeType = nodeType;}

            // Return the type of the node
            unsigned int getType(void) const {return mNodeType;}

            // Although the width of the node is automatically adjusted to its content, it is possible
            // to change (override) the width manually
            void setWidth(qreal width);

            // Set the height of the header
            void setHeaderHeight(qreal headerHeight);

            // Although the body height of the node is automatically adjusted to its content, it is possible
            // to change (override) the body height manually
            void setBodyHeight(qreal bodyHeight);

            // Get the dimensions of the node (width and total height)
            qreal getWidth(void) const;
            qreal getHeigth(void) const;

            // Scale the node
            void setZoom(qreal zoom);

            // Set the color of the header; this results in a gradient with grey
            void setHeaderColor(const QColor& color);

            // Set the color of the title in the header
            void setTitleColor(const QColor& color);

            // Set the color of the name of all ports
            void setPortNameColor(const QColor& color);

            // Align the text of the header (default is center)
            void alignTitle(Alignment alignment);

            // Set the size of the icon in the header
            void setIconSize(qreal size);

            // Set the icon, associated with the title in the nodes' header
            void setHeaderTitleIcon(const QString& fileNameIcon);

            // Set the icon, associated with action 1
            void setAction1Icon(const QString& fileNameIcon);

            // Set the icon, associated with action 2
            void setAction2Icon(const QString& fileNameIcon);

            /* Create a port
             * portId:          Identification (handle) of the port.
             * portName:        The name of the port. This is also the text displayed.
             * portType:        Define the type of port. By means of the portType it is also possible to define whether it is
             *                  possible to connect this port to another port (of another or the same type). By default, 2 prefab
             *                  portTypes exist, a QtInputPortType and a QtOutputPortType. It is also possible to create your own
             *                  port type.
             * portColour:      The color of a port.
             * portShape:       A port can be shaped circular or as a square.
             * alignement:      A port can be positioned left, right or in the middle of a node.
             * connectionColor: If connecting is started from this port, it gets the color defined by 'connectionColor'.
             *                  The created port is in that case the 'base port' of the connection.
            */
            QtPort* createPort(unsigned int portId,
                                const QString& portName,
                                QtPortType portType,
                                QColor portColour,
                                QtPortShape portShape,
                                Alignment alignement,
                                QColor connectionColor = Qt::black);

            // Add an image to the node; the image is adjusted to the size of the node and position at the top
            // (under the header)
            void setImage(const QString& fileNameImage);
            void setImage(const QPixmap& pixmap);

            // Add an image to the node; copy fromt the original pixmap*
            void copyImage(const QPixmap* pixmap);

            // Add an image to the node; the node is adjusted to the size of the image
            void createImage(const QString& fileNameImage, QSize size);

            // Return all nodes connected to this node
            QVector<QtNode*> getNodes (void);

            // Return the port, based on the name
            QtPort* getPort (const QString& portName);

            // Return the port, based on the id
            QtPort* getPort (unsigned int portId);

            // Return a port that has no connection. The first free port from portIdFrom to portIdTo (included) is returned
            QtPort* getFirstFreePort (unsigned int portIdFrom, unsigned int portIdTo);

            // Return the port, based on the name
            // In case there are multiple ports with the same name, the first occurence is returned; use the occurence
            // argument in case of more than one port with the same name; occurence starts with 1
            QtPort* getPort (const QString& portName, unsigned int occurence);

            // Return all ports of a node
            QVector<QtPort*> getPorts (void);

            // If there are multiple ports with the same name, they can also be returned as a vector
            QVector<QtPort*> getPorts (const QString& portName);

            // Returns true, if a given port is part of 'this' node
            bool isPortOfThisNode(QtPort* port);
            bool isPortOfThisNode(unsigned int portId);
            bool isPortOfThisNode(const QString& portName);

            // Returns true, if a given connection is connected to a port of 'this' node
            bool isConnectionConnectedToThisNode(QtConnection* connection);

            // Return the node that is connected to 'this' node by means of a given port
            // (identified by its name or a pointer to the port)
            // Returns 0 if there is no connection
            QtNode* getNodeConnectedToPort (QtPort* port);

            // Return the node that is connected to 'this' node by means of a given portId
            QtNode* getNodeConnectedToPort (unsigned int portId);

            // Return the node that is connected to 'this' node by means of a given portName
            // Returns 0 if there is no connection
            QtNode* getNodeConnectedToPort (const QString& portName);

            // Return the node that is connected to 'this' node by means of a given portName
            // In case there are multiple ports with the same name, the first occurence is returned; use the occurence
            // argument in case of more than one port with the same name; occurence starts with 1
            // Returns 0 if there is no connection
            QtNode* getNodeConnectedToPort (const QString& portName, unsigned int occurence);

            // If there are multiple ports with the same name, the nodes can also be returned as a vector
            QVector<QtNode*> getNodesConnectedToPorts (const QString& portName);

            // Return the port that is connected to the port of 'this' node
            // Returns 0 if there is no connection
            QtPort* getPortConnectedToPort (QtPort* port);

            // Return the port that is connected to the port of 'this' node
            // Returns 0 if there is no connection
            QtPort* getPortConnectedToPort (unsigned int portId);

            // Return the port that is connected to the port of 'this' node
            // Returns 0 if there is no connection
            QtPort* getPortConnectedToPort (const QString& portName);

            // Return the port that is connected to the port of 'this' node
            // In case there are multiple ports with the same name, the first occurence is returned; use the occurence
            // argument in case of more than one port with the same name; occurence starts with 1
            // Returns 0 if there is no connection
            QtPort* getPortConnectedToPort (const QString& portName, unsigned int occurence);

            // If there are multiple ports with the same name, the ports can also be returned as a vector
            QVector<QtPort*> getPortsConnectedToPorts (const QString& portName);

            // Create an active connection that must be connected to another node (using the mouse)
            // port = The base port to which the connection is attached; this is also the start position
            // pos = End position
            QtConnection* createActiveConnection(QtPort* port, QPointF pos);

            // Delete the connection that is currently active
            void deleteActiveConnection(void);

            // Delete all connections, connected to this node
            void deleteAllConnections(void);

            // Select or deselect all connections; this only applies to finalized (established) connections
            void selectConnections(bool selected);

            // Make a connection between nodes.
            // This function makes a connection between to the first free port in the range portIdFrom-portIdTo
            // and the port defined with targetPortId. Only ports that are allowed to be connected are actually
            // connected.
            bool connectNode (unsigned int portIdFrom,
                              unsigned int portIdTo,
                              QtNode* targetNode,
                              unsigned int targetPortId);

            // Make a connection between nodes. These functions do not use a range of port id's,
            // but the identification of a specific port id.
            bool connectNode (unsigned int portId, QtNode* targetNode, unsigned int targetPortId);
            bool connectNode (const QString& portName, QtNode* targetNode, const QString& targetPortName);
            bool connectNode (unsigned int portId, QtNode* targetNode, const QString& targetPortName);
            bool connectNode (const QString& portName, QtNode* targetNode, unsigned int targetPortId);

            // Called from the QNodeEditor when either a left mouse click on the action1 or action2 button
            // has been done. This handler function performs default behaviour, but it is possible to overload
            // these functions. Default behaviour:
            // Click action1 button (mouseLeftClickAction1ButtonHandler): Toggle collapse and expand the node
            // Click action2 button (mouseLeftClickAction2ButtonHandler): Close (delete) the node
            virtual void mouseLeftClickAction1ButtonHandler(QGraphicsSceneMouseEvent* mouseEvent, QGraphicsItem* item);
            virtual void mouseLeftClickAction2ButtonHandler(QGraphicsSceneMouseEvent* mouseEvent, QGraphicsItem* item);

            // Called from the QNodeEditor when either a left mouse click on the QtNode has taken place,
            // or on one of its child QGraphicsItems. The mouseLeftClickHandler function performs default
            // behaviour, but it is possible to overload this function.
            virtual bool mouseLeftClickHandler(QGraphicsSceneMouseEvent* mouseEvent,
                                               QGraphicsItem* item,
                                               unsigned int action = 0,
                                               QtConnection* activeConnection = 0);

            // Called from the QNodeEditor when either a right mouse click on the QtNode has taken place,
            // or on one of its child QGraphicsItems.
            virtual bool mouseRightClickHandler(QGraphicsSceneMouseEvent* mouseEvent,
                                                QGraphicsItem* item,
                                                unsigned int action = 0,
                                                QtConnection* activeConnection = 0);

            // Called from the QNodeEditor when either a double click on the QtNode has taken place,
            // or on one of its child QGraphicsItems. The mouseDoubleClickHandler function performs
            // default behaviour, but it is possible to overload this function.
            virtual bool mouseDoubleClickHandler(QGraphicsSceneMouseEvent* mouseEvent, QGraphicsItem* item);

            // Called from the QNodeEditor.
            virtual bool mouseMoveHandler(QGraphicsSceneMouseEvent* mouseEvent, QGraphicsItem* item);

            // Collapse the node (and hide the ports)
            void collapse(void);

            // Make all ports visible and restore the endpoint of the connection
            void expand(void);

        signals:
            // Emitted when the action 1 icon is clicked
            void action1Clicked(QtNode*);

            // Emitted when the action 2 icon is clicked
            void action2Clicked(QtNode*);

            // Emitted when the node is selected
            void nodeSelected(QtNode*);

            // Emitted when a connection has been created with a port of this node, but not finalized (established) yet
            // This is only done in case the port is the base port!
            void connectionStarted(QtNode*, QtPort*, QtConnection*);

            // Emitted when a connection has been established with a port of this node
            // This is only done in case the port is the target port!
            void connectionEstablished(QtNode*, QtPort*, QtConnection*);

            // Emitted when a connection has been deleted
            // This is only done in case the port is the base port!
            void connectionDeleted(QtNode*, QtPort*);

        protected:
            void setTitlePosition(void);
            void adjustWidthForTitle(void);
            void setPortAlignedPos(QtPort* port, qreal height);
            void redraw(void);

            unsigned int mNodeType;
            bool mAutoSize;
            QtPort* getCheckedPortConnectedToPort(QtPort* port);
            qreal mZoom;
            qreal mIconSize;
            qreal mWidth;
            qreal mNormalizedWidth;
            qreal mNormalizedBodyHeight;
            qreal mHeaderHeight;
            qreal mBodyHeight;
            QGraphicsPathItem* mBody;
            QGraphicsPixmapItem* mHeaderTitleIcon;
            QGraphicsPixmapItem* mAction1Icon;
            QGraphicsPixmapItem* mAction2Icon;
            QBrush mHeaderBrush;
            QPen mPen;
            QtNodeEditor* mEditor;
            QGraphicsScene* mScene;
            QString mTitle;
            QGraphicsTextItem* mTitleLabel;
            QFont mFontHeader;
            Alignment mTitleAlignment;
            QVector<QtPort*> mPortList;
            QColor mPortNameColor;
            QGraphicsItem* mOriginalParent;
            QPixmap mImage;
            QGraphicsPixmapItem* mPixmapItem;
            bool mImageSet;
    };
}

#endif
