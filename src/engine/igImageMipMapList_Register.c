/* 0x001330e0 igImageMipMapList_Register: registers class igImageMipMapList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igImageMipMapList_GetVTable[];
extern char thunk_igImageMipMapList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igImageMipMapList_callbackList[];
extern char igImageMipMapList_className[];
extern char g_igImageMipMapList_metaObject[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();

void igImageMipMapList_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igImageMipMapList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                   /* base class registrar */
        igObjectList_GetPublishedMetaObject,     /* base class MetaObject accessor */
        thunk_igImageMipMapList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igImageMipMapList_className,  /* class name */
        0x14,                                    /* instance size */
        igImageMipMapList_GetVTable,             /* vtable getter */
        0,                                       /* field adder */
        0,                                       /* extra callback item */
        g_igImageMipMapList_callbackList  /* callback list */
    );
}
