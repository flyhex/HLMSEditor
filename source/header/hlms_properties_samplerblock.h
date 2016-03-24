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

#ifndef HLMS_PROPERTIES_SAMPLERBLOCK_H
#define HLMS_PROPERTIES_SAMPLERBLOCK_H

#include <QWidget>
#include "asset_assetwidget.h"
#include "hlms_node_samplerblock.h"
#include "asset_propertywidget_select.h"
#include "asset_propertywidget_decimal.h"

QT_BEGIN_NAMESPACE

QT_END_NAMESPACE

using namespace Magus; // Use 'namespace Magus' because of issues with signal and slots;

class HlmsPropertiesSamplerblock : public QWidget
{
    Q_OBJECT

    public:
        HlmsPropertiesSamplerblock(const QString& fileNameIcon, QWidget* parent = 0);
        virtual ~HlmsPropertiesSamplerblock(void);
        void setObject (HlmsNodeSamplerblock* hlmsNodeSamplerblock);

        // Set properties visible/invisible
        void setTextureTypePropertyVisible (bool visible);
        void setDetailMapPropertyVisible (bool visible);

    private slots:
        void propertyValueChanged(QtProperty* property);
        void infoClicked(void);

    private:
        HlmsNodeSamplerblock* mHlmsNodeSamplerblock;
        Magus::QtAssetWidget* mAssetWidget;
        Magus::QtSelectProperty* mTextureTypeSelectProperty;
        Magus::QtDecimalProperty* mMapWeightSelectProperty;
        Magus::QtContainerWidget* mDetailMapContainer;
};

#endif
