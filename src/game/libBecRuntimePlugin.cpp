#include "dw4/support/reflected.h"
#include "dw4/game/be.h"
#include "dw4/game/beAction2.h"
#include "dw4/game/beActionStarter.h"
#include "dw4/game/beBkColor.h"
#include "dw4/game/beCameraCtrl.h"
#include "dw4/game/beChangePosTransform.h"
#include "dw4/game/beCri.h"
#include "dw4/game/beDBManager.h"
#include "dw4/game/beDemoManager.h"
#include "dw4/game/beFileListInfoManager.h"
#include "dw4/game/beFont.h"
#include "dw4/game/beGenerater.h"
#include "dw4/game/beHitLandDeliv.h"
#include "dw4/game/beHitLandModel.h"
#include "dw4/game/beLayerCtl.h"
#include "dw4/game/beLightCtrl.h"
#include "dw4/game/beLua.h"
#include "dw4/game/beMatCtrl.h"
#include "dw4/game/beMessenger.h"
#include "dw4/game/beMeterCtrl.h"
#include "dw4/game/beMovie.h"
#include "dw4/game/beNumberCtrl.h"
#include "dw4/game/bePadManager.h"
#include "dw4/game/beParticleCtrl2.h"
#include "dw4/game/bePoint01.h"
#include "dw4/game/beSaveUtil.h"
#include "dw4/game/beSeCtl.h"
#include "dw4/game/beSelectCtrl.h"
#include "dw4/game/beShadow01.h"
#include "dw4/game/beSound.h"
#include "dw4/game/beStaticInfoCtl.h"
#include "dw4/game/beSwitchCtrl.h"
#include "dw4/game/beSystem.h"
#include "dw4/game/beTargetObj.h"
#include "dw4/game/beTextureCtrl.h"
#include "dw4/game/beTimer.h"
#include "dw4/game/beWaterPlain.h"
#include "dw4/game/beWeapon.h"
#include "dw4/insight/igInsightCore.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igObject.h"
#include "dw4/game/libBecRuntimePlugin.h"


/* vfunc_21 replaces every manager with a fresh instance, released through the refcount in the low
 * 23 bits of _refCount and allocated from the plugin's own allocator when g_useOwnerAllocator is set,
 * then adds each manager that exists to the core. vfunc_22 removes them again. */
static inline int PluginAllocator(libBecRuntimePlugin *plugin) {
    int allocator = (int)((Gap::Core::igObject *)plugin)->getMemoryPool();
    return g_useOwnerAllocator != 0 ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0);
}

static inline void ReleaseRef(int field) {
    igObject *object = (igObject *)field;
    igObject::release(object);
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

#define REPLACE_MANAGER(field, create) { int allocator = PluginAllocator(plugin); ReleaseRef(plugin->field); plugin->field = (int)create(allocator); }

extern "C" void libBecRuntimePlugin_Attach(libBecRuntimePlugin *plugin, igInsightCore *core) {
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

extern "C" void libBecRuntimePlugin_Detach(libBecRuntimePlugin *plugin, igInsightCore *core) {
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

extern "C" igMetaObject *libBecRuntimePlugin_GetMeta(void) {
    return g_libBecRuntimePlugin_metaObject;
}
