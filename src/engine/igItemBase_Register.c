/* 0x00228960 igItemBase_Register: registers class igItemBase with the object system, derived from igBase.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igBase_GetPublishedMetaObject_00226010[];
extern char thunk_igItemBase_GetMetaObject[];
extern char igBase_Register[];
extern char s_igItemBase_className_004e7d90[];
extern char g_igItemBase_metaObject_0056d9e8[];
int GpFlag_SetOnce_00225770();
int igMetaObject_RegisterClass();

void igItemBase_Register(void) {
    GpFlag_SetOnce_00225770();
    igMetaObject_RegisterClass(
        1,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igItemBase_metaObject_0056d9e8,       /* published MetaObject slot */
        igBase_Register,                        /* base class registrar */
        igBase_GetPublishedMetaObject_00226010, /* base class MetaObject accessor */
        thunk_igItemBase_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        s_igItemBase_className_004e7d90,        /* class name */
        0x20,                                   /* instance size */
        0,                                      /* vtable getter */
        0,                                      /* field adder */
        0,                                      /* extra callback item */
        0                                       /* callback list */
    );
}
