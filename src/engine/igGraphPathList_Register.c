/* 0x0019f5b0 igGraphPathList_Register: registers class igGraphPathList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igGraphPathList_GetVTable[];
extern char thunk_igGraphPathList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igGraphPathList_callbackList[];
extern char igGraphPathList_className[];
extern char g_igGraphPathList_metaObject[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igGraphPathList_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igGraphPathList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                 /* base class registrar */
        igObjectList_GetPublishedMetaObject,   /* base class MetaObject accessor */
        thunk_igGraphPathList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igGraphPathList_className,  /* class name */
        0x14,                                  /* instance size */
        igGraphPathList_GetVTable,             /* vtable getter */
        0,                                     /* field adder */
        0,                                     /* extra callback item */
        g_igGraphPathList_callbackList  /* callback list */
    );
}
