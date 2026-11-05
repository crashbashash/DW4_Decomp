/* 0x001e5ac0 igDataPump_Register: registers class igDataPump with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igDataPump_GetVTable[];
extern char thunk_igDataPump_GetMetaObject[];
extern char igObject_Register[];
extern char g_igDataPump_callbackList_0048dbe0[];
extern char s_igDataPump_className_004e4a18[];
extern char g_igDataPump_metaObject_00562c20[];
int GpFlag_SetOnce_001e3ff0();
int igMetaObject_RegisterClass();
int igDataPump_InitFields();

void igDataPump_Register(void) {
    GpFlag_SetOnce_001e3ff0();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igDataPump_metaObject_00562c20,      /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igDataPump_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        s_igDataPump_className_004e4a18,       /* class name */
        0x1C,                                  /* instance size */
        igDataPump_GetVTable,                  /* vtable getter */
        &igDataPump_InitFields,                /* field adder */
        0,                                     /* extra callback item */
        g_igDataPump_callbackList_0048dbe0     /* callback list */
    );
}
