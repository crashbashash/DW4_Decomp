/* 0x002c8c20 igMetaFieldList_Register: registers class igMetaFieldList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igMetaFieldList_GetVTable[];
extern char thunk_igMetaFieldList_GetMetaObject[];
extern char g_igMetaFieldList_callbackList_004c13d8[];
extern char s_igMetaFieldList_className_004f84b0[];
extern char g_igMetaFieldList_metaObject_005867c0[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igMetaFieldList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMetaFieldList_metaObject_005867c0, /* published MetaObject slot */
        igObjectList_Register,                 /* base class registrar */
        igObjectList_GetPublishedMetaObject,   /* base class MetaObject accessor */
        thunk_igMetaFieldList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igMetaFieldList_className_004f84b0,  /* class name */
        0x14,                                  /* instance size */
        igMetaFieldList_GetVTable,             /* vtable getter */
        0,                                     /* field adder */
        0,                                     /* extra callback item */
        g_igMetaFieldList_callbackList_004c13d8  /* callback list */
    );
}
