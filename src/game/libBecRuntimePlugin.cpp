#include "dw4/reflected.h"

extern "C" int igObject_Destroy(igObject *object);
extern "C" int igObject_GetAllocator(igObject *object);
extern "C" int Memory_GetAllocatorBySelector(int selector);
extern "C" void igInsightCore_AddManager(igInsightCore *core, int manager);
extern "C" void igInsightCore_RemoveManager(igInsightCore *core, int manager);
extern "C" unsigned char g_useOwnerAllocator;
extern "C" int g_ndmwAllocatorSelector[4];
extern "C" int g_libBecRuntimePlugin_metaObject[4];
extern "C" int FUN_00342ca0(int allocator);
extern "C" int FUN_0036dfa0(int allocator);
extern "C" int FUN_003578d0(int allocator);
extern "C" int FUN_00367860(int allocator);
extern "C" int FUN_003627f0(int allocator);
extern "C" int FUN_0034c8a0(int allocator);
extern "C" int FUN_00343760(int allocator);
extern "C" int FUN_003660d0(int allocator);
extern "C" int FUN_0035b730(int allocator);
extern "C" int FUN_00363210(int allocator);
extern "C" int FUN_00369dc0(int allocator);
extern "C" int FUN_003442b0(int allocator);
extern "C" int FUN_003464f0(int allocator);
extern "C" int FUN_00340cc0(int allocator);
extern "C" int FUN_0035caa0(int allocator);
extern "C" int FUN_00361e50(int allocator);
extern "C" int FUN_0034ef30(int allocator);
extern "C" int FUN_00346c80(int allocator);
extern "C" int FUN_00368710(int allocator);
extern "C" int FUN_0035d780(int allocator);
extern "C" int FUN_0035eb90(int allocator);
extern "C" int FUN_00345a00(int allocator);
extern "C" int FUN_00357660(int allocator);
extern "C" int FUN_00342970(int allocator);
extern "C" int FUN_0036dd30(int allocator);
extern "C" int FUN_0033f410(int allocator);
extern "C" int FUN_00369820(int allocator);
extern "C" int FUN_00344e40(int allocator);
extern "C" int FUN_00360b70(int allocator);
extern "C" int FUN_0034b9e0(int allocator);
extern "C" int FUN_0035a710(int allocator);
extern "C" int FUN_0036c030(int allocator);
extern "C" int FUN_0034c630(int allocator);
extern "C" int FUN_00343490(int allocator);
extern "C" int FUN_0035c010(int allocator);
extern "C" int FUN_0034e360(int allocator);
extern "C" int FUN_00342310(int allocator);
extern "C" int FUN_00341340(int allocator);

/* vfunc_21 replaces every manager with a fresh instance, released through the refcount in the low
 * 23 bits of _refCount and allocated from the plugin's own allocator when g_useOwnerAllocator is set,
 * then adds each manager that exists to the core. vfunc_22 removes them again. */
