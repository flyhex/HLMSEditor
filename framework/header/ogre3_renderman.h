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

#ifndef MAGUS_OGRE_RENDERMANAGER_H
#define MAGUS_OGRE_RENDERMANAGER_H

#include "OgreRoot.h"
#include "OgreRenderWindow.h"
#include "OgreRenderSystem.h"
#include "OgreString.h"
#include "OgreTimer.h"
#include "OgreColourValue.h"
#include "ogre3_widget.h"
#include "Compositor/OgreCompositorManager2.h"
#include "Compositor/Pass/OgreCompositorPassProvider.h"

namespace Ogre
{
    class MyCompositorPassProvider : public CompositorPassProvider
    {
        public:
            virtual CompositorPassDef* addPassDef( CompositorPassType passType,
                                                   IdString customId,
                                                   uint32 rtIndex,
                                                   CompositorNodeDef *parentNodeDef )
        {
            return 0;
        }

            virtual CompositorPass* addPass( const CompositorPassDef *definition, Camera *defaultCamera,
                                             CompositorNode *parentNode, const CompositorChannel &target,
                                             SceneManager *sceneManager )
        {
            return 0;
        }
    };
}

namespace Magus
{
    static const Ogre::String OGRE_RENDERSYSTEM_DIRECTX11 = "Direct3D11 Rendering Subsystem";
    static const Ogre::String OGRE_RENDERSYSTEM_OPENGL3PLUS = "OpenGL 3+ Rendering Subsystem";

    /****************************************************************************
     * This class manages the rendering of the Ogre widgets
     * Ogre Manager for Ogre > V2.0
    ***************************************************************************/
    class OgreManager : public QObject
    {
        public:
            OgreManager(void);
            virtual ~OgreManager(void);
            void initialize(void);
            void renderOgreWidgetsOneFrame(void);
            void registerOgreWidget(int ogreWidgetId, QOgreWidget* ogreWidget);
            void unregisterOgreWidget(int ogreWidgetId);
            QOgreWidget* getOgreWidget(int ogreWidgetId) const;
            Ogre::Root* getOgreRoot(void);
            bool isRenderSystemGL(void);
            HGLRC getGlContext(void) const;
            void setGlContext(HGLRC glContext);

        private:
            QMap<int, QOgreWidget*> mQOgreWidgetMap;
            Ogre::Root* mRoot;
            Ogre::Timer* mTimer;
            Ogre::String mResourcesCfg;
            Ogre::String mPluginsCfg;
            Ogre::RenderSystem* mCurrentRenderSystem;
            void setupResources(void);
            void registerHlms(void);
            HGLRC mGlContext;
            Ogre::MyCompositorPassProvider* mCompositorPassProvider;
    };
}

//****************************************************************************/
#endif // MAGUS_OGRE_RENDERMANAGER_H
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
