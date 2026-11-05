/* 0x002bcd40 igObjectStringMap_Register: registers class igObjectStringMap with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObjectStringMap_GetVTable[];
extern char thunk_igObjectStringMap_GetMetaObject[];
extern char igObject_Register[];
extern char g_igObjectStringMap_callbackList_004bfa78[];
extern char s_igObjectStringMap_className_004f6400[];
extern char g_igObjectStringMap_metaObject_00585b08[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igObjectStringMap_InitFields();

void igObjectStringMap_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igObjectStringMap_metaObject_00585b08, /* published MetaObject slot */
        igObject_Register,                       /* base class registrar */
        igObject_GetMetaObject_ParentAccessor,   /* base class MetaObject accessor */
        thunk_igObjectStringMap_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igObjectStringMap_className_004f6400,  /* class name */
        0x10,                                    /* instance size */
        igObjectStringMap_GetVTable,             /* vtable getter */
        &igObjectStringMap_InitFields,           /* field adder */
        0,                                       /* extra callback item */
        g_igObjectStringMap_callbackList_004bfa78  /* callback list */
    );
}
