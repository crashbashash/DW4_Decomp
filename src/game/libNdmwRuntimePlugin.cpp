#include "dw4/reflected.h"

extern "C" int igObject_Destroy(igObject *object);
extern "C" int igObject_GetAllocator(igObject *object);
extern "C" int Memory_GetAllocatorBySelector(int selector);
extern "C" void igInsightCore_AddManager(igInsightCore *core, int manager);
extern "C" void igInsightCore_RemoveManager(igInsightCore *core, int manager);
extern "C" unsigned char g_useOwnerAllocator;
extern "C" int g_ndmwAllocatorSelector[4];
extern "C" int g_libNdmwRuntimePlugin_metaObject[4];
extern "C" int FUN_003cae00(int allocator);
extern "C" int FUN_003bbda0(int allocator);
extern "C" int FUN_003bee90(int allocator);
extern "C" int FUN_003c2340(int allocator);
extern "C" int FUN_003b28a0(int allocator);
extern "C" int FUN_003c7da0(int allocator);
extern "C" int FUN_003c4700(int allocator);
extern "C" int FUN_003bd3f0(int allocator);
extern "C" int FUN_003bcc80(int allocator);
extern "C" int FUN_003c9ca0(int allocator);
extern "C" int FUN_003bb790(int allocator);
extern "C" int FUN_003bf890(int allocator);
extern "C" int FUN_003bf1b0(int allocator);
extern "C" int FUN_003c0960(int allocator);
extern "C" int FUN_003c1720(int allocator);
extern "C" int FUN_003c1ca0(int allocator);
extern "C" int FUN_003c0b50(int allocator);
extern "C" int FUN_003c1120(int allocator);
extern "C" int FUN_003c1ab0(int allocator);
extern "C" int FUN_003c0f30(int allocator);
extern "C" int FUN_003c0d40(int allocator);

/* vfunc_21 replaces every manager with a fresh instance, released through the refcount in the low
 * 23 bits of _refCount and allocated from the plugin's own allocator when g_useOwnerAllocator is set,
 * then adds each manager that exists to the core. vfunc_22 removes them again. */
static inline int PluginAllocator(libNdmwRuntimePlugin *plugin) {
    int allocator = igObject_GetAllocator(plugin);
    return g_useOwnerAllocator != 0 ? allocator : Memory_GetAllocatorBySelector(g_ndmwAllocatorSelector[0]);
}

static inline void ReleaseRef(int field) {
    igObject *object = (igObject *)field;
    if (object != 0) {
        object->_refCount = object->_refCount - 1;
        if ((object->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(object);
        }
    }
}

static inline void AddManager(igInsightCore *core, int manager) {
    if (manager != 0) {
        igInsightCore_AddManager(core, manager);
    }
}

static inline void RemoveManager(igInsightCore *core, int manager) {
    if (manager != 0) {
        igInsightCore_RemoveManager(core, manager);
    }
}

#define REPLACE_MANAGER(field, create) { int allocator = PluginAllocator(plugin); ReleaseRef(plugin->field); plugin->field = create(allocator); }

extern "C" void Gap__Bec__libNdmwRuntimePlugin__vfunc_21(libNdmwRuntimePlugin *plugin, igInsightCore *core) {
    REPLACE_MANAGER(_afsSetup, FUN_003cae00)
    REPLACE_MANAGER(_stageCtl, FUN_003bbda0)
    REPLACE_MANAGER(_panelWaza, FUN_003bee90)
    REPLACE_MANAGER(_logo, FUN_003c2340)
    REPLACE_MANAGER(_title2, FUN_003b28a0)
    REPLACE_MANAGER(_loadCtrl2, FUN_003c7da0)
    REPLACE_MANAGER(_loadIntf2, FUN_003c4700)
    REPLACE_MANAGER(_saveCtrl, FUN_003bd3f0)
    REPLACE_MANAGER(_saveIntf, FUN_003bcc80)
    REPLACE_MANAGER(_gameRam, FUN_003c9ca0)
    REPLACE_MANAGER(_status, FUN_003bb790)
    REPLACE_MANAGER(_mdlPlayer, FUN_003bf890)
    REPLACE_MANAGER(_mdlPlayer2, FUN_003bf1b0)
    REPLACE_MANAGER(_mdlPBullet, FUN_003c0960)
    REPLACE_MANAGER(_mdlEnemy, FUN_003c1720)
    REPLACE_MANAGER(_mdlEBullet, FUN_003c1ca0)
    REPLACE_MANAGER(_mdlObject, FUN_003c0b50)
    REPLACE_MANAGER(_mdlItem, FUN_003c1120)
    REPLACE_MANAGER(_mdlEffect, FUN_003c1ab0)
    REPLACE_MANAGER(_mdlMapBase, FUN_003c0f30)
    REPLACE_MANAGER(_mdlMapCursor, FUN_003c0d40)

    AddManager(core, plugin->_afsSetup);
    AddManager(core, plugin->_stageCtl);
    AddManager(core, plugin->_panelWaza);
    AddManager(core, plugin->_logo);
    AddManager(core, plugin->_title2);
    AddManager(core, plugin->_loadCtrl2);
    AddManager(core, plugin->_loadIntf2);
    AddManager(core, plugin->_saveCtrl);
    AddManager(core, plugin->_saveIntf);
    AddManager(core, plugin->_gameRam);
    AddManager(core, plugin->_status);
    AddManager(core, plugin->_mdlPlayer2);
    AddManager(core, plugin->_mdlPBullet);
    AddManager(core, plugin->_mdlEBullet);
    AddManager(core, plugin->_mdlObject);
    AddManager(core, plugin->_mdlItem);
    AddManager(core, plugin->_mdlEffect);
    AddManager(core, plugin->_mdlMapBase);
    AddManager(core, plugin->_mdlMapCursor);
    AddManager(core, plugin->_mdlPlayer);
    AddManager(core, plugin->_mdlEnemy);
}

#undef REPLACE_MANAGER

extern "C" void Gap__Bec__libNdmwRuntimePlugin__vfunc_22(libNdmwRuntimePlugin *plugin, igInsightCore *core) {
    RemoveManager(core, plugin->_mdlMapCursor);
    RemoveManager(core, plugin->_mdlMapBase);
    RemoveManager(core, plugin->_mdlEffect);
    RemoveManager(core, plugin->_mdlItem);
    RemoveManager(core, plugin->_mdlObject);
    RemoveManager(core, plugin->_mdlEBullet);
    RemoveManager(core, plugin->_mdlEnemy);
    RemoveManager(core, plugin->_mdlPBullet);
    RemoveManager(core, plugin->_mdlPlayer2);
    RemoveManager(core, plugin->_mdlPlayer);
    RemoveManager(core, plugin->_status);
    RemoveManager(core, plugin->_gameRam);
    RemoveManager(core, plugin->_saveCtrl);
    RemoveManager(core, plugin->_saveIntf);
    RemoveManager(core, plugin->_loadIntf2);
    RemoveManager(core, plugin->_loadCtrl2);
    RemoveManager(core, plugin->_title2);
    RemoveManager(core, plugin->_logo);
    RemoveManager(core, plugin->_panelWaza);
    RemoveManager(core, plugin->_afsSetup);
    RemoveManager(core, plugin->_stageCtl);
}

extern "C" int Gap__Bec__libNdmwRuntimePlugin__vfunc_20(void) {
    return g_libNdmwRuntimePlugin_metaObject[0];
}
