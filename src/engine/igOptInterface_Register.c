/* 0x00225c20 igOptInterface_Register: registers class igOptInterface with the object system, derived from igInterface.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igOptInterface_GetVTable[];
extern char thunk_igOptInterface_GetMetaObject[];
extern char igInterface_GetPublishedMetaObject[];
extern char igInterface_Register[];
extern char g_igOptInterface_callbackList[];
extern char igOptInterface_className[];
extern char g_igOptInterface_metaObject[];
int GpFlag_SetOnce_00225770();
int igMetaObject_RegisterClass();
int igOptInterface_InitFields();

void igOptInterface_Register(void) {
    GpFlag_SetOnce_00225770();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igOptInterface_metaObject,        /* published MetaObject slot */
        igInterface_Register,                        /* base class registrar */
        igInterface_GetPublishedMetaObject, /* base class MetaObject accessor */
        thunk_igOptInterface_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        igOptInterface_className,         /* class name */
        0x30,                                        /* instance size */
        igOptInterface_GetVTable,                    /* vtable getter */
        &igOptInterface_InitFields,                  /* field adder */
        0,                                           /* extra callback item */
        g_igOptInterface_callbackList       /* callback list */
    );
}
