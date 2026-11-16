#include "dw4/reflected.h"
#include "dw4/be.h"
#include "dw4/beAction2.h"
#include "dw4/beActionStarter.h"
#include "dw4/beBkColor.h"
#include "dw4/beCameraCtrl.h"
#include "dw4/beChangePosTransform.h"
#include "dw4/beCri.h"
#include "dw4/beDBManager.h"
#include "dw4/beDemoManager.h"
#include "dw4/beFileListInfoManager.h"
#include "dw4/beFont.h"
#include "dw4/beGenerater.h"
#include "dw4/beHitLandDeliv.h"
#include "dw4/beHitLandModel.h"
#include "dw4/beLayerCtl.h"
#include "dw4/beLightCtrl.h"
#include "dw4/beLua.h"
#include "dw4/beMatCtrl.h"
#include "dw4/beMessenger.h"
#include "dw4/beMeterCtrl.h"
#include "dw4/beMovie.h"
#include "dw4/beNumberCtrl.h"
#include "dw4/bePadManager.h"
#include "dw4/beParticleCtrl2.h"
#include "dw4/bePoint01.h"
#include "dw4/beSaveUtil.h"
#include "dw4/beSeCtl.h"
#include "dw4/beSelectCtrl.h"
#include "dw4/beShadow01.h"
#include "dw4/beSound.h"
#include "dw4/beStaticInfoCtl.h"
#include "dw4/beSwitchCtrl.h"
#include "dw4/beSystem.h"
#include "dw4/beTargetObj.h"
#include "dw4/beTextureCtrl.h"
#include "dw4/beTimer.h"
#include "dw4/beWaterPlain.h"
#include "dw4/beWeapon.h"
#include "dw4/igInsightCore.h"
#include "dw4/igMemoryPoolContext.h"
#include "dw4/igObject.h"
#include "dw4/libBecRuntimePlugin.h"


/* vfunc_21 replaces every manager with a fresh instance, released through the refcount in the low
 * 23 bits of _refCount and allocated from the plugin's own allocator when g_useOwnerAllocator is set,
 * then adds each manager that exists to the core. vfunc_22 removes them again. */
static inline int PluginAllocator(libBecRuntimePlugin *plugin) {
    int allocator = (int)igObject_GetAllocator(plugin);
    return g_useOwnerAllocator != 0 ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0);
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
