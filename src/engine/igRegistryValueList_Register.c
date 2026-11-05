/* 0x002bb480 igRegistryValueList_Register: registers class igRegistryValueList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igRegistryValueList_GetVTable[];
extern char thunk_igRegistryValueList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igRegistryValueList_callbackList_004bf908[];
extern char s_igRegistryValueList_className_004f6210[];
extern char g_igRegistryValueList_metaObject_00585a38[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igRegistryValueList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0,                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igRegistryValueList_metaObject_00585a38, /* published MetaObject slot */
        igObjectList_Register,                     /* base class registrar */
        igObjectList_GetPublishedMetaObject,       /* base class MetaObject accessor */
        thunk_igRegistryValueList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igRegistryValueList_className_004f6210,  /* class name */
        0x14,                                      /* instance size */
        igRegistryValueList_GetVTable,             /* vtable getter */
        0,                                         /* field adder */
        0,                                         /* extra callback item */
        g_igRegistryValueList_callbackList_004bf908  /* callback list */
    );
}
