/* 0x001a92a0 igAnimation_Register: registers class igAnimation with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject_0014a6e0[];
extern char igAnimation_GetVTable[];
extern char thunk_igAnimation_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igAnimation_callbackList_0048d4f0[];
extern char s_igAnimation_className_004e4110[];
extern char g_igAnimation_metaObject_00562370[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igAnimation_InitFields();

void igAnimation_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igAnimation_metaObject_00562370,             /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject_0014a6e0, /* base class MetaObject accessor */
        thunk_igAnimation_GetMetaObject,               /* own MetaObject accessor (stored at +0x54) */
        s_igAnimation_className_004e4110,              /* class name */
        0x40,                                          /* instance size */
        igAnimation_GetVTable,                         /* vtable getter */
        &igAnimation_InitFields,                       /* field adder */
        0,                                             /* extra callback item */
        g_igAnimation_callbackList_0048d4f0            /* callback list */
    );
}
