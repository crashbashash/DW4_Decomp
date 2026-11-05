/* 0x00226210 igMessageInterface_Register: registers class igMessageInterface with the object system, derived from igInterface.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igInterface_GetPublishedMetaObject_00225cb0[];
extern char igMessageInterface_GetVTable[];
extern char thunk_igMessageInterface_GetMetaObject[];
extern char igInterface_Register[];
extern char g_igMessageInterface_callbackList_00497c30[];
extern char s_igMessageInterface_className_004e7a70[];
extern char g_igMessageInterface_metaObject_0056d8a8[];
int GpFlag_SetOnce_00225770();
int igMetaObject_RegisterClass();
int igMessageInterface_InitFields();

void igMessageInterface_Register(void) {
    GpFlag_SetOnce_00225770();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMessageInterface_metaObject_0056d8a8,    /* published MetaObject slot */
        igInterface_Register,                        /* base class registrar */
        igInterface_GetPublishedMetaObject_00225cb0, /* base class MetaObject accessor */
        thunk_igMessageInterface_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        s_igMessageInterface_className_004e7a70,     /* class name */
        0x24,                                        /* instance size */
        igMessageInterface_GetVTable,                /* vtable getter */
        &igMessageInterface_InitFields,              /* field adder */
        0,                                           /* extra callback item */
        g_igMessageInterface_callbackList_00497c30   /* callback list */
    );
}
