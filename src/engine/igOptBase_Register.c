/* 0x00225f90 igOptBase_Register: registers class igOptBase with the object system, derived from igBase.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char thunk_igOptBase_GetMetaObject[];
extern char igBase_GetPublishedMetaObject[];
extern char igBase_Register[];
extern char g_igOptBase_callbackList[];
extern char igOptBase_className[];
extern char g_igOptBase_metaObject[];
int GpFlag_SetOnce_00225770();
int igMetaObject_RegisterClass();
int igOptBase_InitFields();

void igOptBase_Register(void) {
    GpFlag_SetOnce_00225770();
    igMetaObject_RegisterClass(
        1,                                      /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igOptBase_metaObject,        /* published MetaObject slot */
        igBase_Register,                        /* base class registrar */
        igBase_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igOptBase_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        igOptBase_className,         /* class name */
        0x28,                                   /* instance size */
        0,                                      /* vtable getter */
        &igOptBase_InitFields,                  /* field adder */
        0,                                      /* extra callback item */
        g_igOptBase_callbackList       /* callback list */
    );
}
