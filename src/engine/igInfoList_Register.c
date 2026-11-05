/* 0x002c3530 igInfoList_Register: registers class igInfoList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igInfoList_GetVTable[];
extern char thunk_igInfoList_GetMetaObject[];
extern char g_igInfoList_callbackList_004c0610[];
extern char s_igInfoList_className_004f7008[];
extern char g_igInfoList_metaObject_00586120[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igInfoList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igInfoList_metaObject_00586120,    /* published MetaObject slot */
        igObjectList_Register,               /* base class registrar */
        igObjectList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igInfoList_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        s_igInfoList_className_004f7008,     /* class name */
        0x14,                                /* instance size */
        igInfoList_GetVTable,                /* vtable getter */
        0,                                   /* field adder */
        0,                                   /* extra callback item */
        g_igInfoList_callbackList_004c0610   /* callback list */
    );
}
