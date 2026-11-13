#include "dw4/reflected.h"

extern "C" int igObject_Destroy(igObject *object);
extern "C" int igObject_GetAllocator(igObject *object);
extern "C" int Memory_GetAllocatorBySelector(int selector);
extern "C" void igInsightCore_AddManager(igInsightCore *core, int manager);
extern "C" void igInsightCore_RemoveManager(igInsightCore *core, int manager);
extern "C" unsigned char g_useOwnerAllocator;
extern "C" int kIGMemoryPoolHandleUser0[4];
extern "C" int g_libNdmwRuntimePlugin_metaObject[4];
extern "C" int beNDMWAfsSetup_CreateInstance(int allocator);
extern "C" int beNDMWStageCtl_CreateInstance(int allocator);
extern "C" int beNDMWPanelWaza_CreateInstance(int allocator);
extern "C" int beNDMWLogo_CreateInstance(int allocator);
extern "C" int beNDMWTitle2_CreateInstance(int allocator);
extern "C" int beNDMWLoadCtrl2_CreateInstance(int allocator);
extern "C" int beNDMWLoadIntf2_CreateInstance(int allocator);
extern "C" int beNDMWSaveCtrl_CreateInstance(int allocator);
extern "C" int beNDMWSaveIntf_CreateInstance(int allocator);
extern "C" int beNDMWGameRam_CreateInstance(int allocator);
extern "C" int beNDMWStatus_CreateInstance(int allocator);
extern "C" int beNDMWMdlPlayer_CreateInstance(int allocator);
extern "C" int beNDMWMdlPlayer2_CreateInstance(int allocator);
extern "C" int beNDMWMdlPBullet_CreateInstance(int allocator);
extern "C" int beNDMWMdlEnemy_CreateInstance(int allocator);
extern "C" int beNDMWMdlEBullet_CreateInstance(int allocator);
extern "C" int beNDMWMdlObject_CreateInstance(int allocator);
extern "C" int beNDMWMdlItem_CreateInstance(int allocator);
extern "C" int beNDMWMdlEffect_CreateInstance(int allocator);
extern "C" int beNDMWMdlMapBase_CreateInstance(int allocator);
extern "C" int beNDMWMdlMapCursor_CreateInstance(int allocator);

/* vfunc_21 replaces every manager with a fresh instance, released through the refcount in the low
 * 23 bits of _refCount and allocated from the plugin's own allocator when g_useOwnerAllocator is set,
 * then adds each manager that exists to the core. vfunc_22 removes them again. */
static inline int PluginAllocator(libNdmwRuntimePlugin *plugin) {
    int allocator = igObject_GetAllocator(plugin);
    return g_useOwnerAllocator != 0 ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0[0]);
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
    REPLACE_MANAGER(_afsSetup, beNDMWAfsSetup_CreateInstance)
    REPLACE_MANAGER(_stageCtl, beNDMWStageCtl_CreateInstance)
    REPLACE_MANAGER(_panelWaza, beNDMWPanelWaza_CreateInstance)
    REPLACE_MANAGER(_logo, beNDMWLogo_CreateInstance)
    REPLACE_MANAGER(_title2, beNDMWTitle2_CreateInstance)
    REPLACE_MANAGER(_loadCtrl2, beNDMWLoadCtrl2_CreateInstance)
    REPLACE_MANAGER(_loadIntf2, beNDMWLoadIntf2_CreateInstance)
    REPLACE_MANAGER(_saveCtrl, beNDMWSaveCtrl_CreateInstance)
    REPLACE_MANAGER(_saveIntf, beNDMWSaveIntf_CreateInstance)
    REPLACE_MANAGER(_gameRam, beNDMWGameRam_CreateInstance)
    REPLACE_MANAGER(_status, beNDMWStatus_CreateInstance)
    REPLACE_MANAGER(_mdlPlayer, beNDMWMdlPlayer_CreateInstance)
    REPLACE_MANAGER(_mdlPlayer2, beNDMWMdlPlayer2_CreateInstance)
    REPLACE_MANAGER(_mdlPBullet, beNDMWMdlPBullet_CreateInstance)
    REPLACE_MANAGER(_mdlEnemy, beNDMWMdlEnemy_CreateInstance)
    REPLACE_MANAGER(_mdlEBullet, beNDMWMdlEBullet_CreateInstance)
    REPLACE_MANAGER(_mdlObject, beNDMWMdlObject_CreateInstance)
    REPLACE_MANAGER(_mdlItem, beNDMWMdlItem_CreateInstance)
    REPLACE_MANAGER(_mdlEffect, beNDMWMdlEffect_CreateInstance)
    REPLACE_MANAGER(_mdlMapBase, beNDMWMdlMapBase_CreateInstance)
    REPLACE_MANAGER(_mdlMapCursor, beNDMWMdlMapCursor_CreateInstance)

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
