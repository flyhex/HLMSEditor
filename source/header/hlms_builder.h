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

#ifndef HLMS_BUILDER_H
#define HLMS_BUILDER_H

#include "OgreString.h"
#include "OgreHlmsDatablock.h"
#include "OgreHlmsSamplerblock.h"
#include "hlms_node_samplerblock.h"
#include "hlms_node_macroblock.h"
#include "hlms_node_blenddblock.h"
#include "node_editorwidget.h"
#include "ogre3_renderman.h"

/****************************************************************************
 This class is the base class for other builder classes, responsible for
 generation of a datablocks (pbs, unlit, ...) / generation of a node structure,
 based on a datablock.
 ***************************************************************************/
class HlmsBuilder
{
	public:
        HlmsBuilder(void);
        ~HlmsBuilder(void);

        // Save all resource locations to the Ogre resource file
        void saveAllResourcesLocations(void);

        // Create a Sampler node and add it to the node editor canvas
        virtual HlmsNodeSamplerblock* createSamplerNode(Magus::QtNodeEditor* nodeEditor);

        // Create a Macro node and add it to the node editor canvas
        virtual HlmsNodeMacroblock* createMacroNode(Magus::QtNodeEditor* nodeEditor);

        // Create a Blend node and add it to the node editor canvas
        virtual HlmsNodeBlendblock* createBlendNode(Magus::QtNodeEditor* nodeEditor);

        // Determine whether a directory is part of Ogre's resource locations
        bool isResourceLocationExisting(const Ogre::String& path);

    protected:

        // The samplerblock is enriched with values from a samplernode
        void enrichSamplerBlockGeneric (Ogre::HlmsSamplerblock* samplerblock,
                                        HlmsNodeSamplerblock* samplernode);

        // The samplernode is enriched with values from a samplerblock
        void enrichSamplerNodeGeneric (HlmsNodeSamplerblock* samplernode,
                                       const Ogre::HlmsSamplerblock* samplerblock);

        // The macroblock is enriched with values from a macro node
        void enrichMacroblock(HlmsNodeMacroblock* macronode, Ogre::HlmsMacroblock* macroblock);

        // The blendblock is enriched with values from a blend node
        void enrichBlendblock(HlmsNodeBlendblock* blendnode, Ogre::HlmsBlendblock* blendblock);

        Ogre::CompareFunction getCompareFunctionFromIndex(unsigned int index);
        unsigned int getIndexFromCompareFunction(Ogre::CompareFunction compareFunction);
        Ogre::SceneBlendFactor getSceneBlendFactorFromIndex(unsigned int index);
        unsigned int getIndexFromSceneBlendFactor(const Ogre::SceneBlendFactor& sceneBlendFactor);
        Ogre::SceneBlendOperation getSceneBlendOperationFromIndex(unsigned int index);
        unsigned int getIndexFromSceneBlendOperation(const Ogre::SceneBlendOperation& sceneBlendOperation);
        unsigned int getIndexFromTAM (Ogre::TextureAddressingMode textureAddressingMode);
        Ogre::TextureAddressingMode getTAMFromIndex (unsigned int index);
        unsigned int getIndexFromFilterOption (Ogre::FilterOptions filterOption);
        Ogre::FilterOptions getFilterOptionFromIndex (unsigned int index);
};

#endif

