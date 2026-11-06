/* 0x002bebc0 igMetaFieldInfo_Register: registers class igMetaFieldInfo with the object system, derived from igInfo.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igInfo_GetPublishedMetaObject[];
extern char igMetaFieldInfo_GetVTable[];
extern char thunk_igMetaFieldInfo_GetMetaObject[];
extern char igInfo_Register[];
extern char igMetaFieldInfo_className[];
extern char g_igMetaFieldInfo_metaObject_00585cb8[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igMetaFieldInfo_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMetaFieldInfo_metaObject_00585cb8,  /* published MetaObject slot */
        igInfo_Register,                        /* base class registrar */
        igInfo_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igMetaFieldInfo_GetMetaObject,    /* own MetaObject accessor (stored at +0x54) */
        igMetaFieldInfo_className,   /* class name */
        0x14,                                   /* instance size */
        igMetaFieldInfo_GetVTable,              /* vtable getter */
        0,                                      /* field adder */
        0,                                      /* extra callback item */
        0                                       /* callback list */
    );
}
