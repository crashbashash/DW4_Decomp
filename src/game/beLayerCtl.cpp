#include "dw4/reflected.h"
#include "dw4/igobject_release.h"

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

extern "C" void igObject_Destroy(void *);
extern "C" void *igObject_GetAllocator(void *);
extern "C" void *Memory_GetAllocatorBySelector(int);
extern "C" void igNamedObject_SetName(void *, char *);
extern "C" void *igInsightCore_FindManager(int, int);
extern "C" igSwitch *igSwitch_CreateInstance(void *);
extern "C" igGroup *igGroup_CreateInstance(void *);
extern "C" int igGroup_AppendChild(void *, void *);
extern "C" int igGroup_RemoveChild(void *, void *);
extern "C" int igSwitch_AppendChild(igSwitch *, void *);
extern "C" void *igSwitch_RemoveChildAt(igSwitch *, int);
extern "C" int igSwitch_EnableChild(igSwitch *, int);
extern "C" int igSwitch_DisableChild(igSwitch *, int);
extern "C" int igSwitch_EnableAllChildren(igSwitch *);
extern "C" int igSwitch_DisableAllChildren(igSwitch *);
extern "C" int beLayerCtl_GetSwtCtlEnum(void);
extern "C" int beLayerCtl_GetMessageEnum(void);
extern "C" void beMessenger_RegisterReceiver(int, int, char *, int, int);
extern "C" unsigned int beMessenger_ResolveEnumValue(int, int, void *);
extern "C" int beMessenger_GetStringCount(int);
extern "C" char *beMessenger_GetString(int, int);
extern "C" int beMessenger_AppendBool(int, int);
extern "C" int beMessenger_AppendObject(int, void *);
extern "C" int beMessenger_AppendString(int, char *);
extern "C" int beMessenger_ClearObjects(int);
extern "C" int strcmp(char *, char *);
extern "C" char LAYERCTL_3[];
extern "C" char LayerSwt[];
extern "C" char LAYERPARENT[];
extern "C" char NONE_2[];
extern "C" char ROOTATTR[];
extern "C" char ALL_4[];
extern "C" char emptyString[];
extern "C" int g_beLayerInfo_metaObject[4];
extern "C" int g_beLayerCtl_metaObject[4];
extern "C" int g_igLightStateSet_metaObject[4];
extern "C" int g_igViewerSceneInfoManager_metaObject[4];
extern "C" int g_ndmwAllocatorSelector[4];
extern "C" int g_defaultAllocatorSelector[4];
extern "C" unsigned char g_useOwnerAllocator;

/* A scene-graph node seen through its vtable: slot 20 is igObject::getMeta. */
class igNodeView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int getMeta();
};
#define META_OF(node) (((igNodeView *)(node))->getMeta())

