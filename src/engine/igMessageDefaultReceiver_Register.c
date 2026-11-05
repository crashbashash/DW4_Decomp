/* 0x00232330 igMessageDefaultReceiver_Register: registers class igMessageDefaultReceiver with the object system, derived from igMessageReceiver.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igMessageReceiver_Register[];
extern char igMessageDefaultReceiver_GetVTable[];
extern char thunk_igMessageDefaultReceiver_GetMetaObject[];
extern char igMessageReceiver_GetPublishedMetaObject_002323c0[];
extern char g_igMessageDefaultReceiver_callbackList_00498040[];
extern char s_igMessageDefaultReceiver_className_004e8530[];
extern char g_igMessageDefaultReceiver_metaObject_0056db30[];
int GpFlag_SetOnce_00230f50();
int igMetaObject_RegisterClass();
int igMessageDefaultReceiver_InitFields();

void igMessageDefaultReceiver_Register(void) {
    GpFlag_SetOnce_00230f50();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMessageDefaultReceiver_metaObject_0056db30,    /* published MetaObject slot */
        igMessageReceiver_Register,                        /* base class registrar */
        igMessageReceiver_GetPublishedMetaObject_002323c0, /* base class MetaObject accessor */
        thunk_igMessageDefaultReceiver_GetMetaObject,      /* own MetaObject accessor (stored at +0x54) */
        s_igMessageDefaultReceiver_className_004e8530,     /* class name */
        0x18,                                              /* instance size */
        igMessageDefaultReceiver_GetVTable,                /* vtable getter */
        &igMessageDefaultReceiver_InitFields,              /* field adder */
        0,                                                 /* extra callback item */
        g_igMessageDefaultReceiver_callbackList_00498040   /* callback list */
    );
}
