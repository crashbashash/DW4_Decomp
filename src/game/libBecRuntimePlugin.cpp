#include "dw4/reflected.h"

extern "C" int FUN_0033f410(int);
extern "C" int FUN_00340cc0(int);
extern "C" int FUN_00341340(int);
extern "C" int FUN_00342310(int);
extern "C" int FUN_00342970(int);
extern "C" int FUN_00342ca0(int);
extern "C" int FUN_00343490(int);
extern "C" int FUN_00343760(int);
extern "C" int FUN_003442b0(int);
extern "C" int FUN_00344e40(int);
extern "C" int FUN_00345a00(int);
extern "C" int FUN_003464f0(int);
extern "C" int FUN_00346c80(int);
extern "C" int FUN_0034b9e0(int);
extern "C" int FUN_0034c630(int);
extern "C" int FUN_0034c8a0(int);
extern "C" int FUN_0034e360(int);
extern "C" int FUN_0034ef30(int);
extern "C" int FUN_00357660(int);
extern "C" int FUN_003578d0(int);
extern "C" int FUN_0035a710(int);
extern "C" int FUN_0035b730(int);
extern "C" int FUN_0035c010(int);
extern "C" int FUN_0035caa0(int);
extern "C" int FUN_0035d780(int);
extern "C" int FUN_0035eb90(int);
extern "C" int FUN_00360b70(int);
extern "C" int FUN_00361e50(int);
extern "C" int FUN_003627f0(int);
extern "C" int FUN_00363210(int);
extern "C" int FUN_003660d0(int);
extern "C" int FUN_00367860(int);
extern "C" int FUN_00368710(int);
extern "C" int FUN_00369820(int);
extern "C" int FUN_00369dc0(int);
extern "C" int FUN_0036c030(int);
extern "C" int FUN_0036dd30(int);
extern "C" int FUN_0036dfa0(int);
extern "C" int FUN_00236ab0(int, int);
extern "C" int Memory_GetAllocatorBySelector(int);
extern "C" int FUN_00236b10(int, int);
extern "C" int Gap__Bec__libBecRuntimePlugin__vfunc_20(void);
/* Builds the plugin's subsystem objects. Phase 1 replaces every _member with a freshly created
 * object: the old reference is released (refcount in the low 23 bits of +4, igObject_Destroy at
 * zero) and the creator is handed the plugin's allocator, which is the object's own allocator when
 * the global override flag is set and the selected allocator otherwise. Phase 2 registers each
 * member that exists with the context passed in arg1. */

struct RefCountedObject { int w0; int refCount; };
extern "C" int igObject_Destroy(RefCountedObject *);
extern "C" int igObject_GetAllocator(libBecRuntimePlugin *);
extern "C" int g_ndmwAllocatorSelector[4];
extern "C" unsigned char GPR_00554c14;
extern "C" void Gap__Bec__libBecRuntimePlugin__vfunc_21(libBecRuntimePlugin *plugin, int context);
extern "C" void Gap__Bec__libBecRuntimePlugin__vfunc_22(libBecRuntimePlugin *arg0, int arg1);
extern "C" int g_libBecRuntimePlugin_metaObject[4];

