/* 0x0044bae0 igViewList_Register: registers class igViewList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igViewList_GetVTable[];
extern char thunk_igViewList_GetMetaObject[];
extern char g_igViewList_callbackList_004cfee8[];
extern char s_igViewList_className_0051dd38[];
extern char g_igViewList_metaObject_0058c1b8[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();

void igViewList_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                   /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igViewList_metaObject_0058c1b8,    /* published MetaObject slot */
        igObjectList_Register,               /* base class registrar */
        igObjectList_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igViewList_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        s_igViewList_className_0051dd38,     /* class name */
        0x14,                                /* instance size */
        igViewList_GetVTable,                /* vtable getter */
        0,                                   /* field adder */
        0,                                   /* extra callback item */
        g_igViewList_callbackList_004cfee8   /* callback list */
    );
}
