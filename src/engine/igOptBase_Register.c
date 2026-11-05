/* 0x00225f90 igOptBase_Register: registers class igOptBase with the object system, derived from igBase.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char thunk_igOptBase_GetMetaObject[];
extern char igBase_GetPublishedMetaObject_00226010[];
extern char igBase_Register[];
extern char g_igOptBase_callbackList_00497c00[];
extern char s_igOptBase_className_004e7a58[];
extern char g_igOptBase_metaObject_0056d890[];
int GpFlag_SetOnce_00225770();
int igMetaObject_RegisterClass();
int igOptBase_InitFields();

void igOptBase_Register(void) {
    GpFlag_SetOnce_00225770();
    igMetaObject_RegisterClass(
        1,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igOptBase_metaObject_0056d890,        /* published MetaObject slot */
        igBase_Register,                        /* base class registrar */
        igBase_GetPublishedMetaObject_00226010, /* base class MetaObject accessor */
        thunk_igOptBase_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        s_igOptBase_className_004e7a58,         /* class name */
        0x28,                                   /* instance size */
        0,                                      /* vtable getter */
        &igOptBase_InitFields,                  /* field adder */
        0,                                      /* extra callback item */
        g_igOptBase_callbackList_00497c00       /* callback list */
    );
}
