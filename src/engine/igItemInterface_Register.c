/* 0x00227f00 igItemInterface_Register: registers class igItemInterface with the object system, derived from igInterface.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igInterface_GetPublishedMetaObject_00225cb0[];
extern char igItemInterface_GetVTable[];
extern char thunk_igItemInterface_GetMetaObject[];
extern char igInterface_Register[];
extern char g_igItemInterface_callbackList_00497dd0[];
extern char s_igItemInterface_className_004e7cb0[];
extern char g_igItemInterface_metaObject_0056d998[];
int GpFlag_SetOnce_00225770();
int igMetaObject_RegisterClass();
int igItemInterface_InitFields();

void igItemInterface_Register(void) {
    GpFlag_SetOnce_00225770();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igItemInterface_metaObject_0056d998,       /* published MetaObject slot */
        igInterface_Register,                        /* base class registrar */
        igInterface_GetPublishedMetaObject_00225cb0, /* base class MetaObject accessor */
        thunk_igItemInterface_GetMetaObject,         /* own MetaObject accessor (stored at +0x54) */
        s_igItemInterface_className_004e7cb0,        /* class name */
        0x34,                                        /* instance size */
        igItemInterface_GetVTable,                   /* vtable getter */
        &igItemInterface_InitFields,                 /* field adder */
        0,                                           /* extra callback item */
        g_igItemInterface_callbackList_00497dd0      /* callback list */
    );
}
