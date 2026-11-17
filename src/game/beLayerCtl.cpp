#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/core/igObjectDispatchView.h"
#include "dw4/core/igobject_release.h"
#include "dw4/game/beLayerCtl.h"
#include "dw4/game/beLayerInfo.h"
#include "dw4/game/beMessenger.h"
#include "dw4/scenegraph/igGroup.h"
#include "dw4/insight/igInsightCore.h"
#include "dw4/scenegraph/igLightStateSet.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igNamedObject.h"
#include "dw4/core/igObject.h"
#include "dw4/scenegraph/igSwitch.h"
#include "dw4/viewer/igViewerSceneInfoManager.h"
#include <string.h>
#include "dw4/support/emptyString.h"
#pragma push
#pragma readonly_strings on

/* beLayerCtl sorts the scene root's children into named layers. ORDER builds an igSwitch,
 * "LayerSwt", under the root's light state set (or its "LAYERPARENT" child), gives it one igGroup
 * per beLayerGroup of the receiver's info plus a "NONE" group, and moves every other root child
 * into the layer of the same name (NONE when no layer matches). SWITCH, REMOVE, GETNAMELIST and
 * GETLAYERNODE then address the layers by name. */

enum LayerCtlMessage {
    MESSAGE_ORDER, MESSAGE_SWITCH, MESSAGE_REMOVE, MESSAGE_GETNAMELIST, MESSAGE_GETLAYERNODE,
    MESSAGE_INFO
};

/* SwtCtl values: CLR and DISPOFF hide a layer, SET and DISPON show it, FLIP toggles it. */
enum SwtCtl { SWTCTL_CLR, SWTCTL_SET, SWTCTL_FLIP };

#define CHILDREN(group) ((igNodeList *)(group)->_childList)
#define CHILD_COUNT(list) ((list) != 0 ? (list)->_count : 0)
#define NODE_AT(list, i) ((igGroup *)((int *)(list)->_data)[i])
#define NAME_OF(object) ((object)->_name ? (char *)(object)->_name : emptyString)
#define LAYER_SWITCH(self) ((igSwitch *)(self)->_layerSwt)
#define LAYERS(self) CHILDREN(LAYER_SWITCH(self))
#define PICK_ALLOCATOR(allocator, owner, selector) { allocator = igObject_GetAllocator(owner); allocator = g_useOwnerAllocator ? allocator : Memory_GetAllocatorBySelector(selector); }


#define META_OF(node) (((igObjectDispatchView *)(node))->GetMeta())

extern "C" void beLayerCtl_Prepare(beLayerCtl *self);
extern "C" void beLayerCtl_OnAddRam(beLayerCtl *self, int receiver);
extern "C" igMetaObject *beLayerCtl__GetInfoMeta(void);
extern "C" void beLayerCtl_UpdateRam(void);
extern "C" int beLayerCtl_OnMessage(beLayerCtl *self, beLayerInfoRam *ram, beMessengerWork *work);
extern "C" igMetaObject *beLayerCtl__GetMeta(void);

void beLayerCtl_Prepare(beLayerCtl *self) {
    igSwitch *layers;
    igNodeList *children;
    int count;
    self->_isOrdered = 0;
    if (self->_layerSwt != 0) {
        goto test; /* matching construct: goto/label layout reproduces the retail loop shape */
    body:
        igSwitch_RemoveChildAt(layers, 0);
    test:
        layers = LAYER_SWITCH(self);
        children = CHILDREN(layers);
        if (children != 0) {
            count = children->_count;
        } else {
            count = 0;
        }
        if (count > 0) goto body;
        IG_OBJECT_RELEASE(layers);
        self->_layerSwt = 0;
    }
}

void beLayerCtl_OnAddRam(beLayerCtl *self, int receiver)
{
    beMessenger_RegisterReceiver((beMessenger *)self->_messenger, (beBaseInfoRam *)receiver, "LAYERCTL", 0, -1);
}

