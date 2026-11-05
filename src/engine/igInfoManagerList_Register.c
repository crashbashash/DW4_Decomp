/* 0x00233840 igInfoManagerList_Register: registers class igInfoManagerList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igInfoManagerList_GetVTable[];
extern char thunk_igInfoManagerList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igInfoManagerList_callbackList_00498240[];
extern char s_igInfoManagerList_className_004e8770[];
extern char g_igInfoManagerList_metaObject_0056dc30[];
int GpFlag_SetOnce_00230f50();
int igMetaObject_RegisterClass();

void igInfoManagerList_Register(void) {
    GpFlag_SetOnce_00230f50();
    igMetaObject_RegisterClass(
        0,                                       /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igInfoManagerList_metaObject_0056dc30, /* published MetaObject slot */
        igObjectList_Register,                   /* base class registrar */
        igObjectList_GetPublishedMetaObject,     /* base class MetaObject accessor */
        thunk_igInfoManagerList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igInfoManagerList_className_004e8770,  /* class name */
        0x14,                                    /* instance size */
        igInfoManagerList_GetVTable,             /* vtable getter */
        0,                                       /* field adder */
        0,                                       /* extra callback item */
        g_igInfoManagerList_callbackList_00498240  /* callback list */
    );
}
