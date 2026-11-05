/* 0x002c74c0 igDirectory_Register: registers class igDirectory with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igDirectory_GetVTable[];
extern char thunk_igDirectory_GetMetaObject[];
extern char g_igDirectory_callbackList_004c10f0[];
extern char s_igDirectory_className_004f8150[];
extern char g_igDirectory_metaObject_00586668[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
extern int thunk_FUN_002d7b00[4];
int igDirectory_InitFields();

void igDirectory_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDirectory_metaObject_00586668,   /* published MetaObject slot */
        igObjectList_Register,               /* base class registrar */
        igObjectList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igDirectory_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        s_igDirectory_className_004f8150,    /* class name */
        0x48,                                /* instance size */
        igDirectory_GetVTable,               /* vtable getter */
        &igDirectory_InitFields,             /* field adder */
        thunk_FUN_002d7b00,                  /* extra callback item */
        g_igDirectory_callbackList_004c10f0  /* callback list */
    );
}
