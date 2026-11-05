/* 0x00132a10 igTextureBindAttr_Register: registers class igTextureBindAttr with the object system, derived from igVisualAttribute.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject_00130610[];
extern char igTextureBindAttr_GetVTable[];
extern char thunk_igTextureBindAttr_GetMetaObject[];
extern char g_igTextureBindAttr_callbackList_00485ca8[];
extern char s_igTextureBindAttr_className_004d4d90[];
extern char g_igTextureBindAttr_metaObject_0055ed88[];
int GpFlag_SetOnce_00130000();
int igMetaObject_RegisterClass();
extern int thunk_FUN_00140f40[4];
int igTextureBindAttr_InitFields();

void igTextureBindAttr_Register(void) {
    GpFlag_SetOnce_00130000();
    igMetaObject_RegisterClass(
        0,                                                 /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igTextureBindAttr_metaObject_0055ed88,           /* published MetaObject slot */
        igVisualAttribute_Register,                        /* base class registrar */
        igVisualAttribute_GetPublishedMetaObject_00130610, /* base class MetaObject accessor */
        thunk_igTextureBindAttr_GetMetaObject,             /* own MetaObject accessor (stored at +0x54) */
        s_igTextureBindAttr_className_004d4d90,            /* class name */
        0x14,                                              /* instance size */
        igTextureBindAttr_GetVTable,                       /* vtable getter */
        &igTextureBindAttr_InitFields,                     /* field adder */
        thunk_FUN_00140f40,                                /* extra callback item */
        g_igTextureBindAttr_callbackList_00485ca8          /* callback list */
    );
}
