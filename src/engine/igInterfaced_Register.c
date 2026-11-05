/* 0x00228a30 igInterfaced_Register: registers class igInterfaced with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igInterfaced_GetMetaObject[];
extern char igObject_Register[];
extern char g_igInterfaced_callbackList_00497e70[];
extern char s_igInterfaced_className_004e7da0[];
extern char g_igInterfaced_metaObject_0056d9f0[];
int GpFlag_SetOnce_00225770();
int igMetaObject_RegisterClass();
int igInterfaced_InitFields();

void igInterfaced_Register(void) {
    GpFlag_SetOnce_00225770();
    igMetaObject_RegisterClass(
        1,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igInterfaced_metaObject_0056d9f0,    /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igInterfaced_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        s_igInterfaced_className_004e7da0,     /* class name */
        0x20,                                  /* instance size */
        0,                                     /* vtable getter */
        &igInterfaced_InitFields,              /* field adder */
        0,                                     /* extra callback item */
        g_igInterfaced_callbackList_00497e70   /* callback list */
    );
}
