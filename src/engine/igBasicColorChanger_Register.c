/* 0x004520b0 igBasicColorChanger_Register: registers class igBasicColorChanger with the object system, derived from igColorChanger.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igBasicColorChanger_GetVTable[];
extern char thunk_igBasicColorChanger_GetMetaObject[];
extern char igColorChanger_GetPublishedMetaObject[];
extern char igColorChanger_Register[];
extern char igBasicColorChanger_className[];
extern char g_igBasicColorChanger_metaObject[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_0044b860();
int igBasicColorChanger_InitFields();

void igBasicColorChanger_Register(void) {
    GpFlag_SetOnce_0044b860();
    igMetaObject_RegisterClass(
        0,                                              /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igBasicColorChanger_metaObject,      /* published MetaObject slot */
        igColorChanger_Register,                        /* base class registrar */
        igColorChanger_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igBasicColorChanger_GetMetaObject,        /* own MetaObject accessor (stored at +0x54) */
        igBasicColorChanger_className,       /* class name */
        0x58,                                           /* instance size */
        igBasicColorChanger_GetVTable,                  /* vtable getter */
        &igBasicColorChanger_InitFields,                /* field adder */
        0,                                              /* extra callback item */
        0                                               /* callback list */
    );
}
