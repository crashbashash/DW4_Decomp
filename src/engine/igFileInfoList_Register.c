/* 0x00228de0 igFileInfoList_Register: registers class igFileInfoList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igFileInfoList_GetVTable[];
extern char thunk_igFileInfoList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igFileInfoList_callbackList_00497f08[];
extern char s_igFileInfoList_className_004e7e28[];
extern char g_igFileInfoList_metaObject_0056da30[];
int GpFlag_SetOnce_00225770();
int igMetaObject_RegisterClass();

void igFileInfoList_Register(void) {
    GpFlag_SetOnce_00225770();
    igMetaObject_RegisterClass(
        0,                                    /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igFileInfoList_metaObject_0056da30, /* published MetaObject slot */
        igObjectList_Register,                /* base class registrar */
        igObjectList_GetPublishedMetaObject,  /* base class MetaObject accessor */
        thunk_igFileInfoList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igFileInfoList_className_004e7e28,  /* class name */
        0x14,                                 /* instance size */
        igFileInfoList_GetVTable,             /* vtable getter */
        0,                                    /* field adder */
        0,                                    /* extra callback item */
        g_igFileInfoList_callbackList_00497f08  /* callback list */
    );
}
