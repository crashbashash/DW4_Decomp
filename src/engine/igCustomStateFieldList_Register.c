/* 0x0014ea60 igCustomStateFieldList_Register: registers class igCustomStateFieldList with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igCustomStateFieldList_GetVTable[];
extern char thunk_igCustomStateFieldList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igCustomStateFieldList_callbackList[];
extern char igCustomStateFieldList_className[];
extern char g_igCustomStateFieldList_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();

void igCustomStateFieldList_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCustomStateFieldList_metaObject, /* published MetaObject slot */
        igObjectList_Register,                        /* base class registrar */
        igObjectList_GetPublishedMetaObject,          /* base class MetaObject accessor */
        thunk_igCustomStateFieldList_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        igCustomStateFieldList_className,  /* class name */
        0x14,                                         /* instance size */
        igCustomStateFieldList_GetVTable,             /* vtable getter */
        0,                                            /* field adder */
        0,                                            /* extra callback item */
        g_igCustomStateFieldList_callbackList  /* callback list */
    );
}
