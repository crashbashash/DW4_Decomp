/* 0x0018a790 igAABox_Register: registers class igAABox with the object system, derived from igVolume.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVolume_Register[];
extern char igVolume_GetPublishedMetaObject[];
extern char igAABox_GetVTable[];
extern char thunk_igAABox_GetMetaObject[];
extern char thunk_FUN_0018a8f0[];
extern char igAABox_className[];
extern char g_igAABox_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();
int igAABox_InitFields();

void igAABox_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0,                                        /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAABox_metaObject,            /* published MetaObject slot */
        igVolume_Register,                        /* base class registrar */
        igVolume_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igAABox_GetMetaObject,              /* own MetaObject accessor (stored at +0x54) */
        igAABox_className,             /* class name */
        0x20,                                     /* instance size */
        igAABox_GetVTable,                        /* vtable getter */
        &igAABox_InitFields,                      /* field adder */
        thunk_FUN_0018a8f0,                       /* extra callback item */
        0                                         /* callback list */
    );
}
