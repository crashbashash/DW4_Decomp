/* 0x0014ef30 igCustomStateCollectionList_Register: registers class igCustomStateCollectionList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igCustomStateCollectionList_GetVTable[];
extern char thunk_igCustomStateCollectionList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igCustomStateCollectionList_callbackList_00489040[];
extern char s_igCustomStateCollectionList_className_004dccc0[];
extern char g_igCustomStateCollectionList_metaObject_0055fe68[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();

void igCustomStateCollectionList_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCustomStateCollectionList_metaObject_0055fe68, /* published MetaObject slot */
        igObjectList_Register,                             /* base class registrar */
        igObjectList_GetPublishedMetaObject,               /* base class MetaObject accessor */
        thunk_igCustomStateCollectionList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igCustomStateCollectionList_className_004dccc0,  /* class name */
        0x14,                                              /* instance size */
        igCustomStateCollectionList_GetVTable,             /* vtable getter */
        0,                                                 /* field adder */
        0,                                                 /* extra callback item */
        g_igCustomStateCollectionList_callbackList_00489040  /* callback list */
    );
}
