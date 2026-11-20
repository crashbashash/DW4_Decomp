#include "dw4/support/reflected.h"
#include "dw4/game/ndmw/beNDMWAfsSetup.h"
#include "dw4/game/ndmw/beNDMWGameRam.h"
#include "dw4/game/ndmw/beNDMWLoadCtrl2.h"
#include "dw4/game/ndmw/beNDMWLoadIntf2.h"
#include "dw4/game/ndmw/beNDMWLogo.h"
#include "dw4/game/ndmw/beNDMWMdlEBullet.h"
#include "dw4/game/ndmw/beNDMWMdlEffect.h"
#include "dw4/game/ndmw/beNDMWMdlEnemy.h"
#include "dw4/game/ndmw/beNDMWMdlItem.h"
#include "dw4/game/ndmw/beNDMWMdlMapBase.h"
#include "dw4/game/ndmw/beNDMWMdlMapCursor.h"
#include "dw4/game/ndmw/beNDMWMdlObject.h"
#include "dw4/game/ndmw/beNDMWMdlPBullet.h"
#include "dw4/game/ndmw/beNDMWMdlPlayer.h"
#include "dw4/game/ndmw/beNDMWMdlPlayer2.h"
#include "dw4/game/ndmw/beNDMWPanelWaza.h"
#include "dw4/game/ndmw/beNDMWSaveCtrl.h"
#include "dw4/game/ndmw/beNDMWSaveIntf.h"
#include "dw4/game/ndmw/beNDMWStageCtl.h"
#include "dw4/game/ndmw/beNDMWStatus.h"
#include "dw4/game/ndmw/beNDMWTitle2.h"
#include "dw4/insight/igInsightCore.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igObject.h"
#include "dw4/game/ndmw/libNdmwRuntimePlugin.h"

/* vfunc_21 replaces every manager with a fresh instance, released through the refcount in the low
 * 23 bits of _refCount and allocated from the plugin's own allocator when g_useOwnerAllocator is set,
 * then adds each manager that exists to the core. vfunc_22 removes them again. */
static inline igMemoryPoolView *PluginAllocator(libNdmwRuntimePlugin *plugin) {
    igMemoryPoolView *allocator = ((Gap::Core::igObject *)plugin)->getMemoryPool();
    return g_useOwnerAllocator != 0 ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0);
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
        igInsightCore_AddManager(core, (igObject *)manager);
    }
}

static inline void RemoveManager(igInsightCore *core, int manager) {
    if (manager != 0) {
        igInsightCore_RemoveManager(core, (igObject *)manager);
    }
}

#define REPLACE_MANAGER(field, create) { igMemoryPoolView *allocator = PluginAllocator(plugin); ReleaseRef(plugin->field); plugin->field = (int)create((int)allocator); }

extern "C" void libNdmwRuntimePlugin_Attach(libNdmwRuntimePlugin *plugin, igInsightCore *core) {
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

extern "C" void libNdmwRuntimePlugin_Detach(libNdmwRuntimePlugin *plugin, igInsightCore *core) {
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

extern "C" int libNdmwRuntimePlugin_GetMeta(void) {
    return (int)g_libNdmwRuntimePlugin_metaObject;
}
