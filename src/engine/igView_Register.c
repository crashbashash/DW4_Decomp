/* 0x0044bbc0 igView_Register: registers class igView with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char thunk_igView_GetMetaObject[];
extern char g_igView_callbackList_004cfef0[];
extern char s_igView_className_0051dd48[];
extern char g_igView_metaObject_0058c1c0[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();
int igView_InitFields();

void igView_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        1,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igView_metaObject_0058c1c0,          /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igView_GetMetaObject,            /* own MetaObject accessor (stored at +0x54) */
        s_igView_className_0051dd48,           /* class name */
        0xC,                                   /* instance size */
        0,                                     /* vtable getter */
        &igView_InitFields,                    /* field adder */
        0,                                     /* extra callback item */
        g_igView_callbackList_004cfef0         /* callback list */
    );
}
