/* 0x00188530 igPlane_Register: registers class igPlane with the object system, derived from igVolume.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVolume_Register[];
extern char igVolume_GetPublishedMetaObject[];
extern char igPlane_GetVTable[];
extern char thunk_igPlane_GetMetaObject[];
extern char thunk_FUN_0018c660[];
extern char igPlane_className[];
extern char g_igPlane_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();
int igPlane_InitFields();

void igPlane_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0,                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igPlane_metaObject,            /* published MetaObject slot */
        igVolume_Register,                        /* base class registrar */
        igVolume_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igPlane_GetMetaObject,              /* own MetaObject accessor (stored at +0x54) */
        igPlane_className,             /* class name */
        0x1C,                                     /* instance size */
        igPlane_GetVTable,                        /* vtable getter */
        &igPlane_InitFields,                      /* field adder */
        thunk_FUN_0018c660,                       /* extra callback item */
        0                                         /* callback list */
    );
}
