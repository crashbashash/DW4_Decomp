/* 0x004522c0 igColorChanger_Register: registers class igColorChanger with the object system, derived from igObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char igColorChanger_GetVTable[];
extern char thunk_igColorChanger_GetMetaObject[];
extern char s_igColorChanger_className_0051e720[];
extern char g_igColorChanger_metaObject_0058c608[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();

void igColorChanger_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                     /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igColorChanger_metaObject_0058c608,  /* published MetaObject slot */
        igObject_Register,                     /* base class registrar */
        igObject_GetMetaObject_ParentAccessor, /* base class MetaObject accessor */
        thunk_igColorChanger_GetMetaObject,    /* own MetaObject accessor (stored at +0x54) */
        s_igColorChanger_className_0051e720,   /* class name */
        8,                                     /* instance size */
        igColorChanger_GetVTable,              /* vtable getter */
        0,                                     /* field adder */
        0,                                     /* extra callback item */
        0                                      /* callback list */
    );
}
