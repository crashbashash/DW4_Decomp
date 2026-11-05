/* 0x00226e40 igListenerInterface_Register: registers class igListenerInterface with the object system, derived from igInterface.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igInterface_GetPublishedMetaObject_00225cb0[];
extern char igListenerInterface_GetVTable[];
extern char thunk_igListenerInterface_GetMetaObject[];
extern char igInterface_Register[];
extern char g_igListenerInterface_callbackList_00497cd0[];
extern char s_igListenerInterface_className_004e7b50[];
extern char g_igListenerInterface_metaObject_0056d900[];
int GpFlag_SetOnce_00225770();
int igMetaObject_RegisterClass();
int igListenerInterface_InitFields();

void igListenerInterface_Register(void) {
    GpFlag_SetOnce_00225770();
    igMetaObject_RegisterClass(
        0,                                           /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igListenerInterface_metaObject_0056d900,   /* published MetaObject slot */
        igInterface_Register,                        /* base class registrar */
        igInterface_GetPublishedMetaObject_00225cb0, /* base class MetaObject accessor */
        thunk_igListenerInterface_GetMetaObject,     /* own MetaObject accessor (stored at +0x54) */
        s_igListenerInterface_className_004e7b50,    /* class name */
        0x30,                                        /* instance size */
        igListenerInterface_GetVTable,               /* vtable getter */
        &igListenerInterface_InitFields,             /* field adder */
        0,                                           /* extra callback item */
        g_igListenerInterface_callbackList_00497cd0  /* callback list */
    );
}