#define PICK_ALLOCATOR(owner) allocator = igObject_GetAllocator(owner); allocator = GPR_00554c14 != 0 ? allocator : Memory_GetAllocatorBySelector(g_ndmwAllocatorSelector[0]);
#define RELEASE_REF(ref) if ((ref) != 0) { (ref)->refCount = (ref)->refCount - 1; if (((ref)->refCount & 0x7FFFFF) == 0) { igObject_Destroy(ref); } }
void Gap__Bec__libBecRuntimePlugin__vfunc_21(libBecRuntimePlugin *plugin, int context) {
    int allocator;
    struct RefCountedObject *old;
    int object;

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_system;
    RELEASE_REF(old)
    plugin->_system = (int)FUN_00342ca0(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_luaInterface;
    RELEASE_REF(old)
    plugin->_luaInterface = (int)FUN_0036dfa0(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_messenger;
    RELEASE_REF(old)
    plugin->_messenger = (int)FUN_003578d0(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_cri;
    RELEASE_REF(old)
    plugin->_cri = (int)FUN_00367860(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_fileList;
    RELEASE_REF(old)
    plugin->_fileList = (int)FUN_003627f0(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_padManager;
    RELEASE_REF(old)
    plugin->_padManager = (int)FUN_0034c8a0(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_staticInfoCtl;
    RELEASE_REF(old)
    plugin->_staticInfoCtl = (int)FUN_00343760(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_dbManager;
    RELEASE_REF(old)
    plugin->_dbManager = (int)FUN_003660d0(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_luaManager;
    RELEASE_REF(old)
    plugin->_luaManager = (int)FUN_0035b730(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_demoManager;
    RELEASE_REF(old)
    plugin->_demoManager = (int)FUN_00363210(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_bkColor;
    RELEASE_REF(old)
    plugin->_bkColor = (int)FUN_00369dc0(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_sound;
    RELEASE_REF(old)
    plugin->_sound = (int)FUN_003442b0(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_seCtl;
    RELEASE_REF(old)
    plugin->_seCtl = (int)FUN_003464f0(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_waterPlain;
    RELEASE_REF(old)
    plugin->_waterPlain = (int)FUN_00340cc0(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_layerCtl;
    RELEASE_REF(old)
    plugin->_layerCtl = (int)FUN_0035caa0(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_font;
    RELEASE_REF(old)
    plugin->_font = (int)FUN_00361e50(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_movie;
    RELEASE_REF(old)
    plugin->_movie = (int)FUN_0034ef30(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_saveUtil;
    RELEASE_REF(old)
    plugin->_saveUtil = (int)FUN_00346c80(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_cpTransform;
    RELEASE_REF(old)
    plugin->_cpTransform = (int)FUN_00368710(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_hitLandModel;
    RELEASE_REF(old)
    plugin->_hitLandModel = (int)FUN_0035d780(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_hitLandDeliv;
    RELEASE_REF(old)
    plugin->_hitLandDeliv = (int)FUN_0035eb90(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_selectCtrl;
    RELEASE_REF(old)
    plugin->_selectCtrl = (int)FUN_00345a00(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_meterCtrl;
    RELEASE_REF(old)
    plugin->_meterCtrl = (int)FUN_00357660(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_targetObj;
    RELEASE_REF(old)
    plugin->_targetObj = (int)FUN_00342970(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_action2;
    RELEASE_REF(old)
    plugin->_action2 = (int)FUN_0036dd30(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_weapon;
    RELEASE_REF(old)
    plugin->_weapon = (int)FUN_0033f410(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_cameraCtrl;
    RELEASE_REF(old)
    plugin->_cameraCtrl = (int)FUN_00369820(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_shadow01;
    RELEASE_REF(old)
    plugin->_shadow01 = (int)FUN_00344e40(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_generater;
    RELEASE_REF(old)
    plugin->_generater = (int)FUN_00360b70(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_point01;
    RELEASE_REF(old)
    plugin->_point01 = (int)FUN_0034b9e0(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_matCtrl;
    RELEASE_REF(old)
    plugin->_matCtrl = (int)FUN_0035a710(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_actionStarter;
    RELEASE_REF(old)
    plugin->_actionStarter = (int)FUN_0036c030(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_particleCtrl2;
    RELEASE_REF(old)
    plugin->_particleCtrl2 = (int)FUN_0034c630(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_switchCtrl;
    RELEASE_REF(old)
    plugin->_switchCtrl = (int)FUN_00343490(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_lightCtrl;
    RELEASE_REF(old)
    plugin->_lightCtrl = (int)FUN_0035c010(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_numberCtrl;
    RELEASE_REF(old)
    plugin->_numberCtrl = (int)FUN_0034e360(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_textureCtrl;
    RELEASE_REF(old)
    plugin->_textureCtrl = (int)FUN_00342310(allocator);

    PICK_ALLOCATOR(plugin)
    old = (struct RefCountedObject *)plugin->_timer;
    RELEASE_REF(old)
    plugin->_timer = (int)FUN_00341340(allocator);

    object = plugin->_system;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_luaInterface;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_messenger;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_cri;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_fileList;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_padManager;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_staticInfoCtl;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_dbManager;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_luaManager;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_demoManager;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_bkColor;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_sound;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_seCtl;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_layerCtl;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_font;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_movie;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_saveUtil;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_waterPlain;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_cpTransform;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_hitLandModel;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_hitLandDeliv;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_selectCtrl;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_meterCtrl;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_targetObj;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_action2;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_weapon;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_cameraCtrl;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_shadow01;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_generater;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_point01;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_matCtrl;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_actionStarter;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_particleCtrl2;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_switchCtrl;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_lightCtrl;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_numberCtrl;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_textureCtrl;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_memory;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
    object = plugin->_timer;
    if (object != 0) {
        FUN_00236ab0(context, object);
    }
}

#undef RELEASE_REF
#undef PICK_ALLOCATOR

void Gap__Bec__libBecRuntimePlugin__vfunc_22(libBecRuntimePlugin *arg0, int arg1) {
    int temp_a1;
    int temp_a1_10;
    int temp_a1_11;
    int temp_a1_12;
    int temp_a1_13;
    int temp_a1_14;
    int temp_a1_15;
    int temp_a1_16;
    int temp_a1_17;
    int temp_a1_18;
    int temp_a1_19;
    int temp_a1_20;
    int temp_a1_21;
    int temp_a1_22;
    int temp_a1_23;
    int temp_a1_24;
    int temp_a1_25;
    int temp_a1_26;
    int temp_a1_27;
    int temp_a1_28;
    int temp_a1_29;
    int temp_a1_2;
    int temp_a1_30;
    int temp_a1_31;
    int temp_a1_32;
    int temp_a1_33;
    int temp_a1_34;
    int temp_a1_35;
    int temp_a1_36;
    int temp_a1_37;
    int temp_a1_38;
    int temp_a1_39;
    int temp_a1_3;
    int temp_a1_4;
    int temp_a1_5;
    int temp_a1_6;
    int temp_a1_7;
    int temp_a1_8;
    int temp_a1_9;

    temp_a1 = arg0->_system;
    if (temp_a1 != 0) {
        FUN_00236b10(arg1, temp_a1);
    }
    temp_a1_2 = arg0->_luaInterface;
    if (temp_a1_2 != 0) {
        FUN_00236b10(arg1, temp_a1_2);
    }
    temp_a1_3 = arg0->_messenger;
    if (temp_a1_3 != 0) {
        FUN_00236b10(arg1, temp_a1_3);
    }
    temp_a1_4 = arg0->_fileList;
    if (temp_a1_4 != 0) {
        FUN_00236b10(arg1, temp_a1_4);
    }
    temp_a1_5 = arg0->_cri;
    if (temp_a1_5 != 0) {
        FUN_00236b10(arg1, temp_a1_5);
    }
    temp_a1_6 = arg0->_padManager;
    if (temp_a1_6 != 0) {
        FUN_00236b10(arg1, temp_a1_6);
    }
    temp_a1_7 = arg0->_dbManager;
    if (temp_a1_7 != 0) {
        FUN_00236b10(arg1, temp_a1_7);
    }
    temp_a1_8 = arg0->_cpTransform;
    if (temp_a1_8 != 0) {
        FUN_00236b10(arg1, temp_a1_8);
    }
    temp_a1_9 = arg0->_hitLandModel;
    if (temp_a1_9 != 0) {
        FUN_00236b10(arg1, temp_a1_9);
    }
    temp_a1_10 = arg0->_hitLandDeliv;
    if (temp_a1_10 != 0) {
        FUN_00236b10(arg1, temp_a1_10);
    }
    temp_a1_11 = arg0->_selectCtrl;
    if (temp_a1_11 != 0) {
        FUN_00236b10(arg1, temp_a1_11);
    }
    temp_a1_12 = arg0->_targetObj;
    if (temp_a1_12 != 0) {
        FUN_00236b10(arg1, temp_a1_12);
    }
    temp_a1_13 = arg0->_meterCtrl;
    if (temp_a1_13 != 0) {
        FUN_00236b10(arg1, temp_a1_13);
    }
    temp_a1_14 = arg0->_action2;
    if (temp_a1_14 != 0) {
        FUN_00236b10(arg1, temp_a1_14);
    }
    temp_a1_15 = arg0->_weapon;
    if (temp_a1_15 != 0) {
        FUN_00236b10(arg1, temp_a1_15);
    }
    temp_a1_16 = arg0->_cameraCtrl;
    if (temp_a1_16 != 0) {
        FUN_00236b10(arg1, temp_a1_16);
    }
    temp_a1_17 = arg0->_shadow01;
    if (temp_a1_17 != 0) {
        FUN_00236b10(arg1, temp_a1_17);
    }
    temp_a1_18 = arg0->_generater;
    if (temp_a1_18 != 0) {
        FUN_00236b10(arg1, temp_a1_18);
    }
    temp_a1_19 = arg0->_point01;
    if (temp_a1_19 != 0) {
        FUN_00236b10(arg1, temp_a1_19);
    }
    temp_a1_20 = arg0->_bkColor;
    if (temp_a1_20 != 0) {
        FUN_00236b10(arg1, temp_a1_20);
    }
    temp_a1_21 = arg0->_sound;
    if (temp_a1_21 != 0) {
        FUN_00236b10(arg1, temp_a1_21);
    }
    temp_a1_22 = arg0->_seCtl;
    if (temp_a1_22 != 0) {
        FUN_00236b10(arg1, temp_a1_22);
    }
    temp_a1_23 = arg0->_waterPlain;
    if (temp_a1_23 != 0) {
        FUN_00236b10(arg1, temp_a1_23);
    }
    temp_a1_24 = arg0->_matCtrl;
    if (temp_a1_24 != 0) {
        FUN_00236b10(arg1, temp_a1_24);
    }
    temp_a1_25 = arg0->_actionStarter;
    if (temp_a1_25 != 0) {
        FUN_00236b10(arg1, temp_a1_25);
    }
    temp_a1_26 = arg0->_luaManager;
    if (temp_a1_26 != 0) {
        FUN_00236b10(arg1, temp_a1_26);
    }
    temp_a1_27 = arg0->_particleCtrl2;
    if (temp_a1_27 != 0) {
        FUN_00236b10(arg1, temp_a1_27);
    }
    temp_a1_28 = arg0->_layerCtl;
    if (temp_a1_28 != 0) {
        FUN_00236b10(arg1, temp_a1_28);
    }
    temp_a1_29 = arg0->_font;
    if (temp_a1_29 != 0) {
        FUN_00236b10(arg1, temp_a1_29);
    }
    temp_a1_30 = arg0->_demoManager;
    if (temp_a1_30 != 0) {
        FUN_00236b10(arg1, temp_a1_30);
    }
    temp_a1_31 = arg0->_switchCtrl;
    if (temp_a1_31 != 0) {
        FUN_00236b10(arg1, temp_a1_31);
    }
    temp_a1_32 = arg0->_lightCtrl;
    if (temp_a1_32 != 0) {
        FUN_00236b10(arg1, temp_a1_32);
    }
    temp_a1_33 = arg0->_numberCtrl;
    if (temp_a1_33 != 0) {
        FUN_00236b10(arg1, temp_a1_33);
    }
    temp_a1_34 = arg0->_staticInfoCtl;
    if (temp_a1_34 != 0) {
        FUN_00236b10(arg1, temp_a1_34);
    }
    temp_a1_35 = arg0->_movie;
    if (temp_a1_35 != 0) {
        FUN_00236b10(arg1, temp_a1_35);
    }
    temp_a1_36 = arg0->_saveUtil;
    if (temp_a1_36 != 0) {
        FUN_00236b10(arg1, temp_a1_36);
    }
    temp_a1_37 = arg0->_textureCtrl;
    if (temp_a1_37 != 0) {
        FUN_00236b10(arg1, temp_a1_37);
    }
    temp_a1_38 = arg0->_memory;
    if (temp_a1_38 != 0) {
        FUN_00236b10(arg1, temp_a1_38);
    }
    temp_a1_39 = arg0->_timer;
    if (temp_a1_39 != 0) {
        FUN_00236b10(arg1, temp_a1_39);
    }
}

int Gap__Bec__libBecRuntimePlugin__vfunc_20(void)
{
    return g_libBecRuntimePlugin_metaObject[0];
}
