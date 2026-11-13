#include "dw4/reflected.h"

extern "C" int igObject_Destroy(igObject *object);
extern "C" int igObject_GetAllocator(igObject *object);
extern "C" int Memory_GetAllocatorBySelector(int selector);
extern "C" void igInsightCore_AddManager(igInsightCore *core, int manager);
extern "C" void igInsightCore_RemoveManager(igInsightCore *core, int manager);
extern "C" unsigned char g_useOwnerAllocator;
extern "C" int kIGMemoryPoolHandleUser0[4];
extern "C" int g_libBecRuntimePlugin_metaObject[4];
extern "C" int beSystem_CreateInstance(int allocator);
extern "C" int be_CreateInstance(int allocator);
extern "C" int beMessenger_CreateInstance(int allocator);
extern "C" int beCri_CreateInstance(int allocator);
extern "C" int beFileListInfoManager_CreateInstance(int allocator);
extern "C" int bePadManager_CreateInstance(int allocator);
extern "C" int beStaticInfoCtl_CreateInstance(int allocator);
extern "C" int beDBManager_CreateInstance(int allocator);
extern "C" int beLua_CreateInstance(int allocator);
extern "C" int beDemoManager_CreateInstance(int allocator);
extern "C" int beBkColor_CreateInstance(int allocator);
extern "C" int beSound_CreateInstance(int allocator);
extern "C" int beSeCtl_CreateInstance(int allocator);
extern "C" int beWaterPlain_CreateInstance(int allocator);
extern "C" int beLayerCtl_CreateInstance(int allocator);
extern "C" int beFont_CreateInstance(int allocator);
extern "C" int beMovie_CreateInstance(int allocator);
extern "C" int beSaveUtil_CreateInstance(int allocator);
extern "C" int beChangePosTransform_CreateInstance(int allocator);
extern "C" int beHitLandModel_CreateInstance(int allocator);
extern "C" int beHitLandDeliv_CreateInstance(int allocator);
extern "C" int beSelectCtrl_CreateInstance(int allocator);
extern "C" int beMeterCtrl_CreateInstance(int allocator);
extern "C" int beTargetObj_CreateInstance(int allocator);
extern "C" int beAction2_CreateInstance(int allocator);
extern "C" int beWeapon_CreateInstance(int allocator);
extern "C" int beCameraCtrl_CreateInstance(int allocator);
extern "C" int beShadow01_CreateInstance(int allocator);
extern "C" int beGenerater_CreateInstance(int allocator);
extern "C" int bePoint01_CreateInstance(int allocator);
extern "C" int beMatCtrl_CreateInstance(int allocator);
extern "C" int beActionStarter_CreateInstance(int allocator);
extern "C" int beParticleCtrl2_CreateInstance(int allocator);
extern "C" int beSwitchCtrl_CreateInstance(int allocator);
extern "C" int beLightCtrl_CreateInstance(int allocator);
extern "C" int beNumberCtrl_CreateInstance(int allocator);
extern "C" int beTextureCtrl_CreateInstance(int allocator);
extern "C" int beTimer_CreateInstance(int allocator);

/* vfunc_21 replaces every manager with a fresh instance, released through the refcount in the low
 * 23 bits of _refCount and allocated from the plugin's own allocator when g_useOwnerAllocator is set,
 * then adds each manager that exists to the core. vfunc_22 removes them again. */
static inline int PluginAllocator(libBecRuntimePlugin *plugin) {
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

extern "C" void Gap__Bec__libBecRuntimePlugin__vfunc_21(libBecRuntimePlugin *plugin, igInsightCore *core) {
    REPLACE_MANAGER(_system, beSystem_CreateInstance)
    REPLACE_MANAGER(_luaInterface, be_CreateInstance)
    REPLACE_MANAGER(_messenger, beMessenger_CreateInstance)
    REPLACE_MANAGER(_cri, beCri_CreateInstance)
    REPLACE_MANAGER(_fileList, beFileListInfoManager_CreateInstance)
    REPLACE_MANAGER(_padManager, bePadManager_CreateInstance)
    REPLACE_MANAGER(_staticInfoCtl, beStaticInfoCtl_CreateInstance)
    REPLACE_MANAGER(_dbManager, beDBManager_CreateInstance)
    REPLACE_MANAGER(_luaManager, beLua_CreateInstance)
    REPLACE_MANAGER(_demoManager, beDemoManager_CreateInstance)
    REPLACE_MANAGER(_bkColor, beBkColor_CreateInstance)
    REPLACE_MANAGER(_sound, beSound_CreateInstance)
    REPLACE_MANAGER(_seCtl, beSeCtl_CreateInstance)
    REPLACE_MANAGER(_waterPlain, beWaterPlain_CreateInstance)
    REPLACE_MANAGER(_layerCtl, beLayerCtl_CreateInstance)
    REPLACE_MANAGER(_font, beFont_CreateInstance)
    REPLACE_MANAGER(_movie, beMovie_CreateInstance)
    REPLACE_MANAGER(_saveUtil, beSaveUtil_CreateInstance)
    REPLACE_MANAGER(_cpTransform, beChangePosTransform_CreateInstance)
    REPLACE_MANAGER(_hitLandModel, beHitLandModel_CreateInstance)
    REPLACE_MANAGER(_hitLandDeliv, beHitLandDeliv_CreateInstance)
    REPLACE_MANAGER(_selectCtrl, beSelectCtrl_CreateInstance)
    REPLACE_MANAGER(_meterCtrl, beMeterCtrl_CreateInstance)
    REPLACE_MANAGER(_targetObj, beTargetObj_CreateInstance)
    REPLACE_MANAGER(_action2, beAction2_CreateInstance)
    REPLACE_MANAGER(_weapon, beWeapon_CreateInstance)
    REPLACE_MANAGER(_cameraCtrl, beCameraCtrl_CreateInstance)
    REPLACE_MANAGER(_shadow01, beShadow01_CreateInstance)
    REPLACE_MANAGER(_generater, beGenerater_CreateInstance)
    REPLACE_MANAGER(_point01, bePoint01_CreateInstance)
    REPLACE_MANAGER(_matCtrl, beMatCtrl_CreateInstance)
    REPLACE_MANAGER(_actionStarter, beActionStarter_CreateInstance)
    REPLACE_MANAGER(_particleCtrl2, beParticleCtrl2_CreateInstance)
    REPLACE_MANAGER(_switchCtrl, beSwitchCtrl_CreateInstance)
    REPLACE_MANAGER(_lightCtrl, beLightCtrl_CreateInstance)
    REPLACE_MANAGER(_numberCtrl, beNumberCtrl_CreateInstance)
    REPLACE_MANAGER(_textureCtrl, beTextureCtrl_CreateInstance)
    REPLACE_MANAGER(_timer, beTimer_CreateInstance)

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