/* Holds a new layer group's reference for the rest of ORDER. */
struct Ref {
    igNamedObject *p;
    Ref(igNamedObject *o) : p(o) {}
    ~Ref() {
        igNamedObject *object = p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};

extern "C" void beLayerCtl__ReleaseLayerSwitch(beLayerCtl *self);
extern "C" void beLayerCtl__RegisterReceiver(beLayerCtl *self, int receiver);
extern "C" int beLayerCtl__GetInfoMeta(void);
extern "C" void beLayerCtl__Update(void);
extern "C" int beLayerCtl__OnMessage(beLayerCtl *self, beLayerInfoRam *ram, beMessengerWork *work);
extern "C" int beLayerCtl__GetMeta(void);

void beLayerCtl__ReleaseLayerSwitch(beLayerCtl *self) {
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

void beLayerCtl__RegisterReceiver(beLayerCtl *self, int receiver)
{
    beMessenger_RegisterReceiver(self->_messenger, receiver, LAYERCTL_3, 0, -1);
}

int beLayerCtl__GetInfoMeta(void)
{
    return g_beLayerInfo_metaObject[0];
}

void beLayerCtl__Update(void)
{
}

int beLayerCtl__OnMessage(beLayerCtl *self, beLayerInfoRam *ram, beMessengerWork *work) {
    beLayerInfo *info = (beLayerInfo *)ram->_parentInfo;
    switch (beMessenger_ResolveEnumValue(self->_messenger, beLayerCtl_GetMessageEnum(), (void *)work->_message)) {
    case MESSAGE_ORDER: {
        igViewerSceneInfoManager *viewer = (igViewerSceneInfoManager *)igInsightCore_FindManager(self->_insight, g_igViewerSceneInfoManager_metaObject[0]);
        igGroup *root = (igGroup *)((igViewerParameters *)viewer->_parameters)->_scene;
        if (self->_isOrdered == 0) {
            void *allocator;
            PICK_ALLOCATOR(allocator, self, g_ndmwAllocatorSelector[0])
            igSwitch *old = LAYER_SWITCH(self);
            IG_OBJECT_RELEASE(old);
            self->_layerSwt = (int)igSwitch_CreateInstance(allocator);
            igNamedObject_SetName((void *)self->_layerSwt, LayerSwt);
            igGroup *lights = 0;
            int i;
            for (i = 0; i < CHILD_COUNT(CHILDREN(root)); i++) {
                igGroup *node = NODE_AT(CHILDREN(root), i);
                int lightMeta = g_igLightStateSet_metaObject[0];
                if (lightMeta == META_OF(node)) lights = node;
            }
            if (lights == 0) return 0;
            igGroup *parent = 0;
            int j;
            for (j = 0; j < CHILD_COUNT(CHILDREN(lights)); j++) {
                igGroup *node = NODE_AT(CHILDREN(lights), j);
                if (NAME_OF(node) != 0 && strcmp(LAYERPARENT, NAME_OF(node)) == 0) { parent = node; break; }
            }
            if (parent != 0) igGroup_AppendChild(parent, (void *)self->_layerSwt);
            else igGroup_AppendChild(lights, (void *)self->_layerSwt);
            self->_isOrdered = 1;
        }
        beLayerGroupList *groups = (beLayerGroupList *)info->_groups;
        if (groups == 0) return 1;
        int g;
        for (g = 0; g < groups->_count; g++) {
            void *allocator;
            PICK_ALLOCATOR(allocator, self, g_defaultAllocatorSelector[0])
            Ref layer((igNamedObject *)igGroup_CreateInstance(allocator));
            igNamedObject_SetName(layer.p, NAME_OF(NODE_AT(groups, g)));
            igSwitch_AppendChild(LAYER_SWITCH(self), layer.p);
        }
        void *noneAllocator;
        PICK_ALLOCATOR(noneAllocator, self, g_defaultAllocatorSelector[0])
        Ref none((igNamedObject *)igGroup_CreateInstance(noneAllocator));
        igNamedObject_SetName(none.p, NONE_2);
        igSwitch_AppendChild(LAYER_SWITCH(self), none.p);
        int index;
        igGroup *layer;
        igGroup *target;
        char *name;
        int k;
        igGroup *node;
        index = 0;
        while (index < CHILD_COUNT(CHILDREN(root))) {
            node = NODE_AT(CHILDREN(root), index);
            if (NAME_OF(node) == 0) igNamedObject_SetName(node, NONE_2);
            if (strcmp(ROOTATTR, NAME_OF(node)) == 0 || g_igLightStateSet_metaObject[0] == META_OF(node)) {
                index += 1;
            } else {
                name = NAME_OF(node);
                target = 0;
                for (k = 0; k < CHILD_COUNT(LAYERS(self)); k++) {
                    layer = NODE_AT(LAYERS(self), k);
                    if (strcmp(name, NAME_OF(layer)) == 0) { target = layer; break; }
                }
                if (target != 0) igGroup_AppendChild(target, node);
                else igGroup_AppendChild(none.p, node);
                igGroup_RemoveChild(root, node);
            }
        }
        beMessenger_AppendBool(self->_messenger, 1);
        break;
    }
    case MESSAGE_SWITCH: {
        if (beMessenger_GetStringCount(self->_messenger) < 2) return 0;
        char *layerName = beMessenger_GetString(self->_messenger, 0);
        char *control = beMessenger_GetString(self->_messenger, 1);
        if (strcmp(layerName, ALL_4) == 0) {
            switch (beMessenger_ResolveEnumValue(self->_messenger, beLayerCtl_GetSwtCtlEnum(), control)) {
            case SWTCTL_CLR: igSwitch_DisableAllChildren(LAYER_SWITCH(self)); break;
            case SWTCTL_SET: igSwitch_EnableAllChildren(LAYER_SWITCH(self)); break;
            case SWTCTL_FLIP: break;
            }
        } else {
            int i;
            for (i = 0; i < CHILD_COUNT(LAYERS(self)); i++) {
                if (strcmp(NAME_OF(NODE_AT(LAYERS(self), i)), layerName) == 0) {
                    switch (beMessenger_ResolveEnumValue(self->_messenger, beLayerCtl_GetSwtCtlEnum(), control)) {
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
        if (beMessenger_GetStringCount(self->_messenger) <= 0) return 0;
        char *layerName = beMessenger_GetString(self->_messenger, 0);
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
            beMessenger_AppendString(self->_messenger, NAME_OF(NODE_AT(LAYERS(self), i)));
        break;
    }
    case MESSAGE_GETLAYERNODE: {
        if (beMessenger_GetStringCount(self->_messenger) <= 0) return 0;
        char *layerName = beMessenger_GetString(self->_messenger, 0);
        int found = -1;
        int i;
        for (i = 0; i < CHILD_COUNT(LAYERS(self)); i++) {
            if (strcmp(NAME_OF(NODE_AT(LAYERS(self), i)), layerName) == 0) { found = i; break; }
        }
        if (found != -1) {
            beMessenger_ClearObjects(self->_messenger);
            beMessenger_AppendObject(self->_messenger, NODE_AT(LAYERS(self), found));
            beMessenger_AppendBool(self->_messenger, 1);
        }
        break;
    }
    case MESSAGE_INFO:
    default:
        break;
    }
    return 1;
}

int beLayerCtl__GetMeta(void)
{
    return g_beLayerCtl_metaObject[0];
}
