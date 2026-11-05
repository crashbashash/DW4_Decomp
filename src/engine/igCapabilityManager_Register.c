/* 0x0014fdf0 igCapabilityManager_Register: registers class igCapabilityManager with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igCapabilityManager_GetMetaObject[];
extern char igObject_Register[];
extern char s_igCapabilityManager_className_004dcdf0[];
extern char g_igCapabilityManager_metaObject_0055fef8[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();

void igCapabilityManager_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1,                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCapabilityManager_metaObject_0055fef8, /* published MetaObject slot */
        igObject_Register,                         /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,     /* base class MetaObject accessor */
        thunk_igCapabilityManager_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igCapabilityManager_className_004dcdf0,  /* class name */
        8,                                         /* instance size */
        0,                                         /* vtable getter */
        0,                                         /* field adder */
        0,                                         /* extra callback item */
        0                                          /* callback list */
    );
}
