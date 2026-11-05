/* 0x0014f0d0 igCustomStateCollection_Register: registers class igCustomStateCollection with the object system, derived from igObjectList.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectList_GetPublishedMetaObject[];
extern char igCustomStateCollection_GetVTable[];
extern char thunk_igCustomStateCollection_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igCustomStateCollection_callbackList_00489048[];
extern char s_igCustomStateCollection_className_004dcce0[];
extern char g_igCustomStateCollection_metaObject_0055fe70[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igCustomStateCollection_InitFields();

void igCustomStateCollection_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCustomStateCollection_metaObject_0055fe70, /* published MetaObject slot */
        igObjectList_Register,                         /* base class registrar */
        igObjectList_GetPublishedMetaObject,           /* base class MetaObject accessor */
        thunk_igCustomStateCollection_GetMetaObject,   /* own MetaObject accessor (stored at +0x54) */
        s_igCustomStateCollection_className_004dcce0,  /* class name */
        0x1C,                                          /* instance size */
        igCustomStateCollection_GetVTable,             /* vtable getter */
        &igCustomStateCollection_InitFields,           /* field adder */
        0,                                             /* extra callback item */
        g_igCustomStateCollection_callbackList_00489048  /* callback list */
    );
}
