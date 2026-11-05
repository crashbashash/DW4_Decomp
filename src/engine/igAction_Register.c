/* 0x00453300 igAction_Register: registers class igAction with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char thunk_igAction_GetMetaObject[];
extern char s_igAction_className_0051e800[];
extern char g_igAction_metaObject_0058c658[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();

void igAction_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        1,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAction_metaObject_0058c658,        /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igAction_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        s_igAction_className_0051e800,         /* class name */
        8,                                     /* instance size */
        0,                                     /* vtable getter */
        0,                                     /* field adder */
        0,                                     /* extra callback item */
        0                                      /* callback list */
    );
}
