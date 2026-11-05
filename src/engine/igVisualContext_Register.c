/* 0x0014a0f0 igVisualContext_Register: registers class igVisualContext with the object system, derived from igContext.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char thunk_igVisualContext_GetMetaObject[];
extern char igContext_GetPublishedMetaObject_0014a170[];
extern char igContext_Register[];
extern char g_igVisualContext_callbackList_00488300[];
extern char s_igVisualContext_className_004db700[];
extern char g_igVisualContext_metaObject_0055f8e8[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igVisualContext_InitFields();

void igVisualContext_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1,                                         /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igVisualContext_metaObject_0055f8e8,     /* published MetaObject slot */
        igContext_Register,                        /* base class registrar */
        igContext_GetPublishedMetaObject_0014a170, /* base class MetaObject accessor */
        thunk_igVisualContext_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        s_igVisualContext_className_004db700,      /* class name */
        0x140,                                     /* instance size */
        0,                                         /* vtable getter */
        &igVisualContext_InitFields,               /* field adder */
        0,                                         /* extra callback item */
        g_igVisualContext_callbackList_00488300    /* callback list */
    );
}
