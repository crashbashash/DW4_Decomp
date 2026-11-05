/* 0x003a2130 - Gap::Bec::libBecRuntimePlugin::vfunc_21: build the runtime plugin's subsystem objects.
 *
 * Phase 1 replaces every _member with a freshly created object: the old reference is released
 * (refcount in the low 23 bits of +4, igObject_Destroy at zero) and the creator is handed the
 * plugin's allocator -- the object's own allocator when the global override flag (GPR_00554c14)
 * is set, otherwise the allocator selected by DAT_00587108.  Phase 2 registers each member that
 * exists with the context passed in arg1 (FUN_00236ab0; vfunc_22 performs the same walk).
 * Evidence: asm/Gap__Bec__libBecRuntimePlugin__vfunc_21.s (38 repeated create blocks, 39 registrations).
 *
 * Compiler: the alternate (combat) MWCC at -O3,p -- its 8-byte alignment nops before the join
 * labels are part of retail's layout (see archived near-miss note wave15). */
#include "dw4/reflected.h"
struct RefCountedObject { int w0; int refCount; };
extern "C" {
int FUN_0033f410(int);
int FUN_00340cc0(int);
int FUN_00341340(int);
int FUN_00342310(int);
int FUN_00342970(int);
int FUN_00342ca0(int);
int FUN_00343490(int);
int FUN_00343760(int);
int FUN_003442b0(int);
int FUN_00344e40(int);
int FUN_00345a00(int);
int FUN_003464f0(int);
int FUN_00346c80(int);
int FUN_0034b9e0(int);
int FUN_0034c630(int);
int FUN_0034c8a0(int);
int FUN_0034e360(int);
int FUN_0034ef30(int);
int FUN_00357660(int);
int FUN_003578d0(int);
int FUN_0035a710(int);
int FUN_0035b730(int);
int FUN_0035c010(int);
int FUN_0035caa0(int);
int FUN_0035d780(int);
int FUN_0035eb90(int);
int FUN_00360b70(int);
int FUN_00361e50(int);
int FUN_003627f0(int);
int FUN_00363210(int);
int FUN_003660d0(int);
int FUN_00367860(int);
int FUN_00368710(int);
int FUN_00369820(int);
int FUN_00369dc0(int);
int FUN_0036c030(int);
int FUN_0036dd30(int);
int FUN_0036dfa0(int);
int FUN_00236ab0(int, int);
int Memory_GetAllocatorBySelector(int);
int igObject_Destroy(RefCountedObject *);
int igObject_GetAllocator(libBecRuntimePlugin *);
extern int DAT_00587108[4];
extern unsigned char GPR_00554c14;
}

/* One-line macros only: tools/units.py cannot split a unit around a continued #define. */
#define PICK_ALLOCATOR(owner) allocator = igObject_GetAllocator(owner); allocator = GPR_00554c14 != 0 ? allocator : Memory_GetAllocatorBySelector(DAT_00587108[0]);
#define RELEASE_REF(ref) if ((ref) != 0) { (ref)->refCount = (ref)->refCount - 1; if (((ref)->refCount & 0x7FFFFF) == 0) { igObject_Destroy(ref); } }

extern "C" {
void Gap__Bec__libBecRuntimePlugin__vfunc_21(libBecRuntimePlugin *plugin, int context);
}
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
