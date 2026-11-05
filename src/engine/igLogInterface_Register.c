/* 0x002266d0 igLogInterface_Register: registers class igLogInterface with the object system, derived from igInterface.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igInterface_GetPublishedMetaObject_00225cb0[];
extern char igLogInterface_GetVTable[];
extern char thunk_igLogInterface_GetMetaObject[];
extern char igInterface_Register[];
extern char s_igLogInterface_className_004e7ab8[];
extern char g_igLogInterface_metaObject_0056d8c8[];
int GpFlag_SetOnce_00225770();
int igMetaObject_RegisterClass();
int igLogInterface_InitFields();

void igLogInterface_Register(void) {
    GpFlag_SetOnce_00225770();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igLogInterface_metaObject_0056d8c8,        /* published MetaObject slot */
        igInterface_Register,                        /* base class registrar */
        igInterface_GetPublishedMetaObject_00225cb0, /* base class MetaObject accessor */
        thunk_igLogInterface_GetMetaObject,          /* own MetaObject accessor (stored at +0x54) */
        s_igLogInterface_className_004e7ab8,         /* class name */
        0x24,                                        /* instance size */
        igLogInterface_GetVTable,                    /* vtable getter */
        &igLogInterface_InitFields,                  /* field adder */
        0,                                           /* extra callback item */
        0                                            /* callback list */
    );
}
