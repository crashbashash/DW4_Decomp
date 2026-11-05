/* 0x00197370 igSorter_Register: registers class igSorter with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igSorter_GetVTable[];
extern char thunk_igSorter_GetMetaObject[];
extern char igObject_Register[];
extern char g_igSorter_callbackList_0048b240[];
extern char s_igSorter_className_004e1640[];
extern char g_igSorter_metaObject_00561318[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igSorter_InitFields();

void igSorter_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igSorter_metaObject_00561318,        /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igSorter_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        s_igSorter_className_004e1640,         /* class name */
        0x84,                                  /* instance size */
        igSorter_GetVTable,                    /* vtable getter */
        &igSorter_InitFields,                  /* field adder */
        0,                                     /* extra callback item */
        g_igSorter_callbackList_0048b240       /* callback list */
    );
}