static inline int PluginAllocator(libBecRuntimePlugin *plugin) {
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

extern "C" void Gap__Bec__libBecRuntimePlugin__vfunc_21(libBecRuntimePlugin *plugin, igInsightCore *core) {
    REPLACE_MANAGER(_system, FUN_00342ca0)
    REPLACE_MANAGER(_luaInterface, FUN_0036dfa0)
    REPLACE_MANAGER(_messenger, FUN_003578d0)
    REPLACE_MANAGER(_cri, FUN_00367860)
    REPLACE_MANAGER(_fileList, FUN_003627f0)
    REPLACE_MANAGER(_padManager, FUN_0034c8a0)
    REPLACE_MANAGER(_staticInfoCtl, FUN_00343760)
    REPLACE_MANAGER(_dbManager, FUN_003660d0)
    REPLACE_MANAGER(_luaManager, FUN_0035b730)
    REPLACE_MANAGER(_demoManager, FUN_00363210)
    REPLACE_MANAGER(_bkColor, FUN_00369dc0)
    REPLACE_MANAGER(_sound, FUN_003442b0)
    REPLACE_MANAGER(_seCtl, FUN_003464f0)
    REPLACE_MANAGER(_waterPlain, FUN_00340cc0)
    REPLACE_MANAGER(_layerCtl, FUN_0035caa0)
    REPLACE_MANAGER(_font, FUN_00361e50)
    REPLACE_MANAGER(_movie, FUN_0034ef30)
    REPLACE_MANAGER(_saveUtil, FUN_00346c80)
    REPLACE_MANAGER(_cpTransform, FUN_00368710)
    REPLACE_MANAGER(_hitLandModel, FUN_0035d780)
    REPLACE_MANAGER(_hitLandDeliv, FUN_0035eb90)
    REPLACE_MANAGER(_selectCtrl, FUN_00345a00)
    REPLACE_MANAGER(_meterCtrl, FUN_00357660)
    REPLACE_MANAGER(_targetObj, FUN_00342970)
    REPLACE_MANAGER(_action2, FUN_0036dd30)
    REPLACE_MANAGER(_weapon, FUN_0033f410)
    REPLACE_MANAGER(_cameraCtrl, FUN_00369820)
    REPLACE_MANAGER(_shadow01, FUN_00344e40)
    REPLACE_MANAGER(_generater, FUN_00360b70)
    REPLACE_MANAGER(_point01, FUN_0034b9e0)
    REPLACE_MANAGER(_matCtrl, FUN_0035a710)
    REPLACE_MANAGER(_actionStarter, FUN_0036c030)
    REPLACE_MANAGER(_particleCtrl2, FUN_0034c630)
    REPLACE_MANAGER(_switchCtrl, FUN_00343490)
    REPLACE_MANAGER(_lightCtrl, FUN_0035c010)
    REPLACE_MANAGER(_numberCtrl, FUN_0034e360)
    REPLACE_MANAGER(_textureCtrl, FUN_00342310)
    REPLACE_MANAGER(_timer, FUN_00341340)

    AddManager(core, plugin->_system);
    AddManager(core, plugin->_luaInterface);
    AddManager(core, plugin->_messenger);
    AddManager(core, plugin->_cri);
    AddManager(core, plugin->_fileList);
    AddManager(core, plugin->_padManager);
    AddManager(core, plugin->_staticInfoCtl);
    AddManager(core, plugin->_dbManager);
    AddManager(core, plugin->_luaManager);
    AddManager(core, plugin->_demoManager);
    AddManager(core, plugin->_bkColor);
    AddManager(core, plugin->_sound);
    AddManager(core, plugin->_seCtl);
    AddManager(core, plugin->_layerCtl);
    AddManager(core, plugin->_font);
    AddManager(core, plugin->_movie);
    AddManager(core, plugin->_saveUtil);
    AddManager(core, plugin->_waterPlain);
    AddManager(core, plugin->_cpTransform);
    AddManager(core, plugin->_hitLandModel);
    AddManager(core, plugin->_hitLandDeliv);
    AddManager(core, plugin->_selectCtrl);
    AddManager(core, plugin->_meterCtrl);
    AddManager(core, plugin->_targetObj);
    AddManager(core, plugin->_action2);
    AddManager(core, plugin->_weapon);
    AddManager(core, plugin->_cameraCtrl);
    AddManager(core, plugin->_shadow01);
    AddManager(core, plugin->_generater);
    AddManager(core, plugin->_point01);
    AddManager(core, plugin->_matCtrl);
    AddManager(core, plugin->_actionStarter);
    AddManager(core, plugin->_particleCtrl2);
    AddManager(core, plugin->_switchCtrl);
    AddManager(core, plugin->_lightCtrl);
    AddManager(core, plugin->_numberCtrl);
    AddManager(core, plugin->_textureCtrl);
    AddManager(core, plugin->_memory);
    AddManager(core, plugin->_timer);
}

#undef REPLACE_MANAGER

extern "C" void Gap__Bec__libBecRuntimePlugin__vfunc_22(libBecRuntimePlugin *plugin, igInsightCore *core) {
    RemoveManager(core, plugin->_system);
    RemoveManager(core, plugin->_luaInterface);
    RemoveManager(core, plugin->_messenger);
    RemoveManager(core, plugin->_fileList);
    RemoveManager(core, plugin->_cri);
    RemoveManager(core, plugin->_padManager);
    RemoveManager(core, plugin->_dbManager);
    RemoveManager(core, plugin->_cpTransform);
    RemoveManager(core, plugin->_hitLandModel);
    RemoveManager(core, plugin->_hitLandDeliv);
    RemoveManager(core, plugin->_selectCtrl);
    RemoveManager(core, plugin->_targetObj);
    RemoveManager(core, plugin->_meterCtrl);
    RemoveManager(core, plugin->_action2);
    RemoveManager(core, plugin->_weapon);
    RemoveManager(core, plugin->_cameraCtrl);
    RemoveManager(core, plugin->_shadow01);
    RemoveManager(core, plugin->_generater);
    RemoveManager(core, plugin->_point01);
    RemoveManager(core, plugin->_bkColor);
    RemoveManager(core, plugin->_sound);
    RemoveManager(core, plugin->_seCtl);
    RemoveManager(core, plugin->_waterPlain);
    RemoveManager(core, plugin->_matCtrl);
    RemoveManager(core, plugin->_actionStarter);
    RemoveManager(core, plugin->_luaManager);
    RemoveManager(core, plugin->_particleCtrl2);
    RemoveManager(core, plugin->_layerCtl);
    RemoveManager(core, plugin->_font);
    RemoveManager(core, plugin->_demoManager);
    RemoveManager(core, plugin->_switchCtrl);
    RemoveManager(core, plugin->_lightCtrl);
    RemoveManager(core, plugin->_numberCtrl);
    RemoveManager(core, plugin->_staticInfoCtl);
    RemoveManager(core, plugin->_movie);
    RemoveManager(core, plugin->_saveUtil);
    RemoveManager(core, plugin->_textureCtrl);
    RemoveManager(core, plugin->_memory);
    RemoveManager(core, plugin->_timer);
}

extern "C" int Gap__Bec__libBecRuntimePlugin__vfunc_20(void) {
    return g_libBecRuntimePlugin_metaObject[0];
}
