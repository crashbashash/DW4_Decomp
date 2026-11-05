/* 0x001982a0 igSkin_Register: registers class igSkin with the object system, derived from igNamedObject.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igNamedObject_GetPublishedMetaObject_0014a6e0[];
extern char igSkin_GetVTable[];
extern char thunk_igSkin_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igSkin_callbackList_0048b550[];
extern char s_igSkin_className_004e1a68[];
extern char g_igSkin_metaObject_00561490[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();
int igSkin_InitFields();

void igSkin_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                             /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igSkin_metaObject_00561490,                  /* published MetaObject slot */
        igNamedObject_Register,                        /* base class registrar */
        igNamedObject_GetPublishedMetaObject_0014a6e0, /* base class MetaObject accessor */
        thunk_igSkin_GetMetaObject,                    /* own MetaObject accessor (stored at +0x54) */
        s_igSkin_className_004e1a68,                   /* class name */
        0x14,                                          /* instance size */
        igSkin_GetVTable,                              /* vtable getter */
        &igSkin_InitFields,                            /* field adder */
        0,                                             /* extra callback item */
        g_igSkin_callbackList_0048b550                 /* callback list */
    );
}
