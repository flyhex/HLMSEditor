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

// Include
#include "constants.h"
#include "mainwindow.h"
#include "paint_dockwidget.h"

class MainWindow;

//****************************************************************************/
PaintDockWidget::PaintDockWidget(QString title, MainWindow* parent, Qt::WindowFlags flags) :
    QDockWidget (title, parent, flags),
    mParent(parent)
{
    mInnerMain = new QMainWindow();
    mInnerMain->setMinimumSize(100,100);
    setWidget(mInnerMain);
    QRect rec = QApplication::desktop()->screenGeometry();
    setMinimumWidth(0.1 * rec.width());
}

//****************************************************************************/
PaintDockWidget::~PaintDockWidget(void)
{
}

//****************************************************************************/
void PaintDockWidget::addDockWidget(Qt::DockWidgetArea area, QDockWidget* dockWidget)
{
    mInnerMain->addDockWidget(area, dockWidget);
}
