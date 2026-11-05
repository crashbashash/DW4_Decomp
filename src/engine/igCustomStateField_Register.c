/* 0x0014ece0 igCustomStateField_Register: registers class igCustomStateField with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject_0014a6e0[];
extern char igCustomStateField_GetVTable[];
extern char thunk_igCustomStateField_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igCustomStateField_callbackList_00489018[];
extern char s_igCustomStateField_className_004dcc70[];
extern char g_igCustomStateField_metaObject_0055fe50[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igCustomStateField_InitFields();

void igCustomStateField_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igCustomStateField_metaObject_0055fe50,      /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject_0014a6e0, /* base class MetaObject accessor */
        thunk_igCustomStateField_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        s_igCustomStateField_className_004dcc70,       /* class name */
        0x14,                                          /* instance size */
        igCustomStateField_GetVTable,                  /* vtable getter */
        &igCustomStateField_InitFields,                /* field adder */
        0,                                             /* extra callback item */
        g_igCustomStateField_callbackList_00489018     /* callback list */
    );
}
