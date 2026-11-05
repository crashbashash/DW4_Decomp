/* 0x0045ca30 igFlyMode_Register: registers class igFlyMode with the object system, derived from igViewMode.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igViewMode_GetPublishedMetaObject_00368c80[];
extern char igFlyMode_GetVTable[];
extern char thunk_igFlyMode_GetMetaObject[];
extern char igViewMode_Register[];
extern char g_igFlyMode_callbackList_004d1588[];
extern char s_igFlyMode_className_0051f740[];
extern char g_igFlyMode_metaObject_0058cc80[];
int igMetaObject_RegisterClass();
int GpFlag_SetOnce_00458680();
int igFlyMode_InitFields();

void igFlyMode_Register(void) {
    GpFlag_SetOnce_00458680();
    igMetaObject_RegisterClass(
        0,                                          /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igFlyMode_metaObject_0058cc80,            /* published MetaObject slot */
        igViewMode_Register,                        /* base class registrar */
        igViewMode_GetPublishedMetaObject_00368c80, /* base class MetaObject accessor */
        thunk_igFlyMode_GetMetaObject,              /* own MetaObject accessor (stored at +0x54) */
        s_igFlyMode_className_0051f740,             /* class name */
        0xA0,                                       /* instance size */
        igFlyMode_GetVTable,                        /* vtable getter */
        &igFlyMode_InitFields,                      /* field adder */
        0,                                          /* extra callback item */
        g_igFlyMode_callbackList_004d1588           /* callback list */
    );
}