igMetaObject *beLayerCtl__GetInfoMeta(void)
{
    return g_beLayerInfo_metaObject;
}

void beLayerCtl_UpdateRam(void)
{
}

int beLayerCtl_OnMessage(beLayerCtl *self, beLayerInfoRam *ram, beMessengerWork *work) {
    beLayerInfo *info = (beLayerInfo *)ram->_parentInfo;
    switch (beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, beLayerCtl_GetMessageEnum(), (const char *)work->_message)) {
    case MESSAGE_ORDER: {
        igViewerSceneInfoManager *viewer = (igViewerSceneInfoManager *)igInsightCore_FindManager((igInsightCore *)self->_insight, g_igViewerSceneInfoManager_metaObject);
        igGroup *root = (igGroup *)((igViewerParameters *)viewer->_parameters)->_scene;
        if (self->_isOrdered == 0) {
            void *allocator;
            PICK_ALLOCATOR(allocator, self, kIGMemoryPoolHandleUser0)
            igSwitch *old = LAYER_SWITCH(self);
            IG_OBJECT_RELEASE(old);
            self->_layerSwt = (int)igSwitch_CreateInstance((int)allocator);
            igNamedObject_SetName((igNamedObject *)self->_layerSwt, "LayerSwt");
            igGroup *lights = 0;
            int i;
            for (i = 0; i < CHILD_COUNT(CHILDREN(root)); i++) {
                igGroup *node = NODE_AT(CHILDREN(root), i);
                igMetaObject *lightMeta = g_igLightStateSet_metaObject;
                if (lightMeta == META_OF(node)) lights = node;
            }
            if (lights == 0) return 0;
            igGroup *parent = 0;
            int j;
            for (j = 0; j < CHILD_COUNT(CHILDREN(lights)); j++) {
                igGroup *node = NODE_AT(CHILDREN(lights), j);
                if (NAME_OF(node) != 0 && strcmp("LAYERPARENT", NAME_OF(node)) == 0) { parent = node; break; }
            }
            if (parent != 0) igGroup_AppendChild(parent, (igNode *)self->_layerSwt);
            else igGroup_AppendChild(lights, (igNode *)self->_layerSwt);
            self->_isOrdered = 1;
        }
        beLayerGroupList *groups = (beLayerGroupList *)info->_groups;
        if (groups == 0) return 1;
        int g;
        for (g = 0; g < groups->_count; g++) {
            void *allocator;
            PICK_ALLOCATOR(allocator, self, kIGMemoryPoolHandleUser1)
            igSmartPointer<igNamedObject> layer((igNamedObject *)igGroup_CreateInstance((int)allocator));
            igNamedObject_SetName(layer.p, NAME_OF(NODE_AT(groups, g)));
            igSwitch_AppendChild(LAYER_SWITCH(self), (igNode *)layer.p);
        }
        void *noneAllocator;
        PICK_ALLOCATOR(noneAllocator, self, kIGMemoryPoolHandleUser1)
        igSmartPointer<igNamedObject> none((igNamedObject *)igGroup_CreateInstance((int)noneAllocator));
        igNamedObject_SetName(none.p, "NONE");
        igSwitch_AppendChild(LAYER_SWITCH(self), (igNode *)none.p);
        int index;
        igGroup *layer;
        igGroup *target;
        char *name;
        int k;
        igGroup *node;
        index = 0;
        while (index < CHILD_COUNT(CHILDREN(root))) {
            node = NODE_AT(CHILDREN(root), index);
            if (NAME_OF(node) == 0) igNamedObject_SetName((igNamedObject *)node, "NONE");
            if (strcmp("ROOTATTR", NAME_OF(node)) == 0 || g_igLightStateSet_metaObject == META_OF(node)) {
                index += 1;
            } else {
                name = NAME_OF(node);
                target = 0;
                for (k = 0; k < CHILD_COUNT(LAYERS(self)); k++) {
                    layer = NODE_AT(LAYERS(self), k);
                    if (strcmp(name, NAME_OF(layer)) == 0) { target = layer; break; }
                }
                if (target != 0) igGroup_AppendChild(target, (igNode *)node);
                else igGroup_AppendChild((igGroup *)none.p, (igNode *)node);
                igGroup_RemoveChild(root, (igNode *)node);
            }
        }
        beMessenger_AppendBool((beMessenger *)self->_messenger, 1);
        break;
    }
    case MESSAGE_SWITCH: {
        if (beMessenger_GetStringCount((beMessenger *)self->_messenger) < 2) return 0;
        char *layerName = (char *)(beMessenger_GetString((beMessenger *)self->_messenger, 0));
        char *control = (char *)(beMessenger_GetString((beMessenger *)self->_messenger, 1));
        if (strcmp(layerName, "ALL") == 0) {
            switch (beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, beLayerCtl_GetSwtCtlEnum(), control)) {
            case SWTCTL_CLR: igSwitch_DisableAllChildren(LAYER_SWITCH(self)); break;
            case SWTCTL_SET: igSwitch_EnableAllChildren(LAYER_SWITCH(self)); break;
            case SWTCTL_FLIP: break;
            }
        } else {
            int i;
            for (i = 0; i < CHILD_COUNT(LAYERS(self)); i++) {
                if (strcmp(NAME_OF(NODE_AT(LAYERS(self), i)), layerName) == 0) {
                    switch (beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, beLayerCtl_GetSwtCtlEnum(), control)) {
                    case SWTCTL_CLR: igSwitch_DisableChild(LAYER_SWITCH(self), i); break;
                    case SWTCTL_SET: igSwitch_EnableChild(LAYER_SWITCH(self), i); break;
                    case SWTCTL_FLIP: {
                        igSwitch *layers = LAYER_SWITCH(self);
                        if ((1 << (i & 31)) & ((unsigned *)((igBitMask *)layers->_childMask)->_data)[(unsigned)i >> 5]) igSwitch_DisableChild(layers, i);
                        else igSwitch_EnableChild(layers, i);
                        break; }
                    }
                    break;
                }
            }
        }
        break;
    }
    case MESSAGE_REMOVE: {
        if (beMessenger_GetStringCount((beMessenger *)self->_messenger) <= 0) return 0;
        char *layerName = (char *)(beMessenger_GetString((beMessenger *)self->_messenger, 0));
        int i;
        for (i = 0; i < CHILD_COUNT(LAYERS(self)); i++) {
            if (strcmp(NAME_OF(NODE_AT(LAYERS(self), i)), layerName) == 0) {
                igSwitch_RemoveChildAt(LAYER_SWITCH(self), i);
                break;
            }
        }
        break;
    }
    case MESSAGE_GETNAMELIST: {
        int i;
        for (i = 0; i < CHILD_COUNT(LAYERS(self)); i++)
            beMessenger_AppendString((beMessenger *)self->_messenger, NAME_OF(NODE_AT(LAYERS(self), i)));
        break;
    }
    case MESSAGE_GETLAYERNODE: {
        if (beMessenger_GetStringCount((beMessenger *)self->_messenger) <= 0) return 0;
        char *layerName = (char *)(beMessenger_GetString((beMessenger *)self->_messenger, 0));
        int found = -1;
        int i;
        for (i = 0; i < CHILD_COUNT(LAYERS(self)); i++) {
            if (strcmp(NAME_OF(NODE_AT(LAYERS(self), i)), layerName) == 0) { found = i; break; }
        }
        if (found != -1) {
            beMessenger_ClearObjects((beMessenger *)self->_messenger);
            beMessenger_AppendObject((beMessenger *)self->_messenger, (igObject *)(NODE_AT(LAYERS(self), found)));
            beMessenger_AppendBool((beMessenger *)self->_messenger, 1);
        }
        break;
    }
    case MESSAGE_INFO:
    default:
        break;
    }
    return 1;
}

igMetaObject *beLayerCtl__GetMeta(void)
{
    return g_beLayerCtl_metaObject;
}

#pragma pop
