/* 0x00187f40 igSphere_Register: registers class igSphere with the object system, derived from igVolume.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVolume_Register[];
extern char igSphere_GetVTable[];
extern char thunk_igSphere_GetMetaObject[];
extern char igVolume_GetPublishedMetaObject_00187fd0[];
extern char thunk_FUN_0018d480[];
extern char s_igSphere_className_004e0a78[];
extern char g_igSphere_metaObject_00560fa0[];
int FUN_00186a40();
int igMetaObject_RegisterClass();
int igSphere_InitFields();

void igSphere_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0,                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igSphere_metaObject_00560fa0,           /* published MetaObject slot */
        igVolume_Register,                        /* base class registrar */
        igVolume_GetPublishedMetaObject_00187fd0, /* base class MetaObject accessor */
        thunk_igSphere_GetMetaObject,             /* own MetaObject accessor (stored at +0x54) */
        s_igSphere_className_004e0a78,            /* class name */
        0x18,                                     /* instance size */
        igSphere_GetVTable,                       /* vtable getter */
        &igSphere_InitFields,                     /* field adder */
        thunk_FUN_0018d480,                       /* extra callback item */
        0                                         /* callback list */
    );
}
