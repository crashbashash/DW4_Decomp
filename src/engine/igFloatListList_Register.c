/* 0x002c96c0 igFloatListList_Register: registers class igFloatListList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igFloatListList_GetVTable[];
extern char thunk_igFloatListList_GetMetaObject[];
extern char g_igFloatListList_callbackList_004c13f8[];
extern char s_igFloatListList_className_004f8540[];
extern char g_igFloatListList_metaObject_00586800[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igFloatListList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igFloatListList_metaObject_00586800, /* published MetaObject slot */
        igObjectList_Register,                 /* base class registrar */
        igObjectList_GetPublishedMetaObject,   /* base class MetaObject accessor */
        thunk_igFloatListList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igFloatListList_className_004f8540,  /* class name */
        0x14,                                  /* instance size */
        igFloatListList_GetVTable,             /* vtable getter */
        0,                                     /* field adder */
        0,                                     /* extra callback item */
        g_igFloatListList_callbackList_004c13f8  /* callback list */
    );
}
